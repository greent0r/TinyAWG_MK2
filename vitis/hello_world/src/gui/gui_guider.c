/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "widgets_init.h"
#include "output_ctrl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "gg_external_data.h"
#endif

// 全局按键蜂鸣：LVGL 8 事件不冒泡，需逐个注册到可点击控件
static void ui_buzz_click_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;
    buzz_beep();
}

// 递归为屏幕所有子控件注册点击蜂鸣（label等不可点击控件不会收到CLICKED）
static void ui_buzz_register_children(lv_obj_t *parent)
{
    uint32_t cnt = lv_obj_get_child_cnt(parent);
    for (uint32_t i = 0; i < cnt; i++) {
        lv_obj_t *child = lv_obj_get_child(parent, i);
        lv_obj_add_event_cb(child, ui_buzz_click_cb, LV_EVENT_ALL, NULL);
        ui_buzz_register_children(child);
    }
}

void ui_init_style(lv_style_t * style)
{
    if (style->prop_cnt > 1)
        lv_style_reset(style);
    else
        lv_style_init(style);
}

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del)
{
    lv_obj_t * act_scr = lv_scr_act();

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
    if(auto_del) {
        gg_edata_task_clear(act_scr);
    }
#endif
    if (auto_del && is_clean) {
        lv_obj_clean(act_scr);
    }
    if (new_scr_del) {
        setup_scr(ui);
    }
    /****用户代码****/
    lv_obj_set_parent(guider_ui.sw_ch, *new_scr);
    lv_obj_move_foreground(guider_ui.sw_ch);
    lv_obj_move_foreground(guider_ui.sw_ch_label);
    /***************/
    lv_scr_load_anim(*new_scr, anim_type, time, delay, auto_del);
    *old_scr_del = auto_del;
}

lv_obj_t *ui_list_add_item(lv_obj_t *list, const char *text, uint16_t w, uint16_t h, lv_style_t *style)
{
    lv_obj_t *btn = lv_list_add_btn(list, NULL, text);
    lv_obj_set_width(btn, w);
    lv_obj_set_height(btn, h);
    lv_obj_set_style_text_align(btn, LV_TEXT_ALIGN_CENTER, 0);
    // 禁用长文字横向滚动，超出部分直接截断
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    lv_label_set_long_mode(label, LV_LABEL_LONG_CLIP);
    if (style) {
        lv_obj_add_style(btn, style, LV_PART_MAIN|LV_STATE_DEFAULT);
    }
    return btn;
}

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                  uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb)
{
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, var);
    lv_anim_set_exec_cb(&anim, exec_cb);
    lv_anim_set_values(&anim, start_value, end_value);
    lv_anim_set_time(&anim, duration);
    lv_anim_set_delay(&anim, delay);
    lv_anim_set_path_cb(&anim, path_cb);
    lv_anim_set_repeat_count(&anim, repeat_cnt);
    lv_anim_set_repeat_delay(&anim, repeat_delay);
    lv_anim_set_playback_time(&anim, playback_time);
    lv_anim_set_playback_delay(&anim, playback_delay);
    if (start_cb) {
        lv_anim_set_start_cb(&anim, start_cb);
    }
    if (ready_cb) {
        lv_anim_set_ready_cb(&anim, ready_cb);
    }
    if (deleted_cb) {
        lv_anim_set_deleted_cb(&anim, deleted_cb);
    }
    lv_anim_start(&anim);
}

void init_scr_del_flag(lv_ui *ui)
{

    ui->normal_del = false;
    ui->mod_del = false;
    ui->scan_del = false;
    ui->pulse_del = false;
    ui->harmonic_del = false;
    ui->user_del = false;
    ui->system_del = false;
}

void setup_ui(lv_ui *ui)
{
    init_scr_del_flag(ui);
    init_keyboard(ui);
    setup_scr_normal(ui);
    setup_scr_mod(ui);
    setup_scr_scan(ui);
    setup_scr_pulse(ui);
    setup_scr_harmonic(ui);
    setup_scr_user(ui);
    setup_scr_system(ui);
    // 全局按键蜂鸣：为所有屏幕的全部可点击控件注册（LVGL 8 无事件冒泡）
    ui_buzz_register_children(ui->normal);
    ui_buzz_register_children(ui->mod);
    ui_buzz_register_children(ui->scan);
    ui_buzz_register_children(ui->pulse);
    ui_buzz_register_children(ui->harmonic);
    ui_buzz_register_children(ui->user);
    ui_buzz_register_children(ui->system);
    lv_scr_load(ui->normal);
}

void init_keyboard(lv_ui *ui)
{
    ui->g_kb_top_layer = lv_keyboard_create(lv_layer_top());
    lv_obj_add_event_cb(ui->g_kb_top_layer, kb_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui->g_kb_top_layer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui->g_kb_top_layer, &lv_font_montserrat_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_keyboard_set_mode(ui->g_kb_top_layer, LV_KEYBOARD_MODE_NUMBER);
}
