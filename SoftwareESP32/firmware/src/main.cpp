/*
 * DC Motor PID Controller - ESP32-S3
 *
 * Architecture: a dedicated real-time control task (PCNT/MCPWM/PID, pinned to
 * core 1) separate from the web/WiFi stack (core 0) and a USB-Serial/JTAG CLI.
 * The web and CLI layers never touch hardware directly - they only call the
 * thread-safe command/status API exposed by control.h.
 */
#include <Arduino.h>
#include "control/control.h"
#include "web/web_server.h"
#include "cli/cli.h"

void setup() {
    Serial.begin(57600); // lowered from 115200 for more reliable comms on this board/wiring

    control_init(); // PCNT tach/encoder, MCPWM + trip-zone, PID task (core 1)
    web_init();     // WiFi, ESPAsyncWebServer, WebSocket telemetry/commands (core 0)
    cli_init();     // esp_console REPL over USB-Serial/JTAG
}

void loop() {
    // Control loop runs in its own task, web server is event-driven, CLI has
    // its own console task - nothing to do in the Arduino loop task.
    vTaskDelete(NULL);
}
