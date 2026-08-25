#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xparameters_ps.h"
#include "sleep.h"
#include "xgpio.h"

#include "output_ctrl.h"
#include "user_dds.h"
#include "gpio.h"
#include "lcd.h"
#include "i2c.h"
#include "spi.h"
#include "DAC8568.h"
#include "max17048.h"
#include "touch.h"



#define SCAN_PAGE_NUM 2

const char *scan_modes[] = {"线性扫频", "对数扫频"};

//设置param5,6,7。第一个索引为波形序号，第二个索引为params的设置
param_t scan_params[2][3] = {
    {{1},{1},{1}},
    {{1},{1},{1}}
};

const char* scan_btn_menu[SCAN_PAGE_NUM][6] = {
    {"模式", "起点", "终点", "点数", "间隔", "换页"},
    {"参数4", "参数5", "参数6", "", "", "换页"}
};
uint8_t scan_btn_page = 0;
lv_obj_t* scan_spinbox_select;
static uint8_t g_is_updating_params = 0;
static uint8_t g_is_cursor_move = 0;
char scan_mod_str[16];

static void update_scan_label_param8()
{
    char buf[32];
    sprintf(buf, "模式:%s", scan_mod_str);
    lv_label_set_text(guider_ui.scan_label_param8, buf);
}

static void update_scan_btn()
{
    lv_label_set_text(guider_ui.scan_btn1_label, scan_btn_menu[scan_btn_page][0]);
    lv_label_set_text(guider_ui.scan_btn2_label, scan_btn_menu[scan_btn_page][1]);
    lv_label_set_text(guider_ui.scan_btn3_label, scan_btn_menu[scan_btn_page][2]);
    lv_label_set_text(guider_ui.scan_btn4_label, scan_btn_menu[scan_btn_page][3]);
    lv_label_set_text(guider_ui.scan_btn5_label, scan_btn_menu[scan_btn_page][4]);
    lv_label_set_text(guider_ui.scan_btn6_label, scan_btn_menu[scan_btn_page][5]);
}

static void update_scan_param_highlight(uint8_t param_idx)
{
    lv_obj_set_style_bg_color(guider_ui.scan_label_param1, param_idx == 1 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_label_param2, param_idx == 2 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_label_param3, param_idx == 3 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_label_param4, param_idx == 4 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_label_param5, param_idx == 5 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_label_param6, param_idx == 6 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_label_param7, param_idx == 7 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
}


static void update_scan_params()
{
    g_is_updating_params = 1;
    param_t param;    
    param = scan_params[p_scan->scan_mode][0];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.scan_spinbox_5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scan_label_param5, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.scan_spinbox_5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.scan_label_param5, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.scan_spinbox_5, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.scan_spinbox_5, param.min, param.max);
        lv_spinbox_set_value(guider_ui.scan_spinbox_5, param_get_scaled_value(p_scan, &param));
        lv_label_set_text(guider_ui.scan_label_param5, param.label);
    }
    param = scan_params[p_scan->scan_mode][1];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.scan_spinbox_6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scan_label_param6, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.scan_spinbox_6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.scan_label_param6, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.scan_spinbox_6, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.scan_spinbox_6, param.min, param.max);
        lv_spinbox_set_value(guider_ui.scan_spinbox_6, param_get_scaled_value(p_scan, &param));
        lv_label_set_text(guider_ui.scan_label_param6, param.label);
    }
    param = scan_params[p_scan->scan_mode][2];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.scan_spinbox_7, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scan_label_param7, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.scan_spinbox_7, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.scan_label_param7, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.scan_spinbox_7, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.scan_spinbox_7, param.min, param.max);
        lv_spinbox_set_value(guider_ui.scan_spinbox_7, param_get_scaled_value(p_scan, &param));
        lv_label_set_text(guider_ui.scan_label_param7, param.label);
    }
    g_is_updating_params = 0;
}

static void scan_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) return;
    uint8_t btn_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); // 1~6

    switch (btn_id) {
        case 1: {
            if (scan_btn_page == 0) {
                if (lv_obj_has_flag(guider_ui.scan_list_mode, LV_OBJ_FLAG_HIDDEN)) {
                    lv_obj_clear_flag(guider_ui.scan_list_mode, LV_OBJ_FLAG_HIDDEN);
                } else {
                    lv_obj_add_flag(guider_ui.scan_list_mode, LV_OBJ_FLAG_HIDDEN);
                }
            } else if (scan_btn_page == 1) {
                if(!scan_params[p_scan->scan_mode][0].is_hide){
                    scan_spinbox_select = guider_ui.scan_spinbox_5;
                    update_scan_param_highlight(5);
                }
            }
            break;
        }
        case 2: {
            if (scan_btn_page == 0) {
                scan_spinbox_select = guider_ui.scan_spinbox_1;
                update_scan_param_highlight(1);
            } else if (scan_btn_page == 1) {
                if(!scan_params[p_scan->scan_mode][1].is_hide){
                    scan_spinbox_select = guider_ui.scan_spinbox_6;
                    update_scan_param_highlight(6);
                }
            }
            break;
        }
        case 3: {
            if (scan_btn_page == 0) {
                scan_spinbox_select = guider_ui.scan_spinbox_2;
                update_scan_param_highlight(2);
            } else if (scan_btn_page == 1) {
                if(!scan_params[p_scan->scan_mode][2].is_hide){
                    scan_spinbox_select = guider_ui.scan_spinbox_7;
                    update_scan_param_highlight(7);
                }
            }
            break;
        }
        case 4: {
            if (scan_btn_page == 0) {
                scan_spinbox_select = guider_ui.scan_spinbox_3;
                update_scan_param_highlight(3);
            } else if (scan_btn_page == 1) {

            }
            break;
        }
        case 5: {
            if (scan_btn_page == 0) {
                scan_spinbox_select = guider_ui.scan_spinbox_4;
                update_scan_param_highlight(4);
            } else if (scan_btn_page == 1) {

            }
            break;
        }
        case 6: {
            scan_btn_page = (scan_btn_page + 1) % SCAN_PAGE_NUM;
            update_scan_btn();
            break;
        }
        default:
            break;
    }
}

void scan_ch_refresh(void)
{
    update_scan_label_param8();
    update_scan_params();
}


static void scan_btn_menu_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    menu_target_t target = (menu_target_t)(uintptr_t)lv_event_get_user_data(e);

    lv_obj_add_flag(guider_ui.scan_list_mode, LV_OBJ_FLAG_HIDDEN);

    switch (target) {
        case MENU_GOTO_NORMAL:
            ui_load_scr_animation(&guider_ui, &guider_ui.normal, guider_ui.normal_del, &guider_ui.scan_del, setup_scr_normal, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        case MENU_GOTO_MOD:
            ui_load_scr_animation(&guider_ui, &guider_ui.mod, guider_ui.mod_del, &guider_ui.scan_del, setup_scr_mod, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        case MENU_GOTO_PULSE:
            ui_load_scr_animation(&guider_ui, &guider_ui.pulse, guider_ui.pulse_del, &guider_ui.scan_del, setup_scr_pulse, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            pulse_ch_refresh();
            break;
        case MENU_GOTO_HARMONIC:
            ui_load_scr_animation(&guider_ui, &guider_ui.harmonic, guider_ui.harmonic_del, &guider_ui.scan_del, setup_scr_harmonic, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            harmonic_ch_refresh();
            break;
        case MENU_GOTO_USER:
            ui_load_scr_animation(&guider_ui, &guider_ui.user, guider_ui.user_del, &guider_ui.scan_del, setup_scr_user, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            user_ch_refresh();
            break;
        case MENU_GOTO_SYSTEM:
            ui_load_scr_animation(&guider_ui, &guider_ui.system, guider_ui.system_del, &guider_ui.scan_del, setup_scr_system, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        default:
            break;
    }
}

static void scan_btn_direction_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_SHORT_CLICKED && code != LV_EVENT_LONG_PRESSED_REPEAT) return;
    if (scan_spinbox_select == NULL) return;

    direction_t dir = (direction_t)(uintptr_t)lv_event_get_user_data(e);

    switch (dir) {
        case DIR_LEFT:
            g_is_cursor_move = 1;
            lv_spinbox_step_prev(scan_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_RIGHT:
            g_is_cursor_move = 1;
            lv_spinbox_step_next(scan_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_UP:
            lv_spinbox_increment(scan_spinbox_select);
            break;
        case DIR_DOWN:
            lv_spinbox_decrement(scan_spinbox_select);
            break;
        default:
            break;
    }
}

static void scan_spinbox_event_handler (lv_event_t *e)
{
    if (g_is_updating_params) return;//关键
    if (g_is_cursor_move) return;//仅移动光标，不触发
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_VALUE_CHANGED) return;
    uint8_t spinbox_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); // 1~7
    switch (spinbox_id) {
	    case 1:
            p_scan->start = lv_spinbox_get_value(guider_ui.scan_spinbox_1) / 10.0;
            break;
	    case 2:
            p_scan->end = lv_spinbox_get_value(guider_ui.scan_spinbox_2) / 10.0;
            break;
	    case 3:
            p_scan->point = lv_spinbox_get_value(guider_ui.scan_spinbox_3);
            break;
	    case 4:
            p_scan->time_interval_ns = lv_spinbox_get_value(guider_ui.scan_spinbox_4) * 100;
            break;
            
	    case 5:
            if(!scan_params[p_scan->scan_mode][0].is_hide){
                param_set_raw_value(p_scan, &scan_params[p_scan->scan_mode][0], lv_spinbox_get_value(guider_ui.scan_spinbox_5));
            }
            break;
	    case 6:
            if(!scan_params[p_scan->scan_mode][1].is_hide){
                param_set_raw_value(p_scan, &scan_params[p_scan->scan_mode][1], lv_spinbox_get_value(guider_ui.scan_spinbox_6));
            }
            break;
	    case 7:
            if(!scan_params[p_scan->scan_mode][2].is_hide){
                param_set_raw_value(p_scan, &scan_params[p_scan->scan_mode][2], lv_spinbox_get_value(guider_ui.scan_spinbox_7));
            }
            break;
        default:break;
	}
}

static void scan_list_mode_item_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) return;

    uint8_t mode_index = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    p_scan->scan_mode = mode_index;
    strcpy(scan_mod_str, scan_modes[p_scan->scan_mode]);
    update_scan_label_param8();
    update_scan_params();
    lv_obj_add_flag(guider_ui.scan_list_mode, LV_OBJ_FLAG_HIDDEN);
}

static void scan_sw_start_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        if(status){
            if (dds_sel != 0) {
                // 扫频仅支持32K(bram_dds)模式, 拒绝启动
                lv_obj_clear_state(guider_ui.scan_sw_start, LV_STATE_CHECKED);
                lv_label_set_text(guider_ui.scan_label_param8, "扫频仅支持32K模式");
                break;
            }
            p_mod->is_modding = 0;
            mod_update(dds_ch);
            lv_obj_clear_state(guider_ui.mod_sw_start, LV_STATE_CHECKED);
            scan_start(dds_ch);
        }else{
            scan[dds_ch].is_running = 0;
            update_scan_label_param8();   // 清除提示, 恢复模式显示
        }
        break;
    }
    default:
        break;
    }
}

static void scan_sw_loop_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        if(status){
            p_scan->is_loop = 1;
        }else{
            p_scan->is_loop = 0;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_scan (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scan_btn1, scan_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->scan_btn2, scan_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->scan_btn3, scan_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->scan_btn4, scan_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->scan_btn5, scan_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->scan_btn6, scan_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->scan_btn_menu1, scan_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_NORMAL);
    lv_obj_add_event_cb(ui->scan_btn_menu2, scan_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_MOD);
    lv_obj_add_event_cb(ui->scan_btn_menu4, scan_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_PULSE);
    lv_obj_add_event_cb(ui->scan_btn_menu5, scan_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_HARMONIC);
    lv_obj_add_event_cb(ui->scan_btn_menu6, scan_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_USER);
    lv_obj_add_event_cb(ui->scan_btn_menu7, scan_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SYSTEM);
    lv_obj_add_event_cb(ui->scan_btn_left,  scan_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_LEFT);
    lv_obj_add_event_cb(ui->scan_btn_right, scan_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_RIGHT);
    lv_obj_add_event_cb(ui->scan_btn_up,    scan_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_UP);
    lv_obj_add_event_cb(ui->scan_btn_down,  scan_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_DOWN);
    lv_obj_add_event_cb(ui->scan_spinbox_1, scan_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->scan_spinbox_2, scan_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->scan_spinbox_3, scan_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->scan_spinbox_4, scan_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->scan_spinbox_5, scan_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->scan_spinbox_6, scan_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->scan_spinbox_7, scan_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)7);
    lv_obj_add_event_cb(ui->scan_list_mode_item0, scan_list_mode_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)0);
    lv_obj_add_event_cb(ui->scan_list_mode_item1, scan_list_mode_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->scan_sw_loop, scan_sw_loop_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_sw_start, scan_sw_start_event_handler, LV_EVENT_ALL, ui);
}
