/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "output_ctrl.h"

typedef enum {
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
} direction_t;

typedef enum {
    MENU_GOTO_NORMAL,
    MENU_GOTO_MOD,
    MENU_GOTO_SCAN,
    MENU_GOTO_PULSE,
    MENU_GOTO_HARMONIC,
    MENU_GOTO_USER,
    MENU_GOTO_SYSTEM
} menu_target_t;

typedef struct {
    uint8_t is_hide;
    char* label;//参数名称
    uint8_t digit_count;//总共的位数
    uint8_t separator_position;//在第几位分出小数点
    uint32_t scale;//数值缩放倍数，给目标赋值时需要获取值除以scale
    int32_t min;//最值，需要实际值乘以scale
    int32_t max;
    uintptr_t target;//参数目标对象
    uint8_t type;//参数目标类型
} param_t;

#define OFFSET(type, member) ((uintptr_t)&((type*)0)->member)


#define TYPE_I8     1   // int8_t
#define TYPE_I16    2   // int16_t
#define TYPE_I32    3   // int32_t
#define TYPE_I64    4   // int64_t
#define TYPE_U8     5   // uint8_t
#define TYPE_U16    6   // uint16_t
#define TYPE_U32    7   // uint32_t
#define TYPE_U64    8   // uint64_t
#define TYPE_F32    9   // float (32-bit)
#define TYPE_F64    10  // double (64-bit)

static inline void param_set_raw_value(uintptr_t p_dds, param_t* param, int32_t raw_val)
{
    void *target = (void*)((uintptr_t)p_dds + param->target);
    switch (param->type) {
        case TYPE_I8:   *(int8_t*)target   = (int8_t)(raw_val / param->scale); break;
        case TYPE_I16:  *(int16_t*)target  = (int16_t)(raw_val / param->scale); break;
        case TYPE_I32:  *(int32_t*)target  = (int32_t)(raw_val / param->scale); break;
        case TYPE_I64:  *(int64_t*)target  = (int64_t)(raw_val / param->scale); break;
        case TYPE_U8:   *(uint8_t*)target  = (uint8_t)(raw_val / param->scale); break;
        case TYPE_U16:  *(uint16_t*)target = (uint16_t)(raw_val / param->scale); break;
        case TYPE_U32:  *(uint32_t*)target = (uint32_t)(raw_val / param->scale); break;
        case TYPE_U64:  *(uint64_t*)target = (uint64_t)(raw_val / param->scale); break;
        case TYPE_F32:  *(float*)target    = (float)raw_val / (param->scale ? (float)param->scale : 1.0f); break;
        case TYPE_F64:  *(double*)target   = (double)raw_val / (param->scale ? (double)param->scale : 1.0); break;
        default: break;
    }
}
static inline int32_t param_get_scaled_value(uintptr_t p_dds, param_t* param)
{
    void *target = (void*)((uintptr_t)p_dds + param->target);
    switch (param->type) {
        case TYPE_I8:   return (int32_t)(*(int8_t*)target) * (int32_t)param->scale;
        case TYPE_I16:  return (int32_t)(*(int16_t*)target) * (int32_t)param->scale;
        case TYPE_I32:  return (int32_t)(*(int32_t*)target) * (int32_t)param->scale;
        case TYPE_I64:  return (int32_t)(*(int64_t*)target) * (int32_t)param->scale;
        case TYPE_U8:   return (int32_t)(*(uint8_t*)target) * (int32_t)param->scale;
        case TYPE_U16:  return (int32_t)(*(uint16_t*)target) * (int32_t)param->scale;
        case TYPE_U32:  return (int32_t)(*(uint32_t*)target) * (int32_t)param->scale;
        case TYPE_U64:  return (int32_t)(*(uint64_t*)target) * (int32_t)param->scale;
        case TYPE_F32:  return (int32_t)((*(float*)target) * (float)param->scale + 0.5f);
        case TYPE_F64:  return (int32_t)((*(double*)target) * (double)param->scale + 0.5);
        default: return 0;
    }
}

void events_init(lv_ui *ui);

void events_init_normal(lv_ui *ui);
void events_init_mod(lv_ui *ui);
void events_init_scan(lv_ui *ui);
void events_init_pulse(lv_ui *ui);
void events_init_harmonic(lv_ui *ui);
void events_init_user(lv_ui *ui);
void events_init_system(lv_ui *ui);

void normal_ch_refresh(void);
void mod_ch_refresh(void);
void scan_ch_refresh(void);
void harmonic_ch_refresh(void);
void pulse_ch_refresh(void);
void user_ch_refresh(void);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
