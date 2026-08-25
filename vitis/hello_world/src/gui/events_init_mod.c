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

#define MOD_PAGE_NUM 2

//设置param3,4,5,6,7。第一个索引为调制类型序号，第二个索引为params的设置
param_t mod_params[3][5] = {
    {{0," 深度                           %",4,3,1000,0,1000,OFFSET(mod_t,depth),TYPE_F64},{1},{1},{1},{1}},    //AM
    {{0," 频偏                           Hz",9,8,10,0,999999999,OFFSET(mod_t,delta_f),TYPE_F64},{1},{1},{1},{1}},// FM
    {{0," 相偏                            ",5,3,100,0,10000,OFFSET(mod_t,pm_index),TYPE_F64},{1},{1},{1},{1}}   // PM
};

const char *mod_modes[] = {"AM", "FM", "PM"};
const char *mod_waves[] = {"正弦波"};

const char* mod_btn_menu[MOD_PAGE_NUM][6] = {
    {"调制类型", "调制波形", "调制频率", "载波频率", "参数3", "换页"},
    {"参数4", "参数5", "参数6", "参数7", "", "换页"}
};

uint8_t mod_btn_page = 0;
lv_obj_t* mod_spinbox_select;
static uint8_t g_is_updating_params = 0;
static uint8_t g_is_cursor_move = 0;
char mod_wave_str[16] = "正弦波";
char mod_mode_str[16];



static void update_mod_label_param8()
{
    char buf[64];
    sprintf(buf, "类型:%s 调制波形:%s", mod_mode_str, mod_wave_str);
    lv_label_set_text(guider_ui.mod_label_param8, buf);
}

static void update_mod_btn()
{
    lv_label_set_text(guider_ui.mod_btn1_label, mod_btn_menu[mod_btn_page][0]);
    lv_label_set_text(guider_ui.mod_btn2_label, mod_btn_menu[mod_btn_page][1]);
    lv_label_set_text(guider_ui.mod_btn3_label, mod_btn_menu[mod_btn_page][2]);
    lv_label_set_text(guider_ui.mod_btn4_label, mod_btn_menu[mod_btn_page][3]);
    lv_label_set_text(guider_ui.mod_btn5_label, mod_btn_menu[mod_btn_page][4]);
    lv_label_set_text(guider_ui.mod_btn6_label, mod_btn_menu[mod_btn_page][5]);
}

static void update_mod_param_highlight(uint8_t param_idx)
{
    lv_obj_set_style_bg_color(guider_ui.mod_label_param1, param_idx == 1 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_label_param2, param_idx == 2 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_label_param3, param_idx == 3 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_label_param4, param_idx == 4 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_label_param5, param_idx == 5 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_label_param6, param_idx == 6 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_label_param7, param_idx == 7 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
}

static void update_mod_params()
{
    g_is_updating_params = 1;
    param_t param;    
    param = mod_params[p_mod->mode][0];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.mod_spinbox_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.mod_label_param3, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.mod_spinbox_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.mod_label_param3, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.mod_spinbox_3, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.mod_spinbox_3, param.min, param.max);
        lv_spinbox_set_value(guider_ui.mod_spinbox_3, param_get_scaled_value(p_mod, &param));
        lv_label_set_text(guider_ui.mod_label_param3, param.label);
    }
    param = mod_params[p_mod->mode][1];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.mod_spinbox_4, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.mod_label_param4, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.mod_spinbox_4, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.mod_label_param4, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.mod_spinbox_4, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.mod_spinbox_4, param.min, param.max);
        lv_spinbox_set_value(guider_ui.mod_spinbox_4, param_get_scaled_value(p_mod, &param));
        lv_label_set_text(guider_ui.mod_label_param4, param.label);
    }
    param = mod_params[p_mod->mode][2];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.mod_spinbox_5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.mod_label_param5, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.mod_spinbox_5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.mod_label_param5, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.mod_spinbox_5, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.mod_spinbox_5, param.min, param.max);
        lv_spinbox_set_value(guider_ui.mod_spinbox_5, param_get_scaled_value(p_mod, &param));
        lv_label_set_text(guider_ui.mod_label_param5, param.label);
    }
    param = mod_params[p_mod->mode][3];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.mod_spinbox_6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.mod_label_param6, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.mod_spinbox_6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.mod_label_param6, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.mod_spinbox_6, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.mod_spinbox_6, param.min, param.max);
        lv_spinbox_set_value(guider_ui.mod_spinbox_6, param_get_scaled_value(p_mod, &param));
        lv_label_set_text(guider_ui.mod_label_param6, param.label);
    }
    param = mod_params[p_mod->mode][4];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.mod_spinbox_7, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.mod_label_param7, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.mod_spinbox_7, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.mod_label_param7, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.mod_spinbox_7, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.mod_spinbox_7, param.min, param.max);
        lv_spinbox_set_value(guider_ui.mod_spinbox_7, param_get_scaled_value(p_mod, &param));
        lv_label_set_text(guider_ui.mod_label_param7, param.label);
    }
    g_is_updating_params = 0;
}

void mod_ch_refresh(void)
{
    update_mod_label_param8();
    update_mod_params();
}


static void mod_btn_menu_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    lv_obj_add_flag(guider_ui.mod_list_wave, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.mod_list_mode, LV_OBJ_FLAG_HIDDEN);
    menu_target_t target = (menu_target_t)(uintptr_t)lv_event_get_user_data(e);
    switch (target) {
        case MENU_GOTO_NORMAL:
            ui_load_scr_animation(&guider_ui, &guider_ui.normal, guider_ui.normal_del, &guider_ui.mod_del, setup_scr_normal, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            normal_ch_refresh();
            break;
        case MENU_GOTO_SCAN:
            ui_load_scr_animation(&guider_ui, &guider_ui.scan, guider_ui.scan_del, &guider_ui.mod_del, setup_scr_scan, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        case MENU_GOTO_PULSE:
            ui_load_scr_animation(&guider_ui, &guider_ui.pulse, guider_ui.pulse_del, &guider_ui.mod_del, setup_scr_pulse, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            pulse_ch_refresh();
            break;
        case MENU_GOTO_HARMONIC:
            ui_load_scr_animation(&guider_ui, &guider_ui.harmonic, guider_ui.harmonic_del, &guider_ui.mod_del, setup_scr_harmonic, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            harmonic_ch_refresh();
            break;
        case MENU_GOTO_USER:
            ui_load_scr_animation(&guider_ui, &guider_ui.user, guider_ui.user_del, &guider_ui.mod_del, setup_scr_user, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            user_ch_refresh();
            break;
        case MENU_GOTO_SYSTEM:
            ui_load_scr_animation(&guider_ui, &guider_ui.system, guider_ui.system_del, &guider_ui.mod_del, setup_scr_system, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        default:
            break;
    }
}

static void mod_btn_direction_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_SHORT_CLICKED && code != LV_EVENT_LONG_PRESSED_REPEAT) return;

    direction_t dir = (direction_t)(uintptr_t)lv_event_get_user_data(e);
    switch (dir) {
        case DIR_LEFT:
            g_is_cursor_move = 1;
            lv_spinbox_step_prev(mod_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_RIGHT:
            g_is_cursor_move = 1;
            lv_spinbox_step_next(mod_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_UP:
            lv_spinbox_increment(mod_spinbox_select);
            break;
        case DIR_DOWN:
            lv_spinbox_decrement(mod_spinbox_select);
            break;
        default:
            break;
    }
}

static void mod_btn_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    uint8_t btn_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    switch (btn_id) {
        case 1: {
            if(mod_btn_page == 0){
                lv_obj_add_flag(guider_ui.mod_list_wave, LV_OBJ_FLAG_HIDDEN);
                if(lv_obj_has_flag(guider_ui.mod_list_mode, LV_OBJ_FLAG_HIDDEN)){
                    lv_obj_clear_flag(guider_ui.mod_list_mode, LV_OBJ_FLAG_HIDDEN);
                }
                else{
                    lv_obj_add_flag(guider_ui.mod_list_mode, LV_OBJ_FLAG_HIDDEN);
                }
            }
            else if(mod_btn_page == 1){
                if(!mod_params[p_mod->mode][1].is_hide){
                    mod_spinbox_select = guider_ui.mod_spinbox_4;
                    update_mod_param_highlight(4);
                }
            }
            break;
        }
        case 2: {
            if(mod_btn_page == 0){
                lv_obj_add_flag(guider_ui.mod_list_mode, LV_OBJ_FLAG_HIDDEN);
                if(lv_obj_has_flag(guider_ui.mod_list_wave, LV_OBJ_FLAG_HIDDEN)){
                    lv_obj_clear_flag(guider_ui.mod_list_wave, LV_OBJ_FLAG_HIDDEN);
                }
                else{
                    lv_obj_add_flag(guider_ui.mod_list_wave, LV_OBJ_FLAG_HIDDEN);
                }
            }
            else if(mod_btn_page == 1){
                if(!mod_params[p_mod->mode][2].is_hide){
                    mod_spinbox_select = guider_ui.mod_spinbox_5;
                    update_mod_param_highlight(5);
                }
            }
            break;
        }
        case 3: {
            if(mod_btn_page == 0){
                mod_spinbox_select = guider_ui.mod_spinbox_1;
                update_mod_param_highlight(1);
            }
            else if(mod_btn_page == 1){
                if(!mod_params[p_mod->mode][3].is_hide){
                    mod_spinbox_select = guider_ui.mod_spinbox_6;
                    update_mod_param_highlight(6);
                }
            }
            break;
        }
        case 4: {
            if(mod_btn_page == 0){
                mod_spinbox_select = guider_ui.mod_spinbox_2;
                update_mod_param_highlight(2);
            }
            else if(mod_btn_page == 1){
                if(!mod_params[p_mod->mode][4].is_hide){
                    mod_spinbox_select = guider_ui.mod_spinbox_7;
                    update_mod_param_highlight(7);
                }
            }
            break;
        }
        case 5: {
            if(mod_btn_page == 0){
                if(!mod_params[p_mod->mode][0].is_hide){
                    mod_spinbox_select = guider_ui.mod_spinbox_3;
                    update_mod_param_highlight(3);
                }
            }
            else if(mod_btn_page == 1){
                
            }
            break;
        }
        case 6: {
            mod_btn_page = (mod_btn_page+1) % MOD_PAGE_NUM;
            update_mod_btn();
            break;
        }
        default:
            break;
    }
}

static void mod_sw_start_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        if(status){
            p_mod->is_modding = 1;
            p_scan->is_running = 0;
            harmonic[dds_ch].enable = 0;   // 调制与谐波互斥
            lv_obj_clear_state(guider_ui.scan_sw_start, LV_STATE_CHECKED);
            mod_update(dds_ch);
        }else{
            p_mod->is_modding = 0;
            mod_update(dds_ch);
        }
        break;
    }
    default:
        break;
    }
}

static void mod_spinbox_event_handler (lv_event_t *e)
{
    if (g_is_updating_params) return;
    if (g_is_cursor_move) return;//仅移动光标，不触发
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_VALUE_CHANGED) return;
    uint8_t spinbox_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); // 1~7
    switch (spinbox_id) {
	    case 1:{
            p_mod->base = lv_spinbox_get_value(guider_ui.mod_spinbox_1) / 10.0;
            mod_update(dds_ch);
            break;
        }
	    case 2:{
            p_mod->carriar = lv_spinbox_get_value(guider_ui.mod_spinbox_2) / 10.0;
            mod_update(dds_ch);
            break;
        }
	    case 3:{
            if(!mod_params[p_mod->mode][0].is_hide){
                param_set_raw_value(p_mod, &mod_params[p_mod->mode][0], lv_spinbox_get_value(guider_ui.mod_spinbox_3));
                mod_update(dds_ch);
            }
            break;
        }
	    case 4:{
            if(!mod_params[p_mod->mode][1].is_hide){
                param_set_raw_value(p_mod, &mod_params[p_mod->mode][1], lv_spinbox_get_value(guider_ui.mod_spinbox_4));
                mod_update(dds_ch);
            }
            break;
        }
	    case 5:{
            if(!mod_params[p_mod->mode][2].is_hide){
                param_set_raw_value(p_mod, &mod_params[p_mod->mode][2], lv_spinbox_get_value(guider_ui.mod_spinbox_5));
                mod_update(dds_ch);
            }
            break;
        }
	    case 6:{
            if(!mod_params[p_mod->mode][3].is_hide){
                param_set_raw_value(p_mod, &mod_params[p_mod->mode][3], lv_spinbox_get_value(guider_ui.mod_spinbox_6));
                mod_update(dds_ch);
            }
            break;
        }
	    case 7:{
            if(!mod_params[p_mod->mode][4].is_hide){
                param_set_raw_value(p_mod, &mod_params[p_mod->mode][4], lv_spinbox_get_value(guider_ui.mod_spinbox_7));
                mod_update(dds_ch);
            }
            break;
        }
        default:break;
	}
}

static void mod_list_mode_item_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) return;

    uint8_t mode_index = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    p_mod->mode = mode_index;
    mod_update(dds_ch);
    strcpy(mod_mode_str, mod_modes[p_mod->mode]);
    update_mod_label_param8();
    update_mod_params();
    lv_obj_add_flag(guider_ui.mod_list_mode, LV_OBJ_FLAG_HIDDEN);
}

static void mod_list_wave_item_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) return;

    uint8_t wave_index = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    p_mod->wave_sel = wave_index;
    mod_update(dds_ch);
    strcpy(mod_wave_str, mod_waves[wave_index]);
    update_mod_label_param8();
    lv_obj_add_flag(guider_ui.mod_list_wave, LV_OBJ_FLAG_HIDDEN);
}


void events_init_mod(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->mod_btn1, mod_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->mod_btn2, mod_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->mod_btn3, mod_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->mod_btn4, mod_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->mod_btn5, mod_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->mod_btn6, mod_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->mod_btn_menu1, mod_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_NORMAL);
    lv_obj_add_event_cb(ui->mod_btn_menu3, mod_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SCAN);
    lv_obj_add_event_cb(ui->mod_btn_menu4, mod_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_PULSE);
    lv_obj_add_event_cb(ui->mod_btn_menu5, mod_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_HARMONIC);
    lv_obj_add_event_cb(ui->mod_btn_menu6, mod_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_USER);
    lv_obj_add_event_cb(ui->mod_btn_menu7, mod_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SYSTEM);
    lv_obj_add_event_cb(ui->mod_btn_left,  mod_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_LEFT);
    lv_obj_add_event_cb(ui->mod_btn_right, mod_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_RIGHT);
    lv_obj_add_event_cb(ui->mod_btn_up,    mod_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_UP);
    lv_obj_add_event_cb(ui->mod_btn_down,  mod_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_DOWN);
    lv_obj_add_event_cb(ui->mod_sw_start,  mod_sw_start_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_spinbox_1, mod_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->mod_spinbox_2, mod_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->mod_spinbox_3, mod_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->mod_spinbox_4, mod_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->mod_spinbox_5, mod_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->mod_spinbox_6, mod_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->mod_spinbox_7, mod_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)7);
    lv_obj_add_event_cb(ui->mod_list_mode_item0, mod_list_mode_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)0);
    lv_obj_add_event_cb(ui->mod_list_mode_item1, mod_list_mode_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->mod_list_mode_item2, mod_list_mode_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->mod_list_wave_item0, mod_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)0);
}
