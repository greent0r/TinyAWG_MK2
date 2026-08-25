# -*- coding: utf-8
"""TinyAWG-MK2 信号发生器控制台 — PyQt6 工业风上位机。

运行(在 tools 目录下):  python -m pc_host_qt.main
运行(在 pc_host_qt 目录下): python -m main  或  python main.py
依赖: PyQt6 pyserial numpy
"""
import os
import sys
import time

# 让本包无论从 tools/ 还是包目录内启动都能被导入
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import numpy as np
from PyQt6.QtCore import Qt, QTimer, pyqtSlot
from PyQt6.QtWidgets import (
    QMainWindow, QWidget, QLabel, QLineEdit, QComboBox, QCheckBox, QPushButton,
    QHBoxLayout, QVBoxLayout, QGridLayout, QTabWidget, QTableWidget, QTableWidgetItem,
    QGroupBox, QProgressBar, QFileDialog, QMessageBox, QSplitter, QFrame, QScrollArea,
    QFormLayout, QHeaderView, QSizePolicy, QApplication,
)
from PyQt6.QtGui import QFont, QPainter, QColor, QPen

from pc_host_qt import __version__
from pc_host_qt.theme import (
    qss, APP_NAME, APP_VERSION, C_CYAN, C_GREEN, C_AMBER, C_RED, C_TEXT,
    C_TEXT_MUT, C_BG, C_GOLD, C_CYAN_CH, FONT_MONO,
)
from pc_host_qt.protocol import (
    ProtocolWorker, WAVE_NAMES, WAVE_PARAMS, PARAM_INFO, MOD_PARAMS,
    DEPTH_NAMES, USER_WAVE_POINTS,
)
from pc_host_qt.waveform import (
    resample_to_1m, import_file, export_file, apply_ops, render_wave, TARGET_POINTS,
)
from pc_host_qt.drawcanvas import WaveCanvas, points_to_1m
from pc_host_qt.widgets import (
    ValueBox, StatusLED, button, panel, vbox, hbox, scroll_area, hline, SectionLabel,
)

BAUD_RATE = 2000000


def f(v, default=0.0):
    try:
        return float(v)
    except (TypeError, ValueError):
        return default


def i(v, default=0):
    try:
        return int(float(v))
    except (TypeError, ValueError):
        return default


# ============================================================================
# 连接栏
# ============================================================================
class ConnectionBar(QWidget):
    def __init__(self, worker: ProtocolWorker, parent=None):
        super().__init__(parent)
        self.worker = worker
        self.setObjectName("topbar")
        lay = QHBoxLayout(self)
        lay.setContentsMargins(12, 6, 12, 6)
        lay.setSpacing(10)

        title = QLabel(APP_NAME)
        title.setObjectName("appTitle")
        lay.addWidget(title)
        sub = QLabel("Zynq-7000 双通道任意波形发生器 · 协议 v2")
        sub.setObjectName("appSub")
        lay.addWidget(sub)

        lay.addStretch(1)

        self.port = QComboBox()
        self.port.setMinimumWidth(150)
        self.port.addItems(self._list_ports())
        lay.addWidget(self.port)

        self.baud = QComboBox()
        self.baud.addItems(["2000000", "115200", "921600", "1000000"])
        self.baud.setCurrentText(str(BAUD_RATE))
        lay.addWidget(self.baud)

        self.btn_conn = button("连 接", accent=True)
        self.btn_conn.clicked.connect(self.toggle_connect)
        lay.addWidget(self.btn_conn)

        self.btn_sync = button("同步状态")
        self.btn_sync.clicked.connect(self.worker.query)
        self.btn_sync.setEnabled(False)
        lay.addWidget(self.btn_sync)

        self.led = StatusLED("未连接", C_TEXT_MUT)
        lay.addWidget(self.led)

        self.bat = QLabel("-- --")
        self.bat.setStyleSheet(f"color: {C_GREEN}; font-family: {FONT_MONO}; font-weight: bold;")
        lay.addWidget(self.bat)

        self.ch_badge = QLabel("控制通道: CH0")
        self.ch_badge.setStyleSheet(f"color: {C_CYAN}; font-weight: bold; font-size: 14px; letter-spacing: 1px;")
        lay.addWidget(self.ch_badge)

    @staticmethod
    def _list_ports():
        try:
            import serial.tools.list_ports as lp
            return [p.device for p in lp.comports()] or ["COM1"]
        except Exception:
            return ["COM1"]

    def refresh_ports(self):
        self.port.clear()
        self.port.addItems(self._list_ports())

    def toggle_connect(self):
        if self.worker.is_open():
            self.worker.close()
            self.led.set_status("未连接", C_TEXT_MUT)
            self.btn_conn.setText("连 接")
            self.btn_conn.setProperty("accent", "1")
            self.btn_sync.setEnabled(False)
        else:
            if self.worker.open_serial(self.port.currentText(), int(self.baud.currentText())):
                self.led.set_status("已连接", C_GREEN)
                self.btn_conn.setText("断 开")
                self.btn_conn.setProperty("accent", "0")
                self.btn_conn.setStyleSheet("")  # 触发样式刷新
                self.btn_conn.setProperty("danger", "1")
                self.btn_sync.setEnabled(True)
                self.worker.query()   # 连接时同步一次设备状态

    def on_connected(self, ok: bool):
        self.refresh_ports()
        if ok:
            self.led.set_status("已连接", C_GREEN)
            self.btn_conn.setText("断 开")
            self.btn_conn.setProperty("danger", "1")
            self.btn_sync.setEnabled(True)
            self.worker.query()
        else:
            self.led.set_status("未连接", C_TEXT_MUT)
            self.btn_conn.setText("连 接")
            self.btn_conn.setProperty("danger", "0")
            self.btn_sync.setEnabled(False)

    def on_status(self, s: dict):
        soc = i(s.get("bat"))
        v = i(s.get("batv"))
        self.bat.setText(f"{soc}%  {v}mV")
        self.set_ch(i(s.get("ch")))

    def set_ch(self, ch):
        """顶栏通道指示（供点击切换与状态同步两处调用）。"""
        self.ch_badge.setText(f"控制通道: CH{ch}")
        self.ch_badge.setStyleSheet(
            f"color: {C_CYAN if ch == 0 else C_CYAN_CH}; font-weight: bold; font-size: 14px; letter-spacing: 1px;")

    def on_error(self, msg):
        self.led.set_status("错误", C_RED)
        QMessageBox.critical(self, "错误", msg)


# ============================================================================
# 页面基类
# ============================================================================
class PageBase(QWidget):
    def __init__(self, worker: ProtocolWorker, conn: ConnectionBar, parent=None):
        super().__init__(parent)
        self.worker = worker
        self.conn = conn
        self._debounce_timers = {}
        self._bindings = []  # (key, widget, getter, setter)

    def debounce(self, key, ms=250):
        if key not in self._debounce_timers:
            t = QTimer(self)
            t.setSingleShot(True)
            self._debounce_timers[key] = t
        return self._debounce_timers[key]

    def wire(self, key, widget, getter=None, setter=None):
        """绑定状态键到控件：状态刷新时自动更新控件；控件变化时自动发送。"""
        self._bindings.append((key, widget, getter, setter))
        return widget

    def sync(self, s: dict):
        for key, widget, getter, setter in self._bindings:
            if key not in s:
                continue
            val = s[key]
            try:
                if getter is None:
                    widget.blockSignals(True)
                    widget.set_value(f(val))
                    widget.blockSignals(False)
                else:
                    widget.blockSignals(True)
                    getter(widget, val)
                    widget.blockSignals(False)
            except Exception:
                pass

    def send(self, key, val):
        self.worker.set_params(**{key: val})


# ============================================================================
# 常规波形页
# ============================================================================
class StandardPage(PageBase):
    def __init__(self, worker, conn, parent=None):
        super().__init__(worker, conn, parent)
        self._preview = None
        self._param_boxes = {}

        root = vbox(self, margins=(0, 0, 0, 0))
        body = QSplitter(Qt.Orientation.Horizontal)

        # 左侧控制
        left = QWidget()
        leftlay = vbox(left, spacing=8)
        g_ch = panel("通道")
        gl = QGridLayout(g_ch)
        self.btn_ch0 = button("CH0")
        self.btn_ch1 = button("CH1")
        self.btn_ch0.setProperty("accent", "1")
        self.btn_ch0.setMinimumHeight(34)
        self.btn_ch1.setMinimumHeight(34)
        self.btn_ch0.clicked.connect(lambda: self._on_ch(0))
        self.btn_ch1.clicked.connect(lambda: self._on_ch(1))
        self.ch_hint = QLabel("当前控制通道，点击切换")
        self.ch_hint.setStyleSheet(f"color: {C_TEXT_MUT}; font-size: 11px;")
        gl.addWidget(self.btn_ch0, 0, 0)
        gl.addWidget(self.btn_ch1, 0, 1)
        gl.addWidget(self.ch_hint, 1, 0, 1, 2)
        leftlay.addWidget(g_ch)

        g_wave = panel("波形类型")
        gl = QGridLayout(g_wave)
        self.wave_combo = QComboBox()
        self.wave_combo.addItems(WAVE_NAMES)
        self.wave_combo.currentIndexChanged.connect(self._on_wave_combo)
        gl.addWidget(self.wave_combo, 0, 0, 1, 2)
        leftlay.addWidget(g_wave)

        g_base = panel("基础参数")
        gl = QGridLayout(g_base)
        self.freq = ValueBox("频率", "Hz", decimals=3, step=1, lo=0.1, hi=1e8)
        self.vpp = ValueBox("峰峰值", "V", decimals=3, step=0.01, lo=0.0, hi=20)
        self.off = ValueBox("偏置", "V", decimals=3, step=0.01, lo=-10, hi=10)
        self.phase = ValueBox("相位", "°", decimals=2, step=1, lo=-360, hi=360)
        for w, key in ((self.freq, "freq"), (self.vpp, "vpp"),
                       (self.off, "offset"), (self.phase, "phase")):
            w.set_key(key)
            w.value_changed.connect(lambda k, v: self.send(k, f"{v:.4g}"))
        gl.addWidget(self.freq, 0, 0)
        gl.addWidget(self.vpp, 0, 1)
        gl.addWidget(self.off, 1, 0)
        gl.addWidget(self.phase, 1, 1)
        leftlay.addWidget(g_base)

        g_p = panel("波形专属参数")
        self.param_area = QWidget()
        self.param_lay = QGridLayout(self.param_area)
        self.param_lay.setSpacing(6)
        g_p.setLayout(QVBoxLayout())
        g_p.layout().addWidget(self.param_area)
        leftlay.addWidget(g_p)

        leftlay.addStretch(1)

        # 右侧预览
        right = QWidget()
        rl = vbox(right, spacing=8)
        title = QLabel("本地波形预览")
        title.setStyleSheet(f"color: {C_CYAN}; font-weight: bold; letter-spacing: 2px;")
        self.preview = WaveCanvas()
        self.preview.setMinimumSize(360, 240)
        rl.addWidget(title)
        rl.addWidget(self.preview)
        right.setLayout(rl)

        body.addWidget(left)
        body.addWidget(right)
        body.setSizes([360, 420])
        root.addWidget(body)

        self.wire("freq", self.freq)
        self.wire("vpp", self.vpp)
        self.wire("offset", self.off)
        self.wire("phase", self.phase)
        self.wire("wave", self.wave_combo, getter=self._set_wave_combo)
        self._refresh_params(0)
        self._render(0)

    def _set_wave_combo(self, combo, val):
        idx = i(val)
        if 0 <= idx < len(WAVE_NAMES):
            combo.setCurrentIndex(idx)

    def _on_wave_combo(self, idx):
        if 0 <= idx < len(WAVE_NAMES):
            self.send("wave", idx)
            self._refresh_params(idx)
            self._render(idx)

    def _refresh_params(self, idx):
        if getattr(self, "_current_param_wave", None) == idx:
            return
        self._current_param_wave = idx
        # 移除旧的波形专属参数绑定与控件
        old_keys = set()
        for b in list(self._bindings):
            if b[0] in PARAM_INFO:
                old_keys.add(b[0])
        self._bindings = [b for b in self._bindings if b[0] not in old_keys]
        # 清空参数区布局中的旧控件
        while self.param_lay.count():
            item = self.param_lay.takeAt(0)
            w = item.widget()
            if w:
                w.setParent(None)
                w.deleteLater()
        self._param_boxes.clear()

        keys = WAVE_PARAMS.get(idx, [])
        for j, key in enumerate(keys):
            info = PARAM_INFO.get(key)
            if not info:
                continue
            label, unit, step, dec, lo, hi = info
            if key == "rising":
                c = QComboBox()
                c.addItems(["下降", "上升"])
                c.currentIndexChanged.connect(lambda _idx, k=key: self.send(k, _idx))
                self.param_lay.addWidget(QLabel(label), j, 0)
                self.param_lay.addWidget(c, j, 1)
                self.wire(key, c, getter=self._set_rising_combo)
            else:
                vb = ValueBox(label, unit, decimals=dec, step=step, lo=lo, hi=hi)
                vb.set_key(key)
                vb.value_changed.connect(lambda k, v: self.send(k, f"{v:.6g}"))
                self.param_lay.addWidget(vb, j, 0, 1, 2)
                self._param_boxes[key] = vb
                self.wire(key, vb)

    def _set_rising_combo(self, combo, val):
        combo.setCurrentIndex(i(val) & 1)

    def _on_ch(self, ch):
        self._set_ch(ch)
        self.conn.set_ch(ch)
        self.send("ch", ch)

    def _set_ch(self, ch):
        """高亮当前控制通道按钮：选中通道青色填充，未选中暗色。"""
        self.btn_ch0.setProperty("accent", "1" if ch == 0 else "0")
        self.btn_ch1.setProperty("accent", "1" if ch == 1 else "0")
        # 强制重新应用样式
        self.btn_ch0.setStyleSheet("")
        self.btn_ch1.setStyleSheet("")
        self.ch_hint.setText(f"当前控制通道: CH{ch}")

    def _render(self, idx, state=None):
        params = {}
        for key in WAVE_PARAMS.get(idx, []):
            if key in self._param_boxes:
                params[key] = self._param_boxes[key].value()
            elif state and key in state:
                params[key] = f(state[key])
            else:
                params[key] = 0.0
        arr = render_wave(idx, params)
        n = len(arr)
        pts = [(j / max(1, n - 1), float(arr[j])) for j in range(n)]
        self.preview.set_points(pts)

    def sync(self, s):
        self._last_state = s
        self._set_ch(i(s.get("ch")))
        idx = i(s.get("wave"))
        if self.wave_combo.currentIndex() != idx:
            self.wave_combo.blockSignals(True)
            self.wave_combo.setCurrentIndex(idx)
            self.wave_combo.blockSignals(False)
        self._refresh_params(idx)
        super().sync(s)
        self._render(idx, s)

    def on_state_refresh(self):
        self.worker.query()


# ============================================================================
# 调制页
# ============================================================================
class ModPage(PageBase):
    def __init__(self, worker, conn, parent=None):
        super().__init__(worker, conn, parent)
        root = vbox(self, margins=(0, 0, 0, 0))

        g_main = panel("调制设置")
        gl = QGridLayout(g_main)
        self.en = QCheckBox("启用调制")
        self.en.toggled.connect(lambda on: self.send("m_en", 1 if on else 0))
        self.mode = QComboBox()
        self.mode.addItems(["AM", "FM", "PM"])
        self.mode.currentIndexChanged.connect(lambda idx: self.send("m_mode", idx))
        self.base = ValueBox("调制频率", "Hz", decimals=3, step=1, lo=0.1, hi=1e8)
        self.carr = ValueBox("载波频率", "Hz", decimals=3, step=1, lo=0.1, hi=1e8)
        self.base.set_key("m_base")
        self.carr.set_key("m_carr")
        self.base.value_changed.connect(lambda k, v: self.send(k, f"{v:.6g}"))
        self.carr.value_changed.connect(lambda k, v: self.send(k, f"{v:.6g}"))
        gl.addWidget(self.en, 0, 0)
        gl.addWidget(self.mode, 0, 1)
        gl.addWidget(self.base, 1, 0)
        gl.addWidget(self.carr, 1, 1)
        root.addWidget(g_main)

        g_extra = panel("调制深度参数")
        self.extra_area = QWidget()
        self.extra_lay = QGridLayout(self.extra_area)
        g_extra.setLayout(QVBoxLayout())
        g_extra.layout().addWidget(self.extra_area)
        root.addWidget(g_extra)
        root.addStretch(1)

        self.wire("m_en", self.en, getter=self._set_en)
        self.wire("m_mode", self.mode, getter=self._set_mode)
        self.wire("m_base", self.base)
        self.wire("m_carr", self.carr)

        self._mode_boxes = {}
        self._refresh_extra(0)

    def _set_en(self, w, v):
        w.setChecked(i(v) == 1)

    def _set_mode(self, w, v):
        idx = i(v)
        if 0 <= idx < 3:
            w.blockSignals(True)
            w.setCurrentIndex(idx)
            w.blockSignals(False)
            self._refresh_extra(idx)

    def _refresh_extra(self, mode):
        if getattr(self, "_current_mod_mode", None) == mode and self._mode_boxes:
            return
        self._current_mod_mode = mode
        for key in ("m_depth", "m_dev", "m_index"):
            self._bindings = [b for b in self._bindings if b[0] != key]
        for w in list(self._mode_boxes.values()):
            w.setParent(None)
            w.deleteLater()
        self._mode_boxes.clear()
        while self.extra_lay.count():
            item = self.extra_lay.takeAt(0)
            w = item.widget()
            if w:
                w.setParent(None)
                w.deleteLater()

        for j, key in enumerate(MOD_PARAMS.get(mode, [])):
            info = {"m_depth": ("深度", "%", 0.01, 2, 0.0, 1.0),
                    "m_dev": ("最大频偏", "Hz", 1, 0, 0.0, 1e8),
                    "m_index": ("相偏", "rad", 0.01, 2, 0.0, 100.0)}[key]
            label, unit, step, dec, lo, hi = info
            vb = ValueBox(label, unit, decimals=dec, step=step, lo=lo, hi=hi)
            vb.set_key(key)
            vb.value_changed.connect(lambda k, v: self.send(k, f"{v:.6g}"))
            self.extra_lay.addWidget(vb, j, 0)
            self._mode_boxes[key] = vb
            self.wire(key, vb)

    def sync(self, s):
        super().sync(s)
        self._refresh_extra(i(s.get("m_mode")))


# ============================================================================
# 扫频页
# ============================================================================
class ScanPage(PageBase):
    def __init__(self, worker, conn, parent=None):
        super().__init__(worker, conn, parent)
        root = vbox(self, margins=(0, 0, 0, 0))

        g = panel("扫频设置（仅 32K 存储模式）")
        gl = QGridLayout(g)
        self.en = QCheckBox("开始扫频")
        self.en.toggled.connect(self._toggle)
        self.loop = QCheckBox("循环")
        self.loop.toggled.connect(lambda on: self.send("s_loop", 1 if on else 0))
        self.mode = QComboBox()
        self.mode.addItems(["线性", "对数"])
        self.mode.currentIndexChanged.connect(lambda idx: self.send("s_mode", idx))
        self.start = ValueBox("起始频率", "Hz", decimals=3, step=1, lo=0.0, hi=1e8)
        self.end = ValueBox("终止频率", "Hz", decimals=3, step=1, lo=0.0, hi=1e8)
        self.points = ValueBox("点数", "", integer=True, step=10, lo=2, hi=100000)
        self.interval = ValueBox("驻留间隔", "ns", integer=True, step=100, lo=500, hi=100000000)
        for w, key in ((self.start, "s_start"), (self.end, "s_end"),
                       (self.points, "s_points"), (self.interval, "s_intv")):
            w.set_key(key)
            w.value_changed.connect(lambda k, v: self.send(k, f"{v:.6g}" if isinstance(v, float) else int(v)))
        gl.addWidget(self.en, 0, 0)
        gl.addWidget(self.loop, 0, 1)
        gl.addWidget(self.mode, 0, 2)
        gl.addWidget(self.start, 1, 0)
        gl.addWidget(self.end, 1, 1)
        gl.addWidget(self.points, 2, 0)
        gl.addWidget(self.interval, 2, 1)
        root.addWidget(g)
        root.addStretch(1)

        self.wire("s_loop", self.loop, getter=self._set_check)
        self.wire("s_mode", self.mode, getter=self._set_mode)
        self.wire("s_start", self.start)
        self.wire("s_end", self.end)
        self.wire("s_points", self.points)
        self.wire("s_intv", self.interval)

    def _set_check(self, w, v):
        w.setChecked(i(v) == 1)

    def _set_mode(self, w, v):
        w.blockSignals(True)
        w.setCurrentIndex(i(v))
        w.blockSignals(False)

    def _toggle(self, on):
        if on:
            if i(self.worker.state.get("dds_sel")) != 0:
                self.en.setChecked(False)
                QMessageBox.warning(self, "无法启动", "扫频仅支持 32K(bram_dds) 存储模式")
                return
            self.send("s_run", 1)
        else:
            self.send("s_run", 0)

    def sync(self, s):
        super().sync(s)
        running = i(s.get("s_run")) == 1
        self.en.blockSignals(True)
        self.en.setChecked(running)
        self.en.blockSignals(False)


# ============================================================================
# 谐波页
# ============================================================================
class HarmonicPage(PageBase):
    def __init__(self, worker, conn, parent=None):
        super().__init__(worker, conn, parent)
        root = vbox(self, margins=(0, 0, 0, 0))

        g = panel("谐波合成（基波频率=常规页频率）")
        gl = QGridLayout(g)
        self.en = QCheckBox("启用谐波")
        self.en.toggled.connect(lambda on: self.send("h_en", 1 if on else 0))
        self.count = ValueBox("谐波个数", "", integer=True, step=1, lo=1, hi=16)
        self.idx = ValueBox("编辑序号", "", integer=True, step=1, lo=1, hi=16)
        self.count.set_key("h_count")
        self.idx.set_key("h_idx")
        self.count.value_changed.connect(lambda k, v: self.send(k, int(v)))
        self.idx.value_changed.connect(lambda k, v: self.send(k, int(v)))
        gl.addWidget(self.en, 0, 0)
        gl.addWidget(self.count, 0, 1)
        gl.addWidget(self.idx, 0, 2)
        root.addWidget(g)

        self.table = QTableWidget(16, 3)
        self.table.setHorizontalHeaderLabels(["谐波", "幅值(%)", "相位(°)"])
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        self.table.verticalHeader().setVisible(False)
        for r in range(16):
            item = QTableWidgetItem(f"{r+1}次")
            item.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
            item.setFlags(item.flags() & ~Qt.ItemFlag.ItemIsEditable)
            self.table.setItem(r, 0, item)
            amp = QTableWidgetItem("100")
            ph = QTableWidgetItem("0")
            amp.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
            ph.setTextAlignment(Qt.AlignmentFlag.AlignCenter)
            self.table.setItem(r, 1, amp)
            self.table.setItem(r, 2, ph)
        self.table.itemChanged.connect(self._on_cell)
        root.addWidget(self.table)

        btn = button("应用谐波参数", accent=True)
        btn.clicked.connect(self.apply_all)
        root.addWidget(btn)

        self.wire("h_en", self.en, getter=self._set_check)
        self.wire("h_count", self.count)
        self.wire("h_idx", self.idx)

    def _set_check(self, w, v):
        w.setChecked(i(v) == 1)

    def _on_cell(self, item):
        r = item.row()
        col = item.column()
        if col == 0 or r >= 16:
            return
        try:
            val = float(item.text())
        except ValueError:
            return
        key = f"h_amp{r+1}" if col == 1 else f"h_ph{r+1}"
        # 单条短命令 + h_apply 立即触发一次重生成（固件按≤64字节短命令接收）
        self.worker.set_params(**{key: f"{val:.4f}", "h_apply": 1})

    def apply_all(self):
        ch = i(self.conn.worker.state.get("ch"))
        # 先开关/个数/序号（短命令）
        self.worker.set_params(ch=ch, h_en=1 if self.en.isChecked() else 0,
                               h_count=i(self.count.value()), h_idx=i(self.idx.value()))
        # 再逐行短命令发送幅值/相位（不重生成）
        for r in range(16):
            try:
                amp = float(self.table.item(r, 1).text())
            except ValueError:
                amp = 0.0
            try:
                ph = float(self.table.item(r, 2).text())
            except ValueError:
                ph = 0.0
            self.worker.set_params(**{f"h_amp{r+1}": f"{amp:.4f}", f"h_ph{r+1}": f"{ph:.4f}"})
        # 最后统一触发一次谐波重生成
        self.worker.set_params(h_apply=1)

    def sync(self, s):
        super().sync(s)
        self.table.blockSignals(True)
        for r in range(16):
            amp = s.get(f"h_amp{r+1}")
            ph = s.get(f"h_ph{r+1}")
            if amp is not None:
                self.table.item(r, 1).setText(f"{f(amp):.1f}")
            if ph is not None:
                self.table.item(r, 2).setText(f"{f(ph):.1f}")
        self.table.blockSignals(False)


# ============================================================================
# 脉冲页
# ============================================================================
class PulsePage(PageBase):
    def __init__(self, worker, conn, parent=None):
        super().__init__(worker, conn, parent)
        root = vbox(self, margins=(0, 0, 0, 0))

        g = panel("脉冲串（突发输出）")
        gl = QGridLayout(g)
        self.en = QCheckBox("启用脉冲功能")
        self.en.toggled.connect(lambda on: self.send("b_en", 1 if on else 0))
        self.cycles = ValueBox("循环数(0=连续)", "", integer=True, step=1, lo=0, hi=999999)
        self.phase = ValueBox("相位", "°", decimals=2, step=1, lo=-180, hi=180)
        self.delay = ValueBox("触发延迟", "µs", integer=True, step=1, lo=0, hi=1000000)
        self.cycles.set_key("b_cycles")
        self.phase.set_key("b_phase")
        self.delay.set_key("b_delay")
        self.cycles.value_changed.connect(lambda k, v: self.send(k, int(v)))
        self.phase.value_changed.connect(lambda k, v: self.send(k, f"{v:.4f}"))
        self.delay.value_changed.connect(lambda k, v: self.send(k, int(v)))
        gl.addWidget(self.en, 0, 0)
        gl.addWidget(self.cycles, 0, 1)
        gl.addWidget(self.phase, 1, 0)
        gl.addWidget(self.delay, 1, 1)
        root.addWidget(g)

        trig = button("手动触发一次", accent=True)
        trig.clicked.connect(lambda: self.send("b_trig", 1))
        root.addWidget(trig)
        root.addStretch(1)

        self.wire("b_en", self.en, getter=self._set_check)
        self.wire("b_cycles", self.cycles)
        self.wire("b_phase", self.phase)
        self.wire("b_delay", self.delay)

    def _set_check(self, w, v):
        w.setChecked(i(v) == 1)


# ============================================================================
# 用户波形页
# ============================================================================
class UserWavePage(PageBase):
    def __init__(self, worker, conn, parent=None):
        super().__init__(worker, conn, parent)
        root = vbox(self, margins=(0, 0, 0, 0))

        g = panel("用户波形编辑器（32 组 × 512K 点，上传后自动重采样到 512K）")
        gl = QGridLayout(g)

        self.group = QComboBox()
        self.group.addItems([f"组 {i:02d}" for i in range(32)])
        self.group.setCurrentIndex(0)
        self.group.currentIndexChanged.connect(lambda idx: self.send("u_sel", idx))
        gl.addWidget(QLabel("目标组"), 0, 0)
        gl.addWidget(self.group, 0, 1)

        self.out = QCheckBox("输出用户波形（当前通道）")
        self.out.toggled.connect(self._toggle_out)
        gl.addWidget(self.out, 0, 2)

        self.depth_info = QLabel("存储深度需 ≤ 512K 才能输出用户波形")
        self.depth_info.setStyleSheet(f"color: {C_AMBER};")
        gl.addWidget(self.depth_info, 0, 3)

        self.canvas = WaveCanvas()   # 先创建画布，供下方工具按钮连接信号

        self.import_btn = button("导入文件", amber=True)
        self.import_btn.clicked.connect(self.import_file)
        self.export_btn = button("导出波形")
        self.export_btn.clicked.connect(self.export_file)
        self.clear_btn = button("清空")
        self.clear_btn.clicked.connect(self.canvas.clear)
        self.undo_btn = button("撤销")
        self.undo_btn.clicked.connect(self.canvas.undo)
        self.smooth_btn = button("平滑")
        self.smooth_btn.clicked.connect(self.canvas.smooth)
        self.norm_btn = button("归一化")
        self.norm_btn.clicked.connect(self.canvas.normalize)
        self.inv_btn = button("取反")
        self.inv_btn.clicked.connect(self.canvas.invert)
        gl.addWidget(self.import_btn, 1, 0)
        gl.addWidget(self.export_btn, 1, 1)
        gl.addWidget(self.clear_btn, 2, 0)
        gl.addWidget(self.undo_btn, 2, 1)
        gl.addWidget(self.smooth_btn, 3, 0)
        gl.addWidget(self.norm_btn, 3, 1)
        gl.addWidget(self.inv_btn, 3, 2)
        root.addWidget(g)

        self.canvas.setMinimumSize(300, 220)
        self.canvas.changed.connect(self._on_canvas_change)
        root.addWidget(self.canvas, 1)
        self.info = QLabel("点数: 2   状态: 待编辑（左键绘制/右键撤销/C清空/Z撤销/S平滑/N归一化/I取反）")
        self.info.setStyleSheet(f"color: {C_TEXT_MUT};")
        root.addWidget(self.info)

        self.progress = QProgressBar()
        self.progress.setRange(0, 1000)
        self.progress.setValue(0)
        self.progress.setFormat("%p%  %v KB / %m KB")
        root.addWidget(self.progress)

        self.upload_btn = button("上传到设备", accent=True)
        self.upload_btn.clicked.connect(self.upload)
        root.addWidget(self.upload_btn)

        self.wire("u_sel", self.group, getter=self._set_group)
        self.wire("u_en", self.out, getter=self._set_out)
        self.wire("depth", self.depth_info, getter=self._set_depth)

    def _set_group(self, w, v):
        idx = i(v)
        if 0 <= idx < 32:
            w.blockSignals(True)
            w.setCurrentIndex(idx)
            w.blockSignals(False)

    def _set_out(self, w, v):
        w.setChecked(i(v) == 1)

    def _set_depth(self, w, v):
        depth = i(v)
        ok = depth <= 3  # 0..3 => 32K..512K
        self.depth_info.setStyleSheet(
            f"color: {C_GREEN if ok else C_AMBER};")
        self.depth_info.setText(
            "存储深度 ≤ 512K，可输出用户波形" if ok else
            f"当前存储深度 {DEPTH_NAMES[depth] if 0 <= depth < len(DEPTH_NAMES) else '?'} > 512K，禁止输出用户波形")

    def _toggle_out(self, on):
        if on:
            depth = i(self.worker.state.get("depth"))
            if depth > 3:  # 存储深度 > 512K
                self.out.blockSignals(True)
                self.out.setChecked(False)
                self.out.blockSignals(False)
                QMessageBox.warning(self, "无法输出", "当前存储深度超过 512K，请先在系统页切换到 ≤512K")
                return
        self.send("u_en", 1 if on else 0)

    def _on_canvas_change(self):
        n = len(self.canvas.points)
        self.info.setText(f"编辑点: {n}   (上传时将重采样到 {TARGET_POINTS:,} 点 = 512K)")

    def import_file(self):
        path, _ = QFileDialog.getOpenFileName(
            self, "导入波形文件", "", "波形文件 (*.wav *.csv *.txt *.bin *.raw);;所有文件 (*)")
        if not path:
            return
        try:
            raw = import_file(path)
        except Exception as e:
            QMessageBox.critical(self, "导入失败", str(e))
            return
        # 重采样到 512K 并预览（画布显示前 512 点）
        samples = resample_to_1m(raw, normalize=True)
        n = 512
        xs = np.linspace(0.0, 1.0, n)
        ys = samples[np.linspace(0, len(samples) - 1, n).astype(int)] / 32767.0
        pts = list(zip(xs.tolist(), ys.tolist()))
        self.canvas.set_points(pts)
        self.info.setText(
            f"已导入: {os.path.basename(path)} ({len(raw):,} 点 → 重采样到 {TARGET_POINTS:,} 点)")

    def export_file(self):
        path, _ = QFileDialog.getSaveFileName(
            self, "导出波形", "user_wave.wav", "WAV (*.wav);;CSV (*.csv);;BIN (*.bin)")
        if not path:
            return
        try:
            samples = self._to_samples()
            export_file(path, samples)
            self.info.setText(f"已导出: {path}")
        except Exception as e:
            QMessageBox.critical(self, "导出失败", str(e))

    def _to_samples(self):
        vals = points_to_1m(self.canvas.points)
        return resample_to_1m(vals, normalize=True)

    def upload(self):
        group = self.group.currentIndex()
        try:
            samples = self._to_samples()
        except Exception as e:
            QMessageBox.critical(self, "处理失败", str(e))
            return
        payload = samples.tobytes()  # int16 little-endian
        self.worker.upload_wave(group, payload)
        self.progress.setValue(0)

    def sync(self, s):
        super().sync(s)
        self._set_depth(self.depth_info, s.get("depth", "0"))
        self.progress.setValue(0)


# ============================================================================
# 系统页
# ============================================================================
class SystemPage(PageBase):
    def __init__(self, worker, conn, parent=None):
        super().__init__(worker, conn, parent)
        root = vbox(self, margins=(0, 0, 0, 0))

        g = panel("系统")
        gl = QGridLayout(g)
        self.depth = QComboBox()
        self.depth.addItems(DEPTH_NAMES)
        self.depth.currentIndexChanged.connect(lambda idx: self.send("depth", idx))
        gl.addWidget(QLabel("存储深度"), 0, 0)
        gl.addWidget(self.depth, 0, 1)

        self.buzz = QCheckBox("按键蜂鸣")
        self.buzz.toggled.connect(lambda on: self.send("buzz", 1 if on else 0))
        gl.addWidget(self.buzz, 0, 2)

        self.sync_btn = button("双通道同步", accent=True)
        self.sync_btn.clicked.connect(lambda: self.send("sync", 1))
        gl.addWidget(self.sync_btn, 0, 3)
        root.addWidget(g)

        g2 = panel("输出通道")
        gl = QGridLayout(g2)
        self.out0 = QCheckBox("通道0 输出")
        self.out0.toggled.connect(lambda on: self.send("out0", 1 if on else 0))
        self.out1 = QCheckBox("通道1 输出")
        self.out1.toggled.connect(lambda on: self.send("out1", 1 if on else 0))
        gl.addWidget(self.out0, 0, 0)
        gl.addWidget(self.out1, 0, 1)
        root.addWidget(g2)

        g3 = panel("电池与状态")
        gl = QGridLayout(g3)
        self.bat = QLabel("--")
        self.batv = QLabel("--")
        self.bat.setStyleSheet(f"color: {C_GREEN}; font-family: {FONT_MONO}; font-weight: bold; font-size: 16px;")
        self.batv.setStyleSheet(f"color: {C_TEXT}; font-family: {FONT_MONO}; font-size: 14px;")
        gl.addWidget(QLabel("电量"), 0, 0)
        gl.addWidget(self.bat, 0, 1)
        gl.addWidget(QLabel("电压"), 0, 2)
        gl.addWidget(self.batv, 0, 3)
        root.addWidget(g3)

        g4 = panel("DAC 校准电压测试（0~5V）")
        gl = QGridLayout(g4)
        self.dac_boxes = []
        self.dac_names = ["REFIO0", "REFIO1", "VG_in0", "VG_in1", "OFFSET_in0", "OFFSET_in1"]
        for i, name in enumerate(self.dac_names):
            vb = ValueBox(name, "V", decimals=4, step=0.01, lo=0.0, hi=5.0)
            self.dac_boxes.append(vb)
            gl.addWidget(vb, i // 2, i % 2)
        dac_btn = button("写入 DAC", accent=True)
        dac_btn.clicked.connect(self.apply_dac)
        gl.addWidget(dac_btn, 3, 0, 1, 2)
        root.addWidget(g4)

        root.addStretch(1)

        self.wire("depth", self.depth, getter=self._set_depth)
        self.wire("buzz", self.buzz, getter=self._set_check)
        self.wire("out0", self.out0, getter=self._set_check)
        self.wire("out1", self.out1, getter=self._set_check)
        self.wire("bat", self.bat, getter=self._set_text)
        self.wire("batv", self.batv, getter=self._set_text)

    def _set_check(self, w, v):
        w.setChecked(i(v) == 1)

    def _set_depth(self, w, v):
        idx = i(v)
        if 0 <= idx < len(DEPTH_NAMES):
            w.blockSignals(True)
            w.setCurrentIndex(idx)
            w.blockSignals(False)

    def _set_text(self, w, v):
        w.setText(str(v))

    def apply_dac(self):
        volts = [vb.value() for vb in self.dac_boxes]
        self.worker.set_dac(volts)

    def sync(self, s):
        super().sync(s)


# ============================================================================
# 主窗口
# ============================================================================
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle(f"{APP_NAME}  v{APP_VERSION}")
        self.resize(1120, 720)
        self.setStyleSheet(qss())

        self.worker = ProtocolWorker(self)
        self.connbar = ConnectionBar(self.worker, self)
        self.setMenuWidget(self.connbar)

        self.tabs = QTabWidget()
        self.std_page = StandardPage(self.worker, self.connbar)
        self.mod_page = ModPage(self.worker, self.connbar)
        self.scan_page = ScanPage(self.worker, self.connbar)
        self.harmonic_page = HarmonicPage(self.worker, self.connbar)
        self.pulse_page = PulsePage(self.worker, self.connbar)
        self.user_page = UserWavePage(self.worker, self.connbar)
        self.sys_page = SystemPage(self.worker, self.connbar)

        self.tabs.addTab(scroll_area(self.std_page), "常规")
        self.tabs.addTab(scroll_area(self.mod_page), "调制")
        self.tabs.addTab(scroll_area(self.scan_page), "扫频")
        self.tabs.addTab(scroll_area(self.harmonic_page), "谐波")
        self.tabs.addTab(scroll_area(self.pulse_page), "脉冲")
        self.tabs.addTab(scroll_area(self.user_page), "用户波形")
        self.tabs.addTab(scroll_area(self.sys_page), "系统")
        self.setCentralWidget(self.tabs)

        # 信号连接
        self.worker.status_ready.connect(self.on_status)
        self.worker.ack.connect(self.on_ack)
        self.worker.connected.connect(self.connbar.on_connected)
        self.worker.error.connect(self.connbar.on_error)
        self.worker.log.connect(self.statusBar().showMessage)
        self.worker.upload_progress.connect(self.on_upload_progress)
        self.worker.upload_done.connect(self.on_upload_done)

        self.statusBar().showMessage("就绪")

    @pyqtSlot(dict)
    def on_status(self, s: dict):
        self.connbar.on_status(s)
        self.std_page.sync(s)
        self.mod_page.sync(s)
        self.scan_page.sync(s)
        self.harmonic_page.sync(s)
        self.pulse_page.sync(s)
        self.user_page.sync(s)
        self.sys_page.sync(s)

    @pyqtSlot(str)
    def on_ack(self, msg):
        self.statusBar().showMessage(f"设备应答: {msg}", 2000)

    @pyqtSlot(int, int, float)
    def on_upload_progress(self, sent, total, remain):
        pct = int(sent * 1000 / total) if total else 0
        self.user_page.progress.setValue(pct)
        self.statusBar().showMessage(f"上传中... {sent/1024:.0f}KB / {total/1024:.0f}KB  剩余约 {remain:.0f}s")

    @pyqtSlot(int)
    def on_upload_done(self, group):
        self.user_page.progress.setValue(1000)
        self.statusBar().showMessage(f"用户波形组 {group} 上传完成", 5000)


def main():
    app = QApplication(sys.argv)
    app.setFont(QFont("Microsoft YaHei UI", 10))
    win = MainWindow()
    win.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()