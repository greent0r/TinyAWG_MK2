/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *normal;
	bool normal_del;
	lv_obj_t *normal_btn1;
	lv_obj_t *normal_btn1_label;
	lv_obj_t *normal_btn2;
	lv_obj_t *normal_btn2_label;
	lv_obj_t *normal_btn3;
	lv_obj_t *normal_btn3_label;
	lv_obj_t *normal_btn4;
	lv_obj_t *normal_btn4_label;
	lv_obj_t *normal_btn5;
	lv_obj_t *normal_btn5_label;
	lv_obj_t *normal_btn6;
	lv_obj_t *normal_btn6_label;
	lv_obj_t *normal_label_line1;
	lv_obj_t *normal_btn_menu1;
	lv_obj_t *normal_btn_menu1_label;
	lv_obj_t *normal_btn_menu2;
	lv_obj_t *normal_btn_menu2_label;
	lv_obj_t *normal_btn_menu3;
	lv_obj_t *normal_btn_menu3_label;
	lv_obj_t *normal_btn_menu4;
	lv_obj_t *normal_btn_menu4_label;
	lv_obj_t *normal_canvas1;
	lv_obj_t *normal_label_param1;
	lv_obj_t *normal_label_param2;
	lv_obj_t *normal_label_param3;
	lv_obj_t *normal_label_param4;
	lv_obj_t *normal_label_param5;
	lv_obj_t *normal_label_param6;
	lv_obj_t *normal_label_param7;
	lv_obj_t *normal_label_param8;
	lv_obj_t *normal_btn_left;
	lv_obj_t *normal_btn_left_label;
	lv_obj_t *normal_btn_up;
	lv_obj_t *normal_btn_up_label;
	lv_obj_t *normal_btn_down;
	lv_obj_t *normal_btn_down_label;
	lv_obj_t *normal_btn_right;
	lv_obj_t *normal_btn_right_label;
	lv_obj_t *normal_list_wave;
	lv_obj_t *normal_list_wave_item0;
	lv_obj_t *normal_list_wave_item1;
	lv_obj_t *normal_list_wave_item2;
	lv_obj_t *normal_list_wave_item3;
	lv_obj_t *mod;
	bool mod_del;
	lv_obj_t *mod_btn1;
	lv_obj_t *mod_btn1_label;
	lv_obj_t *mod_btn2;
	lv_obj_t *mod_btn2_label;
	lv_obj_t *mod_btn3;
	lv_obj_t *mod_btn3_label;
	lv_obj_t *mod_btn4;
	lv_obj_t *mod_btn4_label;
	lv_obj_t *mod_btn5;
	lv_obj_t *mod_btn5_label;
	lv_obj_t *mod_btn6;
	lv_obj_t *mod_btn6_label;
	lv_obj_t *mod_label_param8;
	lv_obj_t *mod_label_line1;
	lv_obj_t *mod_btn_menu1;
	lv_obj_t *mod_btn_menu1_label;
	lv_obj_t *mod_btn_menu2;
	lv_obj_t *mod_btn_menu2_label;
	lv_obj_t *mod_btn_menu3;
	lv_obj_t *mod_btn_menu3_label;
	lv_obj_t *mod_btn_menu4;
	lv_obj_t *mod_btn_menu4_label;
	lv_obj_t *mod_btn_right;
	lv_obj_t *mod_btn_right_label;
	lv_obj_t *mod_btn_down;
	lv_obj_t *mod_btn_down_label;
	lv_obj_t *mod_btn_left;
	lv_obj_t *mod_btn_left_label;
	lv_obj_t *mod_btn_up;
	lv_obj_t *mod_btn_up_label;
	lv_obj_t *mod_btn_1;
	lv_obj_t *mod_btn_1_label;
	lv_obj_t *mod_sw_1;
	lv_obj_t *mod_label_1;
	lv_obj_t *scan;
	bool scan_del;
	lv_obj_t *scan_btn1;
	lv_obj_t *scan_btn1_label;
	lv_obj_t *scan_btn2;
	lv_obj_t *scan_btn2_label;
	lv_obj_t *scan_btn3;
	lv_obj_t *scan_btn3_label;
	lv_obj_t *scan_btn4;
	lv_obj_t *scan_btn4_label;
	lv_obj_t *scan_btn5;
	lv_obj_t *scan_btn5_label;
	lv_obj_t *scan_btn6;
	lv_obj_t *scan_btn6_label;
	lv_obj_t *scan_label_param8;
	lv_obj_t *scan_label_line1;
	lv_obj_t *scan_btn_menu1;
	lv_obj_t *scan_btn_menu1_label;
	lv_obj_t *scan_btn_menu2;
	lv_obj_t *scan_btn_menu2_label;
	lv_obj_t *scan_btn_menu3;
	lv_obj_t *scan_btn_menu3_label;
	lv_obj_t *scan_btn_menu4;
	lv_obj_t *scan_btn_menu4_label;
	lv_obj_t *scan_label_param7;
	lv_obj_t *scan_label_param6;
	lv_obj_t *scan_label_param5;
	lv_obj_t *scan_label_param4;
	lv_obj_t *scan_label_param3;
	lv_obj_t *scan_label_param2;
	lv_obj_t *scan_label_param1;
	lv_obj_t *scan_sw_start;
	lv_obj_t *scan_label_start;
	lv_obj_t *scan_btn_right;
	lv_obj_t *scan_btn_right_label;
	lv_obj_t *scan_btn_down;
	lv_obj_t *scan_btn_down_label;
	lv_obj_t *scan_btn_left;
	lv_obj_t *scan_btn_left_label;
	lv_obj_t *scan_btn_up;
	lv_obj_t *scan_btn_up_label;
	lv_obj_t *scan_sw_loop;
	lv_obj_t *scan_label_loop;
	lv_obj_t *scan_list_mode;
	lv_obj_t *scan_list_mode_item0;
	lv_obj_t *scan_list_mode_item1;
	lv_obj_t *system;
	bool system_del;
	lv_obj_t *system_btn1;
	lv_obj_t *system_btn1_label;
	lv_obj_t *system_btn2;
	lv_obj_t *system_btn2_label;
	lv_obj_t *system_btn3;
	lv_obj_t *system_btn3_label;
	lv_obj_t *system_btn4;
	lv_obj_t *system_btn4_label;
	lv_obj_t *system_btn5;
	lv_obj_t *system_btn5_label;
	lv_obj_t *system_btn6;
	lv_obj_t *system_btn6_label;
	lv_obj_t *system_label_param8;
	lv_obj_t *system_label_line1;
	lv_obj_t *system_btn_menu1;
	lv_obj_t *system_btn_menu1_label;
	lv_obj_t *system_btn_menu2;
	lv_obj_t *system_btn_menu2_label;
	lv_obj_t *system_btn_menu3;
	lv_obj_t *system_btn_menu3_label;
	lv_obj_t *system_btn_menu4;
	lv_obj_t *system_btn_menu4_label;
	lv_obj_t *system_label_param1;
	lv_obj_t *system_sw_oe;
	lv_obj_t *system_label_oe;
	lv_obj_t *system_sw_1;
	lv_obj_t *system_label_1;
	lv_obj_t *system_dropdown_rom;
	lv_obj_t *system_label_rom;
	lv_obj_t *g_kb_top_layer;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_normal(lv_ui *ui);
void setup_scr_mod(lv_ui *ui);
void setup_scr_scan(lv_ui *ui);
void setup_scr_system(lv_ui *ui);

LV_FONT_DECLARE(lv_font_ZiHunDaHei_18)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_ZiHunDaHei_16)
LV_FONT_DECLARE(lv_font_montserratMedium_14)


#ifdef __cplusplus
}
#endif
#endif
