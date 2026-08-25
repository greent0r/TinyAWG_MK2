/*
* Copyright 2025 NXP
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
	lv_obj_t *sw_ch;//全界面共享的通道切换开关
	lv_obj_t *sw_ch_label;
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
	lv_obj_t *normal_label_param8;
	lv_obj_t *normal_label_line1;
	lv_obj_t *normal_label_param1;
	lv_obj_t *normal_btn_menu1;
	lv_obj_t *normal_btn_menu1_label;
	lv_obj_t *normal_btn_menu2;
	lv_obj_t *normal_btn_menu2_label;
	lv_obj_t *normal_btn_menu3;
	lv_obj_t *normal_btn_menu3_label;
	lv_obj_t *normal_btn_menu4;
	lv_obj_t *normal_btn_menu4_label;
	lv_obj_t *normal_btn_menu5;
	lv_obj_t *normal_btn_menu5_label;
	lv_obj_t *normal_btn_menu6;
	lv_obj_t *normal_btn_menu6_label;
	lv_obj_t *normal_btn_menu7;
	lv_obj_t *normal_btn_menu7_label;
	lv_obj_t *normal_canvas1;
	lv_obj_t *normal_label_param2;
	lv_obj_t *normal_label_param3;
	lv_obj_t *normal_label_param4;
	lv_obj_t *normal_label_param5;
	lv_obj_t *normal_label_param6;
	lv_obj_t *normal_label_param7;
	lv_obj_t *normal_btn_left;
	lv_obj_t *normal_btn_left_label;
	lv_obj_t *normal_btn_up;
	lv_obj_t *normal_btn_up_label;
	lv_obj_t *normal_btn_down;
	lv_obj_t *normal_btn_down_label;
	lv_obj_t *normal_btn_right;
	lv_obj_t *normal_btn_right_label;
	lv_obj_t *normal_list_wave;
	lv_obj_t *normal_list_wave_item0;	lv_obj_t *normal_list_wave_item1;	lv_obj_t *normal_list_wave_item2;
	lv_obj_t *normal_list_wave_item3;	lv_obj_t *normal_list_wave_item4;	lv_obj_t *normal_list_wave_item5;
	lv_obj_t *normal_list_wave_item6;	lv_obj_t *normal_list_wave_item7;	lv_obj_t *normal_list_wave_item8;
	lv_obj_t *normal_list_wave_item9;	lv_obj_t *normal_list_wave_item10;	lv_obj_t *normal_list_wave_item11;
	lv_obj_t *normal_list_wave_item12;	lv_obj_t *normal_list_wave_item13;	lv_obj_t *normal_list_wave_item14;
	lv_obj_t *normal_list_wave_item15;	lv_obj_t *normal_list_wave_item16;	lv_obj_t *normal_list_wave_item17;
	lv_obj_t *normal_list_wave_item18;	lv_obj_t *normal_list_wave_item19;	lv_obj_t *normal_list_wave_item20;
	lv_obj_t *normal_list_wave_item21;	lv_obj_t *normal_list_wave_item22;	lv_obj_t *normal_list_wave_item23;
	lv_obj_t *normal_list_wave_item24;	lv_obj_t *normal_list_wave_item25;	lv_obj_t *normal_list_wave_item26;
	lv_obj_t *normal_list_wave_item27;	lv_obj_t *normal_list_wave_item28;	lv_obj_t *normal_list_wave_item29;
	lv_obj_t *normal_list_wave_item30;	lv_obj_t *normal_list_wave_item31;	lv_obj_t *normal_list_wave_item32;
	lv_obj_t *normal_list_wave_item33;
 	lv_obj_t *normal_spinbox_1;
	lv_obj_t *normal_spinbox_2;
	lv_obj_t *normal_spinbox_3;
	lv_obj_t *normal_spinbox_4;
	lv_obj_t *normal_spinbox_5;
	lv_obj_t *normal_spinbox_6;
	lv_obj_t *normal_spinbox_7;
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
    lv_obj_t *mod_label_param1;
    lv_obj_t *mod_label_param2;
	lv_obj_t *mod_label_param3;
	lv_obj_t *mod_label_param4;
	lv_obj_t *mod_label_param5;
	lv_obj_t *mod_label_param6;
	lv_obj_t *mod_label_param7;
	lv_obj_t *mod_label_line1;
	lv_obj_t *mod_btn_menu1;
	lv_obj_t *mod_btn_menu1_label;
	lv_obj_t *mod_btn_menu2;
	lv_obj_t *mod_btn_menu2_label;
	lv_obj_t *mod_btn_menu3;
	lv_obj_t *mod_btn_menu3_label;
	lv_obj_t *mod_btn_menu4;
	lv_obj_t *mod_btn_menu4_label;
	lv_obj_t *mod_btn_menu5;
	lv_obj_t *mod_btn_menu5_label;
	lv_obj_t *mod_btn_menu6;
	lv_obj_t *mod_btn_menu6_label;
	lv_obj_t *mod_btn_menu7;
	lv_obj_t *mod_btn_menu7_label;
	lv_obj_t *mod_btn_right;
	lv_obj_t *mod_btn_right_label;
	lv_obj_t *mod_btn_down;
	lv_obj_t *mod_btn_down_label;
	lv_obj_t *mod_btn_left;
	lv_obj_t *mod_btn_left_label;
	lv_obj_t *mod_btn_up;
	lv_obj_t *mod_btn_up_label;
	lv_obj_t *mod_sw_start;
	lv_obj_t *mod_label_start;
	lv_obj_t *mod_spinbox_1;
	lv_obj_t *mod_spinbox_2;
	lv_obj_t *mod_spinbox_3;
	lv_obj_t *mod_spinbox_4;
	lv_obj_t *mod_spinbox_5;
	lv_obj_t *mod_spinbox_6;
	lv_obj_t *mod_spinbox_7;
    lv_obj_t *mod_list_mode;
    lv_obj_t *mod_list_mode_item0;
	lv_obj_t *mod_list_mode_item1;
    lv_obj_t *mod_list_mode_item2;
	lv_obj_t *mod_list_wave;
    lv_obj_t *mod_list_wave_item0;
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
	lv_obj_t *scan_btn_menu5;
	lv_obj_t *scan_btn_menu5_label;
	lv_obj_t *scan_btn_menu6;
	lv_obj_t *scan_btn_menu6_label;
	lv_obj_t *scan_btn_menu7;
	lv_obj_t *scan_btn_menu7_label;
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
	lv_obj_t *scan_list_mode;
	lv_obj_t *scan_list_mode_item0;
	lv_obj_t *scan_list_mode_item1;
	lv_obj_t *scan_sw_loop;
	lv_obj_t *scan_label_loop;
	lv_obj_t *scan_spinbox_1;
	lv_obj_t *scan_spinbox_2;
	lv_obj_t *scan_spinbox_3;
	lv_obj_t *scan_spinbox_4;
	lv_obj_t *scan_spinbox_5;
	lv_obj_t *scan_spinbox_6;
	lv_obj_t *scan_spinbox_7;
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
	lv_obj_t *system_btn_menu5;
	lv_obj_t *system_btn_menu5_label;
	lv_obj_t *system_btn_menu6;
	lv_obj_t *system_btn_menu6_label;
	lv_obj_t *system_btn_menu7;
	lv_obj_t *system_btn_menu7_label;
	lv_obj_t *system_label_param1;
	lv_obj_t *system_label_param2;
	lv_obj_t *system_sw_oe;
	lv_obj_t *system_label_oe;
	lv_obj_t *system_sw_oe1;
	lv_obj_t *system_label_oe1;
	lv_obj_t *system_sw_buzz;
	lv_obj_t *system_label_buzz;
	lv_obj_t *system_dropdown_rom;
	lv_obj_t *system_label_rom;
	lv_obj_t *pulse;
	bool pulse_del;
	lv_obj_t *pulse_btn1;	lv_obj_t *pulse_btn1_label;
	lv_obj_t *pulse_btn2;
	lv_obj_t *pulse_btn2_label;
	lv_obj_t *pulse_btn3;
	lv_obj_t *pulse_btn3_label;
	lv_obj_t *pulse_btn4;
	lv_obj_t *pulse_btn4_label;
	lv_obj_t *pulse_btn5;
	lv_obj_t *pulse_btn5_label;
	lv_obj_t *pulse_btn6;
	lv_obj_t *pulse_btn6_label;
	lv_obj_t *pulse_btn_menu1;
	lv_obj_t *pulse_btn_menu1_label;
	lv_obj_t *pulse_btn_menu2;
	lv_obj_t *pulse_btn_menu2_label;
	lv_obj_t *pulse_btn_menu3;
	lv_obj_t *pulse_btn_menu3_label;
	lv_obj_t *pulse_btn_menu4;
	lv_obj_t *pulse_btn_menu4_label;
	lv_obj_t *pulse_btn_menu5;
	lv_obj_t *pulse_btn_menu5_label;
	lv_obj_t *pulse_btn_menu6;
	lv_obj_t *pulse_btn_menu6_label;
	lv_obj_t *pulse_btn_menu7;
	lv_obj_t *pulse_btn_menu7_label;
	lv_obj_t *pulse_label_param1;
	lv_obj_t *pulse_label_param2;
	lv_obj_t *pulse_label_param3;
	lv_obj_t *pulse_label_param4;
	lv_obj_t *pulse_label_param5;
	lv_obj_t *pulse_label_param6;
	lv_obj_t *pulse_label_param7;
	lv_obj_t *pulse_spinbox_1;
	lv_obj_t *pulse_spinbox_2;
	lv_obj_t *pulse_spinbox_3;
	lv_obj_t *pulse_spinbox_4;
	lv_obj_t *pulse_spinbox_5;
	lv_obj_t *pulse_spinbox_6;
	lv_obj_t *pulse_spinbox_7;
	lv_obj_t *pulse_btn_left;
	lv_obj_t *pulse_btn_left_label;
	lv_obj_t *pulse_btn_right;
	lv_obj_t *pulse_btn_right_label;
	lv_obj_t *pulse_btn_up;
	lv_obj_t *pulse_btn_up_label;
	lv_obj_t *pulse_btn_down;
	lv_obj_t *pulse_btn_down_label;
	lv_obj_t *pulse_label_param8;
	lv_obj_t *pulse_label_line1;
	lv_obj_t *pulse_sw_start;
	lv_obj_t *pulse_label_start;
	lv_obj_t *pulse_btn_trigger;
	lv_obj_t *pulse_btn_trigger_label;
	lv_obj_t *harmonic;
	bool harmonic_del;
	lv_obj_t *harmonic_btn1;
	lv_obj_t *harmonic_btn1_label;
	lv_obj_t *harmonic_btn2;
	lv_obj_t *harmonic_btn2_label;
	lv_obj_t *harmonic_btn3;
	lv_obj_t *harmonic_btn3_label;
	lv_obj_t *harmonic_btn4;
	lv_obj_t *harmonic_btn4_label;
	lv_obj_t *harmonic_btn5;
	lv_obj_t *harmonic_btn5_label;
	lv_obj_t *harmonic_btn6;
	lv_obj_t *harmonic_btn6_label;
	lv_obj_t *harmonic_btn_menu1;
	lv_obj_t *harmonic_btn_menu1_label;
	lv_obj_t *harmonic_btn_menu2;
	lv_obj_t *harmonic_btn_menu2_label;
	lv_obj_t *harmonic_btn_menu3;
	lv_obj_t *harmonic_btn_menu3_label;
	lv_obj_t *harmonic_btn_menu4;
	lv_obj_t *harmonic_btn_menu4_label;
	lv_obj_t *harmonic_btn_menu5;
	lv_obj_t *harmonic_btn_menu5_label;
	lv_obj_t *harmonic_btn_menu6;
	lv_obj_t *harmonic_btn_menu6_label;
	lv_obj_t *harmonic_btn_menu7;
	lv_obj_t *harmonic_btn_menu7_label;
	lv_obj_t *harmonic_label_param1;
	lv_obj_t *harmonic_label_param2;
	lv_obj_t *harmonic_label_param3;
	lv_obj_t *harmonic_label_param4;
	lv_obj_t *harmonic_label_param5;
	lv_obj_t *harmonic_label_param6;
	lv_obj_t *harmonic_label_param7;
	lv_obj_t *harmonic_spinbox_1;
	lv_obj_t *harmonic_spinbox_2;
	lv_obj_t *harmonic_spinbox_3;
	lv_obj_t *harmonic_spinbox_4;
	lv_obj_t *harmonic_spinbox_5;
	lv_obj_t *harmonic_spinbox_6;
	lv_obj_t *harmonic_spinbox_7;
	lv_obj_t *harmonic_btn_left;
	lv_obj_t *harmonic_btn_left_label;
	lv_obj_t *harmonic_btn_right;
	lv_obj_t *harmonic_btn_right_label;
	lv_obj_t *harmonic_btn_up;
	lv_obj_t *harmonic_btn_up_label;
	lv_obj_t *harmonic_btn_down;
	lv_obj_t *harmonic_btn_down_label;
	lv_obj_t *harmonic_label_param8;
	lv_obj_t *harmonic_label_line1;
	lv_obj_t *harmonic_sw_start;
	lv_obj_t *harmonic_label_start;
	lv_obj_t *user;
	bool user_del;
	lv_obj_t *user_btn1;
	lv_obj_t *user_btn1_label;
	lv_obj_t *user_btn2;
	lv_obj_t *user_btn2_label;
	lv_obj_t *user_btn3;
	lv_obj_t *user_btn3_label;
	lv_obj_t *user_btn4;
	lv_obj_t *user_btn4_label;
	lv_obj_t *user_btn5;
	lv_obj_t *user_btn5_label;
	lv_obj_t *user_btn6;
	lv_obj_t *user_btn6_label;
	lv_obj_t *user_btn_menu1;
	lv_obj_t *user_btn_menu1_label;
	lv_obj_t *user_btn_menu2;
	lv_obj_t *user_btn_menu2_label;
	lv_obj_t *user_btn_menu3;
	lv_obj_t *user_btn_menu3_label;
	lv_obj_t *user_btn_menu4;
	lv_obj_t *user_btn_menu4_label;
	lv_obj_t *user_btn_menu5;
	lv_obj_t *user_btn_menu5_label;
	lv_obj_t *user_btn_menu6;
	lv_obj_t *user_btn_menu6_label;
	lv_obj_t *user_btn_menu7;
	lv_obj_t *user_btn_menu7_label;
	lv_obj_t *user_label_param8;
	lv_obj_t *user_label_line1;
	lv_obj_t *user_list_wave;
	lv_obj_t *user_list_wave_item0;	lv_obj_t *user_list_wave_item1;	lv_obj_t *user_list_wave_item2;
	lv_obj_t *user_list_wave_item3;	lv_obj_t *user_list_wave_item4;	lv_obj_t *user_list_wave_item5;
	lv_obj_t *user_list_wave_item6;	lv_obj_t *user_list_wave_item7;	lv_obj_t *user_list_wave_item8;
	lv_obj_t *user_list_wave_item9;	lv_obj_t *user_list_wave_item10;	lv_obj_t *user_list_wave_item11;
	lv_obj_t *user_list_wave_item12;	lv_obj_t *user_list_wave_item13;	lv_obj_t *user_list_wave_item14;
	lv_obj_t *user_list_wave_item15;	lv_obj_t *user_list_wave_item16;	lv_obj_t *user_list_wave_item17;
	lv_obj_t *user_list_wave_item18;	lv_obj_t *user_list_wave_item19;	lv_obj_t *user_list_wave_item20;
	lv_obj_t *user_list_wave_item21;	lv_obj_t *user_list_wave_item22;	lv_obj_t *user_list_wave_item23;
	lv_obj_t *user_list_wave_item24;	lv_obj_t *user_list_wave_item25;	lv_obj_t *user_list_wave_item26;
	lv_obj_t *user_list_wave_item27;	lv_obj_t *user_list_wave_item28;	lv_obj_t *user_list_wave_item29;
	lv_obj_t *user_list_wave_item30;	lv_obj_t *user_list_wave_item31;
	lv_obj_t *user_sw_en;
	lv_obj_t *user_label_en;
	lv_obj_t *g_kb_top_layer;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

// 弹框列表项快捷创建：add_btn + 固定宽高 + 文字居中 + 可选样式，一行创建一项
lv_obj_t *ui_list_add_item(lv_obj_t *list, const char *text, uint16_t w, uint16_t h, lv_style_t *style);

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
void setup_scr_pulse(lv_ui *ui);
void setup_scr_harmonic(lv_ui *ui);
void setup_scr_user(lv_ui *ui);
void setup_scr_system(lv_ui *ui);

LV_FONT_DECLARE(lv_font_ZiHunDaHei_18)
// LV_FONT_DECLARE(lv_font_montserratMedium_18)


#ifdef __cplusplus
}
#endif
#endif
