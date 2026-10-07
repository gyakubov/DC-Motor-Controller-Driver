#pragma once
#include <stdbool.h>

// ---- Pin assignments - differ per target since GPIO/ADC maps aren't
// portable between chip variants (flash pins, UART0 pins, and which GPIOs
// are ADC-capable all differ). CONFIG_IDF_TARGET_* is set automatically by
// the Arduino-ESP32 build for whichever board/env you build.
#if CONFIG_IDF_TARGET_ESP32S3
// ESP32-S3-DevKitC-1: ADC1 covers GPIO1-10.
#define PIN_TACH        4   // Tachometer opto sensor pulse input (PCNT unit 0)
#define PIN_PWM         5   // MCPWM0A output -> gate driver IN
#define PIN_FAULT       6   // Current-limit comparator digital output -> MCPWM Fault0 (active-high)
#define PIN_DIR         7   // Motor direction relay output
#define PIN_CURRENT_ADC 1   // Hall-effect isolated current sensor analog output (ADC1)
#define PIN_TEMP_ADC    2   // MOSFET NTC thermistor analog input (ADC1)
#else
// Classic ESP32 (DevKitC/WROOM-32 etc): GPIO6-11 are reserved for the
// in-package flash, GPIO1/3 are UART0 TX/RX (Serial/flashing) - avoid both.
// ADC1 (usable with WiFi active) is only on GPIO32-39.
#define PIN_TACH        18  // Tachometer opto sensor pulse input (PCNT unit 0)
#define PIN_PWM         19  // MCPWM0A output -> gate driver IN
#define PIN_FAULT       21  // Current-limit comparator digital output -> MCPWM Fault0 (active-high)
#define PIN_DIR         22  // Motor direction relay output
#define PIN_CURRENT_ADC 34  // Hall-effect isolated current sensor analog output (ADC1_CH6, input-only)
#define PIN_TEMP_ADC    35  // MOSFET NTC thermistor analog input (ADC1_CH7, input-only)
#endif

// Starts the real-time control subsystem: PCNT (tachometer), MCPWM with a
// hardware trip-zone (current-limit / overspeed cutoff independent of
// software), ADC current/temperature sampling, and the PID task pinned to
// its own core. Call once from setup().
void control_init();

// Thread-safe command API - shared by the web (WebSocket) and CLI front ends
// so both stay in sync and share the same validation/clamping logic. All
// setters clamp/validate server-side regardless of what the caller passes.
void control_set_rpm_target(int rpm);
void control_set_pid_gains(float kp, float ki, float kd, float ff);
void control_start();
void control_stop();                      // immediate stop, no ramp
void control_set_direction(bool reverse); // ignored while running
void control_clear_fault();               // required before control_start() after a stall/trip

// Bypasses the PID algorithm: duty follows rpm_target via a fixed linear
// open-loop mapping instead of closed-loop error correction. Stall/overspeed/
// hardware trip-zone protections stay fully active in either mode.
void control_set_mode_direct(bool direct);

// Runtime limits edited from the Settings tab. Validated as a set; refused
// while the motor is running. Persisted by control_save_config().
typedef struct {
    int max_rpm;
    int min_rpm;
    int max_duty; // percent
    int enc_res;  // tach transitions per revolution
} control_settings_t;

control_settings_t control_get_settings();
bool control_set_settings(const control_settings_t &s);

// Writes the current PID gains and limits to NVS; reloaded by control_init().
bool control_save_config();

typedef struct {
    int rpm_target;
    int rpm_actual;
    int duty_percent;
    bool running;
    bool stalled;
    bool current_limited; // hardware trip-zone has latched the PWM off
    bool direction_reverse;
    bool direct_mode; // true = open-loop direct control, false = closed-loop PID
    float current_amps;
    float temperature_c;
    int pulses_per_s;       // tach pulses/s, 100ms window
    int task_load_percent;  // control-task CPU time as % of its 1ms period
    float kp, ki, kd, ff;
} control_status_t;

control_status_t control_get_status();
