# TinyAWG-MK2 信号发生器控制台 (PyQt6)

工业风上位机，通过串口完整控制 TinyAWG-MK2 双通道任意波形发生器，并支持用户波形绘制/导入/上传。

## 安装与运行

```bash
pip install -r requirements.txt
python -m pc_host_qt.main
```

依赖：Python 3.9+，PyQt6、pyserial、numpy。

## 功能

| 页面 | 功能 |
|------|------|
| 常规 | 34 种标准波形、频率/幅度/偏置/相位、每种波形专属参数、本地波形预览 |
| 调制 | AM/FM/PM 调制（深度/频偏/相偏按模式切换） |
| 扫频 | 线性/对数扫频、循环、点数、驻留间隔（仅 32K 存储模式） |
| 谐波 | 16 次谐波幅值/相位表、启用/停用 |
| 脉冲 | 突发输出（循环数/相位/延迟/手动触发） |
| 用户波形 | 32 组 × 512K 点，手绘编辑/导入文件，自动重采样到 512K 后流式上传设备 |
| 系统 | 存储深度、输出开关、蜂鸣、通道同步、电池电量、DAC 校准电压测试 |

## 用户波形上传

设备端用户波形固定 32 组 × 512K 点（int16，共 1MB/组）。上传采用**原始流式传输**（无确认/无校验，速率即串口波特率），1MB 在 2Mbps 下约 4 秒完成。

- **手动绘制**：在画布上左键绘制，右键撤销，C 清空，S 平滑，N 归一化，I 取反
- **导入文件**：支持 WAV / CSV / TXT / BIN / RAW
  - 点数不足 512K：线性插值补足
  - 点数超过 512K：抗混叠均值滤波后抽样到 512K
- **输出限制**：存储深度 ≤ 512K 时才能输出用户波形（与设备端扫描的存储限制策略一致），设备端会拒绝超限开启。
- 上传采用分帧 ACK 流控（每帧 240 字节 + CRC8 校验 + 序号确认），全程显示进度。

## 串口协议 (v2)

| 方向 | 命令 | 说明 |
|------|------|------|
| PC→设备 | `G` | 查询全部参数 |
| PC→设备 | `S key=val key=val ...` | 设置参数（可多个，空格分隔） |
| PC→设备 | `D v0,..,v5` | 设置 DAC 6 通道电压（0~5V） |
| PC→设备 | `U<组>` 后接二进制帧 | 上传用户波形（帧格式见固件 PC_HOST.h） |

完整键名：`ch wave freq vpp offset phase duty sym rising zc decay hr steps cycles damp
trise rcw gaussw dpw erise lw rpulses ssteep sna qna ewave rsq rtr rw uduty prbs
m_en m_mode m_base m_carr m_depth m_dev m_index
s_start s_end s_points s_intv s_mode s_loop s_run
h_en h_count h_idx h_amp1..16 h_ph1..16
b_en b_cycles b_phase b_delay b_trig
u_sel u_en depth buzz sync out out0 out1`

## 界面风格

深色工业控制台：炭黑基底 + 冷色高光 + 琥珀警示色，硬边面板、等宽数字、清晰分区，适合长期值守操作。