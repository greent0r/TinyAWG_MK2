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
#include "MAX17048.h"

lv_timer_t *system_timer;

void my_timer(lv_timer_t * timer) 
{
    max17048_update();
    char buff[20];
    sprintf(buff, " 电池 %d %%", Battery_Soc);
    lv_label_set_text(guider_ui.system_label_param1, buff);
}



void setup_scr_system(lv_ui *ui)
{
    //Write codes system
    ui->system = lv_obj_create(NULL);
    lv_obj_set_size(ui->system, 480, 320);
    lv_obj_set_scrollbar_mode(ui->system, LV_SCROLLBAR_MODE_OFF);

    //Write style for system, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn1
    ui->system_btn1 = lv_btn_create(ui->system);
    ui->system_btn1_label = lv_label_create(ui->system_btn1);
    lv_label_set_text(ui->system_btn1_label, "同相位");
    lv_label_set_long_mode(ui->system_btn1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn1_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn1, 1, 284);
    lv_obj_set_size(ui->system_btn1, 79, 35);

    //Write style for system_btn1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn1, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_btn1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_btn1, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_btn1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn2
    ui->system_btn2 = lv_btn_create(ui->system);
    ui->system_btn2_label = lv_label_create(ui->system_btn2);
    lv_label_set_text(ui->system_btn2_label, "");
    lv_label_set_long_mode(ui->system_btn2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn2_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn2, 81, 284);
    lv_obj_set_size(ui->system_btn2, 79, 35);

    //Write style for system_btn2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn2, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_btn2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_btn2, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_btn2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn3
    ui->system_btn3 = lv_btn_create(ui->system);
    ui->system_btn3_label = lv_label_create(ui->system_btn3);
    lv_label_set_text(ui->system_btn3_label, "");
    lv_label_set_long_mode(ui->system_btn3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn3_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn3, 161, 284);
    lv_obj_set_size(ui->system_btn3, 79, 35);

    //Write style for system_btn3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn3, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_btn3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_btn3, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_btn3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn4
    ui->system_btn4 = lv_btn_create(ui->system);
    ui->system_btn4_label = lv_label_create(ui->system_btn4);
    lv_label_set_text(ui->system_btn4_label, "");
    lv_label_set_long_mode(ui->system_btn4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn4_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn4, 241, 284);
    lv_obj_set_size(ui->system_btn4, 79, 35);

    //Write style for system_btn4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn4, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_btn4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_btn4, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_btn4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn5
    ui->system_btn5 = lv_btn_create(ui->system);
    ui->system_btn5_label = lv_label_create(ui->system_btn5);
    lv_label_set_text(ui->system_btn5_label, "");
    lv_label_set_long_mode(ui->system_btn5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn5_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn5, 321, 284);
    lv_obj_set_size(ui->system_btn5, 79, 35);

    //Write style for system_btn5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn5, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_btn5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_btn5, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_btn5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn6
    ui->system_btn6 = lv_btn_create(ui->system);
    ui->system_btn6_label = lv_label_create(ui->system_btn6);
    lv_label_set_text(ui->system_btn6_label, "");
    lv_label_set_long_mode(ui->system_btn6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn6_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn6, 401, 284);
    lv_obj_set_size(ui->system_btn6, 78, 35);

    //Write style for system_btn6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_btn6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_btn6, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_btn6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_btn6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn6, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_label_param8
    ui->system_label_param8 = lv_label_create(ui->system);
    lv_label_set_text(ui->system_label_param8, "");
    lv_label_set_long_mode(ui->system_label_param8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_label_param8, 0, 263);
    lv_obj_set_size(ui->system_label_param8, 480, 20);

    //Write style for system_label_param8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_label_param8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_label_param8, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_label_param8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_label_param8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_label_param8, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_label_param8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_label_param8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_label_line1
    ui->system_label_line1 = lv_label_create(ui->system);
    lv_label_set_text(ui->system_label_line1, "");
    lv_label_set_long_mode(ui->system_label_line1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_label_line1, 1, 34);
    lv_obj_set_size(ui->system_label_line1, 480, 3);

    //Write style for system_label_line1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_label_line1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_label_line1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_label_line1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_label_line1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_label_line1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_label_line1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_label_line1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn_menu1
    ui->system_btn_menu1 = lv_btn_create(ui->system);
    ui->system_btn_menu1_label = lv_label_create(ui->system_btn_menu1);
    lv_label_set_text(ui->system_btn_menu1_label, " 标准");
    lv_label_set_long_mode(ui->system_btn_menu1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn_menu1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn_menu1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn_menu1_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn_menu1, 1, 1);
    lv_obj_set_size(ui->system_btn_menu1, 57, 35);

    //Write style for system_btn_menu1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_btn_menu1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn_menu1, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn_menu1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn_menu1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn_menu1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn_menu1, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn_menu1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn_menu1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn_menu1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn_menu2
    ui->system_btn_menu2 = lv_btn_create(ui->system);
    ui->system_btn_menu2_label = lv_label_create(ui->system_btn_menu2);
    lv_label_set_text(ui->system_btn_menu2_label, " 调制");
    lv_label_set_long_mode(ui->system_btn_menu2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn_menu2_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn_menu2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn_menu2_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn_menu2, 60, 1);
    lv_obj_set_size(ui->system_btn_menu2, 57, 35);

    //Write style for system_btn_menu2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_btn_menu2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn_menu2, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn_menu2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn_menu2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn_menu2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn_menu2, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn_menu2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn_menu2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn_menu2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn_menu3
    ui->system_btn_menu3 = lv_btn_create(ui->system);
    ui->system_btn_menu3_label = lv_label_create(ui->system_btn_menu3);
    lv_label_set_text(ui->system_btn_menu3_label, " 扫描");
    lv_label_set_long_mode(ui->system_btn_menu3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn_menu3_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn_menu3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn_menu3_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn_menu3, 119, 1);
    lv_obj_set_size(ui->system_btn_menu3, 57, 35);

    //Write style for system_btn_menu3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_btn_menu3, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn_menu3, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn_menu3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn_menu3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn_menu3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn_menu3, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn_menu3, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn_menu3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn_menu3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn_menu4
    ui->system_btn_menu4 = lv_btn_create(ui->system);
    ui->system_btn_menu4_label = lv_label_create(ui->system_btn_menu4);
    lv_label_set_text(ui->system_btn_menu4_label, " 脉冲");
    lv_label_set_long_mode(ui->system_btn_menu4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn_menu4_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn_menu4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn_menu4_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn_menu4, 178, 1);
    lv_obj_set_size(ui->system_btn_menu4, 57, 35);

    //Write style for system_btn_menu4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn_menu4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn_menu4, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn_menu4, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn_menu4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn_menu4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_btn_menu4, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn_menu4, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn_menu4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn_menu4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn_menu5
    ui->system_btn_menu5 = lv_btn_create(ui->system);
    ui->system_btn_menu5_label = lv_label_create(ui->system_btn_menu5);
    lv_label_set_text(ui->system_btn_menu5_label, " 谐波");
    lv_label_set_long_mode(ui->system_btn_menu5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn_menu5_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn_menu5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn_menu5_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn_menu5, 237, 1);
    lv_obj_set_size(ui->system_btn_menu5, 57, 35);

    //Write style for system_btn_menu5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_btn_menu5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn_menu5, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn_menu5, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn_menu5, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn_menu5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn_menu5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_btn_menu5, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn_menu5, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn_menu5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn_menu5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_btn_menu6
    ui->system_btn_menu6 = lv_btn_create(ui->system);
    ui->system_btn_menu6_label = lv_label_create(ui->system_btn_menu6);
    lv_label_set_text(ui->system_btn_menu6_label, " 用户");
    lv_label_set_long_mode(ui->system_btn_menu6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn_menu6_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn_menu6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn_menu6_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn_menu6, 296, 1);
    lv_obj_set_size(ui->system_btn_menu6, 57, 35);

    //Write style for system_btn_menu6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_btn_menu6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn_menu6, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn_menu6, lv_color_hex(0x505050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn_menu6, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn_menu6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn_menu6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_btn_menu6, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn_menu6, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn_menu6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn_menu6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    ui->system_btn_menu7 = lv_btn_create(ui->system);
    ui->system_btn_menu7_label = lv_label_create(ui->system_btn_menu7);
    lv_label_set_text(ui->system_btn_menu7_label, " 系统");
    lv_label_set_long_mode(ui->system_btn_menu7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->system_btn_menu7_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->system_btn_menu7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->system_btn_menu7_label, LV_PCT(100));
    lv_obj_set_pos(ui->system_btn_menu7, 355, 1);
    lv_obj_set_size(ui->system_btn_menu7, 57, 35);

    //Write style for system_btn_menu7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_btn_menu7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_btn_menu7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_btn_menu7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_btn_menu7, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_btn_menu7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_btn_menu7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_btn_menu7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_btn_menu7, lv_color_hex(0xcfb53b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_btn_menu7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_btn_menu7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_label_param1
    ui->system_label_param1 = lv_label_create(ui->system);
    lv_label_set_text(ui->system_label_param1, " 电池 00 %");
    lv_label_set_long_mode(ui->system_label_param1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_label_param1, 5, 85);
    lv_obj_set_size(ui->system_label_param1, 230, 20);

    //Write style for system_label_param1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_label_param1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_label_param1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_label_param1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_label_param1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_label_param1, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_label_param1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_label_param1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_label_param2
    ui->system_label_param2 = lv_label_create(ui->system);
    lv_label_set_text(ui->system_label_param2, " 系统 V1.0 By Greentor");
    lv_label_set_long_mode(ui->system_label_param2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_label_param2, 5, 225);
    lv_obj_set_size(ui->system_label_param2, 230, 20);

    //Write style for system_label_param2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_label_param2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_label_param2, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_label_param2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_label_param2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_label_param2, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_label_param2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_label_param2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_sw_oe
    ui->system_sw_oe = lv_switch_create(ui->system);
    lv_obj_set_pos(ui->system_sw_oe, 103, 45);
    lv_obj_set_size(ui->system_sw_oe, 60, 30);

    //Write style for system_sw_oe, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_sw_oe, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_sw_oe, lv_color_hex(0x0c0d0a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_sw_oe, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_sw_oe, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_sw_oe, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_sw_oe, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_sw_oe, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_sw_oe, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_sw_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for system_sw_oe, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->system_sw_oe, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->system_sw_oe, lv_color_hex(0x267e48), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->system_sw_oe, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->system_sw_oe, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for system_sw_oe, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_sw_oe, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_sw_oe, lv_color_hex(0xe06105), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_sw_oe, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_sw_oe, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_sw_oe, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes system_label_oe
    ui->system_label_oe = lv_label_create(ui->system);
    lv_label_set_text(ui->system_label_oe, " 通道0输出");
    lv_label_set_long_mode(ui->system_label_oe, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_label_oe, 5, 50);
    lv_obj_set_size(ui->system_label_oe, 95, 20);

    //Write style for system_label_oe, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_label_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_label_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_label_oe, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_label_oe, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_label_oe, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_label_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_label_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_label_oe, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_label_oe, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_label_oe, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_label_oe, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_label_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_label_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_label_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_label_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_label_oe, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_sw_oe1
    ui->system_sw_oe1 = lv_switch_create(ui->system);
    lv_obj_set_pos(ui->system_sw_oe1, 270, 45);
    lv_obj_set_size(ui->system_sw_oe1, 60, 30);

    //Write style for system_sw_oe1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_sw_oe1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_sw_oe1, lv_color_hex(0x0c0d0a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_sw_oe1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_sw_oe1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_sw_oe1, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_sw_oe1, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_sw_oe1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_sw_oe1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_sw_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for system_sw_oe1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->system_sw_oe1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->system_sw_oe1, lv_color_hex(0x267e48), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->system_sw_oe1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->system_sw_oe1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for system_sw_oe1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_sw_oe1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_sw_oe1, lv_color_hex(0xe06105), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_sw_oe1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_sw_oe1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_sw_oe1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes system_label_oe1
    ui->system_label_oe1 = lv_label_create(ui->system);
    lv_label_set_text(ui->system_label_oe1, " 通道1输出");
    lv_label_set_long_mode(ui->system_label_oe1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_label_oe1, 175, 50);
    lv_obj_set_size(ui->system_label_oe1, 95, 20);

    //Write style for system_label_oe1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_label_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_label_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_label_oe1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_label_oe1, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_label_oe1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_label_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_label_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_label_oe1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_label_oe1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_label_oe1, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_label_oe1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_label_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_label_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_label_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_label_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_label_oe1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_label_buzz
    ui->system_label_buzz = lv_label_create(ui->system);
    lv_label_set_text(ui->system_label_buzz, " 按键声音");
    lv_label_set_long_mode(ui->system_label_buzz, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_label_buzz, 185, 90);
    lv_obj_set_size(ui->system_label_buzz, 95, 20);

    //Write style for system_label_buzz, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_label_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_label_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_label_buzz, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_label_buzz, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_label_buzz, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_label_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_label_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_label_buzz, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_label_buzz, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_label_buzz, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_label_buzz, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_label_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_label_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_label_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_label_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_label_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes system_sw_buzz
    ui->system_sw_buzz = lv_switch_create(ui->system);
    lv_obj_set_pos(ui->system_sw_buzz, 270, 85);
    lv_obj_set_size(ui->system_sw_buzz, 60, 30);

    //Write style for system_sw_buzz, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_sw_buzz, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_sw_buzz, lv_color_hex(0x0c0d0a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_sw_buzz, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_sw_buzz, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_sw_buzz, 153, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_sw_buzz, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_sw_buzz, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_sw_buzz, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_sw_buzz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for system_sw_buzz, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->system_sw_buzz, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->system_sw_buzz, lv_color_hex(0x267e48), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->system_sw_buzz, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->system_sw_buzz, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for system_sw_buzz, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->system_sw_buzz, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_sw_buzz, lv_color_hex(0xe06105), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_sw_buzz, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_sw_buzz, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_sw_buzz, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes system_dropdown_rom
    ui->system_dropdown_rom = lv_dropdown_create(ui->system);
    lv_dropdown_set_options(ui->system_dropdown_rom, "32K\n128K\n256K\n512K\n1M\n2M\n4M\n8M\n16M\n32M");
    lv_obj_set_pos(ui->system_dropdown_rom, 96, 118);
    lv_obj_set_size(ui->system_dropdown_rom, 130, 30);

    //Write style for system_dropdown_rom, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->system_dropdown_rom, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_dropdown_rom, &lv_font_montserrat_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_dropdown_rom, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->system_dropdown_rom, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->system_dropdown_rom, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->system_dropdown_rom, lv_color_hex(0x30e37a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->system_dropdown_rom, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_dropdown_rom, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_dropdown_rom, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_dropdown_rom, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_dropdown_rom, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_dropdown_rom, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_dropdown_rom, lv_color_hex(0x292929), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_dropdown_rom, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_dropdown_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for system_dropdown_rom, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_text_color(ui->system_dropdown_rom, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->system_dropdown_rom, &lv_font_montserrat_18, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->system_dropdown_rom, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->system_dropdown_rom, 1, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_opa(ui->system_dropdown_rom, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_color(ui->system_dropdown_rom, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_side(ui->system_dropdown_rom, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_pad_top(ui->system_dropdown_rom, 8, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_pad_left(ui->system_dropdown_rom, 6, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_pad_right(ui->system_dropdown_rom, 6, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_radius(ui->system_dropdown_rom, 3, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->system_dropdown_rom, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->system_dropdown_rom, lv_color_hex(0x3bae90), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->system_dropdown_rom, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->system_dropdown_rom, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for system_dropdown_rom, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
    lv_obj_set_style_text_color(ui->system_dropdown_rom, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui->system_dropdown_rom, &lv_font_montserrat_18, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_text_opa(ui->system_dropdown_rom, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(ui->system_dropdown_rom, 1, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_border_opa(ui->system_dropdown_rom, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_border_color(ui->system_dropdown_rom, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_border_side(ui->system_dropdown_rom, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_pad_top(ui->system_dropdown_rom, 8, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_pad_left(ui->system_dropdown_rom, 6, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_pad_right(ui->system_dropdown_rom, 6, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_radius(ui->system_dropdown_rom, 3, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->system_dropdown_rom, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->system_dropdown_rom, lv_color_hex(0x3bcba6), LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_bg_grad_dir(ui->system_dropdown_rom, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->system_dropdown_rom, 0, LV_PART_MAIN|LV_STATE_FOCUSED);

    //Write style state: LV_STATE_CHECKED for &style_system_dropdown_rom_extra_list_selected_checked
    static lv_style_t style_system_dropdown_rom_extra_list_selected_checked;
    ui_init_style(&style_system_dropdown_rom_extra_list_selected_checked);

    lv_style_set_text_color(&style_system_dropdown_rom_extra_list_selected_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_system_dropdown_rom_extra_list_selected_checked, &lv_font_montserrat_18);
    lv_style_set_text_opa(&style_system_dropdown_rom_extra_list_selected_checked, 255);
    lv_style_set_border_width(&style_system_dropdown_rom_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_system_dropdown_rom_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_system_dropdown_rom_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_system_dropdown_rom_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_system_dropdown_rom_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_system_dropdown_rom_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_system_dropdown_rom_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_system_dropdown_rom_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_dropdown_rom), &style_system_dropdown_rom_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_system_dropdown_rom_extra_list_main_default
    static lv_style_t style_system_dropdown_rom_extra_list_main_default;
    ui_init_style(&style_system_dropdown_rom_extra_list_main_default);

    lv_style_set_max_height(&style_system_dropdown_rom_extra_list_main_default, 90);
    lv_style_set_text_color(&style_system_dropdown_rom_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_system_dropdown_rom_extra_list_main_default, &lv_font_montserrat_18);
    lv_style_set_text_opa(&style_system_dropdown_rom_extra_list_main_default, 255);
    lv_style_set_border_width(&style_system_dropdown_rom_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_system_dropdown_rom_extra_list_main_default, 255);
    lv_style_set_border_color(&style_system_dropdown_rom_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_system_dropdown_rom_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_system_dropdown_rom_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_system_dropdown_rom_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_system_dropdown_rom_extra_list_main_default, lv_color_hex(0x53a1d9));
    lv_style_set_bg_grad_dir(&style_system_dropdown_rom_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_dropdown_rom), &style_system_dropdown_rom_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_system_dropdown_rom_extra_list_scrollbar_default
    static lv_style_t style_system_dropdown_rom_extra_list_scrollbar_default;
    ui_init_style(&style_system_dropdown_rom_extra_list_scrollbar_default);

    lv_style_set_radius(&style_system_dropdown_rom_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_system_dropdown_rom_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_system_dropdown_rom_extra_list_scrollbar_default, lv_color_hex(0x62b062));
    lv_style_set_bg_grad_dir(&style_system_dropdown_rom_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->system_dropdown_rom), &style_system_dropdown_rom_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes system_label_rom
    ui->system_label_rom = lv_label_create(ui->system);
    lv_label_set_text(ui->system_label_rom, " 存储深度");
    lv_label_set_long_mode(ui->system_label_rom, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->system_label_rom, 5, 123);
    lv_obj_set_size(ui->system_label_rom, 85, 20);

    //Write style for system_label_rom, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->system_label_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->system_label_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->system_label_rom, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->system_label_rom, &lv_font_ZiHunDaHei_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->system_label_rom, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->system_label_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->system_label_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->system_label_rom, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->system_label_rom, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->system_label_rom, lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->system_label_rom, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->system_label_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->system_label_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->system_label_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->system_label_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->system_label_rom, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of system.
    lv_obj_clear_flag(ui->system, LV_OBJ_FLAG_SCROLLABLE);

    system_timer = lv_timer_create(my_timer, 1000, NULL);

    //Update current screen layout.
    lv_obj_update_layout(ui->system);

    //Init events for screen.
    events_init_system(ui);
}
