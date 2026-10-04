/*==============================================================================
 * UART загрузчик для К1921ВГXT
 *
 * Общий файл конфигурации загрузчика: глобальные константы, общие макросы, типы
 *------------------------------------------------------------------------------
 * НИИЭТ, Долгополов Алексей <dolgopolov@niiet.ru>
 *==============================================================================
 * ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО
 * ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ
 * ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И ОТСУТСТВИЯ
 * НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ
 * ПРЕДНАЗНАЧЕНО ДЛЯ ОЗНАКОМИТЕЛЬНЫХ ЦЕЛЕЙ И НАПРАВЛЕНО ТОЛЬКО НА
 * ПРЕДОСТАВЛЕНИЕ ДОПОЛНИТЕЛЬНОЙ ИНФОРМАЦИИ О ПРОДУКТЕ, С ЦЕЛЬЮ СОХРАНИТЬ ВРЕМЯ
 * ПОТРЕБИТЕЛЮ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ
 * ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА ПРЯМОЙ ИЛИ КОСВЕННЫЙ УЩЕРБ, ИЛИ
 * ПО ИНЫМ ТРЕБОВАНИЯМ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ
 * ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.
 *
 *                              2026 АО "НИИЭТ"
 *==============================================================================
 */

#ifndef BOOT_CONF_H
#define BOOT_CONF_H

#include <stdio.h>
#if __TARGET_IDX__ == 1
#include <K1921VG1T.h>
#include <system_k1921vg1t.h>
#elif __TARGET_IDX__ == 3
#include <K1921VG3T.h>
#include <system_k1921vg3t.h>
#elif __TARGET_IDX__ == 5
#include <K1921VG5T.h>
#include <system_k1921vg5t.h>
#elif __TARGET_IDX__ == 7
#include <K1921VG7T.h>
#include <system_k1921vg7t.h>
#else
#error "please define correct __TARGET_IDX__ in makefile"
#endif

#include "plic.h"
#include "stringify.h"

#define CONCAT(x, y) _CONCAT(x, y)

// Global configuration
#define BOOT_VER_MAJOR 0x0001
#define BOOT_VER_MINOR 0x0001
#define BOOT_VER ((BOOT_VER_MAJOR << 16) | BOOT_VER_MINOR)
#if __TARGET_IDX__ == 1
#define BOOT_NAME "K1921VG1T_BOOTLOADER"
#elif __TARGET_IDX__ == 3
#define BOOT_NAME "K1921VG3T_BOOTLOADER"
#elif __TARGET_IDX__ == 5
#define BOOT_NAME "K1921VG5T_BOOTLOADER"
#elif __TARGET_IDX__ == 7
#define BOOT_NAME "K1921VG7T_BOOTLOADER"
#else
#error "please define correct __TARGET_IDX__ in makefile"
#endif
#define SYSCLK 100000000

/**
 * \note           BOOTEN pin used for activate bootloader
 */
#define BOOTEN

#if __TARGET_IDX__ == 1
#define BOOTEN_PORT_LETTER B
#define BOOTEN_PIN_NUMBER 2
#elif __TARGET_IDX__ == 3
#define BOOTEN_PORT_LETTER A
#define BOOTEN_PIN_NUMBER 8
#elif __TARGET_IDX__ == 5
#define BOOTEN_PORT_LETTER A
#define BOOTEN_PIN_NUMBER 8
#elif __TARGET_IDX__ == 7
/* Плата NIIET-MINI-K1921VG7T rev 2.0: BOOT.EN# на выводе A6 (RTS# через перемычку XP3).
 * В исходнике НИИЭТ был B0, а на этой плате это пользовательский светодиод. */
#define BOOTEN_PORT_LETTER A
#define BOOTEN_PIN_NUMBER 6
#else
#error "please define correct __TARGET_IDX__ in makefile"
#endif

#define BOOTEN_PORT CONCAT(GPIO, BOOTEN_PORT_LETTER) /*!< Port of  BOOTEN pin  \
                                                      */
#define BOOTEN_PORT_EN                                                         \
  CONCAT(RCU_CGCFGAHB_GPIO, CONCAT(BOOTEN_PORT_LETTER, EN_Msk))
#define BOOTEN_PIN_POS BOOTEN_PIN_NUMBER     /*!< Pin num of BOOTEN pin */
#define BOOTEN_PIN_MSK (1 << BOOTEN_PIN_POS) /*!< Pin num of BOOTEN pin */

/**
 * \brief           UART for communicate with HOST
 */
#define UART_NUMBER 0
#define UART UART0

#if __TARGET_IDX__ == 1
#define UART_PORT GPIOB
#define UART_PORT_EN RCU_CGCFGAHB_GPIOBEN_Msk
#define UART_CLK_EN RCU_CGCFGAPB2_UART0EN_Pos
#define UART_PIN_RX_POS 0
#define UART_PIN_TX_POS 1
#define UART_CLK_PORT RCU->CGCFGAPB2
#define UART_RST_PORT RCU->RSTDISAPB2
#define UART_ALTFUNCNUM 3
#elif __TARGET_IDX__ == 3
#define UART_PORT GPIOC
#define UART_PORT_EN RCU_CGCFGAHB_GPIOCEN_Msk
#define UART_CLK_EN RCU_CGCFGAPB1_UART0EN_Pos
#define UART_PIN_RX_POS 0
#define UART_PIN_TX_POS 1
#define UART_CLK_PORT RCU->CGCFGAPB1
#define UART_RST_PORT RCU->RSTDISAPB1
#define UART_ALTFUNCNUM 2
#elif __TARGET_IDX__ == 5
#define UART_PORT GPIOB
#define UART_PORT_EN RCU_CGCFGAHB_GPIOBEN_Msk
#define UART_CLK_EN RCU_CGCFGAPB_UART0EN_Pos
#define UART_PIN_RX_POS 0
#define UART_PIN_TX_POS 1
#define UART_CLK_PORT RCU->CGCFGAPB
#define UART_RST_PORT RCU->RSTDISAPB
#define UART_ALTFUNCNUM 2
#elif __TARGET_IDX__ == 7
/* Плата NIIET-MINI-K1921VG7T rev 2.0: CH340B подключён к UART0 на A8 (RX) / A9 (TX),
 * альтернативная функция 1. В исходнике НИИЭТ было A0/A1 и функция 2.
 * Доработка: Дмитрий (GitHub: mamkincoderr), Telegram: https://t.me/oDeXteRo */
#define UART_PORT GPIOA
#define UART_PORT_EN RCU_CGCFGAHB_GPIOAEN_Msk
#define UART_CLK_EN RCU_CGCFGAPB_UART0EN_Pos
#define UART_PIN_RX_POS 8
#define UART_PIN_TX_POS 9
#define UART_CLK_PORT RCU->CGCFGAPB
#define UART_RST_PORT RCU->RSTDISAPB
#define UART_ALTFUNCNUM 1
#else
#error "please define correct __TARGET_IDX__ in makefile"
#endif

#define UART_RX_IRQn IsrVect_IRQ_UART0

#ifndef UART_TIMEOUT_MS
#define UART_TIMEOUT_MS 100
#endif

#define SIU_UART_TMR_CNT_ENABLE                                                \
  CONCAT(CONCAT(SIU_CNTEN_TMR, UART_TMR_NUBMER), EN_Msk)
/**
 * \brief           Timer for calculate uart speed
 */

#if __TARGET_IDX__ == 1
#ifndef FLASH
#define FLASH FLASHM
#define FLASH_CMD_KEY_Pos FLASHM_CMD_KEY_Pos
#define FLASH_CMD_NVRON_Pos FLASHM_CMD_NVRON_Pos
#define FLASH_CMD_WR_Msk FLASHM_CMD_WR_Msk
#endif
#endif

#if __TARGET_IDX__ == 1
#define UART_TMR TMR0
#define UART_TMR_EN_Msk RCU_CGCFGAPB1_TMR0EN_Msk
#define SIU_TIMER SIU->TMREN
#define SIU_MASK SIU_TMREN_TMR0EN_Msk
#define TIMER_CLK RCU->CGCFGAPB1
#define TIMER_RST RCU->RSTDISAPB1
#elif __TARGET_IDX__ == 3
#define UART_TMR TMR0
#define UART_TMR_EN_Msk RCU_CGCFGAPB0_TMR0EN_Msk
#define SIU_TIMER SIU->CNTEN
#define SIU_MASK SIU_CNTEN_TMR0EN_Msk
#define TIMER_CLK RCU->CGCFGAPB0
#define TIMER_RST RCU->RSTDISAPB0
#elif __TARGET_IDX__ == 5
#define UART_TMR TMR0
#define UART_TMR_EN_Msk RCU_CGCFGAPB_TMR0EN_Msk
#define SIU_TIMER SIU->CNTEN
#define SIU_MASK SIU_CNTEN_TMR0EN_Msk
#define TIMER_CLK RCU->CGCFGAPB
#define TIMER_RST RCU->RSTDISAPB
#elif __TARGET_IDX__ == 7
#define UART_TMR TMR32_0
#define UART_TMR_EN_Msk RCU_CGCFGAPB_TMR0EN_Msk
#define SIU_TIMER SIU->TMREN
#define SIU_MASK SIU_TMREN_CNT0EN_Msk
#define TIMER_CLK RCU->CGCFGAPB
#define TIMER_RST RCU->RSTDISAPB
#else
#error "please define correct __TARGET_IDX__ in makefile"
#endif

/**
 * \brief           Timer for timeout
 */
#define TIMEOUT_TMR TMR32
#define TIMEOUT_TMR_EN_Msk RCU_CGCFGAPB_TMR32EN_Msk

/**
 * \brief           Packet parser values
 */
#define PACKET_FIFO_BYTES 4000
#define PACKET_HOST_SIGN 0x5C81
#define PACKET_DEVICE_SIGN 0x7EA3
#define PACKET_EMPTY_DATA 0x55
#define PACKET_TMP_DATA_BYTES (4096 + 8)

#endif // BOOT_CONF_H
