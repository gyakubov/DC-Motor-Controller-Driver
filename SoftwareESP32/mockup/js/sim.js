/*
 * Mockup-only: replaces WebSocket with an in-page simulator that speaks the
 * same JSON protocol as firmware/src/web/web_server.cpp, so the unmodified
 * firmware GUI (app.js) runs standalone from file://.
 */
(() => {
  const MAX_TICK_MS = 100;
  const s = {
    running: false, reverse: false, direct: false, stalled: false, limited: false,
    target: 0, rpm: 0, duty: 0, current: 0, temp: 25,
    kp: 2.0, ki: 0.5, kd: 0.1, ff: 0.0,
    max_rpm: 3000, min_rpm: 0, max_duty: 95, enc_res: 1000,
    ssid: 'DC-Motor-Controller', indexCount: 0,
    z: 0, x: 0, zinc: false, xinc: false, wcs: 0, tool: 0,
    toolOff: [{ z: 0, x: 0 }, { z: 0, x: 0 }, { z: 0, x: 0 }, { z: 0, x: 0 }],
    zOrigin: 0, xOrigin: 0, zRaw: 0, xRaw: 0,
    z_cpm: 1000, x_cpm: 1000, z_inv: false, x_inv: false, x_dia: true,
    t0: Date.now(),
  };

  class FakeWebSocket {
    static CONNECTING = 0; static OPEN = 1; static CLOSING = 2; static CLOSED = 3;
    constructor() {
      this.readyState = 0;
      setTimeout(() => {
        this.readyState = 1;
        this.onopen?.();
        this.#push(settings());
        this.#push(droCfg());
        this.timer = setInterval(() => { tick(); this.#push(status()); this.#push(dro()); }, MAX_TICK_MS);
      }, 400);
    }
    #push(obj) { if (this.readyState === 1) this.onmessage?.({ data: JSON.stringify(obj) }); }
    send(data) {
      const m = JSON.parse(data);
      const reply = handle(m);
      reply.forEach((r) => this.#push(r));
    }
    close() {
      clearInterval(this.timer);
      this.readyState = 3;
      this.onclose?.();
    }
  }
  window.WebSocket = FakeWebSocket;

  const notice = (level, text) => ({ type: 'notice', level, text });
  const settings = () => ({
    type: 'settings', max_rpm: s.max_rpm, min_rpm: s.min_rpm, max_duty: s.max_duty,
    enc_res: s.enc_res, ssid: s.ssid, fw: 'mockup', chip: 'ESP32 (simulated)',
  });
  const droCfg = () => ({
    type: 'dro_cfg', z_cpm: s.z_cpm, x_cpm: s.x_cpm, z_inv: s.z_inv, x_inv: s.x_inv, x_dia: s.x_dia,
  });
  const status = () => ({
    type: 'status', rpm_target: s.target, rpm_actual: Math.round(s.rpm), duty: Math.round(s.duty),
    running: s.running, dir: s.reverse, stalled: s.stalled, current_limited: s.limited,
    direct_mode: s.direct, current: s.current, temp: s.temp,
    uptime: Math.floor((Date.now() - s.t0) / 1000),
    pulses: Math.round(s.rpm / 60 * s.enc_res * 4), load: 12, heap: 210000,
    sdir: s.rpm > 20 ? (s.reverse ? -1 : 1) : 0, idx: s.indexCount, cpi: s.enc_res * 4, cpr: s.enc_res * 4,
    kp: s.kp, ki: s.ki, kd: s.kd, ff: s.ff,
  });
  const dro = () => ({
    type: 'dro', z: s.z, x: s.x, zinc: s.zinc, xinc: s.xinc, wcs: s.wcs, tool: s.tool,
    tz: s.toolOff[s.tool].z, tx: s.toolOff[s.tool].x,
    fz: s.rpm > 20 ? Math.abs(s.zVel || 0) * 60 / s.rpm : -1,
    fx: s.rpm > 20 ? Math.abs(s.xVel || 0) * 60 / s.rpm : -1,
  });

  const axisKey = (a) => (a === 'x' ? 'x' : 'z');

  function handle(m) {
    switch (m.cmd) {
      case 'start':
        if (s.stalled || s.limited) return [notice('warn', 'Clear the fault before starting')];
        s.running = true; return [];
      case 'stop': s.running = false; s.target = s.target; return [];
      case 'clear_fault': s.stalled = false; s.limited = false; return [];
      case 'set_rpm': s.target = Math.max(0, Math.min(s.max_rpm, m.value | 0)); return [];
      case 'set_dir': if (!s.running) s.reverse = !!m.reverse; return [];
      case 'set_mode': s.direct = !!m.direct; return [];
      case 'set_gains':
        Object.assign(s, { kp: m.kp, ki: m.ki, kd: m.kd, ff: m.ff }); return [];
      case 'save_gains':
        Object.assign(s, { kp: m.kp, ki: m.ki, kd: m.kd, ff: m.ff });
        return [notice('info', 'Gains saved to flash (simulated)')];
      case 'set_settings':
        Object.assign(s, { max_rpm: m.max_rpm || s.max_rpm, min_rpm: m.min_rpm, max_duty: m.max_duty || s.max_duty, enc_res: m.enc_res || s.enc_res });
        return [settings(), notice('info', 'Settings saved (simulated)')];
      case 'set_wifi': s.ssid = m.ssid; return [settings(), notice('info', 'WiFi saved (simulated)')];
      case 'restart': return [notice('warn', 'Restart ignored in mockup')];
      case 'dro_set': {
        const a = axisKey(m.axis);
        s[a] = m.value;
        s[a + 'Origin'] = s[a + 'Raw'] - m.value;
        return [];
      }
      case 'dro_inc': s[axisKey(m.axis) + 'inc'] = !!m.inc; return [];
      case 'dro_wcs': s.wcs = m.n; return [];
      case 'dro_tool': s.tool = m.n; return [];
      case 'dro_tool_set': {
        const a = axisKey(m.axis);
        s.toolOff[s.tool][a] = m.value - s[a];
        return [];
      }
      case 'dro_tool_clr': s.toolOff[s.tool] = { z: 0, x: 0 }; return [];
      case 'set_dro_cfg':
        Object.assign(s, { z_cpm: m.z_cpm, x_cpm: m.x_cpm, z_inv: m.z_inv, x_inv: m.x_inv, x_dia: m.x_dia });
        return [droCfg()];
      default: return [];
    }
  }

  // Demo faults: Shift+S = stall, Shift+C = current limit.
  document.addEventListener('keydown', (e) => {
    if (!e.shiftKey) return;
    if (e.key === 'S') { s.stalled = true; s.running = false; }
    if (e.key === 'C') { s.limited = true; s.running = false; }
  });

  function tick() {
    const dt = MAX_TICK_MS / 1000;
    const driving = s.running && !s.stalled && !s.limited;
    const goal = driving ? s.target : 0;
    s.rpm += (goal - s.rpm) * 0.12 + (driving ? (Math.random() - 0.5) * 6 : 0);
    s.rpm = Math.max(0, s.rpm);
    s.duty = driving ? Math.min(s.max_duty, 20 + (s.rpm / (s.max_rpm || 1)) * 70) : s.duty * 0.8;
    s.current += ((driving ? (s.duty / 100) * 18 : 0) - s.current) * 0.3;
    s.temp += (25 + (driving ? (s.duty / 100) * 55 : 0) - s.temp) * 0.02;
    s.indexCount += s.rpm / 60 * dt;

    // Spindle-linked carriage motion so the DRO and feed readouts move.
    s.zVel = driving ? Math.sin(Date.now() / 4000) * 0.4 : 0;
    s.xVel = driving ? Math.cos(Date.now() / 5000) * 0.15 : 0;
    s.zRaw += s.zVel * dt;
    s.xRaw += s.xVel * dt * (s.x_dia ? 2 : 1);
    s.z = s.zRaw - s.zOrigin;
    s.x = s.xRaw - s.xOrigin;
  }
})();
