# -*- coding: utf-8 -*-
"""波形数据模型：绘制/导入数据 -> 统一重采样到 1M 点 int16 -> 上传设备。"""
import os
import struct

import numpy as np

SAMPLE_MAX = 32767.0
TARGET_POINTS = 1 << 19   # 512K 点/组（用户波形单组容量）

# 支持的文件扩展名
EXT_WAV = ".wav"
EXT_CSV = ".csv"
EXT_TXT = ".txt"
EXT_BIN = ".bin"
EXT_RAW = ".raw"
SUPPORTED_EXTS = (EXT_WAV, EXT_CSV, EXT_TXT, EXT_BIN, EXT_RAW)


def resample_to_1m(data: np.ndarray, normalize=True) -> np.ndarray:
    """将任意长度波形重采样到 1M 点，输出 int16 全幅有符号数据。

    - 点数不足：线性插值补足（拉长）。
    - 点数超出：线性抽样到 1M（压缩），必要时先做抗混叠均值滤波。
    - 数据范围：默认归一化到 ±32767（可用 normalize=False 保留相对幅度）。
    """
    data = np.asarray(data, dtype=np.float64).reshape(-1)
    if data.size == 0:
        raise ValueError("波形数据为空")

    # 超采样(点数 > 1M) 时先按比例均值滤波（抗混叠），再线性重采样
    if data.size > TARGET_POINTS:
        ratio = data.size / TARGET_POINTS
        if ratio >= 3:
            win = int(ratio)
            trim = data.size - (data.size % win)
            data = data[:trim].reshape(-1, win).mean(axis=1)

    x_src = np.linspace(0.0, 1.0, data.size)
    x_dst = np.linspace(0.0, 1.0, TARGET_POINTS)
    out = np.interp(x_dst, x_src, data)

    if normalize:
        mn, mx = float(np.min(out)), float(np.max(out))
        span = mx - mn
        if span < 1e-9:
            out = np.zeros_like(out)  # 平直信号保持为0
        else:
            out = (out - mn) / span * 2.0 - 1.0   # 归一化到 -1..1
    out = np.clip(out, -1.0, 1.0) * SAMPLE_MAX
    return out.astype(np.int16)


def import_file(path: str) -> np.ndarray:
    """导入波形文件 -> float64 数组（原始幅值）。"""
    ext = os.path.splitext(path)[1].lower()
    if ext == EXT_WAV:
        return _import_wav(path)
    if ext in (EXT_CSV, EXT_TXT):
        return _import_text(path)
    if ext in (EXT_BIN, EXT_RAW):
        return _import_bin(path)
    raise ValueError(f"不支持的文件类型: {ext}")


def _import_wav(path: str) -> np.ndarray:
    import wave as wave_module

    with wave_module.open(path, "rb") as w:
        nch = w.getnchannels()
        sw = w.getsampwidth()
        nf = w.getnframes()
        raw = w.readframes(nf)
    if sw == 2:
        fmt = f"<{nch * nf}h"
        arr = np.frombuffer(raw, dtype=np.int16)
    elif sw == 1:
        arr = np.frombuffer(raw, dtype=np.uint8).astype(np.float64) - 128.0
        arr = arr.astype(np.int16) << 8
    elif sw == 4:
        arr = np.frombuffer(raw, dtype=np.int32).astype(np.float64) / 65536.0
        arr = arr.astype(np.int16)
    else:
        raise ValueError("不支持的 WAV 位深")
    if nch > 1:  # 多声道取平均
        arr = arr.reshape(-1, nch).mean(axis=1)
    return arr.astype(np.float64)


def _import_text(path: str) -> np.ndarray:
    vals = []
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith(("#", ";", "//")):
                continue
            for tok in line.replace(",", " ").replace(";", " ").split():
                try:
                    vals.append(float(tok))
                except ValueError:
                    continue
    if not vals:
        raise ValueError("文本文件中没有可用的数值")
    return np.asarray(vals, dtype=np.float64)


def _import_bin(path: str) -> np.ndarray:
    data = open(path, "rb").read()
    # 优先按 int16 小端解释；若字节数恰好为4的倍数且首字节非0，尝试 float32
    if len(data) % 2 != 0:
        raise ValueError("二进制文件字节数必须为偶数")
    arr16 = np.frombuffer(data, dtype="<i2").astype(np.float64)
    if len(data) % 4 == 0 and len(data) >= 16:
        arr32 = np.frombuffer(data, dtype="<f4").astype(np.float64)
        # 启发式判断：float32 数据通常在合理动态范围
        if np.all(np.abs(arr32) < 1e6) and np.any(np.abs(arr32) > 1e-6):
            return arr32
    return arr16


def export_file(path: str, samples: np.ndarray):
    """导出 1M 点 int16 数据为 wav/csv/bin。samples 为 int16 数组。"""
    ext = os.path.splitext(path)[1].lower()
    arr16 = np.asarray(samples, dtype=np.int16)
    if ext == EXT_WAV:
        import wave as wave_module

        with wave_module.open(path, "wb") as w:
            w.setnchannels(1)
            w.setsampwidth(2)
            w.setframerate(200000)
            w.writeframes(arr16.tobytes())
    elif ext in (EXT_CSV, EXT_TXT):
        with open(path, "w", encoding="utf-8") as f:
            for v in arr16:
                f.write(f"{v}\n")
    elif ext in (EXT_BIN, EXT_RAW):
        with open(path, "wb") as f:
            f.write(arr16.tobytes())
    else:
        raise ValueError(f"不支持的导出类型: {ext}")


def apply_ops(points, invert=False, offset=0.0, scale=1.0):
    """对 1M int16 数据做后处理（取反/偏置/缩放）。"""
    out = np.asarray(points, dtype=np.float64)
    if invert:
        out = -out
    out = out + offset * SAMPLE_MAX
    out = out * scale
    return np.clip(out, -SAMPLE_MAX, SAMPLE_MAX).astype(np.int16)


def render_wave(idx: int, p: dict, n=512) -> np.ndarray:
    """本地渲染标准波形预览（复刻设备端 user_dds.c 算法），返回 float64 数组 [-1,1]。"""
    duty = float(p.get("duty", 0.5))
    sym = float(p.get("sym", 0.5))
    rising = int(p.get("rising", 0))
    zc = int(p.get("zc", 7))
    decay = float(p.get("decay", 0.5))
    hr = int(p.get("hr", 90))
    steps = int(p.get("steps", 25))
    cycles = int(p.get("cycles", 5))
    damp = float(p.get("damp", 2.0))
    trise = float(p.get("trise", 0.25))
    rcw = float(p.get("rcw", 0.5))
    gaussw = float(p.get("gaussw", 0.15))
    dpw = float(p.get("dpw", 0.08))
    erise = float(p.get("erise", 0.5))
    lw = float(p.get("lw", 0.05))
    rpulses = int(p.get("rpulses", 20))
    ssteep = float(p.get("ssteep", 0.5))
    sna = float(p.get("sna", 0.3))
    qna = float(p.get("qna", 0.3))
    ewave = float(p.get("ewave", 0.5))
    rsq = float(p.get("rsq", 0.25))
    rtr = float(p.get("rtr", 0.25))
    rw = float(p.get("rw", 0.25))
    uduty = float(p.get("uduty", 0.5))
    prbs = int(p.get("prbs", 7))

    i = np.arange(n)
    x = i / n
    if idx == 0:  # 正弦
        return np.sin(2 * np.pi * i / n)
    if idx == 1:  # 方波
        return np.where(i < n * duty, 1.0, -1.0)
    if idx == 2:  # 三角波
        split = n * sym
        out = np.where(i < split, 2.0 * i / split - 1.0, 1.0 - 2.0 * (i - split) / (n - split))
        return np.clip(out, -1.0, 1.0)
    if idx == 3:  # 直流
        return np.zeros(n)
    if idx == 4:  # 锯齿波
        return (2.0 * i / n - 1.0) if rising else (1.0 - 2.0 * i / n)
    if idx == 5:  # 噪声
        rng = np.random.default_rng(0)
        return rng.uniform(-1.0, 1.0, n)
    if idx == 6:  # 阶跃
        out = np.zeros(n)
        out[0] = 1.0
        return out
    if idx == 7:  # 全波整流
        return np.abs(np.sin(2 * np.pi * i / n))
    if idx == 8:  # 半波整流
        return np.maximum(np.sin(2 * np.pi * i / n), 0.0)
    if idx == 9:  # 衰减正弦
        return np.exp(-damp * x) * np.sin(2 * np.pi * cycles * i / n)
    if idx == 10:  # ECG
        phase = (i % (n / max(1, round(hr / 60))) / (n / max(1, round(hr / 60))))
        pv = np.zeros(n)
        for idx2 in range(n):
            ph = phase[idx2]
            v = 0.0
            if 0.05 <= ph < 0.15:
                pp = (ph - 0.05) / 0.1 - 0.5
                v += 0.25 * np.exp(-50 * pp * pp)
            if 0.2 <= ph < 0.3:
                qp = (ph - 0.2) / 0.1 - 0.5
                v += np.exp(-100 * qp * qp)
                if ph < 0.225: v -= 0.2
                if ph > 0.275: v -= 0.2
            if 0.4 <= ph < 0.6:
                tp = (ph - 0.4) / 0.2 - 0.5
                v += 0.3 * np.exp(-25 * tp * tp)
            if (0.15 <= ph < 0.2) or (0.3 <= ph < 0.4):
                v -= 0.05
            pv[idx2] = v
        return pv / 1.2
    if idx == 11:  # sinc
        t = (2 * zc + 1) * (i / n) - zc - 0.5
        return np.sinc(t)  # numpy sinc(x)=sin(pi x)/(pi x)
    if idx == 12:  # 指数衰减
        return np.exp(-10 * decay * x)
    if idx == 13:  # 阶梯波
        idx3 = np.clip((i * steps // n), 0, steps - 1)
        return (-1.0 + 2.0 * idx3 / max(1, steps - 1)) if rising else (1.0 - 2.0 * idx3 / max(1, steps - 1))
    if idx == 14:  # 梯形波
        rise, fall = trise, 1.0 - trise
        out = np.where(x < rise, -1.0 + 2.0 * x / rise, np.where(x < fall, 1.0, 1.0 - 2.0 * (x - fall) / trise))
        return out
    if idx == 15:  # 升余弦脉冲
        w = rcw * 2 * np.pi
        return np.where(i * 2 * np.pi / n < w, 0.5 * (1 - np.cos(2 * np.pi * (i * 2 * np.pi / n) / w)), 0.0)
    if idx == 16:  # 高斯脉冲
        return np.exp(-((x - 0.5) ** 2) / (gaussw ** 2))
    if idx == 17:  # 双脉冲
        out = np.zeros(n)
        out[x < dpw] = 1.0
        mask = (x >= 0.25) & (x < 0.25 + dpw)
        out[mask] = -1.0
        return out
    if idx == 18:  # 指数上升
        return 1.0 - np.exp(-10 * erise * x)
    if idx == 19:  # 洛伦兹脉冲
        t = x - 0.5
        return 1.0 / (1.0 + (t / lw) ** 2)
    if idx == 20:  # 随机脉冲
        out = np.zeros(n)
        rng = np.random.default_rng(2026)
        for _ in range(rpulses):
            pos = int(rng.random() * n)
            out[pos] = 1.0 if rng.random() > 0.5 else -1.0
        return out
    if idx == 21:  # 平滑阶跃
        return 0.5 + np.arctan(ssteep * 60.0 * (x - 0.5)) / np.pi
    if idx == 22:  # 正弦加噪
        rng = np.random.default_rng(100)
        return (np.sin(2 * np.pi * i / n) + sna * rng.uniform(-1, 1, n)) / (1 + sna)
    if idx == 23:  # 方波加噪
        rng = np.random.default_rng(100)
        s = np.where(i < n / 2, 1.0, -1.0)
        return (s + qna * rng.uniform(-1, 1, n)) / (1 + qna)
    if idx == 24:  # 抛物波
        return 8.0 * (x - 0.5) ** 2 - 1.0
    if idx == 25:  # 三次波
        t = np.where(x < 0.5, 2 * x, 2 - 2 * x)
        return (2 * t - 1) ** 3
    if idx == 26:  # 指数波
        c = 1 + ewave * 9
        return (np.exp(c * x) - 1) / (np.exp(c) - 1) * 2 - 1
    if idx == 27:  # 升余弦方波
        q = np.mod(2 * x, 2.0)
        edge = rsq * 0.5
        out = np.where(q < edge, -np.cos(q / edge * np.pi), np.where(q < 0.5, 1.0,
              np.where(q < 0.5 + edge, np.cos((q - 0.5) / edge * np.pi), np.where(q < 1.5, -1.0,
              np.where(q < 1.5 + edge, -np.cos((q - 1.5) / edge * np.pi), 1.0)))))
        return out
    if idx == 28:  # 圆角三角波
        k = 1.0 / (rtr * 2.0)
        t = np.where(x < 0.5, 2 * x, 2 - 2 * x)
        return np.tanh(k * (2 * t - 1)) / np.tanh(k)
    if idx == 29:  # 矩形脉冲
        return np.where(x < rw, 1.0, 0.0)
    if idx == 30:  # 单极性方波
        return np.where(x < uduty, 1.0, 0.0)
    if idx == 31:  # PRBS
        taps = [0x5, 0x9, 0x12, 0x21, 0x41, 0x8E, 0x108, 0x204,
                0x402, 0x829, 0x100D, 0x2015, 0x4022, 0xB400]
        mask = taps[prbs - 3]
        lfsr = 1
        out = np.zeros(n)
        for j in range(n):
            bit = lfsr & 1
            out[j] = 1.0 if bit else -1.0
            lfsr = (lfsr >> 1) ^ mask if bit else lfsr >> 1
        return out
    if idx == 32:  # 巴克码
        barker = [1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1]
        return np.array([barker[min(len(barker) - 1, (j * 13 // n))] for j in range(n)], dtype=float)
    if idx == 33:  # 曼彻斯特码
        out = np.zeros(n)
        data = 0xA5
        for j in range(n):
            pos = j / n * 8
            bit_idx = min(7, int(pos))
            bit = (data >> (7 - bit_idx)) & 1
            sub = pos - bit_idx
            out[j] = -1.0 if (sub < 0.5 and bit) or (sub >= 0.5 and not bit) else 1.0
        return out
    return np.zeros(n)