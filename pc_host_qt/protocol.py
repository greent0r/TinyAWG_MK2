# -*- coding: utf-8 -*-
"""设备串口协议客户端：连接管理、命令收发、状态解析、用户波形上传。"""
import queue
import threading
import time

from PyQt6.QtCore import QThread, pyqtSignal

try:
    import serial
except ImportError:
    serial = None

# 用户波形上传（原始流式：无帧/无CRC/无ACK，直接连发1MB int16数据，速率=串口数据率）
USER_WAVE_POINTS = 1 << 19          # 512K 点/组
UPLOAD_TOTAL_BYTES = USER_WAVE_POINTS * 2  # 1MB
UPLOAD_STREAM_CHUNK = 16384          # 上位机每片写入字节数（避免一次写1MB阻塞）

WAVE_NAMES = ["正弦波", "方波", "三角波", "直流", "锯齿波", "噪声", "阶跃",
              "全波整流", "半波整流", "衰减正弦", "ECG", "Sinc", "指数衰减", "阶梯波",
              "梯形波", "升余弦脉冲", "高斯脉冲", "双脉冲", "指数上升", "洛伦兹脉冲", "随机脉冲", "平滑阶跃",
              "正弦加噪", "方波加噪", "抛物波", "三次波", "指数波", "升余弦方波", "圆角三角波",
              "矩形脉冲", "单极性方波", "PRBS", "巴克码", "曼彻斯特码"]

WAVE_PARAMS = {
    0: [], 1: ["duty"], 2: ["sym"], 3: [], 4: ["rising"], 5: [], 6: [],
    7: [], 8: [], 9: ["cycles", "damp"], 10: ["hr"], 11: ["zc"], 12: ["decay"],
    13: ["rising", "steps"], 14: ["trise"], 15: ["rcw"], 16: ["gaussw"], 17: ["dpw"],
    18: ["erise"], 19: ["lw"], 20: ["rpulses"], 21: ["ssteep"],
    22: ["sna"], 23: ["qna"], 24: [], 25: [], 26: ["ewave"], 27: ["rsq"],
    28: ["rtr"], 29: ["rw"], 30: ["uduty"], 31: ["prbs"], 32: [], 33: [],
}

# 波形专属参数显示元信息 key -> (标签, 单位, 步进, 小数位, 最小值, 最大值)
PARAM_INFO = {
    "duty":   ("占空比", "%", 0.01, 2, 0.0, 1.0),
    "sym":    ("对称度", "%", 0.01, 2, 0.0, 1.0),
    "rising": ("方向", "", 1, 0, 0, 1),
    "zc":     ("零点数", "", 1, 0, 1, 100),
    "decay":  ("衰减率", "%", 0.01, 2, 0.0, 1.0),
    "hr":     ("心跳", "次/分", 1, 0, 40, 180),
    "steps":  ("阶数", "", 1, 0, 2, 1000),
    "cycles": ("周期数", "", 1, 0, 1, 200),
    "damp":   ("阻尼", "", 0.01, 2, 0.0, 10.0),
    "trise":  ("升沿", "%", 0.01, 2, 0.05, 0.45),
    "rcw":    ("脉宽", "%", 0.01, 2, 0.05, 0.95),
    "gaussw": ("宽度", "%", 0.01, 2, 0.02, 0.5),
    "dpw":    ("脉宽", "%", 0.01, 2, 0.01, 0.2),
    "erise":  ("速率", "%", 0.01, 2, 0.0, 1.0),
    "lw":     ("宽度", "%", 0.01, 2, 0.005, 0.2),
    "rpulses":("脉数", "", 1, 0, 1, 200),
    "ssteep": ("陡度", "%", 0.01, 2, 0.0, 1.0),
    "sna":    ("噪幅", "%", 0.01, 2, 0.0, 1.0),
    "qna":    ("噪幅", "%", 0.01, 2, 0.0, 1.0),
    "ewave":  ("速率", "%", 0.01, 2, 0.0, 1.0),
    "rsq":    ("圆滑", "%", 0.01, 2, 0.02, 0.5),
    "rtr":    ("圆滑", "%", 0.01, 2, 0.02, 0.5),
    "rw":     ("脉宽", "%", 0.01, 2, 0.02, 0.5),
    "uduty":  ("占空比", "%", 0.01, 2, 0.0, 1.0),
    "prbs":   ("阶数", "", 1, 0, 3, 16),
}

MOD_PARAMS = {0: ["m_depth"], 1: ["m_dev"], 2: ["m_index"]}
DEPTH_NAMES = ["32K", "128K", "256K", "512K", "1M", "2M", "4M", "8M", "16M", "32M"]


def crc8(data: bytes) -> int:
    crc = 0
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = ((crc << 1) ^ 0x07) & 0xFF if crc & 0x80 else (crc << 1) & 0xFF
    return crc


def parse_status(line: str) -> dict:
    """解析 STATUS key=val 行 -> dict(str->str)。"""
    d = {}
    parts = line.split()
    for part in parts:
        if "=" in part:
            k, v = part.split("=", 1)
            d[k] = v
    return d


class ProtocolWorker(QThread):
    """串口工作线程：命令队列 + 连续接收解析 + 波形上传。"""

    connected = pyqtSignal(bool)
    status_ready = pyqtSignal(dict)
    ack = pyqtSignal(str)
    upload_progress = pyqtSignal(int, int, float)  # 已传字节, 总字节, 剩余秒估
    upload_done = pyqtSignal(int)                  # 组号
    upload_aborted = pyqtSignal(str)
    log = pyqtSignal(str)
    error = pyqtSignal(str)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.ser = None
        self.tx_queue = queue.Queue()
        self._active = False
        self._lock = threading.Lock()
        self._rxbuf = b""
        self._last_status_time = 0.0
        self.state = {}   # 最新一次 STATUS 解析结果（UI 读取用）

    # ---------------- 连接 ----------------
    def open_serial(self, port: str, baud: int) -> bool:
        try:
            self.ser = serial.Serial(port, baud, timeout=0.05, write_timeout=2)
        except Exception as e:
            self.error.emit(f"串口打开失败: {e}")
            return False
        self._active = True
        self.start()
        self.connected.emit(True)
        self.log.emit(f"已连接 {port} @ {baud}")
        return True

    def close(self):
        self._active = False
        if self.ser:
            try:
                self.ser.close()
            except Exception:
                pass
            self.ser = None
        self.connected.emit(False)
        self.log.emit("连接已断开")

    def is_open(self) -> bool:
        return self.ser is not None and self.ser.is_open

    # ---------------- 命令 ----------------
    def send_text(self, cmd: str):
        if self.is_open():
            self.tx_queue.put(("text", cmd))
            self.log.emit(f">> {cmd.strip()}")

    def query(self):
        self.send_text("G")

    def set_params(self, **kwargs):
        parts = [f"{k}={v}" for k, v in kwargs.items() if v is not None]
        if parts:
            self.send_text("S " + " ".join(parts))

    def set_dac(self, volts):
        s = ",".join(f"{v:.4f}" for v in volts)
        self.send_text("D " + s)

    # ---------------- 线程主循环 ----------------
    def run(self):
        while self._active:
            try:
                item = self.tx_queue.get(timeout=0.05)
                if item[0] == "text":
                    cmd = item[1]
                    if not cmd.endswith("\n"):   # 固件按 \n 分帧，必须带换行
                        cmd = cmd + "\n"
                    self._send_raw(cmd)
                elif item[0] == "upload":
                    self._upload(item[1], item[2])
            except queue.Empty:
                pass
            self._drain_rx()
        self._drain_rx()

    def _send_raw(self, text: str):
        if not self.is_open():
            return
        try:
            # 防御：非ASCII字符替换为'?'，避免单条坏命令导致整线程崩溃
            self.ser.write(text.encode("ascii", errors="replace"))
            self.ser.flush()
        except Exception as e:
            self.error.emit(f"发送失败: {e}")

    def _readline_timeout(self, timeout: float) -> str:
        """阻塞读取一行（以 \\n 结尾），超时返回空串。"""
        deadline = time.time() + timeout
        buf = b""
        while time.time() < deadline:
            if not self.is_open():
                return ""
            try:
                data = self.ser.read(1024)
            except Exception:
                return ""
            if data:
                buf += data
                if b"\n" in buf:
                    line, rest = buf.split(b"\n", 1)
                    if rest:
                        # 剩余字节暂存回线程缓冲
                        self._rxbuf = rest + self._rxbuf
                    return line.decode("ascii", errors="replace").strip()
            else:
                time.sleep(0.001)
        return ""

    def _drain_rx(self):
        """非阻塞读取并把完整行分发。"""
        if not self.is_open():
            return
        try:
            data = self.ser.read(4096)
        except Exception:
            return
        if not data:
            return
        self._rxbuf += data
        while b"\n" in self._rxbuf:
            line, self._rxbuf = self._rxbuf.split(b"\n", 1)
            line = line.decode("ascii", errors="replace").strip()
            if not line:
                continue
            if line.startswith("STATUS "):
                parsed = parse_status(line[7:])
                self.state = parsed
                self.status_ready.emit(parsed)
                self._last_status_time = time.time()
            elif line == "OK":
                self.ack.emit("OK")
            elif line == "ERR":
                self.ack.emit("ERR")
            elif line == "OVR":
                self.log.emit("! 设备接收缓冲溢出")
            else:
                self.log.emit(f"<< {line}")

    # ---------------- 用户波形上传 ----------------
    def upload_wave(self, group: int, payload: bytes, meta: str = ""):
        """上传 int16 小端 2MB 数据到指定组。后台线程执行，进度信号见 upload_progress。"""
        if not self.is_open():
            self.error.emit("未连接设备")
            return
        if len(payload) != UPLOAD_TOTAL_BYTES:
            self.error.emit(f"数据长度错误: {len(payload)} != {UPLOAD_TOTAL_BYTES}")
            return
        self.tx_queue.put(("upload", group, payload))

    def _upload(self, group: int, payload: bytes):
        """原始流式上传：U<g> -> READY -> 连续发送1MB -> DONE。无确认/无校验，速率=波特率。"""
        if not self.is_open():
            return
        self.log.emit(f"上传用户波形 -> 组 {group}（{len(payload) // 1024} KB，流式）")

        # 1. 发送开始命令
        self._send_raw(f"U{group}\n")
        resp = self._readline_timeout(2.0)
        if resp != "READY":
            self.error.emit(f"设备未就绪: {resp or '超时'}")
            return

        # 2. 连续流式发送（无任何等待/校验）
        total = len(payload)
        sent = 0
        t0 = time.time()
        chunk = UPLOAD_STREAM_CHUNK
        while sent < total:
            if not self.is_open():
                return
            try:
                self.ser.write(payload[sent:sent + chunk])
                self.ser.flush()
            except Exception as e:
                self.error.emit(f"上传写入失败: {e}")
                return
            sent += chunk
            elapsed = time.time() - t0
            speed = sent / elapsed if elapsed > 0 else 0
            remain = (total - sent) / speed if speed > 0 else 0
            self.upload_progress.emit(min(sent, total), total, remain)

        # 3. 等待设备收满后回 DONE
        resp = self._readline_timeout(5.0)
        if resp == "DONE":
            self.upload_done.emit(group)
            self.log.emit(f"用户波形组 {group} 上传完成")
        else:
            self.error.emit(f"上传结束未确认: {resp or '超时'}")

    # ---------------- 便捷 ----------------
    def apply_wave(self, ch, wave_idx, **params):
        """组合发送标准波形及其专属参数。"""
        base = {"ch": ch, "wave": wave_idx}
        base.update(params)
        self.set_params(**base)

    def apply_mod(self, ch, enable, mode, **params):
        base = {"ch": ch, "m_en": 1 if enable else 0, "m_mode": mode}
        base.update(params)
        self.set_params(**base)

    def apply_scan(self, ch, **params):
        self.set_params(ch=ch, **params)

    def apply_harmonic(self, ch, enable, count, idx, amps, phases):
        p = {"ch": ch, "h_en": 1 if enable else 0, "h_count": count, "h_idx": idx}
        for i, a in enumerate(amps, 1):
            p[f"h_amp{i}"] = f"{a:.4f}"
        for i, ph in enumerate(phases, 1):
            p[f"h_ph{i}"] = f"{ph:.4f}"
        self.set_params(**p)

    def apply_burst(self, ch, enable, cycles, phase, delay, trigger=False):
        p = {"ch": ch, "b_en": 1 if enable else 0,
             "b_cycles": int(cycles), "b_phase": f"{phase:.4f}",
             "b_delay": int(delay)}
        if trigger:
            p["b_trig"] = 1
        self.set_params(**p)