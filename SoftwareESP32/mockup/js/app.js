/*
 * Static mockup - no real backend yet. Simulates telemetry locally so the
 * layout/interactions can be evaluated on an actual tablet before the
 * WebSocket API exists. Replace `simulate()` with a real `WebSocket` handler
 * (same message shape) when wiring up to the ESP32-S3 firmware.
 */
(() => {
  const state = {
    connected: false, // mockup starts "disconnected" to demo that visual state
    rpmTarget: 0,
    rpmActual: 0,
    dutyPercent: 0,
    running: false,
    direction: false, // false = fwd, true = rev
    stalled: false,
    currentLimited: false,
    directMode: false, // false = closed-loop PID, true = bypass PID (open-loop)
    maxRpm: 3000,
    gains: { kp: 2.0, ki: 0.5, kd: 0.1, ff: 0.0 },
    startedAt: Date.now(),
    history: [], // {t, target, actual}
    current: 0, // Amps, simulated Hall sensor reading
    temperature: 25, // °C, simulated MOSFET temp sensor reading
    history2: [], // {current, temp}
  };

  const $ = (sel) => document.querySelector(sel);
  const el = {
    wsDot: $('#wsDot'), wsText: $('#wsText'), uptime: $('#uptime'),
    faultBanner: $('#faultBanner'),
    rpmActual: $('#rpmActual'), rpmTargetReadout: $('#rpmTargetReadout'),
    dutyReadout: $('#dutyReadout'), gauge: $('#gauge'),
    dirToggle: $('#dirToggle'), dirLockHint: $('#dirLockHint'),
    rpmSlider: $('#rpmSlider'),
    modeBadge: $('#modeBadge'), modeToggle: $('#modeToggle'),
    startBtn: $('#startBtn'), stopBtn: $('#stopBtn'),
    chart: $('#chart'), chart2: $('#chart2'), chart3: $('#chart3'),
    eventLog: $('#eventLog'),
    diagCurrent: $('#diagCurrent'), diagTemp: $('#diagTemp'),
  };

  // ---------------- tabs ----------------
  document.querySelectorAll('.tab-btn').forEach((btn) => {
    btn.addEventListener('click', () => {
      document.querySelectorAll('.tab-btn').forEach((b) => b.classList.remove('active'));
      document.querySelectorAll('.tab-panel').forEach((p) => p.classList.add('hidden'));
      btn.classList.add('active');
      document.querySelector(`.tab-panel[data-panel="${btn.dataset.tab}"]`).classList.remove('hidden');
    });
  });

  // ---------------- connection (fake) ----------------
  setTimeout(() => {
    state.connected = true;
    el.wsDot.className = 'dot online';
    el.wsText.textContent = 'Connected (simulated)';
  }, 900);

  // ---------------- start/stop ----------------
  el.startBtn.addEventListener('click', () => {
    if (state.stalled) return; // require explicit fault clear first
    state.running = true;
    el.startBtn.disabled = true;
    logEvent('Motor started', 'info');
  });
  el.stopBtn.addEventListener('click', () => {
    state.running = false;
    el.startBtn.disabled = false;
    state.dutyPercent = 0;
    logEvent('Motor stopped', 'info');
  });

  // ---------------- direction (locked while running) ----------------
  function refreshDirectionLock() {
    el.dirToggle.disabled = state.running;
    el.dirLockHint.classList.toggle('hidden', !state.running);
  }
  el.dirToggle.addEventListener('change', (e) => {
    state.direction = e.target.checked;
  });

  // ---------------- control mode (PID vs direct/open-loop) ----------------
  function setMode(direct) {
    state.directMode = direct;
    el.modeBadge.textContent = direct ? 'DIRECT CONTROL' : 'PID CONTROL';
    el.modeBadge.classList.toggle('pid', !direct);
    el.modeBadge.classList.toggle('direct', direct);
    el.modeToggle.querySelectorAll('.seg-btn').forEach((b) => {
      b.classList.toggle('active', (b.dataset.mode === 'direct') === direct);
    });
    logEvent(`Control mode set to ${direct ? 'DIRECT (PID bypassed)' : 'PID'}`, direct ? 'warn' : 'info');
  }
  el.modeToggle.querySelectorAll('.seg-btn').forEach((btn) => {
    btn.addEventListener('click', () => setMode(btn.dataset.mode === 'direct'));
  });

  // ---------------- setpoint controls ----------------
  function setTarget(v) {
    state.rpmTarget = Math.max(0, Math.min(state.maxRpm, v));
    el.rpmSlider.value = state.rpmTarget;
    el.rpmTargetReadout.textContent = state.rpmTarget;
  }
  el.rpmSlider.addEventListener('input', (e) => setTarget(parseInt(e.target.value, 10)));
  document.querySelectorAll('.step-btn').forEach((btn) => {
    btn.addEventListener('click', () => setTarget(state.rpmTarget + parseInt(btn.dataset.step, 10)));
  });

  // ---------------- PID gain steppers (tuning tab) ----------------
  document.querySelectorAll('.stepper button').forEach((btn) => {
    btn.addEventListener('click', () => {
      const g = btn.dataset.gain;
      const delta = parseFloat(btn.dataset.delta);
      state.gains[g] = Math.max(0, +(state.gains[g] + delta).toFixed(2));
      document.getElementById(g + 'Val').value = state.gains[g];
    });
  });
  $('#applyGains')?.addEventListener('click', () => logEvent('Gains applied (live test)', 'info'));
  $('#saveGains')?.addEventListener('click', () => logEvent('Gains saved to flash', 'info'));

  // ---------------- settings ----------------
  $('#saveSettings')?.addEventListener('click', () => {
    state.maxRpm = parseInt($('#setMaxRpm').value, 10) || state.maxRpm;
    el.rpmSlider.max = state.maxRpm;
    logEvent('Settings saved to flash', 'info');
  });
  $('#restartBtn')?.addEventListener('click', () => {
    if (confirm('Restart the controller now?')) logEvent('Restart requested', 'warn');
  });

  // ---------------- fault simulation (diagnostics tab) ----------------
  $('#simStall')?.addEventListener('click', () => setFault('stalled', true));
  $('#simCurrent')?.addEventListener('click', () => setFault('currentLimited', true));
  $('#simClear')?.addEventListener('click', () => {
    setFault('stalled', false);
    setFault('currentLimited', false);
  });

  function setFault(which, value) {
    state[which] = value;
    if (value && which === 'stalled') { state.running = false; el.startBtn.disabled = false; }
    updateFaultBanner();
    logEvent(
      `${which === 'stalled' ? 'Stall' : 'Current-limit'} ${value ? 'detected' : 'cleared'}`,
      value ? 'err' : 'info'
    );
  }

  function updateFaultBanner() {
    el.faultBanner.classList.toggle('hidden', !(state.stalled || state.currentLimited));
    el.faultBanner.classList.toggle('stall', state.stalled);
    el.faultBanner.classList.toggle('current-limit', !state.stalled && state.currentLimited);
    el.faultBanner.textContent = state.stalled
      ? 'STALL DETECTED'
      : (state.currentLimited ? 'CURRENT LIMIT ACTIVE' : '');
  }

  function logEvent(text, level) {
    const li = document.createElement('li');
    const t = new Date().toLocaleTimeString();
    li.textContent = `[${t}] ${text}`;
    if (level === 'err') li.className = 'err';
    if (level === 'warn') li.className = 'warn';
    el.eventLog.prepend(li);
    while (el.eventLog.children.length > 50) el.eventLog.removeChild(el.eventLog.lastChild);
  }

  // ---------------- simulated telemetry loop ----------------
  function simulate() {
    if (state.running && !state.stalled && !state.currentLimited) {
      const err = state.rpmTarget - state.rpmActual;
      state.rpmActual += err * 0.12 + (Math.random() - 0.5) * 6;
      state.rpmActual = Math.max(0, state.rpmActual);
      state.dutyPercent = Math.max(0, Math.min(100, 20 + (state.rpmActual / (state.maxRpm || 1)) * 70));
    } else {
      state.rpmActual += (0 - state.rpmActual) * 0.2;
      state.dutyPercent *= 0.8;
    }

    el.rpmActual.textContent = Math.round(state.rpmActual);
    el.dutyReadout.textContent = Math.round(state.dutyPercent);
    const pct = state.maxRpm ? Math.min(100, (state.rpmActual / state.maxRpm) * 100) : 0;
    el.gauge.style.setProperty('--pct', pct.toFixed(1));

    const upSec = Math.floor((Date.now() - state.startedAt) / 1000);
    const hh = String(Math.floor(upSec / 3600)).padStart(2, '0');
    const mm = String(Math.floor((upSec % 3600) / 60)).padStart(2, '0');
    const ss = String(upSec % 60).padStart(2, '0');
    el.uptime.textContent = `Uptime ${hh}:${mm}:${ss}`;

    refreshDirectionLock();

    // Simulated Hall current sensor: tracks duty/load, spikes briefly on a
    // simulated current-limit fault. Simulated MOSFET temp: slow thermal
    // lag towards a running/stopped target (seconds-scale, unlike current).
    const targetCurrent = state.currentLimited ? 28 : (state.dutyPercent / 100) * 18;
    state.current += (targetCurrent - state.current) * 0.3 + (Math.random() - 0.5) * 0.4;
    state.current = Math.max(0, state.current);

    const targetTemp = 25 + (state.running ? (state.dutyPercent / 100) * 55 : 0);
    state.temperature += (targetTemp - state.temperature) * 0.02;

    el.diagCurrent.textContent = `${state.current.toFixed(1)} A`;
    el.diagTemp.textContent = `${state.temperature.toFixed(1)} °C`;

    state.history.push({ target: state.rpmTarget, actual: state.rpmActual });
    if (state.history.length > 120) state.history.shift();
    state.history2.push({ current: state.current, temp: state.temperature });
    if (state.history2.length > 120) state.history2.shift();
    drawChart(el.chart);
    drawChart(el.chart2);
    drawDualChart(el.chart3);
  }

  function drawChart(canvas) {
    if (!canvas || !canvas.getContext) return;
    const ctx = canvas.getContext('2d');
    const w = canvas.width, h = canvas.height;
    ctx.clearRect(0, 0, w, h);

    // grid
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

  // Current and temperature use independent scales/ranges (Amps vs °C),
  // so each series is normalized against its own fixed max rather than a
  // shared one like the RPM target/actual chart above.
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
    const maxCurrent = 30; // Amps - matches the hardware current-limit ballpark
    const maxTemp = 110;   // °C - headroom above a reasonable shutdown threshold

    const plot = (key, max, color) => {
      ctx.strokeStyle = color;
      ctx.lineWidth = 2;
      ctx.beginPath();
      state.history2.forEach((p, i) => {
        const x = i * stepX;
        const y = h - (p[key] / max) * h;
        i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
      });
      ctx.stroke();
    };
    plot('current', maxCurrent, 'rgba(59,130,246,0.9)');
    plot('temp', maxTemp, 'rgba(239,68,68,0.9)');
  }

  setInterval(simulate, 200);
  refreshDirectionLock();

  // ---------------- keep screen awake on real devices ----------------
  if ('wakeLock' in navigator) {
    navigator.wakeLock.request('screen').catch(() => { /* ignore - not critical for mockup */ });
  }
})();
