#pragma once

// WiFi AP SSID/password - change before deploying. Standalone AP by default
// so the tablet can connect directly without a home/shop network.
#define WIFI_AP_SSID "motor-controller"
#define WIFI_AP_PASS "motorpid123"

// Starts WiFi (AP mode), the ESPAsyncWebServer instance (serving the GUI from
// LittleFS under /data), and the WebSocket endpoint used for live telemetry +
// commands. Only calls into control.h's command/status API - never touches
// hardware directly.
void web_init();
