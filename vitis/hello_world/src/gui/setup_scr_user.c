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

void setup_scr_user(lv_ui *ui)
{
    //Write codes user
    ui->user = lv_obj_create(NULL);
    lv_obj_set_size(ui->user, 480, 320);
    lv_obj_set_scrollbar_mode(ui->user, LV_SCROLLBAR_MODE_OFF);

    //Write style for user, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn_menu1
    ui->user_btn_menu1 = lv_btn_create(ui->user);
    ui->user_btn_menu1_label = lv_label_create(ui->user_btn_menu1);
    lv_label_set_text(ui->user_btn_menu1_label, " 标准");
    lv_label_set_long_mode(ui->user_btn_menu1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn_menu1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn_menu1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn_menu1_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn_menu1, 1, 1);
    lv_obj_set_size(ui->user_btn_menu1, 57, 35);

    //Write style for user_btn_menu1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn_menu1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn_menu1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn_menu1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn_menu1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn_menu1, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn_menu1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn_menu1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn_menu1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn_menu2
    ui->user_btn_menu2 = lv_btn_create(ui->user);
    ui->user_btn_menu2_label = lv_label_create(ui->user_btn_menu2);
    lv_label_set_text(ui->user_btn_menu2_label, " 调制");
    lv_label_set_long_mode(ui->user_btn_menu2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn_menu2_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn_menu2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn_menu2_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn_menu2, 60, 1);
    lv_obj_set_size(ui->user_btn_menu2, 57, 35);

    //Write style for user_btn_menu2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn_menu2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn_menu2, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn_menu2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn_menu2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn_menu2, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn_menu2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn_menu2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn_menu2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn_menu3
    ui->user_btn_menu3 = lv_btn_create(ui->user);
    ui->user_btn_menu3_label = lv_label_create(ui->user_btn_menu3);
    lv_label_set_text(ui->user_btn_menu3_label, " 扫描");
    lv_label_set_long_mode(ui->user_btn_menu3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn_menu3_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn_menu3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn_menu3_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn_menu3, 119, 1);
    lv_obj_set_size(ui->user_btn_menu3, 57, 35);

    //Write style for user_btn_menu3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn_menu3, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn_menu3, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn_menu3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn_menu3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn_menu3, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn_menu3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn_menu3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn_menu3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn_menu4
    ui->user_btn_menu4 = lv_btn_create(ui->user);
    ui->user_btn_menu4_label = lv_label_create(ui->user_btn_menu4);
    lv_label_set_text(ui->user_btn_menu4_label, " 脉冲");
    lv_label_set_long_mode(ui->user_btn_menu4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn_menu4_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn_menu4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn_menu4_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn_menu4, 178, 1);
    lv_obj_set_size(ui->user_btn_menu4, 57, 35);

    //Write style for user_btn_menu4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn_menu4, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn_menu4, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn_menu4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn_menu4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn_menu4, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn_menu4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn_menu4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn_menu4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn_menu5
    ui->user_btn_menu5 = lv_btn_create(ui->user);
    ui->user_btn_menu5_label = lv_label_create(ui->user_btn_menu5);
    lv_label_set_text(ui->user_btn_menu5_label, " 谐波");
    lv_label_set_long_mode(ui->user_btn_menu5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn_menu5_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn_menu5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn_menu5_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn_menu5, 237, 1);
    lv_obj_set_size(ui->user_btn_menu5, 57, 35);

    //Write style for user_btn_menu5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn_menu5, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn_menu5, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn_menu5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn_menu5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn_menu5, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn_menu5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn_menu5, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn_menu5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn_menu5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn_menu5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn_menu6
    ui->user_btn_menu6 = lv_btn_create(ui->user);
    ui->user_btn_menu6_label = lv_label_create(ui->user_btn_menu6);
    lv_label_set_text(ui->user_btn_menu6_label, " 用户");
    lv_label_set_long_mode(ui->user_btn_menu6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn_menu6_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn_menu6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn_menu6_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn_menu6, 296, 1);
    lv_obj_set_size(ui->user_btn_menu6, 57, 35);

    //Write style for user_btn_menu6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn_menu6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn_menu6, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn_menu6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn_menu6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn_menu6, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn_menu6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn_menu6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn_menu6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn_menu6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn_menu6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn_menu7
    ui->user_btn_menu7 = lv_btn_create(ui->user);
    ui->user_btn_menu7_label = lv_label_create(ui->user_btn_menu7);
    lv_label_set_text(ui->user_btn_menu7_label, " 系统");
    lv_label_set_long_mode(ui->user_btn_menu7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn_menu7_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn_menu7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn_menu7_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn_menu7, 355, 1);
    lv_obj_set_size(ui->user_btn_menu7, 57, 35);

    //Write style for user_btn_menu7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn_menu7, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn_menu7, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn_menu7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn_menu7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn_menu7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn_menu7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn_menu7, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn_menu7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn_menu7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn_menu7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_label_line1
    ui->user_label_line1 = lv_label_create(ui->user);
    lv_label_set_text(ui->user_label_line1, "");
    lv_label_set_long_mode(ui->user_label_line1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->user_label_line1, 1, 34);
    lv_obj_set_size(ui->user_label_line1, 480, 3);

    //Write style for user_label_line1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->user_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_label_line1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_label_line1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->user_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->user_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_label_line1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->user_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_label_line1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_label_line1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->user_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->user_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->user_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->user_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_label_param8
    ui->user_label_param8 = lv_label_create(ui->user);
    lv_label_set_text(ui->user_label_param8, "用户");
    lv_label_set_long_mode(ui->user_label_param8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->user_label_param8, 0, 263);
    lv_obj_set_size(ui->user_label_param8, 480, 20);

    //Write style for user_label_param8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->user_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_label_param8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_label_param8, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->user_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->user_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_label_param8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->user_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_label_param8, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_label_param8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->user_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->user_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->user_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->user_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn1
    ui->user_btn1 = lv_btn_create(ui->user);
    ui->user_btn1_label = lv_label_create(ui->user_btn1);
    lv_label_set_text(ui->user_btn1_label, "用户波形");
    lv_label_set_long_mode(ui->user_btn1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn1_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn1, 1, 284);
    lv_obj_set_size(ui->user_btn1, 79, 35);

    //Write style for user_btn1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn1, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->user_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->user_btn1, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->user_btn1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn2
    ui->user_btn2 = lv_btn_create(ui->user);
    ui->user_btn2_label = lv_label_create(ui->user_btn2);
    lv_label_set_text(ui->user_btn2_label, "");
    lv_label_set_long_mode(ui->user_btn2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn2_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn2, 81, 284);
    lv_obj_set_size(ui->user_btn2, 79, 35);

    //Write style for user_btn2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn2, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->user_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->user_btn2, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->user_btn2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn3
    ui->user_btn3 = lv_btn_create(ui->user);
    ui->user_btn3_label = lv_label_create(ui->user_btn3);
    lv_label_set_text(ui->user_btn3_label, "");
    lv_label_set_long_mode(ui->user_btn3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn3_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn3, 161, 284);
    lv_obj_set_size(ui->user_btn3, 79, 35);

    //Write style for user_btn3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn3, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->user_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->user_btn3, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->user_btn3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn4
    ui->user_btn4 = lv_btn_create(ui->user);
    ui->user_btn4_label = lv_label_create(ui->user_btn4);
    lv_label_set_text(ui->user_btn4_label, "");
    lv_label_set_long_mode(ui->user_btn4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn4_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn4, 241, 284);
    lv_obj_set_size(ui->user_btn4, 79, 35);

    //Write style for user_btn4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn4, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->user_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->user_btn4, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->user_btn4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn5
    ui->user_btn5 = lv_btn_create(ui->user);
    ui->user_btn5_label = lv_label_create(ui->user_btn5);
    lv_label_set_text(ui->user_btn5_label, "");
    lv_label_set_long_mode(ui->user_btn5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn5_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn5, 321, 284);
    lv_obj_set_size(ui->user_btn5, 79, 35);

    //Write style for user_btn5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn5, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->user_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->user_btn5, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->user_btn5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_btn6
    ui->user_btn6 = lv_btn_create(ui->user);
    ui->user_btn6_label = lv_label_create(ui->user_btn6);
    lv_label_set_text(ui->user_btn6_label, "");
    lv_label_set_long_mode(ui->user_btn6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->user_btn6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->user_btn6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->user_btn6_label, LV_PCT(100));
    lv_obj_set_pos(ui->user_btn6, 401, 284);
    lv_obj_set_size(ui->user_btn6, 78, 35);

    //Write style for user_btn6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->user_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_btn6, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_btn6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_btn6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->user_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->user_btn6, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->user_btn6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_btn6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_btn6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_btn6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_btn6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_btn6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_label_en
    ui->user_label_en = lv_label_create(ui->user);
    lv_label_set_text(ui->user_label_en, "开启");
    lv_label_set_long_mode(ui->user_label_en, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->user_label_en, 258, 45);
    lv_obj_set_size(ui->user_label_en, 36, 20);
    lv_obj_set_style_border_width(ui->user_label_en, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_label_en, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->user_label_en, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->user_label_en, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->user_label_en, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->user_label_en, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->user_label_en, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_label_en, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_label_en, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_label_en, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes user_sw_en
    ui->user_sw_en = lv_switch_create(ui->user);
    lv_obj_set_pos(ui->user_sw_en, 302, 40);
    lv_obj_set_size(ui->user_sw_en, 60, 30);
    lv_obj_set_style_bg_opa(ui->user_sw_en, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_sw_en, lv_color_hex(0x0c0d0a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_sw_en, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_sw_en, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->user_sw_en, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->user_sw_en, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->user_sw_en, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_sw_en, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->user_sw_en, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->user_sw_en, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->user_sw_en, lv_color_hex(0x267e48), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->user_sw_en, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->user_sw_en, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->user_sw_en, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->user_sw_en, lv_color_hex(0xe06105), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->user_sw_en, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->user_sw_en, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->user_sw_en, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes user_list_wave
    ui->user_list_wave = lv_list_create(ui->user);
    lv_obj_set_pos(ui->user_list_wave, 20, 45);
    lv_obj_set_size(ui->user_list_wave, 440, 210);
    lv_obj_set_scrollbar_mode(ui->user_list_wave, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui->user_list_wave, LV_DIR_VER);
    lv_obj_add_flag(ui->user_list_wave, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_layout(ui->user_list_wave, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(ui->user_list_wave, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui->user_list_wave, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(ui->user_list_wave, 8, 0);
    lv_obj_set_style_pad_column(ui->user_list_wave, 8, 0);
    lv_obj_set_style_pad_left(ui->user_list_wave, 4, 0);
    lv_obj_set_style_pad_top(ui->user_list_wave, 4, 0);
    lv_obj_set_style_pad_right(ui->user_list_wave, 4, 0);
    lv_obj_set_style_pad_bottom(ui->user_list_wave, 4, 0);

    static lv_style_t style_user_list_wave_main_main_default;
    ui_init_style(&style_user_list_wave_main_main_default);
    lv_style_set_pad_top(&style_user_list_wave_main_main_default, 5);
    lv_style_set_pad_left(&style_user_list_wave_main_main_default, 5);
    lv_style_set_pad_right(&style_user_list_wave_main_main_default, 5);
    lv_style_set_pad_bottom(&style_user_list_wave_main_main_default, 5);
    lv_style_set_bg_opa(&style_user_list_wave_main_main_default, 255);
    lv_style_set_bg_color(&style_user_list_wave_main_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_user_list_wave_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_user_list_wave_main_main_default, 2);
    lv_style_set_border_opa(&style_user_list_wave_main_main_default, 255);
    lv_style_set_border_color(&style_user_list_wave_main_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_user_list_wave_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_user_list_wave_main_main_default, 3);
    lv_style_set_shadow_width(&style_user_list_wave_main_main_default, 0);
    lv_obj_add_style(ui->user_list_wave, &style_user_list_wave_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    static lv_style_t style_user_list_wave_extra_texts_main_default;
    ui_init_style(&style_user_list_wave_extra_texts_main_default);
    lv_style_set_pad_top(&style_user_list_wave_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_user_list_wave_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_user_list_wave_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_user_list_wave_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_user_list_wave_extra_texts_main_default, 2);
    lv_style_set_border_opa(&style_user_list_wave_extra_texts_main_default, 255);
    lv_style_set_border_color(&style_user_list_wave_extra_texts_main_default, lv_color_hex(0x30e37a));
    lv_style_set_border_side(&style_user_list_wave_extra_texts_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_user_list_wave_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_user_list_wave_extra_texts_main_default, &lv_font_ZiHunDaHei_18);
    lv_style_set_text_opa(&style_user_list_wave_extra_texts_main_default, 255);
    lv_style_set_radius(&style_user_list_wave_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_user_list_wave_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_user_list_wave_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_user_list_wave_extra_texts_main_default, lv_color_hex(0x0d0d0d));
    lv_style_set_bg_grad_dir(&style_user_list_wave_extra_texts_main_default, LV_GRAD_DIR_NONE);
    ui->user_list_wave_item0  = ui_list_add_item(ui->user_list_wave, "用户波01", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item1  = ui_list_add_item(ui->user_list_wave, "用户波02", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item2  = ui_list_add_item(ui->user_list_wave, "用户波03", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item3  = ui_list_add_item(ui->user_list_wave, "用户波04", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item4  = ui_list_add_item(ui->user_list_wave, "用户波05", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item5  = ui_list_add_item(ui->user_list_wave, "用户波06", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item6  = ui_list_add_item(ui->user_list_wave, "用户波07", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item7  = ui_list_add_item(ui->user_list_wave, "用户波08", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item8  = ui_list_add_item(ui->user_list_wave, "用户波09", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item9  = ui_list_add_item(ui->user_list_wave, "用户波10", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item10 = ui_list_add_item(ui->user_list_wave, "用户波11", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item11 = ui_list_add_item(ui->user_list_wave, "用户波12", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item12 = ui_list_add_item(ui->user_list_wave, "用户波13", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item13 = ui_list_add_item(ui->user_list_wave, "用户波14", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item14 = ui_list_add_item(ui->user_list_wave, "用户波15", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item15 = ui_list_add_item(ui->user_list_wave, "用户波16", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item16 = ui_list_add_item(ui->user_list_wave, "用户波17", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item17 = ui_list_add_item(ui->user_list_wave, "用户波18", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item18 = ui_list_add_item(ui->user_list_wave, "用户波19", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item19 = ui_list_add_item(ui->user_list_wave, "用户波20", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item20 = ui_list_add_item(ui->user_list_wave, "用户波21", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item21 = ui_list_add_item(ui->user_list_wave, "用户波22", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item22 = ui_list_add_item(ui->user_list_wave, "用户波23", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item23 = ui_list_add_item(ui->user_list_wave, "用户波24", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item24 = ui_list_add_item(ui->user_list_wave, "用户波25", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item25 = ui_list_add_item(ui->user_list_wave, "用户波26", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item26 = ui_list_add_item(ui->user_list_wave, "用户波27", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item27 = ui_list_add_item(ui->user_list_wave, "用户波28", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item28 = ui_list_add_item(ui->user_list_wave, "用户波29", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item29 = ui_list_add_item(ui->user_list_wave, "用户波30", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item30 = ui_list_add_item(ui->user_list_wave, "用户波31", 100, 28, &style_user_list_wave_extra_texts_main_default);
    ui->user_list_wave_item31 = ui_list_add_item(ui->user_list_wave, "用户波32", 100, 28, &style_user_list_wave_extra_texts_main_default);

    //The custom code of user.
    lv_obj_clear_flag(ui->user, LV_OBJ_FLAG_SCROLLABLE);

    //Update current screen layout.
    lv_obj_update_layout(ui->user);

    events_init_user(ui);
}
