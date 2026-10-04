/* Поддержка платы NIIET-MINI-K1921VG7T (КФДЛ.441461.043, rev 2.0).
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 *
 * BSP из SDK НИИЭТ ставит светодиод на A12, а кнопку на A13. На этой плате это линии JTAG
 * TMS/TCK. Реальная разводка (схема rev 2.0):
 *   светодиод B0 LED (VD5): вывод B0, горит при единице
 *   кнопка USER BTN (SB2): вывод B1, читается как 0 при нажатии
 *   кнопка RESET (SB1): аппаратный сброс, к выводу B1 не подключена
 *   UART0     : A8 = RX, A9 = TX (USB-C -> CH340B), альтернативная функция 1
 *   BOOT.EN#  : A6 (от RTS# через перемычку XP3)
 */
#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include "K1921VG7T.h"

#define LED_PORT      GPIOB
#define LED_PIN_POS   0
#define LED_PIN_MSK   (1u << LED_PIN_POS)

#define BTN_PORT      GPIOB
#define BTN_PIN_POS   1
#define BTN_PIN_MSK   (1u << BTN_PIN_POS)

#define BOOTEN_PORT   GPIOA
#define BOOTEN_PIN_POS 6

void bsp_init(void);
void bsp_led_on(void);
void bsp_led_off(void);
void bsp_led_toggle(void);
int  bsp_button_pressed(void);

#endif
