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

void setup_scr_harmonic(lv_ui *ui)
{
    //Write codes harmonic
    ui->harmonic = lv_obj_create(NULL);
    lv_obj_set_size(ui->harmonic, 480, 320);
    lv_obj_set_scrollbar_mode(ui->harmonic, LV_SCROLLBAR_MODE_OFF);

    //Write style for harmonic, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_menu1
    ui->harmonic_btn_menu1 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_menu1_label = lv_label_create(ui->harmonic_btn_menu1);
    lv_label_set_text(ui->harmonic_btn_menu1_label, " 标准");
    lv_label_set_long_mode(ui->harmonic_btn_menu1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_menu1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_menu1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_menu1_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_menu1, 1, 1);
    lv_obj_set_size(ui->harmonic_btn_menu1, 57, 35);

    //Write style for harmonic_btn_menu1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_menu1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_menu1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_menu1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_menu1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_menu1, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_menu1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_menu1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_menu1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_menu2
    ui->harmonic_btn_menu2 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_menu2_label = lv_label_create(ui->harmonic_btn_menu2);
    lv_label_set_text(ui->harmonic_btn_menu2_label, " 调制");
    lv_label_set_long_mode(ui->harmonic_btn_menu2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_menu2_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_menu2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_menu2_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_menu2, 60, 1);
    lv_obj_set_size(ui->harmonic_btn_menu2, 57, 35);

    //Write style for harmonic_btn_menu2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_menu2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_menu2, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_menu2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_menu2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_menu2, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_menu2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_menu2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_menu2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_menu3
    ui->harmonic_btn_menu3 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_menu3_label = lv_label_create(ui->harmonic_btn_menu3);
    lv_label_set_text(ui->harmonic_btn_menu3_label, " 扫描");
    lv_label_set_long_mode(ui->harmonic_btn_menu3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_menu3_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_menu3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_menu3_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_menu3, 119, 1);
    lv_obj_set_size(ui->harmonic_btn_menu3, 57, 35);

    //Write style for harmonic_btn_menu3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_menu3, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_menu3, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_menu3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_menu3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_menu3, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_menu3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_menu3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_menu3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_menu4
    ui->harmonic_btn_menu4 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_menu4_label = lv_label_create(ui->harmonic_btn_menu4);
    lv_label_set_text(ui->harmonic_btn_menu4_label, " 脉冲");
    lv_label_set_long_mode(ui->harmonic_btn_menu4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_menu4_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_menu4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_menu4_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_menu4, 178, 1);
    lv_obj_set_size(ui->harmonic_btn_menu4, 57, 35);

    //Write style for harmonic_btn_menu4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_menu4, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_menu4, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_menu4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_menu4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_menu4, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_menu4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_menu4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_menu4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_menu5
    ui->harmonic_btn_menu5 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_menu5_label = lv_label_create(ui->harmonic_btn_menu5);
    lv_label_set_text(ui->harmonic_btn_menu5_label, " 谐波");
    lv_label_set_long_mode(ui->harmonic_btn_menu5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_menu5_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_menu5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_menu5_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_menu5, 237, 1);
    lv_obj_set_size(ui->harmonic_btn_menu5, 57, 35);

    //Write style for harmonic_btn_menu5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_menu5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_menu5, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_menu5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_menu5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_menu5, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_menu5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_menu5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_menu5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_menu5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_menu5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_menu6
    ui->harmonic_btn_menu6 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_menu6_label = lv_label_create(ui->harmonic_btn_menu6);
    lv_label_set_text(ui->harmonic_btn_menu6_label, " 用户");
    lv_label_set_long_mode(ui->harmonic_btn_menu6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_menu6_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_menu6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_menu6_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_menu6, 296, 1);
    lv_obj_set_size(ui->harmonic_btn_menu6, 57, 35);

    //Write style for harmonic_btn_menu6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_menu6, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_menu6, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_menu6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_menu6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_menu6, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_menu6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_menu6, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_menu6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_menu6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_menu6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    ui->harmonic_btn_menu7 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_menu7_label = lv_label_create(ui->harmonic_btn_menu7);
    lv_label_set_text(ui->harmonic_btn_menu7_label, " 系统");
    lv_label_set_long_mode(ui->harmonic_btn_menu7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_menu7_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_menu7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_menu7_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_menu7, 355, 1);
    lv_obj_set_size(ui->harmonic_btn_menu7, 57, 35);

    //Write style for harmonic_btn_menu7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_menu7, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_menu7, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_menu7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_menu7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_menu7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_menu7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_menu7, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_menu7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_menu7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_menu7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_label_param8
    ui->harmonic_label_param8 = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_param8, "谐波");
    lv_label_set_long_mode(ui->harmonic_label_param8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_param8, 0, 263);
    lv_obj_set_size(ui->harmonic_label_param8, 480, 20);

    //Write style for harmonic_label_param8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->harmonic_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_param8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_param8, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_param8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_param8, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_param8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_label_line1
    ui->harmonic_label_line1 = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_line1, "");
    lv_label_set_long_mode(ui->harmonic_label_line1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_line1, 1, 34);
    lv_obj_set_size(ui->harmonic_label_line1, 480, 3);

    //Write style for harmonic_label_line1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->harmonic_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_line1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_line1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_line1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_line1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_line1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

        //Write codes harmonic_label_param1
    ui->harmonic_label_param1 = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_param1, " 参数1");
    lv_label_set_long_mode(ui->harmonic_label_param1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_param1, 5, 45);
    lv_obj_set_size(ui->harmonic_label_param1, 245, 20);

    //Write style for harmonic_label_param1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->harmonic_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_param1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_param1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_param1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_param1, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_param1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_label_param2
    ui->harmonic_label_param2 = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_param2, " 参数2");
    lv_label_set_long_mode(ui->harmonic_label_param2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_param2, 5, 75);
    lv_obj_set_size(ui->harmonic_label_param2, 245, 20);

    //Write style for harmonic_label_param2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->harmonic_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_param2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_param2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_param2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_param2, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_param2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_label_param3
    ui->harmonic_label_param3 = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_param3, " 参数3");
    lv_label_set_long_mode(ui->harmonic_label_param3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_param3, 5, 105);
    lv_obj_set_size(ui->harmonic_label_param3, 245, 20);

    //Write style for harmonic_label_param3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->harmonic_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_param3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_param3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_param3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_param3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_param3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_param3, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_param3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_param3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_label_param4
    ui->harmonic_label_param4 = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_param4, " 参数4");
    lv_label_set_long_mode(ui->harmonic_label_param4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_param4, 5, 135);
    lv_obj_set_size(ui->harmonic_label_param4, 245, 20);

    //Write style for harmonic_label_param4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->harmonic_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_param4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_param4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_param4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_param4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_param4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_param4, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_param4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_param4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_label_param5
    ui->harmonic_label_param5 = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_param5, " 参数5");
    lv_label_set_long_mode(ui->harmonic_label_param5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_param5, 5, 165);
    lv_obj_set_size(ui->harmonic_label_param5, 245, 20);

    //Write style for harmonic_label_param5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->harmonic_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_param5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_param5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_param5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_param5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_param5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_param5, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_param5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_param5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_label_param6
    ui->harmonic_label_param6 = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_param6, " 参数6");
    lv_label_set_long_mode(ui->harmonic_label_param6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_param6, 5, 194);
    lv_obj_set_size(ui->harmonic_label_param6, 230, 20);

    //Write style for harmonic_label_param6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->harmonic_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_param6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_param6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_param6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_param6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_param6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_param6, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_param6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_param6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_label_param7
    ui->harmonic_label_param7 = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_param7, " 参数7");
    lv_label_set_long_mode(ui->harmonic_label_param7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_param7, 6, 225);
    lv_obj_set_size(ui->harmonic_label_param7, 230, 20);

    //Write style for harmonic_label_param7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->harmonic_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_param7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_param7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_param7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_param7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_param7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_param7, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_param7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_param7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_sw_start (谐波开关, 样式同 mod_sw_start)
    ui->harmonic_sw_start = lv_switch_create(ui->harmonic);
    lv_obj_set_pos(ui->harmonic_sw_start, 302, 40);
    lv_obj_set_size(ui->harmonic_sw_start, 60, 30);

    lv_obj_set_style_bg_opa(ui->harmonic_sw_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_sw_start, lv_color_hex(0x0c0d0a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_sw_start, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_sw_start, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->harmonic_sw_start, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->harmonic_sw_start, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->harmonic_sw_start, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_sw_start, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_sw_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(ui->harmonic_sw_start, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->harmonic_sw_start, lv_color_hex(0x267e48), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_sw_start, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->harmonic_sw_start, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    lv_obj_set_style_bg_opa(ui->harmonic_sw_start, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_sw_start, lv_color_hex(0xe06105), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_sw_start, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_sw_start, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_sw_start, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes harmonic_label_start
    ui->harmonic_label_start = lv_label_create(ui->harmonic);
    lv_label_set_text(ui->harmonic_label_start, "开启");
    lv_label_set_long_mode(ui->harmonic_label_start, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->harmonic_label_start, 258, 45);
    lv_obj_set_size(ui->harmonic_label_start, 36, 20);

    lv_obj_set_style_border_width(ui->harmonic_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_label_start, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_label_start, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_label_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->harmonic_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_label_start, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_label_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_label_start, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_label_start, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_label_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_spinbox_1
    ui->harmonic_spinbox_1 = lv_spinbox_create(ui->harmonic);
    lv_obj_set_pos(ui->harmonic_spinbox_1, 60, 45);
    lv_obj_set_width(ui->harmonic_spinbox_1, 150);
    lv_obj_set_height(ui->harmonic_spinbox_1, 50);
    lv_spinbox_set_digit_format(ui->harmonic_spinbox_1, 9, 8);
    lv_spinbox_set_range(ui->harmonic_spinbox_1, 0, 999999999);

    //Write style for harmonic_spinbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->harmonic_spinbox_1, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->harmonic_spinbox_1, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_1, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_1, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_spinbox_1, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes harmonic_spinbox_2
    ui->harmonic_spinbox_2 = lv_spinbox_create(ui->harmonic);
    lv_obj_set_pos(ui->harmonic_spinbox_2, 60, 75);
    lv_obj_set_width(ui->harmonic_spinbox_2, 150);
    lv_obj_set_height(ui->harmonic_spinbox_2, 50);
    lv_spinbox_set_digit_format(ui->harmonic_spinbox_2, 9, 8);
    lv_spinbox_set_range(ui->harmonic_spinbox_2, 0, 999999999);

    //Write style for harmonic_spinbox_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_spinbox_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->harmonic_spinbox_2, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->harmonic_spinbox_2, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_2, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_2, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_2, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_spinbox_2, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_spinbox_2, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes harmonic_spinbox_3
    ui->harmonic_spinbox_3 = lv_spinbox_create(ui->harmonic);
    lv_obj_set_pos(ui->harmonic_spinbox_3, 60, 105);
    lv_obj_set_width(ui->harmonic_spinbox_3, 150);
    lv_obj_set_height(ui->harmonic_spinbox_3, 50);
    lv_spinbox_set_digit_format(ui->harmonic_spinbox_3, 9, 8);
    lv_spinbox_set_range(ui->harmonic_spinbox_3, 0, 999999999);

    //Write style for harmonic_spinbox_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_spinbox_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->harmonic_spinbox_3, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->harmonic_spinbox_3, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_3, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_3, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_3, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_spinbox_3, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_spinbox_3, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes harmonic_spinbox_4
    ui->harmonic_spinbox_4 = lv_spinbox_create(ui->harmonic);
    lv_obj_set_pos(ui->harmonic_spinbox_4, 60, 135);
    lv_obj_set_width(ui->harmonic_spinbox_4, 150);
    lv_obj_set_height(ui->harmonic_spinbox_4, 50);
    lv_spinbox_set_digit_format(ui->harmonic_spinbox_4, 9, 8);
    lv_spinbox_set_range(ui->harmonic_spinbox_4, 0, 999999999);

    //Write style for harmonic_spinbox_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_spinbox_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_spinbox_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->harmonic_spinbox_4, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->harmonic_spinbox_4, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_4, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_4, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_4, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_spinbox_4, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_spinbox_4, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes harmonic_spinbox_5
    ui->harmonic_spinbox_5 = lv_spinbox_create(ui->harmonic);
    lv_obj_set_pos(ui->harmonic_spinbox_5, 60, 165);
    lv_obj_set_width(ui->harmonic_spinbox_5, 150);
    lv_obj_set_height(ui->harmonic_spinbox_5, 50);
    lv_spinbox_set_digit_format(ui->harmonic_spinbox_5, 9, 8);
    lv_spinbox_set_range(ui->harmonic_spinbox_5, 0, 999999999);

    //Write style for harmonic_spinbox_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_spinbox_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_spinbox_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->harmonic_spinbox_5, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->harmonic_spinbox_5, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_5, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_5, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_5, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_spinbox_5, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_spinbox_5, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes harmonic_spinbox_6
    ui->harmonic_spinbox_6 = lv_spinbox_create(ui->harmonic);
    lv_obj_set_pos(ui->harmonic_spinbox_6, 60, 195);
    lv_obj_set_width(ui->harmonic_spinbox_6, 150);
    lv_obj_set_height(ui->harmonic_spinbox_6, 50);
    lv_spinbox_set_digit_format(ui->harmonic_spinbox_6, 9, 8);
    lv_spinbox_set_range(ui->harmonic_spinbox_6, 0, 999999999);

    //Write style for harmonic_spinbox_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_spinbox_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_spinbox_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->harmonic_spinbox_6, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->harmonic_spinbox_6, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_6, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_6, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_6, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_spinbox_6, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_spinbox_6, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes harmonic_spinbox_7
    ui->harmonic_spinbox_7 = lv_spinbox_create(ui->harmonic);
    lv_obj_set_pos(ui->harmonic_spinbox_7, 60, 225);
    lv_obj_set_width(ui->harmonic_spinbox_7, 150);
    lv_obj_set_height(ui->harmonic_spinbox_7, 50);
    lv_spinbox_set_digit_format(ui->harmonic_spinbox_7, 9, 8);
    lv_spinbox_set_range(ui->harmonic_spinbox_7, 0, 999999999);

    //Write style for harmonic_spinbox_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->harmonic_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->harmonic_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->harmonic_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->harmonic_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_spinbox_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->harmonic_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_spinbox_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui->harmonic_spinbox_7, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->harmonic_spinbox_7, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_spinbox_7, &lv_font_ZiHunDaHei_18, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_spinbox_7, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->harmonic_spinbox_7, 192, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_spinbox_7, lv_color_hex(0xcfb53b), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_spinbox_7, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_left
    ui->harmonic_btn_left = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_left_label = lv_label_create(ui->harmonic_btn_left);
    lv_label_set_text(ui->harmonic_btn_left_label, "<");
    lv_label_set_long_mode(ui->harmonic_btn_left_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_left_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_left, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_left_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_left, 254, 197);
    lv_obj_set_size(ui->harmonic_btn_left, 64, 35);

    //Write style for harmonic_btn_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_left, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_left, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_left, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_left, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_left, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_left, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_right
    ui->harmonic_btn_right = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_right_label = lv_label_create(ui->harmonic_btn_right);
    lv_label_set_text(ui->harmonic_btn_right_label, ">");
    lv_label_set_long_mode(ui->harmonic_btn_right_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_right_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_right, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_right_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_right, 400, 197);
    lv_obj_set_size(ui->harmonic_btn_right, 64, 35);

    //Write style for harmonic_btn_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_right, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_right, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_right, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_right, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_right, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_right, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_up
    ui->harmonic_btn_up = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_up_label = lv_label_create(ui->harmonic_btn_up);
    lv_label_set_text(ui->harmonic_btn_up_label, "+");
    lv_label_set_long_mode(ui->harmonic_btn_up_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_up_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_up, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_up_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_up, 327, 173);
    lv_obj_set_size(ui->harmonic_btn_up, 64, 35);

    //Write style for harmonic_btn_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_up, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_up, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_up, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_up, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_up, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_up, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn_down
    ui->harmonic_btn_down = lv_btn_create(ui->harmonic);
    ui->harmonic_btn_down_label = lv_label_create(ui->harmonic_btn_down);
    lv_label_set_text(ui->harmonic_btn_down_label, "-");
    lv_label_set_long_mode(ui->harmonic_btn_down_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn_down_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn_down, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn_down_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn_down, 327, 224);
    lv_obj_set_size(ui->harmonic_btn_down, 64, 35);

    //Write style for harmonic_btn_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn_down, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn_down, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn_down, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn_down, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn_down, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn_down, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn1
    ui->harmonic_btn1 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn1_label = lv_label_create(ui->harmonic_btn1);
    lv_label_set_text(ui->harmonic_btn1_label, "");
    lv_label_set_long_mode(ui->harmonic_btn1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn1_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn1, 1, 284);
    lv_obj_set_size(ui->harmonic_btn1, 79, 35);

    //Write style for harmonic_btn1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn1, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->harmonic_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->harmonic_btn1, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->harmonic_btn1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn2
    ui->harmonic_btn2 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn2_label = lv_label_create(ui->harmonic_btn2);
    lv_label_set_text(ui->harmonic_btn2_label, "");
    lv_label_set_long_mode(ui->harmonic_btn2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn2_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn2, 81, 284);
    lv_obj_set_size(ui->harmonic_btn2, 79, 35);

    //Write style for harmonic_btn2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn2, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->harmonic_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->harmonic_btn2, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->harmonic_btn2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn3
    ui->harmonic_btn3 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn3_label = lv_label_create(ui->harmonic_btn3);
    lv_label_set_text(ui->harmonic_btn3_label, "");
    lv_label_set_long_mode(ui->harmonic_btn3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn3_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn3, 161, 284);
    lv_obj_set_size(ui->harmonic_btn3, 79, 35);

    //Write style for harmonic_btn3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn3, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->harmonic_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->harmonic_btn3, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->harmonic_btn3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn4
    ui->harmonic_btn4 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn4_label = lv_label_create(ui->harmonic_btn4);
    lv_label_set_text(ui->harmonic_btn4_label, "");
    lv_label_set_long_mode(ui->harmonic_btn4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn4_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn4, 241, 284);
    lv_obj_set_size(ui->harmonic_btn4, 79, 35);

    //Write style for harmonic_btn4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn4, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->harmonic_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->harmonic_btn4, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->harmonic_btn4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn5
    ui->harmonic_btn5 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn5_label = lv_label_create(ui->harmonic_btn5);
    lv_label_set_text(ui->harmonic_btn5_label, "");
    lv_label_set_long_mode(ui->harmonic_btn5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn5_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn5, 321, 284);
    lv_obj_set_size(ui->harmonic_btn5, 79, 35);

    //Write style for harmonic_btn5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn5, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->harmonic_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->harmonic_btn5, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->harmonic_btn5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes harmonic_btn6
    ui->harmonic_btn6 = lv_btn_create(ui->harmonic);
    ui->harmonic_btn6_label = lv_label_create(ui->harmonic_btn6);
    lv_label_set_text(ui->harmonic_btn6_label, "");
    lv_label_set_long_mode(ui->harmonic_btn6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->harmonic_btn6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->harmonic_btn6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->harmonic_btn6_label, LV_PCT(100));
    lv_obj_set_pos(ui->harmonic_btn6, 401, 284);
    lv_obj_set_size(ui->harmonic_btn6, 78, 35);

    //Write style for harmonic_btn6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->harmonic_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->harmonic_btn6, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->harmonic_btn6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->harmonic_btn6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->harmonic_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->harmonic_btn6, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->harmonic_btn6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->harmonic_btn6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->harmonic_btn6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->harmonic_btn6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->harmonic_btn6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->harmonic_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->harmonic_btn6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



    lv_spinbox_step_prev(ui->harmonic_spinbox_1);
    lv_spinbox_step_prev(ui->harmonic_spinbox_2);
    lv_spinbox_step_prev(ui->harmonic_spinbox_3);
    lv_spinbox_step_prev(ui->harmonic_spinbox_4);
    lv_spinbox_step_prev(ui->harmonic_spinbox_5);
    lv_spinbox_step_prev(ui->harmonic_spinbox_6);
    lv_spinbox_step_prev(ui->harmonic_spinbox_7);


    events_init_harmonic(ui);
}
