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


static void system_btn_menu_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    menu_target_t target = (menu_target_t)(uintptr_t)lv_event_get_user_data(e);

    switch (target) {
        case MENU_GOTO_NORMAL:
            ui_load_scr_animation(&guider_ui, &guider_ui.normal, guider_ui.normal_del, &guider_ui.system_del, setup_scr_normal, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        case MENU_GOTO_MOD:
            ui_load_scr_animation(&guider_ui, &guider_ui.mod, guider_ui.mod_del, &guider_ui.system_del, setup_scr_mod, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        case MENU_GOTO_SCAN:
            ui_load_scr_animation(&guider_ui, &guider_ui.scan, guider_ui.scan_del, &guider_ui.system_del, setup_scr_scan, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        case MENU_GOTO_PULSE:
            ui_load_scr_animation(&guider_ui, &guider_ui.pulse, guider_ui.pulse_del, &guider_ui.system_del, setup_scr_pulse, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            pulse_ch_refresh();
            break;
        case MENU_GOTO_HARMONIC:
            ui_load_scr_animation(&guider_ui, &guider_ui.harmonic, guider_ui.harmonic_del, &guider_ui.system_del, setup_scr_harmonic, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            harmonic_ch_refresh();
            break;
        case MENU_GOTO_USER:
            ui_load_scr_animation(&guider_ui, &guider_ui.user, guider_ui.user_del, &guider_ui.system_del, setup_scr_user, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            user_ch_refresh();
            break;
        default:
            break;
    }
}

static void system_sw_oe_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    uint8_t sw_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); 
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        if(status){
            if(sw_id == 0) DDS0_ON;
            else           DDS1_ON;
        }
        else{
            if(sw_id == 0) DDS0_OFF;
            else           DDS1_OFF;
        }
        break;
    }
    default:
        break;
    }
}

static void system_dropdown_rom_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        int16_t option = lv_dropdown_get_selected(obj);
        if (option != 0) {          // 切到 ddr_dds: 扫频仅32K模式, 停止所有扫频
            scan[0].is_running = 0;
            scan[1].is_running = 0;
        }
        max_rom_bits = option + 16;           // 选项0(32K)→16: bram_dds; 其余→ddr_dds
        dds_sel = (option != 0) ? 1 : 0;      // 双通道同时切换存储模式
        if (max_rom_bits > USER_WAVE_MAX_BITS) {  // 存储深度超过1M: 用户波形不可输出
            user_wave_stop(0);
            user_wave_stop(1);
        }
        mod_update(dds_ch);                   // 切换分辨率/DDS后刷新波形并播放
    }
}

static void system_sw_buzz_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED) return;
    lv_obj_t *status_obj = lv_event_get_target(e);
    buzz_enable = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? 1 : 0;
    if (buzz_enable) buzz_beep();   // 开启时响一声反馈
}

static void system_btn_sync_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    DDS_sync_channels();   // 双通道同步重启，输出相位对齐
}

void events_init_system (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->system_btn_menu1, system_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_NORMAL);
    lv_obj_add_event_cb(ui->system_btn_menu2, system_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_MOD);
    lv_obj_add_event_cb(ui->system_btn_menu3, system_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SCAN);
    lv_obj_add_event_cb(ui->system_btn_menu4, system_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_PULSE);
    lv_obj_add_event_cb(ui->system_btn_menu5, system_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_HARMONIC);
    lv_obj_add_event_cb(ui->system_btn_menu6, system_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_USER);
    lv_obj_add_event_cb(ui->system_sw_oe, system_sw_oe_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)0);
    lv_obj_add_event_cb(ui->system_sw_oe1, system_sw_oe_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->system_sw_buzz, system_sw_buzz_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->system_dropdown_rom, system_dropdown_rom_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->system_btn1, system_btn_sync_event_handler, LV_EVENT_ALL, NULL);
}
