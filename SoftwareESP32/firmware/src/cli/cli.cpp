#include "cli.h"
#include "../control/control.h"
#include <Arduino.h>

static void print_status() {
    control_status_t s = control_get_status();
    Serial.printf("target=%d actual=%d duty=%d%% running=%d stalled=%d fault=%d dir=%s mode=%s\n",
        s.rpm_target, s.rpm_actual, s.duty_percent, s.running, s.stalled,
        s.current_limited, s.direction_reverse ? "rev" : "fwd", s.direct_mode ? "direct" : "pid");
    Serial.printf("current=%.2fA temp=%.1fC kp=%.3f ki=%.3f kd=%.3f ff=%.3f\n",
        s.current_amps, s.temperature_c, s.kp, s.ki, s.kd, s.ff);
}

static void print_help() {
    Serial.println(
        "commands: status | start | stop | clear | dir fwd|rev | mode pid|direct |\n"
        "          set rpm <v> | set kp|ki|kd|ff <v> | help");
}

// Simple whitespace-tokenized command dispatcher - intentionally not a full
// esp_console REPL (see cli.h) to keep this first implementation's build
// dependencies minimal; swap in esp_console later for history/tab-complete.
static void handle_line(char *line) {
    char *tok[4] = {};
    int n = 0;
    for (char *p = strtok(line, " \t"); p && n < 4; p = strtok(NULL, " \t")) tok[n++] = p;
    if (n == 0) return;

    if (!strcmp(tok[0], "status")) {
        print_status();
    } else if (!strcmp(tok[0], "start")) {
        control_start();
        Serial.println("ok");
    } else if (!strcmp(tok[0], "stop")) {
        control_stop();
        Serial.println("ok");
    } else if (!strcmp(tok[0], "clear")) {
        control_clear_fault();
        Serial.println("ok");
    } else if (!strcmp(tok[0], "dir") && n >= 2) {
        control_set_direction(!strcmp(tok[1], "rev"));
        Serial.println("ok");
    } else if (!strcmp(tok[0], "mode")) {
        if (n >= 2) {
            if (strcmp(tok[1], "pid") && strcmp(tok[1], "direct")) {
                Serial.println("usage: mode pid|direct");
                return;
            }
            control_set_mode_direct(!strcmp(tok[1], "direct"));
            Serial.println("ok");
        } else {
            Serial.println(control_get_status().direct_mode ? "direct" : "pid");
        }
    } else if (!strcmp(tok[0], "set") && n >= 3) {
        float v = atof(tok[2]);
        control_status_t s = control_get_status();
        if (!strcmp(tok[1], "rpm")) control_set_rpm_target((int)v);
        else if (!strcmp(tok[1], "kp")) control_set_pid_gains(v, s.ki, s.kd, s.ff);
        else if (!strcmp(tok[1], "ki")) control_set_pid_gains(s.kp, v, s.kd, s.ff);
        else if (!strcmp(tok[1], "kd")) control_set_pid_gains(s.kp, s.ki, v, s.ff);
        else if (!strcmp(tok[1], "ff")) control_set_pid_gains(s.kp, s.ki, s.kd, v);
        else { Serial.println("unknown setting"); return; }
        Serial.println("ok");
    } else {
        print_help();
    }
}

static void cli_task(void *arg) {
    static char line[64];
    static size_t len = 0;
    print_help();

    for (;;) {
        while (Serial.available()) {
            char c = (char)Serial.read();
            if (c == '\r') continue;
            if (c == '\n') {
                line[len] = '\0';
                if (len > 0) handle_line(line);
                len = 0;
            } else if (len < sizeof(line) - 1) {
                line[len++] = c;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void cli_init() {
    xTaskCreatePinnedToCore(cli_task, "cli", 4096, NULL, 2, NULL, 0);
}
