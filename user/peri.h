/* Короткие проверки блоков, которых не было в LL: АЦП, ЦАП, RTC, WDT, SIU, TMR32.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 *
 * CRC и CRYPTO сюда не входят: на К1921ВГ7Т этих блоков нет.
 * ll_crc.h и ll_crypto.h на этом кристалле не компилируются.
 */
#ifndef PERI_H
#define PERI_H

#include <stdint.h>

/* Каналы 0..4, по одному отсчёту. 1 — все пять в FIFO, 0 — таймаут. */
int adc_read5(uint16_t code[5]);

/* CRC-32 (полином ZIP) по байтам. Второй проход и эталон "123456789". */
void crc_check(const void *data, uint32_t len);

/* Секундный счётчик, FCM = 0. Календарь считается из TIME, регистра даты нет. */
void rtc_start(void);
void rtc_print(void);

/* По переднему фронту B1 печатает календарь. Звать из цикла мигания. */
void peri_poll_button(void);

void dac_test(void);    /* код 2048, буфер, программный запуск */
void wdt_test(void);    /* LOAD и замок. RESEN не включаем */
void siu_test(void);    /* CHIPID и признак сервисного режима */
void tmr32_test(void);  /* TMR32_0, счёт разрешает SIU.TMREN */

#endif
