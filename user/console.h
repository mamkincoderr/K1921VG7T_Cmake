/* Консоль на UART0: A8 (RX) / A9 (TX). printf() идёт через _write() из newlib.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 */
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

#ifndef CONSOLE_BAUD
#define CONSOLE_BAUD 115200u
#endif

void console_init(uint32_t uart_clk_hz);
void console_putc(char c);
int  console_getc_nonblock(void);   /* возвращает -1, если приёмный FIFO пуст */

/* Частота ядра в герцах, измеренная по тактированию UART (оно идёт от кварца): считает mcycle
 * за время передачи 100 символов. Не зависит от значения SystemCoreClock. */
uint32_t console_measure_cpu_hz(void);

#endif
