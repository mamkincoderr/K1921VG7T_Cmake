/* Драйверы на несколько вызовов. Полный SPL сюда не тащим.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 */
#include "peri.h"

#include <stdio.h>

#include "bsp.h"
#include "ll_rcu.h"
#include "ll_tmr.h"
#include "systick.h"
#include "system_k1921vg7t.h"

/* 2026-10-04 00:00:00 UTC. RTC хранит только секунды. */
#define RTC_EPOCH  1791072000ul
#define SIU_UNLOCK ((uint32_t)SIU_LOCK_CODE_CHANGE << SIU_LOCK_CODE_Pos)

static void spin(uint32_t n)
{
    volatile uint32_t i;
    for (i = 0; i < n; i++) {
    }
}

/* CRC-32, отражённый полином 0xEDB88320. Эталон "123456789" = 0xCBF43926. */
static uint32_t crc32_sw(const void *data, uint32_t len)
{
    const uint8_t *p = data;
    uint32_t crc = 0xFFFFFFFFu;
    uint32_t i;

    for (i = 0; i < len; i++) {
        int b;
        crc ^= p[i];
        for (b = 0; b < 8; b++) {
            uint32_t mix = (crc & 1u) ? 0xEDB88320u : 0u;
            crc = (crc >> 1) ^ mix;
        }
    }
    return ~crc;
}

int adc_read5(uint16_t code[5])
{
    uint32_t guard;
    int n;
    int ok;

    for (n = 0; n < 5; n++) {
        code[n] = 0;
    }

    /* Такт АЦП — источник 1, не PLL. На 100 МГц SAR не пускаем. */
    ll_rcu_peripheral_init_with_source(LL_RCU_ADC, LL_RCU_CLKSEL_HSE);

    ADC->ACTL = ADC_ACTL_ADCENLDO_Msk | ADC_ACTL_RANGELDO_Msk |
                ((uint32_t)ADC_ACTL_SELRES_12bit << ADC_ACTL_SELRES_Pos) |
                ADC_ACTL_ADCEN_Msk;
    spin(SystemCoreClock / 50000u); /* LDO, около 20 мкс */
    ADC->ACTL |= ADC_ACTL_ADCSTART_Msk;

    /* Секвенсор 0, очередь из пяти каналов, запуск от GSYNC. */
    ADC->EMUX = (uint32_t)ADC_EMUX_EM0_SwReq;
    ADC->SEQ[0].SRQSEL = (0u << 0) | (1u << 4) | (2u << 8) | (3u << 12) | (4u << 16);
    ADC->SEQ[0].SRQCTL = 4u; /* RQMAX = 4, то есть запросы 0..4 */
    for (n = 0; n < 5; n++) {
        ADC->CHDELAY[n].CHDELAY = HSECLK_VAL / 10000u;
    }
    ADC->SEQSYNC = ADC_SEQSYNC_SYNC0_Msk;
    ADC->SEQEN = ADC_SEQEN_SEQEN0_Msk;

    guard = 2000000u;
    while (!ADC->ACTL_bit.ADCRDY && guard--) {
    }
    if (!ADC->ACTL_bit.ADCRDY) {
        return 0;
    }

    ADC->SEQSYNC_bit.GSYNC = 1;
    guard = 2000000u;
    while ((ADC->SEQ[0].SFLOAD & ADC_SEQ_SFLOAD_VAL_Msk) < 5u && guard--) {
    }
    ok = (ADC->SEQ[0].SFLOAD & ADC_SEQ_SFLOAD_VAL_Msk) >= 5u;

    for (n = 0; n < 5; n++) {
        code[n] = (uint16_t)(ADC->SEQ[0].SFIFO & ADC_SEQ_SFIFO_DATA_Msk);
    }
    return ok;
}

void crc_check(const void *data, uint32_t len)
{
    static const char ref_s[] = "123456789";
    uint32_t a = crc32_sw(data, len);
    uint32_t b = crc32_sw(data, len);
    uint32_t ref = crc32_sw(ref_s, 9u);
    int ok = (a == b) && (ref == 0xCBF43926u);

    /* Повтор того же буфера и отдельный эталон. Совпадение двух вызовов одно не доказывает. */
    printf("CRC %08lx %s\n", (unsigned long)a, ok ? "ok" : "FAIL");
}

static void civil_from_unix(uint32_t sec, int *Y, int *M, int *D, int *h, int *mi, int *s)
{
    int32_t z;
    int32_t era;
    uint32_t doe;
    uint32_t yoe;
    uint32_t doy;
    uint32_t mp;
    uint32_t d;
    uint32_t mo;
    int32_t y;

    *s = (int)(sec % 60u);
    sec /= 60u;
    *mi = (int)(sec % 60u);
    sec /= 60u;
    *h = (int)(sec % 24u);

    z = (int32_t)(sec / 24u) + 719468;
    era = z / 146097;
    doe = (uint32_t)(z - era * 146097);
    yoe = (doe - doe / 1460u + doe / 36524u - doe / 146096u) / 365u;
    y = (int32_t)yoe + era * 400;
    doy = doe - (365u * yoe + yoe / 4u - yoe / 100u);
    mp = (5u * doy + 2u) / 153u;
    d = doy - (153u * mp + 2u) / 5u + 1u;
    mo = (mp < 10u) ? (mp + 3u) : (mp - 9u);
    y += (mo <= 2u);
    *Y = (int)y;
    *M = (int)mo;
    *D = (int)d;
}

void rtc_start(void)
{
    uint32_t guard = 200000u;

    ll_rcu_peripheral_init(LL_RCU_RTC);
    RTC->CONTROL = 0; /* DRC = 0, FCM = 0: +1 секунда от RC */
    RTC->TIME = RTC_EPOCH;
    RTC->GPR[0].GPR = 0xA5A5u; /* ячейка общего назначения, часы не трогает */

    while (!(RTC->STATUS & RTC_STATUS_OSC_OK_Msk) && guard--) {
        spin(100u);
    }
    printf("RTC osc %u gpr %s\n",
           (RTC->STATUS & RTC_STATUS_OSC_OK_Msk) ? 1 : 0,
           (RTC->GPR[0].GPR == 0xA5A5u) ? "ok" : "FAIL");
}

void rtc_print(void)
{
    int Y, M, D, h, mi, s;
    civil_from_unix(RTC->TIME, &Y, &M, &D, &h, &mi, &s);
    printf("time %04d-%02d-%02d %02d:%02d:%02d\n", Y, M, D, h, mi, s);
    fflush(stdout);
}

void peri_poll_button(void)
{
    static int stable;
    static uint32_t mark;
    int down = bsp_button_pressed();

    /* Дребезг контакта: уровень должен продержаться 20 мс. */
    if (down == stable) {
        mark = systick_ms();
        return;
    }
    if ((systick_ms() - mark) < 20u) {
        return;
    }
    stable = down;
    mark = systick_ms();
    if (down) {
        rtc_print();
    }
}

void dac_test(void)
{
    ll_rcu_peripheral_init(LL_RCU_DAC);
    DAC->DATA12 = 2048u;
    /* DISABLE = 0 включает блок. Буфер и внутренний ИОН. */
    DAC->CONTROL = DAC_CONTROL_BUF_EN_Msk;
    DAC->SWTRIG = DAC_SWTRIG_SWTRIG_Msk;
    printf("DAC %u\n", (unsigned)(DAC->DATA12 & 0xFFFu));
}

void wdt_test(void)
{
    uint32_t load;
    int locked;

    ll_rcu_peripheral_init(LL_RCU_WDT);
    WDT->LOCK = WDT_LOCK_CODE_UNLOCK;
    WDT->CTRL = 0;              /* INTEN и RESEN выключены, сброса не будет */
    WDT->LOAD = 0x00FFFFFFu;
    load = WDT->LOAD;
    WDT->LOCK = 0;              /* любое значение, кроме ключа, закрывает запись */
    locked = (int)(WDT->LOCKSTAT & WDT_LOCKSTAT_REGWRDIS_Msk);
    printf("WDT load %s lock %s\n",
           (load == 0x00FFFFFFu) ? "ok" : "FAIL",
           locked ? "ok" : "FAIL");
}

void siu_test(void)
{
    ll_rcu_peripheral_init(LL_RCU_SIU);
    printf("SIU id %08lx rev %u serv %u\n",
           (unsigned long)SIU->CHIPID,
           (unsigned)(SIU->CHIPID & SIU_CHIPID_REV_Msk),
           (unsigned)(SIU->SERVCTL & SIU_SERVCTL_SERVSTAT_Msk));
}

void tmr32_test(void)
{
    const ll_tmr_config_t cfg = {
        .clksel = LL_TMR_CLK_SYS,
        .divider = 999u, /* SYSCLK/1000 */
        .period = 0xFFFFFFFFu,
    };
    uint32_t c0;
    uint32_t c1;

    ll_rcu_peripheral_init(LL_RCU_SIU);
    SIU->LOCK = SIU_UNLOCK; /* ключ 0xACCE55, бит LOCK сброшен */
    SIU->TMREN_bit.CNT0EN = 1;

    ll_rcu_peripheral_init(LL_RCU_TMR32_0);
    ll_tmr_init(LL_TMR(TMR32_0), &cfg);
    ll_tmr_start(LL_TMR(TMR32_0), LL_TMR_MODE_CONTINUOUS);
    c0 = ll_tmr_get_count(LL_TMR(TMR32_0));
    spin(SystemCoreClock / 1000u);
    c1 = ll_tmr_get_count(LL_TMR(TMR32_0));
    ll_tmr_stop(LL_TMR(TMR32_0));
    printf("TMR32 %lu -> %lu %s\n",
           (unsigned long)c0, (unsigned long)c1,
           (c1 != c0) ? "runs" : "stopped");
}
