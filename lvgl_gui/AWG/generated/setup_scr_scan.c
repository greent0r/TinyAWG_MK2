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



void setup_scr_scan(lv_ui *ui)
{
    //Write codes scan
    ui->scan = lv_obj_create(NULL);
    lv_obj_set_size(ui->scan, 480, 320);
    lv_obj_set_scrollbar_mode(ui->scan, LV_SCROLLBAR_MODE_OFF);

    //Write style for scan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn1
    ui->scan_btn1 = lv_btn_create(ui->scan);
    ui->scan_btn1_label = lv_label_create(ui->scan_btn1);
    lv_label_set_text(ui->scan_btn1_label, "模式");
    lv_label_set_long_mode(ui->scan_btn1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn1_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn1, 1, 284);
    lv_obj_set_size(ui->scan_btn1, 79, 35);

    //Write style for scan_btn1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn1, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scan_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scan_btn1, lv_color_hex(0x8cecb4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scan_btn1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn2
    ui->scan_btn2 = lv_btn_create(ui->scan);
    ui->scan_btn2_label = lv_label_create(ui->scan_btn2);
    lv_label_set_text(ui->scan_btn2_label, "起点");
    lv_label_set_long_mode(ui->scan_btn2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn2_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn2, 81, 284);
    lv_obj_set_size(ui->scan_btn2, 79, 35);

    //Write style for scan_btn2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn2, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scan_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scan_btn2, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scan_btn2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn3
    ui->scan_btn3 = lv_btn_create(ui->scan);
    ui->scan_btn3_label = lv_label_create(ui->scan_btn3);
    lv_label_set_text(ui->scan_btn3_label, "终点");
    lv_label_set_long_mode(ui->scan_btn3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn3_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn3, 161, 284);
    lv_obj_set_size(ui->scan_btn3, 79, 35);

    //Write style for scan_btn3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn3, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scan_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scan_btn3, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scan_btn3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn4
    ui->scan_btn4 = lv_btn_create(ui->scan);
    ui->scan_btn4_label = lv_label_create(ui->scan_btn4);
    lv_label_set_text(ui->scan_btn4_label, "点数");
    lv_label_set_long_mode(ui->scan_btn4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn4_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn4, 241, 284);
    lv_obj_set_size(ui->scan_btn4, 79, 35);

    //Write style for scan_btn4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn4, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scan_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scan_btn4, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scan_btn4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn5
    ui->scan_btn5 = lv_btn_create(ui->scan);
    ui->scan_btn5_label = lv_label_create(ui->scan_btn5);
    lv_label_set_text(ui->scan_btn5_label, "时间间隔");
    lv_label_set_long_mode(ui->scan_btn5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn5_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn5, 321, 284);
    lv_obj_set_size(ui->scan_btn5, 79, 35);

    //Write style for scan_btn5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn5, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scan_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scan_btn5, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scan_btn5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn6
    ui->scan_btn6 = lv_btn_create(ui->scan);
    ui->scan_btn6_label = lv_label_create(ui->scan_btn6);
    lv_label_set_text(ui->scan_btn6_label, "换页");
    lv_label_set_long_mode(ui->scan_btn6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn6_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn6, 401, 284);
    lv_obj_set_size(ui->scan_btn6, 78, 35);

    //Write style for scan_btn6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn6, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scan_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scan_btn6, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scan_btn6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_label_param8
    ui->scan_label_param8 = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_param8, "线性扫频");
    lv_label_set_long_mode(ui->scan_label_param8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_param8, 0, 263);
    lv_obj_set_size(ui->scan_label_param8, 480, 20);

    //Write style for scan_label_param8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_param8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_param8, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_param8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_param8, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_param8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_label_line1
    ui->scan_label_line1 = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_line1, "");
    lv_label_set_long_mode(ui->scan_label_line1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_line1, 1, 34);
    lv_obj_set_size(ui->scan_label_line1, 480, 3);

    //Write style for scan_label_line1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_line1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_line1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_line1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_line1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_line1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn_menu1
    ui->scan_btn_menu1 = lv_btn_create(ui->scan);
    ui->scan_btn_menu1_label = lv_label_create(ui->scan_btn_menu1);
    lv_label_set_text(ui->scan_btn_menu1_label, "  标准");
    lv_label_set_long_mode(ui->scan_btn_menu1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn_menu1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn_menu1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn_menu1_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn_menu1, 1, 1);
    lv_obj_set_size(ui->scan_btn_menu1, 90, 35);

    //Write style for scan_btn_menu1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn_menu1, 52, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn_menu1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn_menu1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn_menu1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn_menu1, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn_menu1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn_menu1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn_menu1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn_menu2
    ui->scan_btn_menu2 = lv_btn_create(ui->scan);
    ui->scan_btn_menu2_label = lv_label_create(ui->scan_btn_menu2);
    lv_label_set_text(ui->scan_btn_menu2_label, "  调制");
    lv_label_set_long_mode(ui->scan_btn_menu2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn_menu2_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn_menu2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn_menu2_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn_menu2, 93, 1);
    lv_obj_set_size(ui->scan_btn_menu2, 90, 35);

    //Write style for scan_btn_menu2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn_menu2, 53, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn_menu2, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn_menu2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn_menu2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn_menu2, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn_menu2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn_menu2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn_menu2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn_menu3
    ui->scan_btn_menu3 = lv_btn_create(ui->scan);
    ui->scan_btn_menu3_label = lv_label_create(ui->scan_btn_menu3);
    lv_label_set_text(ui->scan_btn_menu3_label, "   扫描");
    lv_label_set_long_mode(ui->scan_btn_menu3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn_menu3_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn_menu3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn_menu3_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn_menu3, 185, 1);
    lv_obj_set_size(ui->scan_btn_menu3, 90, 35);

    //Write style for scan_btn_menu3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn_menu3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn_menu3, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn_menu3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn_menu3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn_menu3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn_menu3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn_menu3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn_menu3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn_menu4
    ui->scan_btn_menu4 = lv_btn_create(ui->scan);
    ui->scan_btn_menu4_label = lv_label_create(ui->scan_btn_menu4);
    lv_label_set_text(ui->scan_btn_menu4_label, "  系统");
    lv_label_set_long_mode(ui->scan_btn_menu4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn_menu4_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn_menu4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn_menu4_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn_menu4, 277, 1);
    lv_obj_set_size(ui->scan_btn_menu4, 90, 35);

    //Write style for scan_btn_menu4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn_menu4, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn_menu4, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn_menu4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn_menu4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn_menu4, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn_menu4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn_menu4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn_menu4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_label_param7
    ui->scan_label_param7 = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_param7, " 无");
    lv_label_set_long_mode(ui->scan_label_param7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_param7, 6, 225);
    lv_obj_set_size(ui->scan_label_param7, 230, 20);
    lv_obj_add_flag(ui->scan_label_param7, LV_OBJ_FLAG_HIDDEN);

    //Write style for scan_label_param7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_param7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_param7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_param7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_param7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_param7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_param7, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_param7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_label_param6
    ui->scan_label_param6 = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_param6, " 无");
    lv_label_set_long_mode(ui->scan_label_param6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_param6, 5, 194);
    lv_obj_set_size(ui->scan_label_param6, 230, 20);
    lv_obj_add_flag(ui->scan_label_param6, LV_OBJ_FLAG_HIDDEN);

    //Write style for scan_label_param6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_param6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_param6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_param6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_param6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_param6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_param6, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_param6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_label_param5
    ui->scan_label_param5 = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_param5, " 无");
    lv_label_set_long_mode(ui->scan_label_param5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_param5, 5, 165);
    lv_obj_set_size(ui->scan_label_param5, 245, 20);
    lv_obj_add_flag(ui->scan_label_param5, LV_OBJ_FLAG_HIDDEN);

    //Write style for scan_label_param5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_param5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_param5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_param5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_param5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_param5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_param5, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_param5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_label_param4
    ui->scan_label_param4 = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_param4, " 时间间隔                      ms");
    lv_label_set_long_mode(ui->scan_label_param4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_param4, 5, 135);
    lv_obj_set_size(ui->scan_label_param4, 245, 20);

    //Write style for scan_label_param4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_param4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_param4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_param4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_param4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_param4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_param4, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_param4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_label_param3
    ui->scan_label_param3 = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_param3, " 点数                            个");
    lv_label_set_long_mode(ui->scan_label_param3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_param3, 5, 105);
    lv_obj_set_size(ui->scan_label_param3, 245, 20);

    //Write style for scan_label_param3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_param3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_param3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_param3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_param3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_param3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_param3, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_param3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_label_param2
    ui->scan_label_param2 = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_param2, " 终点                            Hz");
    lv_label_set_long_mode(ui->scan_label_param2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_param2, 5, 75);
    lv_obj_set_size(ui->scan_label_param2, 245, 20);

    //Write style for scan_label_param2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_param2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_param2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_param2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_param2, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_param2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_label_param1
    ui->scan_label_param1 = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_param1, " 起点                            Hz");
    lv_label_set_long_mode(ui->scan_label_param1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_param1, 5, 45);
    lv_obj_set_size(ui->scan_label_param1, 245, 20);

    //Write style for scan_label_param1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_param1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_param1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_param1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_param1, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_param1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_sw_start
    ui->scan_sw_start = lv_switch_create(ui->scan);
    lv_obj_set_pos(ui->scan_sw_start, 302, 37);
    lv_obj_set_size(ui->scan_sw_start, 60, 30);

    //Write style for scan_sw_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_sw_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_sw_start, lv_color_hex(0x0c0d0a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_sw_start, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_sw_start, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scan_sw_start, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scan_sw_start, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scan_sw_start, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_sw_start, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_sw_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scan_sw_start, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->scan_sw_start, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->scan_sw_start, lv_color_hex(0x267e48), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->scan_sw_start, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->scan_sw_start, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for scan_sw_start, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_sw_start, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_sw_start, lv_color_hex(0xe06105), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_sw_start, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_sw_start, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_sw_start, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes scan_label_start
    ui->scan_label_start = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_start, "启动");
    lv_label_set_long_mode(ui->scan_label_start, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_start, 258, 45);
    lv_obj_set_size(ui->scan_label_start, 36, 20);

    //Write style for scan_label_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_start, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_start, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_start, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_start, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_start, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn_right
    ui->scan_btn_right = lv_btn_create(ui->scan);
    ui->scan_btn_right_label = lv_label_create(ui->scan_btn_right);
    lv_label_set_text(ui->scan_btn_right_label, ">");
    lv_label_set_long_mode(ui->scan_btn_right_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn_right_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn_right, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn_right_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn_right, 400, 197);
    lv_obj_set_size(ui->scan_btn_right, 64, 35);

    //Write style for scan_btn_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn_right, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn_right, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn_right, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn_right, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn_right, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn_right, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn_down
    ui->scan_btn_down = lv_btn_create(ui->scan);
    ui->scan_btn_down_label = lv_label_create(ui->scan_btn_down);
    lv_label_set_text(ui->scan_btn_down_label, "-");
    lv_label_set_long_mode(ui->scan_btn_down_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn_down_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn_down, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn_down_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn_down, 327, 224);
    lv_obj_set_size(ui->scan_btn_down, 64, 35);

    //Write style for scan_btn_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn_down, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn_down, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn_down, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn_down, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn_down, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn_down, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn_left
    ui->scan_btn_left = lv_btn_create(ui->scan);
    ui->scan_btn_left_label = lv_label_create(ui->scan_btn_left);
    lv_label_set_text(ui->scan_btn_left_label, "<");
    lv_label_set_long_mode(ui->scan_btn_left_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn_left_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn_left, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn_left_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn_left, 254, 197);
    lv_obj_set_size(ui->scan_btn_left, 64, 35);

    //Write style for scan_btn_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn_left, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn_left, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn_left, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn_left, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn_left, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn_left, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_btn_up
    ui->scan_btn_up = lv_btn_create(ui->scan);
    ui->scan_btn_up_label = lv_label_create(ui->scan_btn_up);
    lv_label_set_text(ui->scan_btn_up_label, "+");
    lv_label_set_long_mode(ui->scan_btn_up_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scan_btn_up_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scan_btn_up, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scan_btn_up_label, LV_PCT(100));
    lv_obj_set_pos(ui->scan_btn_up, 327, 173);
    lv_obj_set_size(ui->scan_btn_up, 64, 35);

    //Write style for scan_btn_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_btn_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_btn_up, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_btn_up, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_btn_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_btn_up, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_btn_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_btn_up, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_btn_up, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_btn_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_btn_up, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_sw_loop
    ui->scan_sw_loop = lv_switch_create(ui->scan);
    lv_obj_set_pos(ui->scan_sw_loop, 302, 76);
    lv_obj_set_size(ui->scan_sw_loop, 60, 30);

    //Write style for scan_sw_loop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_sw_loop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_sw_loop, lv_color_hex(0x0c0d0a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_sw_loop, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_sw_loop, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scan_sw_loop, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scan_sw_loop, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scan_sw_loop, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_sw_loop, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_sw_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scan_sw_loop, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->scan_sw_loop, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->scan_sw_loop, lv_color_hex(0x267e48), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->scan_sw_loop, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->scan_sw_loop, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for scan_sw_loop, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scan_sw_loop, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_sw_loop, lv_color_hex(0xe06105), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_sw_loop, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scan_sw_loop, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_sw_loop, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes scan_label_loop
    ui->scan_label_loop = lv_label_create(ui->scan);
    lv_label_set_text(ui->scan_label_loop, "循环");
    lv_label_set_long_mode(ui->scan_label_loop, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scan_label_loop, 258, 81);
    lv_obj_set_size(ui->scan_label_loop, 36, 20);

    //Write style for scan_label_loop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scan_label_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scan_label_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scan_label_loop, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scan_label_loop, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scan_label_loop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scan_label_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scan_label_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scan_label_loop, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scan_label_loop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scan_label_loop, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scan_label_loop, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scan_label_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scan_label_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scan_label_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scan_label_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scan_label_loop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scan_list_mode
    ui->scan_list_mode = lv_list_create(ui->scan);
    ui->scan_list_mode_item0 =lv_list_add_text(ui->scan_list_mode, "线性扫频");
    ui->scan_list_mode_item1 =lv_list_add_text(ui->scan_list_mode, "对数扫频");
    lv_obj_set_pos(ui->scan_list_mode, 248, 40);
    lv_obj_set_size(ui->scan_list_mode, 230, 220);
    lv_obj_set_scrollbar_mode(ui->scan_list_mode, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->scan_list_mode, LV_OBJ_FLAG_HIDDEN);

    //Write style state: LV_STATE_DEFAULT for &style_scan_list_mode_main_main_default
    static lv_style_t style_scan_list_mode_main_main_default;
    ui_init_style(&style_scan_list_mode_main_main_default);

    lv_style_set_pad_top(&style_scan_list_mode_main_main_default, 5);
    lv_style_set_pad_left(&style_scan_list_mode_main_main_default, 5);
    lv_style_set_pad_right(&style_scan_list_mode_main_main_default, 5);
    lv_style_set_pad_bottom(&style_scan_list_mode_main_main_default, 5);
    lv_style_set_bg_opa(&style_scan_list_mode_main_main_default, 255);
    lv_style_set_bg_color(&style_scan_list_mode_main_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_scan_list_mode_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_scan_list_mode_main_main_default, 2);
    lv_style_set_border_opa(&style_scan_list_mode_main_main_default, 255);
    lv_style_set_border_color(&style_scan_list_mode_main_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_scan_list_mode_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_scan_list_mode_main_main_default, 3);
    lv_style_set_shadow_width(&style_scan_list_mode_main_main_default, 0);
    lv_obj_add_style(ui->scan_list_mode, &style_scan_list_mode_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_scan_list_mode_main_scrollbar_default
    static lv_style_t style_scan_list_mode_main_scrollbar_default;
    ui_init_style(&style_scan_list_mode_main_scrollbar_default);

    lv_style_set_radius(&style_scan_list_mode_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_scan_list_mode_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_scan_list_mode_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_scan_list_mode_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->scan_list_mode, &style_scan_list_mode_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_scan_list_mode_extra_btns_main_default
    static lv_style_t style_scan_list_mode_extra_btns_main_default;
    ui_init_style(&style_scan_list_mode_extra_btns_main_default);

    lv_style_set_pad_top(&style_scan_list_mode_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_scan_list_mode_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_scan_list_mode_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_scan_list_mode_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_scan_list_mode_extra_btns_main_default, 3);
    lv_style_set_border_opa(&style_scan_list_mode_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_scan_list_mode_extra_btns_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_scan_list_mode_extra_btns_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_scan_list_mode_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_scan_list_mode_extra_btns_main_default, &lv_font_ZiHunDaHei_18);
    lv_style_set_text_opa(&style_scan_list_mode_extra_btns_main_default, 255);
    lv_style_set_radius(&style_scan_list_mode_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_scan_list_mode_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_scan_list_mode_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_scan_list_mode_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_scan_list_mode_extra_texts_main_default
    static lv_style_t style_scan_list_mode_extra_texts_main_default;
    ui_init_style(&style_scan_list_mode_extra_texts_main_default);

    lv_style_set_pad_top(&style_scan_list_mode_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_scan_list_mode_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_scan_list_mode_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_scan_list_mode_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_scan_list_mode_extra_texts_main_default, 2);
    lv_style_set_border_opa(&style_scan_list_mode_extra_texts_main_default, 255);
    lv_style_set_border_color(&style_scan_list_mode_extra_texts_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_scan_list_mode_extra_texts_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_scan_list_mode_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_scan_list_mode_extra_texts_main_default, &lv_font_ZiHunDaHei_18);
    lv_style_set_text_opa(&style_scan_list_mode_extra_texts_main_default, 255);
    lv_style_set_radius(&style_scan_list_mode_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_scan_list_mode_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_scan_list_mode_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_scan_list_mode_extra_texts_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_scan_list_mode_extra_texts_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->scan_list_mode_item1, &style_scan_list_mode_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->scan_list_mode_item0, &style_scan_list_mode_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of scan.
    lv_obj_clear_flag(ui->scan, LV_OBJ_FLAG_SCROLLABLE);

    //Update current screen layout.
    lv_obj_update_layout(ui->scan);

    //Init events for screen.
    events_init_scan(ui);
}
