#pragma once
#include <stdbool.h>
#include <stdint.h>

// Two-axis digital readout (Z = carriage, X = cross slide) fed by TTL
// quadrature linear scales. Each axis is decoded in x4 mode by one PCNT unit
// (units 1 and 2; unit 0 is the spindle tach). Pins are in control.h.
enum { DRO_Z = 0, DRO_X = 1, DRO_AXES = 2 };
enum { DRO_WCS = 6, DRO_TOOLS = 8 };

typedef struct {
    float counts_per_mm[DRO_AXES]; // x4 counts per mm (5um scale = 800, 1um scale = 4000)
    bool invert[DRO_AXES];
    bool x_diameter;               // X reads diameter (2x the cross-slide travel)
} dro_config_t;

typedef struct {
    float mm[DRO_AXES];       // displayed position (mm; X is diameter when x_diameter is set)
    float raw_mm[DRO_AXES];   // scale travel since boot, no offsets (for feed-rate maths)
    bool inc[DRO_AXES];       // axis is in incremental mode
    int wcs;                  // active work zero slot, 0..DRO_WCS-1
    int tool;                 // active tool, 0..DRO_TOOLS-1
    float tool_off[DRO_AXES]; // active tool's offsets (displayed units)
} dro_state_t;

void dro_init();
dro_state_t dro_get_state();

// Makes the displayed value of an axis equal value_mm. ABS mode moves the
// active work zero; INC mode moves the incremental zero. Offsets live in RAM
// only: linear scales are incremental, so a power cycle loses the origin.
bool dro_preset(int axis, float value_mm);

// Switching an axis to INC makes it read 0 from the current position.
bool dro_set_inc(int axis, bool inc);
bool dro_select_wcs(int n);
bool dro_select_tool(int n);

// Touch-off: makes the display read value_mm with the work zero unchanged by
// adjusting the active tool's offset. ABS mode only. Tool offsets persist in NVS.
bool dro_tool_touch_off(int axis, float value_mm);
void dro_tool_clear();

dro_config_t dro_get_config();
bool dro_set_config(const dro_config_t &c);
bool dro_save_config();
