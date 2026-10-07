#include "control.h"
#include <Arduino.h>
#include "driver/pcnt.h"
#include "driver/mcpwm.h"
#include "freertos/semphr.h"
#include <Preferences.h>

// ---------------------------------------------------------------------------
// Fixed constants. Limits that the Settings tab edits (max/min RPM, max duty,
// encoder resolution) live in s_shared and are persisted in NVS.
// ---------------------------------------------------------------------------
static const int SAMPLE_HZ = 1000;                 // PID tick rate
static const int DEFAULT_ENCODER_RESOLUTION = 96;   // tach transitions/rev
static const int DEFAULT_MAX_RPM = 3000;
static const int DEFAULT_MIN_RPM = 50;
static const int DEFAULT_MAX_DUTY = 90;
static const int STATS_WINDOW_TICKS = SAMPLE_HZ / 10; // 100ms window for RPM/pulse-rate/load reporting
static const int STALL_TIMEOUT_TICKS = SAMPLE_HZ / 5;   // ~200ms, matches original PIC18 behavior
static const float OVERSPEED_MARGIN = 1.15f;             // trip if actual > MAX_RPM * margin
static const float STARTUP_RAMP_PERCENT_PER_TICK = 0.05f; // slow-start limiter

// ---------------------------------------------------------------------------
// Shared state - guarded by s_mutex. Only commanded (write side) + reported
// (read side) fields live here; PID-internal state (integral/derivative) is
// task-local and never touched by other tasks.
// ---------------------------------------------------------------------------
static SemaphoreHandle_t s_mutex;

static struct {
    // commanded
    int rpm_target = 0;
    bool running = false;
    bool direction_reverse = false;
    bool direct_mode = false; // true = bypass PID, open-loop duty from rpm_target
    float kp = 2.0f, ki = 0.5f, kd = 0.1f, ff = 0.0f;
    bool clear_fault_request = false;
    int max_rpm = DEFAULT_MAX_RPM;
    int min_rpm = DEFAULT_MIN_RPM;
    int max_duty = DEFAULT_MAX_DUTY;
    int enc_res = DEFAULT_ENCODER_RESOLUTION;
    // reported
    int rpm_actual = 0;
    int duty_percent = 0;
    bool stalled = false;
    bool current_limited = false;
    float current_amps = 0;
    float temperature_c = 25;
    int pulses_per_s = 0;
    int task_load_percent = 0;
} s_shared;

static Preferences s_prefs;

// Set by the fault-pin ISR the instant the comparator trips - informational
// only. The actual PWM shutdown already happened in silicon via the MCPWM
// trip-zone before this ISR even runs.
static volatile bool s_fault_isr_flag = false;
static volatile uint32_t s_tach_total = 0;

static void IRAM_ATTR fault_isr(void *arg) {
    s_fault_isr_flag = true;
}

// ---------------------------------------------------------------------------
// PID (ported from the original PIC18 PID.c - same clamped-integral /
// delayed-derivative / feed-forward algorithm, task-local state).
// ---------------------------------------------------------------------------
struct PidState {
    double integral = 0, last_error = 0, derivative = 0;
    bool integral_limited = false;
};
static PidState s_pid;

static double pid_compute(PidState &p, double kp, double ki, double kd, double ff,
                           double setpoint, double error, double out_clamp) {
    p.derivative = error - p.last_error;
    p.last_error = error;

    if (!p.integral_limited) {
        p.integral += error;
    }

    double out = error * kp + p.integral * ki + p.derivative * kd;
    if (ff != 0) out += setpoint * ff;

    if (out_clamp > 0 && fabs(out) > out_clamp) {
        out = out < 0 ? -out_clamp : out_clamp;
        p.integral_limited = true;
    } else {
        p.integral_limited = false;
    }
    return out;
}

static void pid_reset(PidState &p) {
    p.integral = 0;
    p.last_error = 0;
    p.derivative = 0;
    p.integral_limited = false;
}

// ---------------------------------------------------------------------------
// Hardware init
// ---------------------------------------------------------------------------
static void tach_pcnt_init() {
    pcnt_config_t cfg = {};
    cfg.pulse_gpio_num = PIN_TACH;
    cfg.ctrl_gpio_num = -1; // no control pin, count regardless of level
    cfg.lctrl_mode = PCNT_MODE_KEEP;
    cfg.hctrl_mode = PCNT_MODE_KEEP;
    cfg.pos_mode = PCNT_COUNT_INC;  // count rising edges
    cfg.neg_mode = PCNT_COUNT_DIS;
    cfg.counter_h_lim = 30000;
    cfg.counter_l_lim = -30000;
    cfg.unit = PCNT_UNIT_0;
    cfg.channel = PCNT_CHANNEL_0;
    pcnt_unit_config(&cfg);

    pcnt_set_filter_value(PCNT_UNIT_0, 1000); // reject glitches shorter than ~12.5us @ 80MHz APB
    pcnt_filter_enable(PCNT_UNIT_0);

    pcnt_counter_pause(PCNT_UNIT_0);
    pcnt_counter_clear(PCNT_UNIT_0);
    pcnt_counter_resume(PCNT_UNIT_0);
}

static void pwm_mcpwm_init() {
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, PIN_PWM);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_FAULT_0, PIN_FAULT);

    mcpwm_config_t pwm_config = {};
    pwm_config.frequency = 25000; // 25kHz, matches the original PIC18 PWM frequency
    pwm_config.cmpr_a = 0;
    pwm_config.cmpr_b = 0;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, MCPWM_DUTY_MODE_0);

    // Hardware trip-zone: comparator output on PIN_FAULT forces the PWM
    // output low the instant it goes high, in silicon, independent of any
    // task/ISR/WiFi activity. Oneshot mode latches until re-armed below.
    mcpwm_fault_init(MCPWM_UNIT_0, MCPWM_HIGH_LEVEL_TGR, MCPWM_SELECT_F0);
    mcpwm_fault_set_oneshot_mode(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_SELECT_F0,
                                  MCPWM_ACTION_FORCE_LOW, MCPWM_ACTION_FORCE_LOW);

    pinMode(PIN_FAULT, INPUT);
    attachInterruptArg(PIN_FAULT, fault_isr, nullptr, RISING);
}

static void rearm_trip_zone() {
    mcpwm_fault_init(MCPWM_UNIT_0, MCPWM_HIGH_LEVEL_TGR, MCPWM_SELECT_F0);
    mcpwm_fault_set_oneshot_mode(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_SELECT_F0,
                                  MCPWM_ACTION_FORCE_LOW, MCPWM_ACTION_FORCE_LOW);
}

static void set_duty_percent(float percent, float max_duty) {
    if (percent < 0) percent = 0;
    if (percent > max_duty) percent = max_duty;
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, percent);
}

// ---------------------------------------------------------------------------
// Sensor reads - formulas below are placeholders. Replace the constants with
// your actual Hall-sensor sensitivity/offset and NTC Beta/R0 once the parts
// are chosen; see the hardware-recommendations discussion for context.
// ---------------------------------------------------------------------------
static float read_current_amps() {
    int raw = analogRead(PIN_CURRENT_ADC); // 0-4095 @ 12-bit, 0-3.3V
    float volts = (raw / 4095.0f) * 3.3f;
    const float quiescent_v = 1.65f;  // sensor output at 0A (mid-rail, bidirectional sensor)
    const float sensitivity_v_per_a = 0.066f; // V/A - TODO: match chosen Hall IC datasheet
    return (volts - quiescent_v) / sensitivity_v_per_a;
}

static float read_temperature_c() {
    int raw = analogRead(PIN_TEMP_ADC);
    if (raw <= 0) raw = 1;
    float volts = (raw / 4095.0f) * 3.3f;
    const float series_r = 10000.0f; // ohms, NTC in a divider from 3.3V
    float ntc_r = series_r * (3.3f / volts - 1.0f);
    const float beta = 3950.0f, r0 = 10000.0f, t0 = 298.15f; // 25C reference
    float kelvin = 1.0f / (1.0f / t0 + log(ntc_r / r0) / beta);
    return kelvin - 273.15f;
}

// ---------------------------------------------------------------------------
// Control task - the only place that touches PCNT/MCPWM/PID state. Runs at
// SAMPLE_HZ via vTaskDelayUntil, pinned to core 1, away from WiFi (core 0).
// ---------------------------------------------------------------------------
static void control_task(void *arg) {
    const TickType_t period = pdMS_TO_TICKS(1000 / SAMPLE_HZ);
    TickType_t lastWake = xTaskGetTickCount();
    int stall_ticks = 0;
    int temp_sample_divider = 0;
    int window_ticks = 0;
    long window_pulses = 0;
    uint32_t window_busy_us = 0;
    int reported_rpm = 0, reported_pulses_per_s = 0, reported_load = 0;

    for (;;) {
        vTaskDelayUntil(&lastWake, period);
        uint32_t tick_start_us = micros();

        int16_t raw_count = 0;
        pcnt_get_counter_value(PCNT_UNIT_0, &raw_count);
        pcnt_counter_clear(PCNT_UNIT_0);
        int count_this_tick = raw_count;
        if (raw_count > 0) s_tach_total += raw_count;

        // Snapshot commanded values.
        int rpm_target; bool running, direction_reverse, clear_fault_request, direct_mode;
        float kp, ki, kd, ff;
        int max_rpm, min_rpm, enc_res;
        float max_duty;
        xSemaphoreTake(s_mutex, portMAX_DELAY);
        max_rpm = s_shared.max_rpm;
        min_rpm = s_shared.min_rpm;
        enc_res = s_shared.enc_res;
        max_duty = (float)s_shared.max_duty;
        rpm_target = s_shared.rpm_target;
        running = s_shared.running;
        direction_reverse = s_shared.direction_reverse;
        direct_mode = s_shared.direct_mode;
        kp = s_shared.kp; ki = s_shared.ki; kd = s_shared.kd; ff = s_shared.ff;
        clear_fault_request = s_shared.clear_fault_request;
        s_shared.clear_fault_request = false;
        xSemaphoreGive(s_mutex);

        if (clear_fault_request) {
            stall_ticks = 0;
            s_fault_isr_flag = false;
            rearm_trip_zone();
        }

        digitalWrite(PIN_DIR, direction_reverse ? HIGH : LOW);

        // Instantaneous RPM estimate from this tick's pulse count. Coarse at
        // low speed/low encoder resolution - see design notes for the
        // period-measurement (M/T method) upgrade path.
        int rpm_actual = (int)((long)count_this_tick * 60L * SAMPLE_HZ / enc_res);

        bool hw_fault_latched = s_fault_isr_flag;
        bool overspeed = rpm_actual > (int)(max_rpm * OVERSPEED_MARGIN);

        bool stalled = false;
        if (!direct_mode && running && rpm_target >= min_rpm && count_this_tick == 0) {
            // Stall detection relies on tach feedback, so it only applies in
            // PID mode - direct/open-loop mode is specifically meant to run
            // without depending on a working tachometer.
            if (++stall_ticks >= STALL_TIMEOUT_TICKS) stalled = true;
        } else {
            stall_ticks = 0;
        }

        float duty = 0;
        if (running && !hw_fault_latched && !overspeed && !stalled) {
            double raw;
            if (direct_mode) {
                // Open-loop: duty tracks rpm_target via a fixed linear map,
                // no error correction - PID state stays reset so switching
                // back to PID mode doesn't resume with stale integral/derivative.
                raw = ((double)rpm_target / max_rpm) * max_duty;
                pid_reset(s_pid);
            } else {
                double setpoint = (rpm_target >= min_rpm)
                    ? (((double)rpm_target / 60.0) * enc_res) / SAMPLE_HZ
                    : 0;
                double error = setpoint - (double)count_this_tick;
                raw = pid_compute(s_pid, kp, ki, kd, ff, setpoint, error, max_duty);
            }
            if (raw < 0) raw = 0;

            // Slow-start: ramp the applied duty towards the PID's output,
            // and hold the integral term while the ramp (not the PID itself)
            // is what's actually limiting output - avoids the windup gap
            // noted in the original PIC18 code.
            static float startup_duty = 0;
            if (startup_duty < raw) {
                startup_duty += STARTUP_RAMP_PERCENT_PER_TICK;
                s_pid.integral_limited = true;
            }
            duty = (startup_duty < raw) ? startup_duty : (float)raw;
        } else {
            pid_reset(s_pid);
        }

        if (stalled || overspeed) {
            running = false;
            duty = 0;
        }
        if (hw_fault_latched) {
            running = false;
            duty = 0;
        }

        set_duty_percent(duty, max_duty);

        if (++temp_sample_divider >= 100) { // ~10Hz - thermal is slow, no need for 1kHz
            temp_sample_divider = 0;
        }
        float current_amps = read_current_amps();
        float temperature_c = read_temperature_c();
        bool overtemp = temperature_c > 95.0f;

        // Single-tick pulse counts are too coarse to display (1 pulse = 625 rpm
        // at 96 PPR/1kHz), so report values averaged over a 100ms window.
        window_pulses += count_this_tick;
        window_busy_us += micros() - tick_start_us;
        if (++window_ticks >= STATS_WINDOW_TICKS) {
            reported_pulses_per_s = (int)(window_pulses * SAMPLE_HZ / window_ticks);
            reported_rpm = (int)((long)reported_pulses_per_s * 60L / enc_res);
            reported_load = (int)(window_busy_us / (window_ticks * (1000000UL / SAMPLE_HZ) / 100));
            window_ticks = 0;
            window_pulses = 0;
            window_busy_us = 0;
        }

        xSemaphoreTake(s_mutex, portMAX_DELAY);
        s_shared.running = running && !stalled && !hw_fault_latched && !overspeed;
        s_shared.rpm_actual = reported_rpm;
        s_shared.pulses_per_s = reported_pulses_per_s;
        s_shared.task_load_percent = reported_load;
        s_shared.duty_percent = (int)duty;
        s_shared.stalled = stalled;
        s_shared.current_limited = hw_fault_latched || overspeed || overtemp;
        s_shared.current_amps = current_amps;
        s_shared.temperature_c = temperature_c;
        xSemaphoreGive(s_mutex);
    }
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------
// A single tach pulse in one 1ms tick must stay below the overspeed trip
// point, otherwise the coarse per-tick RPM estimate would false-trip.
static bool settings_valid(const control_settings_t &s) {
    if (s.max_rpm < 100 || s.max_rpm > 20000) return false;
    if (s.min_rpm < 0 || s.min_rpm >= s.max_rpm) return false;
    if (s.max_duty < 10 || s.max_duty > 100) return false;
    if (s.enc_res < 1 || s.enc_res > 2000) return false;
    if (60L * SAMPLE_HZ / s.enc_res >= (long)(s.max_rpm * OVERSPEED_MARGIN)) return false;
    return true;
}

void control_init() {
    s_mutex = xSemaphoreCreateMutex();

    // Load persisted gains/limits before the control task starts. Missing
    // keys keep the compiled defaults; invalid saved limits are ignored.
    s_prefs.begin("control", true);
    s_shared.kp = s_prefs.getFloat("kp", s_shared.kp);
    s_shared.ki = s_prefs.getFloat("ki", s_shared.ki);
    s_shared.kd = s_prefs.getFloat("kd", s_shared.kd);
    s_shared.ff = s_prefs.getFloat("ff", s_shared.ff);
    control_settings_t saved = {
        s_prefs.getInt("max_rpm", s_shared.max_rpm),
        s_prefs.getInt("min_rpm", s_shared.min_rpm),
        s_prefs.getInt("max_duty", s_shared.max_duty),
        s_prefs.getInt("enc_res", s_shared.enc_res),
    };
    s_prefs.end();
    if (settings_valid(saved)) {
        s_shared.max_rpm = saved.max_rpm;
        s_shared.min_rpm = saved.min_rpm;
        s_shared.max_duty = saved.max_duty;
        s_shared.enc_res = saved.enc_res;
    }

    pinMode(PIN_DIR, OUTPUT);
    digitalWrite(PIN_DIR, LOW);
    analogReadResolution(12);

    tach_pcnt_init();
    pwm_mcpwm_init();

    xTaskCreatePinnedToCore(control_task, "control", 4096, NULL, 10, NULL, 1);
}

void control_set_rpm_target(int rpm) {
    if (rpm < 0) rpm = 0;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    if (rpm > s_shared.max_rpm) rpm = s_shared.max_rpm;
    s_shared.rpm_target = rpm;
    xSemaphoreGive(s_mutex);
}

void control_set_pid_gains(float kp, float ki, float kd, float ff) {
    if (kp < 0) kp = 0;
    if (ki < 0) ki = 0;
    if (kd < 0) kd = 0;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    s_shared.kp = kp; s_shared.ki = ki; s_shared.kd = kd; s_shared.ff = ff;
    xSemaphoreGive(s_mutex);
}

void control_start() {
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    if (!s_shared.stalled && !s_shared.current_limited) {
        s_shared.running = true;
    }
    xSemaphoreGive(s_mutex);
}

void control_stop() {
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    s_shared.running = false;
    xSemaphoreGive(s_mutex);
    set_duty_percent(0, 100); // don't wait for the next tick
}

void control_set_direction(bool reverse) {
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    if (!s_shared.running) {
        s_shared.direction_reverse = reverse;
    }
    xSemaphoreGive(s_mutex);
}

void control_set_mode_direct(bool direct) {
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    s_shared.direct_mode = direct;
    xSemaphoreGive(s_mutex);
}

control_settings_t control_get_settings() {
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    control_settings_t s = { s_shared.max_rpm, s_shared.min_rpm, s_shared.max_duty, s_shared.enc_res };
    xSemaphoreGive(s_mutex);
    return s;
}

// Refused while running: changing the limits mid-run could instantly trip
// overspeed or change the PID setpoint scaling under the motor.
bool control_set_settings(const control_settings_t &s) {
    if (!settings_valid(s)) return false;
    bool ok = false;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    if (!s_shared.running) {
        s_shared.max_rpm = s.max_rpm;
        s_shared.min_rpm = s.min_rpm;
        s_shared.max_duty = s.max_duty;
        s_shared.enc_res = s.enc_res;
        if (s_shared.rpm_target > s.max_rpm) s_shared.rpm_target = s.max_rpm;
        ok = true;
    }
    xSemaphoreGive(s_mutex);
    return ok;
}

bool control_save_config() {
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    float kp = s_shared.kp, ki = s_shared.ki, kd = s_shared.kd, ff = s_shared.ff;
    int max_rpm = s_shared.max_rpm, min_rpm = s_shared.min_rpm;
    int max_duty = s_shared.max_duty, enc_res = s_shared.enc_res;
    xSemaphoreGive(s_mutex);

    if (!s_prefs.begin("control", false)) return false;
    s_prefs.putFloat("kp", kp);
    s_prefs.putFloat("ki", ki);
    s_prefs.putFloat("kd", kd);
    s_prefs.putFloat("ff", ff);
    s_prefs.putInt("max_rpm", max_rpm);
    s_prefs.putInt("min_rpm", min_rpm);
    s_prefs.putInt("max_duty", max_duty);
    s_prefs.putInt("enc_res", enc_res);
    s_prefs.end();
    return true;
}

void control_clear_fault() {
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    s_shared.stalled = false;
    s_shared.current_limited = false;
    s_shared.clear_fault_request = true;
    xSemaphoreGive(s_mutex);
}

uint32_t control_get_tach_total() {
    return s_tach_total;
}

control_status_t control_get_status() {
    control_status_t out;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    out.rpm_target = s_shared.rpm_target;
    out.rpm_actual = s_shared.rpm_actual;
    out.duty_percent = s_shared.duty_percent;
    out.running = s_shared.running;
    out.stalled = s_shared.stalled;
    out.current_limited = s_shared.current_limited;
    out.direction_reverse = s_shared.direction_reverse;
    out.direct_mode = s_shared.direct_mode;
    out.current_amps = s_shared.current_amps;
    out.temperature_c = s_shared.temperature_c;
    out.pulses_per_s = s_shared.pulses_per_s;
    out.task_load_percent = s_shared.task_load_percent;
    out.kp = s_shared.kp; out.ki = s_shared.ki; out.kd = s_shared.kd; out.ff = s_shared.ff;
    xSemaphoreGive(s_mutex);
    return out;
}

