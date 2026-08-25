# -*- coding: utf-8 -*-
"""工业控制台暗色主题 (QSS)。深色金属基底、硬边面板、警示色标。"""

APP_NAME = "TinyAWG-MK2 信号发生器控制台"
APP_VERSION = "1.0.0"

# 调色板
C_BG       = "#14171c"   # 炭黑基底
C_BG_PANEL = "#1b2026"   # 面板
C_BG_RAISE = "#222830"   # 凸起块
C_BG_INPUT = "#0e1115"   # 输入框
C_BORDER   = "#3a4450"   # 边框
C_BORDER_HI= "#516070"   # 高亮边框
C_TEXT     = "#d8dee6"   # 主文字
C_TEXT_MUT = "#7f8b99"   # 次要文字
C_CYAN     = "#22c1e6"   # 青蓝高光
C_GREEN    = "#2ecc71"   # 运行/就绪
C_AMBER    = "#f5a623"   # 警示
C_RED      = "#e5533d"   # 故障
C_GOLD     = "#d4b14a"   # 金 (通道0)
C_CYAN_CH  = "#5fd8f4"   # 青蓝 (通道1)

FONT = '"Microsoft YaHei UI"'
FONT_MONO = '"Consolas"'


def qss() -> str:
    return f"""
* {{
    font-family: {FONT};
    font-size: 12px;
    color: {C_TEXT};
    outline: 0;
}}
QMainWindow, QWidget#root {{
    background: {C_BG};
}}
QWidget {{ background: transparent; }}

/* ---- 顶栏 ---- */
#topbar {{
    background: #101318;
    border-bottom: 1px solid {C_BORDER};
}}
#topbar QLabel {{ color: {C_TEXT}; background: transparent; }}
#appTitle {{
    font-size: 16px;
    font-weight: bold;
    letter-spacing: 1px;
    color: #eef4fa;
}}
#appSub {{
    font-size: 11px;
    color: {C_TEXT_MUT};
}}
#chBadge {{
    color: {C_CYAN};
    font-weight: bold;
    font-size: 14px;
}}
#connDot {{
    font-size: 14px;
    font-weight: bold;
}}
QLabel[role="kpi"] {{
    color: {C_TEXT};
    font-family: {FONT_MONO};
    font-size: 14px;
    font-weight: bold;
}}
QLabel[kpiName] {{
    color: {C_TEXT_MUT};
    font-size: 10px;
    letter-spacing: 1px;
}}

/* ---- 选项卡 ---- */
QTabWidget::pane {{
    border: 1px solid {C_BORDER};
    border-radius: 0px;
    background: {C_BG};
    top: -1px;
}}
QTabBar::tab {{
    background: #181d24;
    color: {C_TEXT_MUT};
    border: 1px solid {C_BORDER};
    border-bottom: none;
    padding: 8px 18px;
    margin-right: 2px;
    font-weight: bold;
    font-size: 13px;
    letter-spacing: 1px;
}}
QTabBar::tab:hover {{ background: #20262f; color: {C_TEXT}; }}
QTabBar::tab:selected {{
    background: #222830;
    color: {C_CYAN};
    border-top: 2px solid {C_CYAN};
}}
QTabBar::tab:disabled {{ color: {C_TEXT_MUT}; }}

/* ---- 面板/卡片 ---- */
QGroupBox {{
    background: {C_BG_PANEL};
    border: 1px solid {C_BORDER};
    border-radius: 0px;
    margin-top: 14px;
    font-weight: bold;
    color: {C_TEXT};
    letter-spacing: 1px;
}}
QGroupBox::title {{
    subcontrol-origin: margin;
    left: 12px;
    top: 0px;
    padding: 0 4px;
    color: {C_CYAN};
}}
QFrame[panel="1"] {{
    background: {C_BG_PANEL};
    border: 1px solid {C_BORDER};
    border-radius: 0px;
}}
QFrame[hazard="1"] {{
    background: {C_BG_PANEL};
    border: 2px solid {C_AMBER};
    border-radius: 0px;
}}

/* ---- 按钮 ---- */
QPushButton {{
    background: #232a33;
    border: 1px solid {C_BORDER};
    border-radius: 0px;
    padding: 6px 14px;
    color: {C_TEXT};
    font-weight: bold;
    letter-spacing: 1px;
    min-height: 22px;
}}
QPushButton:hover {{
    background: #2b343f;
    border-color: {C_BORDER_HI};
    color: {C_CYAN};
}}
QPushButton:pressed {{
    background: #14181e;
    border-color: {C_CYAN};
    padding-top: 7px;
}}
QPushButton:disabled {{
    color: {C_TEXT_MUT};
    background: #1a1f26;
    border-color: #2a3038;
}}
QPushButton[accent="1"] {{
    background: {C_CYAN};
    color: #08121a;
    border: 1px solid {C_CYAN};
    font-weight: bold;
}}
QPushButton[accent="1"]:hover {{ background: #45cdef; }}
QPushButton[accent="1"]:pressed {{ background: #1896b3; }}
QPushButton[danger="1"] {{
    background: transparent;
    color: {C_RED};
    border: 1px solid {C_RED};
}}
QPushButton[danger="1"]:hover {{ background: rgba(229,83,61,0.15); }}
QPushButton[danger="1"]:pressed {{ background: {C_RED}; color: #fff; }}
QPushButton[amber="1"] {{
    background: transparent;
    color: {C_AMBER};
    border: 1px solid {C_AMBER};
}}
QPushButton[amber="1"]:hover {{ background: rgba(245,166,35,0.15); }}
QPushButton[amber="1"]:pressed {{ background: {C_AMBER}; color: #1a1408; }}

/* ---- 输入框 ---- */
QLineEdit, QDoubleSpinBox, QSpinBox, QComboBox, QPlainTextEdit {{
    background: {C_BG_INPUT};
    border: 1px solid {C_BORDER};
    border-radius: 0px;
    padding: 4px 8px;
    color: {C_TEXT};
    selection-background-color: {C_CYAN};
    selection-color: #08121a;
    min-height: 20px;
}}
QLineEdit:focus, QDoubleSpinBox:focus, QSpinBox:focus, QComboBox:focus {{
    border-color: {C_CYAN};
}}
QLineEdit:disabled, QDoubleSpinBox:disabled, QSpinBox:disabled, QComboBox:disabled {{
    color: {C_TEXT_MUT};
    background: #13171d;
}}
QDoubleSpinBox::up-button, QSpinBox::up-button {{
    background: #232a33;
    border: 1px solid {C_BORDER};
    width: 16px;
    subcontrol-origin: border;
}}
QDoubleSpinBox::down-button, QSpinBox::down-button {{
    background: #232a33;
    border: 1px solid {C_BORDER};
    width: 16px;
    subcontrol-origin: border;
}}
QComboBox::drop-down {{
    border: none; width: 20px; }}
QComboBox QAbstractItemView {{
    background: {C_BG_PANEL};
    border: 1px solid {C_BORDER};
    selection-background-color: #26323d;
    selection-color: {C_CYAN};
    outline: 0;
}}

/* ---- 复选/开关 ---- */
QCheckBox {{
    spacing: 6px; color: {C_TEXT}; font-weight: bold; }}
QCheckBox::indicator {{
    width: 16px; height: 16px;
    border: 1px solid {C_BORDER};
    background: {C_BG_INPUT};
}}
QCheckBox::indicator:checked {{ background: {C_CYAN}; border-color: {C_CYAN}; }}
QCheckBox::indicator:hover {{ border-color: {C_CYAN}; }}

/* ---- 进度条 ---- */
QProgressBar {{
    background: {C_BG_INPUT};
    border: 1px solid {C_BORDER};
    border-radius: 0px;
    text-align: center;
    color: {C_TEXT};
    font-family: {FONT_MONO};
    font-size: 11px;
    min-height: 18px;
}}
QProgressBar::chunk {{
    background: {C_CYAN};
    border-radius: 0px;
}}

/* ---- 滚动条 ---- */
QScrollBar:vertical {{
    background: {C_BG}; width: 12px; margin: 0; }}
QScrollBar::handle:vertical {{
    background: #323c48; min-height: 30px; border-radius: 0px; }}
QScrollBar::handle:vertical:hover {{ background: {C_BORDER_HI}; }}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {{ height: 0; width: 0; }}
QScrollBar:horizontal {{
    background: {C_BG}; height: 12px; margin: 0; }}
QScrollBar::handle:horizontal {{
    background: #323c48; min-width: 30px; border-radius: 0px; }}
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {{ height: 0; width: 0; }}

/* ---- 表格 ---- */
QTableWidget {{
    background: {C_BG_PANEL};
    border: 1px solid {C_BORDER};
    gridline-color: {C_BORDER};
    selection-background-color: #26323d;
    selection-color: {C_CYAN};
    alternate-background-color: #1e242c;
}}
QHeaderView::section {{
    background: #222830;
    color: {C_CYAN};
    border: 1px solid {C_BORDER};
    padding: 4px 8px;
    font-weight: bold;
    letter-spacing: 1px;
}}
QTableWidget::item {{
    padding: 2px 4px; font-family: {FONT_MONO}; font-size: 12px; }}

/* ---- 状态栏 ---- */
QStatusBar {{
    background: #101318;
    border-top: 1px solid {C_BORDER};
    color: {C_TEXT_MUT};
    font-size: 11px;
}}
QStatusBar QLabel {{ color: {C_TEXT_MUT}; }}

/* ---- 工具提示 ---- */
QToolTip {{
    background: #1b2026;
    color: {C_TEXT};
    border: 1px solid {C_CYAN};
    padding: 4px 8px;
    font-size: 11px;
}}
"""