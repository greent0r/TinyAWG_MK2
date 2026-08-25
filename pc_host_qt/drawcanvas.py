# -*- coding: utf-8 -*-
"""手绘波形画布：鼠标绘制/编辑波形，输出 (0..1, -1..1) 归一化点列。"""
import os
import sys
import math

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import numpy as np
from PyQt6.QtCore import Qt, QPointF, QRectF, pyqtSignal
from PyQt6.QtGui import QPainter, QPen, QColor, QPolygonF
from PyQt6.QtWidgets import QWidget

from pc_host_qt.theme import C_BG_INPUT, C_BORDER, C_CYAN, C_TEXT, C_TEXT_MUT, C_GOLD, C_AMBER


class WaveCanvas(QWidget):
    """可绘制波形画布。

    交互：左键拖动画线；右键清除最近一笔；中键/按钮清除全部。
    数据：points 为 float 列表，x∈[0,1] 归一化到画布宽度，y∈[-1,1]。
    """

    changed = pyqtSignal()
    status = pyqtSignal(str)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.points = [(0.0, 0.0), (1.0, 0.0)]  # (x_norm 0..1, y_norm -1..1)
        self._drawing = False
        self._last = None
        self.setMinimumSize(320, 200)
        self.setFocusPolicy(Qt.FocusPolicy.StrongFocus)

    # ---------------- 数据操作 ----------------
    def set_points(self, pts):
        self.points = list(pts)
        self.update()
        self.changed.emit()

    def clear(self):
        self.points = [(0.0, 0.0), (1.0, 0.0)]
        self.update()
        self.changed.emit()
        self.status.emit("画布已清空")

    def undo(self):
        if len(self.points) > 2:
            self.points.pop()
            self.update()
            self.changed.emit()

    def smooth(self, window=9):
        if len(self.points) < 3:
            return
        xs = np.array([p[0] for p in self.points])
        ys = np.array([p[1] for p in self.points])
        k = max(3, window)
        kernel = np.ones(k) / k
        ys = np.convolve(ys, kernel, mode="same")
        # 保持首尾不动
        ys[0], ys[-1] = self.points[0][1], self.points[-1][1]
        self.points = list(zip(xs.tolist(), ys.tolist()))
        self.update()
        self.changed.emit()
        self.status.emit(f"已平滑（窗口 {k}）")

    def normalize(self):
        ys = np.array([p[1] for p in self.points])
        mn, mx = float(np.min(ys)), float(np.max(ys))
        if mx - mn < 1e-9:
            return
        ys = (ys - mn) / (mx - mn) * 2.0 - 1.0
        self.points = list(zip([p[0] for p in self.points], ys.tolist()))
        self.update()
        self.changed.emit()
        self.status.emit("幅度已归一化到 ±1")

    def invert(self):
        self.points = [(x, -y) for x, y in self.points]
        self.update()
        self.changed.emit()
        self.status.emit("波形已取反")

    # ---------------- 渲染 ----------------
    def paintEvent(self, event):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing, True)
        w, h = self.width(), self.height()

        # 背景
        p.fillRect(0, 0, w, h, QColor(C_BG_INPUT))
        # 网格（细线 20px 网格 + 中轴线）
        pen = QPen(QColor("#232b35"), 1)
        p.setPen(pen)
        for x in range(0, w, 20):
            p.drawLine(x, 0, x, h)
        for y in range(0, h, 20):
            p.drawLine(0, y, w, y)
        # 中轴 + 1/2 幅度参考线
        mid = h / 2
        pen = QPen(QColor(C_BORDER), 1)
        p.setPen(pen)
        p.drawLine(0, int(mid), w, int(mid))
        p.drawLine(0, int(h * 0.25), w, int(h * 0.25))
        p.drawLine(0, int(h * 0.75), w, int(h * 0.75))

        # 边框
        p.setPen(QPen(QColor(C_BORDER), 1))
        p.drawRect(0, 0, w - 1, h - 1)

        # 波形
        if len(self.points) >= 2:
            poly = QPolygonF()
            for x, y in self.points:
                px = x * (w - 2)
                py = mid - y * (h / 2 - 4)
                poly.append(QPointF(px, py))
            pen = QPen(QColor(C_CYAN), 2)
            p.setPen(pen)
            p.drawPolyline(poly)
            # 端点
            pen.setColor(QColor(C_GOLD))
            pen.setWidth(4)
            p.setPen(pen)
            for i in (0, len(self.points) - 1):
                px, py = poly[i].x(), poly[i].y()
                p.drawPoint(int(px), int(py))

        p.end()

    # ---------------- 鼠标交互 ----------------
    def _to_norm(self, pos):
        w, h = self.width(), self.height()
        x = max(0.0, min(1.0, pos.x() / max(1, w)))
        y = (pos.y() - h / 2) / max(1.0, h / 2 - 4)
        y = max(-1.0, min(1.0, -y))  # 屏幕 y 向下为正，翻转
        return x, y

    def mousePressEvent(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            self._drawing = True
            self._last = self._to_norm(event.position())
            self.points.append(self._last)
            self.update()
            self.changed.emit()
        elif event.button() == Qt.MouseButton.RightButton:
            self.undo()
            self.status.emit("撤销上一点")

    def mouseMoveEvent(self, event):
        if self._drawing:
            x, y = self._to_norm(event.position())
            if self._last:
                dx = abs(x - self._last[0])
                if dx >= 0.002:  # 避免过密点
                    self.points.append((x, y))
                    self._last = (x, y)
            self.update()
            self.changed.emit()

    def mouseReleaseEvent(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            self._drawing = False
            self._last = None
            if self.points:
                self.points[0] = (0.0, self.points[0][1])
                self.points[-1] = (1.0, self.points[-1][1])
            self.update()
            self.changed.emit()

    def keyPressEvent(self, event):
        key = event.key()
        if key == Qt.Key.Key_C:
            self.clear()
        elif key == Qt.Key.Key_Z:
            self.undo()
        elif key == Qt.Key.Key_S:
            self.smooth()
        elif key == Qt.Key.Key_N:
            self.normalize()
        elif key == Qt.Key.Key_I:
            self.invert()


def points_to_1m(points) -> np.ndarray:
    """画布点列 -> 512K 点 float 数组（y 值），再交给 waveform.resample_to_1m 处理。"""
    if not points or len(points) < 2:
        return np.zeros(1 << 20, dtype=np.float64)
    pts = sorted(points, key=lambda p: p[0])
    xs = np.array([p[0] for p in pts])
    ys = np.array([p[1] for p in pts])
    n = 1 << 20
    x_out = np.linspace(0.0, 1.0, n)
    return np.interp(x_out, xs, ys)