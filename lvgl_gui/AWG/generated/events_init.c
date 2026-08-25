/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void normal_btn1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        lv_obj_clear_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void normal_btn2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_btn3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_btn4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_btn5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_btn6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_btn_menu2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.mod, guider_ui.mod_del, &guider_ui.normal_del, setup_scr_mod, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void normal_btn_menu3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.system, guider_ui.system_del, &guider_ui.normal_del, setup_scr_system, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void normal_btn_menu4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_label_param1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_btn_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_btn_up_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_btn_down_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_btn_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void normal_list_wave_item0_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        lv_obj_add_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void normal_list_wave_item1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        lv_obj_add_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void normal_list_wave_item2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        lv_obj_add_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void normal_list_wave_item3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        lv_obj_add_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_normal (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->normal_btn1, normal_btn1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn2, normal_btn2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn3, normal_btn3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn4, normal_btn4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn5, normal_btn5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn6, normal_btn6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn_menu2, normal_btn_menu2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn_menu3, normal_btn_menu3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn_menu4, normal_btn_menu4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_label_param1, normal_label_param1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn_left, normal_btn_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn_up, normal_btn_up_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn_down, normal_btn_down_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_btn_right, normal_btn_right_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_list_wave_item0, normal_list_wave_item0_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_list_wave_item1, normal_list_wave_item1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_list_wave_item2, normal_list_wave_item2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->normal_list_wave_item3, normal_list_wave_item3_event_handler, LV_EVENT_ALL, ui);
}

static void mod_btn1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {

        break;
    }
    default:
        break;
    }
}

static void mod_btn2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {

        break;
    }
    default:
        break;
    }
}

static void mod_btn3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {

        break;
    }
    default:
        break;
    }
}

static void mod_btn4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {

        break;
    }
    default:
        break;
    }
}

static void mod_btn5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {

        break;
    }
    default:
        break;
    }
}

static void mod_btn6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {

        break;
    }
    default:
        break;
    }
}

static void mod_btn_menu1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.normal, guider_ui.normal_del, &guider_ui.mod_del, setup_scr_normal, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void mod_btn_menu3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scan, guider_ui.scan_del, &guider_ui.mod_del, setup_scr_scan, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void mod_btn_menu4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.system, guider_ui.system_del, &guider_ui.mod_del, setup_scr_system, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void mod_btn_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {

        break;
    }
    default:
        break;
    }
}

static void mod_btn_down_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {

        break;
    }
    default:
        break;
    }
}

static void mod_btn_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    default:
        break;
    }
}

static void mod_btn_up_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    default:
        break;
    }
}

void events_init_mod (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->mod_btn1, mod_btn1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn2, mod_btn2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn3, mod_btn3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn4, mod_btn4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn5, mod_btn5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn6, mod_btn6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn_menu1, mod_btn_menu1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn_menu3, mod_btn_menu3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn_menu4, mod_btn_menu4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn_right, mod_btn_right_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn_down, mod_btn_down_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn_left, mod_btn_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->mod_btn_up, mod_btn_up_event_handler, LV_EVENT_ALL, ui);
}

static void scan_btn1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        lv_obj_clear_flag(guider_ui.scan_list_mode, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scan_btn2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void scan_btn3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void scan_btn4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void scan_btn5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void scan_btn6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        break;
    }
    default:
        break;
    }
}

static void scan_btn_menu1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.normal, guider_ui.normal_del, &guider_ui.scan_del, setup_scr_normal, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void scan_btn_menu2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.mod, guider_ui.mod_del, &guider_ui.scan_del, setup_scr_mod, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void scan_btn_menu4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.system, guider_ui.system_del, &guider_ui.scan_del, setup_scr_system, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void scan_sw_start_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;

        break;
    }
    default:
        break;
    }
}

static void scan_btn_right_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    default:
        break;
    }
}

static void scan_btn_down_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    default:
        break;
    }
}

static void scan_btn_left_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

        break;
    }
    default:
        break;
    }
}

static void scan_btn_up_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SHORT_CLICKED:
    {

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

        break;
    }
    default:
        break;
    }
}

static void scan_list_mode_item0_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        lv_obj_add_flag(guider_ui.scan_list_mode, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scan_list_mode_item1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        lv_obj_add_flag(guider_ui.scan_list_mode, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_scan (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scan_btn1, scan_btn1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn2, scan_btn2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn3, scan_btn3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn4, scan_btn4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn5, scan_btn5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn6, scan_btn6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn_menu1, scan_btn_menu1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn_menu2, scan_btn_menu2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn_menu4, scan_btn_menu4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_sw_start, scan_sw_start_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn_right, scan_btn_right_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn_down, scan_btn_down_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn_left, scan_btn_left_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_btn_up, scan_btn_up_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_sw_loop, scan_sw_loop_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_list_mode_item0, scan_list_mode_item0_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scan_list_mode_item1, scan_list_mode_item1_event_handler, LV_EVENT_ALL, ui);
}

static void system_btn_menu1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.normal, guider_ui.normal_del, &guider_ui.system_del, setup_scr_normal, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void system_btn_menu2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.mod, guider_ui.mod_del, &guider_ui.system_del, setup_scr_mod, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void system_btn_menu3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scan, guider_ui.scan_del, &guider_ui.system_del, setup_scr_scan, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void system_sw_oe_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;

        break;
    }
    default:
        break;
    }
}

void events_init_system (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->system_btn_menu1, system_btn_menu1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->system_btn_menu2, system_btn_menu2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->system_btn_menu3, system_btn_menu3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->system_sw_oe, system_sw_oe_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
