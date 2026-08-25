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



void setup_scr_normal(lv_ui *ui)
{
    //Write codes normal
    ui->normal = lv_obj_create(NULL);
    lv_obj_set_size(ui->normal, 480, 320);
    lv_obj_set_scrollbar_mode(ui->normal, LV_SCROLLBAR_MODE_OFF);

    //Write style for normal, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn1
    ui->normal_btn1 = lv_btn_create(ui->normal);
    ui->normal_btn1_label = lv_label_create(ui->normal_btn1);
    lv_label_set_text(ui->normal_btn1_label, "波形");
    lv_label_set_long_mode(ui->normal_btn1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn1_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn1, 1, 284);
    lv_obj_set_size(ui->normal_btn1, 79, 35);

    //Write style for normal_btn1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn1, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->normal_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->normal_btn1, lv_color_hex(0x8cecb4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->normal_btn1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn2
    ui->normal_btn2 = lv_btn_create(ui->normal);
    ui->normal_btn2_label = lv_label_create(ui->normal_btn2);
    lv_label_set_text(ui->normal_btn2_label, "频率");
    lv_label_set_long_mode(ui->normal_btn2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn2_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn2, 81, 284);
    lv_obj_set_size(ui->normal_btn2, 79, 35);

    //Write style for normal_btn2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn2, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->normal_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->normal_btn2, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->normal_btn2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn3
    ui->normal_btn3 = lv_btn_create(ui->normal);
    ui->normal_btn3_label = lv_label_create(ui->normal_btn3);
    lv_label_set_text(ui->normal_btn3_label, "幅度");
    lv_label_set_long_mode(ui->normal_btn3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn3_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn3, 161, 284);
    lv_obj_set_size(ui->normal_btn3, 79, 35);

    //Write style for normal_btn3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn3, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->normal_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->normal_btn3, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->normal_btn3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn4
    ui->normal_btn4 = lv_btn_create(ui->normal);
    ui->normal_btn4_label = lv_label_create(ui->normal_btn4);
    lv_label_set_text(ui->normal_btn4_label, "偏置");
    lv_label_set_long_mode(ui->normal_btn4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn4_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn4, 241, 284);
    lv_obj_set_size(ui->normal_btn4, 79, 35);

    //Write style for normal_btn4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn4, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->normal_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->normal_btn4, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->normal_btn4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn5
    ui->normal_btn5 = lv_btn_create(ui->normal);
    ui->normal_btn5_label = lv_label_create(ui->normal_btn5);
    lv_label_set_text(ui->normal_btn5_label, "相位");
    lv_label_set_long_mode(ui->normal_btn5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn5_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn5, 321, 284);
    lv_obj_set_size(ui->normal_btn5, 79, 35);

    //Write style for normal_btn5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn5, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->normal_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->normal_btn5, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->normal_btn5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn6
    ui->normal_btn6 = lv_btn_create(ui->normal);
    ui->normal_btn6_label = lv_label_create(ui->normal_btn6);
    lv_label_set_text(ui->normal_btn6_label, "换页");
    lv_label_set_long_mode(ui->normal_btn6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn6_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn6, 401, 284);
    lv_obj_set_size(ui->normal_btn6, 78, 35);

    //Write style for normal_btn6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn6, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->normal_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->normal_btn6, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->normal_btn6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for normal_btn6, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
    lv_obj_set_style_bg_opa(ui->normal_btn6, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->normal_btn6, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(ui->normal_btn6, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_radius(ui->normal_btn6, 5, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->normal_btn6, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui->normal_btn6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui->normal_btn6, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_text_opa(ui->normal_btn6, 255, LV_PART_MAIN|LV_STATE_FOCUSED);

    //Write style for normal_btn6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->normal_btn6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->normal_btn6, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->normal_btn6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->normal_btn6, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->normal_btn6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->normal_btn6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->normal_btn6, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->normal_btn6, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes normal_label_line1
    ui->normal_label_line1 = lv_label_create(ui->normal);
    lv_label_set_text(ui->normal_label_line1, "");
    lv_label_set_long_mode(ui->normal_label_line1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->normal_label_line1, 1, 34);
    lv_obj_set_size(ui->normal_label_line1, 480, 3);

    //Write style for normal_label_line1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->normal_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_label_line1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_label_line1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->normal_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->normal_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_label_line1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->normal_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_label_line1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_label_line1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->normal_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->normal_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->normal_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->normal_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn_menu1
    ui->normal_btn_menu1 = lv_btn_create(ui->normal);
    ui->normal_btn_menu1_label = lv_label_create(ui->normal_btn_menu1);
    lv_label_set_text(ui->normal_btn_menu1_label, " 普通");
    lv_label_set_long_mode(ui->normal_btn_menu1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn_menu1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn_menu1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn_menu1_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn_menu1, 1, 1);
    lv_obj_set_size(ui->normal_btn_menu1, 90, 35);

    //Write style for normal_btn_menu1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn_menu1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn_menu1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn_menu1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn_menu1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn_menu1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn_menu1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn_menu1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn_menu1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn_menu2
    ui->normal_btn_menu2 = lv_btn_create(ui->normal);
    ui->normal_btn_menu2_label = lv_label_create(ui->normal_btn_menu2);
    lv_label_set_text(ui->normal_btn_menu2_label, "  调制");
    lv_label_set_long_mode(ui->normal_btn_menu2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn_menu2_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn_menu2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn_menu2_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn_menu2, 93, 1);
    lv_obj_set_size(ui->normal_btn_menu2, 90, 35);

    //Write style for normal_btn_menu2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn_menu2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn_menu2, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn_menu2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn_menu2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn_menu2, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn_menu2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn_menu2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn_menu2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn_menu3
    ui->normal_btn_menu3 = lv_btn_create(ui->normal);
    ui->normal_btn_menu3_label = lv_label_create(ui->normal_btn_menu3);
    lv_label_set_text(ui->normal_btn_menu3_label, "  扫描");
    lv_label_set_long_mode(ui->normal_btn_menu3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn_menu3_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn_menu3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn_menu3_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn_menu3, 185, 1);
    lv_obj_set_size(ui->normal_btn_menu3, 90, 35);

    //Write style for normal_btn_menu3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn_menu3, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn_menu3, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn_menu3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn_menu3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn_menu3, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn_menu3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn_menu3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn_menu3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn_menu4
    ui->normal_btn_menu4 = lv_btn_create(ui->normal);
    ui->normal_btn_menu4_label = lv_label_create(ui->normal_btn_menu4);
    lv_label_set_text(ui->normal_btn_menu4_label, "  系统");
    lv_label_set_long_mode(ui->normal_btn_menu4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn_menu4_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn_menu4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn_menu4_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn_menu4, 277, 1);
    lv_obj_set_size(ui->normal_btn_menu4, 90, 35);

    //Write style for normal_btn_menu4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn_menu4, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn_menu4, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn_menu4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn_menu4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn_menu4, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn_menu4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn_menu4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn_menu4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_canvas1
    ui->normal_canvas1 = lv_canvas_create(ui->normal);
    static lv_color_t buf_normal_canvas1[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(220, 120)];
    lv_canvas_set_buffer(ui->normal_canvas1, buf_normal_canvas1, 220, 120, LV_IMG_CF_TRUE_COLOR_ALPHA);
    lv_canvas_fill_bg(ui->normal_canvas1, lv_color_hex(0x1d1c1c), 255);
    //Canvas draw line
    static lv_point_t normal_canvas1_points_array_0[] = {{0, 60},{55, 0},{165, 120},{220, 60},};
    lv_draw_line_dsc_t normal_canvas1_line_dsc_0;
    lv_draw_line_dsc_init(&normal_canvas1_line_dsc_0);
    normal_canvas1_line_dsc_0.color = lv_color_hex(0xfffd00);
    normal_canvas1_line_dsc_0.opa = 255;
    normal_canvas1_line_dsc_0.width = 2;
    normal_canvas1_line_dsc_0.round_start = false;
    normal_canvas1_line_dsc_0.round_end = false;
    lv_canvas_draw_line(ui->normal_canvas1, normal_canvas1_points_array_0, 4, &normal_canvas1_line_dsc_0);

    //Canvas draw line
    static lv_point_t normal_canvas1_points_array_1[] = {{0, 60},{220, 60},};
    lv_draw_line_dsc_t normal_canvas1_line_dsc_1;
    lv_draw_line_dsc_init(&normal_canvas1_line_dsc_1);
    normal_canvas1_line_dsc_1.color = lv_color_hex(0xfbf7f8);
    normal_canvas1_line_dsc_1.opa = 255;
    normal_canvas1_line_dsc_1.width = 1;
    normal_canvas1_line_dsc_1.round_start = false;
    normal_canvas1_line_dsc_1.round_end = false;
    lv_canvas_draw_line(ui->normal_canvas1, normal_canvas1_points_array_1, 2, &normal_canvas1_line_dsc_1);

    lv_obj_set_pos(ui->normal_canvas1, 254, 45);
    lv_obj_set_size(ui->normal_canvas1, 220, 120);
    lv_obj_set_scrollbar_mode(ui->normal_canvas1, LV_SCROLLBAR_MODE_OFF);

    //Write codes normal_label_param1
    ui->normal_label_param1 = lv_label_create(ui->normal);
    lv_label_set_text(ui->normal_label_param1, " 频率                            Hz");
    lv_label_set_long_mode(ui->normal_label_param1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->normal_label_param1, 5, 45);
    lv_obj_set_size(ui->normal_label_param1, 245, 20);

    //Write style for normal_label_param1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->normal_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_label_param1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_label_param1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->normal_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->normal_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_label_param1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->normal_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_label_param1, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_label_param1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->normal_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->normal_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->normal_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->normal_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_label_param2
    ui->normal_label_param2 = lv_label_create(ui->normal);
    lv_label_set_text(ui->normal_label_param2, " 幅度                           Vpp");
    lv_label_set_long_mode(ui->normal_label_param2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->normal_label_param2, 5, 75);
    lv_obj_set_size(ui->normal_label_param2, 245, 20);

    //Write style for normal_label_param2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->normal_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_label_param2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_label_param2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->normal_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->normal_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_label_param2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->normal_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_label_param2, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_label_param2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->normal_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->normal_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->normal_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->normal_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_label_param3
    ui->normal_label_param3 = lv_label_create(ui->normal);
    lv_label_set_text(ui->normal_label_param3, " 偏置                             V");
    lv_label_set_long_mode(ui->normal_label_param3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->normal_label_param3, 5, 105);
    lv_obj_set_size(ui->normal_label_param3, 245, 20);

    //Write style for normal_label_param3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->normal_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_label_param3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_label_param3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_label_param3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->normal_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->normal_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_label_param3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->normal_label_param3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_label_param3, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_label_param3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->normal_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->normal_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->normal_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->normal_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_label_param4
    ui->normal_label_param4 = lv_label_create(ui->normal);
    lv_label_set_text(ui->normal_label_param4, " 相位                           deg");
    lv_label_set_long_mode(ui->normal_label_param4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->normal_label_param4, 5, 135);
    lv_obj_set_size(ui->normal_label_param4, 245, 20);

    //Write style for normal_label_param4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->normal_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_label_param4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_label_param4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_label_param4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->normal_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->normal_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_label_param4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->normal_label_param4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_label_param4, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_label_param4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->normal_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->normal_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->normal_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->normal_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_label_param5
    ui->normal_label_param5 = lv_label_create(ui->normal);
    lv_label_set_text(ui->normal_label_param5, " 占空比                         %");
    lv_label_set_long_mode(ui->normal_label_param5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->normal_label_param5, 5, 165);
    lv_obj_set_size(ui->normal_label_param5, 245, 20);

    //Write style for normal_label_param5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->normal_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_label_param5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_label_param5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_label_param5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->normal_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->normal_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_label_param5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->normal_label_param5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_label_param5, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_label_param5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->normal_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->normal_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->normal_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->normal_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_label_param6
    ui->normal_label_param6 = lv_label_create(ui->normal);
    lv_label_set_text(ui->normal_label_param6, " 无");
    lv_label_set_long_mode(ui->normal_label_param6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->normal_label_param6, 5, 194);
    lv_obj_set_size(ui->normal_label_param6, 230, 20);

    //Write style for normal_label_param6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->normal_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_label_param6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_label_param6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_label_param6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->normal_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->normal_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_label_param6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->normal_label_param6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_label_param6, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_label_param6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->normal_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->normal_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->normal_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->normal_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_label_param7
    ui->normal_label_param7 = lv_label_create(ui->normal);
    lv_label_set_text(ui->normal_label_param7, " 无");
    lv_label_set_long_mode(ui->normal_label_param7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->normal_label_param7, 5, 224);
    lv_obj_set_size(ui->normal_label_param7, 230, 20);

    //Write style for normal_label_param7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->normal_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_label_param7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_label_param7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_label_param7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->normal_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->normal_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_label_param7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->normal_label_param7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_label_param7, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_label_param7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->normal_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->normal_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->normal_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->normal_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_label_param8
    ui->normal_label_param8 = lv_label_create(ui->normal);
    lv_label_set_text(ui->normal_label_param8, "三角波");
    lv_label_set_long_mode(ui->normal_label_param8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->normal_label_param8, 0, 263);
    lv_obj_set_size(ui->normal_label_param8, 480, 20);

    //Write style for normal_label_param8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_label_param8, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_label_param8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_label_param8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_label_param8, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->normal_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->normal_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_label_param8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->normal_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->normal_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->normal_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->normal_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn_left
    ui->normal_btn_left = lv_btn_create(ui->normal);
    ui->normal_btn_left_label = lv_label_create(ui->normal_btn_left);
    lv_label_set_text(ui->normal_btn_left_label, "<");
    lv_label_set_long_mode(ui->normal_btn_left_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn_left_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn_left, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn_left_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn_left, 254, 197);
    lv_obj_set_size(ui->normal_btn_left, 64, 35);

    //Write style for normal_btn_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn_left, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn_left, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn_left, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn_left, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn_left, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn_left, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn_up
    ui->normal_btn_up = lv_btn_create(ui->normal);
    ui->normal_btn_up_label = lv_label_create(ui->normal_btn_up);
    lv_label_set_text(ui->normal_btn_up_label, "+");
    lv_label_set_long_mode(ui->normal_btn_up_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn_up_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn_up, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn_up_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn_up, 327, 173);
    lv_obj_set_size(ui->normal_btn_up, 64, 35);

    //Write style for normal_btn_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn_up, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn_up, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn_up, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn_up, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn_up, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn_up, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn_down
    ui->normal_btn_down = lv_btn_create(ui->normal);
    ui->normal_btn_down_label = lv_label_create(ui->normal_btn_down);
    lv_label_set_text(ui->normal_btn_down_label, "-");
    lv_label_set_long_mode(ui->normal_btn_down_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn_down_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn_down, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn_down_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn_down, 327, 224);
    lv_obj_set_size(ui->normal_btn_down, 64, 35);

    //Write style for normal_btn_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn_down, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn_down, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn_down, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn_down, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn_down, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn_down, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_btn_right
    ui->normal_btn_right = lv_btn_create(ui->normal);
    ui->normal_btn_right_label = lv_label_create(ui->normal_btn_right);
    lv_label_set_text(ui->normal_btn_right_label, ">");
    lv_label_set_long_mode(ui->normal_btn_right_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->normal_btn_right_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->normal_btn_right, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->normal_btn_right_label, LV_PCT(100));
    lv_obj_set_pos(ui->normal_btn_right, 400, 197);
    lv_obj_set_size(ui->normal_btn_right, 64, 35);

    //Write style for normal_btn_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->normal_btn_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->normal_btn_right, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->normal_btn_right, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->normal_btn_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->normal_btn_right, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->normal_btn_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->normal_btn_right, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->normal_btn_right, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->normal_btn_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->normal_btn_right, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes normal_list_wave
    ui->normal_list_wave = lv_list_create(ui->normal);
    ui->normal_list_wave_item0 =lv_list_add_text(ui->normal_list_wave, "正弦波");
    ui->normal_list_wave_item1 =lv_list_add_text(ui->normal_list_wave, "方波");
    ui->normal_list_wave_item2 =lv_list_add_text(ui->normal_list_wave, "锯齿波");
    ui->normal_list_wave_item3 =lv_list_add_text(ui->normal_list_wave, "三角波");
    lv_obj_set_pos(ui->normal_list_wave, 248, 40);
    lv_obj_set_size(ui->normal_list_wave, 230, 220);
    lv_obj_set_scrollbar_mode(ui->normal_list_wave, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->normal_list_wave, LV_OBJ_FLAG_HIDDEN);

    //Write style state: LV_STATE_DEFAULT for &style_normal_list_wave_main_main_default
    static lv_style_t style_normal_list_wave_main_main_default;
    ui_init_style(&style_normal_list_wave_main_main_default);

    lv_style_set_bg_opa(&style_normal_list_wave_main_main_default, 255);
    lv_style_set_bg_color(&style_normal_list_wave_main_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_normal_list_wave_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_normal_list_wave_main_main_default, 2);
    lv_style_set_border_opa(&style_normal_list_wave_main_main_default, 255);
    lv_style_set_border_color(&style_normal_list_wave_main_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_normal_list_wave_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_normal_list_wave_main_main_default, 3);
    lv_style_set_shadow_width(&style_normal_list_wave_main_main_default, 0);
    lv_style_set_pad_top(&style_normal_list_wave_main_main_default, 5);
    lv_style_set_pad_left(&style_normal_list_wave_main_main_default, 5);
    lv_style_set_pad_right(&style_normal_list_wave_main_main_default, 5);
    lv_style_set_pad_bottom(&style_normal_list_wave_main_main_default, 5);
    lv_obj_add_style(ui->normal_list_wave, &style_normal_list_wave_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_normal_list_wave_main_scrollbar_default
    static lv_style_t style_normal_list_wave_main_scrollbar_default;
    ui_init_style(&style_normal_list_wave_main_scrollbar_default);

    lv_style_set_bg_opa(&style_normal_list_wave_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_normal_list_wave_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_normal_list_wave_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_style_set_radius(&style_normal_list_wave_main_scrollbar_default, 3);
    lv_obj_add_style(ui->normal_list_wave, &style_normal_list_wave_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_normal_list_wave_extra_btns_main_default
    static lv_style_t style_normal_list_wave_extra_btns_main_default;
    ui_init_style(&style_normal_list_wave_extra_btns_main_default);

    lv_style_set_bg_opa(&style_normal_list_wave_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_normal_list_wave_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_normal_list_wave_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_normal_list_wave_extra_btns_main_default, 3);
    lv_style_set_border_opa(&style_normal_list_wave_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_normal_list_wave_extra_btns_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_normal_list_wave_extra_btns_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_pad_top(&style_normal_list_wave_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_normal_list_wave_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_normal_list_wave_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_normal_list_wave_extra_btns_main_default, 5);
    lv_style_set_text_color(&style_normal_list_wave_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_normal_list_wave_extra_btns_main_default, &lv_font_ZiHunDaHei_18);
    lv_style_set_text_opa(&style_normal_list_wave_extra_btns_main_default, 255);
    lv_style_set_radius(&style_normal_list_wave_extra_btns_main_default, 3);

    //Write style state: LV_STATE_DEFAULT for &style_normal_list_wave_extra_texts_main_default
    static lv_style_t style_normal_list_wave_extra_texts_main_default;
    ui_init_style(&style_normal_list_wave_extra_texts_main_default);

    lv_style_set_bg_opa(&style_normal_list_wave_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_normal_list_wave_extra_texts_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_normal_list_wave_extra_texts_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_normal_list_wave_extra_texts_main_default, 2);
    lv_style_set_border_opa(&style_normal_list_wave_extra_texts_main_default, 255);
    lv_style_set_border_color(&style_normal_list_wave_extra_texts_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_normal_list_wave_extra_texts_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_normal_list_wave_extra_texts_main_default, 3);
    lv_style_set_pad_top(&style_normal_list_wave_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_normal_list_wave_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_normal_list_wave_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_normal_list_wave_extra_texts_main_default, 5);
    lv_style_set_text_color(&style_normal_list_wave_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_normal_list_wave_extra_texts_main_default, &lv_font_ZiHunDaHei_18);
    lv_style_set_text_opa(&style_normal_list_wave_extra_texts_main_default, 255);
    lv_style_set_transform_width(&style_normal_list_wave_extra_texts_main_default, 0);
    lv_obj_add_style(ui->normal_list_wave_item3, &style_normal_list_wave_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->normal_list_wave_item2, &style_normal_list_wave_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->normal_list_wave_item1, &style_normal_list_wave_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->normal_list_wave_item0, &style_normal_list_wave_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of normal.
    //Write codes normal_spinbox_1
    lv_obj_t* normal_spinbox_1 = lv_spinbox_create(ui->normal);
    lv_obj_set_pos(normal_spinbox_1, 60, 45);
    lv_obj_set_width(normal_spinbox_1, 150);
    lv_obj_set_height(normal_spinbox_1, 30);
    lv_spinbox_set_digit_format(normal_spinbox_1, 10, 8);
    lv_spinbox_set_range(normal_spinbox_1, 0, 100000000);

//Write style for normal_spinbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(normal_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(normal_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(normal_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(normal_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(normal_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(normal_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(normal_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(normal_spinbox_1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(normal_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(normal_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(normal_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(normal_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

//Write style for normal_spinbox_1, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(normal_spinbox_1, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(normal_spinbox_1, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(normal_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(normal_spinbox_1, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(normal_spinbox_1, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(normal_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);



    lv_obj_clear_flag(ui->normal, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(normal_spinbox_1, LV_OBJ_FLAG_SCROLLABLE);



    //Update current screen layout.
    lv_obj_update_layout(ui->normal);

    //Init events for screen.
    events_init_normal(ui);
}
