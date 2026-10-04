/* Системный таймер SCR4: прерывание раз в 1 мс и задержки на его счётчике.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 *
 * Счётчик mtime стоит в области 0xE0000000. Пока MPU её не описал, чтение
 * возвращает нули. systick_init() открывает эту область и взводит сравнение.
 * Прерывание приходит в trap_handler как машинное, номер 7, не через PLIC.
 */
#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

/* Открыть MPU, посчитать тики на 1 мс от SystemCoreClock и взвести первое
 * сравнение. Глобальные прерывания сюда не включаются. */
void systick_init(void);

/* Разрешить прерывание машинного таймера. Вызывать после InterruptEnable(). */
void systick_irq_enable(void);

/* Миллисекунды с момента systick_init(). Счётчик крутится в прерывании. */
uint32_t systick_ms(void);

/* Ждать ms миллисекунд по счётчику прерываний. Пока прерывания выключены,
 * функция не возвращается. */
void delay_ms(uint32_t ms);

#endif
