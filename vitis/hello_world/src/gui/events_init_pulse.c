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

#define PULSE_PAGE_NUM 2

// 底部功能按钮菜单（两页）
const char* pulse_btn_menu[PULSE_PAGE_NUM][6] = {
    {"循环数", "相位", "延迟", "", "", "换页"},
    {"", "", "", "", "", "换页"}
};

// spinbox 参数绑定 (单位放数字后面, 与调制页风格一致)
static param_t pulse_params[3] = {
    {0, " 循环                            ", 8, 0, 1, 0, 99999999, OFFSET(burst_t, cycles), TYPE_U32},
    {0, " 相位                           度", 5, 3, 100, -18000, 18000, OFFSET(burst_t, phase), TYPE_F64},
    {0, " 延迟                           ms", 9, 5, 10, 0, 999999999, OFFSET(burst_t, delay_us), TYPE_U32},
};

uint8_t pulse_btn_page = 0;
lv_obj_t* pulse_spinbox_select;
static uint8_t g_is_updating_params = 0;
static uint8_t g_is_cursor_move = 0;

static void update_pulse_label_param8()
{
    char buf[64];
    burst_t *b = &burst[dds_ch];
    if (!b->enable) {
        lv_label_set_text(guider_ui.pulse_label_param8, "脉冲:关");
        return;
    }
    if (b->cycles == 0)
        sprintf(buf, "脉冲:%s 无限 相位:%.1f度 延迟:%lums",
                b->is_running ? "播放中" : "空闲", b->phase,
                (unsigned long)b->delay_us);
    else
        sprintf(buf, "脉冲:%s 循环数:%lu 相位:%.1f度 延迟:%lums",
                b->is_running ? "播放中" : "空闲", (unsigned long)b->cycles,
                b->phase, (unsigned long)b->delay_us);
    lv_label_set_text(guider_ui.pulse_label_param8, buf);
}

// ============================================================================
// 页面切换
// ============================================================================
static void pulse_btn_menu_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    menu_target_t target = (menu_target_t)(uintptr_t)lv_event_get_user_data(e);

    switch (target) {
        case MENU_GOTO_NORMAL:
            ui_load_scr_animation(&guider_ui, &guider_ui.normal, guider_ui.normal_del, &guider_ui.pulse_del, setup_scr_normal, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            normal_ch_refresh();
            break;
        case MENU_GOTO_MOD:
            ui_load_scr_animation(&guider_ui, &guider_ui.mod, guider_ui.mod_del, &guider_ui.pulse_del, setup_scr_mod, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            mod_ch_refresh();
            break;
        case MENU_GOTO_SCAN:
            ui_load_scr_animation(&guider_ui, &guider_ui.scan, guider_ui.scan_del, &guider_ui.pulse_del, setup_scr_scan, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            scan_ch_refresh();
            break;
        case MENU_GOTO_PULSE:
            ui_load_scr_animation(&guider_ui, &guider_ui.pulse, guider_ui.pulse_del, &guider_ui.pulse_del, setup_scr_pulse, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            pulse_ch_refresh();
            break;
        case MENU_GOTO_HARMONIC:
            ui_load_scr_animation(&guider_ui, &guider_ui.harmonic, guider_ui.harmonic_del, &guider_ui.pulse_del, setup_scr_harmonic, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            harmonic_ch_refresh();
            break;
        case MENU_GOTO_USER:
            ui_load_scr_animation(&guider_ui, &guider_ui.user, guider_ui.user_del, &guider_ui.pulse_del, setup_scr_user, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            user_ch_refresh();
            break;
        case MENU_GOTO_SYSTEM:
            ui_load_scr_animation(&guider_ui, &guider_ui.system, guider_ui.system_del, &guider_ui.pulse_del, setup_scr_system, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        default:
            break;
    }
}

// ============================================================================
// 底部按钮：更新标签 + 高亮当前选中参数
// ============================================================================
static void update_pulse_btn()
{
    lv_label_set_text(guider_ui.pulse_btn1_label, pulse_btn_menu[pulse_btn_page][0]);
    lv_label_set_text(guider_ui.pulse_btn2_label, pulse_btn_menu[pulse_btn_page][1]);
    lv_label_set_text(guider_ui.pulse_btn3_label, pulse_btn_menu[pulse_btn_page][2]);
    lv_label_set_text(guider_ui.pulse_btn4_label, pulse_btn_menu[pulse_btn_page][3]);
    lv_label_set_text(guider_ui.pulse_btn5_label, pulse_btn_menu[pulse_btn_page][4]);
    lv_label_set_text(guider_ui.pulse_btn6_label, pulse_btn_menu[pulse_btn_page][5]);
}

static void update_pulse_param_highlight(uint8_t param_idx)
{
    lv_obj_set_style_bg_color(guider_ui.pulse_label_param1, param_idx == 1 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_label_param2, param_idx == 2 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_label_param3, param_idx == 3 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_label_param4, param_idx == 4 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_label_param5, param_idx == 5 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_label_param6, param_idx == 6 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_label_param7, param_idx == 7 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
}

// ============================================================================
// 底部功能按钮事件（功能留空：仅选中参数/换页，具体逻辑后续实现）
// ============================================================================
static void pulse_btn_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    uint8_t btn_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); // 1~6

    switch (btn_id) {
        case 1: {
            if (pulse_btn_page == 0){
                pulse_spinbox_select = guider_ui.pulse_spinbox_1;
                update_pulse_param_highlight(1);
            }
            else if (pulse_btn_page == 1){
                pulse_spinbox_select = guider_ui.pulse_spinbox_6;
                update_pulse_param_highlight(6);
            }
            break;
        }
        case 2: {
            if (pulse_btn_page == 0){
                pulse_spinbox_select = guider_ui.pulse_spinbox_2;
                update_pulse_param_highlight(2);
            }
            else if (pulse_btn_page == 1){
                pulse_spinbox_select = guider_ui.pulse_spinbox_7;
                update_pulse_param_highlight(7);
            }
            break;
        }
        case 3: {
            if (pulse_btn_page == 0){
                pulse_spinbox_select = guider_ui.pulse_spinbox_3;
                update_pulse_param_highlight(3);
            }
            break;
        }
        case 4: {
            if (pulse_btn_page == 0){
                pulse_spinbox_select = guider_ui.pulse_spinbox_4;
                update_pulse_param_highlight(4);
            }
            break;
        }
        case 5: {
            if (pulse_btn_page == 0){
                pulse_spinbox_select = guider_ui.pulse_spinbox_5;
                update_pulse_param_highlight(5);
            }
            break;
        }
        case 6: {
            pulse_btn_page = (pulse_btn_page + 1) % PULSE_PAGE_NUM;
            update_pulse_btn();
            break;
        }
        default:
            break;
    }
}

// ============================================================================
// 方向按钮：左右移动光标，上下增减数值
// ============================================================================
static void pulse_btn_direction_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_SHORT_CLICKED && code != LV_EVENT_LONG_PRESSED_REPEAT) return;
    if (pulse_spinbox_select == NULL) return;

    direction_t dir = (direction_t)(uintptr_t)lv_event_get_user_data(e);
    switch (dir) {
        case DIR_LEFT:
            g_is_cursor_move = 1;
            lv_spinbox_step_prev(pulse_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_RIGHT:
            g_is_cursor_move = 1;
            lv_spinbox_step_next(pulse_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_UP:
            lv_spinbox_increment(pulse_spinbox_select);
            break;
        case DIR_DOWN:
            lv_spinbox_decrement(pulse_spinbox_select);
            break;
        default:
            break;
    }
}

// ============================================================================
// 参数刷新: 按 burst[dds_ch] 刷新 1~3 号 spinbox, 隐藏 4~7
// ============================================================================
static void update_pulse_params(void)
{
    g_is_updating_params = 1;
    lv_obj_t *spin[3] = {guider_ui.pulse_spinbox_1, guider_ui.pulse_spinbox_2, guider_ui.pulse_spinbox_3};
    lv_obj_t *lab[3]  = {guider_ui.pulse_label_param1, guider_ui.pulse_label_param2, guider_ui.pulse_label_param3};
    for (uint8_t i = 0; i < 3; i++) {
        param_t *p = &pulse_params[i];
        lv_spinbox_set_digit_format(spin[i], p->digit_count, p->separator_position);
        lv_spinbox_set_range(spin[i], p->min, p->max);
        lv_spinbox_set_value(spin[i], param_get_scaled_value(&burst[dds_ch], p));
        lv_label_set_text(lab[i], p->label);
    }
    lv_obj_t *hspin[4] = {guider_ui.pulse_spinbox_4, guider_ui.pulse_spinbox_5,
                          guider_ui.pulse_spinbox_6, guider_ui.pulse_spinbox_7};
    lv_obj_t *hlab[4]  = {guider_ui.pulse_label_param4, guider_ui.pulse_label_param5,
                          guider_ui.pulse_label_param6, guider_ui.pulse_label_param7};
    for (uint8_t i = 0; i < 4; i++) {
        lv_obj_add_flag(hspin[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(hlab[i], LV_OBJ_FLAG_HIDDEN);
    }
    g_is_updating_params = 0;
}

// ============================================================================
// 脉冲功能开关: 开=启用脉冲(触发按钮生效), 关=停止并禁用
// ============================================================================
static void pulse_sw_start_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        if(status){
            burst[dds_ch].enable = 1;
        }else{
            burst[dds_ch].enable = 0;
            burst_stop(dds_ch);
        }
        update_pulse_label_param8();
        break;
    }
    default:
        break;
    }
}

// ============================================================================
// 手动触发按钮
// ============================================================================
static void pulse_btn_trigger_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    burst_trigger(dds_ch);
    update_pulse_label_param8();
}

// ============================================================================
// 参数应用入口: 直接写结构体, 下次触发生效
// ============================================================================
static void pulse_param_apply(uint8_t spinbox_id)
{
    if (spinbox_id < 1 || spinbox_id > 3) return;
    lv_obj_t *spin[3] = {guider_ui.pulse_spinbox_1, guider_ui.pulse_spinbox_2, guider_ui.pulse_spinbox_3};
    param_set_raw_value(&burst[dds_ch], &pulse_params[spinbox_id - 1],
                        lv_spinbox_get_value(spin[spinbox_id - 1]));
    update_pulse_label_param8();
}

static void pulse_spinbox_event_handler(lv_event_t *e)
{
    if (g_is_updating_params) return;
    if (g_is_cursor_move) return;
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED) return;
    uint8_t spinbox_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); // 1~7
    pulse_param_apply(spinbox_id);
}

// 进入脉冲页时刷新
void pulse_ch_refresh(void)
{
    update_pulse_btn();
    update_pulse_params();
    update_pulse_label_param8();
    if (burst[dds_ch].enable)
        lv_obj_add_state(guider_ui.pulse_sw_start, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(guider_ui.pulse_sw_start, LV_STATE_CHECKED);
}

void events_init_pulse (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->pulse_btn_menu1, pulse_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_NORMAL);
    lv_obj_add_event_cb(ui->pulse_btn_menu2, pulse_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_MOD);
    lv_obj_add_event_cb(ui->pulse_btn_menu3, pulse_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SCAN);
    lv_obj_add_event_cb(ui->pulse_btn_menu5, pulse_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_HARMONIC);
    lv_obj_add_event_cb(ui->pulse_btn_menu6, pulse_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_USER);
    lv_obj_add_event_cb(ui->pulse_btn_menu7, pulse_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SYSTEM);
    lv_obj_add_event_cb(ui->pulse_btn1, pulse_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->pulse_btn2, pulse_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->pulse_btn3, pulse_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->pulse_btn4, pulse_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->pulse_btn5, pulse_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->pulse_btn6, pulse_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->pulse_btn_left,  pulse_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_LEFT);
    lv_obj_add_event_cb(ui->pulse_btn_right, pulse_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_RIGHT);
    lv_obj_add_event_cb(ui->pulse_btn_up,    pulse_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_UP);
    lv_obj_add_event_cb(ui->pulse_btn_down,  pulse_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_DOWN);
    lv_obj_add_event_cb(ui->pulse_spinbox_1, pulse_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->pulse_spinbox_2, pulse_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->pulse_spinbox_3, pulse_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->pulse_spinbox_4, pulse_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->pulse_spinbox_5, pulse_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->pulse_spinbox_6, pulse_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->pulse_spinbox_7, pulse_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)7);
    lv_obj_add_event_cb(ui->pulse_sw_start, pulse_sw_start_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->pulse_btn_trigger, pulse_btn_trigger_event_handler, LV_EVENT_ALL, NULL);
}
