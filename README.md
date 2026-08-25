# TinyAWG-MK2

基于 Zynq-7000 的双通道任意波形发生器（AWG）。硬件（Vivado）+ 固件（Vitis）+ 触摸屏界面（LVGL/GUI Guider）+ PC 上位机（PyQt6）全开源。

## 目录结构

```
├── TinyAWG_MK2.xpr            Vivado 工程文件
├── TinyAWG_MK2.srcs/          Vivado 源码（Block Design、约束）
├── design_1_wrapper.xsa       已导出的硬件平台（XSA）
├── vitis/                     Vitis 固件工程
│   └── hello_world/src/       固件源码（DDS、DAC8568、LCD 触摸、LVGL、串口协议）
├── lvgl_gui/AWG/              GUI Guider 界面工程（custom/ 与 generated/）
└── pc_host_qt/                PC 上位机（PyQt6），串口控制与用户波形上传
```

## 构建

1. **硬件**：用 Vivado 打开 `TinyAWG_MK2.xpr`，综合/实现并生成比特流，导出 XSA。
2. **固件**：在 Vitis 中基于 XSA 创建平台与 `hello_world` 应用，源码位于 `vitis/hello_world/src/`。
3. **界面**：用 NXP GUI Guider 打开 `lvgl_gui/AWG/AWG.guiguider` 编辑/导出界面代码。
4. **上位机**：见 `pc_host_qt/README.md`，`pip install -r requirements.txt` 后运行。

> 说明：`vitis/platform/`、`vitis/_ide/`、`lvgl_gui/AWG/lvgl/`、`lvgl-simulator/` 等均由工具链自动生成，未纳入版本库；Vivado 的 `.cache/.runs/.gen` 等生成目录同样被 `.gitignore` 排除。

## 功能

- 双通道 DDS 任意波形输出（正弦/方波/三角/锯齿/噪声等 34 种波形）
- AM/FM/PM 调制、线性/对数扫频、16 次谐波合成、脉冲突发
- 用户自定义波形：32 组 × 512K 点，支持 PC 端手绘/导入后流式上传
- 4.3 寸电容触摸屏（LVGL 界面），电池供电（MAX17048 电量监测）
- 串口协议与 PC 上位机（波形预览、参数控制、DAC 校准）

## 许可证

[GPL-3.0](LICENSE)

第三方组件：LVGL（MIT）、LVGL 驱动库、GUI Guider（NXP）等均保留其各自许可证。