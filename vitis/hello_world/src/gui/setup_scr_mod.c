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
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_mod(lv_ui *ui)
{
    //Write codes mod
    ui->mod = lv_obj_create(NULL);
    lv_obj_set_size(ui->mod, 480, 320);
    lv_obj_set_scrollbar_mode(ui->mod, LV_SCROLLBAR_MODE_OFF);

    //Write style for mod, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn1
    ui->mod_btn1 = lv_btn_create(ui->mod);
    ui->mod_btn1_label = lv_label_create(ui->mod_btn1);
    lv_label_set_text(ui->mod_btn1_label, "调制类型");
    lv_label_set_long_mode(ui->mod_btn1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn1_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn1, 1, 284);
    lv_obj_set_size(ui->mod_btn1, 79, 35);

    //Write style for mod_btn1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn1, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->mod_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->mod_btn1, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->mod_btn1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn2
    ui->mod_btn2 = lv_btn_create(ui->mod);
    ui->mod_btn2_label = lv_label_create(ui->mod_btn2);
    lv_label_set_text(ui->mod_btn2_label, "调制波形");
    lv_label_set_long_mode(ui->mod_btn2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn2_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn2, 81, 284);
    lv_obj_set_size(ui->mod_btn2, 79, 35);

    //Write style for mod_btn2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn2, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->mod_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->mod_btn2, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->mod_btn2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn3
    ui->mod_btn3 = lv_btn_create(ui->mod);
    ui->mod_btn3_label = lv_label_create(ui->mod_btn3);
    lv_label_set_text(ui->mod_btn3_label, "调制频率");
    lv_label_set_long_mode(ui->mod_btn3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn3_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn3, 161, 284);
    lv_obj_set_size(ui->mod_btn3, 79, 35);

    //Write style for mod_btn3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn3, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->mod_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->mod_btn3, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->mod_btn3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn4
    ui->mod_btn4 = lv_btn_create(ui->mod);
    ui->mod_btn4_label = lv_label_create(ui->mod_btn4);
    lv_label_set_text(ui->mod_btn4_label, "载波频率");
    lv_label_set_long_mode(ui->mod_btn4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn4_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn4, 241, 284);
    lv_obj_set_size(ui->mod_btn4, 79, 35);

    //Write style for mod_btn4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn4, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->mod_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->mod_btn4, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->mod_btn4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn5
    ui->mod_btn5 = lv_btn_create(ui->mod);
    ui->mod_btn5_label = lv_label_create(ui->mod_btn5);
    lv_label_set_text(ui->mod_btn5_label, "参数3");
    lv_label_set_long_mode(ui->mod_btn5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn5_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn5, 321, 284);
    lv_obj_set_size(ui->mod_btn5, 79, 35);

    //Write style for mod_btn5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn5, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->mod_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->mod_btn5, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->mod_btn5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn6
    ui->mod_btn6 = lv_btn_create(ui->mod);
    ui->mod_btn6_label = lv_label_create(ui->mod_btn6);
    lv_label_set_text(ui->mod_btn6_label, "换页");
    lv_label_set_long_mode(ui->mod_btn6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn6_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn6, 401, 284);
    lv_obj_set_size(ui->mod_btn6, 78, 35);

    //Write style for mod_btn6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn6, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->mod_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->mod_btn6, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->mod_btn6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_label_param8
    ui->mod_label_param8 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_param8, "类型:AM 调制波形:正弦波");
    lv_label_set_long_mode(ui->mod_label_param8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_param8, 0, 263);
    lv_obj_set_size(ui->mod_label_param8, 480, 20);

    //Write style for mod_label_param8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_param8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_param8, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_param8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_param8, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_param8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_label_line1
    ui->mod_label_line1 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_line1, "");
    lv_label_set_long_mode(ui->mod_label_line1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_line1, 1, 34);
    lv_obj_set_size(ui->mod_label_line1, 480, 3);

    //Write style for mod_label_line1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_line1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_line1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_line1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_line1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_line1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_menu1
    ui->mod_btn_menu1 = lv_btn_create(ui->mod);
    ui->mod_btn_menu1_label = lv_label_create(ui->mod_btn_menu1);
    lv_label_set_text(ui->mod_btn_menu1_label, " 标准");
    lv_label_set_long_mode(ui->mod_btn_menu1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_menu1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_menu1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_menu1_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_menu1, 1, 1);
    lv_obj_set_size(ui->mod_btn_menu1, 57, 35);

    //Write style for mod_btn_menu1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_menu1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_menu1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_menu1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_menu1, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_menu1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_menu1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_menu1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_menu2
    ui->mod_btn_menu2 = lv_btn_create(ui->mod);
    ui->mod_btn_menu2_label = lv_label_create(ui->mod_btn_menu2);
    lv_label_set_text(ui->mod_btn_menu2_label, " 调制");
    lv_label_set_long_mode(ui->mod_btn_menu2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_menu2_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_menu2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_menu2_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_menu2, 60, 1);
    lv_obj_set_size(ui->mod_btn_menu2, 57, 35);

    //Write style for mod_btn_menu2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_menu2, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_menu2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_menu2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_menu2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_menu2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_menu2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_menu2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_menu3
    ui->mod_btn_menu3 = lv_btn_create(ui->mod);
    ui->mod_btn_menu3_label = lv_label_create(ui->mod_btn_menu3);
    lv_label_set_text(ui->mod_btn_menu3_label, " 扫描");
    lv_label_set_long_mode(ui->mod_btn_menu3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_menu3_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_menu3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_menu3_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_menu3, 119, 1);
    lv_obj_set_size(ui->mod_btn_menu3, 57, 35);

    //Write style for mod_btn_menu3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu3, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_menu3, lv_color_hex(0xbba53e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_menu3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_menu3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_menu3, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_menu3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_menu3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_menu3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_menu4
    ui->mod_btn_menu4 = lv_btn_create(ui->mod);
    ui->mod_btn_menu4_label = lv_label_create(ui->mod_btn_menu4);
    lv_label_set_text(ui->mod_btn_menu4_label, " 脉冲");
    lv_label_set_long_mode(ui->mod_btn_menu4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_menu4_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_menu4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_menu4_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_menu4, 178, 1);
    lv_obj_set_size(ui->mod_btn_menu4, 57, 35);

    //Write style for mod_btn_menu4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu4, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_menu4, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_menu4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_menu4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_menu4, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_menu4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_menu4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_menu4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_menu5
    ui->mod_btn_menu5 = lv_btn_create(ui->mod);
    ui->mod_btn_menu5_label = lv_label_create(ui->mod_btn_menu5);
    lv_label_set_text(ui->mod_btn_menu5_label, " 谐波");
    lv_label_set_long_mode(ui->mod_btn_menu5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_menu5_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_menu5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_menu5_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_menu5, 237, 1);
    lv_obj_set_size(ui->mod_btn_menu5, 57, 35);

    //Write style for mod_btn_menu5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu5, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_menu5, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_menu5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_menu5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_menu5, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_menu5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_menu5, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_menu5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_menu5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_menu5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_menu6
    ui->mod_btn_menu6 = lv_btn_create(ui->mod);
    ui->mod_btn_menu6_label = lv_label_create(ui->mod_btn_menu6);
    lv_label_set_text(ui->mod_btn_menu6_label, " 用户");
    lv_label_set_long_mode(ui->mod_btn_menu6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_menu6_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_menu6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_menu6_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_menu6, 296, 1);
    lv_obj_set_size(ui->mod_btn_menu6, 57, 35);

    //Write style for mod_btn_menu6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu6, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_menu6, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_menu6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_menu6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_menu6, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_menu6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_menu6, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_menu6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_menu6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_menu6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    ui->mod_btn_menu7 = lv_btn_create(ui->mod);
    ui->mod_btn_menu7_label = lv_label_create(ui->mod_btn_menu7);
    lv_label_set_text(ui->mod_btn_menu7_label, " 系统");
    lv_label_set_long_mode(ui->mod_btn_menu7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_menu7_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_menu7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_menu7_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_menu7, 355, 1);
    lv_obj_set_size(ui->mod_btn_menu7, 57, 35);

    //Write style for mod_btn_menu7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu7, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_menu7, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_menu7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_menu7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_menu7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_menu7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_menu7, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_menu7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_menu7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_menu7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_label_param1
    ui->mod_label_param1 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_param1, " 调制                           Hz");
    lv_label_set_long_mode(ui->mod_label_param1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_param1, 5, 45);
    lv_obj_set_size(ui->mod_label_param1, 245, 20);

    //Write style for mod_label_param1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_param1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_param1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_param1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_param1, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_param1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_label_param2
    ui->mod_label_param2 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_param2, " 载波                           Hz");
    lv_label_set_long_mode(ui->mod_label_param2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_param2, 5, 75);
    lv_obj_set_size(ui->mod_label_param2, 245, 20);

    //Write style for mod_label_param2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_param2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_param2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_param2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_param2, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_param2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_label_param3
    ui->mod_label_param3 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_param3, " 深度                           %");
    lv_label_set_long_mode(ui->mod_label_param3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_param3, 5, 105);
    lv_obj_set_size(ui->mod_label_param3, 245, 20);

    //Write style for mod_label_param3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_param3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_param3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_param3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_param3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_param3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_param3, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_param3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_label_param4
    ui->mod_label_param4 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_param4, " 无");
    lv_label_set_long_mode(ui->mod_label_param4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_param4, 5, 135);
    lv_obj_set_size(ui->mod_label_param4, 245, 20);
    lv_obj_add_flag(ui->mod_label_param4, LV_OBJ_FLAG_HIDDEN);

    //Write style for mod_label_param4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_param4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_param4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_param4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_param4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_param4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_param4, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_param4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_label_param5
    ui->mod_label_param5 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_param5, " 无");
    lv_label_set_long_mode(ui->mod_label_param5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_param5, 5, 165);
    lv_obj_set_size(ui->mod_label_param5, 245, 20);
    lv_obj_add_flag(ui->mod_label_param5, LV_OBJ_FLAG_HIDDEN);

    //Write style for mod_label_param5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_param5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_param5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_param5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_param5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_param5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_param5, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_param5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_label_param6
    ui->mod_label_param6 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_param6, " 无");
    lv_label_set_long_mode(ui->mod_label_param6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_param6, 5, 194);
    lv_obj_set_size(ui->mod_label_param6, 230, 20);
    lv_obj_add_flag(ui->mod_label_param6, LV_OBJ_FLAG_HIDDEN);

    //Write style for mod_label_param6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_param6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_param6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_param6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_param6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_param6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_param6, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_param6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_label_param7
    ui->mod_label_param7 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_param7, " 无");
    lv_label_set_long_mode(ui->mod_label_param7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_param7, 6, 225);
    lv_obj_set_size(ui->mod_label_param7, 230, 20);
    lv_obj_add_flag(ui->mod_label_param7, LV_OBJ_FLAG_HIDDEN);

    //Write style for mod_label_param7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_param7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_param7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_param7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_param7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_param7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_param7, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_param7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_right
    ui->mod_btn_right = lv_btn_create(ui->mod);
    ui->mod_btn_right_label = lv_label_create(ui->mod_btn_right);
    lv_label_set_text(ui->mod_btn_right_label, ">");
    lv_label_set_long_mode(ui->mod_btn_right_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_right_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_right, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_right_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_right, 400, 197);
    lv_obj_set_size(ui->mod_btn_right, 64, 35);

    //Write style for mod_btn_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_right, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_right, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_right, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_right, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_right, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_right, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_down
    ui->mod_btn_down = lv_btn_create(ui->mod);
    ui->mod_btn_down_label = lv_label_create(ui->mod_btn_down);
    lv_label_set_text(ui->mod_btn_down_label, "-");
    lv_label_set_long_mode(ui->mod_btn_down_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_down_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_down, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_down_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_down, 327, 224);
    lv_obj_set_size(ui->mod_btn_down, 64, 35);

    //Write style for mod_btn_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_down, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_down, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_down, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_down, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_down, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_down, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_left
    ui->mod_btn_left = lv_btn_create(ui->mod);
    ui->mod_btn_left_label = lv_label_create(ui->mod_btn_left);
    lv_label_set_text(ui->mod_btn_left_label, "<");
    lv_label_set_long_mode(ui->mod_btn_left_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_left_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_left, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_left_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_left, 254, 197);
    lv_obj_set_size(ui->mod_btn_left, 64, 35);

    //Write style for mod_btn_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_left, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_left, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_left, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_left, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_left, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_left, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_btn_up
    ui->mod_btn_up = lv_btn_create(ui->mod);
    ui->mod_btn_up_label = lv_label_create(ui->mod_btn_up);
    lv_label_set_text(ui->mod_btn_up_label, "+");
    lv_label_set_long_mode(ui->mod_btn_up_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_up_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_up, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_up_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_up, 327, 173);
    lv_obj_set_size(ui->mod_btn_up, 64, 35);

    //Write style for mod_btn_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_up, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_up, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_up, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_up, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_up, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_up, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_sw_start
    ui->mod_sw_start = lv_switch_create(ui->mod);
    lv_obj_set_pos(ui->mod_sw_start, 302, 40);
    lv_obj_set_size(ui->mod_sw_start, 60, 30);

    //Write style for mod_sw_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_sw_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_sw_start, lv_color_hex(0x0c0d0a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_sw_start, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_sw_start, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->mod_sw_start, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->mod_sw_start, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->mod_sw_start, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_sw_start, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_sw_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for mod_sw_start, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->mod_sw_start, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->mod_sw_start, lv_color_hex(0x267e48), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->mod_sw_start, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->mod_sw_start, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for mod_sw_start, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_sw_start, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_sw_start, lv_color_hex(0xe06105), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_sw_start, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_sw_start, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_sw_start, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes mod_label_start
    ui->mod_label_start = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_start, "开启");
    lv_label_set_long_mode(ui->mod_label_start, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_start, 258, 45);
    lv_obj_set_size(ui->mod_label_start, 36, 20);

    //Write style for mod_label_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_start, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_start, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_start, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_label_start, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_label_start, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_list_mode
    ui->mod_list_mode = lv_list_create(ui->mod);
    lv_obj_set_pos(ui->mod_list_mode, 20, 40);
    lv_obj_set_size(ui->mod_list_mode, 440, 220);
    lv_obj_set_scrollbar_mode(ui->mod_list_mode, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui->mod_list_mode, LV_DIR_VER);
    lv_obj_add_flag(ui->mod_list_mode, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_layout(ui->mod_list_mode, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(ui->mod_list_mode, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui->mod_list_mode, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(ui->mod_list_mode, 8, 0);
    lv_obj_set_style_pad_column(ui->mod_list_mode, 8, 0);
    lv_obj_set_style_pad_left(ui->mod_list_mode, 4, 0);
    lv_obj_set_style_pad_top(ui->mod_list_mode, 4, 0);
    lv_obj_set_style_pad_right(ui->mod_list_mode, 4, 0);
    lv_obj_set_style_pad_bottom(ui->mod_list_mode, 4, 0);

    //Write style state: LV_STATE_DEFAULT for &style_mod_list_mode_main_main_default
    static lv_style_t style_mod_list_mode_main_main_default;
    ui_init_style(&style_mod_list_mode_main_main_default);

    lv_style_set_pad_top(&style_mod_list_mode_main_main_default, 5);
    lv_style_set_pad_left(&style_mod_list_mode_main_main_default, 5);
    lv_style_set_pad_right(&style_mod_list_mode_main_main_default, 5);
    lv_style_set_pad_bottom(&style_mod_list_mode_main_main_default, 5);
    lv_style_set_bg_opa(&style_mod_list_mode_main_main_default, 255);
    lv_style_set_bg_color(&style_mod_list_mode_main_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_mod_list_mode_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_mod_list_mode_main_main_default, 2);
    lv_style_set_border_opa(&style_mod_list_mode_main_main_default, 255);
    lv_style_set_border_color(&style_mod_list_mode_main_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_mod_list_mode_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_mod_list_mode_main_main_default, 3);
    lv_style_set_shadow_width(&style_mod_list_mode_main_main_default, 0);
    lv_obj_add_style(ui->mod_list_mode, &style_mod_list_mode_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_mod_list_mode_extra_texts_main_default
    static lv_style_t style_mod_list_mode_extra_texts_main_default;
    ui_init_style(&style_mod_list_mode_extra_texts_main_default);

    lv_style_set_pad_top(&style_mod_list_mode_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_mod_list_mode_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_mod_list_mode_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_mod_list_mode_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_mod_list_mode_extra_texts_main_default, 2);
    lv_style_set_border_opa(&style_mod_list_mode_extra_texts_main_default, 255);
    lv_style_set_border_color(&style_mod_list_mode_extra_texts_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_mod_list_mode_extra_texts_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_mod_list_mode_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_mod_list_mode_extra_texts_main_default, &lv_font_ZiHunDaHei_18);
    lv_style_set_text_opa(&style_mod_list_mode_extra_texts_main_default, 255);
    lv_style_set_radius(&style_mod_list_mode_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_mod_list_mode_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_mod_list_mode_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_mod_list_mode_extra_texts_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_mod_list_mode_extra_texts_main_default, LV_GRAD_DIR_NONE);
    ui->mod_list_mode_item0 = ui_list_add_item(ui->mod_list_mode, "AM", 100, 28, &style_mod_list_mode_extra_texts_main_default);
    ui->mod_list_mode_item1 = ui_list_add_item(ui->mod_list_mode, "FM", 100, 28, &style_mod_list_mode_extra_texts_main_default);
    ui->mod_list_mode_item2 = ui_list_add_item(ui->mod_list_mode, "PM", 100, 28, &style_mod_list_mode_extra_texts_main_default);
    
    
    //Write codes mod_list_wave
    ui->mod_list_wave = lv_list_create(ui->mod);
    lv_obj_set_pos(ui->mod_list_wave, 20, 40);
    lv_obj_set_size(ui->mod_list_wave, 440, 220);
    lv_obj_set_scrollbar_mode(ui->mod_list_wave, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui->mod_list_wave, LV_DIR_VER);
    lv_obj_add_flag(ui->mod_list_wave, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_layout(ui->mod_list_wave, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(ui->mod_list_wave, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui->mod_list_wave, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(ui->mod_list_wave, 8, 0);
    lv_obj_set_style_pad_column(ui->mod_list_wave, 8, 0);
    lv_obj_set_style_pad_left(ui->mod_list_wave, 4, 0);
    lv_obj_set_style_pad_top(ui->mod_list_wave, 4, 0);
    lv_obj_set_style_pad_right(ui->mod_list_wave, 4, 0);
    lv_obj_set_style_pad_bottom(ui->mod_list_wave, 4, 0);



    //Write style state: LV_STATE_DEFAULT for &style_mod_list_wave_main_main_default
    static lv_style_t style_mod_list_wave_main_main_default;
    ui_init_style(&style_mod_list_wave_main_main_default);

    lv_style_set_pad_top(&style_mod_list_wave_main_main_default, 5);
    lv_style_set_pad_left(&style_mod_list_wave_main_main_default, 5);
    lv_style_set_pad_right(&style_mod_list_wave_main_main_default, 5);
    lv_style_set_pad_bottom(&style_mod_list_wave_main_main_default, 5);
    lv_style_set_bg_opa(&style_mod_list_wave_main_main_default, 255);
    lv_style_set_bg_color(&style_mod_list_wave_main_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_mod_list_wave_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_mod_list_wave_main_main_default, 2);
    lv_style_set_border_opa(&style_mod_list_wave_main_main_default, 255);
    lv_style_set_border_color(&style_mod_list_wave_main_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_mod_list_wave_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_mod_list_wave_main_main_default, 3);
    lv_style_set_shadow_width(&style_mod_list_wave_main_main_default, 0);
    lv_obj_add_style(ui->mod_list_wave, &style_mod_list_wave_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_mod_list_wave_extra_texts_main_default
    static lv_style_t style_mod_list_wave_extra_texts_main_default;
    ui_init_style(&style_mod_list_wave_extra_texts_main_default);

    lv_style_set_pad_top(&style_mod_list_wave_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_mod_list_wave_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_mod_list_wave_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_mod_list_wave_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_mod_list_wave_extra_texts_main_default, 2);
    lv_style_set_border_opa(&style_mod_list_wave_extra_texts_main_default, 255);
    lv_style_set_border_color(&style_mod_list_wave_extra_texts_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_mod_list_wave_extra_texts_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_mod_list_wave_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_mod_list_wave_extra_texts_main_default, &lv_font_ZiHunDaHei_18);
    lv_style_set_text_opa(&style_mod_list_wave_extra_texts_main_default, 255);
    lv_style_set_radius(&style_mod_list_wave_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_mod_list_wave_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_mod_list_wave_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_mod_list_wave_extra_texts_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_mod_list_wave_extra_texts_main_default, LV_GRAD_DIR_NONE);
    ui->mod_list_wave_item0 = ui_list_add_item(ui->mod_list_wave, "正弦波", 100, 28, &style_mod_list_wave_extra_texts_main_default);

    //Write codes mod_spinbox_1
    ui->mod_spinbox_1 = lv_spinbox_create(ui->mod);
    lv_obj_set_pos(ui->mod_spinbox_1, 60, 45);
    lv_obj_set_width(ui->mod_spinbox_1, 150);
    lv_obj_set_height(ui->mod_spinbox_1, 50);
    lv_spinbox_set_digit_format(ui->mod_spinbox_1, 9, 8);
    lv_spinbox_set_range(ui->mod_spinbox_1, 0, 999999999);
    

    //Write style for mod_spinbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->mod_spinbox_1, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->mod_spinbox_1, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_1, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_spinbox_1, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_spinbox_1, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes mod_spinbox_2
    ui->mod_spinbox_2 = lv_spinbox_create(ui->mod);
    lv_obj_set_pos(ui->mod_spinbox_2, 60, 75);
    lv_obj_set_width(ui->mod_spinbox_2, 150);
    lv_obj_set_height(ui->mod_spinbox_2, 50);
    lv_spinbox_set_digit_format(ui->mod_spinbox_2, 9, 8);
    lv_spinbox_set_range(ui->mod_spinbox_2, 0, 999999999);

    //Write style for mod_spinbox_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_spinbox_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->mod_spinbox_2, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->mod_spinbox_2, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_2, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_2, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_spinbox_2, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_spinbox_2, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_spinbox_2, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes mod_spinbox_3
    ui->mod_spinbox_3 = lv_spinbox_create(ui->mod);
    lv_obj_set_pos(ui->mod_spinbox_3, 60, 105);
    lv_obj_set_width(ui->mod_spinbox_3, 150);
    lv_obj_set_height(ui->mod_spinbox_3, 50);
    lv_spinbox_set_digit_format(ui->mod_spinbox_3, 4, 3);
    lv_spinbox_set_range(ui->mod_spinbox_3, 0, 1000);

    //Write style for mod_spinbox_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_spinbox_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->mod_spinbox_3, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->mod_spinbox_3, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_3, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_3, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_spinbox_3, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_spinbox_3, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_spinbox_3, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes mod_spinbox_4
    ui->mod_spinbox_4 = lv_spinbox_create(ui->mod);
    lv_obj_set_pos(ui->mod_spinbox_4, 60, 135);
    lv_obj_set_width(ui->mod_spinbox_4, 150);
    lv_obj_set_height(ui->mod_spinbox_4, 50);
    lv_spinbox_set_digit_format(ui->mod_spinbox_4, 5, 3);
    lv_spinbox_set_range(ui->mod_spinbox_4, 0, 36000);
    lv_obj_add_flag(ui->mod_spinbox_4, LV_OBJ_FLAG_HIDDEN);

    //Write style for mod_spinbox_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_spinbox_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->mod_spinbox_4, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->mod_spinbox_4, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_4, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_4, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_spinbox_4, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_spinbox_4, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_spinbox_4, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes mod_spinbox_5
    ui->mod_spinbox_5 = lv_spinbox_create(ui->mod);
    lv_obj_set_pos(ui->mod_spinbox_5, 60, 165);
    lv_obj_set_width(ui->mod_spinbox_5, 150);
    lv_obj_set_height(ui->mod_spinbox_5, 50);
    lv_spinbox_set_digit_format(ui->mod_spinbox_5, 5, 2);
    lv_spinbox_set_range(ui->mod_spinbox_5, 0, 10000);
    lv_obj_add_flag(ui->mod_spinbox_5, LV_OBJ_FLAG_HIDDEN);

    //Write style for mod_spinbox_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_spinbox_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->mod_spinbox_5, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->mod_spinbox_5, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_5, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_5, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_spinbox_5, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_spinbox_5, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_spinbox_5, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes mod_spinbox_6
    ui->mod_spinbox_6 = lv_spinbox_create(ui->mod);
    lv_obj_set_pos(ui->mod_spinbox_6, 60, 195);
    lv_obj_set_width(ui->mod_spinbox_6, 150);
    lv_obj_set_height(ui->mod_spinbox_6, 50);
    lv_spinbox_set_digit_format(ui->mod_spinbox_6, 5, 2);
    lv_spinbox_set_range(ui->mod_spinbox_6, 0, 10000);
    lv_obj_add_flag(ui->mod_spinbox_6, LV_OBJ_FLAG_HIDDEN);

    //Write style for mod_spinbox_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_spinbox_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->mod_spinbox_6, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->mod_spinbox_6, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_6, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_6, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_spinbox_6, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_spinbox_6, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_spinbox_6, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes mod_spinbox_7
    ui->mod_spinbox_7 = lv_spinbox_create(ui->mod);
    lv_obj_set_pos(ui->mod_spinbox_7, 60, 225);
    lv_obj_set_width(ui->mod_spinbox_7, 150);
    lv_obj_set_height(ui->mod_spinbox_7, 50);
    lv_spinbox_set_digit_format(ui->mod_spinbox_7, 5, 2);
    lv_spinbox_set_range(ui->mod_spinbox_7, 0, 10000);
    lv_obj_add_flag(ui->mod_spinbox_7, LV_OBJ_FLAG_HIDDEN);

    //Write style for mod_spinbox_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_spinbox_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->mod_spinbox_7, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->mod_spinbox_7, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_spinbox_7, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_spinbox_7, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_spinbox_7, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_spinbox_7, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_spinbox_7, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //The custom code of mod.
    lv_obj_clear_flag(ui->mod, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(ui->mod_spinbox_1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(ui->mod_spinbox_2, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(ui->mod_spinbox_3, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(ui->mod_spinbox_4, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(ui->mod_spinbox_5, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(ui->mod_spinbox_6, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(ui->mod_spinbox_7, LV_OBJ_FLAG_SCROLLABLE);
    lv_spinbox_step_prev(ui->mod_spinbox_1);
    lv_spinbox_step_prev(ui->mod_spinbox_2);
    lv_spinbox_step_prev(ui->mod_spinbox_3);
    lv_spinbox_step_prev(ui->mod_spinbox_4);
    lv_spinbox_step_prev(ui->mod_spinbox_5);
    lv_spinbox_step_prev(ui->mod_spinbox_6);
    lv_spinbox_step_prev(ui->mod_spinbox_7);
    lv_spinbox_set_value(ui->mod_spinbox_1, 10000);
    lv_spinbox_set_value(ui->mod_spinbox_2, 10000000);
    lv_spinbox_set_value(ui->mod_spinbox_3, 500);

    //Update current screen layout.
    lv_obj_update_layout(ui->mod);

    //Init events for screen.
    lv_obj_move_foreground(ui->mod_list_mode);
    lv_obj_move_foreground(ui->mod_list_wave);
    events_init_mod(ui);
}
