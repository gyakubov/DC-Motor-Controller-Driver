#include "dro.h"
#include "../control/control.h"
#include <Arduino.h>
#include "driver/pcnt.h"
#include "freertos/semphr.h"
#include <Preferences.h>

// Hardware counter clears itself at +/-LIMIT, so the sampler unwraps deltas
// instead of reading absolute values. Per-poll travel must stay below LIMIT/2.
static const int16_t COUNTER_LIMIT = 30000;
static const int POLL_MS = 2;
static const uint16_t FILTER_CYCLES = 20; // ~250ns glitch filter @ 80MHz APB

static SemaphoreHandle_t s_mutex;
static Preferences s_prefs;
static volatile int32_t s_counts[DRO_AXES];
static int32_t s_wcs[DRO_WCS][DRO_AXES]; // work zeros, in counts
static int s_wcs_active = 0;
static bool s_inc[DRO_AXES];
static int32_t s_inc_offset[DRO_AXES];
static float s_tool_off[DRO_TOOLS][DRO_AXES]; // displayed units
static int s_tool = 0;
static dro_config_t s_cfg = { {800.0f, 800.0f}, {false, false}, true };

static const pcnt_unit_t UNITS[DRO_AXES] = { PCNT_UNIT_1, PCNT_UNIT_2 };

static void quad_init(pcnt_unit_t unit, int pin_a, int pin_b) {
    pcnt_config_t cfg = {};
    cfg.counter_h_lim = COUNTER_LIMIT;
    cfg.counter_l_lim = -COUNTER_LIMIT;
    cfg.unit = unit;
    cfg.pos_mode = PCNT_COUNT_INC;
    cfg.neg_mode = PCNT_COUNT_DEC;

    // Channel 0: edges on A, direction from the level of B.
    cfg.channel = PCNT_CHANNEL_0;
    cfg.pulse_gpio_num = pin_a;
    cfg.ctrl_gpio_num = pin_b;
    cfg.lctrl_mode = PCNT_MODE_KEEP;
    cfg.hctrl_mode = PCNT_MODE_REVERSE;
    pcnt_unit_config(&cfg);

    // Channel 1: edges on B, direction from the level of A (opposite sense).
    cfg.channel = PCNT_CHANNEL_1;
    cfg.pulse_gpio_num = pin_b;
    cfg.ctrl_gpio_num = pin_a;
    cfg.lctrl_mode = PCNT_MODE_REVERSE;
    cfg.hctrl_mode = PCNT_MODE_KEEP;
    pcnt_unit_config(&cfg);

    pcnt_set_filter_value(unit, FILTER_CYCLES);
    pcnt_filter_enable(unit);
    pcnt_counter_pause(unit);
    pcnt_counter_clear(unit);
    pcnt_counter_resume(unit);
}

static void dro_task(void *arg) {
    const TickType_t period = pdMS_TO_TICKS(POLL_MS);
    TickType_t last_wake = xTaskGetTickCount();
    int16_t last[DRO_AXES] = {0, 0};
    int32_t total[DRO_AXES] = {0, 0};

    for (;;) {
        vTaskDelayUntil(&last_wake, period);
        for (int a = 0; a < DRO_AXES; a++) {
            int16_t now = 0;
            pcnt_get_counter_value(UNITS[a], &now);
            int32_t d = (int32_t)now - last[a];
            if (d > COUNTER_LIMIT / 2) d -= COUNTER_LIMIT;
            else if (d < -COUNTER_LIMIT / 2) d += COUNTER_LIMIT;
            last[a] = now;
            total[a] += d;
            s_counts[a] = total[a];
        }
    }
}

static bool config_valid(const dro_config_t &c) {
    for (int a = 0; a < DRO_AXES; a++) {
        if (!(c.counts_per_mm[a] >= 1.0f && c.counts_per_mm[a] <= 100000.0f)) return false;
    }
    return true;
}

// Caller holds s_mutex.
static float axis_scale(int axis) {
    float k = (axis == DRO_X && s_cfg.x_diameter) ? 2.0f : 1.0f;
    float sign = s_cfg.invert[axis] ? -1.0f : 1.0f;
    return sign * k / s_cfg.counts_per_mm[axis]; // mm per count
}

// Caller holds s_mutex.
static float disp(int a) {
    if (s_inc[a]) return (float)(s_counts[a] - s_inc_offset[a]) * axis_scale(a);
    return (float)(s_counts[a] - s_wcs[s_wcs_active][a]) * axis_scale(a) + s_tool_off[s_tool][a];
}

// Caller holds s_mutex. Moves the active zero so the axis reads v.
static void set_display(int a, float v) {
    if (s_inc[a]) s_inc_offset[a] = s_counts[a] - lroundf(v / axis_scale(a));
    else s_wcs[s_wcs_active][a] = s_counts[a] - lroundf((v - s_tool_off[s_tool][a]) / axis_scale(a));
}

static void save_tools() {
    float off[DRO_TOOLS][DRO_AXES];
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    memcpy(off, s_tool_off, sizeof(off));
    int tool = s_tool;
    xSemaphoreGive(s_mutex);

    if (!s_prefs.begin("dro", false)) return;
    char key[8];
    for (int t = 0; t < DRO_TOOLS; t++) {
        snprintf(key, sizeof(key), "tz%d", t);
        s_prefs.putFloat(key, off[t][DRO_Z]);
        snprintf(key, sizeof(key), "tx%d", t);
        s_prefs.putFloat(key, off[t][DRO_X]);
    }
    s_prefs.putUChar("tool", (uint8_t)tool);
    s_prefs.end();
}

void dro_init() {
    s_mutex = xSemaphoreCreateMutex();

    s_prefs.begin("dro", true);
    dro_config_t saved = s_cfg;
    saved.counts_per_mm[DRO_Z] = s_prefs.getFloat("z_cpm", saved.counts_per_mm[DRO_Z]);
    saved.counts_per_mm[DRO_X] = s_prefs.getFloat("x_cpm", saved.counts_per_mm[DRO_X]);
    saved.invert[DRO_Z] = s_prefs.getBool("z_inv", saved.invert[DRO_Z]);
    saved.invert[DRO_X] = s_prefs.getBool("x_inv", saved.invert[DRO_X]);
    saved.x_diameter = s_prefs.getBool("x_dia", saved.x_diameter);
    char key[8];
    for (int t = 0; t < DRO_TOOLS; t++) {
        snprintf(key, sizeof(key), "tz%d", t);
        s_tool_off[t][DRO_Z] = s_prefs.getFloat(key, 0.0f);
        snprintf(key, sizeof(key), "tx%d", t);
        s_tool_off[t][DRO_X] = s_prefs.getFloat(key, 0.0f);
    }
    uint8_t tool = s_prefs.getUChar("tool", 0);
    if (tool < DRO_TOOLS) s_tool = tool;
    s_prefs.end();
    if (config_valid(saved)) s_cfg = saved;

    quad_init(UNITS[DRO_Z], PIN_DRO_Z_A, PIN_DRO_Z_B);
    quad_init(UNITS[DRO_X], PIN_DRO_X_A, PIN_DRO_X_B);

    xTaskCreatePinnedToCore(dro_task, "dro", 3072, NULL, 5, NULL, 1);
}

dro_state_t dro_get_state() {
    dro_state_t s;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    for (int a = 0; a < DRO_AXES; a++) {
        s.mm[a] = disp(a);
        s.raw_mm[a] = (float)s_counts[a] * (s_cfg.invert[a] ? -1.0f : 1.0f) / s_cfg.counts_per_mm[a];
        s.inc[a] = s_inc[a];
        s.tool_off[a] = s_tool_off[s_tool][a];
    }
    s.wcs = s_wcs_active;
    s.tool = s_tool;
    xSemaphoreGive(s_mutex);
    return s;
}

bool dro_preset(int axis, float value_mm) {
    if (axis < 0 || axis >= DRO_AXES || !isfinite(value_mm) || fabsf(value_mm) > 100000.0f) return false;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    set_display(axis, value_mm);
    xSemaphoreGive(s_mutex);
    return true;
}

bool dro_set_inc(int axis, bool inc) {
    if (axis < 0 || axis >= DRO_AXES) return false;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    if (inc && !s_inc[axis]) s_inc_offset[axis] = s_counts[axis];
    s_inc[axis] = inc;
    xSemaphoreGive(s_mutex);
    return true;
}

bool dro_select_wcs(int n) {
    if (n < 0 || n >= DRO_WCS) return false;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    s_wcs_active = n;
    xSemaphoreGive(s_mutex);
    return true;
}

bool dro_select_tool(int n) {
    if (n < 0 || n >= DRO_TOOLS) return false;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    s_tool = n;
    xSemaphoreGive(s_mutex);
    save_tools();
    return true;
}

bool dro_tool_touch_off(int axis, float value_mm) {
    if (axis < 0 || axis >= DRO_AXES || !isfinite(value_mm) || fabsf(value_mm) > 100000.0f) return false;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    bool ok = !s_inc[axis];
    if (ok) {
        float base = (float)(s_counts[axis] - s_wcs[s_wcs_active][axis]) * axis_scale(axis);
        s_tool_off[s_tool][axis] = value_mm - base;
    }
    xSemaphoreGive(s_mutex);
    if (ok) save_tools();
    return ok;
}

void dro_tool_clear() {
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    for (int a = 0; a < DRO_AXES; a++) s_tool_off[s_tool][a] = 0;
    xSemaphoreGive(s_mutex);
    save_tools();
}

dro_config_t dro_get_config() {
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    dro_config_t c = s_cfg;
    xSemaphoreGive(s_mutex);
    return c;
}

bool dro_set_config(const dro_config_t &c) {
    if (!config_valid(c)) return false;
    xSemaphoreTake(s_mutex, portMAX_DELAY);
    // Keep each axis showing the same value across a config change.
    float shown[DRO_AXES];
    for (int a = 0; a < DRO_AXES; a++) shown[a] = disp(a);
    if (c.x_diameter != s_cfg.x_diameter) {
        float ratio = c.x_diameter ? 2.0f : 0.5f; // tool offsets are stored in displayed units
        for (int t = 0; t < DRO_TOOLS; t++) s_tool_off[t][DRO_X] *= ratio;
    }
    s_cfg = c;
    for (int a = 0; a < DRO_AXES; a++) set_display(a, shown[a]);
    xSemaphoreGive(s_mutex);
    return true;
}

bool dro_save_config() {
    dro_config_t c = dro_get_config();
    if (!s_prefs.begin("dro", false)) return false;
    s_prefs.putFloat("z_cpm", c.counts_per_mm[DRO_Z]);
    s_prefs.putFloat("x_cpm", c.counts_per_mm[DRO_X]);
    s_prefs.putBool("z_inv", c.invert[DRO_Z]);
    s_prefs.putBool("x_inv", c.invert[DRO_X]);
    s_prefs.putBool("x_dia", c.x_diameter);
    s_prefs.end();
    save_tools(); // tool offsets are in displayed units, so they follow the diameter setting
    return true;
}
