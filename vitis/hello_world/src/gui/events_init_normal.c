#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xparameters_ps.h"
#include "sleep.h"
#include "xgpio.h"

#include "output_ctrl.h"
#include "user_dds.h"
#include "user_dds.h"
#include "gpio.h"
#include "lcd.h"
#include "i2c.h"
#include "spi.h"
#include "DAC8568.h"
#include "max17048.h"
#include "touch.h"


#define NORMAL_PAGE_NUM 2

const char *normal_waves[] = {
    "正弦波", "方波", "三角波", "直流", "锯齿波", "噪声", "阶跃",
    "全波整流", "半波整流", "衰减正弦", "ECG", "Sinc", "指数衰减", "阶梯波",
    "梯形波", "升余弦脉冲", "高斯脉冲", "双脉冲", "指数上升", "洛伦兹脉冲", "随机脉冲", "平滑阶跃",
    "正弦加噪", "方波加噪", "抛物波", "三次波", "指数波", "升余弦方波", "圆角三角波",
    "矩形脉冲", "单极性方波", "PRBS", "巴克码", "曼彻斯特码"
};

//设置param5,6,7。第一个索引为波形序号，第二个索引为params的设置
//spinbox格式规则: digit_count=总位数(整数位+小数位), separator_position=小数位数(从右数), scale=10^小数位数
//如果单位是%，那么scale还要额外乘以100(因为内部存储是0~1的浮点数)
param_t normal_params[34][3] = {
    {{1},{1},{1}},//正弦
    {{0," 占空                          %",5,3,10000,0,10000,OFFSET(wave_t,duty_cycle),TYPE_F64},{1},{1}}, //方波
    {{0," 对称                          %",5,3,10000,0,10000,OFFSET(wave_t,symmetry),TYPE_F64},{1},{1}}, //三角波
    {{1},{1},{1}}, //直流
    {{0," 升降                          ",1,0,1,0,1,OFFSET(wave_t,rising),TYPE_U8},{1},{1}}, //锯齿波
    {{1},{1},{1}}, //噪声
    {{1},{1},{1}}, //阶跃
    {{1},{1},{1}}, //全波整流
    {{1},{1},{1}}, //半波整流
    {{0," 周期                         个",3,0,1,1,200,OFFSET(wave_t,cycles),TYPE_U32},
     {0," 阻尼                          ",4,2,100,0,1000,OFFSET(wave_t,damping),TYPE_F64},{1}
    }, //衰减正弦
    {{0," 心跳                         次",3,0,1,40,180,OFFSET(wave_t,heart_rate),TYPE_U32},{1},{1}}, //ECG
    {{0," 零点                         个",3,0,1,1,100,OFFSET(wave_t,zero_crossings),TYPE_U32},{1},{1}}, //Sinc
    {{0," 速率                          %",5,3,10000,0,10000,OFFSET(wave_t,decay_factor),TYPE_F64},{1},{1}}, //指数衰减
    {{0," 升降                          ",1,0,1,0,1,OFFSET(wave_t,rising),TYPE_U8},
     {0," 阶数                         个",4,0,1,2,1000,OFFSET(wave_t,steps),TYPE_U32},{1}
    }, //阶梯波
    {{0," 升沿                          %",5,3,10000,0,10000,OFFSET(wave_t,trap_rise),TYPE_F64},{1},{1}}, //梯形波
    {{0," 脉宽                          %",5,3,10000,0,10000,OFFSET(wave_t,rc_width),TYPE_F64},{1},{1}}, //升余弦脉冲
    {{0," 宽度                          %",5,3,10000,0,10000,OFFSET(wave_t,gauss_width),TYPE_F64},{1},{1}}, //高斯脉冲
    {{0," 脉宽                          %",5,3,10000,0,10000,OFFSET(wave_t,dp_width),TYPE_F64},{1},{1}}, //双脉冲
    {{0," 速率                          %",5,3,10000,0,10000,OFFSET(wave_t,exp_rise_rate),TYPE_F64},{1},{1}}, //指数上升
    {{0," 宽度                          %",5,3,10000,0,10000,OFFSET(wave_t,lorentz_width),TYPE_F64},{1},{1}}, //洛伦兹脉冲
    {{0," 脉数                         个",3,0,1,1,200,OFFSET(wave_t,rand_pulses),TYPE_U32},{1},{1}}, //随机脉冲
    {{0," 陡度                          %",5,3,10000,0,10000,OFFSET(wave_t,smooth_steep),TYPE_F64},{1},{1}}, //平滑阶跃
    {{0," 噪幅                          %",5,3,10000,0,10000,OFFSET(wave_t,sine_noise_amp),TYPE_F64},{1},{1}}, //正弦加噪
    {{0," 噪幅                          %",5,3,10000,0,10000,OFFSET(wave_t,square_noise_amp),TYPE_F64},{1},{1}}, //方波加噪
    {{1},{1},{1}}, //抛物波
    {{1},{1},{1}}, //三次波
    {{0," 速率                          %",5,3,10000,0,10000,OFFSET(wave_t,exp_wave_rate),TYPE_F64},{1},{1}}, //指数波
    {{0," 圆滑                          %",5,3,10000,0,10000,OFFSET(wave_t,round_sq),TYPE_F64},{1},{1}}, //升余弦方波
    {{0," 圆滑                          %",5,3,10000,0,10000,OFFSET(wave_t,round_tr),TYPE_F64},{1},{1}}, //圆角三角波
    {{0," 脉宽                          %",5,3,10000,0,10000,OFFSET(wave_t,rect_width),TYPE_F64},{1},{1}}, //矩形脉冲
    {{0," 占空                          %",5,3,10000,0,10000,OFFSET(wave_t,uni_duty),TYPE_F64},{1},{1}}, //单极性方波
    {{0," 阶数                         个",2,0,1,3,16,OFFSET(wave_t,prbs_order),TYPE_U32},{1},{1}}, //PRBS
    {{1},{1},{1}}, //巴克码
    {{1},{1},{1}}  //曼彻斯特码
};

const char* normal_btn_menu[NORMAL_PAGE_NUM][6] = {
    {"波形", "频率", "幅度", "偏置", "相位", "换页"},
    {"参数5", "参数6", "参数7", "", "", "换页"}
};
uint8_t normal_btn_page = 0;
lv_obj_t* normal_spinbox_select;
static uint8_t g_is_updating_params = 0;
static uint8_t g_is_cursor_move = 0;
char normal_wave_str[16];



static void update_normal_label_param8()
{
    char buf[32];
    strcpy(normal_wave_str, normal_waves[p_wave->wave_sel]);
    sprintf(buf, "波形:%s", normal_wave_str);
    lv_label_set_text(guider_ui.normal_label_param8, buf);
}


static void update_normal_canvas()
{
    lv_canvas_fill_bg(guider_ui.normal_canvas1, lv_color_hex(0x1d1c1c), 255);

    // 中轴线（参考线）
    static lv_point_t axis_pts[] = {{0, 60}, {220, 60}};
    lv_draw_line_dsc_t axis_dsc;
    lv_draw_line_dsc_init(&axis_dsc);
    axis_dsc.color = lv_color_hex(0xfbf7f8);
    axis_dsc.opa = 255;
    axis_dsc.width = 1;
    lv_canvas_draw_line(guider_ui.normal_canvas1, axis_pts, 2, &axis_dsc);

    // 满幅归一化：整段波形 min->底部 max->顶部，与幅度/偏置无关
    int16_t *mn = wave_preview_min[dds_ch];
    int16_t *mx = wave_preview_max[dds_ch];
    int32_t g_min = mn[0], g_max = mx[0];
    for (int i = 1; i < WAVE_PREVIEW_POINTS; i++) {
        if (mn[i] < g_min) g_min = mn[i];
        if (mx[i] > g_max) g_max = mx[i];
    }
    if (g_max - g_min < 1) g_max = g_min + 1;
    const int32_t span = g_max - g_min;

    lv_draw_line_dsc_t wav_dsc;
    lv_draw_line_dsc_init(&wav_dsc);
    wav_dsc.color = (dds_ch == 0) ? lv_color_hex(0xfffd00) : lv_color_hex(0x85fffe);
    wav_dsc.opa = 255;
    wav_dsc.width = 2;

    // 连续曲线：取每列中点连线
    static lv_point_t mid_pts[WAVE_PREVIEW_POINTS];
    for (int i = 0; i < WAVE_PREVIEW_POINTS; i++) {
        int32_t mid = ((int32_t)mx[i] + mn[i]) / 2;
        mid_pts[i].x = i;
        mid_pts[i].y = 2 + (int)((g_max - mid) * 116 / span);
        if (mid_pts[i].y < 0) mid_pts[i].y = 0;
        if (mid_pts[i].y > 119) mid_pts[i].y = 119;
    }
    lv_canvas_draw_line(guider_ui.normal_canvas1, mid_pts, WAVE_PREVIEW_POINTS, &wav_dsc);

    // 快沿/尖峰：跨度大的列补画竖条，保证方波边沿、脉冲清晰
    for (int i = 0; i < WAVE_PREVIEW_POINTS; i++) {
        int y1 = 2 + (int)((g_max - (int32_t)mx[i]) * 116 / span);
        int y2 = 2 + (int)((g_max - (int32_t)mn[i]) * 116 / span);
        if (y1 > y2) { int t = y1; y1 = y2; y2 = t; }
        if (y2 - y1 <= 3) continue;
        if (y1 < 0) y1 = 0;
        if (y2 > 119) y2 = 119;
        lv_point_t bar[2] = {{i, y1}, {i, y2}};
        lv_canvas_draw_line(guider_ui.normal_canvas1, bar, 2, &wav_dsc);
    }
}

static void update_normal_btn()
{
    lv_label_set_text(guider_ui.normal_btn1_label, normal_btn_menu[normal_btn_page][0]);
    lv_label_set_text(guider_ui.normal_btn2_label, normal_btn_menu[normal_btn_page][1]);
    lv_label_set_text(guider_ui.normal_btn3_label, normal_btn_menu[normal_btn_page][2]);
    lv_label_set_text(guider_ui.normal_btn4_label, normal_btn_menu[normal_btn_page][3]);
    lv_label_set_text(guider_ui.normal_btn5_label, normal_btn_menu[normal_btn_page][4]);
    lv_label_set_text(guider_ui.normal_btn6_label, normal_btn_menu[normal_btn_page][5]);
}

static void update_normal_params()
{
    g_is_updating_params = 1;
    lv_spinbox_set_value(guider_ui.normal_spinbox_1, p_wave->freq * 10);
    lv_spinbox_set_value(guider_ui.normal_spinbox_2, p_wave->vpp * 1000);
    lv_spinbox_set_value(guider_ui.normal_spinbox_3, p_wave->offset * 1000);
    lv_spinbox_set_value(guider_ui.normal_spinbox_4, p_wave->phase * 100);
    param_t param;    
    param = normal_params[p_wave->wave_sel][0];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.normal_spinbox_5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.normal_label_param5, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.normal_spinbox_5, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.normal_label_param5, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.normal_spinbox_5, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.normal_spinbox_5, param.min, param.max);
        lv_spinbox_set_value(guider_ui.normal_spinbox_5, param_get_scaled_value(p_wave, &param));
        lv_label_set_text(guider_ui.normal_label_param5, param.label);
    }
    param = normal_params[p_wave->wave_sel][1];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.normal_spinbox_6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.normal_label_param6, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.normal_spinbox_6, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.normal_label_param6, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.normal_spinbox_6, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.normal_spinbox_6, param.min, param.max);
        lv_spinbox_set_value(guider_ui.normal_spinbox_6, param_get_scaled_value(p_wave, &param));
        lv_label_set_text(guider_ui.normal_label_param6, param.label);
    }
    param = normal_params[p_wave->wave_sel][2];
    if(param.is_hide){
        lv_obj_add_flag(guider_ui.normal_spinbox_7, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.normal_label_param7, LV_OBJ_FLAG_HIDDEN);
    }
    else{
        lv_obj_clear_flag(guider_ui.normal_spinbox_7, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.normal_label_param7, LV_OBJ_FLAG_HIDDEN);
        lv_spinbox_set_digit_format(guider_ui.normal_spinbox_7, param.digit_count, param.separator_position);
        lv_spinbox_set_range(guider_ui.normal_spinbox_7, param.min, param.max);
        lv_spinbox_set_value(guider_ui.normal_spinbox_7, param_get_scaled_value(p_wave, &param));
        lv_label_set_text(guider_ui.normal_label_param7, param.label);
    }
    g_is_updating_params = 0;
}


static void update_normal_param_highlight(uint8_t param_idx)
{
    lv_obj_set_style_bg_color(guider_ui.normal_label_param1, param_idx == 1 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_label_param2, param_idx == 2 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_label_param3, param_idx == 3 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_label_param4, param_idx == 4 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_label_param5, param_idx == 5 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_label_param6, param_idx == 6 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_label_param7, param_idx == 7 ? lv_color_hex(0x267e48) : lv_color_hex(0x0d0d0d), LV_PART_MAIN|LV_STATE_DEFAULT);
}

static void update_ch_color(uint32_t color)
{
    lv_obj_set_style_bg_color(guider_ui.normal_btn_menu1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_btn_menu2, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_btn_menu3, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_btn_menu4, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_btn_menu5, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_btn_menu6, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_btn_menu7, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_label_line1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.normal_label_param8, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_btn_menu1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_btn_menu2, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_btn_menu3, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_btn_menu4, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_btn_menu5, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_btn_menu6, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_btn_menu7, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_label_line1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.mod_label_param8, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_btn_menu1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_btn_menu2, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_btn_menu3, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_btn_menu4, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_btn_menu5, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_btn_menu6, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_btn_menu7, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_label_line1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.scan_label_param8, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.system_btn_menu1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.system_btn_menu2, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.system_btn_menu3, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.system_btn_menu4, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.system_btn_menu5, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.system_btn_menu6, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.system_btn_menu7, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.system_label_line1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.system_label_param8, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_btn_menu1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_btn_menu2, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_btn_menu3, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_btn_menu4, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_btn_menu5, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_btn_menu6, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_btn_menu7, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_label_line1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.pulse_label_param8, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_btn_menu1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_btn_menu2, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_btn_menu3, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_btn_menu4, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_btn_menu5, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_btn_menu6, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_btn_menu7, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_label_line1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.harmonic_label_param8, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.user_btn_menu1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.user_btn_menu2, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.user_btn_menu3, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.user_btn_menu4, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.user_btn_menu5, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.user_btn_menu6, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.user_btn_menu7, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.user_label_line1, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(guider_ui.user_label_param8, lv_color_hex(color), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void normal_ch_refresh(void)
{
    update_normal_label_param8();
    update_normal_params();
    update_normal_canvas();
}


static void sw_ch_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED) return;
    lv_obj_t * status_obj = lv_event_get_target(e);
    dds_ch = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? 1 : 0;
    p_wave = &wave[dds_ch];
    p_mod = &mod[dds_ch];
    p_scan = &scan[dds_ch];
    // 通道0：黄金 #bba53e，通道1：青蓝 #85fffe
    if(dds_ch == 0) update_ch_color(0xbba53e);
    else            update_ch_color(0x85fffe);
    normal_ch_refresh();
    mod_ch_refresh();
    scan_ch_refresh();
    user_ch_refresh();
}

static void normal_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) return;
    uint8_t btn_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); // 1~6

    switch (btn_id) {
        case 1: {
            if(normal_btn_page == 0){
                if(lv_obj_has_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN)){
                    lv_obj_clear_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN);
                }
                else{
                    lv_obj_add_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN);
                }
            }
            else if(normal_btn_page == 1){
                if(!normal_params[p_wave->wave_sel][0].is_hide){
                    normal_spinbox_select = guider_ui.normal_spinbox_5;
                    update_normal_param_highlight(5);
                }
            }
            break;
        }
        case 2: {
            if(normal_btn_page == 0){
                normal_spinbox_select = guider_ui.normal_spinbox_1;
                update_normal_param_highlight(1);
            }
            else if(normal_btn_page == 1){
                if(!normal_params[p_wave->wave_sel][1].is_hide){
                    normal_spinbox_select = guider_ui.normal_spinbox_6;
                    update_normal_param_highlight(6);
                }
            }
            break;
        }
        case 3: {
            if(normal_btn_page == 0){
                normal_spinbox_select = guider_ui.normal_spinbox_2;
                update_normal_param_highlight(2);
            }
            else if(normal_btn_page == 1){
                if(!normal_params[p_wave->wave_sel][2].is_hide && p_wave->wave_sel == 3){
                    normal_spinbox_select = guider_ui.normal_spinbox_7;
                    update_normal_param_highlight(7);
                }
            }
            break;
        }
        case 4: {
            if(normal_btn_page == 0){
                normal_spinbox_select = guider_ui.normal_spinbox_3;
                update_normal_param_highlight(3);
            }
            else if(normal_btn_page == 1){
                
            }
            break;
        }
        case 5: {
            if(normal_btn_page == 0){
                normal_spinbox_select = guider_ui.normal_spinbox_4;
                update_normal_param_highlight(4);
            }
            else if(normal_btn_page == 1){
                
            }
            break;
        }
        case 6: {
            normal_btn_page = (normal_btn_page+1) % NORMAL_PAGE_NUM;
            update_normal_btn();
            break;
        }

        default:
            break;
    }
}

static void normal_btn_menu_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) return;

    lv_obj_add_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN);

    menu_target_t target = (menu_target_t)(uintptr_t)lv_event_get_user_data(e);

    switch (target) {
        case MENU_GOTO_MOD:
            ui_load_scr_animation(&guider_ui, &guider_ui.mod, guider_ui.mod_del, &guider_ui.normal_del, setup_scr_mod, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        case MENU_GOTO_SCAN:
            ui_load_scr_animation(&guider_ui, &guider_ui.scan, guider_ui.scan_del, &guider_ui.normal_del, setup_scr_scan, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        case MENU_GOTO_PULSE:
            ui_load_scr_animation(&guider_ui, &guider_ui.pulse, guider_ui.pulse_del, &guider_ui.normal_del, setup_scr_pulse, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            pulse_ch_refresh();
            break;
        case MENU_GOTO_HARMONIC:
            ui_load_scr_animation(&guider_ui, &guider_ui.harmonic, guider_ui.harmonic_del, &guider_ui.normal_del, setup_scr_harmonic, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            harmonic_ch_refresh();
            break;
        case MENU_GOTO_USER:
            ui_load_scr_animation(&guider_ui, &guider_ui.user, guider_ui.user_del, &guider_ui.normal_del, setup_scr_user, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            user_ch_refresh();
            break;
        case MENU_GOTO_SYSTEM:
            ui_load_scr_animation(&guider_ui, &guider_ui.system, guider_ui.system_del, &guider_ui.normal_del, setup_scr_system, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
            break;
        default:
            break;
    }
}

static void normal_btn_direction_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_SHORT_CLICKED && code != LV_EVENT_LONG_PRESSED_REPEAT) return;
    if (normal_spinbox_select == NULL) return;

    direction_t dir = (direction_t)(uintptr_t)lv_event_get_user_data(e);

    switch (dir) {
        case DIR_LEFT:
            g_is_cursor_move = 1;
            lv_spinbox_step_prev(normal_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_RIGHT:
            g_is_cursor_move = 1;
            lv_spinbox_step_next(normal_spinbox_select);
            g_is_cursor_move = 0;
            break;
        case DIR_UP:
            lv_spinbox_increment(normal_spinbox_select);
            break;
        case DIR_DOWN:
            lv_spinbox_decrement(normal_spinbox_select);
            break;
        default:
            break;
    }
}

static void normal_spinbox_event_handler (lv_event_t *e)
{
    if (g_is_updating_params) return;//关键
    if (g_is_cursor_move) return;//仅移动光标，不触发
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_VALUE_CHANGED) return;
    uint8_t spinbox_id = (uint8_t)(uintptr_t)lv_event_get_user_data(e); // 1~7
    switch (spinbox_id) {
	    case 1:{
            p_wave->freq = lv_spinbox_get_value(guider_ui.normal_spinbox_1) / 10.0;
            samples_play(dds_ch, p_wave->freq, p_wave->phase);
            break;
        }
	    case 2:{
            p_wave->vpp = lv_spinbox_get_value(guider_ui.normal_spinbox_2) / 1000.0;
            if (harmonic[dds_ch].enable)
                DDS_set_vpp_offset(dds_ch, p_wave->vpp * harmonic[dds_ch].vpp_comp, p_wave->offset);
            else
                DDS_set_vpp_offset(dds_ch, p_wave->vpp, p_wave->offset);
            break;
        }
	    case 3:{
            p_wave->offset = lv_spinbox_get_value(guider_ui.normal_spinbox_3) / 1000.0;
            if (harmonic[dds_ch].enable)
                DDS_set_vpp_offset(dds_ch, p_wave->vpp * harmonic[dds_ch].vpp_comp, p_wave->offset);
            else
                DDS_set_vpp_offset(dds_ch, p_wave->vpp, p_wave->offset);
            break;
        }
	    case 4:{
            p_wave->phase = lv_spinbox_get_value(guider_ui.normal_spinbox_4) / 100.0;
            samples_play(dds_ch, p_wave->freq, p_wave->phase);
            break;
        }
	    case 5:{
            if(!normal_params[p_wave->wave_sel][0].is_hide){
                param_set_raw_value(p_wave, &normal_params[p_wave->wave_sel][0], lv_spinbox_get_value(guider_ui.normal_spinbox_5));
                wave_update(dds_ch);
                update_normal_canvas();
            }
            break;
        }
	    case 6:{
            if(!normal_params[p_wave->wave_sel][1].is_hide){
                param_set_raw_value(p_wave, &normal_params[p_wave->wave_sel][1], lv_spinbox_get_value(guider_ui.normal_spinbox_6));
                wave_update(dds_ch);
                update_normal_canvas();
            }
            break;
        }
	    case 7:{
            if(!normal_params[p_wave->wave_sel][2].is_hide){
                param_set_raw_value(p_wave, &normal_params[p_wave->wave_sel][2], lv_spinbox_get_value(guider_ui.normal_spinbox_7));
                wave_update(dds_ch);
                update_normal_canvas();
            }
            break;
        }
        default:break;
	}
}

static void normal_list_wave_item_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) return;

    uint8_t wave_index = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    p_wave->wave_sel = wave_index;
    wave_update(dds_ch);
    strcpy(normal_wave_str, normal_waves[p_wave->wave_sel]);
    update_normal_label_param8();
    update_normal_params();
    update_normal_canvas();
    lv_obj_add_flag(guider_ui.normal_list_wave, LV_OBJ_FLAG_HIDDEN);
}

void events_init_normal (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->sw_ch, sw_ch_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->normal_btn1, normal_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->normal_btn2, normal_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->normal_btn3, normal_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->normal_btn4, normal_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->normal_btn5, normal_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->normal_btn6, normal_btn_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->normal_btn_menu2, normal_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_MOD);
    lv_obj_add_event_cb(ui->normal_btn_menu3, normal_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SCAN);
    lv_obj_add_event_cb(ui->normal_btn_menu4, normal_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_PULSE);
    lv_obj_add_event_cb(ui->normal_btn_menu5, normal_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_HARMONIC);
    lv_obj_add_event_cb(ui->normal_btn_menu6, normal_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_USER);
    lv_obj_add_event_cb(ui->normal_btn_menu7, normal_btn_menu_event_handler, LV_EVENT_ALL, (void*)MENU_GOTO_SYSTEM);
    lv_obj_add_event_cb(ui->normal_btn_left,  normal_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_LEFT);
    lv_obj_add_event_cb(ui->normal_btn_right, normal_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_RIGHT);
    lv_obj_add_event_cb(ui->normal_btn_up,    normal_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_UP);
    lv_obj_add_event_cb(ui->normal_btn_down,  normal_btn_direction_event_handler, LV_EVENT_ALL, (void*)DIR_DOWN);
    lv_obj_add_event_cb(ui->normal_list_wave_item0, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)0);
    lv_obj_add_event_cb(ui->normal_list_wave_item1, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->normal_list_wave_item2, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->normal_list_wave_item3, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->normal_list_wave_item4, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->normal_list_wave_item5, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->normal_list_wave_item6, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->normal_list_wave_item7, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)7);
    lv_obj_add_event_cb(ui->normal_list_wave_item8, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)8);
    lv_obj_add_event_cb(ui->normal_list_wave_item9, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)9);
    lv_obj_add_event_cb(ui->normal_list_wave_item10, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)10);
    lv_obj_add_event_cb(ui->normal_list_wave_item11, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)11);
    lv_obj_add_event_cb(ui->normal_list_wave_item12, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)12);
    lv_obj_add_event_cb(ui->normal_list_wave_item13, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)13);
    lv_obj_add_event_cb(ui->normal_list_wave_item14, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)14);
    lv_obj_add_event_cb(ui->normal_list_wave_item15, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)15);
    lv_obj_add_event_cb(ui->normal_list_wave_item16, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)16);
    lv_obj_add_event_cb(ui->normal_list_wave_item17, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)17);
    lv_obj_add_event_cb(ui->normal_list_wave_item18, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)18);
    lv_obj_add_event_cb(ui->normal_list_wave_item19, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)19);
    lv_obj_add_event_cb(ui->normal_list_wave_item20, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)20);
    lv_obj_add_event_cb(ui->normal_list_wave_item21, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)21);
    lv_obj_add_event_cb(ui->normal_list_wave_item22, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)22);
    lv_obj_add_event_cb(ui->normal_list_wave_item23, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)23);
    lv_obj_add_event_cb(ui->normal_list_wave_item24, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)24);
    lv_obj_add_event_cb(ui->normal_list_wave_item25, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)25);
    lv_obj_add_event_cb(ui->normal_list_wave_item26, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)26);
    lv_obj_add_event_cb(ui->normal_list_wave_item27, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)27);
    lv_obj_add_event_cb(ui->normal_list_wave_item28, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)28);
    lv_obj_add_event_cb(ui->normal_list_wave_item29, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)29);
    lv_obj_add_event_cb(ui->normal_list_wave_item30, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)30);
    lv_obj_add_event_cb(ui->normal_list_wave_item31, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)31);
    lv_obj_add_event_cb(ui->normal_list_wave_item32, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)32);
    lv_obj_add_event_cb(ui->normal_list_wave_item33, normal_list_wave_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)33);

    lv_obj_add_event_cb(ui->normal_spinbox_1, normal_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)1);
    lv_obj_add_event_cb(ui->normal_spinbox_2, normal_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)2);
    lv_obj_add_event_cb(ui->normal_spinbox_3, normal_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)3);
    lv_obj_add_event_cb(ui->normal_spinbox_4, normal_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)4);
    lv_obj_add_event_cb(ui->normal_spinbox_5, normal_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)5);
    lv_obj_add_event_cb(ui->normal_spinbox_6, normal_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)6);
    lv_obj_add_event_cb(ui->normal_spinbox_7, normal_spinbox_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)7);


}

void events_init(lv_ui *ui)
{

}
