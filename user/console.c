/* Консоль на UART0 (A8/A9) и измерение частоты ядра.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 */
#include "console.h"
#include "K1921VG7T.h"

#define CON_UART       UART0
#define CON_PORT       GPIOA
#define CON_PIN_RX     8
#define CON_PIN_TX     9
#define CON_ALTFUNC    1u      /* A8/A9 -> UART0: подтверждено схемой и retarget.c из SDK */

void console_init(uint32_t uart_clk_hz)
{
    RCU->CGCFGAHB_bit.GPIOAEN = 1;
    RCU->RSTDISAHB_bit.GPIOAEN = 1;
    RCU->CGCFGAPB_bit.UART0EN = 1;
    RCU->RSTDISAPB_bit.UART0EN = 1;

    CON_PORT->ALTFUNCNUM &= ~((3u << (CON_PIN_RX * 2)) | (3u << (CON_PIN_TX * 2)));
    CON_PORT->ALTFUNCNUM |= (CON_ALTFUNC << (CON_PIN_RX * 2)) | (CON_ALTFUNC << (CON_PIN_TX * 2));
    CON_PORT->ALTFUNCSET = (1u << CON_PIN_RX) | (1u << CON_PIN_TX);

    /* Источник тактирования UART выбран так же, как в retarget.c из SDK */
    RCU->UARTCFG[0].UARTCFG = (1u << RCU_UARTCFG_CLKSEL_Pos) |
                              RCU_UARTCFG_CLKEN_Msk |
                              RCU_UARTCFG_RSTDIS_Msk;

    uint32_t ibrd = uart_clk_hz / (16u * CONSOLE_BAUD);
    uint32_t rem  = uart_clk_hz - ibrd * 16u * CONSOLE_BAUD;
    uint32_t fbrd = (rem * 64u + (8u * CONSOLE_BAUD)) / (16u * CONSOLE_BAUD);

    CON_UART->IBRD = ibrd;
    CON_UART->FBRD = fbrd;
    CON_UART->LCRH = UART_LCRH_FEN_Msk | (3u << UART_LCRH_WLEN_Pos);
    CON_UART->CR = UART_CR_TXE_Msk | UART_CR_RXE_Msk | UART_CR_UARTEN_Msk;
}

void console_putc(char c)
{
    while (CON_UART->FR & UART_FR_TXFF_Msk) {
    }
    CON_UART->DR = (uint32_t)(unsigned char)c;
}

int console_getc_nonblock(void)
{
    if (CON_UART->FR & UART_FR_RXFE_Msk) {
        return -1;
    }
    return (int)(CON_UART->DR & 0xFFu);
}

uint32_t console_measure_cpu_hz(void)
{
    const uint32_t chars = 100;
    uint32_t t0, t1;

    while (CON_UART->FR & UART_FR_BUSY_Msk) {
    }
    __asm__ volatile("csrr %0, mcycle" : "=r"(t0));
    for (uint32_t i = 0; i < chars; i++) {
        console_putc(' ');
    }
    while (CON_UART->FR & UART_FR_BUSY_Msk) {
    }
    __asm__ volatile("csrr %0, mcycle" : "=r"(t1));

    /* 10 бит на символ (8N1). Делитель UART округлён, поэтому реальная скорость на ~0,6 %
     * выше номинальных 115200 и результат занижен на столько же. */
    uint64_t cycles = (uint32_t)(t1 - t0);
    return (uint32_t)(cycles * CONSOLE_BAUD / (chars * 10u));
}
