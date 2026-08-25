#include "PC_HOST.h"
#include "xscugic.h"
#include "DAC8568.h"
#include "MAX17048.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>

#define RX_RING_SIZE 262144   // 接收环形缓冲 256KB（2的幂；上传原始流式1MB时吸收主循环停顿）
#define TX_BUF_SIZE  4096
#define CMD_BUF_SIZE 256

XUartPs Uart_Ps;

static uint8_t  rx_ring[RX_RING_SIZE];
static volatile uint32_t rx_wr = 0;   // ISR写索引
static uint32_t rx_rd = 0;            // 主循环读索引
volatile uint8_t uart_rx_pending = 0; // 有数据待处理（ISR置位）
static char cmd_buf[CMD_BUF_SIZE];
static uint16_t cmd_len = 0;
static char tx_buf[TX_BUF_SIZE];

static uint8_t  dirty_wave = 0, dirty_mod = 0;  // 本次命令涉及的需要刷新输出的域

// ============================================================================
// 用户波形上传（原始流式：无帧/无CRC/无ACK，直接写入user_buf，速率=串口数据率）
// ============================================================================
static uint8_t  upload_active = 0;
static uint8_t  upload_group  = 0;
static uint32_t upload_written = 0;

// ============================================================================
// UART接收：正常模式仅TOUT空闲中断（对USB适配器断开后的噪声/悬空电平天然免疫，
// 持续垃圾只会溢出FIFO而无中断）；仅用户波形上传期间临时加开RXFULL实现流式接收。
// 上传结束/中止/超时自动恢复TOUT-only。
// ============================================================================
static void uart_rx_mode_normal(void)
{
    XUartPs_SetInterruptMask(&Uart_Ps, XUARTPS_IXR_TOUT);
}
static void uart_rx_mode_upload(void)
{
    XUartPs_SetInterruptMask(&Uart_Ps, XUARTPS_IXR_RXFULL | XUARTPS_IXR_TOUT);
}

void uart_init()
{
    XUartPs_Config *uart_cfg = XUartPs_LookupConfig(XPS_UART0_BASEADDR);
    XUartPs_CfgInitialize(&Uart_Ps, uart_cfg, uart_cfg->BaseAddress);
    XUartPs_SetOperMode(&Uart_Ps, XUARTPS_OPER_MODE_NORMAL);
    XUartPs_SetBaudRate(&Uart_Ps, 2000000);
    XUartPs_SetRecvTimeout(&Uart_Ps, 4);
    uart_rx_mode_normal();
}

// UART中断处理函数：排空FIFO到环形缓冲（有界XUartPs_Recv，必然返回）
void uart_intr_handler(void *call_back_ref)
{
    (void)call_back_ref;
    u32 base = Uart_Ps.Config.BaseAddress;
    u32 isr = XUartPs_ReadReg(base, XUARTPS_IMR_OFFSET);
    isr &= XUartPs_ReadReg(base, XUARTPS_ISR_OFFSET);

    if (isr & (XUARTPS_IXR_RXFULL | XUARTPS_IXR_TOUT)) {
        uint8_t tmp[64];   // 有界排空（单次最多FIFO深度64字节）
        u16 n = XUartPs_Recv(&Uart_Ps, tmp, sizeof(tmp));
        for (u16 i = 0; i < n; i++) {
            uint32_t nw = (rx_wr + 1) & (RX_RING_SIZE - 1);
            if (nw != rx_rd) {          // 环形未满则写入
                rx_ring[rx_wr] = tmp[i];
                rx_wr = nw;
            }                           // 满则丢弃（256KB环形实际不会满）
        }
        XUartPs_WriteReg(base, XUARTPS_ISR_OFFSET, isr & (XUARTPS_IXR_RXFULL | XUARTPS_IXR_TOUT));
        uart_rx_pending = 1;
    }
}

// 上传超时看门狗：SCU定时器ISR每~500ns调用一次；上传中断开后超时自动退出并恢复TOUT-only
#define UPLOAD_TIMEOUT_TICKS 10000000u   // ~5秒
static volatile uint32_t upload_ticks = 0;
void pc_upload_tick(void)
{
    if (!upload_active) return;
    if (++upload_ticks > UPLOAD_TIMEOUT_TICKS) {
        upload_active = 0;
        upload_written = 0;
        uart_rx_mode_normal();
        Uart_Send((u8 *)"ABRT\n", 6);
    }
}

int Uart_Send(u8 *sendbuf, int length)
{
    // 整段交给驱动发送（内部按TX FIFO空间自动等待），避免逐字节轮询开销
    return XUartPs_Send(&Uart_Ps, sendbuf, length);
}

// ============================================================================
// 发送与格式化
// ============================================================================
static void uart_send_str(const char *s)
{
    Uart_Send((u8 *)s, (int)strlen(s));
}

// 定点小数格式化（不依赖printf的%f，nano newlib下也可靠），返回buf
static char *fmt_f(char *buf, double v, int dec)
{
    int neg = 0;
    if (v < 0) { neg = 1; v = -v; }
    long long scale = 1;
    for (int i = 0; i < dec; i++) scale *= 10;
    long long scaled = (long long)(v * scale + 0.5);
    long long ip = scaled / scale, fp = scaled % scale;
    int n = 0;
    if (neg) buf[n++] = '-';
    n += sprintf(buf + n, "%lld", ip);
    if (dec > 0) {
        buf[n++] = '.';
        char tmp[24];
        int t = sprintf(tmp, "%lld", fp);
        for (int i = t; i < dec; i++) buf[n++] = '0';
        memcpy(buf + n, tmp, t);
        n += t;
    }
    buf[n] = 0;
    return buf;
}

// ============================================================================
// 查询状态：输出一行 STATUS 全部参数
// ============================================================================
static void pc_send_status(void)
{
    wave_t *w = p_wave;
    mod_t *m = p_mod;
    scan_t *s = p_scan;
    harmonic_t *h = &harmonic[dds_ch];
    burst_t *b = &burst[dds_ch];
    char tmp[24];
    uint32_t g = XGpio_DiscreteRead(&xgpio, 1);
    char *p = tx_buf;

    p += sprintf(p, "STATUS ch=%u wave=%lu", dds_ch, (unsigned long)w->wave_sel);
    p += sprintf(p, " freq=%s", fmt_f(tmp, w->freq, 3));
    p += sprintf(p, " vpp=%s", fmt_f(tmp, w->vpp, 3));
    p += sprintf(p, " offset=%s", fmt_f(tmp, w->offset, 3));
    p += sprintf(p, " phase=%s", fmt_f(tmp, w->phase, 2));
    p += sprintf(p, " duty=%s", fmt_f(tmp, w->duty_cycle, 3));
    p += sprintf(p, " sym=%s", fmt_f(tmp, w->symmetry, 3));
    p += sprintf(p, " rising=%u", w->rising);
    p += sprintf(p, " zc=%lu", (unsigned long)w->zero_crossings);
    p += sprintf(p, " decay=%s", fmt_f(tmp, w->decay_factor, 3));
    p += sprintf(p, " hr=%lu", (unsigned long)w->heart_rate);
    p += sprintf(p, " steps=%lu", (unsigned long)w->steps);
    p += sprintf(p, " cycles=%lu", (unsigned long)w->cycles);
    p += sprintf(p, " damp=%s", fmt_f(tmp, w->damping, 3));
    p += sprintf(p, " trise=%s", fmt_f(tmp, w->trap_rise, 3));
    p += sprintf(p, " rcw=%s", fmt_f(tmp, w->rc_width, 3));
    p += sprintf(p, " gaussw=%s", fmt_f(tmp, w->gauss_width, 3));
    p += sprintf(p, " dpw=%s", fmt_f(tmp, w->dp_width, 3));
    p += sprintf(p, " erise=%s", fmt_f(tmp, w->exp_rise_rate, 3));
    p += sprintf(p, " lw=%s", fmt_f(tmp, w->lorentz_width, 3));
    p += sprintf(p, " rpulses=%lu", (unsigned long)w->rand_pulses);
    p += sprintf(p, " ssteep=%s", fmt_f(tmp, w->smooth_steep, 3));
    p += sprintf(p, " sna=%s", fmt_f(tmp, w->sine_noise_amp, 3));
    p += sprintf(p, " qna=%s", fmt_f(tmp, w->square_noise_amp, 3));
    p += sprintf(p, " ewave=%s", fmt_f(tmp, w->exp_wave_rate, 3));
    p += sprintf(p, " rsq=%s", fmt_f(tmp, w->round_sq, 3));
    p += sprintf(p, " rtr=%s", fmt_f(tmp, w->round_tr, 3));
    p += sprintf(p, " rw=%s", fmt_f(tmp, w->rect_width, 3));
    p += sprintf(p, " uduty=%s", fmt_f(tmp, w->uni_duty, 3));
    p += sprintf(p, " prbs=%lu", (unsigned long)w->prbs_order);
    p += sprintf(p, " mod_en=%u mod_mode=%u", m->is_modding, m->mode);
    p += sprintf(p, " mod_base=%s", fmt_f(tmp, m->base, 3));
    p += sprintf(p, " mod_carr=%s", fmt_f(tmp, m->carriar, 3));
    p += sprintf(p, " mod_depth=%s", fmt_f(tmp, m->depth, 3));
    p += sprintf(p, " mod_dev=%s", fmt_f(tmp, m->delta_f, 3));
    p += sprintf(p, " mod_index=%s", fmt_f(tmp, m->pm_index, 3));
    p += sprintf(p, " scan_start=%s", fmt_f(tmp, s->start, 3));
    p += sprintf(p, " scan_end=%s", fmt_f(tmp, s->end, 3));
    p += sprintf(p, " scan_points=%lu", (unsigned long)s->point);
    p += sprintf(p, " scan_intv=%lu", (unsigned long)s->time_interval_ns);
    p += sprintf(p, " scan_mode=%lu scan_loop=%u scan_run=%u",
                 (unsigned long)s->scan_mode, s->is_loop, s->is_running);

    // 谐波
    p += sprintf(p, " h_en=%u h_count=%u h_idx=%u", h->enable, h->count, h->idx);
    for (int i = 0; i < HARM_MAX; i++) {
        p += sprintf(p, " h_amp%d=%s", i + 1, fmt_f(tmp, h->amp[i], 3));
    }
    for (int i = 0; i < HARM_MAX; i++) {
        p += sprintf(p, " h_ph%d=%s", i + 1, fmt_f(tmp, h->phase[i], 3));
    }

    // 脉冲串
    p += sprintf(p, " b_en=%u b_cycles=%lu b_phase=%s b_delay=%lu b_run=%u",
                 b->enable, (unsigned long)b->cycles, fmt_f(tmp, b->phase, 2),
                 (unsigned long)b->delay_us, b->is_running);

    // 用户波形 / 存储 / 系统
    max17048_update();
    p += sprintf(p, " u_sel=%u u_en=%u", (unsigned)user_wave_sel, (unsigned)user_wave_en[dds_ch]);
    p += sprintf(p, " depth=%u dds_sel=%u", (unsigned)(max_rom_bits - 16), (unsigned)dds_sel);
    p += sprintf(p, " buzz=%u", (unsigned)buzz_enable);
    p += sprintf(p, " bat=%u batv=%u", (unsigned)Battery_Soc, (unsigned)Battery_Voltage);
    p += sprintf(p, " out0=%u out1=%u",
                 (unsigned)(!(g & K0)), (unsigned)(!(g & K1)));
    strcpy(p, "\r\n");
    uart_send_str(tx_buf);
}

// ============================================================================
// 参数设置
// ============================================================================
static int pc_set_one(const char *key, const char *val)
{
    wave_t *w = &wave[dds_ch];
    mod_t *m = &mod[dds_ch];
    scan_t *s = &scan[dds_ch];
    harmonic_t *h = &harmonic[dds_ch];
    burst_t *b = &burst[dds_ch];

    if (!strcmp(key, "ch")) {
        int v = atoi(val);
        if (v < 0 || v > 1) return 0;
        dds_ch = (uint8_t)v;
        p_wave = &wave[v]; p_mod = &mod[v]; p_scan = &scan[v];
        return 1;
    }
    if (!strcmp(key, "wave")) {
        long v = strtol(val, NULL, 0);
        if (v < 0 || v > 33) return 0;
        w->wave_sel = (uint32_t)v;
        dirty_wave = 1;
        return 1;
    }
    if (!strcmp(key, "freq"))   { w->freq = atof(val);       dirty_wave = 1; return 1; }
    if (!strcmp(key, "vpp"))    { w->vpp = atof(val);        dirty_wave = 1; return 1; }
    if (!strcmp(key, "offset")) { w->offset = atof(val);     dirty_wave = 1; return 1; }
    if (!strcmp(key, "phase"))  { w->phase = atof(val);      dirty_wave = 1; return 1; }
    if (!strcmp(key, "duty"))   { w->duty_cycle = atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "sym"))    { w->symmetry = atof(val);   dirty_wave = 1; return 1; }
    if (!strcmp(key, "rising")) { w->rising = (uint8_t)atoi(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "zc"))     { w->zero_crossings = (uint32_t)strtol(val, NULL, 0); dirty_wave = 1; return 1; }
    if (!strcmp(key, "decay"))  { w->decay_factor = (float)atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "hr"))     { w->heart_rate = (uint32_t)strtol(val, NULL, 0); dirty_wave = 1; return 1; }
    if (!strcmp(key, "steps"))  { w->steps = (uint32_t)strtol(val, NULL, 0); dirty_wave = 1; return 1; }
    if (!strcmp(key, "cycles")) { w->cycles = (uint32_t)strtol(val, NULL, 0); dirty_wave = 1; return 1; }
    if (!strcmp(key, "damp"))   { w->damping = atof(val);    dirty_wave = 1; return 1; }
    if (!strcmp(key, "trise"))  { w->trap_rise = atof(val);  dirty_wave = 1; return 1; }
    if (!strcmp(key, "rcw"))    { w->rc_width = atof(val);   dirty_wave = 1; return 1; }
    if (!strcmp(key, "gaussw")) { w->gauss_width = atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "dpw"))    { w->dp_width = atof(val);   dirty_wave = 1; return 1; }
    if (!strcmp(key, "erise"))  { w->exp_rise_rate = atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "lw"))     { w->lorentz_width = atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "rpulses")){ w->rand_pulses = (uint32_t)strtol(val, NULL, 0); dirty_wave = 1; return 1; }
    if (!strcmp(key, "ssteep")) { w->smooth_steep = atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "sna"))    { w->sine_noise_amp = atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "qna"))    { w->square_noise_amp = atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "ewave"))  { w->exp_wave_rate = atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "rsq"))    { w->round_sq = atof(val);   dirty_wave = 1; return 1; }
    if (!strcmp(key, "rtr"))    { w->round_tr = atof(val);   dirty_wave = 1; return 1; }
    if (!strcmp(key, "rw"))     { w->rect_width = atof(val); dirty_wave = 1; return 1; }
    if (!strcmp(key, "uduty"))  { w->uni_duty = atof(val);   dirty_wave = 1; return 1; }
    if (!strcmp(key, "prbs"))   { w->prbs_order = (uint32_t)strtol(val, NULL, 0); dirty_wave = 1; return 1; }

    if (!strcmp(key, "m_en")) {
        m->is_modding = (uint8_t)atoi(val);
        if (m->is_modding) s->is_running = 0;   // 调制开启时停扫频（与设备UI一致）
        dirty_mod = 1;
        return 1;
    }
    if (!strcmp(key, "m_mode")) {
        int v = atoi(val);
        if (v < 0 || v > 2) return 0;
        m->mode = (uint8_t)v;
        dirty_mod = 1;
        return 1;
    }
    if (!strcmp(key, "m_base"))  { m->base = atof(val);    dirty_mod = 1; return 1; }
    if (!strcmp(key, "m_carr"))  { m->carriar = atof(val); dirty_mod = 1; return 1; }
    if (!strcmp(key, "m_depth")) { m->depth = atof(val);   dirty_mod = 1; return 1; }
    if (!strcmp(key, "m_dev"))   { m->delta_f = atof(val); dirty_mod = 1; return 1; }
    if (!strcmp(key, "m_index")) { m->pm_index = atof(val); dirty_mod = 1; return 1; }

    if (!strcmp(key, "s_start"))  { s->start = atof(val); return 1; }
    if (!strcmp(key, "s_end"))    { s->end = atof(val); return 1; }
    if (!strcmp(key, "s_points")) { s->point = (uint32_t)strtol(val, NULL, 0); return 1; }
    if (!strcmp(key, "s_intv"))   { s->time_interval_ns = (uint32_t)strtol(val, NULL, 0); return 1; }
    if (!strcmp(key, "s_mode")) {
        int v = atoi(val);
        if (v < 0 || v > 1) return 0;
        s->scan_mode = (uint32_t)v;
        return 1;
    }
    if (!strcmp(key, "s_loop")) { s->is_loop = (uint8_t)atoi(val); return 1; }
    if (!strcmp(key, "s_run")) {
        if (atoi(val)) {
            p_mod->is_modding = 0;      // 扫频开启时停调制（与设备UI一致）
            mod_update(dds_ch);
            scan_start(dds_ch);
        } else {
            scan[dds_ch].is_running = 0;
        }
        return 1;
    }

    // ---- 谐波 ----
    if (!strcmp(key, "h_en")) {
        h->enable = (uint8_t)atoi(val);
        if (h->enable) m->is_modding = 0;   // 谐波开启时停调制（与设备UI一致）
        dirty_wave = 1;
        return 1;
    }
    if (!strcmp(key, "h_count")) {
        int v = atoi(val);
        if (v < 1 || v > HARM_MAX) return 0;
        h->count = (uint8_t)v;
        if (h->idx > h->count) h->idx = h->count;
        dirty_wave = 1;
        return 1;
    }
    if (!strcmp(key, "h_idx")) {
        int v = atoi(val);
        if (v < 1 || v > HARM_MAX) return 0;
        h->idx = (uint8_t)v;
        return 1;   // 仅切换编辑序号，不重生成
    }
    if (key[0] == 'h' && key[1] == '_' && key[2] == 'a' && key[3] == 'm' && key[4] == 'p') {
        int k = atoi(key + 5);
        if (k < 1 || k > HARM_MAX) return 0;
        h->amp[k - 1] = atof(val);
        return 1;   // 延后重生成：由 h_apply 统一触发（避免大命令超64字节）
    }
    if (key[0] == 'h' && key[1] == '_' && key[2] == 'p' && key[3] == 'h') {
        int k = atoi(key + 4);
        if (k < 1 || k > HARM_MAX) return 0;
        h->phase[k - 1] = atof(val);
        return 1;
    }
    if (!strcmp(key, "h_apply")) { dirty_wave = 1; return 1; }

    // ---- 脉冲串 ----
    if (!strcmp(key, "b_en")) {
        b->enable = (uint8_t)atoi(val);
        if (!b->enable) burst_stop(dds_ch);
        return 1;
    }
    if (!strcmp(key, "b_cycles")) { b->cycles = (uint32_t)strtol(val, NULL, 0); return 1; }
    if (!strcmp(key, "b_phase"))  { b->phase = atof(val); return 1; }
    if (!strcmp(key, "b_delay"))  { b->delay_us = (uint32_t)strtol(val, NULL, 0); return 1; }
    if (!strcmp(key, "b_trig"))   { if (atoi(val)) burst_trigger(dds_ch); return 1; }

    // ---- 用户波形 ----
    if (!strcmp(key, "u_sel")) {
        int v = atoi(val);
        if (v < 0 || v >= USER_WAVE_GROUPS) return 0;
        user_wave_sel = (uint8_t)v;
        dirty_wave = 1;   // 已开启用户波形时刷新输出
        return 1;
    }
    if (!strcmp(key, "u_en")) {
        if (atoi(val)) {
            if (user_wave_start(dds_ch) != 0) return 0;   // 存储深度超限
        } else {
            user_wave_stop(dds_ch);
        }
        return 1;
    }

    // ---- 系统 ----
    if (!strcmp(key, "depth")) {
        int v = atoi(val);
        if (v < 0 || v > 9) return 0;
        if (v != 0) {   // 切到 ddr_dds: 扫频仅32K模式, 停止所有扫频
            scan[0].is_running = 0;
            scan[1].is_running = 0;
        }
        max_rom_bits = (uint8_t)(v + 16);
        dds_sel = (v != 0) ? 1 : 0;
        if (max_rom_bits > USER_WAVE_MAX_BITS) {   // 存储深度超过1M: 用户波形不可输出
            user_wave_stop(0);
            user_wave_stop(1);
        }
        dirty_wave = 1;
        return 1;
    }
    if (!strcmp(key, "buzz")) { buzz_enable = (uint8_t)atoi(val) ? 1 : 0; return 1; }
    if (!strcmp(key, "sync")) { if (atoi(val)) DDS_sync_channels(); return 1; }
    if (!strcmp(key, "out")) {
        if (dds_ch == 0) {
            if (atoi(val)) DDS0_ON; else DDS0_OFF;
        } else {
            if (atoi(val)) DDS1_ON; else DDS1_OFF;
        }
        return 1;
    }
    if (!strcmp(key, "out0")) { if (atoi(val)) DDS0_ON; else DDS0_OFF; return 1; }
    if (!strcmp(key, "out1")) { if (atoi(val)) DDS1_ON; else DDS1_OFF; return 1; }
    return 0;
}

static void pc_set_params(char *p)
{
    dirty_wave = 0;
    dirty_mod = 0;
    int ok = 1;
    char *tok = strtok(p, " \t");
    while (tok) {
        char *eq = strchr(tok, '=');
        if (!eq) { ok = 0; break; }
        *eq = 0;
        if (!pc_set_one(tok, eq + 1)) { ok = 0; break; }
        tok = strtok(NULL, " \t");
    }
    if (dirty_wave || dirty_mod) mod_update(dds_ch);
    uart_send_str(ok ? "OK\r\n" : "ERR\r\n");
}

// ============================================================================
// DAC 6通道电压设置
// ============================================================================
static int dac_apply(char *p)
{
    float v[6];
    for (int i = 0; i < 6; i++) {
        while (*p == ' ' || *p == ',' || *p == ';' || *p == '\t' || *p == '\r' || *p == '\n') p++;
        char *end;
        v[i] = strtof(p, &end);
        if (end == p) return 0;
        p = end;
    }
    for (int i = 0; i < 6; i++) {
        if (v[i] < 0.0f) v[i] = 0.0f;
        if (v[i] > 5.0f) v[i] = 5.0f;
    }
    DAC8568_SetVolt(REFIO0,     v[0]);
    DAC8568_SetVolt(REFIO1,     v[1]);
    DAC8568_SetVolt(VG_in0,     v[2]);
    DAC8568_SetVolt(VG_in1,     v[3]);
    DAC8568_SetVolt(OFFSET_in0, v[4]);
    DAC8568_SetVolt(OFFSET_in1, v[5]);
    return 1;
}

// ============================================================================
// 命令行处理
// ============================================================================
static void pc_cmd_process_line(char *p)
{
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;

    if (p[0] == 'G' && (p[1] == 0 || p[1] == '\r' || p[1] == '\n')) {
        pc_send_status();
        return;
    }
    if (p[0] == 'D' && (p[1] == ' ' || p[1] == '\t' || p[1] == 0)) {
        uart_send_str(dac_apply(p + 1) ? "OK\r\n" : "ERR\r\n");
        return;
    }
    if (p[0] == 'U' && p[1] >= '0' && p[1] <= '9') {
        int g = atoi(p + 1);
        if (g >= 0 && g < GROUP_COUNT) {
            upload_active = 1;
            upload_group  = (uint8_t)g;
            upload_written = 0;
            upload_ticks   = 0;
            uart_rx_mode_upload();   // 上传期间临时开启RXFULL流式接收
            uart_send_str("READY\n");
        } else {
            uart_send_str("ERR\n");
        }
        return;
    }
    if (p[0] == 'S' && (p[1] == ' ' || p[1] == '\t')) {
        pc_set_params(p + 2);
        return;
    }
    // 旧格式兼容：数字开头的6个电压值
    if ((*p >= '0' && *p <= '9') || *p == '.' || *p == '-' || *p == '+') {
        uart_send_str(dac_apply(p) ? "OK\r\n" : "ERR\r\n");
        return;
    }
    uart_send_str("ERR\r\n");
}

// 主循环中调用：排空环形缓冲。上传模式=原始流式写user_buf；命令模式=按\n分帧
void pc_cmd_process(void)
{
    while (rx_rd != rx_wr) {
        uint8_t b = rx_ring[rx_rd];
        rx_rd = (rx_rd + 1) & (RX_RING_SIZE - 1);

        if (upload_active) {
            // 无确认/无校验的原始流式上传：直接写入user_buf
            if (upload_written < UPLOAD_TOTAL_BYTES) {
                ((uint8_t *)user_buf[upload_group])[upload_written++] = b;
            }
            upload_ticks = 0;   // 有数据到达，刷新上传看门狗
        } else {
            if (cmd_len >= CMD_BUF_SIZE - 1) cmd_len = 0;   // 溢出丢弃（防噪声）
            cmd_buf[cmd_len++] = (char)b;
            if (b == '\n') {
                cmd_buf[cmd_len] = 0;
                cmd_len = 0;
                pc_cmd_process_line(cmd_buf);
            }
        }
    }

    if (upload_active && upload_written >= UPLOAD_TOTAL_BYTES) {
        upload_active = 0;
        uart_rx_mode_normal();   // 上传完成恢复TOUT-only
        uart_send_str("DONE\n");
        // 若当前选中的正是该组且某通道已开启用户波形输出，刷新输出
        for (uint8_t c = 0; c < 2; c++)
            if (user_wave_en[c] && user_wave_sel == upload_group) wave_update(c);
    }
}

// 主循环中调用：处理收到的串口数据
void uart_rx_process(void)
{
    if (!uart_rx_pending) return;
    uart_rx_pending = 0;
    pc_cmd_process();
}