/*
 * Live GUI for the ESP32 DC motor controller. The firmware is the source of
 * truth: the UI sends commands over the /ws WebSocket and renders whatever
 * "status" / "settings" / "notice" messages come back (see web_server.cpp).
 */
(() => {
  const state = {
    connected: false,
    rpmTarget: 0,
    rpmActual: 0,
    dutyPercent: 0,
    running: false,
    reverse: false,
    stalled: false,
    currentLimited: false,
    directMode: false,
    maxRpm: 3000,
    ssid: '',
    uptime: 0,
    history: [], // {target, actual}
    current: 0,
    temperature: 25,
    history2: [], // {current, temp}
    prev: null, // previous status, for event-log transitions
  };

  let ws = null;
  let lastLocalTarget = 0; // ms timestamp of the last local setpoint edit
  let gainsDirty = false;  // user is editing gains - don't overwrite from telemetry
  let settingsDirty = false;
  let targetTimer = null;

  const $ = (sel) => document.querySelector(sel);
  const el = {
    wsDot: $('#wsDot'), wsText: $('#wsText'), uptime: $('#uptime'),
    faultBanner: $('#faultBanner'), clearFaultBtn: $('#clearFaultBtn'),
    rpmActual: $('#rpmActual'), rpmTargetReadout: $('#rpmTargetReadout'),
    dutyReadout: $('#dutyReadout'), gauge: $('#gauge'),
    dirToggle: $('#dirToggle'), dirLockHint: $('#dirLockHint'),
    rpmSlider: $('#rpmSlider'),
    modeBadge: $('#modeBadge'), modeToggle: $('#modeToggle'),
    startBtn: $('#startBtn'), stopBtn: $('#stopBtn'),
    chart: $('#chart'), chart2: $('#chart2'), chart3: $('#chart3'),
    eventLog: $('#eventLog'),
    diagPulses: $('#diagPulses'), diagCurrent: $('#diagCurrent'), diagTemp: $('#diagTemp'),
    diagLoad: $('#diagLoad'), diagHeap: $('#diagHeap'),
    gains: { kp: $('#kpVal'), ki: $('#kiVal'), kd: $('#kdVal'), ff: $('#ffVal') },
    set: {
      maxRpm: $('#setMaxRpm'), minRpm: $('#setMinRpm'), maxDuty: $('#setMaxDuty'),
      encRes: $('#setEncRes'), ssid: $('#setSsid'), pass: $('#setPass'),
    },
    fwInfo: $('#fwInfo'),
  };

  const clamp = (v, lo, hi) => Math.max(lo, Math.min(hi, v));
  const fmtNum = (v) => String(+v.toFixed(3));

  // ---------------- tabs ----------------
  document.querySelectorAll('.tab-btn').forEach((btn) => {
    btn.addEventListener('click', () => {
      document.querySelectorAll('.tab-btn').forEach((b) => b.classList.remove('active'));
      document.querySelectorAll('.tab-panel').forEach((p) => p.classList.add('hidden'));
      btn.classList.add('active');
      document.querySelector(`.tab-panel[data-panel="${btn.dataset.tab}"]`).classList.remove('hidden');
    });
  });

  // ---------------- WebSocket ----------------
  function send(obj) {
    if (!ws || ws.readyState !== WebSocket.OPEN) {
      logEvent('Not connected - command not sent', 'warn');
      return false;
    }
    ws.send(JSON.stringify(obj));
    return true;
  }

  function setConnected(connected) {
    state.connected = connected;
    el.wsDot.className = connected ? 'dot online' : 'dot offline';
    el.wsText.textContent = connected ? 'Connected' : 'Disconnected - reconnecting...';
    if (!connected) state.prev = null;
    render();
  }

  function connect() {
    const proto = location.protocol === 'https:' ? 'wss' : 'ws';
    ws = new WebSocket(`${proto}://${location.host}/ws`);
    ws.onopen = () => { setConnected(true); logEvent('Connected to controller', 'info'); };
    ws.onclose = () => {
      if (state.connected) logEvent('Connection lost', 'err');
      setConnected(false);
      setTimeout(connect, 1000);
    };
    ws.onerror = () => ws.close();
    ws.onmessage = (ev) => {
      let m;
      try { m = JSON.parse(ev.data); } catch { return; }
      if (m.type === 'status') onStatus(m);
      else if (m.type === 'settings') onSettings(m);
      else if (m.type === 'notice') logEvent(m.text, m.level);
    };
  }

  // ---------------- incoming telemetry ----------------
  function onStatus(m) {
    const prev = state.prev;
    state.rpmActual = m.rpm_actual;
    state.dutyPercent = m.duty;
    state.running = m.running;
    state.reverse = m.dir;
    state.stalled = m.stalled;
    state.currentLimited = m.current_limited;
    state.directMode = m.direct_mode;
    state.current = m.current;
    state.temperature = m.temp;
    state.uptime = m.uptime;

    // Let a just-made local edit win briefly so the slider doesn't jump back.
    if (Date.now() - lastLocalTarget > 600) state.rpmTarget = m.rpm_target;

    if (prev) {
      if (prev.running !== m.running) logEvent(m.running ? 'Motor started' : 'Motor stopped', 'info');
      if (prev.stalled !== m.stalled) logEvent(m.stalled ? 'Stall detected' : 'Stall cleared', m.stalled ? 'err' : 'info');
      if (prev.current_limited !== m.current_limited) {
        logEvent(m.current_limited ? 'Fault: current limit / overspeed / overtemp' : 'Fault cleared', m.current_limited ? 'err' : 'info');
      }
      if (prev.direct_mode !== m.direct_mode) {
        logEvent(`Control mode: ${m.direct_mode ? 'DIRECT (PID bypassed)' : 'PID'}`, m.direct_mode ? 'warn' : 'info');
      }
    }
    state.prev = m;

    if (!gainsDirty) {
      for (const g of ['kp', 'ki', 'kd', 'ff']) {
        if (document.activeElement !== el.gains[g]) el.gains[g].value = fmtNum(m[g]);
      }
    }

    el.diagPulses.textContent = m.pulses;
    el.diagLoad.textContent = `${m.load} %`;
    el.diagHeap.textContent = `${Math.round(m.heap / 1024)} kB`;

    state.history.push({ target: state.rpmTarget, actual: state.rpmActual });
    if (state.history.length > 120) state.history.shift();
    state.history2.push({ current: state.current, temp: state.temperature });
    if (state.history2.length > 120) state.history2.shift();

    render();
    drawChart(el.chart);
    drawChart(el.chart2);
    drawDualChart(el.chart3);
  }

  function onSettings(m) {
    state.maxRpm = m.max_rpm;
    state.ssid = m.ssid;
    el.rpmSlider.max = m.max_rpm;
    if (!settingsDirty) {
      el.set.maxRpm.value = m.max_rpm;
      el.set.minRpm.value = m.min_rpm;
      el.set.maxDuty.value = m.max_duty;
      el.set.encRes.value = m.enc_res;
      el.set.ssid.value = m.ssid;
    }
    el.fwInfo.textContent = `Firmware ${m.fw} \u00b7 ${m.chip}`;
  }

  // ---------------- rendering ----------------
  function render() {
    el.rpmActual.textContent = Math.round(state.rpmActual);
    el.rpmTargetReadout.textContent = state.rpmTarget;
    el.dutyReadout.textContent = Math.round(state.dutyPercent);
    const pct = state.maxRpm ? Math.min(100, (state.rpmActual / state.maxRpm) * 100) : 0;
    el.gauge.style.setProperty('--pct', pct.toFixed(1));
    if (Date.now() - lastLocalTarget > 600) el.rpmSlider.value = state.rpmTarget;

    const hh = String(Math.floor(state.uptime / 3600)).padStart(2, '0');
    const mm = String(Math.floor((state.uptime % 3600) / 60)).padStart(2, '0');
    const ss = String(state.uptime % 60).padStart(2, '0');
    el.uptime.textContent = `Uptime ${hh}:${mm}:${ss}`;

    el.startBtn.disabled = !state.connected || state.running;
    el.stopBtn.disabled = !state.connected;

    el.dirToggle.checked = state.reverse;
    el.dirToggle.disabled = !state.connected || state.running;
    el.dirLockHint.classList.toggle('hidden', !state.running);

    el.modeBadge.textContent = state.directMode ? 'DIRECT CONTROL' : 'PID CONTROL';
    el.modeBadge.classList.toggle('pid', !state.directMode);
    el.modeBadge.classList.toggle('direct', state.directMode);
    el.modeToggle.querySelectorAll('.seg-btn').forEach((b) => {
      b.classList.toggle('active', (b.dataset.mode === 'direct') === state.directMode);
    });

    const fault = state.stalled || state.currentLimited;
    el.faultBanner.classList.toggle('hidden', !fault);
    el.faultBanner.classList.toggle('stall', state.stalled);
    el.faultBanner.classList.toggle('current-limit', !state.stalled && state.currentLimited);
    el.faultBanner.textContent = state.stalled
      ? 'STALL DETECTED'
      : (state.currentLimited ? 'CURRENT LIMIT ACTIVE' : '');
    el.clearFaultBtn.classList.toggle('hidden', !fault);

    el.diagCurrent.textContent = `${state.current.toFixed(1)} A`;
    el.diagTemp.textContent = `${state.temperature.toFixed(1)} \u00b0C`;
  }

  // ---------------- start/stop/faults ----------------
  el.startBtn.addEventListener('click', () => {
    if (state.stalled || state.currentLimited) {
      logEvent('Clear the fault before starting', 'warn');
      return;
    }
    send({ cmd: 'start' });
  });
  el.stopBtn.addEventListener('click', () => send({ cmd: 'stop' }));
  el.clearFaultBtn.addEventListener('click', () => send({ cmd: 'clear_fault' }));

  // ---------------- direction / mode ----------------
  el.dirToggle.addEventListener('change', (e) => send({ cmd: 'set_dir', reverse: e.target.checked }));
  el.modeToggle.querySelectorAll('.seg-btn').forEach((btn) => {
    btn.addEventListener('click', () => send({ cmd: 'set_mode', direct: btn.dataset.mode === 'direct' }));
  });

  // ---------------- setpoint ----------------
  function setTarget(v, immediate) {
    state.rpmTarget = clamp(Math.round(v) || 0, 0, state.maxRpm);
    lastLocalTarget = Date.now();
    el.rpmSlider.value = state.rpmTarget;
    el.rpmTargetReadout.textContent = state.rpmTarget;
    if (immediate) {
      clearTimeout(targetTimer);
      targetTimer = null;
      send({ cmd: 'set_rpm', value: state.rpmTarget });
    } else if (!targetTimer) {
      // Throttle slider drags to ~12 messages/s.
      targetTimer = setTimeout(() => {
        targetTimer = null;
        send({ cmd: 'set_rpm', value: state.rpmTarget });
      }, 80);
    }
  }
  el.rpmSlider.addEventListener('input', (e) => setTarget(parseInt(e.target.value, 10), false));
  el.rpmSlider.addEventListener('change', (e) => setTarget(parseInt(e.target.value, 10), true));
  document.querySelectorAll('.step-btn').forEach((btn) => {
    btn.addEventListener('click', () => setTarget(state.rpmTarget + parseInt(btn.dataset.step, 10), true));
  });

  // ---------------- PID gains (tuning tab) ----------------
  function readGains() {
    const out = { };
    for (const g of ['kp', 'ki', 'kd', 'ff']) {
      const v = parseFloat(el.gains[g].value);
      out[g] = Number.isFinite(v) ? Math.max(0, v) : 0;
    }
    return out;
  }
  Object.values(el.gains).forEach((input) => input.addEventListener('input', () => { gainsDirty = true; }));
  document.querySelectorAll('.stepper button').forEach((btn) => {
    btn.addEventListener('click', () => {
      const g = btn.dataset.gain;
      const cur = parseFloat(el.gains[g].value) || 0;
      el.gains[g].value = Math.max(0, +(cur + parseFloat(btn.dataset.delta)).toFixed(3));
      gainsDirty = true;
    });
  });
  $('#applyGains').addEventListener('click', () => {
    if (send({ cmd: 'set_gains', ...readGains() })) {
      gainsDirty = false;
      logEvent('Gains applied (live test, not saved)', 'info');
    }
  });
  $('#saveGains').addEventListener('click', () => {
    if (send({ cmd: 'save_gains', ...readGains() })) gainsDirty = false;
  });

  // ---------------- settings ----------------
  Object.values(el.set).forEach((input) => input.addEventListener('input', () => { settingsDirty = true; }));

  $('#saveSettings').addEventListener('click', () => {
    const ssid = el.set.ssid.value.trim();
    const pass = el.set.pass.value;
    const wifiChanged = pass !== '' || (ssid !== '' && ssid !== state.ssid);
    if (wifiChanged && (ssid === '' || pass.length < 8)) {
      logEvent('WiFi change needs an SSID and a password of at least 8 characters', 'err');
      return;
    }
    const sent = send({
      cmd: 'set_settings',
      max_rpm: parseInt(el.set.maxRpm.value, 10) || 0,
      min_rpm: parseInt(el.set.minRpm.value, 10) || 0,
      max_duty: parseInt(el.set.maxDuty.value, 10) || 0,
      enc_res: parseInt(el.set.encRes.value, 10) || 0,
    });
    if (!sent) return;
    if (wifiChanged) send({ cmd: 'set_wifi', ssid, pass });
    el.set.pass.value = '';
    settingsDirty = false; // next "settings" message repopulates the fields with what the firmware accepted
  });

  $('#restartBtn').addEventListener('click', () => {
    if (confirm('Restart the controller now? The motor will be stopped.')) send({ cmd: 'restart' });
  });

  function logEvent(text, level) {
    const li = document.createElement('li');
    li.textContent = `[${new Date().toLocaleTimeString()}] ${text}`;
    if (level === 'err') li.className = 'err';
    if (level === 'warn') li.className = 'warn';
    el.eventLog.prepend(li);
    while (el.eventLog.children.length > 50) el.eventLog.removeChild(el.eventLog.lastChild);
  }

  // ---------------- charts ----------------
  function drawChart(canvas) {
    if (!canvas || !canvas.getContext) return;
    const ctx = canvas.getContext('2d');
    const w = canvas.width, h = canvas.height;
    ctx.clearRect(0, 0, w, h);

    ctx.strokeStyle = 'rgba(255,255,255,0.06)';
    ctx.lineWidth = 1;
    for (let i = 1; i < 4; i++) {
      const y = (h / 4) * i;
      ctx.beginPath(); ctx.moveTo(0, y); ctx.lineTo(w, y); ctx.stroke();
    }

    if (state.history.length < 2) return;
    const maxV = Math.max(state.maxRpm, ...state.history.map((p) => Math.max(p.target, p.actual)), 1);
    const stepX = w / (state.history.length - 1);

    const plot = (key, color) => {
      ctx.strokeStyle = color;
      ctx.lineWidth = 2;
      ctx.beginPath();
      state.history.forEach((p, i) => {
        const x = i * stepX;
        const y = h - (p[key] / maxV) * h;
        i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
      });
      ctx.stroke();
    };
    plot('target', 'rgba(59,130,246,0.9)');
    plot('actual', 'rgba(53,208,127,0.95)');
  }

  // Current and temperature use independent scales (Amps vs degC), so each
  // series is normalized against its own fixed max.
  function drawDualChart(canvas) {
    if (!canvas || !canvas.getContext) return;
    const ctx = canvas.getContext('2d');
    const w = canvas.width, h = canvas.height;
    ctx.clearRect(0, 0, w, h);

    ctx.strokeStyle = 'rgba(255,255,255,0.06)';
    ctx.lineWidth = 1;
    for (let i = 1; i < 4; i++) {
      const y = (h / 4) * i;
      ctx.beginPath(); ctx.moveTo(0, y); ctx.lineTo(w, y); ctx.stroke();
    }

    if (state.history2.length < 2) return;
    const stepX = w / (state.history2.length - 1);
    const maxCurrent = 30;
    const maxTemp = 110;

    const plot = (key, max, color) => {
      ctx.strokeStyle = color;
      ctx.lineWidth = 2;
      ctx.beginPath();
      state.history2.forEach((p, i) => {
        const x = i * stepX;
        const y = h - (clamp(p[key], 0, max) / max) * h;
        i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
      });
      ctx.stroke();
    };
    plot('current', maxCurrent, 'rgba(59,130,246,0.9)');
    plot('temp', maxTemp, 'rgba(239,68,68,0.9)');
  }

  // ---------------- keep screen awake on real devices ----------------
  if ('wakeLock' in navigator) {
    navigator.wakeLock.request('screen').catch(() => { /* not critical */ });
  }

  setConnected(false);
  el.wsText.textContent = 'Connecting...';
  connect();
})();
