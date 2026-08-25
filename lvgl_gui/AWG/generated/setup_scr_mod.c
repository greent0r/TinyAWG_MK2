/*
* Copyright 2026 NXP
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
    lv_label_set_text(ui->mod_btn1_label, "");
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
    lv_obj_set_style_border_color(ui->mod_btn1, lv_color_hex(0x8cecb4), LV_PART_MAIN|LV_STATE_DEFAULT);
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
    lv_label_set_text(ui->mod_btn2_label, "");
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
    lv_label_set_text(ui->mod_btn3_label, "");
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
    lv_label_set_text(ui->mod_btn4_label, "");
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
    lv_label_set_text(ui->mod_btn5_label, "");
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
    lv_label_set_text(ui->mod_btn6_label, "");
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
    lv_label_set_text(ui->mod_label_param8, "\n");
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
    lv_obj_set_style_pad_top(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

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
    lv_obj_set_size(ui->mod_btn_menu1, 75, 35);

    //Write style for mod_btn_menu1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu1, 52, LV_PART_MAIN|LV_STATE_DEFAULT);
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
    lv_obj_set_pos(ui->mod_btn_menu2, 78, 1);
    lv_obj_set_size(ui->mod_btn_menu2, 75, 35);

    //Write style for mod_btn_menu2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_menu2, lv_color_hex(0xbba53e), LV_PART_MAIN|LV_STATE_DEFAULT);
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
    lv_label_set_text(ui->mod_btn_menu3_label, "  扫描");
    lv_label_set_long_mode(ui->mod_btn_menu3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_menu3_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_menu3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_menu3_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_menu3, 155, 1);
    lv_obj_set_size(ui->mod_btn_menu3, 75, 35);

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
    lv_label_set_text(ui->mod_btn_menu4_label, "  系统");
    lv_label_set_long_mode(ui->mod_btn_menu4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_menu4_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_menu4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_menu4_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_menu4, 232, 1);
    lv_obj_set_size(ui->mod_btn_menu4, 75, 35);

    //Write style for mod_btn_menu4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_menu4, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_menu4, lv_color_hex(0xbba53e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_menu4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_menu4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_menu4, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_menu4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_menu4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_menu4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

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

    //Write codes mod_btn_1
    ui->mod_btn_1 = lv_btn_create(ui->mod);
    ui->mod_btn_1_label = lv_label_create(ui->mod_btn_1);
    lv_label_set_text(ui->mod_btn_1_label, "  ");
    lv_label_set_long_mode(ui->mod_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->mod_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->mod_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->mod_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->mod_btn_1, 309, 1);
    lv_obj_set_size(ui->mod_btn_1, 75, 35);

    //Write style for mod_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_btn_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_btn_1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_btn_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_btn_1, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_btn_1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes mod_sw_1
    ui->mod_sw_1 = lv_switch_create(ui->mod);
    lv_obj_set_pos(ui->mod_sw_1, 419, 2);
    lv_obj_set_size(ui->mod_sw_1, 60, 30);

    //Write style for mod_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_sw_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_sw_1, lv_color_hex(0x0c0d0a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_sw_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_sw_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->mod_sw_1, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->mod_sw_1, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->mod_sw_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_sw_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for mod_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->mod_sw_1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->mod_sw_1, lv_color_hex(0x267e48), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->mod_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->mod_sw_1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for mod_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->mod_sw_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->mod_sw_1, lv_color_hex(0xe06105), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->mod_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->mod_sw_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_sw_1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes mod_label_1
    ui->mod_label_1 = lv_label_create(ui->mod);
    lv_label_set_text(ui->mod_label_1, "1    2");
    lv_label_set_long_mode(ui->mod_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->mod_label_1, 419, 8);
    lv_obj_set_size(ui->mod_label_1, 60, 18);

    //Write style for mod_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->mod_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->mod_label_1, &lv_font_ZiHunDaHei_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->mod_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->mod_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->mod_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of mod.
    lv_obj_clear_flag(ui->mod, LV_OBJ_FLAG_SCROLLABLE);

    //Update current screen layout.
    lv_obj_update_layout(ui->mod);

    //Init events for screen.
    events_init_mod(ui);
}
