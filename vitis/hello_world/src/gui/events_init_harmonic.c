#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xparameters_ps.h"
#include "sleep.h"
#include "xgpio.h"

#include "output_ctrl.h"
#include "gpio.h"
#include "lcd.h"
#include "i2c.h"
#include "spi.h"
#include "DAC8568.h"
#include "max17048.h"
#include "touch.h"

#define HARMONIC_PAGE_NUM 2

// 底部功能按钮菜单（两页）
const char* harmonic_btn_menu[HARMONIC_PAGE_NUM][6] = {
    {"个数", "序号", "幅值", "相位", "", "换页"},
    {"", "", "", "", "", "换页"}
};

// spinbox 参数绑定: 个数/序号为固定字段, 幅值/相位按当前序号动态寻址
// (单位放数字后面, 与调制页风格一致; 相位 000.00~360.00, 5位2位小数)
static param_t harmonic_params[5] = {
    {0, " 个数                            ", 2, 0, 1, 1, HARM_MAX, OFFSET(harmonic_t, count), TYPE_U8},
    {0, " 序号                            ", 2, 0, 1, 1, HARM_MAX, OFFSET(harmonic_t, idx), TYPE_U8},
    {0, " 幅值                           %", 4, 3, 10, 0, 1000, 0, TYPE_F64},  // 动态: amp[idx-1]
    {0, " 相位                           度", 5, 3, 100, 0, 36000, 0, TYPE_F64}, // 动态: phase[idx-1]
    {1, "", 0, 0, 1, 0, 0, 0, 0}                   // 预留
};

uint8_t harmonic_btn_page = 0;
lv_obj_t* harmonic_spinbox_select;
static uint8_t g_is_updating_params = 0;
static uint8_t g_is_cursor_move = 0;

// 当前序号对应的幅值/相位动态 param
static param_t harmonic_param_dyn(uint8_t spinbox_id)
{
    param_t p = harmonic_params[spinbox_id - 1];
    p.target = (spinbox_id == 3) ? OFFSET(harmonic_t, amp[0])
                                 : OFFSET(harmonic_t, phase[0]);
    p.target += (uintptr_t)(harmonic[dds_ch].idx - 1) * sizeof(double);
    return p;
}

static void update_harmonic_label_param8()
{
    char buf[64];
    harmonic_t *h = &harmonic[dds_ch];
    sprintf(buf, "谐波:%s %d次 序号%d 幅值%.1f%%",
            h->enable ? "开" : "关", h->count, h->idx, h->amp[h->idx - 1]);
    lv_label_set_text(guider_ui.harmonic_label_param8, buf);
}

// ============================================================================
// 页面切换
// ============================================================================
static void harmonic_btn_menu_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    menu_target_t target = (menu_target_t)(uintptr_t)lv_event_get_user_data(e);

    switch (target) {
        case MENU_GOTO_NORMAL:
            ui_load_scr_animation(&guider_ui, &guider_ui.normal, guider_ui.normal_del, &guider_ui.harmonic_del, setup_scr_normal, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            normal_ch_refresh();
            break;
        case MENU_GOTO_MOD:
            ui_load_scr_animation(&guider_ui, &guider_ui.mod, guider_ui.mod_del, &guider_ui.harmonic_del, setup_scr_mod, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            mod_ch_refresh();
            break;
        case MENU_GOTO_SCAN:
            ui_load_scr_animation(&guider_ui, &guider_ui.scan, guider_ui.scan_del, &guider_ui.harmonic_del, setup_scr_scan, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            scan_ch_refresh();
            break;
        case MENU_GOTO_PULSE:
            ui_load_scr_animation(&guider_ui, &guider_ui.pulse, guider_ui.pulse_del, &guider_ui.harmonic_del, setup_scr_pulse, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            pulse_ch_refresh();
            break;
        case MENU_GOTO_HARMONIC:
            ui_load_scr_animation(&guider_ui, &guider_ui.harmonic, guider_ui.harmonic_del, &guider_ui.harmonic_del, setup_scr_harmonic, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            harmonic_ch_refresh();
            break;
        case MENU_GOTO_USER:
            ui_load_scr_animation(&guider_ui, &guider_ui.user, guider_ui.user_del, &guider_ui.harmonic_del, setup_scr_user, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            user_ch_refresh();
            break;
        case MENU_GOTO_SYSTEM:
            ui_load_scr_animation(&guider_ui, &guider_ui.system, guider_ui.system_del, &guider_ui.harmonic_del, setup_scr_system, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        default:
            break;
    }
}

// ============================================================================
// 底部按钮：更新标签 + 高亮当前选中参数
// ============================================================================
static void update_harmonic_btn()
{
    lv_label_set_text(guider_ui.harmonic_btn1_label, harmonic_btn_menu[harmonic_btn_page][0]);
    lv_label_set_text(guider_ui.harmonic_btn2_label, harmonic_btn_menu[harmonic_btn_page][1]);
    lv_label_set_text(guider_ui.harmonic_btn3_label, harmonic_btn_menu[harmonic_btn_page][2]);
    lv_label_set_text(guider_ui.harmonic_btn4_label, harmonic_btn_menu[harmonic_btn_page][3]);
    lv_label_set_text(guider_ui.harmonic_btn5_label, harmonic_btn_menu[harmonic_btn_page][4]);
    lv_label_set_text(guider_ui.harmonic_btn6_label, harmonic_btn_menu[harmonic_btn_page][5]);
}

static void update_harmonic_param_highlight(uint8_t param_idx)
{
    lv_obj_set_style_bg_color(guider_ui.harmonic_label_param1, param_idx == 1 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_label_param2, param_idx == 2 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_label_param3, param_idx == 3 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_label_param4, param_idx == 4 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_label_param5, param_idx == 5 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_label_param6, param_idx == 6 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_label_param7, param_idx == 7 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
}

// ============================================================================
// 底部功能按钮事件（功能留空：仅选中参数/换页，具体逻辑后续实现）
// ============================================================================
static void harmonic_btn_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    uint8_t btn_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); // 1~6

    switch (btn_id) {
        case 1: {
            if (harmonic_btn_page == 0){
                harmonic_spinbox_select = guider_ui.harmonic_spinbox_1;
                update_harmonic_param_highlight(1);
            }
            else if (harmonic_btn_page == 1){
                harmonic_spinbox_select = guider_ui.harmonic_spinbox_6;
                update_harmonic_param_highlight(6);
            }
            break;
        }
        case 2: {
            if (harmonic_btn_page == 0){
                harmonic_spinbox_select = guider_ui.harmonic_spinbox_2;
                update_harmonic_param_highlight(2);
            }
            else if (harmonic_btn_page == 1){
                harmonic_spinbox_select = guider_ui.harmonic_spinbox_7;
                update_harmonic_param_highlight(7);
            }
            break;
        }
        case 3: {
            if (harmonic_btn_page == 0){
                harmonic_spinbox_select = guider_ui.harmonic_spinbox_3;
                update_harmonic_param_highlight(3);
            }
            break;
        }
        case 4: {
            if (harmonic_btn_page == 0){
                harmonic_spinbox_select = guider_ui.harmonic_spinbox_4;
                update_harmonic_param_highlight(4);
            }
            break;
        }
        case 5: {
            if (harmonic_btn_page == 0){
                harmonic_spinbox_select = guider_ui.harmonic_spinbox_5;
                update_harmonic_param_highlight(5);
            }
            break;
        }
        case 6: {
            harmonic_btn_page = (harmonic_btn_page + 1) % HARMONIC_PAGE_NUM;
            update_harmonic_btn();
            break;
        }
        default:
            break;
    }
}

// ============================================================================
// 方向按钮：左右移动光标，上下增减数值
// ============================================================================
static void harmonic_btn_direction_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_SHORT_CLICKED && code != LV_EVENT_LONG_PRESSED_REPEAT) return;
    if (harmonic_spinbox_select == NULL) return;

    direction_t dir = (direction_t)(uintptr_t)lv_event_get_user_data(e);
    switch (dir) {
        case DIR_LEFT:
            g_is_cursor_move = 1;
            lv_spinbox_step_prev(harmonic_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_RIGHT:
            g_is_cursor_move = 1;
            lv_spinbox_step_next(harmonic_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_UP:
            lv_spinbox_increment(harmonic_spinbox_select);
            break;
        case DIR_DOWN:
            lv_spinbox_decrement(harmonic_spinbox_select);
            break;
        default:
            break;
    }
}

// ============================================================================
// 参数刷新: 按 harmonic[dds_ch] 当前状态刷新 1~4 号 spinbox/标签
// ============================================================================
static void update_harmonic_params(void)
{
    g_is_updating_params = 1;
    harmonic_t *h = &harmonic[dds_ch];
    if (h->idx < 1) h->idx = 1;
    if (h->idx > h->count) h->idx = h->count;

    param_t p;
    p = harmonic_params[0];
    lv_spinbox_set_digit_format(guider_ui.harmonic_spinbox_1, p.digit_count, p.separator_position);
    lv_spinbox_set_range(guider_ui.harmonic_spinbox_1, p.min, p.max);
    lv_spinbox_set_value(guider_ui.harmonic_spinbox_1, param_get_scaled_value(h, &p));
    lv_label_set_text(guider_ui.harmonic_label_param1, p.label);

    p = harmonic_params[1];
    lv_spinbox_set_digit_format(guider_ui.harmonic_spinbox_2, p.digit_count, p.separator_position);
    lv_spinbox_set_range(guider_ui.harmonic_spinbox_2, p.min, h->count);
    lv_spinbox_set_value(guider_ui.harmonic_spinbox_2, param_get_scaled_value(h, &p));
    lv_label_set_text(guider_ui.harmonic_label_param2, p.label);

    p = harmonic_param_dyn(3);
    lv_spinbox_set_digit_format(guider_ui.harmonic_spinbox_3, p.digit_count, p.separator_position);
    lv_spinbox_set_range(guider_ui.harmonic_spinbox_3, p.min, p.max);
    lv_spinbox_set_value(guider_ui.harmonic_spinbox_3, param_get_scaled_value(h, &p));
    lv_label_set_text(guider_ui.harmonic_label_param3, p.label);

    p = harmonic_param_dyn(4);
    lv_spinbox_set_digit_format(guider_ui.harmonic_spinbox_4, p.digit_count, p.separator_position);
    lv_spinbox_set_range(guider_ui.harmonic_spinbox_4, p.min, p.max);
    lv_spinbox_set_value(guider_ui.harmonic_spinbox_4, param_get_scaled_value(h, &p));
    lv_label_set_text(guider_ui.harmonic_label_param4, p.label);

    // 预留参数隐藏
    lv_obj_add_flag(guider_ui.harmonic_spinbox_5, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.harmonic_label_param5, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.harmonic_spinbox_6, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.harmonic_label_param6, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.harmonic_spinbox_7, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.harmonic_label_param7, LV_OBJ_FLAG_HIDDEN);

    g_is_updating_params = 0;
}

// ============================================================================
// 谐波开关: 开=启用谐波(关调制), 关=恢复普通波形
// ============================================================================
static void harmonic_sw_start_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        if(status){
            harmonic[dds_ch].enable = 1;
            p_mod->is_modding = 0;
            lv_obj_clear_state(guider_ui.mod_sw_start, LV_STATE_CHECKED);
            mod_update(dds_ch);
        }else{
            harmonic[dds_ch].enable = 0;
            mod_update(dds_ch);
        }
        break;
    }
    default:
        break;
    }
}

// ============================================================================
// 参数应用入口: spinbox值变化时调用
// ============================================================================
static void harmonic_param_apply(uint8_t spinbox_id)
{
    harmonic_t *h = &harmonic[dds_ch];
    uint8_t need_regen = 0;

    switch (spinbox_id) {
        case 1:  // 谐波个数
            param_set_raw_value(h, &harmonic_params[0], lv_spinbox_get_value(guider_ui.harmonic_spinbox_1));
            if (h->idx > h->count) h->idx = h->count;
            need_regen = 1;
            break;
        case 2:  // 谐波序号(仅切换编辑对象, 不重生成)
            param_set_raw_value(h, &harmonic_params[1], lv_spinbox_get_value(guider_ui.harmonic_spinbox_2));
            break;
        case 3:  // 幅值
        {
            param_t p = harmonic_param_dyn(3);
            param_set_raw_value(h, &p, lv_spinbox_get_value(guider_ui.harmonic_spinbox_3));
            need_regen = 1;
            break;
        }
        case 4:  // 相位
        {
            param_t p = harmonic_param_dyn(4);
            param_set_raw_value(h, &p, lv_spinbox_get_value(guider_ui.harmonic_spinbox_4));
            need_regen = 1;
            break;
        }
        default:
            break;
    }

    update_harmonic_params();           // 刷新 UI(序号变化后重载幅值/相位)
    update_harmonic_label_param8();
    if (need_regen && harmonic[dds_ch].enable)
        mod_update(dds_ch);             // 重新合成并播放
}

static void harmonic_spinbox_event_handler(lv_event_t *e)
{
    if (g_is_updating_params) return;
    if (g_is_cursor_move) return;
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED) return;
    uint8_t spinbox_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); // 1~7
    harmonic_param_apply(spinbox_id);
}

// 进入谐波页时刷新
void harmonic_ch_refresh(void)
{
    update_harmonic_btn();
    update_harmonic_params();
    update_harmonic_label_param8();
    if (harmonic[dds_ch].enable)
        lv_obj_add_state(guider_ui.harmonic_sw_start, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(guider_ui.harmonic_sw_start, LV_STATE_CHECKED);
}

void events_init_harmonic (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->harmonic_btn_menu1, harmonic_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_NORMAL);
    lv_obj_add_event_cb(ui->harmonic_btn_menu2, harmonic_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_MOD);
    lv_obj_add_event_cb(ui->harmonic_btn_menu3, harmonic_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SCAN);
    lv_obj_add_event_cb(ui->harmonic_btn_menu4, harmonic_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_PULSE);
    lv_obj_add_event_cb(ui->harmonic_btn_menu6, harmonic_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_USER);
    lv_obj_add_event_cb(ui->harmonic_btn_menu7, harmonic_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SYSTEM);
    lv_obj_add_event_cb(ui->harmonic_btn1, harmonic_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->harmonic_btn2, harmonic_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->harmonic_btn3, harmonic_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->harmonic_btn4, harmonic_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->harmonic_btn5, harmonic_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->harmonic_btn6, harmonic_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->harmonic_btn_left,  harmonic_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_LEFT);
    lv_obj_add_event_cb(ui->harmonic_btn_right, harmonic_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_RIGHT);
    lv_obj_add_event_cb(ui->harmonic_btn_up,    harmonic_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_UP);
    lv_obj_add_event_cb(ui->harmonic_btn_down,  harmonic_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_DOWN);
    lv_obj_add_event_cb(ui->harmonic_spinbox_1, harmonic_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->harmonic_spinbox_2, harmonic_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->harmonic_spinbox_3, harmonic_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->harmonic_spinbox_4, harmonic_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->harmonic_spinbox_5, harmonic_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->harmonic_spinbox_6, harmonic_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->harmonic_spinbox_7, harmonic_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)7);
    lv_obj_add_event_cb(ui->harmonic_sw_start, harmonic_sw_start_event_handler, LV_EVENT_ALL, ui);
}
