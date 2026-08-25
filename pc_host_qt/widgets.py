# -*- coding: utf-8 -*-
"""工业风可复用控件：带标签数值框、状态灯、分组面板、滚动区。"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from PyQt6.QtCore import Qt, pyqtSignal
from PyQt6.QtGui import QColor
from PyQt6.QtWidgets import (
    QWidget, QLabel, QDoubleSpinBox, QSpinBox, QComboBox, QCheckBox,
    QPushButton, QFrame, QHBoxLayout, QVBoxLayout, QGridLayout,
    QScrollArea, QSizePolicy, QGroupBox,
)

from pc_host_qt.theme import C_GREEN, C_AMBER, C_RED, C_TEXT_MUT, C_TEXT, C_CYAN


class ValueBox(QWidget):
    """带标签与单位的数值输入框（浮点/整数），值变化时发出 value_changed。"""

    value_changed = pyqtSignal(str, float)

    def __init__(self, label, unit="", decimals=3, step=0.1, lo=-1e9, hi=1e9, value=0.0, integer=False, parent=None):
        super().__init__(parent)
        lay = QHBoxLayout(self)
        lay.setContentsMargins(0, 0, 0, 0)
        lay.setSpacing(6)
        self.lab = QLabel(label)
        self.lab.setFixedWidth(78)
        self.lab.setStyleSheet(f"color: {C_TEXT_MUT}; font-weight: bold;")
        lay.addWidget(self.lab)

        if integer:
            self.spin = QSpinBox()
            self.spin.setRange(int(lo), int(hi))
            self.spin.setValue(int(value))
            self.spin.setSingleStep(max(1, int(step)))
        else:
            self.spin = QDoubleSpinBox()
            self.spin.setDecimals(decimals)
            self.spin.setRange(lo, hi)
            self.spin.setValue(float(value))
            self.spin.setSingleStep(step)
        self.spin.setKeyboardTracking(False)
        lay.addWidget(self.spin, 1)

        self.unit = QLabel(unit)
        self.unit.setFixedWidth(48)
        self.unit.setStyleSheet(f"color: {C_TEXT_MUT};")
        lay.addWidget(self.unit)

        self._key = None
        self.spin.valueChanged.connect(self._emit)

    def _emit(self, v):
        self.value_changed.emit(self._key or self.lab.text(), float(v))

    def set_key(self, key):
        self._key = key

    def set_value(self, v, block=False):
        if block:
            self.spin.blockSignals(True)
        try:
            self.spin.setValue(float(v))
        finally:
            if block:
                self.spin.blockSignals(False)

    def value(self):
        return self.spin.value()


class StatusLED(QLabel):
    """状态指示灯：绿/琥珀/红 + 文字。"""

    def __init__(self, text="待机", color=C_TEXT_MUT, parent=None):
        super().__init__(parent)
        self.setStyleSheet(f"color: {color}; font-weight: bold;")
        self.setText(f"● {text}")

    def set_status(self, text, color):
        self.setText(f"● {text}")
        self.setStyleSheet(f"color: {color}; font-weight: bold;")


def panel(title=None, parent=None) -> QGroupBox:
    g = QGroupBox(title or "", parent)
    return g


def button(text, accent=False, danger=False, amber=False) -> QPushButton:
    b = QPushButton(text)
    if accent:
        b.setProperty("accent", "1")
    if danger:
        b.setProperty("danger", "1")
    if amber:
        b.setProperty("amber", "1")
    return b


def vbox(parent=None, *items, spacing=8, margins=(8, 8, 8, 8)) -> QVBoxLayout:
    lay = QVBoxLayout(parent)
    lay.setSpacing(spacing)
    lay.setContentsMargins(*margins)
    for w in items:
        if isinstance(w, QWidget):
            lay.addWidget(w)
        else:
            lay.addLayout(w)
    return lay


def hbox(parent=None, *items, spacing=8) -> QHBoxLayout:
    lay = QHBoxLayout(parent)
    lay.setSpacing(spacing)
    for w in items:
        if isinstance(w, QWidget):
            lay.addWidget(w)
        else:
            lay.addLayout(w)
    return lay


def scroll_area(widget: QWidget, min_w=700) -> QScrollArea:
    sa = QScrollArea()
    sa.setWidgetResizable(True)
    sa.setWidget(widget)
    widget.setMinimumWidth(min_w)
    return sa


def grid(widgets, cols=2, spacing=10) -> QGridLayout:
    g = QGridLayout()
    g.setSpacing(spacing)
    for i, w in enumerate(widgets):
        g.addWidget(w, i // cols, i % cols)
    return g


def hline() -> QFrame:
    f = QFrame()
    f.setFrameShape(QFrame.Shape.HLine)
    f.setStyleSheet("color: #2a3038; background: #2a3038;")
    return f


class SectionLabel(QLabel):
    def __init__(self, text, parent=None):
        super().__init__(text, parent)
        self.setStyleSheet(
            f"color: {C_CYAN}; font-size: 13px; font-weight: bold; letter-spacing: 2px;"
        )