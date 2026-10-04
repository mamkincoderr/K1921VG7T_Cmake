/* Пример для NIIET-MINI-K1921VG7T: короткий тест периферии, затем мигание B0.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 *
 * Перед сборкой распакуйте pack\k1921vg7t-tools.7z в папку tools.
 * Должны появиться tools\gcc и tools\openocd. Без них сборка не запустится.
 *
 * Тексты на UART латиницей. Кнопка B1 в цикле мигания печатает календарь.
 */
#include <stdio.h>

#include "bsp.h"
#include "console.h"
#include "ll_gpio.h"
#include "peri.h"
#include "systick.h"
#include "system_k1921vg7t.h"

static void delay_btn(uint32_t ms)
{
    uint32_t t0 = systick_ms();
    while ((systick_ms() - t0) < ms) {
        peri_poll_button();
    }
}

int main(void)
{
    uint16_t code[5];
    int adc_ok;
    unsigned i;

    SystemInit();
    SystemCoreClockUpdate();

    bsp_init();
    console_init(HSECLK_VAL);
    systick_init();

    printf("\nK1921VG7T, SYSCLK = %lu MHz\n",
           (unsigned long)(SystemCoreClock / 1000000u));

    /* Пять каналов АЦП до мигания. Входы платы могут быть никуда не подключены. */
    adc_ok = adc_read5(code);
    printf("ADC");
    for (i = 0; i < 5u; i++) {
        printf(" %u", (unsigned)code[i]);
    }
    printf(" %s\n", adc_ok ? "ok" : "timeout");

    /* Аппаратных CRC, HASH и CRYPTO на К1921ВГ7Т нет. CRC-32 считается в peri.c. */
    crc_check(code, (uint32_t)sizeof code);

    /* Часы: секундный счётчик и календарь из него. Потом то же по кнопке B1. */
    rtc_start();
    rtc_print();

    dac_test();
    wdt_test();
    siu_test();
    tmr32_test();

    printf("B1 prints time. LED B0 blinks 1 Hz\n");

    InterruptEnable();
    systick_irq_enable();

    for (;;) {
        ll_gpio_set(LED_PORT, LL_GPIO_PIN_0);
        delay_btn(500);
        ll_gpio_clear(LED_PORT, LL_GPIO_PIN_0);
        delay_btn(500);
    }
}
