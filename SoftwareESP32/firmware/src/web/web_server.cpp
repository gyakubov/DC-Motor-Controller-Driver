#include "web_server.h"
#include "../control/control.h"
#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#define FW_VERSION "v0.2.0"

static AsyncWebServer server(80);
static AsyncWebSocket ws("/ws");
static Preferences s_wifi_prefs;
static String s_ssid = WIFI_AP_SSID;
static String s_pass = WIFI_AP_PASS;
static volatile bool s_restart_requested = false;

static void send_json(AsyncWebSocketClient *client, const JsonDocument &doc) {
    String out;
    serializeJson(doc, out);
    if (client) client->text(out);
    else ws.textAll(out);
}

static void send_notice(AsyncWebSocketClient *client, const char *level, const char *text) {
    JsonDocument doc;
    doc["type"] = "notice";
    doc["level"] = level;
    doc["text"] = text;
    send_json(client, doc);
}

// The WiFi password is deliberately never included here.
static void send_settings(AsyncWebSocketClient *client) {
    control_settings_t s = control_get_settings();
    JsonDocument doc;
    doc["type"] = "settings";
    doc["max_rpm"] = s.max_rpm;
    doc["min_rpm"] = s.min_rpm;
    doc["max_duty"] = s.max_duty;
    doc["enc_res"] = s.enc_res;
    doc["ssid"] = s_ssid;
    doc["fw"] = FW_VERSION;
    doc["chip"] = ESP.getChipModel();
    send_json(client, doc);
}

static void load_wifi_config() {
    s_wifi_prefs.begin("wifi", true);
    String ssid = s_wifi_prefs.getString("ssid", "");
    String pass = s_wifi_prefs.getString("pass", "");
    s_wifi_prefs.end();
    if (ssid.length() >= 1 && ssid.length() <= 32 && pass.length() >= 8 && pass.length() <= 63) {
        s_ssid = ssid;
        s_pass = pass;
    }
}

// Incoming WebSocket command handling. Every setter goes through control.h's
// own clamping/validation, so a malformed or out-of-range value from the
// client can never bypass the limits enforced on the control task.
static void handle_command(AsyncWebSocketClient *client, const JsonDocument &doc) {
    const char *cmd = doc["cmd"] | "";

    if (!strcmp(cmd, "set_rpm")) {
        control_set_rpm_target(doc["value"] | 0);
    } else if (!strcmp(cmd, "set_gains") || !strcmp(cmd, "save_gains")) {
        control_set_pid_gains(doc["kp"] | 0.0f, doc["ki"] | 0.0f,
                               doc["kd"] | 0.0f, doc["ff"] | 0.0f);
        if (!strcmp(cmd, "save_gains")) {
            if (control_save_config()) send_notice(client, "info", "Gains saved to flash");
            else send_notice(client, "err", "Saving to flash failed");
        }
    } else if (!strcmp(cmd, "start")) {
        control_start();
    } else if (!strcmp(cmd, "stop")) {
        control_stop();
    } else if (!strcmp(cmd, "set_dir")) {
        control_set_direction(doc["reverse"] | false);
    } else if (!strcmp(cmd, "set_mode")) {
        control_set_mode_direct(doc["direct"] | false);
    } else if (!strcmp(cmd, "clear_fault")) {
        control_clear_fault();
    } else if (!strcmp(cmd, "set_settings")) {
        control_settings_t s = { doc["max_rpm"] | 0, doc["min_rpm"] | 0,
                                 doc["max_duty"] | 0, doc["enc_res"] | 0 };
        if (!control_set_settings(s)) {
            send_notice(client, "err", "Settings rejected: stop the motor and check the value ranges");
        } else if (!control_save_config()) {
            send_notice(client, "err", "Settings applied but saving to flash failed");
        } else {
            send_notice(client, "info", "Settings saved to flash");
        }
        send_settings(nullptr);
    } else if (!strcmp(cmd, "set_wifi")) {
        String ssid = doc["ssid"] | "";
        String pass = doc["pass"] | "";
        if (ssid.length() < 1 || ssid.length() > 32 || pass.length() < 8 || pass.length() > 63) {
            send_notice(client, "err", "WiFi rejected: SSID 1-32 chars, password 8-63 chars");
        } else {
            s_wifi_prefs.begin("wifi", false);
            s_wifi_prefs.putString("ssid", ssid);
            s_wifi_prefs.putString("pass", pass);
            s_wifi_prefs.end();
            send_notice(client, "warn", "WiFi credentials saved - restart the controller to apply");
        }
    } else if (!strcmp(cmd, "restart")) {
        control_stop();
        send_notice(nullptr, "warn", "Restarting controller...");
        s_restart_requested = true;
    }
}

static void on_ws_event(AsyncWebSocket *server, AsyncWebSocketClient *client,
                        AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        send_settings(client);
        return;
    }
    if (type != WS_EVT_DATA) return;

    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (!info->final || info->index != 0 || info->len != len || info->opcode != WS_TEXT) return;

    JsonDocument doc;
    if (deserializeJson(doc, data, len) == DeserializationError::Ok) {
        handle_command(client, doc);
    }
}

// Telemetry broadcast task - the only thing driving this is control_get_status(),
// which is a quick mutex-protected read; this task never touches hardware.
static void telemetry_task(void *arg) {
    char buf[512];
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(150));

        if (s_restart_requested) {
            vTaskDelay(pdMS_TO_TICKS(400)); // let the notice reach the client
            ESP.restart();
        }

        if (ws.count() == 0) continue;

        control_status_t s = control_get_status();
        snprintf(buf, sizeof(buf),
            "{\"type\":\"status\",\"rpm_target\":%d,\"rpm_actual\":%d,\"duty\":%d,"
            "\"running\":%s,\"stalled\":%s,\"current_limited\":%s,\"dir\":%s,\"direct_mode\":%s,"
            "\"current\":%.2f,\"temp\":%.1f,\"kp\":%.3f,\"ki\":%.3f,\"kd\":%.3f,\"ff\":%.3f,"
            "\"pulses\":%d,\"load\":%d,\"heap\":%u,\"uptime\":%lu}",
            s.rpm_target, s.rpm_actual, s.duty_percent,
            s.running ? "true" : "false", s.stalled ? "true" : "false",
            s.current_limited ? "true" : "false", s.direction_reverse ? "true" : "false",
            s.direct_mode ? "true" : "false",
            s.current_amps, s.temperature_c, s.kp, s.ki, s.kd, s.ff,
            s.pulses_per_s, s.task_load_percent, (unsigned)ESP.getFreeHeap(),
            (unsigned long)(millis() / 1000));
        ws.textAll(buf);
        ws.cleanupClients();
    }
}

void web_init() {
    LittleFS.begin(true); // format on first boot if no filesystem image was uploaded yet
    load_wifi_config();

    WiFi.mode(WIFI_AP);
    WiFi.softAP(s_ssid.c_str(), s_pass.c_str());

    ws.onEvent(on_ws_event);
    server.addHandler(&ws);
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
    server.begin();

    xTaskCreatePinnedToCore(telemetry_task, "telemetry", 4096, NULL, 3, NULL, 0);
}
