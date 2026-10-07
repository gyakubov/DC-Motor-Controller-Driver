#pragma once

// Starts a lightweight line-based command console over Serial (USB-CDC/UART),
// calling the same control.h API used by the web layer (status, set/get PID
// gains, start/stop, direction, clear-fault). Type "help" for the command
// list once connected. A fuller esp_console REPL (history/tab-complete) can
// replace this later without changing the control/web layers.
void cli_init();
