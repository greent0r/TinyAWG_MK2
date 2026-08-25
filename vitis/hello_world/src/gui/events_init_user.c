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

char user_param8_str[32];

// 底部信息栏: 组号 + 输出状态(与扫描页 param8 用法一致)
static void update_user_label_param8()
{
    sprintf(user_param8_str, "用户波形组:%02u 输出:%s",
            (unsigned)user_wave_sel + 1, user_wave_en[dds_ch] ? "开" : "关");
    lv_label_set_text(guider_ui.user_label_param8, user_param8_str);
}

static void update_user_sw_state()
{
    if (user_wave_en[dds_ch])
        lv_obj_add_state(guider_ui.user_sw_en, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(guider_ui.user_sw_en, LV_STATE_CHECKED);
}

// 通道切换/进入页面时刷新组号与开关状态
void user_ch_refresh(void)
{
    update_user_label_param8();
    update_user_sw_state();
}

static void user_btn1_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    if (lv_obj_has_flag(guider_ui.user_list_wave, LV_OBJ_FLAG_HIDDEN))
        lv_obj_clear_flag(guider_ui.user_list_wave, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(guider_ui.user_list_wave, LV_OBJ_FLAG_HIDDEN);
}

static void user_list_wave_item_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    uint8_t idx = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    if (idx >= USER_WAVE_GROUPS) return;
    user_wave_sel = idx;
    update_user_label_param8();
    lv_obj_add_flag(guider_ui.user_list_wave, LV_OBJ_FLAG_HIDDEN);
    if (user_wave_en[dds_ch]) {
        wave_update(dds_ch);   // 切换组后刷新输出
    }
}

static void user_sw_en_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED) return;
    lv_obj_t *status_obj = lv_event_get_target(e);
    if (lv_obj_has_state(status_obj, LV_STATE_CHECKED)) {
        if (user_wave_start(dds_ch) != 0) {
            // 存储深度超过1M, 禁止开启(与扫频的存储限制一致)
            lv_obj_clear_state(guider_ui.user_sw_en, LV_STATE_CHECKED);
            lv_label_set_text(guider_ui.user_label_param8, "用户波形输出需要存储深度≤1M");
            return;
        }
        update_user_label_param8();
    } else {
        user_wave_stop(dds_ch);
        update_user_label_param8();
    }
}

static void user_btn_menu_event_handler(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    menu_target_t target = (menu_target_t)(uintptr_t)lv_event_get_user_data(e);

    switch (target) {
        case MENU_GOTO_NORMAL:
            ui_load_scr_animation(&guider_ui, &guider_ui.normal, guider_ui.normal_del, &guider_ui.user_del, setup_scr_normal, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            normal_ch_refresh();
            break;
        case MENU_GOTO_MOD:
            ui_load_scr_animation(&guider_ui, &guider_ui.mod, guider_ui.mod_del, &guider_ui.user_del, setup_scr_mod, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            mod_ch_refresh();
            break;
        case MENU_GOTO_SCAN:
            ui_load_scr_animation(&guider_ui, &guider_ui.scan, guider_ui.scan_del, &guider_ui.user_del, setup_scr_scan, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            scan_ch_refresh();
            break;
        case MENU_GOTO_PULSE:
            ui_load_scr_animation(&guider_ui, &guider_ui.pulse, guider_ui.pulse_del, &guider_ui.user_del, setup_scr_pulse, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            pulse_ch_refresh();
            break;
        case MENU_GOTO_HARMONIC:
            ui_load_scr_animation(&guider_ui, &guider_ui.harmonic, guider_ui.harmonic_del, &guider_ui.user_del, setup_scr_harmonic, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            harmonic_ch_refresh();
            break;
        case MENU_GOTO_SYSTEM:
            ui_load_scr_animation(&guider_ui, &guider_ui.system, guider_ui.system_del, &guider_ui.user_del, setup_scr_system, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        default:
            break;
    }
}

void events_init_user (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->user_btn_menu1, user_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_NORMAL);
    lv_obj_add_event_cb(ui->user_btn_menu2, user_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_MOD);
    lv_obj_add_event_cb(ui->user_btn_menu3, user_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SCAN);
    lv_obj_add_event_cb(ui->user_btn_menu4, user_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_PULSE);
    lv_obj_add_event_cb(ui->user_btn_menu5, user_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_HARMONIC);
    lv_obj_add_event_cb(ui->user_btn_menu7, user_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SYSTEM);

    lv_obj_add_event_cb(ui->user_btn1, user_btn1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->user_sw_en, user_sw_en_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->user_list_wave_item0,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)0);
    lv_obj_add_event_cb(ui->user_list_wave_item1,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->user_list_wave_item2,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->user_list_wave_item3,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->user_list_wave_item4,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->user_list_wave_item5,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->user_list_wave_item6,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->user_list_wave_item7,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)7);
    lv_obj_add_event_cb(ui->user_list_wave_item8,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)8);
    lv_obj_add_event_cb(ui->user_list_wave_item9,  user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)9);
    lv_obj_add_event_cb(ui->user_list_wave_item10, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)10);
    lv_obj_add_event_cb(ui->user_list_wave_item11, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)11);
    lv_obj_add_event_cb(ui->user_list_wave_item12, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)12);
    lv_obj_add_event_cb(ui->user_list_wave_item13, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)13);
    lv_obj_add_event_cb(ui->user_list_wave_item14, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)14);
    lv_obj_add_event_cb(ui->user_list_wave_item15, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)15);
    lv_obj_add_event_cb(ui->user_list_wave_item16, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)16);
    lv_obj_add_event_cb(ui->user_list_wave_item17, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)17);
    lv_obj_add_event_cb(ui->user_list_wave_item18, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)18);
    lv_obj_add_event_cb(ui->user_list_wave_item19, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)19);
    lv_obj_add_event_cb(ui->user_list_wave_item20, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)20);
    lv_obj_add_event_cb(ui->user_list_wave_item21, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)21);
    lv_obj_add_event_cb(ui->user_list_wave_item22, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)22);
    lv_obj_add_event_cb(ui->user_list_wave_item23, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)23);
    lv_obj_add_event_cb(ui->user_list_wave_item24, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)24);
    lv_obj_add_event_cb(ui->user_list_wave_item25, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)25);
    lv_obj_add_event_cb(ui->user_list_wave_item26, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)26);
    lv_obj_add_event_cb(ui->user_list_wave_item27, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)27);
    lv_obj_add_event_cb(ui->user_list_wave_item28, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)28);
    lv_obj_add_event_cb(ui->user_list_wave_item29, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)29);
    lv_obj_add_event_cb(ui->user_list_wave_item30, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)30);
    lv_obj_add_event_cb(ui->user_list_wave_item31, user_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)31);
}