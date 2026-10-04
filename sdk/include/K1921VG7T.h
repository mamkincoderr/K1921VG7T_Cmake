/*****************************************************************************
 * @file:    K1921VG7T.h
 * @author   NIIET
 * @version: V1.15.11
 * @date:    03.03.2026
 * @brief:   K1921VG7T header file
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, NIIET NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2026 NIIET </center></h2>
 *****************************************************************************
 * FILE K1921VG7T.h
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __K1921VG7T_H
#define __K1921VG7T_H

#define __I     volatile const                /*!< defines 'read only' permissions      */
#define __O     volatile                      /*!< defines 'write only' permissions     */
#define __IO    volatile                      /*!< defines 'read / write' permissions   */

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                   Plic  Interrupt Number Definition                        */
/******************************************************************************/

typedef enum Plic_IsrVect {
    IsrVect_IRQ_0 = 0x0,
/*-- Device specific Interrupt Numbers ---------------------------------------*/
    IsrVect_IRQ_WDT                       = 1, /* Watchdog timer interrupt */
    IsrVect_IRQ_RTC                       = 2, /* RTC interrupt [any cause] */
    IsrVect_IRQ_TMR32_0                   = 3, /* 32-bit timer 0 interrupt */
    IsrVect_IRQ_TMR32_1                   = 4, /* 32-bit timer 1 interrupt */
    IsrVect_IRQ_TMR16_0                   = 5, /* 16-bit timer 0 interrupt */
    IsrVect_IRQ_TMR16_1                   = 6, /* 16-bit timer 1 interrupt */
    IsrVect_IRQ_TMR16_2                   = 7, /* 16-bit timer 2 interrupt */
    IsrVect_IRQ_CAN0                      = 8, /* CAN0 interrupt */
    IsrVect_IRQ_CAN1                      = 9, /* CAN1 interrupt */
    IsrVect_IRQ_CAN2                      = 10, /* CAN2 interrupt */
    IsrVect_IRQ_CAN3                      = 11, /* CAN3 interrupt */
    IsrVect_IRQ_CAN4                      = 12, /* CAN4 interrupt */
    IsrVect_IRQ_CAN5                      = 13, /* CAN5 interrupt */
    IsrVect_IRQ_CAN6                      = 14, /* CAN6 interrupt */
    IsrVect_IRQ_CAN7                      = 15, /* CAN7 interrupt */
    IsrVect_IRQ_CAN8                      = 16, /* CAN8 interrupt */
    IsrVect_IRQ_CAN9                      = 17, /* CAN9 interrupt */
    IsrVect_IRQ_CAN10                     = 18, /* CAN10 interrupt */
    IsrVect_IRQ_CAN11                     = 19, /* CAN11 interrupt */
    IsrVect_IRQ_CAN12                     = 20, /* CAN12 interrupt */
    IsrVect_IRQ_CAN13                     = 21, /* CAN13 interrupt */
    IsrVect_IRQ_CAN14                     = 22, /* CAN14 interrupt */
    IsrVect_IRQ_CAN15                     = 23, /* CAN15 interrupt */
    IsrVect_IRQ_I2C0                      = 24, /* I2C0 interrupt */
    IsrVect_IRQ_I2C1                      = 25, /* I2C1 interrupt */
    IsrVect_IRQ_SPI0                      = 26, /* SPI0 interrupt [any cause] */
    IsrVect_IRQ_SPI0_RO                   = 27, /* SPI0 Receive Overrun interrupt */
    IsrVect_IRQ_SPI0_RT                   = 28, /* SPI0 Receive Timeout interrupt */
    IsrVect_IRQ_SPI0_RX                   = 29, /* SPI0 Receive interrupt */
    IsrVect_IRQ_SPI0_TX                   = 30, /* SPI0 Transmit interrupt */
    IsrVect_IRQ_SPI1                      = 31, /* SPI1 interrupt [any cause] */
    IsrVect_IRQ_SPI1_RO                   = 32, /* SPI1 Receive Overrun interrupt */
    IsrVect_IRQ_SPI1_RT                   = 33, /* SPI1 Receive Timeout interrupt */
    IsrVect_IRQ_SPI1_RX                   = 34, /* SPI1 Receive interrupt */
    IsrVect_IRQ_SPI1_TX                   = 35, /* SPI1 Transmit interrupt */
    IsrVect_IRQ_SPI2                      = 36, /* SPI2 interrupt [any cause] */
    IsrVect_IRQ_SPI2_RO                   = 37, /* SPI2 Receive Overrun interrupt */
    IsrVect_IRQ_SPI2_RT                   = 38, /* SPI2 Receive Timeout interrupt */
    IsrVect_IRQ_SPI2_RX                   = 39, /* SPI2 Receive interrupt */
    IsrVect_IRQ_SPI2_TX                   = 40, /* SPI2 Transmit interrupt */
    IsrVect_IRQ_UART0                     = 41, /* UART0 interrupt [any cause] */
    IsrVect_IRQ_UART0_E                   = 42, /* UART0 Error interrupt */
    IsrVect_IRQ_UART0_RT                  = 43, /* UART0 Receive Timeout interrupt */
    IsrVect_IRQ_UART0_RX                  = 44, /* UART0 Receive interrupt */
    IsrVect_IRQ_UART0_TD                  = 45, /* UART0 Transmit Done interrupt */
    IsrVect_IRQ_UART0_TX                  = 46, /* UART0 Transmit interrupt */
    IsrVect_IRQ_UART1                     = 47, /* UART1 interrupt [any cause] */
    IsrVect_IRQ_UART1_E                   = 48, /* UART1 Error interrupt */
    IsrVect_IRQ_UART1_RT                  = 49, /* UART1 Receive Timeout interrupt */
    IsrVect_IRQ_UART1_RX                  = 50, /* UART1 Receive interrupt */
    IsrVect_IRQ_UART1_TD                  = 51, /* UART1 Transmit Done interrupt */
    IsrVect_IRQ_UART1_TX                  = 52, /* UART1 Transmit interrupt */
    IsrVect_IRQ_ADC_DC                    = 53, /* ADC Digital Comparators interrupt [any source] */
    IsrVect_IRQ_ADC_DC0                   = 54, /* ADC Digital Comparator 0 interrupt */
    IsrVect_IRQ_ADC_DC1                   = 55, /* ADC Digital Comparator 1 interrupt */
    IsrVect_IRQ_ADC_DC2                   = 56, /* ADC Digital Comparator 2 interrupt */
    IsrVect_IRQ_ADC_DC3                   = 57, /* ADC Digital Comparator 3 interrupt */
    IsrVect_IRQ_ADC_DC4                   = 58, /* ADC Digital Comparator 4 interrupt */
    IsrVect_IRQ_ADC_DC5                   = 59, /* ADC Digital Comparator 5 interrupt */
    IsrVect_IRQ_ADC_DC6                   = 60, /* ADC Digital Comparator 6 interrupt */
    IsrVect_IRQ_ADC_DC7                   = 61, /* ADC Digital Comparator 7 interrupt */
    IsrVect_IRQ_GPIOA                     = 62, /* GPIO A interrupt [any source] */
    IsrVect_IRQ_GPIOB                     = 63, /* GPIO B interrupt [any source] */
    IsrVect_IRQ_GPIO0                     = 64, /* GPIO A pin 0 interrupt */
    IsrVect_IRQ_GPIO1                     = 65, /* GPIO A pin 1 interrupt */
    IsrVect_IRQ_GPIO2                     = 66, /* GPIO A pin 2 interrupt */
    IsrVect_IRQ_GPIO3                     = 67, /* GPIO A pin 3 interrupt */
    IsrVect_IRQ_GPIO4                     = 68, /* GPIO A pin 4 interrupt */
    IsrVect_IRQ_GPIO5                     = 69, /* GPIO A pin 5 interrupt */
    IsrVect_IRQ_GPIO6                     = 70, /* GPIO A pin 6 interrupt */
    IsrVect_IRQ_GPIO7                     = 71, /* GPIO A pin 7 interrupt */
    IsrVect_IRQ_GPIO8                     = 72, /* GPIO A pin 8 interrupt */
    IsrVect_IRQ_GPIO9                     = 73, /* GPIO A pin 9 interrupt */
    IsrVect_IRQ_GPIO10                    = 74, /* GPIO A pin 10 interrupt */
    IsrVect_IRQ_GPIO11                    = 75, /* GPIO A pin 11 interrupt */
    IsrVect_IRQ_GPIO12                    = 76, /* GPIO A pin 12 interrupt */
    IsrVect_IRQ_GPIO13                    = 77, /* GPIO A pin 13 interrupt */
    IsrVect_IRQ_GPIO14                    = 78, /* GPIO A pin 14 interrupt */
    IsrVect_IRQ_GPIO15                    = 79, /* GPIO A pin 15 interrupt */
    IsrVect_IRQ_GPIO16                    = 80, /* GPIO B pin 0 interrupt */
    IsrVect_IRQ_GPIO17                    = 81, /* GPIO B pin 1 interrupt */
    IsrVect_IRQ_GPIO18                    = 82, /* GPIO B pin 2 interrupt */
    IsrVect_IRQ_GPIO19                    = 83, /* GPIO B pin 3 interrupt */
    IsrVect_IRQ_GPIO20                    = 84, /* GPIO B pin 4 interrupt */
    IsrVect_IRQ_GPIO21                    = 85, /* GPIO B pin 5 interrupt */
    IsrVect_IRQ_GPIO22                    = 86, /* GPIO B pin 6 interrupt */
    IsrVect_IRQ_GPIO23                    = 87, /* GPIO B pin 7 interrupt */
    IsrVect_IRQ_GPIO24                    = 88, /* GPIO B pin 8 interrupt */
    IsrVect_IRQ_GPIO25                    = 89, /* GPIO B pin 9 interrupt */
    IsrVect_IRQ_GPIO26                    = 90, /* GPIO B pin 10 interrupt */
    IsrVect_IRQ_GPIO27                    = 91, /* GPIO B pin 11 interrupt */
    IsrVect_IRQ_GPIO28                    = 92, /* GPIO B pin 12 interrupt */
    IsrVect_IRQ_GPIO29                    = 93, /* GPIO B pin 13 interrupt */
    IsrVect_IRQ_GPIO30                    = 94, /* GPIO B pin 14 interrupt */
    IsrVect_IRQ_ADC_SEQ                   = 95, /* ADC Sequencers interrupt [any source] */
    IsrVect_IRQ_DMA_CH0                   = 96, /* DMA channel 0 interrupt */
    IsrVect_IRQ_DMA_CH1                   = 97, /* DMA channel 1 interrupt */
    IsrVect_IRQ_DMA_CH2                   = 98, /* DMA channel 2 interrupt */
    IsrVect_IRQ_DMA_CH3                   = 99, /* DMA channel 3 interrupt */
    IsrVect_IRQ_DMA_CH4                   = 100, /* DMA channel 4 interrupt */
    IsrVect_IRQ_DMA_CH5                   = 101, /* DMA channel 5 interrupt */
    IsrVect_IRQ_DMA_CH6                   = 102, /* DMA channel 6 interrupt */
    IsrVect_IRQ_DMA_CH7                   = 103, /* DMA channel 7 interrupt */
    IsrVect_IRQ_ADC_SEQ0                  = 104, /* ADC Sequencer 0 interrupt */
    IsrVect_IRQ_ADC_SEQ1                  = 105, /* ADC Sequencer 1 interrupt */
    IsrVect_IRQ_ADC_SEQ2                  = 106, /* ADC Sequencer 2 interrupt */
    IsrVect_IRQ_ADC_SEQ3                  = 107, /* ADC Sequencer 3 interrupt */
    IsrVect_IRQ_FLASH                     = 108, /* Flash interrupt */
    IsrVect_IRQ_RCU                       = 109, /* RCU interrupt */
    IsrVect_IRQ_RTC_ALARM1                = 110, /* RTC alarm 1 interrupt */
    IsrVect_IRQ_RTC_ALARM2                = 111, /* RTC alarm 2 interrupt */
    IsrVect_IRQ_RTC_BATTERY               = 112, /* RTC switch to battery power supply interrupt */
    IsrVect_IRQ_RTC_N_POWER               = 113, /* RTC switch to normal power supply interrupt */
    IsrVect_IRQ_RTC_OVERFLOW              = 114, /* RTC timer overflow interrupt */
    IsrVect_IRQ_TMR32_0_P                 = 115, /* 32-bit timer 0 period interrupt */
    IsrVect_IRQ_TMR32_1_P                 = 116, /* 32-bit timer 1 period interrupt */
    IsrVect_IRQ_TMR16_0_P                 = 117, /* 16-bit timer 0 period interrupt */
    IsrVect_IRQ_TMR16_1_P                 = 118, /* 16-bit timer 1 period interrupt */
    IsrVect_IRQ_TMR16_2_P                 = 119, /* 16-bit timer 2 period interrupt */
    IsrVect_IRQ_TMR32_0_CC                = 120, /* 32-bit timer 0 capture/compare interrupt */
    IsrVect_IRQ_TMR32_1_CC                = 121, /* 32-bit timer 1 capture/compare interrupt */
    IsrVect_IRQ_TMR16_0_CC                = 122, /* 16-bit timer 0 capture/compare interrupt */
    IsrVect_IRQ_TMR16_1_CC                = 123, /* 16-bit timer 1 capture/compare interrupt */
    IsrVect_IRQ_TMR16_2_CC                = 124, /* 16-bit timer 2 capture/compare interrupt */
} Plic_IsrVect_TypeDef;


//#include <system_K1921VG7T.h>        /* System initialization                   */

/******************************************************************************/
/*                         System Specific Defenitions                        */
/******************************************************************************/
/*--  System memory ----------------------------------------------------------*/
/*--  Flash size: 512kb, RAM size: 32Kb, TCM size: 32Kb ----------------------*/
/*--  Flash chip is 128x64 bits per sector. ----------------------------------*/
/*--  Flash page size = sector size * 1 (1 chip in line) ---------------------*/

#define MEM_FLASH_BASE                       0x00000000UL
#define MEM_FLASH_BUS_WIDTH_WORDS            2UL
#define MEM_FLASH_PAGE_SIZE                  1024UL
#define MEM_FLASH_PAGE_SIZE_LOG2             10UL
#define MEM_FLASH_PAGE_TOTAL                 512UL
#define MEM_FLASH_SIZE                       (MEM_FLASH_PAGE_TOTAL * MEM_FLASH_PAGE_SIZE)

#define LATENCY_DEFAULT                      (1)
#define LATENCY_100MHz                       (2)
#define LATENCY_150MHz                       (3)
#define LATENCY_200MHz                       (4)

#define MEM_RAM_BASE                         0x20000000UL
#define MEM_RAM_SIZE                         0x00008000UL

#define MEM_TCM_BASE                         0xF0000000UL
#define MEM_TCM_SIZE                         0x00008000UL

/******************************************************************************/
/*                         DMA channel parameters                             */
/******************************************************************************/

/*--  BUFFER_SIZE: DMA channel Size of buffer (Not Block) to transfer --------------------------------*/
typedef struct {
    uint32_t BUFFSIZE             : 16;                              /*!< The operating mode of the DMA cycle */
} _CHANNEL_BUFFER_SIZE_bits;

/* Bit field positions: */
#define DMA_CHANNEL_BUFFER_SIZE_BUFFSIZE_Pos        0                /*!< The operating mode of the DMA cycle */

/* Bit field masks: */
#define DMA_CHANNEL_BUFFER_SIZE_BUFFSIZE_Msk        0x0000FFFFUL     /*!< The operating mode of the DMA cycle */

/*--  BLOCK_SIZE: DMA channel Size of buffer (Block) to transfer --------------------------------*/
typedef struct {
    uint32_t XSIZE             : 8;                               /*!< Block width */
    uint32_t YSIZE             : 8;                               /*!< Number of block lines */
} _CHANNEL_BLOCK_SIZE_bits;

/* Bit field positions: */
#define DMA_CHANNEL_BLOCK_SIZE_XSIZE_Pos        0                 /*!< The operating mode of the DMA cycle */
#define DMA_CHANNEL_BLOCK_SIZE_YSIZE_Pos        8                 /*!< The operating mode of the DMA cycle */

/* Bit field masks: */
#define DMA_CHANNEL_BLOCK_SIZE_XSIZE_Msk        0x000000FFUL      /*!< The operating mode of the DMA cycle */
#define DMA_CHANNEL_BLOCK_SIZE_YSIZE_Msk        0x0000FF00UL      /*!< The operating mode of the DMA cycle */

/*--  CHANNEL_CFG: DMA channel configure --------------------------------*/
typedef struct {
    uint32_t INTEN             : 1;                               /*!< Enable interrupt */
    uint32_t LAST              : 1;                               /*!< Last command in list */
    uint32_t NEXTPTR           : 30;                              /*!< Next command pointer */
} _CHANNEL_CFG_bits;

/* Bit field positions: */
#define DMA_CHANNEL_CFG_INTEN_Pos        0                 /*!< Enable interrupt DMA cycle */
#define DMA_CHANNEL_CFG_LAST_Pos         1                 /*!< Last command in list */
#define DMA_CHANNEL_CFG_NEXTPTR_Pos      2                 /*!< Next pointer DMA cycle */

/* Bit field masks: */
#define DMA_CHANNEL_CFG_INTEN_Msk        0x00000001UL      /*!< The operating mode of the DMA cycle */
#define DMA_CHANNEL_CFG_LAST_Msk         0x00000002UL      /*!< The operating mode of the DMA cycle */
#define DMA_CHANNEL_CFG_NEXTPTR_Msk      0xFFFFFFFCUL      /*!< The operating mode of the DMA cycle */

/*--  DMA channel structure --------------------------------------------------*/
typedef struct
{
    __IO uint32_t SRC_DATA_END_PTR;                                       /*!< Source data end pointer */
    __IO uint32_t DST_DATA_END_PTR;                                       /*!< Destination data end pointer */
    union {
        __IO uint32_t BUFFER_SIZE;                                        /*!< Channel Size of buffer to transfer */
        __IO _CHANNEL_BUFFER_SIZE_bits BUFFER_SIZE_bit;                   /*!< channel Size of buffer to transfer: bit access */
        __IO uint32_t BLOCK_SIZE;                                         /*!< Channel Size of buffer to transfer */
        __IO _CHANNEL_BLOCK_SIZE_bits BLOCK_SIZE_bit;                     /*!< channel Size of buffer to transfer: bit access */
    };
    union {
        __IO uint32_t CHANNEL_CFG;                                        /*!< Channel configure word */
        __IO _CHANNEL_CFG_bits CHANNEL_CFG_bit;                           /*!< channel configure word: bit access */
    };
} DMA_Channel_TypeDef;

#define MEMORY_DMA_REQUESTOR_IDX    0                                     /*!<Default requestor*/
#define SPI0_DMA_REQUESTOR_IDX      1
#define SPI1_DMA_REQUESTOR_IDX      2
#define SPI2_DMA_REQUESTOR_IDX      3
#define UART0_DMA_REQUESTOR_IDX     4
#define UART1_DMA_REQUESTOR_IDX     5
#define TMR0_DMA_REQUESTOR_IDX      6
#define TMR1_DMA_REQUESTOR_IDX      7
#define TMR2_DMA_REQUESTOR_IDX      8
#define TMR3_DMA_REQUESTOR_IDX      9
#define TMR4_DMA_REQUESTOR_IDX      10
#define ADCSEQ0_DMA_REQUESTOR_IDX   11
#define ADCSEQ1_DMA_REQUESTOR_IDX   12
#define ADCSEQ2_DMA_REQUESTOR_IDX   13
#define ADCSEQ3_DMA_REQUESTOR_IDX   14
#define GPIOA_DMA_REQUESTOR_IDX     15
#define GPIOB_DMA_REQUESTOR_IDX     16
#define DAC_DMA_REQUESTOR_IDX       17



/******************************************************************************/
/*                         ADC registers                                      */
/******************************************************************************/

/*--  SEQEN: Enable sequencer register ------------------------------------------------------------------------*/
typedef struct {
  uint32_t SEQEN0                 :1;                                /*!< Enable sequencer 0 */
  uint32_t SEQEN1                 :1;                                /*!< Enable sequencer 1 */
  uint32_t SEQEN2                 :1;                                /*!< Enable sequencer 2 */
  uint32_t SEQEN3                 :1;                                /*!< Enable sequencer 3 */
} _ADC_SEQEN_bits;

/* Bit field positions: */
#define ADC_SEQEN_SEQEN0_Pos                  0                      /*!< Enable sequencer 0 */
#define ADC_SEQEN_SEQEN1_Pos                  1                      /*!< Enable sequencer 1 */
#define ADC_SEQEN_SEQEN2_Pos                  2                      /*!< Enable sequencer 2 */
#define ADC_SEQEN_SEQEN3_Pos                  3                      /*!< Enable sequencer 3 */

/* Bit field masks: */
#define ADC_SEQEN_SEQEN0_Msk                  0x00000001UL           /*!< Enable sequencer 0 */
#define ADC_SEQEN_SEQEN1_Msk                  0x00000002UL           /*!< Enable sequencer 1 */
#define ADC_SEQEN_SEQEN2_Msk                  0x00000004UL           /*!< Enable sequencer 2 */
#define ADC_SEQEN_SEQEN3_Msk                  0x00000008UL           /*!< Enable sequencer 3 */

/*--  SEQSYNC: Sequencer sync register ------------------------------------------------------------------------*/
typedef struct {
  uint32_t SYNC0                  :1;                                /*!< Enable sequencer 0 software sync */
  uint32_t SYNC1                  :1;                                /*!< Enable sequencer 1 software sync */
  uint32_t SYNC2                  :1;                                /*!< Enable sequencer 2 software sync */
  uint32_t SYNC3                  :1;                                /*!< Enable sequencer 3 software sync */
  uint32_t                        :27;                               /*!< RESERVED */
  uint32_t GSYNC                  :1;                                /*!< Sync all sequencers */
} _ADC_SEQSYNC_bits;

/* Bit field positions: */
#define ADC_SEQSYNC_SYNC0_Pos                 0                      /*!< Enable sequencer 0 software sync */
#define ADC_SEQSYNC_SYNC1_Pos                 1                      /*!< Enable sequencer 1 software sync */
#define ADC_SEQSYNC_SYNC2_Pos                 2                      /*!< Enable sequencer 2 software sync */
#define ADC_SEQSYNC_SYNC3_Pos                 3                      /*!< Enable sequencer 3 software sync */
#define ADC_SEQSYNC_GSYNC_Pos                 31                     /*!< Sync all sequencers */

/* Bit field masks: */
#define ADC_SEQSYNC_SYNC0_Msk                 0x00000001UL           /*!< Enable sequencer 0 software sync */
#define ADC_SEQSYNC_SYNC1_Msk                 0x00000002UL           /*!< Enable sequencer 1 software sync */
#define ADC_SEQSYNC_SYNC2_Msk                 0x00000004UL           /*!< Enable sequencer 2 software sync */
#define ADC_SEQSYNC_SYNC3_Msk                 0x00000008UL           /*!< Enable sequencer 3 software sync */
#define ADC_SEQSYNC_GSYNC_Msk                 0x80000000UL           /*!< Sync all sequencers */

/*--  FSTAT: FIFO overflow status register --------------------------------------------------------------------*/
typedef struct {
  uint32_t OV0                    :1;                                /*!< Sequencer 0 FIFO overflow */
  uint32_t OV1                    :1;                                /*!< Sequencer 1 FIFO overflow */
  uint32_t OV2                    :1;                                /*!< Sequencer 2 FIFO overflow */
  uint32_t OV3                    :1;                                /*!< Sequencer 3 FIFO overflow */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t UN0                    :1;                                /*!< Sequencer 0 FIFO underflow */
  uint32_t UN1                    :1;                                /*!< Sequencer 1 FIFO underflow */
  uint32_t UN2                    :1;                                /*!< Sequencer 2 FIFO underflow */
  uint32_t UN3                    :1;                                /*!< Sequencer 3 FIFO underflow */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t DOV0                   :1;                                /*!< Sequencer 0 FIFO DMA request overflow */
  uint32_t DOV1                   :1;                                /*!< Sequencer 1 FIFO DMA request overflow */
  uint32_t DOV2                   :1;                                /*!< Sequencer 2 FIFO DMA request overflow */
  uint32_t DOV3                   :1;                                /*!< Sequencer 3 FIFO DMA request overflow */
} _ADC_FSTAT_bits;

/* Bit field positions: */
#define ADC_FSTAT_OV0_Pos                     0                      /*!< Sequencer 0 FIFO overflow */
#define ADC_FSTAT_OV1_Pos                     1                      /*!< Sequencer 1 FIFO overflow */
#define ADC_FSTAT_OV2_Pos                     2                      /*!< Sequencer 2 FIFO overflow */
#define ADC_FSTAT_OV3_Pos                     3                      /*!< Sequencer 3 FIFO overflow */
#define ADC_FSTAT_UN0_Pos                     8                      /*!< Sequencer 0 FIFO underflow */
#define ADC_FSTAT_UN1_Pos                     9                      /*!< Sequencer 1 FIFO underflow */
#define ADC_FSTAT_UN2_Pos                     10                     /*!< Sequencer 2 FIFO underflow */
#define ADC_FSTAT_UN3_Pos                     11                     /*!< Sequencer 3 FIFO underflow */
#define ADC_FSTAT_DOV0_Pos                    16                     /*!< Sequencer 0 FIFO DMA request overflow */
#define ADC_FSTAT_DOV1_Pos                    17                     /*!< Sequencer 1 FIFO DMA request overflow */
#define ADC_FSTAT_DOV2_Pos                    18                     /*!< Sequencer 2 FIFO DMA request overflow */
#define ADC_FSTAT_DOV3_Pos                    19                     /*!< Sequencer 3 FIFO DMA request overflow */

/* Bit field masks: */
#define ADC_FSTAT_OV0_Msk                     0x00000001UL           /*!< Sequencer 0 FIFO overflow */
#define ADC_FSTAT_OV1_Msk                     0x00000002UL           /*!< Sequencer 1 FIFO overflow */
#define ADC_FSTAT_OV2_Msk                     0x00000004UL           /*!< Sequencer 2 FIFO overflow */
#define ADC_FSTAT_OV3_Msk                     0x00000008UL           /*!< Sequencer 3 FIFO overflow */
#define ADC_FSTAT_UN0_Msk                     0x00000100UL           /*!< Sequencer 0 FIFO underflow */
#define ADC_FSTAT_UN1_Msk                     0x00000200UL           /*!< Sequencer 1 FIFO underflow */
#define ADC_FSTAT_UN2_Msk                     0x00000400UL           /*!< Sequencer 2 FIFO underflow */
#define ADC_FSTAT_UN3_Msk                     0x00000800UL           /*!< Sequencer 3 FIFO underflow */
#define ADC_FSTAT_DOV0_Msk                    0x00010000UL           /*!< Sequencer 0 FIFO DMA request overflow */
#define ADC_FSTAT_DOV1_Msk                    0x00020000UL           /*!< Sequencer 1 FIFO DMA request overflow */
#define ADC_FSTAT_DOV2_Msk                    0x00040000UL           /*!< Sequencer 2 FIFO DMA request overflow */
#define ADC_FSTAT_DOV3_Msk                    0x00080000UL           /*!< Sequencer 3 FIFO DMA request overflow */

/*--  BSTAT: Busy status register -----------------------------------------------------------------------------*/
typedef struct {
  uint32_t SEQBUSY0               :1;                                /*!< Sequencer 0 busy */
  uint32_t SEQBUSY1               :1;                                /*!< Sequencer 1 busy */
  uint32_t SEQBUSY2               :1;                                /*!< Sequencer 2 busy */
  uint32_t SEQBUSY3               :1;                                /*!< Sequencer 3 busy */
  uint32_t                        :12;                               /*!< RESERVED */
  uint32_t ADCBUSY0               :1;                                /*!< ADC module 0 conversion busy */
} _ADC_BSTAT_bits;

/* Bit field positions: */
#define ADC_BSTAT_SEQBUSY0_Pos                0                      /*!< Sequencer 0 busy */
#define ADC_BSTAT_SEQBUSY1_Pos                1                      /*!< Sequencer 1 busy */
#define ADC_BSTAT_SEQBUSY2_Pos                2                      /*!< Sequencer 2 busy */
#define ADC_BSTAT_SEQBUSY3_Pos                3                      /*!< Sequencer 3 busy */
#define ADC_BSTAT_ADCBUSY0_Pos                16                     /*!< ADC module 0 conversion busy */

/* Bit field masks: */
#define ADC_BSTAT_SEQBUSY0_Msk                0x00000001UL           /*!< Sequencer 0 busy */
#define ADC_BSTAT_SEQBUSY1_Msk                0x00000002UL           /*!< Sequencer 1 busy */
#define ADC_BSTAT_SEQBUSY2_Msk                0x00000004UL           /*!< Sequencer 2 busy */
#define ADC_BSTAT_SEQBUSY3_Msk                0x00000008UL           /*!< Sequencer 3 busy */
#define ADC_BSTAT_ADCBUSY0_Msk                0x00010000UL           /*!< ADC module 0 conversion busy */

/*--  DCTRIG: Digital comparator output trigger status register -----------------------------------------------*/
typedef struct {
  uint32_t TOS0                   :1;                                /*!< DC 0 output trigger status */
  uint32_t TOS1                   :1;                                /*!< DC 1 output trigger status */
  uint32_t TOS2                   :1;                                /*!< DC 2 output trigger status */
  uint32_t TOS3                   :1;                                /*!< DC 3 output trigger status */
  uint32_t TOS4                   :1;                                /*!< DC 4 output trigger status */
  uint32_t TOS5                   :1;                                /*!< DC 5 output trigger status */
  uint32_t TOS6                   :1;                                /*!< DC 6 output trigger status */
  uint32_t TOS7                   :1;                                /*!< DC 7 output trigger status */
} _ADC_DCTRIG_bits;

/* Bit field positions: */
#define ADC_DCTRIG_TOS0_Pos                   0                      /*!< DC 0 output trigger status */
#define ADC_DCTRIG_TOS1_Pos                   1                      /*!< DC 1 output trigger status */
#define ADC_DCTRIG_TOS2_Pos                   2                      /*!< DC 2 output trigger status */
#define ADC_DCTRIG_TOS3_Pos                   3                      /*!< DC 3 output trigger status */
#define ADC_DCTRIG_TOS4_Pos                   4                      /*!< DC 4 output trigger status */
#define ADC_DCTRIG_TOS5_Pos                   5                      /*!< DC 5 output trigger status */
#define ADC_DCTRIG_TOS6_Pos                   6                      /*!< DC 6 output trigger status */
#define ADC_DCTRIG_TOS7_Pos                   7                      /*!< DC 7 output trigger status */

/* Bit field masks: */
#define ADC_DCTRIG_TOS0_Msk                   0x00000001UL           /*!< DC 0 output trigger status */
#define ADC_DCTRIG_TOS1_Msk                   0x00000002UL           /*!< DC 1 output trigger status */
#define ADC_DCTRIG_TOS2_Msk                   0x00000004UL           /*!< DC 2 output trigger status */
#define ADC_DCTRIG_TOS3_Msk                   0x00000008UL           /*!< DC 3 output trigger status */
#define ADC_DCTRIG_TOS4_Msk                   0x00000010UL           /*!< DC 4 output trigger status */
#define ADC_DCTRIG_TOS5_Msk                   0x00000020UL           /*!< DC 5 output trigger status */
#define ADC_DCTRIG_TOS6_Msk                   0x00000040UL           /*!< DC 6 output trigger status */
#define ADC_DCTRIG_TOS7_Msk                   0x00000080UL           /*!< DC 7 output trigger status */

/*--  DCEV: Digital comparator compare event status register --------------------------------------------------*/
typedef struct {
  uint32_t DCEV0                  :1;                                /*!< Digital compare event 0 */
  uint32_t DCEV1                  :1;                                /*!< Digital compare event 1 */
  uint32_t DCEV2                  :1;                                /*!< Digital compare event 2 */
  uint32_t DCEV3                  :1;                                /*!< Digital compare event 3 */
  uint32_t DCEV4                  :1;                                /*!< Digital compare event 4 */
  uint32_t DCEV5                  :1;                                /*!< Digital compare event 5 */
  uint32_t DCEV6                  :1;                                /*!< Digital compare event 6 */
  uint32_t DCEV7                  :1;                                /*!< Digital compare event 7 */
} _ADC_DCEV_bits;

/* Bit field positions: */
#define ADC_DCEV_DCEV0_Pos                    0                      /*!< Digital compare event 0 */
#define ADC_DCEV_DCEV1_Pos                    1                      /*!< Digital compare event 1 */
#define ADC_DCEV_DCEV2_Pos                    2                      /*!< Digital compare event 2 */
#define ADC_DCEV_DCEV3_Pos                    3                      /*!< Digital compare event 3 */
#define ADC_DCEV_DCEV4_Pos                    4                      /*!< Digital compare event 4 */
#define ADC_DCEV_DCEV5_Pos                    5                      /*!< Digital compare event 5 */
#define ADC_DCEV_DCEV6_Pos                    6                      /*!< Digital compare event 6 */
#define ADC_DCEV_DCEV7_Pos                    7                      /*!< Digital compare event 7 */

/* Bit field masks: */
#define ADC_DCEV_DCEV0_Msk                    0x00000001UL           /*!< Digital compare event 0 */
#define ADC_DCEV_DCEV1_Msk                    0x00000002UL           /*!< Digital compare event 1 */
#define ADC_DCEV_DCEV2_Msk                    0x00000004UL           /*!< Digital compare event 2 */
#define ADC_DCEV_DCEV3_Msk                    0x00000008UL           /*!< Digital compare event 3 */
#define ADC_DCEV_DCEV4_Msk                    0x00000010UL           /*!< Digital compare event 4 */
#define ADC_DCEV_DCEV5_Msk                    0x00000020UL           /*!< Digital compare event 5 */
#define ADC_DCEV_DCEV6_Msk                    0x00000040UL           /*!< Digital compare event 6 */
#define ADC_DCEV_DCEV7_Msk                    0x00000080UL           /*!< Digital compare event 7 */

/*--  CICNT: Interrupt counter clear control ------------------------------------------------------------------*/
typedef struct {
  uint32_t ICNT0                  :1;                                /*!< Clear interrupt counter on sequencer 0 start */
  uint32_t ICNT1                  :1;                                /*!< Clear interrupt counter on sequencer 1 start */
  uint32_t ICNT2                  :1;                                /*!< Clear interrupt counter on sequencer 2 start */
  uint32_t ICNT3                  :1;                                /*!< Clear interrupt counter on sequencer 3 start */
  uint32_t ICNT4                  :1;                                /*!< Clear interrupt counter on sequencer 4 start */
  uint32_t ICNT5                  :1;                                /*!< Clear interrupt counter on sequencer 5 start */
  uint32_t ICNT6                  :1;                                /*!< Clear interrupt counter on sequencer 6 start */
  uint32_t ICNT7                  :1;                                /*!< Clear interrupt counter on sequencer 7 start */
} _ADC_CICNT_bits;

/* Bit field positions: */
#define ADC_CICNT_ICNT0_Pos                   0                      /*!< Clear interrupt counter on sequencer 0 start */
#define ADC_CICNT_ICNT1_Pos                   1                      /*!< Clear interrupt counter on sequencer 1 start */
#define ADC_CICNT_ICNT2_Pos                   2                      /*!< Clear interrupt counter on sequencer 2 start */
#define ADC_CICNT_ICNT3_Pos                   3                      /*!< Clear interrupt counter on sequencer 3 start */
#define ADC_CICNT_ICNT4_Pos                   4                      /*!< Clear interrupt counter on sequencer 4 start */
#define ADC_CICNT_ICNT5_Pos                   5                      /*!< Clear interrupt counter on sequencer 5 start */
#define ADC_CICNT_ICNT6_Pos                   6                      /*!< Clear interrupt counter on sequencer 6 start */
#define ADC_CICNT_ICNT7_Pos                   7                      /*!< Clear interrupt counter on sequencer 7 start */

/* Bit field masks: */
#define ADC_CICNT_ICNT0_Msk                   0x00000001UL           /*!< Clear interrupt counter on sequencer 0 start */
#define ADC_CICNT_ICNT1_Msk                   0x00000002UL           /*!< Clear interrupt counter on sequencer 1 start */
#define ADC_CICNT_ICNT2_Msk                   0x00000004UL           /*!< Clear interrupt counter on sequencer 2 start */
#define ADC_CICNT_ICNT3_Msk                   0x00000008UL           /*!< Clear interrupt counter on sequencer 3 start */
#define ADC_CICNT_ICNT4_Msk                   0x00000010UL           /*!< Clear interrupt counter on sequencer 4 start */
#define ADC_CICNT_ICNT5_Msk                   0x00000020UL           /*!< Clear interrupt counter on sequencer 5 start */
#define ADC_CICNT_ICNT6_Msk                   0x00000040UL           /*!< Clear interrupt counter on sequencer 6 start */
#define ADC_CICNT_ICNT7_Msk                   0x00000080UL           /*!< Clear interrupt counter on sequencer 7 start */

/*--  EMUX: Sequencer start event selection register ----------------------------------------------------------*/
typedef struct {
  uint32_t EM0                    :4;                                /*!< Select start event for sequencer 0 */
  uint32_t EM1                    :4;                                /*!< Select start event for sequencer 1 */
  uint32_t EM2                    :4;                                /*!< Select start event for sequencer 2 */
  uint32_t EM3                    :4;                                /*!< Select start event for sequencer 3 */
} _ADC_EMUX_bits;

/* Bit field positions: */
#define ADC_EMUX_EM0_Pos                      0                      /*!< Select start event for sequencer 0 */
#define ADC_EMUX_EM1_Pos                      4                      /*!< Select start event for sequencer 1 */
#define ADC_EMUX_EM2_Pos                      8                      /*!< Select start event for sequencer 2 */
#define ADC_EMUX_EM3_Pos                      12                     /*!< Select start event for sequencer 3 */

/* Bit field masks: */
#define ADC_EMUX_EM0_Msk                      0x0000000FUL           /*!< Select start event for sequencer 0 */
#define ADC_EMUX_EM1_Msk                      0x000000F0UL           /*!< Select start event for sequencer 1 */
#define ADC_EMUX_EM2_Msk                      0x00000F00UL           /*!< Select start event for sequencer 2 */
#define ADC_EMUX_EM3_Msk                      0x0000F000UL           /*!< Select start event for sequencer 3 */

/* Bit field enums: */
typedef enum {
  ADC_EMUX_EM0_SwReq                         = 0x0UL,                /*!< software request by GSYNC bit */
  ADC_EMUX_EM0_GPIOA                         = 0x1UL,                /*!< GPIOA interrupt */
  ADC_EMUX_EM0_GPIOB                         = 0x2UL,                /*!< GPIOB interrupt */
  ADC_EMUX_EM0_TMR0                          = 0x3UL,                /*!< Timer 0 request */
  ADC_EMUX_EM0_TMR1                          = 0x4UL,                /*!< Timer 1 request */
  ADC_EMUX_EM0_TMR2                          = 0x5UL,                /*!< Timer 2 request */
  ADC_EMUX_EM0_TMR3                          = 0x6UL,                /*!< Timer 3 request */
  ADC_EMUX_EM0_TMR4                          = 0x7UL,                /*!< Timer 4 request */
  ADC_EMUX_EM0_Cycle                         = 0xFUL,                /*!< Cycle mode */
} ADC_EMUX_EM0_Enum;

typedef enum {
  ADC_EMUX_EM1_SwReq                         = 0x0UL,                /*!< software request by GSYNC bit */
  ADC_EMUX_EM1_GPIOA                         = 0x1UL,                /*!< GPIOA interrupt */
  ADC_EMUX_EM1_GPIOB                         = 0x2UL,                /*!< GPIOB interrupt */
  ADC_EMUX_EM1_TMR0                          = 0x3UL,                /*!< Timer 0 request */
  ADC_EMUX_EM1_TMR1                          = 0x4UL,                /*!< Timer 1 request */
  ADC_EMUX_EM1_TMR2                          = 0x5UL,                /*!< Timer 2 request */
  ADC_EMUX_EM1_TMR3                          = 0x6UL,                /*!< Timer 3 request */
  ADC_EMUX_EM1_TMR4                          = 0x7UL,                /*!< Timer 4 request */
  ADC_EMUX_EM1_Cycle                         = 0xFUL,                /*!< Cycle mode */
} ADC_EMUX_EM1_Enum;

typedef enum {
  ADC_EMUX_EM2_SwReq                         = 0x0UL,                /*!< software request by GSYNC bit */
  ADC_EMUX_EM2_GPIOA                         = 0x1UL,                /*!< GPIOA interrupt */
  ADC_EMUX_EM2_GPIOB                         = 0x2UL,                /*!< GPIOB interrupt */
  ADC_EMUX_EM2_TMR0                          = 0x3UL,                /*!< Timer 0 request */
  ADC_EMUX_EM2_TMR1                          = 0x4UL,                /*!< Timer 1 request */
  ADC_EMUX_EM2_TMR2                          = 0x5UL,                /*!< Timer 2 request */
  ADC_EMUX_EM2_TMR3                          = 0x6UL,                /*!< Timer 3 request */
  ADC_EMUX_EM2_TMR4                          = 0x7UL,                /*!< Timer 4 request */
  ADC_EMUX_EM2_Cycle                         = 0xFUL,                /*!< Cycle mode */
} ADC_EMUX_EM2_Enum;

typedef enum {
  ADC_EMUX_EM3_SwReq                         = 0x0UL,                /*!< software request by GSYNC bit */
  ADC_EMUX_EM3_GPIOA                         = 0x1UL,                /*!< GPIOA interrupt */
  ADC_EMUX_EM3_GPIOB                         = 0x2UL,                /*!< GPIOB interrupt */
  ADC_EMUX_EM3_TMR0                          = 0x3UL,                /*!< Timer 0 request */
  ADC_EMUX_EM3_TMR1                          = 0x4UL,                /*!< Timer 1 request */
  ADC_EMUX_EM3_TMR2                          = 0x5UL,                /*!< Timer 2 request */
  ADC_EMUX_EM3_TMR3                          = 0x6UL,                /*!< Timer 3 request */
  ADC_EMUX_EM3_TMR4                          = 0x7UL,                /*!< Timer 4 request */
  ADC_EMUX_EM3_Cycle                         = 0xFUL,                /*!< Cycle mode */
} ADC_EMUX_EM3_Enum;

/*--  RIS: Raw interrupt status register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t SEQRIS0                :1;                                /*!< Sequencer 0 raw interrupt status */
  uint32_t SEQRIS1                :1;                                /*!< Sequencer 1 raw interrupt status */
  uint32_t SEQRIS2                :1;                                /*!< Sequencer 2 raw interrupt status */
  uint32_t SEQRIS3                :1;                                /*!< Sequencer 3 raw interrupt status */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t DCRIS0                 :1;                                /*!< Raw interrupt status of Digital Comparator 0 */
  uint32_t DCRIS1                 :1;                                /*!< Raw interrupt status of Digital Comparator 1 */
  uint32_t DCRIS2                 :1;                                /*!< Raw interrupt status of Digital Comparator 2 */
  uint32_t DCRIS3                 :1;                                /*!< Raw interrupt status of Digital Comparator 3 */
  uint32_t DCRIS4                 :1;                                /*!< Raw interrupt status of Digital Comparator 4 */
  uint32_t DCRIS5                 :1;                                /*!< Raw interrupt status of Digital Comparator 5 */
  uint32_t DCRIS6                 :1;                                /*!< Raw interrupt status of Digital Comparator 6 */
  uint32_t DCRIS7                 :1;                                /*!< Raw interrupt status of Digital Comparator 7 */
} _ADC_RIS_bits;

/* Bit field positions: */
#define ADC_RIS_SEQRIS0_Pos                   0                      /*!< Sequencer 0 raw interrupt status */
#define ADC_RIS_SEQRIS1_Pos                   1                      /*!< Sequencer 1 raw interrupt status */
#define ADC_RIS_SEQRIS2_Pos                   2                      /*!< Sequencer 2 raw interrupt status */
#define ADC_RIS_SEQRIS3_Pos                   3                      /*!< Sequencer 3 raw interrupt status */
#define ADC_RIS_DCRIS0_Pos                    8                      /*!< Raw interrupt status of Digital Comparator 0 */
#define ADC_RIS_DCRIS1_Pos                    9                      /*!< Raw interrupt status of Digital Comparator 1 */
#define ADC_RIS_DCRIS2_Pos                    10                     /*!< Raw interrupt status of Digital Comparator 2 */
#define ADC_RIS_DCRIS3_Pos                    11                     /*!< Raw interrupt status of Digital Comparator 3 */
#define ADC_RIS_DCRIS4_Pos                    12                     /*!< Raw interrupt status of Digital Comparator 4 */
#define ADC_RIS_DCRIS5_Pos                    13                     /*!< Raw interrupt status of Digital Comparator 5 */
#define ADC_RIS_DCRIS6_Pos                    14                     /*!< Raw interrupt status of Digital Comparator 6 */
#define ADC_RIS_DCRIS7_Pos                    15                     /*!< Raw interrupt status of Digital Comparator 7 */

/* Bit field masks: */
#define ADC_RIS_SEQRIS0_Msk                   0x00000001UL           /*!< Sequencer 0 raw interrupt status */
#define ADC_RIS_SEQRIS1_Msk                   0x00000002UL           /*!< Sequencer 1 raw interrupt status */
#define ADC_RIS_SEQRIS2_Msk                   0x00000004UL           /*!< Sequencer 2 raw interrupt status */
#define ADC_RIS_SEQRIS3_Msk                   0x00000008UL           /*!< Sequencer 3 raw interrupt status */
#define ADC_RIS_DCRIS0_Msk                    0x00000100UL           /*!< Raw interrupt status of Digital Comparator 0 */
#define ADC_RIS_DCRIS1_Msk                    0x00000200UL           /*!< Raw interrupt status of Digital Comparator 1 */
#define ADC_RIS_DCRIS2_Msk                    0x00000400UL           /*!< Raw interrupt status of Digital Comparator 2 */
#define ADC_RIS_DCRIS3_Msk                    0x00000800UL           /*!< Raw interrupt status of Digital Comparator 3 */
#define ADC_RIS_DCRIS4_Msk                    0x00001000UL           /*!< Raw interrupt status of Digital Comparator 4 */
#define ADC_RIS_DCRIS5_Msk                    0x00002000UL           /*!< Raw interrupt status of Digital Comparator 5 */
#define ADC_RIS_DCRIS6_Msk                    0x00004000UL           /*!< Raw interrupt status of Digital Comparator 6 */
#define ADC_RIS_DCRIS7_Msk                    0x00008000UL           /*!< Raw interrupt status of Digital Comparator 7 */

/*--  IM: Interrupt mask register -----------------------------------------------------------------------------*/
typedef struct {
  uint32_t SEQIM0                 :1;                                /*!< Sequencer 0 interrupt mask */
  uint32_t SEQIM1                 :1;                                /*!< Sequencer 1 interrupt mask */
  uint32_t SEQIM2                 :1;                                /*!< Sequencer 2 interrupt mask */
  uint32_t SEQIM3                 :1;                                /*!< Sequencer 3 interrupt mask */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t DCIM0                  :1;                                /*!< Interrupt mask of Digital Comparator 0 */
  uint32_t DCIM1                  :1;                                /*!< Interrupt mask of Digital Comparator 1 */
  uint32_t DCIM2                  :1;                                /*!< Interrupt mask of Digital Comparator 2 */
  uint32_t DCIM3                  :1;                                /*!< Interrupt mask of Digital Comparator 3 */
  uint32_t DCIM4                  :1;                                /*!< Interrupt mask of Digital Comparator 4 */
  uint32_t DCIM5                  :1;                                /*!< Interrupt mask of Digital Comparator 5 */
  uint32_t DCIM6                  :1;                                /*!< Interrupt mask of Digital Comparator 6 */
  uint32_t DCIM7                  :1;                                /*!< Interrupt mask of Digital Comparator 7 */
} _ADC_IM_bits;

/* Bit field positions: */
#define ADC_IM_SEQIM0_Pos                     0                      /*!< Sequencer 0 interrupt mask */
#define ADC_IM_SEQIM1_Pos                     1                      /*!< Sequencer 1 interrupt mask */
#define ADC_IM_SEQIM2_Pos                     2                      /*!< Sequencer 2 interrupt mask */
#define ADC_IM_SEQIM3_Pos                     3                      /*!< Sequencer 3 interrupt mask */
#define ADC_IM_DCIM0_Pos                      8                      /*!< Interrupt mask of Digital Comparator 0 */
#define ADC_IM_DCIM1_Pos                      9                      /*!< Interrupt mask of Digital Comparator 1 */
#define ADC_IM_DCIM2_Pos                      10                     /*!< Interrupt mask of Digital Comparator 2 */
#define ADC_IM_DCIM3_Pos                      11                     /*!< Interrupt mask of Digital Comparator 3 */
#define ADC_IM_DCIM4_Pos                      12                     /*!< Interrupt mask of Digital Comparator 4 */
#define ADC_IM_DCIM5_Pos                      13                     /*!< Interrupt mask of Digital Comparator 5 */
#define ADC_IM_DCIM6_Pos                      14                     /*!< Interrupt mask of Digital Comparator 6 */
#define ADC_IM_DCIM7_Pos                      15                     /*!< Interrupt mask of Digital Comparator 7 */

/* Bit field masks: */
#define ADC_IM_SEQIM0_Msk                     0x00000001UL           /*!< Sequencer 0 interrupt mask */
#define ADC_IM_SEQIM1_Msk                     0x00000002UL           /*!< Sequencer 1 interrupt mask */
#define ADC_IM_SEQIM2_Msk                     0x00000004UL           /*!< Sequencer 2 interrupt mask */
#define ADC_IM_SEQIM3_Msk                     0x00000008UL           /*!< Sequencer 3 interrupt mask */
#define ADC_IM_DCIM0_Msk                      0x00000100UL           /*!< Interrupt mask of Digital Comparator 0 */
#define ADC_IM_DCIM1_Msk                      0x00000200UL           /*!< Interrupt mask of Digital Comparator 1 */
#define ADC_IM_DCIM2_Msk                      0x00000400UL           /*!< Interrupt mask of Digital Comparator 2 */
#define ADC_IM_DCIM3_Msk                      0x00000800UL           /*!< Interrupt mask of Digital Comparator 3 */
#define ADC_IM_DCIM4_Msk                      0x00001000UL           /*!< Interrupt mask of Digital Comparator 4 */
#define ADC_IM_DCIM5_Msk                      0x00002000UL           /*!< Interrupt mask of Digital Comparator 5 */
#define ADC_IM_DCIM6_Msk                      0x00004000UL           /*!< Interrupt mask of Digital Comparator 6 */
#define ADC_IM_DCIM7_Msk                      0x00008000UL           /*!< Interrupt mask of Digital Comparator 7 */

/*--  MIS: Masked interrupt status and clear register ---------------------------------------------------------*/
typedef struct {
  uint32_t SEQMIS0                :1;                                /*!< Sequencer 0 masked interrupt status */
  uint32_t SEQMIS1                :1;                                /*!< Sequencer 1 masked interrupt status  */
  uint32_t SEQMIS2                :1;                                /*!< Sequencer 2 masked interrupt status  */
  uint32_t SEQMIS3                :1;                                /*!< Sequencer 3 masked interrupt status  */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t DCMIS0                 :1;                                /*!< DC 0 masked interrupt status  */
  uint32_t DCMIS1                 :1;                                /*!< DC 1 masked interrupt status  */
  uint32_t DCMIS2                 :1;                                /*!< DC 2 masked interrupt status  */
  uint32_t DCMIS3                 :1;                                /*!< DC 3 masked interrupt status  */
  uint32_t DCMIS4                 :1;                                /*!< DC 4 masked interrupt status  */
  uint32_t DCMIS5                 :1;                                /*!< DC 5 masked interrupt status  */
  uint32_t DCMIS6                 :1;                                /*!< DC 6 masked interrupt status  */
  uint32_t DCMIS7                 :1;                                /*!< DC 7 masked interrupt status  */
} _ADC_MIS_bits;

/* Bit field positions: */
#define ADC_MIS_SEQMIS0_Pos                   0                      /*!< Sequencer 0 masked interrupt status */
#define ADC_MIS_SEQMIS1_Pos                   1                      /*!< Sequencer 1 masked interrupt status  */
#define ADC_MIS_SEQMIS2_Pos                   2                      /*!< Sequencer 2 masked interrupt status  */
#define ADC_MIS_SEQMIS3_Pos                   3                      /*!< Sequencer 3 masked interrupt status  */
#define ADC_MIS_DCMIS0_Pos                    8                      /*!< DC 0 masked interrupt status  */
#define ADC_MIS_DCMIS1_Pos                    9                      /*!< DC 1 masked interrupt status  */
#define ADC_MIS_DCMIS2_Pos                    10                     /*!< DC 2 masked interrupt status  */
#define ADC_MIS_DCMIS3_Pos                    11                     /*!< DC 3 masked interrupt status  */
#define ADC_MIS_DCMIS4_Pos                    12                     /*!< DC 4 masked interrupt status  */
#define ADC_MIS_DCMIS5_Pos                    13                     /*!< DC 5 masked interrupt status  */
#define ADC_MIS_DCMIS6_Pos                    14                     /*!< DC 6 masked interrupt status  */
#define ADC_MIS_DCMIS7_Pos                    15                     /*!< DC 7 masked interrupt status  */

/* Bit field masks: */
#define ADC_MIS_SEQMIS0_Msk                   0x00000001UL           /*!< Sequencer 0 masked interrupt status */
#define ADC_MIS_SEQMIS1_Msk                   0x00000002UL           /*!< Sequencer 1 masked interrupt status  */
#define ADC_MIS_SEQMIS2_Msk                   0x00000004UL           /*!< Sequencer 2 masked interrupt status  */
#define ADC_MIS_SEQMIS3_Msk                   0x00000008UL           /*!< Sequencer 3 masked interrupt status  */
#define ADC_MIS_DCMIS0_Msk                    0x00000100UL           /*!< DC 0 masked interrupt status  */
#define ADC_MIS_DCMIS1_Msk                    0x00000200UL           /*!< DC 1 masked interrupt status  */
#define ADC_MIS_DCMIS2_Msk                    0x00000400UL           /*!< DC 2 masked interrupt status  */
#define ADC_MIS_DCMIS3_Msk                    0x00000800UL           /*!< DC 3 masked interrupt status  */
#define ADC_MIS_DCMIS4_Msk                    0x00001000UL           /*!< DC 4 masked interrupt status  */
#define ADC_MIS_DCMIS5_Msk                    0x00002000UL           /*!< DC 5 masked interrupt status  */
#define ADC_MIS_DCMIS6_Msk                    0x00004000UL           /*!< DC 6 masked interrupt status  */
#define ADC_MIS_DCMIS7_Msk                    0x00008000UL           /*!< DC 7 masked interrupt status  */

/*--  IC: Interrupt clear register ----------------------------------------------------------------------------*/
typedef struct {
  uint32_t SEQIC0                 :1;                                /*!< Sequencer 0 interrupt status clear */
  uint32_t SEQIC1                 :1;                                /*!< Sequencer 1 interrupt status clear */
  uint32_t SEQIC2                 :1;                                /*!< Sequencer 2 interrupt status clear */
  uint32_t SEQIC3                 :1;                                /*!< Sequencer 3 interrupt status clear */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t DCIC0                  :1;                                /*!< DC 0 interrupt status clear */
  uint32_t DCIC1                  :1;                                /*!< DC 1 interrupt status clear */
  uint32_t DCIC2                  :1;                                /*!< DC 2 interrupt status clear */
  uint32_t DCIC3                  :1;                                /*!< DC 3 interrupt status clear */
  uint32_t DCIC4                  :1;                                /*!< DC 4 interrupt status clear */
  uint32_t DCIC5                  :1;                                /*!< DC 5 interrupt status clear */
  uint32_t DCIC6                  :1;                                /*!< DC 6 interrupt status clear */
  uint32_t DCIC7                  :1;                                /*!< DC 7 interrupt status clear */
} _ADC_IC_bits;

/* Bit field positions: */
#define ADC_IC_SEQIC0_Pos                     0                      /*!< Sequencer 0 interrupt status clear */
#define ADC_IC_SEQIC1_Pos                     1                      /*!< Sequencer 1 interrupt status clear */
#define ADC_IC_SEQIC2_Pos                     2                      /*!< Sequencer 2 interrupt status clear */
#define ADC_IC_SEQIC3_Pos                     3                      /*!< Sequencer 3 interrupt status clear */
#define ADC_IC_DCIC0_Pos                      8                      /*!< DC 0 interrupt status clear */
#define ADC_IC_DCIC1_Pos                      9                      /*!< DC 1 interrupt status clear */
#define ADC_IC_DCIC2_Pos                      10                     /*!< DC 2 interrupt status clear */
#define ADC_IC_DCIC3_Pos                      11                     /*!< DC 3 interrupt status clear */
#define ADC_IC_DCIC4_Pos                      12                     /*!< DC 4 interrupt status clear */
#define ADC_IC_DCIC5_Pos                      13                     /*!< DC 5 interrupt status clear */
#define ADC_IC_DCIC6_Pos                      14                     /*!< DC 6 interrupt status clear */
#define ADC_IC_DCIC7_Pos                      15                     /*!< DC 7 interrupt status clear */

/* Bit field masks: */
#define ADC_IC_SEQIC0_Msk                     0x00000001UL           /*!< Sequencer 0 interrupt status clear */
#define ADC_IC_SEQIC1_Msk                     0x00000002UL           /*!< Sequencer 1 interrupt status clear */
#define ADC_IC_SEQIC2_Msk                     0x00000004UL           /*!< Sequencer 2 interrupt status clear */
#define ADC_IC_SEQIC3_Msk                     0x00000008UL           /*!< Sequencer 3 interrupt status clear */
#define ADC_IC_DCIC0_Msk                      0x00000100UL           /*!< DC 0 interrupt status clear */
#define ADC_IC_DCIC1_Msk                      0x00000200UL           /*!< DC 1 interrupt status clear */
#define ADC_IC_DCIC2_Msk                      0x00000400UL           /*!< DC 2 interrupt status clear */
#define ADC_IC_DCIC3_Msk                      0x00000800UL           /*!< DC 3 interrupt status clear */
#define ADC_IC_DCIC4_Msk                      0x00001000UL           /*!< DC 4 interrupt status clear */
#define ADC_IC_DCIC5_Msk                      0x00002000UL           /*!< DC 5 interrupt status clear */
#define ADC_IC_DCIC6_Msk                      0x00004000UL           /*!< DC 6 interrupt status clear */
#define ADC_IC_DCIC7_Msk                      0x00008000UL           /*!< DC 7 interrupt status clear */

/*-- SEQ: SRQSEL: Sequencer request ADC channels selection register 0 -----------------------------------------*/
typedef struct {
  uint32_t RQ0                    :4;                                /*!< Select ADC channel for request 0 */
  uint32_t RQ1                    :4;                                /*!< Select ADC channel for request 1 */
  uint32_t RQ2                    :4;                                /*!< Select ADC channel for request 2 */
  uint32_t RQ3                    :4;                                /*!< Select ADC channel for request 3 */
  uint32_t RQ4                    :4;                                /*!< Select ADC channel for request 4 */
  uint32_t RQ5                    :4;                                /*!< Select ADC channel for request 5 */
  uint32_t RQ6                    :4;                                /*!< Select ADC channel for request 6 */
  uint32_t RQ7                    :4;                                /*!< Select ADC channel for request 7 */
} _ADC_SEQ_SRQSEL_bits;

/* Bit field positions: */
#define ADC_SEQ_SRQSEL_RQ0_Pos                0                      /*!< Select ADC channel for request 0 */
#define ADC_SEQ_SRQSEL_RQ1_Pos                4                      /*!< Select ADC channel for request 1 */
#define ADC_SEQ_SRQSEL_RQ2_Pos                8                      /*!< Select ADC channel for request 2 */
#define ADC_SEQ_SRQSEL_RQ3_Pos                12                     /*!< Select ADC channel for request 3 */
#define ADC_SEQ_SRQSEL_RQ4_Pos                16                     /*!< Select ADC channel for request 4 */
#define ADC_SEQ_SRQSEL_RQ5_Pos                20                     /*!< Select ADC channel for request 5 */
#define ADC_SEQ_SRQSEL_RQ6_Pos                24                     /*!< Select ADC channel for request 6 */
#define ADC_SEQ_SRQSEL_RQ7_Pos                28                     /*!< Select ADC channel for request 7 */

/* Bit field masks: */
#define ADC_SEQ_SRQSEL_RQ0_Msk                0x0000000FUL           /*!< Select ADC channel for request 0 */
#define ADC_SEQ_SRQSEL_RQ1_Msk                0x000000F0UL           /*!< Select ADC channel for request 1 */
#define ADC_SEQ_SRQSEL_RQ2_Msk                0x00000F00UL           /*!< Select ADC channel for request 2 */
#define ADC_SEQ_SRQSEL_RQ3_Msk                0x0000F000UL           /*!< Select ADC channel for request 3 */
#define ADC_SEQ_SRQSEL_RQ4_Msk                0x000F0000UL           /*!< Select ADC channel for request 4 */
#define ADC_SEQ_SRQSEL_RQ5_Msk                0x00F00000UL           /*!< Select ADC channel for request 5 */
#define ADC_SEQ_SRQSEL_RQ6_Msk                0x0F000000UL           /*!< Select ADC channel for request 6 */
#define ADC_SEQ_SRQSEL_RQ7_Msk                0xF0000000UL           /*!< Select ADC channel for request 7 */

/*-- SEQ: SRQCTL: Sequencer request control register ----------------------------------------------------------*/
typedef struct {
  uint32_t RQMAX                  :3;                                /*!< Request queue max depth */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t QAVGEN                 :1;                                /*!< Queue avearage (scanning) enable */
  uint32_t QAVGVAL                :3;                                /*!< Queue average value */
} _ADC_SEQ_SRQCTL_bits;

/* Bit field positions: */
#define ADC_SEQ_SRQCTL_RQMAX_Pos              0                      /*!< Request queue max depth */
#define ADC_SEQ_SRQCTL_QAVGEN_Pos             8                      /*!< Queue avearage (scanning) enable */
#define ADC_SEQ_SRQCTL_QAVGVAL_Pos            9                      /*!< Queue average value */

/* Bit field masks: */
#define ADC_SEQ_SRQCTL_RQMAX_Msk              0x00000007UL           /*!< Request queue max depth */
#define ADC_SEQ_SRQCTL_QAVGEN_Msk             0x00000100UL           /*!< Queue avearage (scanning) enable */
#define ADC_SEQ_SRQCTL_QAVGVAL_Msk            0x00000E00UL           /*!< Queue average value */

/* Bit field enums: */
typedef enum {
  ADC_SEQ_SRQCTL_QAVGVAL_Disable             = 0x0UL,                /*!< Average disabled */
  ADC_SEQ_SRQCTL_QAVGVAL_Average2            = 0x1UL,                /*!< Average with 2 measures */
  ADC_SEQ_SRQCTL_QAVGVAL_Average4            = 0x2UL,                /*!< Average with 4 measures */
  ADC_SEQ_SRQCTL_QAVGVAL_Average8            = 0x3UL,                /*!< Average with 8 measures */
  ADC_SEQ_SRQCTL_QAVGVAL_Average16           = 0x4UL,                /*!< Average with 16 measures */
  ADC_SEQ_SRQCTL_QAVGVAL_Average32           = 0x5UL,                /*!< Average with 32 measures */
  ADC_SEQ_SRQCTL_QAVGVAL_Average64           = 0x6UL,                /*!< Average with 64 measures */
} ADC_SEQ_SRQCTL_QAVGVAL_Enum;

/*-- SEQ: SRQSTAT: Sequencer request status register ----------------------------------------------------------*/
typedef struct {
  uint32_t RQPTR                  :3;                                /*!< Pointer to queue current request */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t RQBUSY                 :1;                                /*!< Active request status */
} _ADC_SEQ_SRQSTAT_bits;

/* Bit field positions: */
#define ADC_SEQ_SRQSTAT_RQPTR_Pos             0                      /*!< Pointer to queue current request */
#define ADC_SEQ_SRQSTAT_RQBUSY_Pos            8                      /*!< Active request status */

/* Bit field masks: */
#define ADC_SEQ_SRQSTAT_RQPTR_Msk             0x00000007UL           /*!< Pointer to queue current request */
#define ADC_SEQ_SRQSTAT_RQBUSY_Msk            0x00000100UL           /*!< Active request status */

/*-- SEQ: SDMACTL: Sequencer DMA control register -------------------------------------------------------------*/
typedef struct {
  uint32_t DMAEN                  :1;                                /*!< Enable DMA use */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t WMARK                  :3;                                /*!< FIFO load threshold for DMA request generation */
} _ADC_SEQ_SDMACTL_bits;

/* Bit field positions: */
#define ADC_SEQ_SDMACTL_DMAEN_Pos             0                      /*!< Enable DMA use */
#define ADC_SEQ_SDMACTL_WMARK_Pos             8                      /*!< FIFO load threshold for DMA request generation */

/* Bit field masks: */
#define ADC_SEQ_SDMACTL_DMAEN_Msk             0x00000001UL           /*!< Enable DMA use */
#define ADC_SEQ_SDMACTL_WMARK_Msk             0x00000700UL           /*!< FIFO load threshold for DMA request generation */

/* Bit field enums: */
typedef enum {
  ADC_SEQ_SDMACTL_WMARK_Level1               = 0x1UL,                /*!< 1 measure for dma request */
  ADC_SEQ_SDMACTL_WMARK_Level2               = 0x2UL,                /*!< 2 measures for dma request */
  ADC_SEQ_SDMACTL_WMARK_Level4               = 0x3UL,                /*!< 4 measures for dma request */
  ADC_SEQ_SDMACTL_WMARK_Level8               = 0x4UL,                /*!< 8 measures for dma request */
  ADC_SEQ_SDMACTL_WMARK_Level16              = 0x5UL,                /*!< 16 measures for dma request */
  ADC_SEQ_SDMACTL_WMARK_Level32              = 0x6UL,                /*!< 32 measures for dma request */
} ADC_SEQ_SDMACTL_WMARK_Enum;

/*-- SEQ: SCCTL: Sequencer ADC interrupt and restart counter control register ---------------------------------*/
typedef struct {
  uint32_t RCNT                   :8;                                /*!< Current number of ADC restarts by sequencer */
  uint32_t RAVGEN                 :1;                                /*!< Average of ADC restarts enable */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t ICNT                   :8;                                /*!< Number of ADC restarts for interrupt generation */
} _ADC_SEQ_SCCTL_bits;

/* Bit field positions: */
#define ADC_SEQ_SCCTL_RCNT_Pos                0                      /*!< Current number of ADC restarts by sequencer */
#define ADC_SEQ_SCCTL_RAVGEN_Pos              8                      /*!< Average of ADC restarts enable */
#define ADC_SEQ_SCCTL_ICNT_Pos                16                     /*!< Number of ADC restarts for interrupt generation */

/* Bit field masks: */
#define ADC_SEQ_SCCTL_RCNT_Msk                0x000000FFUL           /*!< Current number of ADC restarts by sequencer */
#define ADC_SEQ_SCCTL_RAVGEN_Msk              0x00000100UL           /*!< Average of ADC restarts enable */
#define ADC_SEQ_SCCTL_ICNT_Msk                0x00FF0000UL           /*!< Number of ADC restarts for interrupt generation */

/*-- SEQ: SCVAL: Sequencer ADC interrupt and restart counter current value register --------------------------------*/
typedef struct {
  uint32_t RCNT                   :8;                                /*!< Current number of ADC restarts by sequencer */
  uint32_t                        :8;                                /*!< RESERVED */
  uint32_t ICNT                   :8;                                /*!< Current number of ADC restarts for interrupt generation */
  uint32_t ICLR                   :1;                                /*!< Clear interrupt counter */
} _ADC_SEQ_SCVAL_bits;

/* Bit field positions: */
#define ADC_SEQ_SCVAL_RCNT_Pos                0                      /*!< Current number of ADC restarts by sequencer */
#define ADC_SEQ_SCVAL_ICNT_Pos                16                     /*!< Current number of ADC restarts for interrupt generation */
#define ADC_SEQ_SCVAL_ICLR_Pos                24                     /*!< Clear interrupt counter */

/* Bit field masks: */
#define ADC_SEQ_SCVAL_RCNT_Msk                0x000000FFUL           /*!< Current number of ADC restarts by sequencer */
#define ADC_SEQ_SCVAL_ICNT_Msk                0x00FF0000UL           /*!< Current number of ADC restarts for interrupt generation */
#define ADC_SEQ_SCVAL_ICLR_Msk                0x01000000UL           /*!< Clear interrupt counter */

/*-- SEQ: SDC: Sequencer digital comparator selection register ------------------------------------------------*/
typedef struct {
  uint32_t DC0                    :1;                                /*!< Enable DC 0 */
  uint32_t DC1                    :1;                                /*!< Enable DC 1 */
  uint32_t DC2                    :1;                                /*!< Enable DC 2 */
  uint32_t DC3                    :1;                                /*!< Enable DC 3 */
  uint32_t DC4                    :1;                                /*!< Enable DC 4 */
  uint32_t DC5                    :1;                                /*!< Enable DC 5 */
  uint32_t DC6                    :1;                                /*!< Enable DC 6 */
  uint32_t DC7                    :1;                                /*!< Enable DC 7 */
} _ADC_SEQ_SDC_bits;

/* Bit field positions: */
#define ADC_SEQ_SDC_DC0_Pos                   0                      /*!< Enable DC 0 */
#define ADC_SEQ_SDC_DC1_Pos                   1                      /*!< Enable DC 1 */
#define ADC_SEQ_SDC_DC2_Pos                   2                      /*!< Enable DC 2 */
#define ADC_SEQ_SDC_DC3_Pos                   3                      /*!< Enable DC 3 */
#define ADC_SEQ_SDC_DC4_Pos                   4                      /*!< Enable DC 4 */
#define ADC_SEQ_SDC_DC5_Pos                   5                      /*!< Enable DC 5 */
#define ADC_SEQ_SDC_DC6_Pos                   6                      /*!< Enable DC 6 */
#define ADC_SEQ_SDC_DC7_Pos                   7                      /*!< Enable DC 7 */

/* Bit field masks: */
#define ADC_SEQ_SDC_DC0_Msk                   0x00000001UL           /*!< Enable DC 0 */
#define ADC_SEQ_SDC_DC1_Msk                   0x00000002UL           /*!< Enable DC 1 */
#define ADC_SEQ_SDC_DC2_Msk                   0x00000004UL           /*!< Enable DC 2 */
#define ADC_SEQ_SDC_DC3_Msk                   0x00000008UL           /*!< Enable DC 3 */
#define ADC_SEQ_SDC_DC4_Msk                   0x00000010UL           /*!< Enable DC 4 */
#define ADC_SEQ_SDC_DC5_Msk                   0x00000020UL           /*!< Enable DC 5 */
#define ADC_SEQ_SDC_DC6_Msk                   0x00000040UL           /*!< Enable DC 6 */
#define ADC_SEQ_SDC_DC7_Msk                   0x00000080UL           /*!< Enable DC 7 */

/*-- SEQ: SRTMR: Sequencer ADC restart timer register ---------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :24;                               /*!< Sequencer ADC restart timer value */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t NOWAIT                 :1;                                /*!< Timer update with no waiting the end of current seq task */
} _ADC_SEQ_SRTMR_bits;

/* Bit field positions: */
#define ADC_SEQ_SRTMR_VAL_Pos                 0                      /*!< Sequencer ADC restart timer value */
#define ADC_SEQ_SRTMR_NOWAIT_Pos              31                     /*!< Timer update with no waiting the end of current seq task */

/* Bit field masks: */
#define ADC_SEQ_SRTMR_VAL_Msk                 0x00FFFFFFUL           /*!< Sequencer ADC restart timer value */
#define ADC_SEQ_SRTMR_NOWAIT_Msk              0x80000000UL           /*!< Timer update with no waiting the end of current seq task */

/*-- SEQ: SFLOAD: Sequencer FIFO load status register ---------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :6;                                /*!< Sequencer FIFO current load value */
} _ADC_SEQ_SFLOAD_bits;

/* Bit field positions: */
#define ADC_SEQ_SFLOAD_VAL_Pos                0                      /*!< Sequencer FIFO current load value */

/* Bit field masks: */
#define ADC_SEQ_SFLOAD_VAL_Msk                0x0000003FUL           /*!< Sequencer FIFO current load value */

/*-- SEQ: SFIFO: Sequencer FIFO register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t DATA                   :12;                               /*!< AD conversion value */
} _ADC_SEQ_SFIFO_bits;

/* Bit field positions: */
#define ADC_SEQ_SFIFO_DATA_Pos                0                      /*!< AD conversion value */

/* Bit field masks: */
#define ADC_SEQ_SFIFO_DATA_Msk                0x00000FFFUL           /*!< AD conversion value */

/*-- DC: DCTL: Digital comparator control register ------------------------------------------------------------*/
typedef struct {
  uint32_t CIM                    :2;                                /*!< DC interrupt generation mode */
  uint32_t CIC                    :2;                                /*!< DC interrupt generation compare conditions */
  uint32_t CIE                    :1;                                /*!< Enable DC interrupt generation */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t CTM                    :2;                                /*!< DC output trigger mode */
  uint32_t CTC                    :2;                                /*!< DC output trigger compare conditions */
  uint32_t CTE                    :1;                                /*!< Enable DC output trigger */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t CHNL                   :4;                                /*!< ADC channel selection */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t SRC                    :1;                                /*!< Select data source for comparation: ADC module (0) or sequencer(1) */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t HWTCLR                 :1;                                /*!< Hardware output trigger clear */
} _ADC_DC_DCTL_bits;

/* Bit field positions: */
#define ADC_DC_DCTL_CIM_Pos                   0                      /*!< DC interrupt generation mode */
#define ADC_DC_DCTL_CIC_Pos                   2                      /*!< DC interrupt generation compare conditions */
#define ADC_DC_DCTL_CIE_Pos                   4                      /*!< Enable DC interrupt generation */
#define ADC_DC_DCTL_CTM_Pos                   8                      /*!< DC output trigger mode */
#define ADC_DC_DCTL_CTC_Pos                   10                     /*!< DC output trigger compare conditions */
#define ADC_DC_DCTL_CTE_Pos                   12                     /*!< Enable DC output trigger */
#define ADC_DC_DCTL_CHNL_Pos                  16                     /*!< ADC channel selection */
#define ADC_DC_DCTL_SRC_Pos                   24                     /*!< Select data source for comparation: ADC module (0) or sequencer(1) */
#define ADC_DC_DCTL_HWTCLR_Pos                28                     /*!< Hardware output trigger clear */

/* Bit field masks: */
#define ADC_DC_DCTL_CIM_Msk                   0x00000003UL           /*!< DC interrupt generation mode */
#define ADC_DC_DCTL_CIC_Msk                   0x0000000CUL           /*!< DC interrupt generation compare conditions */
#define ADC_DC_DCTL_CIE_Msk                   0x00000010UL           /*!< Enable DC interrupt generation */
#define ADC_DC_DCTL_CTM_Msk                   0x00000300UL           /*!< DC output trigger mode */
#define ADC_DC_DCTL_CTC_Msk                   0x00000C00UL           /*!< DC output trigger compare conditions */
#define ADC_DC_DCTL_CTE_Msk                   0x00001000UL           /*!< Enable DC output trigger */
#define ADC_DC_DCTL_CHNL_Msk                  0x000F0000UL           /*!< ADC channel selection */
#define ADC_DC_DCTL_SRC_Msk                   0x01000000UL           /*!< Select data source for comparation: ADC module (0) or sequencer(1) */
#define ADC_DC_DCTL_HWTCLR_Msk                0x10000000UL           /*!< Hardware output trigger clear */

/* Bit field enums: */
typedef enum {
  ADC_DC_DCTL_CIM_Multiple                   = 0x0UL,                /*!< multiple trigger mode */
  ADC_DC_DCTL_CIM_Single                     = 0x1UL,                /*!< single trigger mode */
  ADC_DC_DCTL_CIM_MultipleHyst               = 0x2UL,                /*!< multiple trigger mode with hysteresis */
  ADC_DC_DCTL_CIM_SingleHyst                 = 0x3UL,                /*!< single trigger mode with hysteresis */
} ADC_DC_DCTL_CIM_Enum;

typedef enum {
  ADC_DC_DCTL_CIC_Low                        = 0x0UL,                /*!< result lower or equal COMP0 */
  ADC_DC_DCTL_CIC_Window                     = 0x1UL,                /*!< result between COMP0 and COMP1 or equal any of them */
  ADC_DC_DCTL_CIC_High                       = 0x2UL,                /*!< result higher or equal COMP1 */
} ADC_DC_DCTL_CIC_Enum;

typedef enum {
  ADC_DC_DCTL_CTM_Multiple                   = 0x0UL,                /*!< multiple trigger mode */
  ADC_DC_DCTL_CTM_Single                     = 0x1UL,                /*!< single trigger mode */
  ADC_DC_DCTL_CTM_MultipleHyst               = 0x2UL,                /*!< multiple trigger mode with hysteresis */
  ADC_DC_DCTL_CTM_SingleHyst                 = 0x3UL,                /*!< single trigger mode with hysteresis */
} ADC_DC_DCTL_CTM_Enum;

typedef enum {
  ADC_DC_DCTL_CTC_Low                        = 0x0UL,                /*!< result lower or equal COMP0 */
  ADC_DC_DCTL_CTC_Window                     = 0x1UL,                /*!< result between COMP0 and COMP1 or equal any of them */
  ADC_DC_DCTL_CTC_High                       = 0x2UL,                /*!< result higher or equal COMP1 */
} ADC_DC_DCTL_CTC_Enum;

/*-- DC: DCMP: Digital comparator range register --------------------------------------------------------------*/
typedef struct {
  uint32_t CMPL                   :12;                               /*!< Low threshold compare value */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t CMPH                   :12;                               /*!< High threshold compare value */
} _ADC_DC_DCMP_bits;

/* Bit field positions: */
#define ADC_DC_DCMP_CMPL_Pos                  0                      /*!< Low threshold compare value */
#define ADC_DC_DCMP_CMPH_Pos                  16                     /*!< High threshold compare value */

/* Bit field masks: */
#define ADC_DC_DCMP_CMPL_Msk                  0x00000FFFUL           /*!< Low threshold compare value */
#define ADC_DC_DCMP_CMPH_Msk                  0x0FFF0000UL           /*!< High threshold compare value */

/*-- DC: DDATA: Digital comparator last compared data register ------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :12;                               /*!< Value of last compared AD conversion result */
} _ADC_DC_DDATA_bits;

/* Bit field positions: */
#define ADC_DC_DDATA_VAL_Pos                  0                      /*!< Value of last compared AD conversion result */

/* Bit field masks: */
#define ADC_DC_DDATA_VAL_Msk                  0x00000FFFUL           /*!< Value of last compared AD conversion result */

/*--  ACTL: ADC module control register -----------------------------------------------------------------------*/
typedef struct {
  uint32_t ADCEN                  :1;                                /*!< Enable ADC module */
  uint32_t ADCRDY                 :1;                                /*!< ADC ready for conversions */
  uint32_t ADCENLDO               :1;                                /*!< Enable LDO */
  uint32_t ADCSTART               :1;                                /*!< Start ADC module */
  uint32_t SELRES                 :2;                                /*!< ADC resolution select */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t CALEN                  :1;                                /*!< Enable ADC internal calibration */
  uint32_t CALLOAD                :1;                                /*!< Load CALIN value to the ADC internal calibration system */
  uint32_t CALSTART               :1;                                /*!< Start ADC internal calibration */
  uint32_t CALBUSY                :1;                                /*!< ADC internal calibration in progress flag */
  uint32_t RANGELDO               :1;                                /*!< Select voltage range ADC module LDO 0.9/1.1 V */
  uint32_t DISLVL                 :1;                                /*!< Disable level-shifters */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t CALIN                  :7;                                /*!< ADC calibration input value */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t CALOUT                 :7;                                /*!< ADC calibration output value */
} _ADC_ACTL_bits;

/* Bit field positions: */
#define ADC_ACTL_ADCEN_Pos                    0                      /*!< Enable ADC module */
#define ADC_ACTL_ADCRDY_Pos                   1                      /*!< ADC ready for conversions */
#define ADC_ACTL_ADCENLDO_Pos                 2                      /*!< Enable LDO */
#define ADC_ACTL_ADCSTART_Pos                 3                      /*!< Start ADC module */
#define ADC_ACTL_SELRES_Pos                   4                      /*!< ADC resolution select */
#define ADC_ACTL_CALEN_Pos                    8                      /*!< Enable ADC internal calibration */
#define ADC_ACTL_CALLOAD_Pos                  9                      /*!< Load CALIN value to the ADC internal calibration system */
#define ADC_ACTL_CALSTART_Pos                 10                     /*!< Start ADC internal calibration */
#define ADC_ACTL_CALBUSY_Pos                  11                     /*!< ADC internal calibration in progress flag */
#define ADC_ACTL_RANGELDO_Pos                 12                     /*!< Select voltage range ADC module LDO 0.9/1.1 V */
#define ADC_ACTL_DISLVL_Pos                   13                     /*!< Disable level-shifters */
#define ADC_ACTL_CALIN_Pos                    16                     /*!< ADC calibration input value */
#define ADC_ACTL_CALOUT_Pos                   24                     /*!< ADC calibration output value */

/* Bit field masks: */
#define ADC_ACTL_ADCEN_Msk                    0x00000001UL           /*!< Enable ADC module */
#define ADC_ACTL_ADCRDY_Msk                   0x00000002UL           /*!< ADC ready for conversions */
#define ADC_ACTL_ADCENLDO_Msk                 0x00000004UL           /*!< Enable LDO */
#define ADC_ACTL_ADCSTART_Msk                 0x00000008UL           /*!< Start ADC module */
#define ADC_ACTL_SELRES_Msk                   0x00000030UL           /*!< ADC resolution select */
#define ADC_ACTL_CALEN_Msk                    0x00000100UL           /*!< Enable ADC internal calibration */
#define ADC_ACTL_CALLOAD_Msk                  0x00000200UL           /*!< Load CALIN value to the ADC internal calibration system */
#define ADC_ACTL_CALSTART_Msk                 0x00000400UL           /*!< Start ADC internal calibration */
#define ADC_ACTL_CALBUSY_Msk                  0x00000800UL           /*!< ADC internal calibration in progress flag */
#define ADC_ACTL_RANGELDO_Msk                 0x00001000UL           /*!< Select voltage range ADC module LDO 0.9/1.1 V */
#define ADC_ACTL_DISLVL_Msk                   0x00002000UL           /*!< Disable level-shifters */
#define ADC_ACTL_CALIN_Msk                    0x007F0000UL           /*!< ADC calibration input value */
#define ADC_ACTL_CALOUT_Msk                   0x7F000000UL           /*!< ADC calibration output value */

/* Bit field enums: */
typedef enum {
  ADC_ACTL_SELRES_6bit                       = 0x0UL,                /*!< 6 bit mode */
  ADC_ACTL_SELRES_8bit                       = 0x1UL,                /*!< 8 bit mode */
  ADC_ACTL_SELRES_10bit                      = 0x2UL,                /*!< 10 bit mode */
  ADC_ACTL_SELRES_12bit                      = 0x3UL,                /*!< 12 bit mode */
} ADC_ACTL_SELRES_Enum;

/*--  TACC0: ADC test access register -------------------------------------------------------------------------*/
typedef struct {
  uint32_t SOC                    :1;                                /*!< Generate Start Of Conversion pulse in test mode */
  uint32_t REARM                  :1;                                /*!< Generate REARM pulse in test mode */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t SEL                    :4;                                /*!< Select channel in test mode */
  uint32_t SELRES                 :2;                                /*!< Select resolution in test mode */
  uint32_t RSTADC                 :1;                                /*!< Reset ADC module in tesst mode */
  uint32_t BPCAL                  :1;                                /*!< Disable bypass calibration ADC module in test mode */
  uint32_t RSTCAL                 :1;                                /*!< Generate Reset Calculation pulse in test mode */
  uint32_t LOADCAL                :1;                                /*!< Generate Load Calculation pulse in test mode */
  uint32_t STARTCAL               :1;                                /*!< Generate Start Calculation pulse in test mode */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t KEY                    :16;                               /*!< Write key   0xFAAC to enter test mode */
} _ADC_TACC0_bits;

/* Bit field positions: */
#define ADC_TACC0_SOC_Pos                     0                      /*!< Generate Start Of Conversion pulse in test mode */
#define ADC_TACC0_REARM_Pos                   1                      /*!< Generate REARM pulse in test mode */
#define ADC_TACC0_SEL_Pos                     4                      /*!< Select channel in test mode */
#define ADC_TACC0_SELRES_Pos                  8                      /*!< Select resolution in test mode */
#define ADC_TACC0_RSTADC_Pos                  10                     /*!< Reset ADC module in tesst mode */
#define ADC_TACC0_BPCAL_Pos                   11                     /*!< Disable bypass calibration ADC module in test mode */
#define ADC_TACC0_RSTCAL_Pos                  12                     /*!< Generate Reset Calculation pulse in test mode */
#define ADC_TACC0_LOADCAL_Pos                 13                     /*!< Generate Load Calculation pulse in test mode */
#define ADC_TACC0_STARTCAL_Pos                14                     /*!< Generate Start Calculation pulse in test mode */
#define ADC_TACC0_KEY_Pos                     16                     /*!< Write key 0xFAAC to enter test mode */

/* Bit field masks: */
#define ADC_TACC0_SOC_Msk                     0x00000001UL           /*!< Generate Start Of Conversion pulse in test mode */
#define ADC_TACC0_REARM_Msk                   0x00000002UL           /*!< Generate REARM pulse in test mode */
#define ADC_TACC0_SEL_Msk                     0x000000F0UL           /*!< Select channel in test mode */
#define ADC_TACC0_SELRES_Msk                  0x00000300UL           /*!< Select resolution in test mode */
#define ADC_TACC0_RSTADC_Msk                  0x00000400UL           /*!< Reset ADC module in tesst mode */
#define ADC_TACC0_BPCAL_Msk                   0x00000800UL           /*!< Disable bypass calibration ADC module in test mode */
#define ADC_TACC0_RSTCAL_Msk                  0x00001000UL           /*!< Generate Reset Calculation pulse in test mode */
#define ADC_TACC0_LOADCAL_Msk                 0x00002000UL           /*!< Generate Load Calculation pulse in test mode */
#define ADC_TACC0_STARTCAL_Msk                0x00004000UL           /*!< Generate Start Calculation pulse in test mode */
#define ADC_TACC0_KEY_Msk                     0xFFFF0000UL           /*!< Write key 0xFAAC to enter test mode */

/* Bit field enums: */
typedef enum {
  ADC_TACC0_KEY_TEST_MODE                    = 0xFAACUL,             /*!< Value that allows to ADC test activities */
  ADC_TACC0_KEY_DUMMY_0                      = 0x0UL,                /*!< Example value that prevents entering to test mode */
  ADC_TACC0_KEY_DUMMY_1                      = 0x1UL,                /*!< Example value that prevents entering to test mode */
} ADC_TACC0_KEY_Enum;

/*--  TACC1: ADC test access register -------------------------------------------------------------------------*/
typedef struct {
  uint32_t DATA                   :12;                               /*!< Raw data value */
  uint32_t EOC                    :1;                                /*!< End Of Conversion signal value */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t EOCF                   :1;                                /*!< End Of Conversion falling edge detected */
  uint32_t EOCR                   :1;                                /*!< End Of Conversion rising edge detected */
} _ADC_TACC1_bits;

/* Bit field positions: */
#define ADC_TACC1_DATA_Pos                    0                      /*!< Raw data value */
#define ADC_TACC1_EOC_Pos                     12                     /*!< End Of Conversion signal value */
#define ADC_TACC1_EOCF_Pos                    16                     /*!< End Of Conversion falling edge detected */
#define ADC_TACC1_EOCR_Pos                    17                     /*!< End Of Conversion rising edge detected */

/* Bit field masks: */
#define ADC_TACC1_DATA_Msk                    0x00000FFFUL           /*!< Raw data value */
#define ADC_TACC1_EOC_Msk                     0x00001000UL           /*!< End Of Conversion signal value */
#define ADC_TACC1_EOCF_Msk                    0x00010000UL           /*!< End Of Conversion falling edge detected */
#define ADC_TACC1_EOCR_Msk                    0x00020000UL           /*!< End Of Conversion rising edge detected */

/*--  CHCTL: ADC channel control register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t OFFTRIM                :9;                                /*!< ADC channel offset trimm value */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t GAINTRIM               :9;                                /*!< ADC channel gain trimm value */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t PRIORITY               :1;                                /*!< ADC channel priority level */
} _ADC_CHCTL_bits;

/* Bit field positions: */
#define ADC_CHCTL_OFFTRIM_Pos                 0                      /*!< ADC channel offset trimm value */
#define ADC_CHCTL_GAINTRIM_Pos                16                     /*!< ADC channel gain trimm value */
#define ADC_CHCTL_PRIORITY_Pos                28                     /*!< ADC channel priority level */

/* Bit field masks: */
#define ADC_CHCTL_OFFTRIM_Msk                 0x000001FFUL           /*!< ADC channel offset trimm value */
#define ADC_CHCTL_GAINTRIM_Msk                0x01FF0000UL           /*!< ADC channel gain trimm value */
#define ADC_CHCTL_PRIORITY_Msk                0x10000000UL           /*!< ADC channel priority level */

/*--  CHDELAY: ADC channel delay register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t DELAY                  :16;                               /*!< ADC channel delay value */
} _ADC_CHDELAY_bits;

/* Bit field positions: */
#define ADC_CHDELAY_DELAY_Pos                 0                      /*!< ADC channel delay value */

/* Bit field masks: */
#define ADC_CHDELAY_DELAY_Msk                 0x0000FFFFUL           /*!< ADC channel delay value */

//Cluster SEQ:
typedef struct {
  union {
  /*!< Sequencer request ADC channels selection register 0 */
    __IO uint32_t SRQSEL;                                            /*!< SRQSEL : type used for word access */
    __IO _ADC_SEQ_SRQSEL_bits SRQSEL_bit;                            /*!< SRQSEL_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0[5];
  union {
  /*!< Sequencer request control register */
    __IO uint32_t SRQCTL;                                            /*!< SRQCTL : type used for word access */
    __IO _ADC_SEQ_SRQCTL_bits SRQCTL_bit;                            /*!< SRQCTL_bit: structure used for bit access */
  };
  union {
  /*!< Sequencer request status register */
    __I uint32_t SRQSTAT;                                            /*!< SRQSTAT : type used for word access */
    __I _ADC_SEQ_SRQSTAT_bits SRQSTAT_bit;                           /*!< SRQSTAT_bit: structure used for bit access */
  };
  union {
  /*!< Sequencer DMA control register */
    __IO uint32_t SDMACTL;                                           /*!< SDMACTL : type used for word access */
    __IO _ADC_SEQ_SDMACTL_bits SDMACTL_bit;                          /*!< SDMACTL_bit: structure used for bit access */
  };
  union {
  /*!< Sequencer ADC interrupt and restart counter control register */
    __IO uint32_t SCCTL;                                             /*!< SCCTL : type used for word access */
    __IO _ADC_SEQ_SCCTL_bits SCCTL_bit;                              /*!< SCCTL_bit: structure used for bit access */
  };
  union {
  /*!< Sequencer ADC interrupt and restart counter current value register */
    __O uint32_t SCVAL;                                              /*!< SCVAL : type used for word access */
    __O _ADC_SEQ_SCVAL_bits SCVAL_bit;                               /*!< SCVAL_bit: structure used for bit access */
  };
  union {
  /*!< Sequencer digital comparator selection register */
    __IO uint32_t SDC;                                               /*!< SDC : type used for word access */
    __IO _ADC_SEQ_SDC_bits SDC_bit;                                  /*!< SDC_bit: structure used for bit access */
  };
  union {
  /*!< Sequencer ADC restart timer register */
    __IO uint32_t SRTMR;                                             /*!< SRTMR : type used for word access */
    __IO _ADC_SEQ_SRTMR_bits SRTMR_bit;                              /*!< SRTMR_bit: structure used for bit access */
  };
  union {
  /*!< Sequencer FIFO load status register */
    __I uint32_t SFLOAD;                                             /*!< SFLOAD : type used for word access */
    __I _ADC_SEQ_SFLOAD_bits SFLOAD_bit;                             /*!< SFLOAD_bit: structure used for bit access */
  };
  union {
  /*!< Sequencer FIFO register */
    __I uint32_t SFIFO;                                              /*!< SFIFO : type used for word access */
    __I _ADC_SEQ_SFIFO_bits SFIFO_bit;                               /*!< SFIFO_bit: structure used for bit access */
  };
} _ADC_SEQ_TypeDef;
//Cluster DC:
typedef struct {
  union {
  /*!< Digital comparator control register */
    __IO uint32_t DCTL;                                              /*!< DCTL : type used for word access */
    __IO _ADC_DC_DCTL_bits DCTL_bit;                                 /*!< DCTL_bit: structure used for bit access */
  };
  union {
  /*!< Digital comparator range register */
    __IO uint32_t DCMP;                                              /*!< DCMP : type used for word access */
    __IO _ADC_DC_DCMP_bits DCMP_bit;                                 /*!< DCMP_bit: structure used for bit access */
  };
  union {
  /*!< Digital comparator last compared data register */
    __I uint32_t DDATA;                                              /*!< DDATA : type used for word access */
    __I _ADC_DC_DDATA_bits DDATA_bit;                                /*!< DDATA_bit: structure used for bit access */
  };
} _ADC_DC_TypeDef;
//Cluster CHCTL:
typedef struct {
  union {
  /*!< ADC channel control register */
    __IO uint32_t CHCTL;                                             /*!< CHCTL : type used for word access */
    __IO _ADC_CHCTL_bits CHCTL_bit;                                  /*!< CHCTL_bit: structure used for bit access */
  };
} _ADC_CHCTL_TypeDef;
//Cluster CHDELAY:
typedef struct {
  union {
  /*!< ADC channel delay register */
    __IO uint32_t CHDELAY;                                           /*!< CHDELAY : type used for word access */
    __IO _ADC_CHDELAY_bits CHDELAY_bit;                              /*!< CHDELAY_bit: structure used for bit access */
  };
} _ADC_CHDELAY_TypeDef;
typedef struct {
  union {                                                            /*!< Enable sequencer register */
    __IO uint32_t SEQEN;                                             /*!< SEQEN    : type used for word access */
    __IO _ADC_SEQEN_bits  SEQEN_bit;                                 /*!< SEQEN_bit: structure used for bit access */
  };
  union {                                                            /*!< Sequencer sync register */
    __IO uint32_t SEQSYNC;                                           /*!< SEQSYNC    : type used for word access */
    __IO _ADC_SEQSYNC_bits  SEQSYNC_bit;                             /*!< SEQSYNC_bit: structure used for bit access */
  };
  union {                                                            /*!< FIFO overflow status register */
    __IO uint32_t FSTAT;                                             /*!< FSTAT    : type used for word access */
    __IO _ADC_FSTAT_bits  FSTAT_bit;                                 /*!< FSTAT_bit: structure used for bit access */
  };
  union {                                                            /*!< Busy status register */
    __I uint32_t BSTAT;                                              /*!< BSTAT    : type used for word access */
    __I _ADC_BSTAT_bits  BSTAT_bit;                                  /*!< BSTAT_bit: structure used for bit access */
  };
  union {                                                            /*!< Digital comparator output trigger status register */
    __O uint32_t DCTRIG;                                             /*!< DCTRIG    : type used for word access */
    __O _ADC_DCTRIG_bits  DCTRIG_bit;                                /*!< DCTRIG_bit: structure used for bit access */
  };
  union {                                                            /*!< Digital comparator compare event status register */
    __O uint32_t DCEV;                                               /*!< DCEV    : type used for word access */
    __O _ADC_DCEV_bits  DCEV_bit;                                    /*!< DCEV_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt counter clear control */
    __IO uint32_t CICNT;                                             /*!< CICNT    : type used for word access */
    __IO _ADC_CICNT_bits  CICNT_bit;                                 /*!< CICNT_bit: structure used for bit access */
  };
  union {                                                            /*!< Sequencer start event selection register */
    __IO uint32_t EMUX;                                              /*!< EMUX    : type used for word access */
    __IO _ADC_EMUX_bits  EMUX_bit;                                   /*!< EMUX_bit: structure used for bit access */
  };
  union {                                                            /*!< Raw interrupt status register */
    __I uint32_t RIS;                                                /*!< RIS    : type used for word access */
    __I _ADC_RIS_bits  RIS_bit;                                      /*!< RIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt mask register */
    __IO uint32_t IM;                                                /*!< IM    : type used for word access */
    __IO _ADC_IM_bits  IM_bit;                                       /*!< IM_bit: structure used for bit access */
  };
  union {                                                            /*!< Masked interrupt status and clear register */
    __I uint32_t MIS;                                                /*!< MIS    : type used for word access */
    __I _ADC_MIS_bits  MIS_bit;                                      /*!< MIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt clear register */
    __O uint32_t IC;                                                 /*!< IC    : type used for word access */
    __O _ADC_IC_bits  IC_bit;                                        /*!< IC_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0[4];
  _ADC_SEQ_TypeDef SEQ[4];
    __IO uint32_t Reserved1[180];
  _ADC_DC_TypeDef DC[8];
    __IO uint32_t Reserved2[56];
  union {                                                            /*!< ADC module control register */
    __IO uint32_t ACTL;                                              /*!< ACTL    : type used for word access */
    __IO _ADC_ACTL_bits  ACTL_bit;                                   /*!< ACTL_bit: structure used for bit access */
  };
  union {                                                            /*!< ADC test access register */
    __IO uint32_t TACC0;                                             /*!< TACC0    : type used for word access */
    __IO _ADC_TACC0_bits  TACC0_bit;                                 /*!< TACC0_bit: structure used for bit access */
  };
  union {                                                            /*!< ADC test access register */
    __IO uint32_t TACC1;                                             /*!< TACC1    : type used for word access */
    __IO _ADC_TACC1_bits  TACC1_bit;                                 /*!< TACC1_bit: structure used for bit access */
  };
    __IO uint32_t Reserved3[13];
  _ADC_CHCTL_TypeDef CHCTL[9];
    __IO uint32_t Reserved4[55];
  _ADC_CHDELAY_TypeDef CHDELAY[9];
} ADC_TypeDef;


/******************************************************************************/
/*                         CAN registers                                      */
/******************************************************************************/

/*--  CLC: Frequency control register -------------------------------------------------------------------------*/
typedef struct {
  uint32_t DISR                   :1;                                /*!< OFF module CAN */
  uint32_t DISS                   :1;                                /*!< State CAN */
} _CAN_CLC_bits;

/* Bit field positions: */
#define CAN_CLC_DISR_Pos                      0                      /*!< OFF module CAN */
#define CAN_CLC_DISS_Pos                      1                      /*!< State CAN */

/* Bit field masks: */
#define CAN_CLC_DISR_Msk                      0x00000001UL           /*!< OFF module CAN */
#define CAN_CLC_DISS_Msk                      0x00000002UL           /*!< State CAN */

/*--  ID: Identity register -----------------------------------------------------------------------------------*/
typedef struct {
  uint32_t MODREV                 :8;                                /*!< Number of modifications of the CAN */
  uint32_t MODTYPE                :8;                                /*!< Digit capacity CAN */
  uint32_t MODNUM                 :16;                               /*!< Identification number CAN */
} _CAN_ID_bits;

/* Bit field positions: */
#define CAN_ID_MODREV_Pos                     0                      /*!< Number of modifications of the CAN */
#define CAN_ID_MODTYPE_Pos                    8                      /*!< Digit capacity CAN */
#define CAN_ID_MODNUM_Pos                     16                     /*!< Identification number CAN */

/* Bit field masks: */
#define CAN_ID_MODREV_Msk                     0x000000FFUL           /*!< Number of modifications of the CAN */
#define CAN_ID_MODTYPE_Msk                    0x0000FF00UL           /*!< Digit capacity CAN */
#define CAN_ID_MODNUM_Msk                     0xFFFF0000UL           /*!< Identification number CAN */

/*--  FDR: Register divider -----------------------------------------------------------------------------------*/
typedef struct {
  uint32_t STEP                   :10;                               /*!< Step divider */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t DM                     :2;                                /*!< Mode setting of the frequency divider */
  uint32_t RESULT                 :10;                               /*!< Count frequency divider */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t ENHW                   :1;                                /*!< Control bit synchronization */
  uint32_t DISCLK                 :1;                                /*!< Disable bit internal clock */
} _CAN_FDR_bits;

/* Bit field positions: */
#define CAN_FDR_STEP_Pos                      0                      /*!< Step divider */
#define CAN_FDR_DM_Pos                        14                     /*!< Mode setting of the frequency divider */
#define CAN_FDR_RESULT_Pos                    16                     /*!< Count frequency divider */
#define CAN_FDR_ENHW_Pos                      30                     /*!< Control bit synchronization */
#define CAN_FDR_DISCLK_Pos                    31                     /*!< Disable bit internal clock */

/* Bit field masks: */
#define CAN_FDR_STEP_Msk                      0x000003FFUL           /*!< Step divider */
#define CAN_FDR_DM_Msk                        0x0000C000UL           /*!< Mode setting of the frequency divider */
#define CAN_FDR_RESULT_Msk                    0x03FF0000UL           /*!< Count frequency divider */
#define CAN_FDR_ENHW_Msk                      0x40000000UL           /*!< Control bit synchronization */
#define CAN_FDR_DISCLK_Msk                    0x80000000UL           /*!< Disable bit internal clock */

/* Bit field enums: */
typedef enum {
  CAN_FDR_DM_Disable                         = 0x0UL,                /*!< counter disabled */
  CAN_FDR_DM_NormalMode                      = 0x1UL,                /*!< normal operation mode */
  CAN_FDR_DM_DividerMode                     = 0x2UL,                /*!< divider operation mode */
} CAN_FDR_DM_Enum;

/*--  LIST: Register list0 ------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t BEGIN                  :8;                                /*!< Number of the first message object */
  uint32_t END                    :8;                                /*!< Number of the last message object */
  uint32_t SIZE                   :8;                                /*!< List size */
  uint32_t EMPTY                  :1;                                /*!< Indicate empty list */
} _CAN_LIST_bits;

/* Bit field positions: */
#define CAN_LIST_BEGIN_Pos                    0                      /*!< Number of the first message object */
#define CAN_LIST_END_Pos                      8                      /*!< Number of the last message object */
#define CAN_LIST_SIZE_Pos                     16                     /*!< List size */
#define CAN_LIST_EMPTY_Pos                    24                     /*!< Indicate empty list */

/* Bit field masks: */
#define CAN_LIST_BEGIN_Msk                    0x000000FFUL           /*!< Number of the first message object */
#define CAN_LIST_END_Msk                      0x0000FF00UL           /*!< Number of the last message object */
#define CAN_LIST_SIZE_Msk                     0x00FF0000UL           /*!< List size */
#define CAN_LIST_EMPTY_Msk                    0x01000000UL           /*!< Indicate empty list */

/*--  MSPND: Register waiting interrupts0 ---------------------------------------------------------------------*/
typedef struct {
  uint32_t PND                    :32;                               /*!< Field waiting interrupts */
} _CAN_MSPND_bits;

/* Bit field positions: */
#define CAN_MSPND_PND_Pos                     0                      /*!< Field waiting interrupts */

/* Bit field masks: */
#define CAN_MSPND_PND_Msk                     0xFFFFFFFFUL           /*!< Field waiting interrupts */

/*--  MSID: Register messages index0 --------------------------------------------------------------------------*/
typedef struct {
  uint32_t INDEX                  :6;                                /*!<  */
} _CAN_MSID_bits;

/* Bit field positions: */
#define CAN_MSID_INDEX_Pos                    0                      /*!<  */

/* Bit field masks: */
#define CAN_MSID_INDEX_Msk                    0x0000003FUL           /*!<  */

/*--  MSIMASK: Mask register message index --------------------------------------------------------------------*/
typedef struct {
  uint32_t IM                     :32;                               /*!< Mask for waiting bit messages */
} _CAN_MSIMASK_bits;

/* Bit field positions: */
#define CAN_MSIMASK_IM_Pos                    0                      /*!< Mask for waiting bit messages */

/* Bit field masks: */
#define CAN_MSIMASK_IM_Msk                    0xFFFFFFFFUL           /*!< Mask for waiting bit messages */

/*--  PANCTR: Register command panel --------------------------------------------------------------------------*/
typedef struct {
  uint32_t PANCMD                 :8;                                /*!< Command panel */
  uint32_t BUSY                   :1;                                /*!< Busy flag panels arguments (waiting to be written at the end of the command) */
  uint32_t RBUSY                  :1;                                /*!< Busy flag panels arguments (running the command list, the result of which will be recorded in PANAR1 and PANAR2) */
  uint32_t                        :6;                                /*!< RESERVED */
  uint32_t PANAR1                 :8;                                /*!< Panel argument 8 */
  uint32_t PANAR2                 :8;                                /*!< Panel argument 9 */
} _CAN_PANCTR_bits;

/* Bit field positions: */
#define CAN_PANCTR_PANCMD_Pos                 0                      /*!< Command panel */
#define CAN_PANCTR_BUSY_Pos                   8                      /*!< Busy flag panels arguments (waiting to be written at the end of the command) */
#define CAN_PANCTR_RBUSY_Pos                  9                      /*!< Busy flag panels arguments (running the command list, the result of which will be recorded in PANAR1 and PANAR2) */
#define CAN_PANCTR_PANAR1_Pos                 16                     /*!< Panel argument 8 */
#define CAN_PANCTR_PANAR2_Pos                 24                     /*!< Panel argument 9 */

/* Bit field masks: */
#define CAN_PANCTR_PANCMD_Msk                 0x000000FFUL           /*!< Command panel */
#define CAN_PANCTR_BUSY_Msk                   0x00000100UL           /*!< Busy flag panels arguments (waiting to be written at the end of the command) */
#define CAN_PANCTR_RBUSY_Msk                  0x00000200UL           /*!< Busy flag panels arguments (running the command list, the result of which will be recorded in PANAR1 and PANAR2) */
#define CAN_PANCTR_PANAR1_Msk                 0x00FF0000UL           /*!< Panel argument 8 */
#define CAN_PANCTR_PANAR2_Msk                 0xFF000000UL           /*!< Panel argument 9 */

/*--  MCR: Control register -----------------------------------------------------------------------------------*/
typedef struct {
  uint32_t                        :12;                               /*!< RESERVED */
  uint32_t MPSEL                  :4;                                /*!< Field task position after waiting message bit transmit / receive messages */
} _CAN_MCR_bits;

/* Bit field positions: */
#define CAN_MCR_MPSEL_Pos                     12                     /*!< Field task position after waiting message bit transmit / receive messages */

/* Bit field masks: */
#define CAN_MCR_MPSEL_Msk                     0x0000F000UL           /*!< Field task position after waiting message bit transmit / receive messages */

/*--  MITR: Interrupt register --------------------------------------------------------------------------------*/
typedef struct {
  uint32_t IT                     :16;                               /*!< Field  generate interrupt */
} _CAN_MITR_bits;

/* Bit field positions: */
#define CAN_MITR_IT_Pos                       0                      /*!< Field  generate interrupt */

/* Bit field masks: */
#define CAN_MITR_IT_Msk                       0x0000FFFFUL           /*!< Field  generate interrupt */

/*-- Node: NCR: Register control node0 ------------------------------------------------------------------------*/
typedef struct {
  uint32_t INIT                   :1;                                /*!< Node initialization */
  uint32_t TRIE                   :1;                                /*!< Interrupt enable bit of the assembly at the end of the transmission / reception */
  uint32_t LECIE                  :1;                                /*!< Interrupt enable bit of the assembly when it detects the last error code */
  uint32_t ALIE                   :1;                                /*!< Enable interrupt ALERT from node */
  uint32_t CANDIS                 :1;                                /*!< Off node */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t CCE                    :1;                                /*!< Permission node configuration changes */
  uint32_t CALM                   :1;                                /*!< Activate the node analysis */
} _CAN_Node_NCR_bits;

/* Bit field positions: */
#define CAN_Node_NCR_INIT_Pos                 0                      /*!< Node initialization */
#define CAN_Node_NCR_TRIE_Pos                 1                      /*!< Interrupt enable bit of the assembly at the end of the transmission / reception */
#define CAN_Node_NCR_LECIE_Pos                2                      /*!< Interrupt enable bit of the assembly when it detects the last error code */
#define CAN_Node_NCR_ALIE_Pos                 3                      /*!< Enable interrupt ALERT from node */
#define CAN_Node_NCR_CANDIS_Pos               4                      /*!< Off node */
#define CAN_Node_NCR_CCE_Pos                  6                      /*!< Permission node configuration changes */
#define CAN_Node_NCR_CALM_Pos                 7                      /*!< Activate the node analysis */

/* Bit field masks: */
#define CAN_Node_NCR_INIT_Msk                 0x00000001UL           /*!< Node initialization */
#define CAN_Node_NCR_TRIE_Msk                 0x00000002UL           /*!< Interrupt enable bit of the assembly at the end of the transmission / reception */
#define CAN_Node_NCR_LECIE_Msk                0x00000004UL           /*!< Interrupt enable bit of the assembly when it detects the last error code */
#define CAN_Node_NCR_ALIE_Msk                 0x00000008UL           /*!< Enable interrupt ALERT from node */
#define CAN_Node_NCR_CANDIS_Msk               0x00000010UL           /*!< Off node */
#define CAN_Node_NCR_CCE_Msk                  0x00000040UL           /*!< Permission node configuration changes */
#define CAN_Node_NCR_CALM_Msk                 0x00000080UL           /*!< Activate the node analysis */

/*-- Node: NSR: Register state node0 --------------------------------------------------------------------------*/
typedef struct {
  uint32_t LEC                    :3;                                /*!< Last error code */
  uint32_t TXOK                   :1;                                /*!< Flag successful message transmission */
  uint32_t RXOK                   :1;                                /*!< Flag successful reception of messages */
  uint32_t ALERT                  :1;                                /*!< Warning flag ALERT */
  uint32_t EWRN                   :1;                                /*!< Flag critical errors */
  uint32_t BOFF                   :1;                                /*!< Status flag 'is disconnected from the bus' */
  uint32_t LLE                    :1;                                /*!< Error flag list */
  uint32_t LOE                    :1;                                /*!< Error Flag Room list */
} _CAN_Node_NSR_bits;

/* Bit field positions: */
#define CAN_Node_NSR_LEC_Pos                  0                      /*!< Last error code */
#define CAN_Node_NSR_TXOK_Pos                 3                      /*!< Flag successful message transmission */
#define CAN_Node_NSR_RXOK_Pos                 4                      /*!< Flag successful reception of messages */
#define CAN_Node_NSR_ALERT_Pos                5                      /*!< Warning flag ALERT */
#define CAN_Node_NSR_EWRN_Pos                 6                      /*!< Flag critical errors */
#define CAN_Node_NSR_BOFF_Pos                 7                      /*!< Status flag 'is disconnected from the bus' */
#define CAN_Node_NSR_LLE_Pos                  8                      /*!< Error flag list */
#define CAN_Node_NSR_LOE_Pos                  9                      /*!< Error Flag Room list */

/* Bit field masks: */
#define CAN_Node_NSR_LEC_Msk                  0x00000007UL           /*!< Last error code */
#define CAN_Node_NSR_TXOK_Msk                 0x00000008UL           /*!< Flag successful message transmission */
#define CAN_Node_NSR_RXOK_Msk                 0x00000010UL           /*!< Flag successful reception of messages */
#define CAN_Node_NSR_ALERT_Msk                0x00000020UL           /*!< Warning flag ALERT */
#define CAN_Node_NSR_EWRN_Msk                 0x00000040UL           /*!< Flag critical errors */
#define CAN_Node_NSR_BOFF_Msk                 0x00000080UL           /*!< Status flag 'is disconnected from the bus' */
#define CAN_Node_NSR_LLE_Msk                  0x00000100UL           /*!< Error flag list */
#define CAN_Node_NSR_LOE_Msk                  0x00000200UL           /*!< Error Flag Room list */

/* Bit field enums: */
typedef enum {
  CAN_Node_NSR_LEC_NoErr                     = 0x0UL,                /*!< no error */
  CAN_Node_NSR_LEC_StuffErr                  = 0x1UL,                /*!< stuff error */
  CAN_Node_NSR_LEC_FormErr                   = 0x2UL,                /*!< form error */
  CAN_Node_NSR_LEC_AckErr                    = 0x3UL,                /*!< acknowlegment error */
  CAN_Node_NSR_LEC_Bit1Err                   = 0x4UL,                /*!< bit 1 error */
  CAN_Node_NSR_LEC_Bit0Err                   = 0x5UL,                /*!< bit 0 error */
  CAN_Node_NSR_LEC_CRCErr                    = 0x6UL,                /*!< CRC error */
  CAN_Node_NSR_LEC_WriteEn                   = 0x7UL,                /*!< enable hardware write */
} CAN_Node_NSR_LEC_Enum;

/*-- Node: NIPR: Interrupt pointer register node0 -------------------------------------------------------------*/
typedef struct {
  uint32_t ALINP                  :4;                                /*!<  */
  uint32_t LECINP                 :4;                                /*!<  */
  uint32_t TRINP                  :4;                                /*!<  */
  uint32_t CFCINP                 :4;                                /*!<  */
} _CAN_Node_NIPR_bits;

/* Bit field positions: */
#define CAN_Node_NIPR_ALINP_Pos               0                      /*!<  */
#define CAN_Node_NIPR_LECINP_Pos              4                      /*!<  */
#define CAN_Node_NIPR_TRINP_Pos               8                      /*!<  */
#define CAN_Node_NIPR_CFCINP_Pos              12                     /*!<  */

/* Bit field masks: */
#define CAN_Node_NIPR_ALINP_Msk               0x0000000FUL           /*!<  */
#define CAN_Node_NIPR_LECINP_Msk              0x000000F0UL           /*!<  */
#define CAN_Node_NIPR_TRINP_Msk               0x00000F00UL           /*!<  */
#define CAN_Node_NIPR_CFCINP_Msk              0x0000F000UL           /*!<  */

/*-- Node: NPCR: Port control register node0 ------------------------------------------------------------------*/
typedef struct {
  uint32_t                        :8;                                /*!< RESERVED */
  uint32_t LBM                    :1;                                /*!< Enable mode Loop-Back */
} _CAN_Node_NPCR_bits;

/* Bit field positions: */
#define CAN_Node_NPCR_LBM_Pos                 8                      /*!< Enable mode Loop-Back */

/* Bit field masks: */
#define CAN_Node_NPCR_LBM_Msk                 0x00000100UL           /*!< Enable mode Loop-Back */

/*-- Node: NBTR: Timing register bits 0 -----------------------------------------------------------------------*/
typedef struct {
  uint32_t BRP                    :6;                                /*!< Prescaler rate */
  uint32_t SJW                    :2;                                /*!< Transition width resynchronization */
  uint32_t TSEG1                  :4;                                /*!< Parameter 1 */
  uint32_t TSEG2                  :3;                                /*!< Parameter 2 */
  uint32_t DIV8                   :1;                                /*!< Frequency divider by 8 */
} _CAN_Node_NBTR_bits;

/* Bit field positions: */
#define CAN_Node_NBTR_BRP_Pos                 0                      /*!< Prescaler rate */
#define CAN_Node_NBTR_SJW_Pos                 6                      /*!< Transition width resynchronization */
#define CAN_Node_NBTR_TSEG1_Pos               8                      /*!< Parameter 1 */
#define CAN_Node_NBTR_TSEG2_Pos               12                     /*!< Parameter 2 */
#define CAN_Node_NBTR_DIV8_Pos                15                     /*!< Frequency divider by 8 */

/* Bit field masks: */
#define CAN_Node_NBTR_BRP_Msk                 0x0000003FUL           /*!< Prescaler rate */
#define CAN_Node_NBTR_SJW_Msk                 0x000000C0UL           /*!< Transition width resynchronization */
#define CAN_Node_NBTR_TSEG1_Msk               0x00000F00UL           /*!< Parameter 1 */
#define CAN_Node_NBTR_TSEG2_Msk               0x00007000UL           /*!< Parameter 2 */
#define CAN_Node_NBTR_DIV8_Msk                0x00008000UL           /*!< Frequency divider by 8 */

/*-- Node: NECNT: Counter error register node0 ----------------------------------------------------------------*/
typedef struct {
  uint32_t REC                    :8;                                /*!< Receive Error Counter field messages */
  uint32_t TEC                    :8;                                /*!< Counter field messaging error */
  uint32_t EWRNLVL                :8;                                /*!< Error limit at which a flag is set in the register EWRN NSR */
  uint32_t LETD                   :1;                                /*!< Flag last transmission errors */
  uint32_t LEINC                  :1;                                /*!< Indicator increment at the last error */
} _CAN_Node_NECNT_bits;

/* Bit field positions: */
#define CAN_Node_NECNT_REC_Pos                0                      /*!< Receive Error Counter field messages */
#define CAN_Node_NECNT_TEC_Pos                8                      /*!< Counter field messaging error */
#define CAN_Node_NECNT_EWRNLVL_Pos            16                     /*!< Error limit at which a flag is set in the register EWRN NSR */
#define CAN_Node_NECNT_LETD_Pos               24                     /*!< Flag last transmission errors */
#define CAN_Node_NECNT_LEINC_Pos              25                     /*!< Indicator increment at the last error */

/* Bit field masks: */
#define CAN_Node_NECNT_REC_Msk                0x000000FFUL           /*!< Receive Error Counter field messages */
#define CAN_Node_NECNT_TEC_Msk                0x0000FF00UL           /*!< Counter field messaging error */
#define CAN_Node_NECNT_EWRNLVL_Msk            0x00FF0000UL           /*!< Error limit at which a flag is set in the register EWRN NSR */
#define CAN_Node_NECNT_LETD_Msk               0x01000000UL           /*!< Flag last transmission errors */
#define CAN_Node_NECNT_LEINC_Msk              0x02000000UL           /*!< Indicator increment at the last error */

/*-- Node: NFCR: Register message counter node0 ---------------------------------------------------------------*/
typedef struct {
  uint32_t CFC                    :16;                               /*!< Field of the message counter  */
  uint32_t CFSEL                  :3;                                /*!< Field parameter setting mode selected message counter */
  uint32_t CFMOD                  :2;                                /*!< Field task mode message counter */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t CFCIE                  :1;                                /*!< Interrupt enable bit of the message counter */
  uint32_t CFCOV                  :1;                                /*!< Counter overflow flag messages */
} _CAN_Node_NFCR_bits;

/* Bit field positions: */
#define CAN_Node_NFCR_CFC_Pos                 0                      /*!< Field of the message counter  */
#define CAN_Node_NFCR_CFSEL_Pos               16                     /*!< Field parameter setting mode selected message counter */
#define CAN_Node_NFCR_CFMOD_Pos               19                     /*!< Field task mode message counter */
#define CAN_Node_NFCR_CFCIE_Pos               22                     /*!< Interrupt enable bit of the message counter */
#define CAN_Node_NFCR_CFCOV_Pos               23                     /*!< Counter overflow flag messages */

/* Bit field masks: */
#define CAN_Node_NFCR_CFC_Msk                 0x0000FFFFUL           /*!< Field of the message counter  */
#define CAN_Node_NFCR_CFSEL_Msk               0x00070000UL           /*!< Field parameter setting mode selected message counter */
#define CAN_Node_NFCR_CFMOD_Msk               0x00180000UL           /*!< Field task mode message counter */
#define CAN_Node_NFCR_CFCIE_Msk               0x00400000UL           /*!< Interrupt enable bit of the message counter */
#define CAN_Node_NFCR_CFCOV_Msk               0x00800000UL           /*!< Counter overflow flag messages */

//Cluster LIST:
typedef struct {
  union {
  /*!< Register list0 */
    __I uint32_t LIST;                                               /*!< LIST : type used for word access */
    __I _CAN_LIST_bits LIST_bit;                                     /*!< LIST_bit: structure used for bit access */
  };
} _CAN_LIST_TypeDef;
//Cluster MSPND:
typedef struct {
  union {
  /*!< Register waiting interrupts0 */
    __IO uint32_t MSPND;                                             /*!< MSPND : type used for word access */
    __IO _CAN_MSPND_bits MSPND_bit;                                  /*!< MSPND_bit: structure used for bit access */
  };
} _CAN_MSPND_TypeDef;
//Cluster MSID:
typedef struct {
  union {
  /*!< Register messages index0 */
    __I uint32_t MSID;                                               /*!< MSID : type used for word access */
    __I _CAN_MSID_bits MSID_bit;                                     /*!< MSID_bit: structure used for bit access */
  };
} _CAN_MSID_TypeDef;
//Cluster Node:
typedef struct {
  union {
  /*!< Register control node0 */
    __IO uint32_t NCR;                                               /*!< NCR : type used for word access */
    __IO _CAN_Node_NCR_bits NCR_bit;                                 /*!< NCR_bit: structure used for bit access */
  };
  union {
  /*!< Register state node0 */
    __IO uint32_t NSR;                                               /*!< NSR : type used for word access */
    __IO _CAN_Node_NSR_bits NSR_bit;                                 /*!< NSR_bit: structure used for bit access */
  };
  union {
  /*!< Interrupt pointer register node0 */
    __IO uint32_t NIPR;                                              /*!< NIPR : type used for word access */
    __IO _CAN_Node_NIPR_bits NIPR_bit;                               /*!< NIPR_bit: structure used for bit access */
  };
  union {
  /*!< Port control register node0 */
    __IO uint32_t NPCR;                                              /*!< NPCR : type used for word access */
    __IO _CAN_Node_NPCR_bits NPCR_bit;                               /*!< NPCR_bit: structure used for bit access */
  };
  union {
  /*!< Timing register bits 0 */
    __IO uint32_t NBTR;                                              /*!< NBTR : type used for word access */
    __IO _CAN_Node_NBTR_bits NBTR_bit;                               /*!< NBTR_bit: structure used for bit access */
  };
  union {
  /*!< Counter error register node0 */
    __IO uint32_t NECNT;                                             /*!< NECNT : type used for word access */
    __IO _CAN_Node_NECNT_bits NECNT_bit;                             /*!< NECNT_bit: structure used for bit access */
  };
  union {
  /*!< Register message counter node0 */
    __IO uint32_t NFCR;                                              /*!< NFCR : type used for word access */
    __IO _CAN_Node_NFCR_bits NFCR_bit;                               /*!< NFCR_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0[57];
} _CAN_Node_TypeDef;
typedef struct {
  union {                                                            /*!< Frequency control register */
    __IO uint32_t CLC;                                               /*!< CLC    : type used for word access */
    __IO _CAN_CLC_bits  CLC_bit;                                     /*!< CLC_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0;
  union {                                                            /*!< Identity register */
    __IO uint32_t ID;                                                /*!< ID    : type used for word access */
    __IO _CAN_ID_bits  ID_bit;                                       /*!< ID_bit: structure used for bit access */
  };
  union {                                                            /*!< Register divider */
    __IO uint32_t FDR;                                               /*!< FDR    : type used for word access */
    __IO _CAN_FDR_bits  FDR_bit;                                     /*!< FDR_bit: structure used for bit access */
  };
    __IO uint32_t Reserved1[60];
  _CAN_LIST_TypeDef LIST[8];
    __IO uint32_t Reserved2[8];
  _CAN_MSPND_TypeDef MSPND[8];
    __IO uint32_t Reserved3[8];
  _CAN_MSID_TypeDef MSID[8];
    __IO uint32_t Reserved4[8];
  union {                                                            /*!< Mask register message index */
    __IO uint32_t MSIMASK;                                           /*!< MSIMASK    : type used for word access */
    __IO _CAN_MSIMASK_bits  MSIMASK_bit;                             /*!< MSIMASK_bit: structure used for bit access */
  };
  union {                                                            /*!< Register command panel */
    __IO uint32_t PANCTR;                                            /*!< PANCTR    : type used for word access */
    __IO _CAN_PANCTR_bits  PANCTR_bit;                               /*!< PANCTR_bit: structure used for bit access */
  };
  union {                                                            /*!< Control register */
    __IO uint32_t MCR;                                               /*!< MCR    : type used for word access */
    __IO _CAN_MCR_bits  MCR_bit;                                     /*!< MCR_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt register */
    __O uint32_t MITR;                                               /*!< MITR    : type used for word access */
    __O _CAN_MITR_bits  MITR_bit;                                    /*!< MITR_bit: structure used for bit access */
  };
    __IO uint32_t Reserved5[12];
  _CAN_Node_TypeDef Node[2];
} CAN_TypeDef;


/******************************************************************************/
/*                         CANMSG registers                                   */
/******************************************************************************/

/*-- Msg: MOFCR: Register control the operation of the message object 0 ---------------------------------------*/
typedef struct {
  uint32_t MMC                    :4;                                /*!<  */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t GDFS                   :1;                                /*!<  */
  uint32_t IDC                    :1;                                /*!<  */
  uint32_t DLCC                   :1;                                /*!<  */
  uint32_t DATC                   :1;                                /*!<  */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t RXIE                   :1;                                /*!< Interrupt enable after taking the messages */
  uint32_t TXIE                   :1;                                /*!< Interrupt enable at the end of the message */
  uint32_t OVIE                   :1;                                /*!< Interrupt enable FIFO to fill the message object 0 */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t FRREN                  :1;                                /*!< Enable remote request */
  uint32_t RMM                    :1;                                /*!< Enable remote monitoring of the communication object */
  uint32_t SDT                    :1;                                /*!< Bit single of the message object 0 participation in shipment */
  uint32_t STT                    :1;                                /*!< Bit single data transfer */
  uint32_t DLC                    :4;                                /*!< Data length code */
} _CANMSG_Msg_MOFCR_bits;

/* Bit field positions: */
#define CANMSG_Msg_MOFCR_MMC_Pos              0                      /*!<  */
#define CANMSG_Msg_MOFCR_GDFS_Pos             8                      /*!<  */
#define CANMSG_Msg_MOFCR_IDC_Pos              9                      /*!<  */
#define CANMSG_Msg_MOFCR_DLCC_Pos             10                     /*!<  */
#define CANMSG_Msg_MOFCR_DATC_Pos             11                     /*!<  */
#define CANMSG_Msg_MOFCR_RXIE_Pos             16                     /*!< Interrupt enable after taking the messages */
#define CANMSG_Msg_MOFCR_TXIE_Pos             17                     /*!< Interrupt enable at the end of the message */
#define CANMSG_Msg_MOFCR_OVIE_Pos             18                     /*!< Interrupt enable FIFO to fill the message object 0 */
#define CANMSG_Msg_MOFCR_FRREN_Pos            20                     /*!< Enable remote request */
#define CANMSG_Msg_MOFCR_RMM_Pos              21                     /*!< Enable remote monitoring of the communication object */
#define CANMSG_Msg_MOFCR_SDT_Pos              22                     /*!< Bit single of the message object 0 participation in shipment */
#define CANMSG_Msg_MOFCR_STT_Pos              23                     /*!< Bit single data transfer */
#define CANMSG_Msg_MOFCR_DLC_Pos              24                     /*!< Data length code */

/* Bit field masks: */
#define CANMSG_Msg_MOFCR_MMC_Msk              0x0000000FUL           /*!<  */
#define CANMSG_Msg_MOFCR_GDFS_Msk             0x00000100UL           /*!<  */
#define CANMSG_Msg_MOFCR_IDC_Msk              0x00000200UL           /*!<  */
#define CANMSG_Msg_MOFCR_DLCC_Msk             0x00000400UL           /*!<  */
#define CANMSG_Msg_MOFCR_DATC_Msk             0x00000800UL           /*!<  */
#define CANMSG_Msg_MOFCR_RXIE_Msk             0x00010000UL           /*!< Interrupt enable after taking the messages */
#define CANMSG_Msg_MOFCR_TXIE_Msk             0x00020000UL           /*!< Interrupt enable at the end of the message */
#define CANMSG_Msg_MOFCR_OVIE_Msk             0x00040000UL           /*!< Interrupt enable FIFO to fill the message object 0 */
#define CANMSG_Msg_MOFCR_FRREN_Msk            0x00100000UL           /*!< Enable remote request */
#define CANMSG_Msg_MOFCR_RMM_Msk              0x00200000UL           /*!< Enable remote monitoring of the communication object */
#define CANMSG_Msg_MOFCR_SDT_Msk              0x00400000UL           /*!< Bit single of the message object 0 participation in shipment */
#define CANMSG_Msg_MOFCR_STT_Msk              0x00800000UL           /*!< Bit single data transfer */
#define CANMSG_Msg_MOFCR_DLC_Msk              0x0F000000UL           /*!< Data length code */

/* Bit field enums: */
typedef enum {
  CANMSG_Msg_MOFCR_MMC_MsgObj                = 0x0UL,                /*!< message object */
  CANMSG_Msg_MOFCR_MMC_RXObj                 = 0x1UL,                /*!< receiver FIFO structure object */
  CANMSG_Msg_MOFCR_MMC_TXObj                 = 0x2UL,                /*!< transmitter FIFO structure object */
  CANMSG_Msg_MOFCR_MMC_SlaveTXObj            = 0x3UL,                /*!< transmitter FIFO structure slave object */
  CANMSG_Msg_MOFCR_MMC_SrcObj                = 0x4UL,                /*!< gateway source object */
} CANMSG_Msg_MOFCR_MMC_Enum;

/*-- Msg: MOFGPR: Pointer register FIFO / gateway message object 0 --------------------------------------------*/
typedef struct {
  uint32_t BOT                    :8;                                /*!< FIFO pointer to the lower element */
  uint32_t TOP                    :8;                                /*!< FIFO pointer to the top element  */
  uint32_t CUR                    :8;                                /*!< A pointer to the current object within the FIFO or gateway */
  uint32_t SEL                    :8;                                /*!< Object pointer message */
} _CANMSG_Msg_MOFGPR_bits;

/* Bit field positions: */
#define CANMSG_Msg_MOFGPR_BOT_Pos             0                      /*!< FIFO pointer to the lower element */
#define CANMSG_Msg_MOFGPR_TOP_Pos             8                      /*!< FIFO pointer to the top element  */
#define CANMSG_Msg_MOFGPR_CUR_Pos             16                     /*!< A pointer to the current object within the FIFO or gateway */
#define CANMSG_Msg_MOFGPR_SEL_Pos             24                     /*!< Object pointer message */

/* Bit field masks: */
#define CANMSG_Msg_MOFGPR_BOT_Msk             0x000000FFUL           /*!< FIFO pointer to the lower element */
#define CANMSG_Msg_MOFGPR_TOP_Msk             0x0000FF00UL           /*!< FIFO pointer to the top element  */
#define CANMSG_Msg_MOFGPR_CUR_Msk             0x00FF0000UL           /*!< A pointer to the current object within the FIFO or gateway */
#define CANMSG_Msg_MOFGPR_SEL_Msk             0xFF000000UL           /*!< Object pointer message */

/*-- Msg: MOIPR: Pointer register interrupt message object 0 --------------------------------------------------*/
typedef struct {
  uint32_t RXINP                  :4;                                /*!< Pointer interrupt line to interrupt after receiving */
  uint32_t TXINP                  :4;                                /*!< Pointer interrupt line to interrupt after transfer */
  uint32_t MPN                    :8;                                /*!< Number message waiting bit */
  uint32_t CFCVAL                 :16;                               /*!< Number of frames */
} _CANMSG_Msg_MOIPR_bits;

/* Bit field positions: */
#define CANMSG_Msg_MOIPR_RXINP_Pos            0                      /*!< Pointer interrupt line to interrupt after receiving */
#define CANMSG_Msg_MOIPR_TXINP_Pos            4                      /*!< Pointer interrupt line to interrupt after transfer */
#define CANMSG_Msg_MOIPR_MPN_Pos              8                      /*!< Number message waiting bit */
#define CANMSG_Msg_MOIPR_CFCVAL_Pos           16                     /*!< Number of frames */

/* Bit field masks: */
#define CANMSG_Msg_MOIPR_RXINP_Msk            0x0000000FUL           /*!< Pointer interrupt line to interrupt after receiving */
#define CANMSG_Msg_MOIPR_TXINP_Msk            0x000000F0UL           /*!< Pointer interrupt line to interrupt after transfer */
#define CANMSG_Msg_MOIPR_MPN_Msk              0x0000FF00UL           /*!< Number message waiting bit */
#define CANMSG_Msg_MOIPR_CFCVAL_Msk           0xFFFF0000UL           /*!< Number of frames */

/*-- Msg: MOAMR: Mask register message object 0 ---------------------------------------------------------------*/
typedef struct {
  uint32_t AM                     :29;                               /*!< Mask ID */
  uint32_t MIDE                   :1;                                /*!< Mask bit IDE message */
} _CANMSG_Msg_MOAMR_bits;

/* Bit field positions: */
#define CANMSG_Msg_MOAMR_AM_Pos               0                      /*!< Mask ID */
#define CANMSG_Msg_MOAMR_MIDE_Pos             29                     /*!< Mask bit IDE message */

/* Bit field masks: */
#define CANMSG_Msg_MOAMR_AM_Msk               0x1FFFFFFFUL           /*!< Mask ID */
#define CANMSG_Msg_MOAMR_MIDE_Msk             0x20000000UL           /*!< Mask bit IDE message */

/*-- Msg: MODATAL: Low data registers of the message object 0 -------------------------------------------------*/
typedef struct {
  uint32_t DB0                    :8;                                /*!< Zero byte data */
  uint32_t DB1                    :8;                                /*!< The first data byte */
  uint32_t DB2                    :8;                                /*!< Second data byte */
  uint32_t DB3                    :8;                                /*!< The third data byte */
} _CANMSG_Msg_MODATAL_bits;

/* Bit field positions: */
#define CANMSG_Msg_MODATAL_DB0_Pos            0                      /*!< Zero byte data */
#define CANMSG_Msg_MODATAL_DB1_Pos            8                      /*!< The first data byte */
#define CANMSG_Msg_MODATAL_DB2_Pos            16                     /*!< Second data byte */
#define CANMSG_Msg_MODATAL_DB3_Pos            24                     /*!< The third data byte */

/* Bit field masks: */
#define CANMSG_Msg_MODATAL_DB0_Msk            0x000000FFUL           /*!< Zero byte data */
#define CANMSG_Msg_MODATAL_DB1_Msk            0x0000FF00UL           /*!< The first data byte */
#define CANMSG_Msg_MODATAL_DB2_Msk            0x00FF0000UL           /*!< Second data byte */
#define CANMSG_Msg_MODATAL_DB3_Msk            0xFF000000UL           /*!< The third data byte */

/*-- Msg: MODATAH: High data registers of the message object 0 ------------------------------------------------*/
typedef struct {
  uint32_t DB4                    :8;                                /*!< The fourth data byte */
  uint32_t DB5                    :8;                                /*!< Fifth byte data */
  uint32_t DB6                    :8;                                /*!< Sixth byte data  */
  uint32_t DB7                    :8;                                /*!< Seventh byte of data  */
} _CANMSG_Msg_MODATAH_bits;

/* Bit field positions: */
#define CANMSG_Msg_MODATAH_DB4_Pos            0                      /*!< The fourth data byte */
#define CANMSG_Msg_MODATAH_DB5_Pos            8                      /*!< Fifth byte data */
#define CANMSG_Msg_MODATAH_DB6_Pos            16                     /*!< Sixth byte data  */
#define CANMSG_Msg_MODATAH_DB7_Pos            24                     /*!< Seventh byte of data  */

/* Bit field masks: */
#define CANMSG_Msg_MODATAH_DB4_Msk            0x000000FFUL           /*!< The fourth data byte */
#define CANMSG_Msg_MODATAH_DB5_Msk            0x0000FF00UL           /*!< Fifth byte data */
#define CANMSG_Msg_MODATAH_DB6_Msk            0x00FF0000UL           /*!< Sixth byte data  */
#define CANMSG_Msg_MODATAH_DB7_Msk            0xFF000000UL           /*!< Seventh byte of data  */

/*-- Msg: MOAR: Register arbitration message object 0 ---------------------------------------------------------*/
typedef struct {
  uint32_t ID                     :29;                               /*!< Object ID message 0 */
  uint32_t IDE                    :1;                                /*!< Bit extension identifier of the message object 0 */
  uint32_t PRI                    :2;                                /*!< Priority class */
} _CANMSG_Msg_MOAR_bits;

/* Bit field positions: */
#define CANMSG_Msg_MOAR_ID_Pos                0                      /*!< Object ID message 0 */
#define CANMSG_Msg_MOAR_IDE_Pos               29                     /*!< Bit extension identifier of the message object 0 */
#define CANMSG_Msg_MOAR_PRI_Pos               30                     /*!< Priority class */

/* Bit field masks: */
#define CANMSG_Msg_MOAR_ID_Msk                0x1FFFFFFFUL           /*!< Object ID message 0 */
#define CANMSG_Msg_MOAR_IDE_Msk               0x20000000UL           /*!< Bit extension identifier of the message object 0 */
#define CANMSG_Msg_MOAR_PRI_Msk               0xC0000000UL           /*!< Priority class */

/*-- Msg: MOCTR: Control register Message object 0 ------------------------------------------------------------*/
typedef struct {
  uint32_t RESRXPND               :1;                                /*!< Reset bit RXPND */
  uint32_t RESTXPND               :1;                                /*!< Reset bit TXPND */
  uint32_t RESRXUPD               :1;                                /*!< Reset bit RXUPD */
  uint32_t RESNEWDAT              :1;                                /*!< Reset bit NEWDAT */
  uint32_t RESMSGLST              :1;                                /*!< Reset bit MSGLST */
  uint32_t RESMSGVAL              :1;                                /*!< Reset bit MSGVAL */
  uint32_t RESRTSEL               :1;                                /*!< Reset bit RTSEL */
  uint32_t RESRXEN                :1;                                /*!< Reset bit RXEN */
  uint32_t RESTXRQ                :1;                                /*!< Reset bit TXRQ */
  uint32_t RESTXEN0               :1;                                /*!< Reset bit TXEN0 */
  uint32_t RESTXEN1               :1;                                /*!< Reset bit TXEN1 */
  uint32_t RESDIR                 :1;                                /*!< Reset bit DIR */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t SETRXPND               :1;                                /*!< Set bit RXPND */
  uint32_t SETTXPND               :1;                                /*!< Set bit TXPND */
  uint32_t SETRXUPD               :1;                                /*!< Set bit RXUPD */
  uint32_t SETNEWDAT              :1;                                /*!< Set bit NEWDAT */
  uint32_t SETMSGLST              :1;                                /*!< Set bit MSGLST */
  uint32_t SETMSGVAL              :1;                                /*!< Set bit MSGVAL */
  uint32_t SETRTSEL               :1;                                /*!< Set bit RTSEL */
  uint32_t SETRXEN                :1;                                /*!< Set bit RXEN */
  uint32_t SETTXRQ                :1;                                /*!< Set bit TXRQ */
  uint32_t SETTXEN0               :1;                                /*!< Set bit TXEN0 */
  uint32_t SETTXEN1               :1;                                /*!< Set bit TXEN1 */
  uint32_t SETDIR                 :1;                                /*!< Set bit DIR */
} _CANMSG_Msg_MOCTR_bits;

/* Bit field positions: */
#define CANMSG_Msg_MOCTR_RESRXPND_Pos         0                      /*!< Reset bit RXPND */
#define CANMSG_Msg_MOCTR_RESTXPND_Pos         1                      /*!< Reset bit TXPND */
#define CANMSG_Msg_MOCTR_RESRXUPD_Pos         2                      /*!< Reset bit RXUPD */
#define CANMSG_Msg_MOCTR_RESNEWDAT_Pos        3                      /*!< Reset bit NEWDAT */
#define CANMSG_Msg_MOCTR_RESMSGLST_Pos        4                      /*!< Reset bit MSGLST */
#define CANMSG_Msg_MOCTR_RESMSGVAL_Pos        5                      /*!< Reset bit MSGVAL */
#define CANMSG_Msg_MOCTR_RESRTSEL_Pos         6                      /*!< Reset bit RTSEL */
#define CANMSG_Msg_MOCTR_RESRXEN_Pos          7                      /*!< Reset bit RXEN */
#define CANMSG_Msg_MOCTR_RESTXRQ_Pos          8                      /*!< Reset bit TXRQ */
#define CANMSG_Msg_MOCTR_RESTXEN0_Pos         9                      /*!< Reset bit TXEN0 */
#define CANMSG_Msg_MOCTR_RESTXEN1_Pos         10                     /*!< Reset bit TXEN1 */
#define CANMSG_Msg_MOCTR_RESDIR_Pos           11                     /*!< Reset bit DIR */
#define CANMSG_Msg_MOCTR_SETRXPND_Pos         16                     /*!< Set bit RXPND */
#define CANMSG_Msg_MOCTR_SETTXPND_Pos         17                     /*!< Set bit TXPND */
#define CANMSG_Msg_MOCTR_SETRXUPD_Pos         18                     /*!< Set bit RXUPD */
#define CANMSG_Msg_MOCTR_SETNEWDAT_Pos        19                     /*!< Set bit NEWDAT */
#define CANMSG_Msg_MOCTR_SETMSGLST_Pos        20                     /*!< Set bit MSGLST */
#define CANMSG_Msg_MOCTR_SETMSGVAL_Pos        21                     /*!< Set bit MSGVAL */
#define CANMSG_Msg_MOCTR_SETRTSEL_Pos         22                     /*!< Set bit RTSEL */
#define CANMSG_Msg_MOCTR_SETRXEN_Pos          23                     /*!< Set bit RXEN */
#define CANMSG_Msg_MOCTR_SETTXRQ_Pos          24                     /*!< Set bit TXRQ */
#define CANMSG_Msg_MOCTR_SETTXEN0_Pos         25                     /*!< Set bit TXEN0 */
#define CANMSG_Msg_MOCTR_SETTXEN1_Pos         26                     /*!< Set bit TXEN1 */
#define CANMSG_Msg_MOCTR_SETDIR_Pos           27                     /*!< Set bit DIR */

/* Bit field masks: */
#define CANMSG_Msg_MOCTR_RESRXPND_Msk         0x00000001UL           /*!< Reset bit RXPND */
#define CANMSG_Msg_MOCTR_RESTXPND_Msk         0x00000002UL           /*!< Reset bit TXPND */
#define CANMSG_Msg_MOCTR_RESRXUPD_Msk         0x00000004UL           /*!< Reset bit RXUPD */
#define CANMSG_Msg_MOCTR_RESNEWDAT_Msk        0x00000008UL           /*!< Reset bit NEWDAT */
#define CANMSG_Msg_MOCTR_RESMSGLST_Msk        0x00000010UL           /*!< Reset bit MSGLST */
#define CANMSG_Msg_MOCTR_RESMSGVAL_Msk        0x00000020UL           /*!< Reset bit MSGVAL */
#define CANMSG_Msg_MOCTR_RESRTSEL_Msk         0x00000040UL           /*!< Reset bit RTSEL */
#define CANMSG_Msg_MOCTR_RESRXEN_Msk          0x00000080UL           /*!< Reset bit RXEN */
#define CANMSG_Msg_MOCTR_RESTXRQ_Msk          0x00000100UL           /*!< Reset bit TXRQ */
#define CANMSG_Msg_MOCTR_RESTXEN0_Msk         0x00000200UL           /*!< Reset bit TXEN0 */
#define CANMSG_Msg_MOCTR_RESTXEN1_Msk         0x00000400UL           /*!< Reset bit TXEN1 */
#define CANMSG_Msg_MOCTR_RESDIR_Msk           0x00000800UL           /*!< Reset bit DIR */
#define CANMSG_Msg_MOCTR_SETRXPND_Msk         0x00010000UL           /*!< Set bit RXPND */
#define CANMSG_Msg_MOCTR_SETTXPND_Msk         0x00020000UL           /*!< Set bit TXPND */
#define CANMSG_Msg_MOCTR_SETRXUPD_Msk         0x00040000UL           /*!< Set bit RXUPD */
#define CANMSG_Msg_MOCTR_SETNEWDAT_Msk        0x00080000UL           /*!< Set bit NEWDAT */
#define CANMSG_Msg_MOCTR_SETMSGLST_Msk        0x00100000UL           /*!< Set bit MSGLST */
#define CANMSG_Msg_MOCTR_SETMSGVAL_Msk        0x00200000UL           /*!< Set bit MSGVAL */
#define CANMSG_Msg_MOCTR_SETRTSEL_Msk         0x00400000UL           /*!< Set bit RTSEL */
#define CANMSG_Msg_MOCTR_SETRXEN_Msk          0x00800000UL           /*!< Set bit RXEN */
#define CANMSG_Msg_MOCTR_SETTXRQ_Msk          0x01000000UL           /*!< Set bit TXRQ */
#define CANMSG_Msg_MOCTR_SETTXEN0_Msk         0x02000000UL           /*!< Set bit TXEN0 */
#define CANMSG_Msg_MOCTR_SETTXEN1_Msk         0x04000000UL           /*!< Set bit TXEN1 */
#define CANMSG_Msg_MOCTR_SETDIR_Msk           0x08000000UL           /*!< Set bit DIR */

/*-- Msg: MOSTAT: Status register of the message object 0 -----------------------------------------------------*/
typedef struct {
  uint32_t RXPND                  :1;                                /*!< Indicator deadline */
  uint32_t TXPND                  :1;                                /*!< Indicator end of transmission */
  uint32_t RXUPD                  :1;                                /*!< Indicator changes */
  uint32_t NEWDAT                 :1;                                /*!< New data indicator */
  uint32_t MSGLST                 :1;                                /*!< Bit message loss */
  uint32_t MSGVAL                 :1;                                /*!< Activity bit of the message object 0 */
  uint32_t RTSEL                  :1;                                /*!< The indication of transmission / reception */
  uint32_t RXEN                   :1;                                /*!< Bits allow reception */
  uint32_t TXRQ                   :1;                                /*!< Initiate transmission */
  uint32_t TXEN0                  :1;                                /*!< Enable bit transmission frame */
  uint32_t TXEN1                  :1;                                /*!< Enable bit transmission frame */
  uint32_t DIR                    :1;                                /*!< Bit allocation */
  uint32_t LIST                   :4;                                /*!< Number list  the message object 0 */
  uint32_t PPREV                  :8;                                /*!< Pointer to the previous entry */
  uint32_t PNEXT                  :8;                                /*!< Pointer to the next item in the list */
} _CANMSG_Msg_MOSTAT_bits;

/* Bit field positions: */
#define CANMSG_Msg_MOSTAT_RXPND_Pos           0                      /*!< Indicator deadline */
#define CANMSG_Msg_MOSTAT_TXPND_Pos           1                      /*!< Indicator end of transmission */
#define CANMSG_Msg_MOSTAT_RXUPD_Pos           2                      /*!< Indicator changes */
#define CANMSG_Msg_MOSTAT_NEWDAT_Pos          3                      /*!< New data indicator */
#define CANMSG_Msg_MOSTAT_MSGLST_Pos          4                      /*!< Bit message loss */
#define CANMSG_Msg_MOSTAT_MSGVAL_Pos          5                      /*!< Activity bit of the message object 0 */
#define CANMSG_Msg_MOSTAT_RTSEL_Pos           6                      /*!< The indication of transmission / reception */
#define CANMSG_Msg_MOSTAT_RXEN_Pos            7                      /*!< Bits allow reception */
#define CANMSG_Msg_MOSTAT_TXRQ_Pos            8                      /*!< Initiate transmission */
#define CANMSG_Msg_MOSTAT_TXEN0_Pos           9                      /*!< Enable bit transmission frame */
#define CANMSG_Msg_MOSTAT_TXEN1_Pos           10                     /*!< Enable bit transmission frame */
#define CANMSG_Msg_MOSTAT_DIR_Pos             11                     /*!< Bit allocation */
#define CANMSG_Msg_MOSTAT_LIST_Pos            12                     /*!< Number list  the message object 0 */
#define CANMSG_Msg_MOSTAT_PPREV_Pos           16                     /*!< Pointer to the previous entry */
#define CANMSG_Msg_MOSTAT_PNEXT_Pos           24                     /*!< Pointer to the next item in the list */

/* Bit field masks: */
#define CANMSG_Msg_MOSTAT_RXPND_Msk           0x00000001UL           /*!< Indicator deadline */
#define CANMSG_Msg_MOSTAT_TXPND_Msk           0x00000002UL           /*!< Indicator end of transmission */
#define CANMSG_Msg_MOSTAT_RXUPD_Msk           0x00000004UL           /*!< Indicator changes */
#define CANMSG_Msg_MOSTAT_NEWDAT_Msk          0x00000008UL           /*!< New data indicator */
#define CANMSG_Msg_MOSTAT_MSGLST_Msk          0x00000010UL           /*!< Bit message loss */
#define CANMSG_Msg_MOSTAT_MSGVAL_Msk          0x00000020UL           /*!< Activity bit of the message object 0 */
#define CANMSG_Msg_MOSTAT_RTSEL_Msk           0x00000040UL           /*!< The indication of transmission / reception */
#define CANMSG_Msg_MOSTAT_RXEN_Msk            0x00000080UL           /*!< Bits allow reception */
#define CANMSG_Msg_MOSTAT_TXRQ_Msk            0x00000100UL           /*!< Initiate transmission */
#define CANMSG_Msg_MOSTAT_TXEN0_Msk           0x00000200UL           /*!< Enable bit transmission frame */
#define CANMSG_Msg_MOSTAT_TXEN1_Msk           0x00000400UL           /*!< Enable bit transmission frame */
#define CANMSG_Msg_MOSTAT_DIR_Msk             0x00000800UL           /*!< Bit allocation */
#define CANMSG_Msg_MOSTAT_LIST_Msk            0x0000F000UL           /*!< Number list  the message object 0 */
#define CANMSG_Msg_MOSTAT_PPREV_Msk           0x00FF0000UL           /*!< Pointer to the previous entry */
#define CANMSG_Msg_MOSTAT_PNEXT_Msk           0xFF000000UL           /*!< Pointer to the next item in the list */

//Cluster Msg:
typedef struct {
  union {
  /*!< Register control the operation of the message object 0 */
    __IO uint32_t MOFCR;                                             /*!< MOFCR : type used for word access */
    __IO _CANMSG_Msg_MOFCR_bits MOFCR_bit;                           /*!< MOFCR_bit: structure used for bit access */
  };
  union {
  /*!< Pointer register FIFO / gateway message object 0 */
    __IO uint32_t MOFGPR;                                            /*!< MOFGPR : type used for word access */
    __IO _CANMSG_Msg_MOFGPR_bits MOFGPR_bit;                         /*!< MOFGPR_bit: structure used for bit access */
  };
  union {
  /*!< Pointer register interrupt message object 0 */
    __IO uint32_t MOIPR;                                             /*!< MOIPR : type used for word access */
    __IO _CANMSG_Msg_MOIPR_bits MOIPR_bit;                           /*!< MOIPR_bit: structure used for bit access */
  };
  union {
  /*!< Mask register message object 0 */
    __IO uint32_t MOAMR;                                             /*!< MOAMR : type used for word access */
    __IO _CANMSG_Msg_MOAMR_bits MOAMR_bit;                           /*!< MOAMR_bit: structure used for bit access */
  };
  union {
  /*!< Low data registers of the message object 0 */
    __IO uint32_t MODATAL;                                           /*!< MODATAL : type used for word access */
    __IO _CANMSG_Msg_MODATAL_bits MODATAL_bit;                       /*!< MODATAL_bit: structure used for bit access */
  };
  union {
  /*!< High data registers of the message object 0 */
    __IO uint32_t MODATAH;                                           /*!< MODATAH : type used for word access */
    __IO _CANMSG_Msg_MODATAH_bits MODATAH_bit;                       /*!< MODATAH_bit: structure used for bit access */
  };
  union {
  /*!< Register arbitration message object 0 */
    __IO uint32_t MOAR;                                              /*!< MOAR : type used for word access */
    __IO _CANMSG_Msg_MOAR_bits MOAR_bit;                             /*!< MOAR_bit: structure used for bit access */
  };
  union {
      union {
                                                                     /*!< Control register Message object 0 */
        __O uint32_t MOCTR;                                           /*!< MOCTR : type used for word access */
        __O _CANMSG_Msg_MOCTR_bits MOCTR_bit;                        /*!< MOCTR_bit: structure used for bit access */
      };
      union {
                                                                     /*!< Status register of the message object 0 */
        __I uint32_t MOSTAT;                                           /*!< MOSTAT : type used for word access */
        __I _CANMSG_Msg_MOSTAT_bits MOSTAT_bit;                      /*!< MOSTAT_bit: structure used for bit access */
      };
  };
} _CANMSG_Msg_TypeDef;
typedef struct {
  _CANMSG_Msg_TypeDef Msg[64];
} CANMSG_TypeDef;


/******************************************************************************/
/*                         DAC registers                                      */
/******************************************************************************/

/*--  DATA12: Output data register (12 bits) ------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :12;                               /*!<  */
} _DAC_DATA12_bits;

/* Bit field positions: */
#define DAC_DATA12_VAL_Pos                    0                      /*!<  */

/* Bit field masks: */
#define DAC_DATA12_VAL_Msk                    0x00000FFFUL           /*!<  */

/*--  DATA8: Output data register (8 MSBs) --------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :8;                                /*!< Write 8 most significant bits (4 less significant bits will be set to 0) */
} _DAC_DATA8_bits;

/* Bit field positions: */
#define DAC_DATA8_VAL_Pos                     0                      /*!< Write 8 most significant bits (4 less significant bits will be set to 0) */

/* Bit field masks: */
#define DAC_DATA8_VAL_Msk                     0x000000FFUL           /*!< Write 8 most significant bits (4 less significant bits will be set to 0) */

/*--  CONTROL: Control register -------------------------------------------------------------------------------*/
typedef struct {
  uint32_t DISABLE                :1;                                /*!< Disable DAC block */
  uint32_t EXT_REF                :1;                                /*!< Use external reference voltage source */
  uint32_t BUF_EN                 :1;                                /*!< Enable output buffer */
  uint32_t SHUNT                  :1;                                /*!< Enable shunt resistor (explore) */
  uint32_t TSEL                   :4;                                /*!< Select DAC trigger event */
  uint32_t WAVE                   :2;                                /*!< DAC channel wave generation enable */
  uint32_t DATAMODE               :1;                                /*!< [unused] Switch between independent and simultaneous DAC mode */
  uint32_t SIGN                   :1;                                /*!< Signed DAC mode enable */
  uint32_t MASK                   :4;                                /*!< DAC channel mask/amplitude selector */
  uint32_t SCALE                  :3;                                /*!< Scale value for up/downscale input data in steps by power of 4 */
  uint32_t MULDIV                 :1;                                /*!< Switch between up and downscale */
  uint32_t NEGATE                 :1;                                /*!< Convert data to it's two's complement value */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t OFFSET                 :8;                                /*!< Offset for pattern generator */
} _DAC_CONTROL_bits;

/* Bit field positions: */
#define DAC_CONTROL_DISABLE_Pos               0                      /*!< Disable DAC block */
#define DAC_CONTROL_EXT_REF_Pos               1                      /*!< Use external reference voltage source */
#define DAC_CONTROL_BUF_EN_Pos                2                      /*!< Enable output buffer */
#define DAC_CONTROL_SHUNT_Pos                 3                      /*!< Enable shunt resistor (explore) */
#define DAC_CONTROL_TSEL_Pos                  4                      /*!< Select DAC trigger event */
#define DAC_CONTROL_WAVE_Pos                  8                      /*!< DAC channel wave generation enable */
#define DAC_CONTROL_DATAMODE_Pos              10                     /*!< [unused] Switch between independent and simultaneous DAC mode */
#define DAC_CONTROL_SIGN_Pos                  11                     /*!< Signed DAC mode enable */
#define DAC_CONTROL_MASK_Pos                  12                     /*!< DAC channel mask/amplitude selector */
#define DAC_CONTROL_SCALE_Pos                 16                     /*!< Scale value for up/downscale input data in steps by power of 4 */
#define DAC_CONTROL_MULDIV_Pos                19                     /*!< Switch between up and downscale */
#define DAC_CONTROL_NEGATE_Pos                20                     /*!< Convert data to it's two's complement value */
#define DAC_CONTROL_OFFSET_Pos                24                     /*!< Offset for pattern generator */

/* Bit field masks: */
#define DAC_CONTROL_DISABLE_Msk               0x00000001UL           /*!< Disable DAC block */
#define DAC_CONTROL_EXT_REF_Msk               0x00000002UL           /*!< Use external reference voltage source */
#define DAC_CONTROL_BUF_EN_Msk                0x00000004UL           /*!< Enable output buffer */
#define DAC_CONTROL_SHUNT_Msk                 0x00000008UL           /*!< Enable shunt resistor (explore) */
#define DAC_CONTROL_TSEL_Msk                  0x000000F0UL           /*!< Select DAC trigger event */
#define DAC_CONTROL_WAVE_Msk                  0x00000300UL           /*!< DAC channel wave generation enable */
#define DAC_CONTROL_DATAMODE_Msk              0x00000400UL           /*!< [unused] Switch between independent and simultaneous DAC mode */
#define DAC_CONTROL_SIGN_Msk                  0x00000800UL           /*!< Signed DAC mode enable */
#define DAC_CONTROL_MASK_Msk                  0x0000F000UL           /*!< DAC channel mask/amplitude selector */
#define DAC_CONTROL_SCALE_Msk                 0x00070000UL           /*!< Scale value for up/downscale input data in steps by power of 4 */
#define DAC_CONTROL_MULDIV_Msk                0x00080000UL           /*!< Switch between up and downscale */
#define DAC_CONTROL_NEGATE_Msk                0x00100000UL           /*!< Convert data to it's two's complement value */
#define DAC_CONTROL_OFFSET_Msk                0xFF000000UL           /*!< Offset for pattern generator */

/* Bit field enums: */
typedef enum {
  DAC_CONTROL_EXT_REF_INTERNAL_REF           = 0x0UL,                /*!< Use internal reference volatage source */
  DAC_CONTROL_EXT_REF_EXTERNAL_REF           = 0x1UL,                /*!< Use external 3.3 V reference volatage source */
} DAC_CONTROL_EXT_REF_Enum;

typedef enum {
  DAC_CONTROL_TSEL_SWTRIG                    = 0x0UL,                /*!< software request by SWTRIG bit */
  DAC_CONTROL_TSEL_HWTRIG                    = 0x1UL,                /*!< hardware request from internal trigger generator */
  DAC_CONTROL_TSEL_GPIOA                     = 0x2UL,                /*!< GPIO A interrupt */
  DAC_CONTROL_TSEL_GPIOB                     = 0x3UL,                /*!< GPIO B interrupt */
  DAC_CONTROL_TSEL_TMR32_0                   = 0x4UL,                /*!< Timer 0 (TMR32_0) request */
  DAC_CONTROL_TSEL_TMR32_1                   = 0x5UL,                /*!< Timer 1 (TMR32_1) request */
  DAC_CONTROL_TSEL_TMR16_0                   = 0x6UL,                /*!< Timer 2 (TMR16_0) request */
  DAC_CONTROL_TSEL_TMR16_1                   = 0x7UL,                /*!< Timer 3 (TMR16_1) request */
  DAC_CONTROL_TSEL_TMR16_2                   = 0x8UL,                /*!< Timer 4 (TMR16_2) request */
  DAC_CONTROL_TSEL_DUMMY_9                   = 0x9UL,                /*!< Reserved */
  DAC_CONTROL_TSEL_DUMMY_10                  = 0xAUL,                /*!< Reserved */
  DAC_CONTROL_TSEL_DUMMY_11                  = 0xBUL,                /*!< Reserved */
  DAC_CONTROL_TSEL_DUMMY_12                  = 0xCUL,                /*!< Reserved */
  DAC_CONTROL_TSEL_DUMMY_13                  = 0xDUL,                /*!< Reserved */
  DAC_CONTROL_TSEL_DUMMY_14                  = 0xEUL,                /*!< Reserved */
  DAC_CONTROL_TSEL_DUMMY_15                  = 0xFUL,                /*!< Reserved */
} DAC_CONTROL_TSEL_Enum;

typedef enum {
  DAC_CONTROL_WAVE_NONE                      = 0x0UL,                /*!< Wave generation disabled */
  DAC_CONTROL_WAVE_NOISE                     = 0x1UL,                /*!< Noise wave generation enable */
  DAC_CONTROL_WAVE_TRIANGULAR                = 0x2UL,                /*!< Triangular wave generation enable */
  DAC_CONTROL_WAVE_PATTERN                   = 0x3UL,                /*!< Pattern generator enable */
} DAC_CONTROL_WAVE_Enum;

typedef enum {
  DAC_CONTROL_DATAMODE_INDEPENDENT           = 0x0UL,                /*!< Independent DAC mode */
  DAC_CONTROL_DATAMODE_SIMULTANEOUS          = 0x1UL,                /*!< Simultaneous DAC mode */
} DAC_CONTROL_DATAMODE_Enum;

typedef enum {
  DAC_CONTROL_SIGN_UNSIGNED                  = 0x0UL,                /*!< Data treated as unsigned value */
  DAC_CONTROL_SIGN_SIGNED                    = 0x1UL,                /*!< Data treated as signed values */
} DAC_CONTROL_SIGN_Enum;

typedef enum {
  DAC_CONTROL_SCALE_NOSHIFT                  = 0x0UL,                /*!< multiplication/division by 1 */
  DAC_CONTROL_SCALE_SHIFT1                   = 0x1UL,                /*!< multiplication/division by 2 */
  DAC_CONTROL_SCALE_SHIFT2                   = 0x2UL,                /*!< multiplication/division by 4 */
  DAC_CONTROL_SCALE_SHIFT3                   = 0x3UL,                /*!< multiplication/division by 8 */
  DAC_CONTROL_SCALE_SHIFT4                   = 0x4UL,                /*!< multiplication/division by 16 */
  DAC_CONTROL_SCALE_SHIFT5                   = 0x5UL,                /*!< multiplication/division by 32 */
  DAC_CONTROL_SCALE_SHIFT6                   = 0x6UL,                /*!< multiplication/division by 64 */
  DAC_CONTROL_SCALE_SHIFT7                   = 0x7UL,                /*!< multiplication/division by 128 */
} DAC_CONTROL_SCALE_Enum;

typedef enum {
  DAC_CONTROL_MULDIV_DOWNSCALE               = 0x0UL,                /*!< division (shift SCALE positions to the right) */
  DAC_CONTROL_MULDIV_UPSCALE                 = 0x1UL,                /*!< multiplication (shift SCALE positions to the left) */
} DAC_CONTROL_MULDIV_Enum;

/*--  BGCTRL: Internal reference-voltage source (adjustable BandGap) register ---------------------------------*/
typedef struct {
  uint32_t TUNE                   :12;                               /*!< Tune bandgap voltage */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t EN                     :1;                                /*!< Turn-on internal reference-voltage source */
  uint32_t ADJUST                 :2;                                /*!< Adjust output voltage of internal reference-voltage source */
} _DAC_BGCTRL_bits;

/* Bit field positions: */
#define DAC_BGCTRL_TUNE_Pos                   0                      /*!< Tune bandgap voltage */
#define DAC_BGCTRL_EN_Pos                     16                     /*!< Turn-on internal reference-voltage source */
#define DAC_BGCTRL_ADJUST_Pos                 17                     /*!< Adjust output voltage of internal reference-voltage source */

/* Bit field masks: */
#define DAC_BGCTRL_TUNE_Msk                   0x00000FFFUL           /*!< Tune bandgap voltage */
#define DAC_BGCTRL_EN_Msk                     0x00010000UL           /*!< Turn-on internal reference-voltage source */
#define DAC_BGCTRL_ADJUST_Msk                 0x00060000UL           /*!< Adjust output voltage of internal reference-voltage source */

/* Bit field enums: */
typedef enum {
  DAC_BGCTRL_ADJUST_V_1p5                    = 0x0UL,                /*!< Output 1.5 V */
  DAC_BGCTRL_ADJUST_V_1p8                    = 0x1UL,                /*!< Output 1.8 V */
  DAC_BGCTRL_ADJUST_V_2p048                  = 0x2UL,                /*!< Output 2.048 V */
  DAC_BGCTRL_ADJUST_V_2p5                    = 0x3UL,                /*!< Output 2.5 V */
} DAC_BGCTRL_ADJUST_Enum;

/*--  DMACTRL: DAC DMA control register -----------------------------------------------------------------------*/
typedef struct {
  uint32_t ENABLE                 :1;                                /*!< DMA request generation enable */
  uint32_t TXSTOP                 :1;                                /*!< Automatic clear DMA TX request generation when channel ends all transactions */
} _DAC_DMACTRL_bits;

/* Bit field positions: */
#define DAC_DMACTRL_ENABLE_Pos                0                      /*!< DMA request generation enable */
#define DAC_DMACTRL_TXSTOP_Pos                1                      /*!< Automatic clear DMA TX request generation when channel ends all transactions */

/* Bit field masks: */
#define DAC_DMACTRL_ENABLE_Msk                0x00000001UL           /*!< DMA request generation enable */
#define DAC_DMACTRL_TXSTOP_Msk                0x00000002UL           /*!< Automatic clear DMA TX request generation when channel ends all transactions */

/*--  SWTRIG: Software trigger control register ---------------------------------------------------------------*/
typedef struct {
  uint32_t SWTRIG                 :1;                                /*!< Software trigger */
} _DAC_SWTRIG_bits;

/* Bit field positions: */
#define DAC_SWTRIG_SWTRIG_Pos                 0                      /*!< Software trigger */

/* Bit field masks: */
#define DAC_SWTRIG_SWTRIG_Msk                 0x00000001UL           /*!< Software trigger */

/*--  HWTRIG: Internal Hardware trigger generator control register --------------------------------------------*/
typedef struct {
  uint32_t ENABLE                 :1;                                /*!< Start internal trigger generation */
  uint32_t                        :15;                               /*!< RESERVED */
  uint32_t DIVIDER                :16;                               /*!< Frequency divider value */
} _DAC_HWTRIG_bits;

/* Bit field positions: */
#define DAC_HWTRIG_ENABLE_Pos                 0                      /*!< Start internal trigger generation */
#define DAC_HWTRIG_DIVIDER_Pos                16                     /*!< Frequency divider value */

/* Bit field masks: */
#define DAC_HWTRIG_ENABLE_Msk                 0x00000001UL           /*!< Start internal trigger generation */
#define DAC_HWTRIG_DIVIDER_Msk                0xFFFF0000UL           /*!< Frequency divider value */

/*--  PATDORL: Pattern data output register (low part) --------------------------------------------------------*/
typedef struct {
  uint32_t PAT0                   :5;                                /*!< Pattern number 0 for pattern generator */
  uint32_t PAT1                   :5;                                /*!< Pattern number 1 for pattern generator */
  uint32_t PAT2                   :5;                                /*!< Pattern number 2 for pattern generator */
  uint32_t PAT3                   :5;                                /*!< Pattern number 3 for pattern generator */
  uint32_t PAT4                   :5;                                /*!< Pattern number 4 for pattern generator */
  uint32_t PAT5                   :5;                                /*!< Pattern number 5 for pattern generator */
} _DAC_PATDORL_bits;

/* Bit field positions: */
#define DAC_PATDORL_PAT0_Pos                  0                      /*!< Pattern number 0 for pattern generator */
#define DAC_PATDORL_PAT1_Pos                  5                      /*!< Pattern number 1 for pattern generator */
#define DAC_PATDORL_PAT2_Pos                  10                     /*!< Pattern number 2 for pattern generator */
#define DAC_PATDORL_PAT3_Pos                  15                     /*!< Pattern number 3 for pattern generator */
#define DAC_PATDORL_PAT4_Pos                  20                     /*!< Pattern number 4 for pattern generator */
#define DAC_PATDORL_PAT5_Pos                  25                     /*!< Pattern number 5 for pattern generator */

/* Bit field masks: */
#define DAC_PATDORL_PAT0_Msk                  0x0000001FUL           /*!< Pattern number 0 for pattern generator */
#define DAC_PATDORL_PAT1_Msk                  0x000003E0UL           /*!< Pattern number 1 for pattern generator */
#define DAC_PATDORL_PAT2_Msk                  0x00007C00UL           /*!< Pattern number 2 for pattern generator */
#define DAC_PATDORL_PAT3_Msk                  0x000F8000UL           /*!< Pattern number 3 for pattern generator */
#define DAC_PATDORL_PAT4_Msk                  0x01F00000UL           /*!< Pattern number 4 for pattern generator */
#define DAC_PATDORL_PAT5_Msk                  0x3E000000UL           /*!< Pattern number 5 for pattern generator */

/* Bit field enums: */
typedef enum {
  DAC_PATDORL_PAT0_TRIANGLE_SIN              = 0x0UL,                /*!< Triangle or SIN pattern data 0 */
  DAC_PATDORL_PAT0_MEANDER                   = 0x1FUL,               /*!< Meander pattern data 0 */
} DAC_PATDORL_PAT0_Enum;

typedef enum {
  DAC_PATDORL_PAT1_TRIANGLE                  = 0x4UL,                /*!< Triangle pattern data 1 */
  DAC_PATDORL_PAT1_SIN                       = 0x6UL,                /*!< SIN pattern data 1 */
  DAC_PATDORL_PAT1_MEANDER                   = 0x1FUL,               /*!< Meander pattern data 1 */
} DAC_PATDORL_PAT1_Enum;

typedef enum {
  DAC_PATDORL_PAT2_TRIANGLE                  = 0x8UL,                /*!< Triangle pattern data 2 */
  DAC_PATDORL_PAT2_SIN                       = 0xCUL,                /*!< SIN pattern data 2 */
  DAC_PATDORL_PAT2_MEANDER                   = 0x1FUL,               /*!< Meander pattern data 2 */
} DAC_PATDORL_PAT2_Enum;

typedef enum {
  DAC_PATDORL_PAT3_TRIANGLE                  = 0xCUL,                /*!< Triangle pattern data 3 */
  DAC_PATDORL_PAT3_SIN                       = 0x11UL,               /*!< SIN pattern data 3 */
  DAC_PATDORL_PAT3_MEANDER                   = 0x1FUL,               /*!< Meander pattern data 3 */
} DAC_PATDORL_PAT3_Enum;

typedef enum {
  DAC_PATDORL_PAT4_TRIANGLE                  = 0x10UL,               /*!< Triangle pattern data 4 */
  DAC_PATDORL_PAT4_SIN                       = 0x16UL,               /*!< SIN pattern data 4 */
  DAC_PATDORL_PAT4_MEANDER                   = 0x1FUL,               /*!< Meander pattern data 4 */
} DAC_PATDORL_PAT4_Enum;

typedef enum {
  DAC_PATDORL_PAT5_TRIANGLE                  = 0x13UL,               /*!< Triangle pattern data 5 */
  DAC_PATDORL_PAT5_SIN                       = 0x1AUL,               /*!< SIN pattern data 5 */
  DAC_PATDORL_PAT5_MEANDER                   = 0x1FUL,               /*!< Meander pattern data 5 */
} DAC_PATDORL_PAT5_Enum;

/*--  PATDORH: Pattern data output register (high part) -------------------------------------------------------*/
typedef struct {
  uint32_t PAT6                   :5;                                /*!< Pattern number 6 for pattern generator */
  uint32_t PAT7                   :5;                                /*!< Pattern number 7 for pattern generator */
  uint32_t PAT8                   :5;                                /*!< Pattern number 8 for pattern generator */
} _DAC_PATDORH_bits;

/* Bit field positions: */
#define DAC_PATDORH_PAT6_Pos                  0                      /*!< Pattern number 6 for pattern generator */
#define DAC_PATDORH_PAT7_Pos                  5                      /*!< Pattern number 7 for pattern generator */
#define DAC_PATDORH_PAT8_Pos                  10                     /*!< Pattern number 8 for pattern generator */

/* Bit field masks: */
#define DAC_PATDORH_PAT6_Msk                  0x0000001FUL           /*!< Pattern number 6 for pattern generator */
#define DAC_PATDORH_PAT7_Msk                  0x000003E0UL           /*!< Pattern number 7 for pattern generator */
#define DAC_PATDORH_PAT8_Msk                  0x00007C00UL           /*!< Pattern number 8 for pattern generator */

/* Bit field enums: */
typedef enum {
  DAC_PATDORH_PAT6_TRIANGLE                  = 0x17UL,               /*!< Triangle pattern data 6 */
  DAC_PATDORH_PAT6_SIN                       = 0x1DUL,               /*!< SIN pattern data 6 */
  DAC_PATDORH_PAT6_MEANDER                   = 0x1FUL,               /*!< Meander pattern data 6 */
} DAC_PATDORH_PAT6_Enum;

typedef enum {
  DAC_PATDORH_PAT7_TRIANGLE                  = 0x1BUL,               /*!< Triangle pattern data 7 */
  DAC_PATDORH_PAT7_SIN                       = 0x1EUL,               /*!< SIN pattern data 7 */
  DAC_PATDORH_PAT7_MEANDER                   = 0x1FUL,               /*!< Meander pattern data 7 */
} DAC_PATDORH_PAT7_Enum;

typedef enum {
  DAC_PATDORH_PAT8_TRIANGLE_SIN_MEANDER      = 0x1FUL,               /*!< Triangle, SIN or meander pattern data 8 */
} DAC_PATDORH_PAT8_Enum;

typedef struct {
  union {                                                            /*!< Output data register (12 bits) */
    __IO uint32_t DATA12;                                            /*!< DATA12    : type used for word access */
    __IO _DAC_DATA12_bits  DATA12_bit;                               /*!< DATA12_bit: structure used for bit access */
  };
  union {                                                            /*!< Output data register (8 MSBs) */
    __IO uint32_t DATA8;                                             /*!< DATA8    : type used for word access */
    __IO _DAC_DATA8_bits  DATA8_bit;                                 /*!< DATA8_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0;
  union {                                                            /*!< Control register */
    __IO uint32_t CONTROL;                                           /*!< CONTROL    : type used for word access */
    __IO _DAC_CONTROL_bits  CONTROL_bit;                             /*!< CONTROL_bit: structure used for bit access */
  };
  union {                                                            /*!< Internal reference-voltage source (adjustable BandGap) register */
    __IO uint32_t BGCTRL;                                            /*!< BGCTRL    : type used for word access */
    __IO _DAC_BGCTRL_bits  BGCTRL_bit;                               /*!< BGCTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< DAC DMA control register */
    __IO uint32_t DMACTRL;                                           /*!< DMACTRL    : type used for word access */
    __IO _DAC_DMACTRL_bits  DMACTRL_bit;                             /*!< DMACTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< Software trigger control register */
    __O uint32_t SWTRIG;                                             /*!< SWTRIG    : type used for word access */
    __O _DAC_SWTRIG_bits  SWTRIG_bit;                                /*!< SWTRIG_bit: structure used for bit access */
  };
  union {                                                            /*!< Internal Hardware trigger generator control register */
    __IO uint32_t HWTRIG;                                            /*!< HWTRIG    : type used for word access */
    __IO _DAC_HWTRIG_bits  HWTRIG_bit;                               /*!< HWTRIG_bit: structure used for bit access */
  };
  union {                                                            /*!< Pattern data output register (low part) */
    __IO uint32_t PATDORL;                                           /*!< PATDORL    : type used for word access */
    __IO _DAC_PATDORL_bits  PATDORL_bit;                             /*!< PATDORL_bit: structure used for bit access */
  };
  union {                                                            /*!< Pattern data output register (high part) */
    __IO uint32_t PATDORH;                                           /*!< PATDORH    : type used for word access */
    __IO _DAC_PATDORH_bits  PATDORH_bit;                             /*!< PATDORH_bit: structure used for bit access */
  };
} DAC_TypeDef;


/******************************************************************************/
/*                         DMA registers                                      */
/******************************************************************************/

/*-- CH: SRC_PTR: Command register 0 (source pointer) ---------------------------------------------------------*/
typedef struct {
  uint32_t RD_ADDR                :32;                               /*!< Start address of read buffer */
} _DMA_CH_SRC_PTR_bits;

/* Bit field positions: */
#define DMA_CH_SRC_PTR_RD_ADDR_Pos            0                      /*!< Start address of read buffer */

/* Bit field masks: */
#define DMA_CH_SRC_PTR_RD_ADDR_Msk            0xFFFFFFFFUL           /*!< Start address of read buffer */

/*-- CH: DST_PTR: Command register 1 (destination pointer) ----------------------------------------------------*/
typedef struct {
  uint32_t WR_ADDR                :32;                               /*!< Start address of write buffer */
} _DMA_CH_DST_PTR_bits;

/* Bit field positions: */
#define DMA_CH_DST_PTR_WR_ADDR_Pos            0                      /*!< Start address of write buffer */

/* Bit field masks: */
#define DMA_CH_DST_PTR_WR_ADDR_Msk            0xFFFFFFFFUL           /*!< Start address of write buffer */

/*-- CH: NDTL: Command register 2 (number of data to transfer, linear mode) -----------------------------------*/
typedef struct {
  uint32_t BUFFER_SIZE            :10;                               /*!< Size of buffer to transfer */
} _DMA_CH_NDTL_bits;

/* Bit field positions: */
#define DMA_CH_NDTL_BUFFER_SIZE_Pos           0                      /*!< Size of buffer to transfer */

/* Bit field masks: */
#define DMA_CH_NDTL_BUFFER_SIZE_Msk           0x000003FFUL           /*!< Size of buffer to transfer */

/*-- CH: NDTB: Command register 2 (number of data to transfer, block mode) - Not Implemented --------------------------------*/
typedef struct {
  uint32_t X_SIZE                 :8;                                /*!< Block width. Value is in bytes and has no size restrictions  - Not Implemented */
  uint32_t Y_SIZE                 :8;                                /*!< Number of block lines  - Not Implemented */
} _DMA_CH_NDTB_bits;

/* Bit field positions: */
#define DMA_CH_NDTB_X_SIZE_Pos                0                      /*!< Block width. Value is in bytes and has no size restrictions  - Not Implemented */
#define DMA_CH_NDTB_Y_SIZE_Pos                8                      /*!< Number of block lines  - Not Implemented */

/* Bit field masks: */
#define DMA_CH_NDTB_X_SIZE_Msk                0x000000FFUL           /*!< Block width. Value is in bytes and has no size restrictions  - Not Implemented */
#define DMA_CH_NDTB_Y_SIZE_Msk                0x0000FF00UL           /*!< Number of block lines  - Not Implemented */

/*-- CH: CONFIG: Command register 3 (config) ------------------------------------------------------------------*/
typedef struct {
  uint32_t CMD_SET_INT            :1;                                /*!< Set interrupt after the entire buffer has been transferred */
  uint32_t CMD_LAST               :1;                                /*!< This is a last DMA command */
  uint32_t NEXT_ADDR              :30;                               /*!< Address of next command */
} _DMA_CH_CONFIG_bits;

/* Bit field positions: */
#define DMA_CH_CONFIG_CMD_SET_INT_Pos         0                      /*!< Set interrupt after the entire buffer has been transferred */
#define DMA_CH_CONFIG_CMD_LAST_Pos            1                      /*!< This is a last DMA command */
#define DMA_CH_CONFIG_NEXT_ADDR_Pos           2                      /*!< Address of next command */

/* Bit field masks: */
#define DMA_CH_CONFIG_CMD_SET_INT_Msk         0x00000001UL           /*!< Set interrupt after the entire buffer has been transferred */
#define DMA_CH_CONFIG_CMD_LAST_Msk            0x00000002UL           /*!< This is a last DMA command */
#define DMA_CH_CONFIG_NEXT_ADDR_Msk           0xFFFFFFFCUL           /*!< Address of next command */

/*-- CH: STATIC0: Static register 0 ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t RD_BURST_MAX           :7;                                /*!< Maximum number of bytes of an AXI read burst */
  uint32_t                        :9;                                /*!< RESERVED */
  uint32_t RD_TOKENS              :6;                                /*!< Number of AXI read commands to issue before the channel releases the AXI command bus */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t RD_OUTS_MAX            :4;                                /*!< Number of maximum outstanding AXI read commands */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t RD_OUTSTCFG            :1;                                /*!< Channel cfg: Use AXI read command when FIFO is full - Not implemented */
  uint32_t RD_INCR                :1;                                /*!< Increment next burst address */
} _DMA_CH_STATIC0_bits;

/* Bit field positions: */
#define DMA_CH_STATIC0_RD_BURST_MAX_Pos       0                      /*!< Maximum number of bytes of an AXI read burst */
#define DMA_CH_STATIC0_RD_TOKENS_Pos          16                     /*!< Number of AXI read commands to issue before the channel releases the AXI command bus */
#define DMA_CH_STATIC0_RD_OUTS_MAX_Pos        24                     /*!< Number of maximum outstanding AXI read commands */
#define DMA_CH_STATIC0_RD_OUTSTCFG_Pos        30                     /*!< Channel cfg: Use AXI read command when FIFO is full - Not implemented */
#define DMA_CH_STATIC0_RD_INCR_Pos            31                     /*!< Increment next burst address */

/* Bit field masks: */
#define DMA_CH_STATIC0_RD_BURST_MAX_Msk       0x0000007FUL           /*!< Maximum number of bytes of an AXI read burst */
#define DMA_CH_STATIC0_RD_TOKENS_Msk          0x003F0000UL           /*!< Number of AXI read commands to issue before the channel releases the AXI command bus */
#define DMA_CH_STATIC0_RD_OUTS_MAX_Msk        0x0F000000UL           /*!< Number of maximum outstanding AXI read commands */
#define DMA_CH_STATIC0_RD_OUTSTCFG_Msk        0x40000000UL           /*!< Channel cfg: Use AXI read command when FIFO is full - Not implemented */
#define DMA_CH_STATIC0_RD_INCR_Msk            0x80000000UL           /*!< Increment next burst address */

/*-- CH: STATIC1: Static register 1 ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t WR_BURST_MAX           :7;                                /*!< Maximum number of bytes of an AXI write burst */
  uint32_t                        :9;                                /*!< RESERVED */
  uint32_t WR_TOKENS              :6;                                /*!< Number of AXI write commands to issue before the channel releases the AXI command bus */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t WR_OUTS_MAX            :4;                                /*!< Number of maximum outstanding AXI write commands */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t WR_OUTSTCFG            :1;                                /*!< Channel cfg: Use AXI write command when FIFO is full - Not implemented */
  uint32_t WR_INCR                :1;                                /*!< Increment next burst address */
} _DMA_CH_STATIC1_bits;

/* Bit field positions: */
#define DMA_CH_STATIC1_WR_BURST_MAX_Pos       0                      /*!< Maximum number of bytes of an AXI write burst */
#define DMA_CH_STATIC1_WR_TOKENS_Pos          16                     /*!< Number of AXI write commands to issue before the channel releases the AXI command bus */
#define DMA_CH_STATIC1_WR_OUTS_MAX_Pos        24                     /*!< Number of maximum outstanding AXI write commands */
#define DMA_CH_STATIC1_WR_OUTSTCFG_Pos        30                     /*!< Channel cfg: Use AXI write command when FIFO is full - Not implemented */
#define DMA_CH_STATIC1_WR_INCR_Pos            31                     /*!< Increment next burst address */

/* Bit field masks: */
#define DMA_CH_STATIC1_WR_BURST_MAX_Msk       0x0000007FUL           /*!< Maximum number of bytes of an AXI write burst */
#define DMA_CH_STATIC1_WR_TOKENS_Msk          0x003F0000UL           /*!< Number of AXI write commands to issue before the channel releases the AXI command bus */
#define DMA_CH_STATIC1_WR_OUTS_MAX_Msk        0x0F000000UL           /*!< Number of maximum outstanding AXI write commands */
#define DMA_CH_STATIC1_WR_OUTSTCFG_Msk        0x40000000UL           /*!< Channel cfg: Use AXI write command when FIFO is full - Not implemented */
#define DMA_CH_STATIC1_WR_INCR_Msk            0x80000000UL           /*!< Increment next burst address */

/*-- CH: STATIC2: Static register 2 ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t FRAME_WIDTH            :12;                               /*!< Frame width for block mode - Not Implemented */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t BLOCK                  :1;                                /*!< Work in block mode - Not Implemented */
  uint32_t JOINT                  :1;                                /*!< Channel works in joint mode */
  uint32_t RETRY                  :1;                                /*!< If set the channel will automatically retry transfer if overflow or underflow occurs - Not implemented */
  uint32_t                        :10;                               /*!< RESERVED */
  uint32_t END_SWAP               :2;                                /*!< Endiannes byte swapping */
} _DMA_CH_STATIC2_bits;

/* Bit field positions: */
#define DMA_CH_STATIC2_FRAME_WIDTH_Pos        0                      /*!< Frame width for block mode - Not Implemented */
#define DMA_CH_STATIC2_BLOCK_Pos              15                     /*!< Work in block mode - Not Implemented */
#define DMA_CH_STATIC2_JOINT_Pos              16                     /*!< Channel works in joint mode */
#define DMA_CH_STATIC2_RETRY_Pos              17                     /*!< If set the channel will automatically retry transfer if overflow or underflow occurs - Not implemented */
#define DMA_CH_STATIC2_END_SWAP_Pos           28                     /*!< Endiannes byte swapping */

/* Bit field masks: */
#define DMA_CH_STATIC2_FRAME_WIDTH_Msk        0x00000FFFUL           /*!< Frame width for block mode - Not Implemented */
#define DMA_CH_STATIC2_BLOCK_Msk              0x00008000UL           /*!< Work in block mode - Not Implemented */
#define DMA_CH_STATIC2_JOINT_Msk              0x00010000UL           /*!< Channel works in joint mode */
#define DMA_CH_STATIC2_RETRY_Msk              0x00020000UL           /*!< If set the channel will automatically retry transfer if overflow or underflow occurs - Not implemented */
#define DMA_CH_STATIC2_END_SWAP_Msk           0x30000000UL           /*!< Endiannes byte swapping */

/* Bit field enums: */
typedef enum {
  DMA_CH_STATIC2_END_SWAP_NO_SWAP            = 0x0UL,                /*!< No swapping */
  DMA_CH_STATIC2_END_SWAP_SWAP_WITHIN16bits   = 0x1UL,               /*!< Swap bytes within 16 bits */
  DMA_CH_STATIC2_END_SWAP_SWAP_WITHIN32bits   = 0x2UL,               /*!< Swap bytes within 32 bits */
  DMA_CH_STATIC2_END_SWAP_                   = 0x3UL,                /*!<  */
} DMA_CH_STATIC2_END_SWAP_Enum;

/*-- CH: STATIC3: Static register 3 ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t RD_WAIT_LIM            :12;                               /*!< Maximum number of cycles to wait after a channel is released and before its starts read command */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t WR_WAIT_LIM            :12;                               /*!< Maximum number of cycles to wait after a channel is released and before its starts write command */
} _DMA_CH_STATIC3_bits;

/* Bit field positions: */
#define DMA_CH_STATIC3_RD_WAIT_LIM_Pos        0                      /*!< Maximum number of cycles to wait after a channel is released and before its starts read command */
#define DMA_CH_STATIC3_WR_WAIT_LIM_Pos        16                     /*!< Maximum number of cycles to wait after a channel is released and before its starts write command */

/* Bit field masks: */
#define DMA_CH_STATIC3_RD_WAIT_LIM_Msk        0x00000FFFUL           /*!< Maximum number of cycles to wait after a channel is released and before its starts read command */
#define DMA_CH_STATIC3_WR_WAIT_LIM_Msk        0x0FFF0000UL           /*!< Maximum number of cycles to wait after a channel is released and before its starts write command */

/*-- CH: STATIC4: Static register 4 ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t RD_PER_NUM             :5;                                /*!< Number of peripheral to read from */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t RD_PER_DELAY           :3;                                /*!< Peripheral latency for AXI read operation (must be set more than 1 for work with perepherals) */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t RD_PER_BLOCK           :1;                                /*!< Peripheral control works in block mode */
  uint32_t WR_PER_NUM             :5;                                /*!< Number of peripheral to write from */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t WR_PER_DELAY           :3;                                /*!< Peripheral latency for AXI write operation (must be set more than 1 for work with perepherals) */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t WR_PER_BLOCK           :1;                                /*!< Peripheral control works in block mode */
} _DMA_CH_STATIC4_bits;

/* Bit field positions: */
#define DMA_CH_STATIC4_RD_PER_NUM_Pos         0                      /*!< Number of peripheral to read from */
#define DMA_CH_STATIC4_RD_PER_DELAY_Pos       8                      /*!< Peripheral latency for AXI read operation (must be set more than 1 for work with perepherals) */
#define DMA_CH_STATIC4_RD_PER_BLOCK_Pos       15                     /*!< Peripheral control works in block mode */
#define DMA_CH_STATIC4_WR_PER_NUM_Pos         16                     /*!< Number of peripheral to write from */
#define DMA_CH_STATIC4_WR_PER_DELAY_Pos       24                     /*!< Peripheral latency for AXI write operation (must be set more than 1 for work with perepherals) */
#define DMA_CH_STATIC4_WR_PER_BLOCK_Pos       31                     /*!< Peripheral control works in block mode */

/* Bit field masks: */
#define DMA_CH_STATIC4_RD_PER_NUM_Msk         0x0000001FUL           /*!< Number of peripheral to read from */
#define DMA_CH_STATIC4_RD_PER_DELAY_Msk       0x00000700UL           /*!< Peripheral latency for AXI read operation (must be set more than 1 for work with perepherals) */
#define DMA_CH_STATIC4_RD_PER_BLOCK_Msk       0x00008000UL           /*!< Peripheral control works in block mode */
#define DMA_CH_STATIC4_WR_PER_NUM_Msk         0x001F0000UL           /*!< Number of peripheral to write from */
#define DMA_CH_STATIC4_WR_PER_DELAY_Msk       0x07000000UL           /*!< Peripheral latency for AXI write operation (must be set more than 1 for work with perepherals) */
#define DMA_CH_STATIC4_WR_PER_BLOCK_Msk       0x80000000UL           /*!< Peripheral control works in block mode */

/*-- CH: RESTRICT: Channels restrictions status register ------------------------------------------------------*/
typedef struct {
  uint32_t RD_ALLOWFIFO           :1;                                /*!< Read start address does not restrict burst size */
  uint32_t WR_ALLOWFIFO           :1;                                /*!< Write start address does not restrict burst size */
  uint32_t ALLOW_FIFO             :1;                                /*!< Burst size can equal data buffer size */
  uint32_t ALLOW_FBURST           :1;                                /*!< Maximum bursts of 16 strobes can be used */
  uint32_t ALLOW_JBURST           :1;                                /*!< Joint bursts are currently active */
  uint32_t RD_OUTSTAND            :1;                                /*!< Read outstanding is currently active */
  uint32_t WR_OUTSTAND            :1;                                /*!< Write outstanding is currently active */
  uint32_t NONALIGN               :1;                                /*!< Block configuration is not aligned */
  uint32_t SIMPLE_STAT            :1;                                /*!< Configuration is aligned and perepherals are not used */
} _DMA_CH_RESTRICT_bits;

/* Bit field positions: */
#define DMA_CH_RESTRICT_RD_ALLOWFIFO_Pos       0                     /*!< Read start address does not restrict burst size */
#define DMA_CH_RESTRICT_WR_ALLOWFIFO_Pos       1                     /*!< Write start address does not restrict burst size */
#define DMA_CH_RESTRICT_ALLOW_FIFO_Pos        2                      /*!< Burst size can equal data buffer size */
#define DMA_CH_RESTRICT_ALLOW_FBURST_Pos       3                     /*!< Maximum bursts of 16 strobes can be used */
#define DMA_CH_RESTRICT_ALLOW_JBURST_Pos       4                     /*!< Joint bursts are currently active */
#define DMA_CH_RESTRICT_RD_OUTSTAND_Pos       5                      /*!< Read outstanding is currently active */
#define DMA_CH_RESTRICT_WR_OUTSTAND_Pos       6                      /*!< Write outstanding is currently active */
#define DMA_CH_RESTRICT_NONALIGN_Pos          7                      /*!< Block configuration is not aligned */
#define DMA_CH_RESTRICT_SIMPLE_STAT_Pos       8                      /*!< Configuration is aligned and perepherals are not used */

/* Bit field masks: */
#define DMA_CH_RESTRICT_RD_ALLOWFIFO_Msk       0x00000001UL          /*!< Read start address does not restrict burst size */
#define DMA_CH_RESTRICT_WR_ALLOWFIFO_Msk       0x00000002UL          /*!< Write start address does not restrict burst size */
#define DMA_CH_RESTRICT_ALLOW_FIFO_Msk        0x00000004UL           /*!< Burst size can equal data buffer size */
#define DMA_CH_RESTRICT_ALLOW_FBURST_Msk       0x00000008UL          /*!< Maximum bursts of 16 strobes can be used */
#define DMA_CH_RESTRICT_ALLOW_JBURST_Msk       0x00000010UL          /*!< Joint bursts are currently active */
#define DMA_CH_RESTRICT_RD_OUTSTAND_Msk       0x00000020UL           /*!< Read outstanding is currently active */
#define DMA_CH_RESTRICT_WR_OUTSTAND_Msk       0x00000040UL           /*!< Write outstanding is currently active */
#define DMA_CH_RESTRICT_NONALIGN_Msk          0x00000080UL           /*!< Block configuration is not aligned */
#define DMA_CH_RESTRICT_SIMPLE_STAT_Msk       0x00000100UL           /*!< Configuration is aligned and perepherals are not used */

/*-- CH: RDOFFSET: Channels read offset status register -------------------------------------------------------*/
typedef struct {
  uint32_t RD_OFFSET              :16;                               /*!< Offset from the beginning of the buffer */
} _DMA_CH_RDOFFSET_bits;

/* Bit field positions: */
#define DMA_CH_RDOFFSET_RD_OFFSET_Pos         0                      /*!< Offset from the beginning of the buffer */

/* Bit field masks: */
#define DMA_CH_RDOFFSET_RD_OFFSET_Msk         0x0000FFFFUL           /*!< Offset from the beginning of the buffer */

/*-- CH: WROFFSET: Channels write offset status register ------------------------------------------------------*/
typedef struct {
  uint32_t WR_OFFSET              :16;                               /*!< Offset from the beginning of the buffer */
} _DMA_CH_WROFFSET_bits;

/* Bit field positions: */
#define DMA_CH_WROFFSET_WR_OFFSET_Pos         0                      /*!< Offset from the beginning of the buffer */

/* Bit field masks: */
#define DMA_CH_WROFFSET_WR_OFFSET_Msk         0x0000FFFFUL           /*!< Offset from the beginning of the buffer */

/*-- CH: FIFOSTAT: FIFO fullness status register --------------------------------------------------------------*/
typedef struct {
  uint32_t RD_GAP                 :6;                                /*!< Remaining space for channels FIFO for read data */
  uint32_t                        :10;                               /*!< RESERVED */
  uint32_t WR_FULLNESS            :6;                                /*!< Occupied space in channels FIFO by write data */
} _DMA_CH_FIFOSTAT_bits;

/* Bit field positions: */
#define DMA_CH_FIFOSTAT_RD_GAP_Pos            0                      /*!< Remaining space for channels FIFO for read data */
#define DMA_CH_FIFOSTAT_WR_FULLNESS_Pos       16                     /*!< Occupied space in channels FIFO by write data */

/* Bit field masks: */
#define DMA_CH_FIFOSTAT_RD_GAP_Msk            0x0000003FUL           /*!< Remaining space for channels FIFO for read data */
#define DMA_CH_FIFOSTAT_WR_FULLNESS_Msk       0x003F0000UL           /*!< Occupied space in channels FIFO by write data */

/*-- CH: CMD_OUTS: Outstanding commands status register -------------------------------------------------------*/
typedef struct {
  uint32_t RD_CMD_OUTS            :4;                                /*!< Number of channels pending AXI read commands */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t WR_CMD_OUTS            :4;                                /*!< Number of channels pending AXI write commands */
} _DMA_CH_CMD_OUTS_bits;

/* Bit field positions: */
#define DMA_CH_CMD_OUTS_RD_CMD_OUTS_Pos       0                      /*!< Number of channels pending AXI read commands */
#define DMA_CH_CMD_OUTS_WR_CMD_OUTS_Pos       8                      /*!< Number of channels pending AXI write commands */

/* Bit field masks: */
#define DMA_CH_CMD_OUTS_RD_CMD_OUTS_Msk       0x0000000FUL           /*!< Number of channels pending AXI read commands */
#define DMA_CH_CMD_OUTS_WR_CMD_OUTS_Msk       0x00000F00UL           /*!< Number of channels pending AXI write commands */

/*-- CH: CH_ACTIVE: Channel active register -------------------------------------------------------------------*/
typedef struct {
  uint32_t CH_ACTIVE              :1;                                /*!< Channel is currently active */
} _DMA_CH_CH_ACTIVE_bits;

/* Bit field positions: */
#define DMA_CH_CH_ACTIVE_CH_ACTIVE_Pos        0                      /*!< Channel is currently active */

/* Bit field masks: */
#define DMA_CH_CH_ACTIVE_CH_ACTIVE_Msk        0x00000001UL           /*!< Channel is currently active */

/*-- CH: CH_START: Channel start register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t CH_START               :1;                                /*!< Start channel */
} _DMA_CH_CH_START_bits;

/* Bit field positions: */
#define DMA_CH_CH_START_CH_START_Pos          0                      /*!< Start channel */

/* Bit field masks: */
#define DMA_CH_CH_START_CH_START_Msk          0x00000001UL           /*!< Start channel */

/*-- CH: CH_STATUS: Channel status register -------------------------------------------------------------------*/
typedef struct {
  uint32_t CH_RD_ACTIVE           :1;                                /*!< Read on AXI bus is performed */
  uint32_t CH_WR_ACTIVE           :1;                                /*!< Write on AXI bus is performed */
} _DMA_CH_CH_STATUS_bits;

/* Bit field positions: */
#define DMA_CH_CH_STATUS_CH_RD_ACTIVE_Pos       0                    /*!< Read on AXI bus is performed */
#define DMA_CH_CH_STATUS_CH_WR_ACTIVE_Pos       1                    /*!< Write on AXI bus is performed */

/* Bit field masks: */
#define DMA_CH_CH_STATUS_CH_RD_ACTIVE_Msk       0x00000001UL         /*!< Read on AXI bus is performed */
#define DMA_CH_CH_STATUS_CH_WR_ACTIVE_Msk       0x00000002UL         /*!< Write on AXI bus is performed */

/*-- CH: COUNT: Buffer counter status register ----------------------------------------------------------------*/
typedef struct {
  uint32_t BUFF_COUNT             :12;                               /*!< Number of buffers transferred by channel since started */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t INT_COUNT              :5;                                /*!< Number of unserviced end interrupts */
} _DMA_CH_COUNT_bits;

/* Bit field positions: */
#define DMA_CH_COUNT_BUFF_COUNT_Pos           0                      /*!< Number of buffers transferred by channel since started */
#define DMA_CH_COUNT_INT_COUNT_Pos            16                     /*!< Number of unserviced end interrupts */

/* Bit field masks: */
#define DMA_CH_COUNT_BUFF_COUNT_Msk           0x00000FFFUL           /*!< Number of buffers transferred by channel since started */
#define DMA_CH_COUNT_INT_COUNT_Msk            0x001F0000UL           /*!< Number of unserviced end interrupts */

/*-- CH: INT_RAWSTAT: Interrupt raw status register -----------------------------------------------------------*/
typedef struct {
  uint32_t CH_END                 :1;                                /*!< Channel end interrupt */
  uint32_t RD_SLVERR              :1;                                /*!< A read issued by this channel caused an AXI read slave decode error */
  uint32_t WR_SLVERR              :1;                                /*!< A write issued by this channel caused an AXI write slave decode error */
  uint32_t RD_DECERR              :1;                                /*!< A read issued by this channel caused an AXI read decode error */
  uint32_t WR_DECERR              :1;                                /*!< A write issued by this channel caused an AXI write decode error */
  uint32_t OVERFLOW               :1;                                /*!< Data FIFO has been overflowed */
  uint32_t UNDERFLOW              :1;                                /*!< Data FIFO has been underflowed */
  uint32_t TIMEOUT_R              :1;                                /*!< A read issued by this channel caused a timeout on AXI read data bus */
  uint32_t TIMEOUT_AR             :1;                                /*!< A read issued by this channel caused a timeout on AXI read command  bus */
  uint32_t TIMEOUT_B              :1;                                /*!< A write issued by this channel caused a timeout on AXI write response bus */
  uint32_t TIMEOUT_W              :1;                                /*!< A write issued by this channel caused a timeout on AXI write data bus */
  uint32_t TIMEOUT_AW             :1;                                /*!< A write issued by this channel caused a timeout on AXI write command bus */
  uint32_t WDT_TIMEOUT            :1;                                /*!< Cnannel is active but did not start a burst for 2048 cycles */
} _DMA_CH_INT_RAWSTAT_bits;

/* Bit field positions: */
#define DMA_CH_INT_RAWSTAT_CH_END_Pos         0                      /*!< Channel end interrupt */
#define DMA_CH_INT_RAWSTAT_RD_SLVERR_Pos       1                     /*!< A read issued by this channel caused an AXI read slave decode error */
#define DMA_CH_INT_RAWSTAT_WR_SLVERR_Pos       2                     /*!< A write issued by this channel caused an AXI write slave decode error */
#define DMA_CH_INT_RAWSTAT_RD_DECERR_Pos       3                     /*!< A read issued by this channel caused an AXI read decode error */
#define DMA_CH_INT_RAWSTAT_WR_DECERR_Pos       4                     /*!< A write issued by this channel caused an AXI write decode error */
#define DMA_CH_INT_RAWSTAT_OVERFLOW_Pos       5                      /*!< Data FIFO has been overflowed */
#define DMA_CH_INT_RAWSTAT_UNDERFLOW_Pos       6                     /*!< Data FIFO has been underflowed */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_R_Pos       7                     /*!< A read issued by this channel caused a timeout on AXI read data bus */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_AR_Pos       8                    /*!< A read issued by this channel caused a timeout on AXI read command  bus */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_B_Pos       9                     /*!< A write issued by this channel caused a timeout on AXI write response bus */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_W_Pos       10                    /*!< A write issued by this channel caused a timeout on AXI write data bus */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_AW_Pos       11                   /*!< A write issued by this channel caused a timeout on AXI write command bus */
#define DMA_CH_INT_RAWSTAT_WDT_TIMEOUT_Pos       12                  /*!< Cnannel is active but did not start a burst for 2048 cycles */

/* Bit field masks: */
#define DMA_CH_INT_RAWSTAT_CH_END_Msk         0x00000001UL           /*!< Channel end interrupt */
#define DMA_CH_INT_RAWSTAT_RD_SLVERR_Msk       0x00000002UL          /*!< A read issued by this channel caused an AXI read slave decode error */
#define DMA_CH_INT_RAWSTAT_WR_SLVERR_Msk       0x00000004UL          /*!< A write issued by this channel caused an AXI write slave decode error */
#define DMA_CH_INT_RAWSTAT_RD_DECERR_Msk       0x00000008UL          /*!< A read issued by this channel caused an AXI read decode error */
#define DMA_CH_INT_RAWSTAT_WR_DECERR_Msk       0x00000010UL          /*!< A write issued by this channel caused an AXI write decode error */
#define DMA_CH_INT_RAWSTAT_OVERFLOW_Msk       0x00000020UL           /*!< Data FIFO has been overflowed */
#define DMA_CH_INT_RAWSTAT_UNDERFLOW_Msk       0x00000040UL          /*!< Data FIFO has been underflowed */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_R_Msk       0x00000080UL          /*!< A read issued by this channel caused a timeout on AXI read data bus */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_AR_Msk       0x00000100UL         /*!< A read issued by this channel caused a timeout on AXI read command  bus */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_B_Msk       0x00000200UL          /*!< A write issued by this channel caused a timeout on AXI write response bus */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_W_Msk       0x00000400UL          /*!< A write issued by this channel caused a timeout on AXI write data bus */
#define DMA_CH_INT_RAWSTAT_TIMEOUT_AW_Msk       0x00000800UL         /*!< A write issued by this channel caused a timeout on AXI write command bus */
#define DMA_CH_INT_RAWSTAT_WDT_TIMEOUT_Msk       0x00001000UL         /*!< Cnannel is active but did not start a burst for 2048 cycles */

/*-- CH: INT_CLEAR: Interrupt clear register ------------------------------------------------------------------*/
typedef struct {
  uint32_t CH_END                 :1;                                /*!< Channel end interrupt */
  uint32_t RD_SLVERR              :1;                                /*!< A read issued by this channel caused an AXI read slave decode error */
  uint32_t WR_SLVERR              :1;                                /*!< A write issued by this channel caused an AXI write slave decode error */
  uint32_t RD_DECERR              :1;                                /*!< A read issued by this channel caused an AXI read decode error */
  uint32_t WR_DECERR              :1;                                /*!< A write issued by this channel caused an AXI write decode error */
  uint32_t OVERFLOW               :1;                                /*!< Data FIFO has been overflowed */
  uint32_t UNDERFLOW              :1;                                /*!< Data FIFO has been underflowed */
  uint32_t TIMEOUT_R              :1;                                /*!< A read issued by this channel caused a timeout on AXI read data bus */
  uint32_t TIMEOUT_AR             :1;                                /*!< A read issued by this channel caused a timeout on AXI read command  bus */
  uint32_t TIMEOUT_B              :1;                                /*!< A write issued by this channel caused a timeout on AXI write response bus */
  uint32_t TIMEOUT_W              :1;                                /*!< A write issued by this channel caused a timeout on AXI write data bus */
  uint32_t TIMEOUT_AW             :1;                                /*!< A write issued by this channel caused a timeout on AXI write command bus */
  uint32_t WDT_TIMEOUT            :1;                                /*!< Cnannel is active but did not start a burst for 2048 cycles */
} _DMA_CH_INT_CLEAR_bits;

/* Bit field positions: */
#define DMA_CH_INT_CLEAR_CH_END_Pos           0                      /*!< Channel end interrupt */
#define DMA_CH_INT_CLEAR_RD_SLVERR_Pos        1                      /*!< A read issued by this channel caused an AXI read slave decode error */
#define DMA_CH_INT_CLEAR_WR_SLVERR_Pos        2                      /*!< A write issued by this channel caused an AXI write slave decode error */
#define DMA_CH_INT_CLEAR_RD_DECERR_Pos        3                      /*!< A read issued by this channel caused an AXI read decode error */
#define DMA_CH_INT_CLEAR_WR_DECERR_Pos        4                      /*!< A write issued by this channel caused an AXI write decode error */
#define DMA_CH_INT_CLEAR_OVERFLOW_Pos         5                      /*!< Data FIFO has been overflowed */
#define DMA_CH_INT_CLEAR_UNDERFLOW_Pos        6                      /*!< Data FIFO has been underflowed */
#define DMA_CH_INT_CLEAR_TIMEOUT_R_Pos        7                      /*!< A read issued by this channel caused a timeout on AXI read data bus */
#define DMA_CH_INT_CLEAR_TIMEOUT_AR_Pos       8                      /*!< A read issued by this channel caused a timeout on AXI read command  bus */
#define DMA_CH_INT_CLEAR_TIMEOUT_B_Pos        9                      /*!< A write issued by this channel caused a timeout on AXI write response bus */
#define DMA_CH_INT_CLEAR_TIMEOUT_W_Pos        10                     /*!< A write issued by this channel caused a timeout on AXI write data bus */
#define DMA_CH_INT_CLEAR_TIMEOUT_AW_Pos       11                     /*!< A write issued by this channel caused a timeout on AXI write command bus */
#define DMA_CH_INT_CLEAR_WDT_TIMEOUT_Pos       12                    /*!< Cnannel is active but did not start a burst for 2048 cycles */

/* Bit field masks: */
#define DMA_CH_INT_CLEAR_CH_END_Msk           0x00000001UL           /*!< Channel end interrupt */
#define DMA_CH_INT_CLEAR_RD_SLVERR_Msk        0x00000002UL           /*!< A read issued by this channel caused an AXI read slave decode error */
#define DMA_CH_INT_CLEAR_WR_SLVERR_Msk        0x00000004UL           /*!< A write issued by this channel caused an AXI write slave decode error */
#define DMA_CH_INT_CLEAR_RD_DECERR_Msk        0x00000008UL           /*!< A read issued by this channel caused an AXI read decode error */
#define DMA_CH_INT_CLEAR_WR_DECERR_Msk        0x00000010UL           /*!< A write issued by this channel caused an AXI write decode error */
#define DMA_CH_INT_CLEAR_OVERFLOW_Msk         0x00000020UL           /*!< Data FIFO has been overflowed */
#define DMA_CH_INT_CLEAR_UNDERFLOW_Msk        0x00000040UL           /*!< Data FIFO has been underflowed */
#define DMA_CH_INT_CLEAR_TIMEOUT_R_Msk        0x00000080UL           /*!< A read issued by this channel caused a timeout on AXI read data bus */
#define DMA_CH_INT_CLEAR_TIMEOUT_AR_Msk       0x00000100UL           /*!< A read issued by this channel caused a timeout on AXI read command  bus */
#define DMA_CH_INT_CLEAR_TIMEOUT_B_Msk        0x00000200UL           /*!< A write issued by this channel caused a timeout on AXI write response bus */
#define DMA_CH_INT_CLEAR_TIMEOUT_W_Msk        0x00000400UL           /*!< A write issued by this channel caused a timeout on AXI write data bus */
#define DMA_CH_INT_CLEAR_TIMEOUT_AW_Msk       0x00000800UL           /*!< A write issued by this channel caused a timeout on AXI write command bus */
#define DMA_CH_INT_CLEAR_WDT_TIMEOUT_Msk       0x00001000UL          /*!< Cnannel is active but did not start a burst for 2048 cycles */

/*-- CH: INT_ENABLE: Interrupt enable register ----------------------------------------------------------------*/
typedef struct {
  uint32_t CH_END                 :1;                                /*!< Channel end interrupt */
  uint32_t RD_SLVERR              :1;                                /*!< A read issued by this channel caused an AXI read slave decode error */
  uint32_t WR_SLVERR              :1;                                /*!< A write issued by this channel caused an AXI write slave decode error */
  uint32_t RD_DECERR              :1;                                /*!< A read issued by this channel caused an AXI read decode error */
  uint32_t WR_DECERR              :1;                                /*!< A write issued by this channel caused an AXI write decode error */
  uint32_t OVERFLOW               :1;                                /*!< Data FIFO has been overflowed */
  uint32_t UNDERFLOW              :1;                                /*!< Data FIFO has been underflowed */
  uint32_t TIMEOUT_R              :1;                                /*!< A read issued by this channel caused a timeout on AXI read data bus */
  uint32_t TIMEOUT_AR             :1;                                /*!< A read issued by this channel caused a timeout on AXI read command  bus */
  uint32_t TIMEOUT_B              :1;                                /*!< A write issued by this channel caused a timeout on AXI write response bus */
  uint32_t TIMEOUT_W              :1;                                /*!< A write issued by this channel caused a timeout on AXI write data bus */
  uint32_t TIMEOUT_AW             :1;                                /*!< A write issued by this channel caused a timeout on AXI write command bus */
  uint32_t WDT_TIMEOUT            :1;                                /*!< Cnannel is active but did not start a burst for 2048 cycles */
} _DMA_CH_INT_ENABLE_bits;

/* Bit field positions: */
#define DMA_CH_INT_ENABLE_CH_END_Pos          0                      /*!< Channel end interrupt */
#define DMA_CH_INT_ENABLE_RD_SLVERR_Pos       1                      /*!< A read issued by this channel caused an AXI read slave decode error */
#define DMA_CH_INT_ENABLE_WR_SLVERR_Pos       2                      /*!< A write issued by this channel caused an AXI write slave decode error */
#define DMA_CH_INT_ENABLE_RD_DECERR_Pos       3                      /*!< A read issued by this channel caused an AXI read decode error */
#define DMA_CH_INT_ENABLE_WR_DECERR_Pos       4                      /*!< A write issued by this channel caused an AXI write decode error */
#define DMA_CH_INT_ENABLE_OVERFLOW_Pos        5                      /*!< Data FIFO has been overflowed */
#define DMA_CH_INT_ENABLE_UNDERFLOW_Pos       6                      /*!< Data FIFO has been underflowed */
#define DMA_CH_INT_ENABLE_TIMEOUT_R_Pos       7                      /*!< A read issued by this channel caused a timeout on AXI read data bus */
#define DMA_CH_INT_ENABLE_TIMEOUT_AR_Pos       8                     /*!< A read issued by this channel caused a timeout on AXI read command  bus */
#define DMA_CH_INT_ENABLE_TIMEOUT_B_Pos       9                      /*!< A write issued by this channel caused a timeout on AXI write response bus */
#define DMA_CH_INT_ENABLE_TIMEOUT_W_Pos       10                     /*!< A write issued by this channel caused a timeout on AXI write data bus */
#define DMA_CH_INT_ENABLE_TIMEOUT_AW_Pos       11                    /*!< A write issued by this channel caused a timeout on AXI write command bus */
#define DMA_CH_INT_ENABLE_WDT_TIMEOUT_Pos       12                   /*!< Cnannel is active but did not start a burst for 2048 cycles */

/* Bit field masks: */
#define DMA_CH_INT_ENABLE_CH_END_Msk          0x00000001UL           /*!< Channel end interrupt */
#define DMA_CH_INT_ENABLE_RD_SLVERR_Msk       0x00000002UL           /*!< A read issued by this channel caused an AXI read slave decode error */
#define DMA_CH_INT_ENABLE_WR_SLVERR_Msk       0x00000004UL           /*!< A write issued by this channel caused an AXI write slave decode error */
#define DMA_CH_INT_ENABLE_RD_DECERR_Msk       0x00000008UL           /*!< A read issued by this channel caused an AXI read decode error */
#define DMA_CH_INT_ENABLE_WR_DECERR_Msk       0x00000010UL           /*!< A write issued by this channel caused an AXI write decode error */
#define DMA_CH_INT_ENABLE_OVERFLOW_Msk        0x00000020UL           /*!< Data FIFO has been overflowed */
#define DMA_CH_INT_ENABLE_UNDERFLOW_Msk       0x00000040UL           /*!< Data FIFO has been underflowed */
#define DMA_CH_INT_ENABLE_TIMEOUT_R_Msk       0x00000080UL           /*!< A read issued by this channel caused a timeout on AXI read data bus */
#define DMA_CH_INT_ENABLE_TIMEOUT_AR_Msk       0x00000100UL          /*!< A read issued by this channel caused a timeout on AXI read command  bus */
#define DMA_CH_INT_ENABLE_TIMEOUT_B_Msk       0x00000200UL           /*!< A write issued by this channel caused a timeout on AXI write response bus */
#define DMA_CH_INT_ENABLE_TIMEOUT_W_Msk       0x00000400UL           /*!< A write issued by this channel caused a timeout on AXI write data bus */
#define DMA_CH_INT_ENABLE_TIMEOUT_AW_Msk       0x00000800UL          /*!< A write issued by this channel caused a timeout on AXI write command bus */
#define DMA_CH_INT_ENABLE_WDT_TIMEOUT_Msk       0x00001000UL         /*!< Cnannel is active but did not start a burst for 2048 cycles */

/*-- CH: INT_STATUS: Interrupt status -------------------------------------------------------------------------*/
typedef struct {
  uint32_t CH_END                 :1;                                /*!< Channel end interrupt */
  uint32_t RD_SLVERR              :1;                                /*!< A read issued by this channel caused an AXI read slave decode error */
  uint32_t WR_SLVERR              :1;                                /*!< A write issued by this channel caused an AXI write slave decode error */
  uint32_t RD_DECERR              :1;                                /*!< A read issued by this channel caused an AXI read decode error */
  uint32_t WR_DECERR              :1;                                /*!< A write issued by this channel caused an AXI write decode error */
  uint32_t OVERFLOW               :1;                                /*!< Data FIFO has been overflowed */
  uint32_t UNDERFLOW              :1;                                /*!< Data FIFO has been underflowed */
  uint32_t TIMEOUT_R              :1;                                /*!< A read issued by this channel caused a timeout on AXI read data bus */
  uint32_t TIMEOUT_AR             :1;                                /*!< A read issued by this channel caused a timeout on AXI read command  bus */
  uint32_t TIMEOUT_B              :1;                                /*!< A write issued by this channel caused a timeout on AXI write response bus */
  uint32_t TIMEOUT_W              :1;                                /*!< A write issued by this channel caused a timeout on AXI write data bus */
  uint32_t TIMEOUT_AW             :1;                                /*!< A write issued by this channel caused a timeout on AXI write command bus */
  uint32_t WDT_TIMEOUT            :1;                                /*!< Cnannel is active but did not start a burst for 2048 cycles */
} _DMA_CH_INT_STATUS_bits;

/* Bit field positions: */
#define DMA_CH_INT_STATUS_CH_END_Pos          0                      /*!< Channel end interrupt */
#define DMA_CH_INT_STATUS_RD_SLVERR_Pos       1                      /*!< A read issued by this channel caused an AXI read slave decode error */
#define DMA_CH_INT_STATUS_WR_SLVERR_Pos       2                      /*!< A write issued by this channel caused an AXI write slave decode error */
#define DMA_CH_INT_STATUS_RD_DECERR_Pos       3                      /*!< A read issued by this channel caused an AXI read decode error */
#define DMA_CH_INT_STATUS_WR_DECERR_Pos       4                      /*!< A write issued by this channel caused an AXI write decode error */
#define DMA_CH_INT_STATUS_OVERFLOW_Pos        5                      /*!< Data FIFO has been overflowed */
#define DMA_CH_INT_STATUS_UNDERFLOW_Pos       6                      /*!< Data FIFO has been underflowed */
#define DMA_CH_INT_STATUS_TIMEOUT_R_Pos       7                      /*!< A read issued by this channel caused a timeout on AXI read data bus */
#define DMA_CH_INT_STATUS_TIMEOUT_AR_Pos       8                     /*!< A read issued by this channel caused a timeout on AXI read command  bus */
#define DMA_CH_INT_STATUS_TIMEOUT_B_Pos       9                      /*!< A write issued by this channel caused a timeout on AXI write response bus */
#define DMA_CH_INT_STATUS_TIMEOUT_W_Pos       10                     /*!< A write issued by this channel caused a timeout on AXI write data bus */
#define DMA_CH_INT_STATUS_TIMEOUT_AW_Pos       11                    /*!< A write issued by this channel caused a timeout on AXI write command bus */
#define DMA_CH_INT_STATUS_WDT_TIMEOUT_Pos       12                   /*!< Cnannel is active but did not start a burst for 2048 cycles */

/* Bit field masks: */
#define DMA_CH_INT_STATUS_CH_END_Msk          0x00000001UL           /*!< Channel end interrupt */
#define DMA_CH_INT_STATUS_RD_SLVERR_Msk       0x00000002UL           /*!< A read issued by this channel caused an AXI read slave decode error */
#define DMA_CH_INT_STATUS_WR_SLVERR_Msk       0x00000004UL           /*!< A write issued by this channel caused an AXI write slave decode error */
#define DMA_CH_INT_STATUS_RD_DECERR_Msk       0x00000008UL           /*!< A read issued by this channel caused an AXI read decode error */
#define DMA_CH_INT_STATUS_WR_DECERR_Msk       0x00000010UL           /*!< A write issued by this channel caused an AXI write decode error */
#define DMA_CH_INT_STATUS_OVERFLOW_Msk        0x00000020UL           /*!< Data FIFO has been overflowed */
#define DMA_CH_INT_STATUS_UNDERFLOW_Msk       0x00000040UL           /*!< Data FIFO has been underflowed */
#define DMA_CH_INT_STATUS_TIMEOUT_R_Msk       0x00000080UL           /*!< A read issued by this channel caused a timeout on AXI read data bus */
#define DMA_CH_INT_STATUS_TIMEOUT_AR_Msk       0x00000100UL          /*!< A read issued by this channel caused a timeout on AXI read command  bus */
#define DMA_CH_INT_STATUS_TIMEOUT_B_Msk       0x00000200UL           /*!< A write issued by this channel caused a timeout on AXI write response bus */
#define DMA_CH_INT_STATUS_TIMEOUT_W_Msk       0x00000400UL           /*!< A write issued by this channel caused a timeout on AXI write data bus */
#define DMA_CH_INT_STATUS_TIMEOUT_AW_Msk       0x00000800UL          /*!< A write issued by this channel caused a timeout on AXI write command bus */
#define DMA_CH_INT_STATUS_WDT_TIMEOUT_Msk       0x00001000UL         /*!< Cnannel is active but did not start a burst for 2048 cycles */

/*-- CH: ERR_STOP: Channel error stop condition register ------------------------------------------------------*/
typedef struct {
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t RD_SLVERR              :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t WR_SLVERR              :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t RD_DECERR              :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t WR_DECERR              :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t OVERFLOW               :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t UNDERFLOW              :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t TIMEOUT_R              :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t TIMEOUT_AR             :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t TIMEOUT_B              :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t TIMEOUT_W              :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t TIMEOUT_AW             :1;                                /*!< If set, stop read and write transactions when this condition occurs */
  uint32_t WDT_TIMEOUT            :1;                                /*!< If set, stop read and write transactions when this condition occurs */
} _DMA_CH_ERR_STOP_bits;

/* Bit field positions: */
#define DMA_CH_ERR_STOP_RD_SLVERR_Pos         1                      /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_WR_SLVERR_Pos         2                      /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_RD_DECERR_Pos         3                      /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_WR_DECERR_Pos         4                      /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_OVERFLOW_Pos          5                      /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_UNDERFLOW_Pos         6                      /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_R_Pos         7                      /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_AR_Pos        8                      /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_B_Pos         9                      /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_W_Pos         10                     /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_AW_Pos        11                     /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_WDT_TIMEOUT_Pos       12                     /*!< If set, stop read and write transactions when this condition occurs */

/* Bit field masks: */
#define DMA_CH_ERR_STOP_RD_SLVERR_Msk         0x00000002UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_WR_SLVERR_Msk         0x00000004UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_RD_DECERR_Msk         0x00000008UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_WR_DECERR_Msk         0x00000010UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_OVERFLOW_Msk          0x00000020UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_UNDERFLOW_Msk         0x00000040UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_R_Msk         0x00000080UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_AR_Msk        0x00000100UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_B_Msk         0x00000200UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_W_Msk         0x00000400UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_TIMEOUT_AW_Msk        0x00000800UL           /*!< If set, stop read and write transactions when this condition occurs */
#define DMA_CH_ERR_STOP_WDT_TIMEOUT_Msk       0x00001000UL           /*!< If set, stop read and write transactions when this condition occurs */

/*-- CH: ERR_RD_ADDR: Erroneous read transaction address register ---------------------------------------------*/
typedef struct {
  uint32_t ERR_ADDR               :32;                               /*!< First encountered erroneous address in read transaction */
} _DMA_CH_ERR_RD_ADDR_bits;

/* Bit field positions: */
#define DMA_CH_ERR_RD_ADDR_ERR_ADDR_Pos       0                      /*!< First encountered erroneous address in read transaction */

/* Bit field masks: */
#define DMA_CH_ERR_RD_ADDR_ERR_ADDR_Msk       0xFFFFFFFFUL           /*!< First encountered erroneous address in read transaction */

/*-- CH: ERR_WR_ADDR: Erroneous write transaction address register --------------------------------------------*/
typedef struct {
  uint32_t ERR_ADDR               :32;                               /*!< First encountered erroneous address in write transaction */
} _DMA_CH_ERR_WR_ADDR_bits;

/* Bit field positions: */
#define DMA_CH_ERR_WR_ADDR_ERR_ADDR_Pos       0                      /*!< First encountered erroneous address in write transaction */

/* Bit field masks: */
#define DMA_CH_ERR_WR_ADDR_ERR_ADDR_Msk       0xFFFFFFFFUL           /*!< First encountered erroneous address in write transaction */

/*--  CH_INTSTAT: Status register indicating which channels caused an interrupt on INT[7:0] --------------------------------*/
typedef struct {
  uint32_t CH0                    :1;                                /*!< Interrupt caused by Channel 0 */
  uint32_t CH1                    :1;                                /*!< Interrupt caused by Channel 1 */
  uint32_t CH2                    :1;                                /*!< Interrupt caused by Channel 2 */
  uint32_t CH3                    :1;                                /*!< Interrupt caused by Channel 3 */
  uint32_t CH4                    :1;                                /*!< Interrupt caused by Channel 4 */
  uint32_t CH5                    :1;                                /*!< Interrupt caused by Channel 5 */
  uint32_t CH6                    :1;                                /*!< Interrupt caused by Channel 6 */
  uint32_t CH7                    :1;                                /*!< Interrupt caused by Channel 7 */
} _DMA_CH_INTSTAT_bits;

/* Bit field positions: */
#define DMA_CH_INTSTAT_CH0_Pos                0                      /*!< Interrupt caused by Channel 0 */
#define DMA_CH_INTSTAT_CH1_Pos                1                      /*!< Interrupt caused by Channel 1 */
#define DMA_CH_INTSTAT_CH2_Pos                2                      /*!< Interrupt caused by Channel 2 */
#define DMA_CH_INTSTAT_CH3_Pos                3                      /*!< Interrupt caused by Channel 3 */
#define DMA_CH_INTSTAT_CH4_Pos                4                      /*!< Interrupt caused by Channel 4 */
#define DMA_CH_INTSTAT_CH5_Pos                5                      /*!< Interrupt caused by Channel 5 */
#define DMA_CH_INTSTAT_CH6_Pos                6                      /*!< Interrupt caused by Channel 6 */
#define DMA_CH_INTSTAT_CH7_Pos                7                      /*!< Interrupt caused by Channel 7 */

/* Bit field masks: */
#define DMA_CH_INTSTAT_CH0_Msk                0x00000001UL           /*!< Interrupt caused by Channel 0 */
#define DMA_CH_INTSTAT_CH1_Msk                0x00000002UL           /*!< Interrupt caused by Channel 1 */
#define DMA_CH_INTSTAT_CH2_Msk                0x00000004UL           /*!< Interrupt caused by Channel 2 */
#define DMA_CH_INTSTAT_CH3_Msk                0x00000008UL           /*!< Interrupt caused by Channel 3 */
#define DMA_CH_INTSTAT_CH4_Msk                0x00000010UL           /*!< Interrupt caused by Channel 4 */
#define DMA_CH_INTSTAT_CH5_Msk                0x00000020UL           /*!< Interrupt caused by Channel 5 */
#define DMA_CH_INTSTAT_CH6_Msk                0x00000040UL           /*!< Interrupt caused by Channel 6 */
#define DMA_CH_INTSTAT_CH7_Msk                0x00000080UL           /*!< Interrupt caused by Channel 7 */

/*--  CONTROL: DMA Core control arbitrage and mode ------------------------------------------------------------*/
typedef struct {
  uint32_t JOINT_MODE             :1;                                /*!< Joint mode select */
} _DMA_CONTROL_bits;

/* Bit field positions: */
#define DMA_CONTROL_JOINT_MODE_Pos            0                      /*!< Joint mode select */

/* Bit field masks: */
#define DMA_CONTROL_JOINT_MODE_Msk            0x00000001UL           /*!< Joint mode select */

/*--  RD_PRIORITY: DMA Core read priority channels ------------------------------------------------------------*/
typedef struct {
  uint32_t CH0                    :1;                                /*!< Set the priority of channel 0 */
  uint32_t CH1                    :1;                                /*!< Set the priority of channel 1 */
  uint32_t CH2                    :1;                                /*!< Set the priority of channel 2 */
  uint32_t CH3                    :1;                                /*!< Set the priority of channel 3 */
  uint32_t CH4                    :1;                                /*!< Set the priority of channel 4 */
  uint32_t CH5                    :1;                                /*!< Set the priority of channel 5 */
  uint32_t CH6                    :1;                                /*!< Set the priority of channel 6 */
  uint32_t CH7                    :1;                                /*!< Set the priority of channel 7 */
} _DMA_RD_PRIORITY_bits;

/* Bit field positions: */
#define DMA_RD_PRIORITY_CH0_Pos               0                      /*!< Set the priority of channel 0 */
#define DMA_RD_PRIORITY_CH1_Pos               1                      /*!< Set the priority of channel 1 */
#define DMA_RD_PRIORITY_CH2_Pos               2                      /*!< Set the priority of channel 2 */
#define DMA_RD_PRIORITY_CH3_Pos               3                      /*!< Set the priority of channel 3 */
#define DMA_RD_PRIORITY_CH4_Pos               4                      /*!< Set the priority of channel 4 */
#define DMA_RD_PRIORITY_CH5_Pos               5                      /*!< Set the priority of channel 5 */
#define DMA_RD_PRIORITY_CH6_Pos               6                      /*!< Set the priority of channel 6 */
#define DMA_RD_PRIORITY_CH7_Pos               7                      /*!< Set the priority of channel 7 */

/* Bit field masks: */
#define DMA_RD_PRIORITY_CH0_Msk               0x00000001UL           /*!< Set the priority of channel 0 */
#define DMA_RD_PRIORITY_CH1_Msk               0x00000002UL           /*!< Set the priority of channel 1 */
#define DMA_RD_PRIORITY_CH2_Msk               0x00000004UL           /*!< Set the priority of channel 2 */
#define DMA_RD_PRIORITY_CH3_Msk               0x00000008UL           /*!< Set the priority of channel 3 */
#define DMA_RD_PRIORITY_CH4_Msk               0x00000010UL           /*!< Set the priority of channel 4 */
#define DMA_RD_PRIORITY_CH5_Msk               0x00000020UL           /*!< Set the priority of channel 5 */
#define DMA_RD_PRIORITY_CH6_Msk               0x00000040UL           /*!< Set the priority of channel 6 */
#define DMA_RD_PRIORITY_CH7_Msk               0x00000080UL           /*!< Set the priority of channel 7 */

/*--  WR_PRIORITY: DMA Core read priority channels ------------------------------------------------------------*/
typedef struct {
  uint32_t CH0                    :1;                                /*!< Set the priority of channel 0 */
  uint32_t CH1                    :1;                                /*!< Set the priority of channel 1 */
  uint32_t CH2                    :1;                                /*!< Set the priority of channel 2 */
  uint32_t CH3                    :1;                                /*!< Set the priority of channel 3 */
  uint32_t CH4                    :1;                                /*!< Set the priority of channel 4 */
  uint32_t CH5                    :1;                                /*!< Set the priority of channel 5 */
  uint32_t CH6                    :1;                                /*!< Set the priority of channel 6 */
  uint32_t CH7                    :1;                                /*!< Set the priority of channel 7 */
} _DMA_WR_PRIORITY_bits;

/* Bit field positions: */
#define DMA_WR_PRIORITY_CH0_Pos               0                      /*!< Set the priority of channel 0 */
#define DMA_WR_PRIORITY_CH1_Pos               1                      /*!< Set the priority of channel 1 */
#define DMA_WR_PRIORITY_CH2_Pos               2                      /*!< Set the priority of channel 2 */
#define DMA_WR_PRIORITY_CH3_Pos               3                      /*!< Set the priority of channel 3 */
#define DMA_WR_PRIORITY_CH4_Pos               4                      /*!< Set the priority of channel 4 */
#define DMA_WR_PRIORITY_CH5_Pos               5                      /*!< Set the priority of channel 5 */
#define DMA_WR_PRIORITY_CH6_Pos               6                      /*!< Set the priority of channel 6 */
#define DMA_WR_PRIORITY_CH7_Pos               7                      /*!< Set the priority of channel 7 */

/* Bit field masks: */
#define DMA_WR_PRIORITY_CH0_Msk               0x00000001UL           /*!< Set the priority of channel 0 */
#define DMA_WR_PRIORITY_CH1_Msk               0x00000002UL           /*!< Set the priority of channel 1 */
#define DMA_WR_PRIORITY_CH2_Msk               0x00000004UL           /*!< Set the priority of channel 2 */
#define DMA_WR_PRIORITY_CH3_Msk               0x00000008UL           /*!< Set the priority of channel 3 */
#define DMA_WR_PRIORITY_CH4_Msk               0x00000010UL           /*!< Set the priority of channel 4 */
#define DMA_WR_PRIORITY_CH5_Msk               0x00000020UL           /*!< Set the priority of channel 5 */
#define DMA_WR_PRIORITY_CH6_Msk               0x00000040UL           /*!< Set the priority of channel 6 */
#define DMA_WR_PRIORITY_CH7_Msk               0x00000080UL           /*!< Set the priority of channel 7 */

/*--  CH_START: DMA channel start -----------------------------------------------------------------------------*/
typedef struct {
  uint32_t CH0                    :1;                                /*!< Start Channel 0 */
  uint32_t CH1                    :1;                                /*!< Start Channel 1 */
  uint32_t CH2                    :1;                                /*!< Start Channel 2 */
  uint32_t CH3                    :1;                                /*!< Start Channel 3 */
  uint32_t CH4                    :1;                                /*!< Start Channel 4 */
  uint32_t CH5                    :1;                                /*!< Start Channel 5 */
  uint32_t CH6                    :1;                                /*!< Start Channel 6 */
  uint32_t CH7                    :1;                                /*!< Start Channel 7 */
} _DMA_CH_START_bits;

/* Bit field positions: */
#define DMA_CH_START_CH0_Pos                  0                      /*!< Start Channel 0 */
#define DMA_CH_START_CH1_Pos                  1                      /*!< Start Channel 1 */
#define DMA_CH_START_CH2_Pos                  2                      /*!< Start Channel 2 */
#define DMA_CH_START_CH3_Pos                  3                      /*!< Start Channel 3 */
#define DMA_CH_START_CH4_Pos                  4                      /*!< Start Channel 4 */
#define DMA_CH_START_CH5_Pos                  5                      /*!< Start Channel 5 */
#define DMA_CH_START_CH6_Pos                  6                      /*!< Start Channel 6 */
#define DMA_CH_START_CH7_Pos                  7                      /*!< Start Channel 7 */

/* Bit field masks: */
#define DMA_CH_START_CH0_Msk                  0x00000001UL           /*!< Start Channel 0 */
#define DMA_CH_START_CH1_Msk                  0x00000002UL           /*!< Start Channel 1 */
#define DMA_CH_START_CH2_Msk                  0x00000004UL           /*!< Start Channel 2 */
#define DMA_CH_START_CH3_Msk                  0x00000008UL           /*!< Start Channel 3 */
#define DMA_CH_START_CH4_Msk                  0x00000010UL           /*!< Start Channel 4 */
#define DMA_CH_START_CH5_Msk                  0x00000020UL           /*!< Start Channel 5 */
#define DMA_CH_START_CH6_Msk                  0x00000040UL           /*!< Start Channel 6 */
#define DMA_CH_START_CH7_Msk                  0x00000080UL           /*!< Start Channel 7 */

/*--  CH_ENABLE: DMA channel enable ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t CH0                    :1;                                /*!< Enable Channel 0 */
  uint32_t CH1                    :1;                                /*!< Enable Channel 1 */
  uint32_t CH2                    :1;                                /*!< Enable Channel 2 */
  uint32_t CH3                    :1;                                /*!< Enable Channel 3 */
  uint32_t CH4                    :1;                                /*!< Enable Channel 4 */
  uint32_t CH5                    :1;                                /*!< Enable Channel 5 */
  uint32_t CH6                    :1;                                /*!< Enable Channel 6 */
  uint32_t CH7                    :1;                                /*!< Enable Channel 7 */
} _DMA_CH_ENABLE_bits;

/* Bit field positions: */
#define DMA_CH_ENABLE_CH0_Pos                 0                      /*!< Enable Channel 0 */
#define DMA_CH_ENABLE_CH1_Pos                 1                      /*!< Enable Channel 1 */
#define DMA_CH_ENABLE_CH2_Pos                 2                      /*!< Enable Channel 2 */
#define DMA_CH_ENABLE_CH3_Pos                 3                      /*!< Enable Channel 3 */
#define DMA_CH_ENABLE_CH4_Pos                 4                      /*!< Enable Channel 4 */
#define DMA_CH_ENABLE_CH5_Pos                 5                      /*!< Enable Channel 5 */
#define DMA_CH_ENABLE_CH6_Pos                 6                      /*!< Enable Channel 6 */
#define DMA_CH_ENABLE_CH7_Pos                 7                      /*!< Enable Channel 7 */

/* Bit field masks: */
#define DMA_CH_ENABLE_CH0_Msk                 0x00000001UL           /*!< Enable Channel 0 */
#define DMA_CH_ENABLE_CH1_Msk                 0x00000002UL           /*!< Enable Channel 1 */
#define DMA_CH_ENABLE_CH2_Msk                 0x00000004UL           /*!< Enable Channel 2 */
#define DMA_CH_ENABLE_CH3_Msk                 0x00000008UL           /*!< Enable Channel 3 */
#define DMA_CH_ENABLE_CH4_Msk                 0x00000010UL           /*!< Enable Channel 4 */
#define DMA_CH_ENABLE_CH5_Msk                 0x00000020UL           /*!< Enable Channel 5 */
#define DMA_CH_ENABLE_CH6_Msk                 0x00000040UL           /*!< Enable Channel 6 */
#define DMA_CH_ENABLE_CH7_Msk                 0x00000080UL           /*!< Enable Channel 7 */

/*--  IDLE: Idle indication register --------------------------------------------------------------------------*/
typedef struct {
  uint32_t IDLE                   :1;                                /*!< IDLE Status */
} _DMA_IDLE_bits;

/* Bit field positions: */
#define DMA_IDLE_IDLE_Pos                     0                      /*!< IDLE Status */

/* Bit field masks: */
#define DMA_IDLE_IDLE_Msk                     0x00000001UL           /*!< IDLE Status */

/*--  PER_RX_CTRL: Direct control of peripheral RX request ----------------------------------------------------*/
typedef struct {
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t RXREQ                  :17;                               /*!< Read requests {[unused] DAC, GPIOB, GPIOA, ADC Seq 3..0, TMR 4..0, UART 1..0, SPI 2..0} */
} _DMA_PER_RX_CTRL_bits;

/* Bit field positions: */
#define DMA_PER_RX_CTRL_RXREQ_Pos             1                      /*!< Read requests {[unused] DAC, GPIOB, GPIOA, ADC Seq 3..0, TMR 4..0, UART 1..0, SPI 2..0} */

/* Bit field masks: */
#define DMA_PER_RX_CTRL_RXREQ_Msk             0x0003FFFEUL           /*!< Read requests {[unused] DAC, GPIOB, GPIOA, ADC Seq 3..0, TMR 4..0, UART 1..0, SPI 2..0} */

/*--  PER_RXN_CTRL: Direct control of peripheral RX request (named bits) --------------------------------------*/
typedef struct {
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t RXSPI0                 :1;                                /*!< Read request SPI0 */
  uint32_t RXSPI1                 :1;                                /*!< Read request SPI1 */
  uint32_t RXSPI2                 :1;                                /*!< Read request SPI2 */
  uint32_t RXUART0                :1;                                /*!< Read request UART0 */
  uint32_t RXUART1                :1;                                /*!< Read request UART1 */
  uint32_t RXTMR0                 :1;                                /*!< Read request TMR0 */
  uint32_t RXTMR1                 :1;                                /*!< Read request TMR1 */
  uint32_t RXTMR2                 :1;                                /*!< Read request TMR2 */
  uint32_t RXTMR3                 :1;                                /*!< Read request TMR3 */
  uint32_t RXTMR4                 :1;                                /*!< Read request TMR4 */
  uint32_t RXADCSEQ0              :1;                                /*!< Read request ADC Seq0 */
  uint32_t RXADCSEQ1              :1;                                /*!< Read request ADC Seq1 */
  uint32_t RXADCSEQ2              :1;                                /*!< Read request ADC Seq2 */
  uint32_t RXADCSEQ3              :1;                                /*!< Read request ADC Seq3 */
  uint32_t RXGPIOA                :1;                                /*!< Read request GPIOA */
  uint32_t RXGPIOB                :1;                                /*!<  Read request GPIOB */
  uint32_t RXDAC                  :1;                                /*!<  [unused] Read request DAC */
} _DMA_PER_RXN_CTRL_bits;

/* Bit field positions: */
#define DMA_PER_RXN_CTRL_RXSPI0_Pos           1                      /*!< Read request SPI0 */
#define DMA_PER_RXN_CTRL_RXSPI1_Pos           2                      /*!< Read request SPI1 */
#define DMA_PER_RXN_CTRL_RXSPI2_Pos           3                      /*!< Read request SPI2 */
#define DMA_PER_RXN_CTRL_RXUART0_Pos          4                      /*!< Read request UART0 */
#define DMA_PER_RXN_CTRL_RXUART1_Pos          5                      /*!< Read request UART1 */
#define DMA_PER_RXN_CTRL_RXTMR0_Pos           6                      /*!< Read request TMR0 */
#define DMA_PER_RXN_CTRL_RXTMR1_Pos           7                      /*!< Read request TMR1 */
#define DMA_PER_RXN_CTRL_RXTMR2_Pos           8                      /*!< Read request TMR2 */
#define DMA_PER_RXN_CTRL_RXTMR3_Pos           9                      /*!< Read request TMR3 */
#define DMA_PER_RXN_CTRL_RXTMR4_Pos           10                     /*!< Read request TMR4 */
#define DMA_PER_RXN_CTRL_RXADCSEQ0_Pos        11                     /*!< Read request ADC Seq0 */
#define DMA_PER_RXN_CTRL_RXADCSEQ1_Pos        12                     /*!< Read request ADC Seq1 */
#define DMA_PER_RXN_CTRL_RXADCSEQ2_Pos        13                     /*!< Read request ADC Seq2 */
#define DMA_PER_RXN_CTRL_RXADCSEQ3_Pos        14                     /*!< Read request ADC Seq3 */
#define DMA_PER_RXN_CTRL_RXGPIOA_Pos          15                     /*!< Read request GPIOA */
#define DMA_PER_RXN_CTRL_RXGPIOB_Pos          16                     /*!<  Read request GPIOB */
#define DMA_PER_RXN_CTRL_RXDAC_Pos            17                     /*!<  [unused] Read request DAC */

/* Bit field masks: */
#define DMA_PER_RXN_CTRL_RXSPI0_Msk           0x00000002UL           /*!< Read request SPI0 */
#define DMA_PER_RXN_CTRL_RXSPI1_Msk           0x00000004UL           /*!< Read request SPI1 */
#define DMA_PER_RXN_CTRL_RXSPI2_Msk           0x00000008UL           /*!< Read request SPI2 */
#define DMA_PER_RXN_CTRL_RXUART0_Msk          0x00000010UL           /*!< Read request UART0 */
#define DMA_PER_RXN_CTRL_RXUART1_Msk          0x00000020UL           /*!< Read request UART1 */
#define DMA_PER_RXN_CTRL_RXTMR0_Msk           0x00000040UL           /*!< Read request TMR0 */
#define DMA_PER_RXN_CTRL_RXTMR1_Msk           0x00000080UL           /*!< Read request TMR1 */
#define DMA_PER_RXN_CTRL_RXTMR2_Msk           0x00000100UL           /*!< Read request TMR2 */
#define DMA_PER_RXN_CTRL_RXTMR3_Msk           0x00000200UL           /*!< Read request TMR3 */
#define DMA_PER_RXN_CTRL_RXTMR4_Msk           0x00000400UL           /*!< Read request TMR4 */
#define DMA_PER_RXN_CTRL_RXADCSEQ0_Msk        0x00000800UL           /*!< Read request ADC Seq0 */
#define DMA_PER_RXN_CTRL_RXADCSEQ1_Msk        0x00001000UL           /*!< Read request ADC Seq1 */
#define DMA_PER_RXN_CTRL_RXADCSEQ2_Msk        0x00002000UL           /*!< Read request ADC Seq2 */
#define DMA_PER_RXN_CTRL_RXADCSEQ3_Msk        0x00004000UL           /*!< Read request ADC Seq3 */
#define DMA_PER_RXN_CTRL_RXGPIOA_Msk          0x00008000UL           /*!< Read request GPIOA */
#define DMA_PER_RXN_CTRL_RXGPIOB_Msk          0x00010000UL           /*!<  Read request GPIOB */
#define DMA_PER_RXN_CTRL_RXDAC_Msk            0x00020000UL           /*!<  [unused] Read request DAC */

/*--  PER_TX_CTRL: Direct control of peripheral TX request ----------------------------------------------------*/
typedef struct {
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t TXREQ                  :17;                               /*!< Write requests {DAC, GPIOB, GPIOA, [unused] ADC Seq 3..0, TMR 4..0, UART 1..0, SPI 2..0} */
} _DMA_PER_TX_CTRL_bits;

/* Bit field positions: */
#define DMA_PER_TX_CTRL_TXREQ_Pos             1                      /*!< Write requests {DAC, GPIOB, GPIOA, [unused] ADC Seq 3..0, TMR 4..0, UART 1..0, SPI 2..0} */

/* Bit field masks: */
#define DMA_PER_TX_CTRL_TXREQ_Msk             0x0003FFFEUL           /*!< Write requests {DAC, GPIOB, GPIOA, [unused] ADC Seq 3..0, TMR 4..0, UART 1..0, SPI 2..0} */

/*--  PER_TXN_CTRL: Direct control of peripheral TX request (named bits) --------------------------------------*/
typedef struct {
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t TXSPI0                 :1;                                /*!< Write request SPI0 */
  uint32_t TXSPI1                 :1;                                /*!< Write request SPI1 */
  uint32_t TXSPI2                 :1;                                /*!< Write request SPI2 */
  uint32_t TXUART0                :1;                                /*!< Write request UART0 */
  uint32_t TXUART1                :1;                                /*!< Write request UART1 */
  uint32_t TXTMR0                 :1;                                /*!< Write request TMR0 */
  uint32_t TXTMR1                 :1;                                /*!< Write request TMR1 */
  uint32_t TXTMR2                 :1;                                /*!< Write request TMR2 */
  uint32_t TXTMR3                 :1;                                /*!< Write request TMR3 */
  uint32_t TXTMR4                 :1;                                /*!< Write request TMR4 */
  uint32_t TXADCSEQ0              :1;                                /*!< [unused] Write request ADC Seq0 */
  uint32_t TXADCSEQ1              :1;                                /*!< [unused] Write request ADC Seq1 */
  uint32_t TXADCSEQ2              :1;                                /*!< [unused] Write request ADC Seq2 */
  uint32_t TXADCSEQ3              :1;                                /*!< [unused] Write request ADC Seq3 */
  uint32_t TXGPIOA                :1;                                /*!< Write request GPIOA */
  uint32_t TXGPIOB                :1;                                /*!< Write request GPIOB */
  uint32_t TXDAC                  :1;                                /*!< Write request DAC */
} _DMA_PER_TXN_CTRL_bits;

/* Bit field positions: */
#define DMA_PER_TXN_CTRL_TXSPI0_Pos           1                      /*!< Write request SPI0 */
#define DMA_PER_TXN_CTRL_TXSPI1_Pos           2                      /*!< Write request SPI1 */
#define DMA_PER_TXN_CTRL_TXSPI2_Pos           3                      /*!< Write request SPI2 */
#define DMA_PER_TXN_CTRL_TXUART0_Pos          4                      /*!< Write request UART0 */
#define DMA_PER_TXN_CTRL_TXUART1_Pos          5                      /*!< Write request UART1 */
#define DMA_PER_TXN_CTRL_TXTMR0_Pos           6                      /*!< Write request TMR0 */
#define DMA_PER_TXN_CTRL_TXTMR1_Pos           7                      /*!< Write request TMR1 */
#define DMA_PER_TXN_CTRL_TXTMR2_Pos           8                      /*!< Write request TMR2 */
#define DMA_PER_TXN_CTRL_TXTMR3_Pos           9                      /*!< Write request TMR3 */
#define DMA_PER_TXN_CTRL_TXTMR4_Pos           10                     /*!< Write request TMR4 */
#define DMA_PER_TXN_CTRL_TXADCSEQ0_Pos        11                     /*!< [unused] Write request ADC Seq0 */
#define DMA_PER_TXN_CTRL_TXADCSEQ1_Pos        12                     /*!< [unused] Write request ADC Seq1 */
#define DMA_PER_TXN_CTRL_TXADCSEQ2_Pos        13                     /*!< [unused] Write request ADC Seq2 */
#define DMA_PER_TXN_CTRL_TXADCSEQ3_Pos        14                     /*!< [unused] Write request ADC Seq3 */
#define DMA_PER_TXN_CTRL_TXGPIOA_Pos          15                     /*!< Write request GPIOA */
#define DMA_PER_TXN_CTRL_TXGPIOB_Pos          16                     /*!< Write request GPIOB */
#define DMA_PER_TXN_CTRL_TXDAC_Pos            17                     /*!< Write request DAC */

/* Bit field masks: */
#define DMA_PER_TXN_CTRL_TXSPI0_Msk           0x00000002UL           /*!< Write request SPI0 */
#define DMA_PER_TXN_CTRL_TXSPI1_Msk           0x00000004UL           /*!< Write request SPI1 */
#define DMA_PER_TXN_CTRL_TXSPI2_Msk           0x00000008UL           /*!< Write request SPI2 */
#define DMA_PER_TXN_CTRL_TXUART0_Msk          0x00000010UL           /*!< Write request UART0 */
#define DMA_PER_TXN_CTRL_TXUART1_Msk          0x00000020UL           /*!< Write request UART1 */
#define DMA_PER_TXN_CTRL_TXTMR0_Msk           0x00000040UL           /*!< Write request TMR0 */
#define DMA_PER_TXN_CTRL_TXTMR1_Msk           0x00000080UL           /*!< Write request TMR1 */
#define DMA_PER_TXN_CTRL_TXTMR2_Msk           0x00000100UL           /*!< Write request TMR2 */
#define DMA_PER_TXN_CTRL_TXTMR3_Msk           0x00000200UL           /*!< Write request TMR3 */
#define DMA_PER_TXN_CTRL_TXTMR4_Msk           0x00000400UL           /*!< Write request TMR4 */
#define DMA_PER_TXN_CTRL_TXADCSEQ0_Msk        0x00000800UL           /*!< [unused] Write request ADC Seq0 */
#define DMA_PER_TXN_CTRL_TXADCSEQ1_Msk        0x00001000UL           /*!< [unused] Write request ADC Seq1 */
#define DMA_PER_TXN_CTRL_TXADCSEQ2_Msk        0x00002000UL           /*!< [unused] Write request ADC Seq2 */
#define DMA_PER_TXN_CTRL_TXADCSEQ3_Msk        0x00004000UL           /*!< [unused] Write request ADC Seq3 */
#define DMA_PER_TXN_CTRL_TXGPIOA_Msk          0x00008000UL           /*!< Write request GPIOA */
#define DMA_PER_TXN_CTRL_TXGPIOB_Msk          0x00010000UL           /*!< Write request GPIOB */
#define DMA_PER_TXN_CTRL_TXDAC_Msk            0x00020000UL           /*!< Write request DAC */

//Cluster CH:
typedef struct {
  union {
  /*!< Command register 0 (source pointer) */
    __IO uint32_t SRC_PTR;                                           /*!< SRC_PTR : type used for word access */
    __IO _DMA_CH_SRC_PTR_bits SRC_PTR_bit;                           /*!< SRC_PTR_bit: structure used for bit access */
  };
  union {
  /*!< Command register 1 (destination pointer) */
    __IO uint32_t DST_PTR;                                           /*!< DST_PTR : type used for word access */
    __IO _DMA_CH_DST_PTR_bits DST_PTR_bit;                           /*!< DST_PTR_bit: structure used for bit access */
  };
  union {
      union {
                                                                     /*!< Command register 2 (number of data to transfer, linear mode) */
        __IO uint32_t NDTL;                                           /*!< NDTL : type used for word access */
        __IO _DMA_CH_NDTL_bits NDTL_bit;                             /*!< NDTL_bit: structure used for bit access */
      };
      union {
                                                                     /*!< Command register 2 (number of data to transfer, block mode) - Not Implemented */
        __I uint32_t NDTB;                                           /*!< NDTB : type used for word access */
        __I _DMA_CH_NDTB_bits NDTB_bit;                              /*!< NDTB_bit: structure used for bit access */
      };
  };
  union {
  /*!< Command register 3 (config) */
    __IO uint32_t CONFIG;                                            /*!< CONFIG : type used for word access */
    __IO _DMA_CH_CONFIG_bits CONFIG_bit;                             /*!< CONFIG_bit: structure used for bit access */
  };
  union {
  /*!< Static register 0 */
    __IO uint32_t STATIC0;                                           /*!< STATIC0 : type used for word access */
    __IO _DMA_CH_STATIC0_bits STATIC0_bit;                           /*!< STATIC0_bit: structure used for bit access */
  };
  union {
  /*!< Static register 1 */
    __IO uint32_t STATIC1;                                           /*!< STATIC1 : type used for word access */
    __IO _DMA_CH_STATIC1_bits STATIC1_bit;                           /*!< STATIC1_bit: structure used for bit access */
  };
  union {
  /*!< Static register 2 */
    __IO uint32_t STATIC2;                                           /*!< STATIC2 : type used for word access */
    __IO _DMA_CH_STATIC2_bits STATIC2_bit;                           /*!< STATIC2_bit: structure used for bit access */
  };
  union {
  /*!< Static register 3 */
    __IO uint32_t STATIC3;                                           /*!< STATIC3 : type used for word access */
    __IO _DMA_CH_STATIC3_bits STATIC3_bit;                           /*!< STATIC3_bit: structure used for bit access */
  };
  union {
  /*!< Static register 4 */
    __IO uint32_t STATIC4;                                           /*!< STATIC4 : type used for word access */
    __IO _DMA_CH_STATIC4_bits STATIC4_bit;                           /*!< STATIC4_bit: structure used for bit access */
  };
  union {
  /*!< Channels restrictions status register */
    __I uint32_t RESTRICT;                                           /*!< RESTRICT : type used for word access */
    __I _DMA_CH_RESTRICT_bits RESTRICT_bit;                          /*!< RESTRICT_bit: structure used for bit access */
  };
  union {
  /*!< Channels read offset status register */
    __I uint32_t RDOFFSET;                                           /*!< RDOFFSET : type used for word access */
    __I _DMA_CH_RDOFFSET_bits RDOFFSET_bit;                          /*!< RDOFFSET_bit: structure used for bit access */
  };
  union {
  /*!< Channels write offset status register */
    __I uint32_t WROFFSET;                                           /*!< WROFFSET : type used for word access */
    __I _DMA_CH_WROFFSET_bits WROFFSET_bit;                          /*!< WROFFSET_bit: structure used for bit access */
  };
  union {
  /*!< FIFO fullness status register */
    __I uint32_t FIFOSTAT;                                           /*!< FIFOSTAT : type used for word access */
    __I _DMA_CH_FIFOSTAT_bits FIFOSTAT_bit;                          /*!< FIFOSTAT_bit: structure used for bit access */
  };
  union {
  /*!< Outstanding commands status register */
    __I uint32_t CMD_OUTS;                                           /*!< CMD_OUTS : type used for word access */
    __I _DMA_CH_CMD_OUTS_bits CMD_OUTS_bit;                          /*!< CMD_OUTS_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0[2];
  union {
  /*!< Channel active register */
    __IO uint32_t CH_ACTIVE;                                           /*!< CH_ACTIVE : type used for word access */
    __IO _DMA_CH_CH_ACTIVE_bits CH_ACTIVE_bit;                       /*!< CH_ACTIVE_bit: structure used for bit access */
  };
  union {
  /*!< Channel start register */
    __O uint32_t CH_START;                                           /*!< CH_START : type used for word access */
    __O _DMA_CH_CH_START_bits CH_START_bit;                          /*!< CH_START_bit: structure used for bit access */
  };
  union {
  /*!< Channel status register */
    __I uint32_t CH_STATUS;                                           /*!< CH_STATUS : type used for word access */
    __I _DMA_CH_CH_STATUS_bits CH_STATUS_bit;                        /*!< CH_STATUS_bit: structure used for bit access */
  };
  union {
  /*!< Buffer counter status register */
    __I uint32_t COUNT;                                              /*!< COUNT : type used for word access */
    __I _DMA_CH_COUNT_bits COUNT_bit;                                /*!< COUNT_bit: structure used for bit access */
  };
  union {
  /*!< Interrupt raw status register */
    __IO uint32_t INT_RAWSTAT;                                           /*!< INT_RAWSTAT : type used for word access */
    __IO _DMA_CH_INT_RAWSTAT_bits INT_RAWSTAT_bit;                   /*!< INT_RAWSTAT_bit: structure used for bit access */
  };
  union {
  /*!< Interrupt clear register */
    __O uint32_t INT_CLEAR;                                           /*!< INT_CLEAR : type used for word access */
    __O _DMA_CH_INT_CLEAR_bits INT_CLEAR_bit;                        /*!< INT_CLEAR_bit: structure used for bit access */
  };
  union {
  /*!< Interrupt enable register */
    __IO uint32_t INT_ENABLE;                                           /*!< INT_ENABLE : type used for word access */
    __IO _DMA_CH_INT_ENABLE_bits INT_ENABLE_bit;                     /*!< INT_ENABLE_bit: structure used for bit access */
  };
  union {
  /*!< Interrupt status */
    __I uint32_t INT_STATUS;                                           /*!< INT_STATUS : type used for word access */
    __I _DMA_CH_INT_STATUS_bits INT_STATUS_bit;                      /*!< INT_STATUS_bit: structure used for bit access */
  };
  union {
  /*!< Channel error stop condition register */
    __IO uint32_t ERR_STOP;                                           /*!< ERR_STOP : type used for word access */
    __IO _DMA_CH_ERR_STOP_bits ERR_STOP_bit;                         /*!< ERR_STOP_bit: structure used for bit access */
  };
  union {
  /*!< Erroneous read transaction address register */
    __I uint32_t ERR_RD_ADDR;                                           /*!< ERR_RD_ADDR : type used for word access */
    __I _DMA_CH_ERR_RD_ADDR_bits ERR_RD_ADDR_bit;                    /*!< ERR_RD_ADDR_bit: structure used for bit access */
  };
  union {
  /*!< Erroneous write transaction address register */
    __I uint32_t ERR_WR_ADDR;                                           /*!< ERR_WR_ADDR : type used for word access */
    __I _DMA_CH_ERR_WR_ADDR_bits ERR_WR_ADDR_bit;                    /*!< ERR_WR_ADDR_bit: structure used for bit access */
  };
    __IO uint32_t Reserved1[5];
} _DMA_CH_TypeDef;
typedef struct {
  _DMA_CH_TypeDef CH[8];
    __IO uint32_t Reserved0[768];
  union {                                                            /*!< Status register indicating which channels caused an interrupt on INT[7:0] */
    __I uint32_t CH_INTSTAT;                                           /*!< CH_INTSTAT    : type used for word access */
    __I _DMA_CH_INTSTAT_bits  CH_INTSTAT_bit;                        /*!< CH_INTSTAT_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA Core control arbitrage and mode */
    __IO uint32_t CONTROL;                                           /*!< CONTROL    : type used for word access */
    __IO _DMA_CONTROL_bits  CONTROL_bit;                             /*!< CONTROL_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA Core read priority channels */
    __IO uint32_t RD_PRIORITY;                                           /*!< RD_PRIORITY    : type used for word access */
    __IO _DMA_RD_PRIORITY_bits  RD_PRIORITY_bit;                     /*!< RD_PRIORITY_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA Core read priority channels */
    __IO uint32_t WR_PRIORITY;                                           /*!< WR_PRIORITY    : type used for word access */
    __IO _DMA_WR_PRIORITY_bits  WR_PRIORITY_bit;                     /*!< WR_PRIORITY_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA channel start */
    __O uint32_t CH_START;                                           /*!< CH_START    : type used for word access */
    __O _DMA_CH_START_bits  CH_START_bit;                            /*!< CH_START_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA channel enable */
    __IO uint32_t CH_ENABLE;                                           /*!< CH_ENABLE    : type used for word access */
    __IO _DMA_CH_ENABLE_bits  CH_ENABLE_bit;                         /*!< CH_ENABLE_bit: structure used for bit access */
  };
  union {                                                            /*!< Idle indication register */
    __I uint32_t IDLE;                                               /*!< IDLE    : type used for word access */
    __I _DMA_IDLE_bits  IDLE_bit;                                    /*!< IDLE_bit: structure used for bit access */
  };
    __IO uint32_t Reserved1;
  union {
    union {                                                            /*!< Direct control of peripheral RX request */
      __IO uint32_t PER_RX_CTRL;                                           /*!< PER_RX_CTRL    : type used for word access */
      __IO _DMA_PER_RX_CTRL_bits  PER_RX_CTRL_bit;                   /*!< PER_RX_CTRL_bit: structure used for bit access */
    };
    struct {
      union {                                                            /*!< Direct control of peripheral RX request (named bits) */
        __IO uint32_t PER_RXN_CTRL;                                           /*!< PER_RXN_CTRL    : type used for word access */
        __IO _DMA_PER_RXN_CTRL_bits  PER_RXN_CTRL_bit;                /*!< PER_RXN_CTRL_bit: structure used for bit access */
      };
    };
  };
  union {
    union {                                                            /*!< Direct control of peripheral TX request */
      __IO uint32_t PER_TX_CTRL;                                           /*!< PER_TX_CTRL    : type used for word access */
      __IO _DMA_PER_TX_CTRL_bits  PER_TX_CTRL_bit;                   /*!< PER_TX_CTRL_bit: structure used for bit access */
    };
    struct {
      union {                                                            /*!< Direct control of peripheral TX request (named bits) */
        __IO uint32_t PER_TXN_CTRL;                                           /*!< PER_TXN_CTRL    : type used for word access */
        __IO _DMA_PER_TXN_CTRL_bits  PER_TXN_CTRL_bit;                /*!< PER_TXN_CTRL_bit: structure used for bit access */
      };
    };
  };
} DMA_TypeDef;


/******************************************************************************/
/*                         FLASH registers                                    */
/******************************************************************************/

/*--  ADDR: Address Register ----------------------------------------------------------------------------------*/
typedef struct {
  uint32_t BYTESEL                :3;                                /*!< Address value for each byte */
  uint32_t ADDRESS                :16;                               /*!< Address value to selected flash IP */
} _FLASH_ADDR_bits;

/* Bit field positions: */
#define FLASH_ADDR_BYTESEL_Pos                0                      /*!< Address value for each byte */
#define FLASH_ADDR_ADDRESS_Pos                3                      /*!< Address value to selected flash IP */

/* Bit field masks: */
#define FLASH_ADDR_BYTESEL_Msk                0x00000007UL           /*!< Address value for each byte */
#define FLASH_ADDR_ADDRESS_Msk                0x0007FFF8UL           /*!< Address value to selected flash IP */

/*--  NVR_ADDR: Address Register for NVR access ---------------------------------------------------------------*/
typedef struct {
  uint32_t BYTESEL                :3;                                /*!< Address value for each byte */
  uint32_t ADDRESS                :7;                                /*!< Address value within current sector to selected flash IP */
  uint32_t SECTOR_ADDR            :3;                                /*!< Sector address value (lsb) to selected flash IP */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t HIGH_SECTOR            :1;                                /*!< Sector address value (msb) to selected flash IP */
} _FLASH_NVR_ADDR_bits;

/* Bit field positions: */
#define FLASH_NVR_ADDR_BYTESEL_Pos            0                      /*!< Address value for each byte */
#define FLASH_NVR_ADDR_ADDRESS_Pos            3                      /*!< Address value within current sector to selected flash IP */
#define FLASH_NVR_ADDR_SECTOR_ADDR_Pos        10                     /*!< Sector address value (lsb) to selected flash IP */
#define FLASH_NVR_ADDR_HIGH_SECTOR_Pos        18                     /*!< Sector address value (msb) to selected flash IP */

/* Bit field masks: */
#define FLASH_NVR_ADDR_BYTESEL_Msk            0x00000007UL           /*!< Address value for each byte */
#define FLASH_NVR_ADDR_ADDRESS_Msk            0x000003F8UL           /*!< Address value within current sector to selected flash IP */
#define FLASH_NVR_ADDR_SECTOR_ADDR_Msk        0x00001C00UL           /*!< Sector address value (lsb) to selected flash IP */
#define FLASH_NVR_ADDR_HIGH_SECTOR_Msk        0x00040000UL           /*!< Sector address value (msb) to selected flash IP */

/*--  NVRCFG_ADDR: Address Register for NVR_CFG access --------------------------------------------------------*/
typedef struct {
  uint32_t BYTESEL                :4;                                /*!< Address value for each byte */
  uint32_t ADDRESS                :7;                                /*!< Address value within current sector to selected flash IP */
} _FLASH_NVRCFG_ADDR_bits;

/* Bit field positions: */
#define FLASH_NVRCFG_ADDR_BYTESEL_Pos         0                      /*!< Address value for each byte */
#define FLASH_NVRCFG_ADDR_ADDRESS_Pos         4                      /*!< Address value within current sector to selected flash IP */

/* Bit field masks: */
#define FLASH_NVRCFG_ADDR_BYTESEL_Msk         0x0000000FUL           /*!< Address value for each byte */
#define FLASH_NVRCFG_ADDR_ADDRESS_Msk         0x000007F0UL           /*!< Address value within current sector to selected flash IP */

/*--  EXPAND_ADDR: Address Register with expanded fields ------------------------------------------------------*/
typedef struct {
  uint32_t BYTESEL                :3;                                /*!< Address value for each byte */
  uint32_t ADDRESS                :7;                                /*!< Address value within current sector to selected flash IP */
  uint32_t SECTOR_ADDR            :9;                                /*!< Sector address value to selected flash IP */
} _FLASH_EXPAND_ADDR_bits;

/* Bit field positions: */
#define FLASH_EXPAND_ADDR_BYTESEL_Pos         0                      /*!< Address value for each byte */
#define FLASH_EXPAND_ADDR_ADDRESS_Pos         3                      /*!< Address value within current sector to selected flash IP */
#define FLASH_EXPAND_ADDR_SECTOR_ADDR_Pos       10                   /*!< Sector address value to selected flash IP */

/* Bit field masks: */
#define FLASH_EXPAND_ADDR_BYTESEL_Msk         0x00000007UL           /*!< Address value for each byte */
#define FLASH_EXPAND_ADDR_ADDRESS_Msk         0x000003F8UL           /*!< Address value within current sector to selected flash IP */
#define FLASH_EXPAND_ADDR_SECTOR_ADDR_Msk       0x0007FC00UL         /*!< Sector address value to selected flash IP */

/*--  DATA: Data Register -------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!< Data register value for flash operations */
} _FLASH_DATA_bits;

/* Bit field positions: */
#define FLASH_DATA_VAL_Pos                    0                      /*!< Data register value for flash operations */

/* Bit field masks: */
#define FLASH_DATA_VAL_Msk                    0xFFFFFFFFUL           /*!< Data register value for flash operations */

/*--  CMD: Command Register -----------------------------------------------------------------------------------*/
typedef struct {
  uint32_t RD                     :1;                                /*!< Read enable command */
  uint32_t WR                     :1;                                /*!< Write enable command */
  uint32_t ERSEC                  :1;                                /*!< Erase sector enable command */
  uint32_t ALLSEC                 :1;                                /*!< Select all sectors for erase */
  uint32_t DPD                    :1;                                /*!< Enter/Exit power down mode */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t NVRON                  :1;                                /*!< NVR access bit */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t KEY                    :16;                               /*!< Magic Key for flash access "C0DE" */
} _FLASH_CMD_bits;

/* Bit field positions: */
#define FLASH_CMD_RD_Pos                      0                      /*!< Read enable command */
#define FLASH_CMD_WR_Pos                      1                      /*!< Write enable command */
#define FLASH_CMD_ERSEC_Pos                   2                      /*!< Erase sector enable command */
#define FLASH_CMD_ALLSEC_Pos                  3                      /*!< Select all sectors for erase */
#define FLASH_CMD_DPD_Pos                     4                      /*!< Enter/Exit power down mode */
#define FLASH_CMD_NVRON_Pos                   8                      /*!< NVR access bit */
#define FLASH_CMD_KEY_Pos                     16                     /*!< Magic Key for flash access "C0DE" */

/* Bit field masks: */
#define FLASH_CMD_RD_Msk                      0x00000001UL           /*!< Read enable command */
#define FLASH_CMD_WR_Msk                      0x00000002UL           /*!< Write enable command */
#define FLASH_CMD_ERSEC_Msk                   0x00000004UL           /*!< Erase sector enable command */
#define FLASH_CMD_ALLSEC_Msk                  0x00000008UL           /*!< Select all sectors for erase */
#define FLASH_CMD_DPD_Msk                     0x00000010UL           /*!< Enter/Exit power down mode */
#define FLASH_CMD_NVRON_Msk                   0x00000100UL           /*!< NVR access bit */
#define FLASH_CMD_KEY_Msk                     0xFFFF0000UL           /*!< Magic Key for flash access "C0DE" */

/* Bit field enums: */
typedef enum {
  FLASH_CMD_KEY_Access                       = 0xC0DEUL,             /*!< magic Key for flash access */
} FLASH_CMD_KEY_Enum;

/*--  STAT: Status Register -----------------------------------------------------------------------------------*/
typedef struct {
  uint32_t BUSY                   :1;                                /*!< Busy status bit when command is processing */
  uint32_t IRQF                   :1;                                /*!< IRQ Flag set when command done. Set by hardware only if IRQEN bit is set. */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t DPD                    :1;                                /*!< Flash IP in powerdown mode */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t NVRLOCK                :1;                                /*!< If set NVR_CFG sector of flash is locked */
} _FLASH_STAT_bits;

/* Bit field positions: */
#define FLASH_STAT_BUSY_Pos                   0                      /*!< Busy status bit when command is processing */
#define FLASH_STAT_IRQF_Pos                   1                      /*!< IRQ Flag set when command done. Set by hardware only if IRQEN bit is set. */
#define FLASH_STAT_DPD_Pos                    4                      /*!< Flash IP in powerdown mode */
#define FLASH_STAT_NVRLOCK_Pos                8                      /*!< If set NVR_CFG sector of flash is locked */

/* Bit field masks: */
#define FLASH_STAT_BUSY_Msk                   0x00000001UL           /*!< Busy status bit when command is processing */
#define FLASH_STAT_IRQF_Msk                   0x00000002UL           /*!< IRQ Flag set when command done. Set by hardware only if IRQEN bit is set. */
#define FLASH_STAT_DPD_Msk                    0x00000010UL           /*!< Flash IP in powerdown mode */
#define FLASH_STAT_NVRLOCK_Msk                0x00000100UL           /*!< If set NVR_CFG sector of flash is locked */

/*--  CTRL: Control Register ----------------------------------------------------------------------------------*/
typedef struct {
  uint32_t FBEN                   :1;                                /*!< Fetch buffer Enable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t IRQEN                  :1;                                /*!< Interrupt enable bit */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t FBFLUSH                :1;                                /*!< Flush internal buffer */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t LAT                    :4;                                /*!< Flash latency */
} _FLASH_CTRL_bits;

/* Bit field positions: */
#define FLASH_CTRL_FBEN_Pos                   0                      /*!< Fetch buffer Enable */
#define FLASH_CTRL_IRQEN_Pos                  4                      /*!< Interrupt enable bit */
#define FLASH_CTRL_FBFLUSH_Pos                8                      /*!< Flush internal buffer */
#define FLASH_CTRL_LAT_Pos                    16                     /*!< Flash latency */

/* Bit field masks: */
#define FLASH_CTRL_FBEN_Msk                   0x00000001UL           /*!< Fetch buffer Enable */
#define FLASH_CTRL_IRQEN_Msk                  0x00000010UL           /*!< Interrupt enable bit */
#define FLASH_CTRL_FBFLUSH_Msk                0x00000100UL           /*!< Flush internal buffer */
#define FLASH_CTRL_LAT_Msk                    0x000F0000UL           /*!< Flash latency */

/*--  FTCETR: Flash Timing Control register (Erase time) ------------------------------------------------------*/
typedef struct {
  uint32_t TSCE                   :32;                               /*!< Erase time value in cycles */
} _FLASH_FTCETR_bits;

/* Bit field positions: */
#define FLASH_FTCETR_TSCE_Pos                 0                      /*!< Erase time value in cycles */

/* Bit field masks: */
#define FLASH_FTCETR_TSCE_Msk                 0xFFFFFFFFUL           /*!< Erase time value in cycles */

/*--  FTCPRT: Flash Timing Control register (Program time) ----------------------------------------------------*/
typedef struct {
  uint32_t TPGS                   :8;                                /*!< Web to PROG2 high time value in cycles */
  uint32_t TPREPROG               :8;                                /*!< Pre-program time value in cycles */
  uint32_t TPREPGS                :8;                                /*!< PREPG to PROG2 time value in cycles */
  uint32_t TPROG                  :8;                                /*!< Program time value in cycles */
} _FLASH_FTCPRT_bits;

/* Bit field positions: */
#define FLASH_FTCPRT_TPGS_Pos                 0                      /*!< Web to PROG2 high time value in cycles */
#define FLASH_FTCPRT_TPREPROG_Pos             8                      /*!< Pre-program time value in cycles */
#define FLASH_FTCPRT_TPREPGS_Pos              16                     /*!< PREPG to PROG2 time value in cycles */
#define FLASH_FTCPRT_TPROG_Pos                24                     /*!< Program time value in cycles */

/* Bit field masks: */
#define FLASH_FTCPRT_TPGS_Msk                 0x000000FFUL           /*!< Web to PROG2 high time value in cycles */
#define FLASH_FTCPRT_TPREPROG_Msk             0x0000FF00UL           /*!< Pre-program time value in cycles */
#define FLASH_FTCPRT_TPREPGS_Msk              0x00FF0000UL           /*!< PREPG to PROG2 time value in cycles */
#define FLASH_FTCPRT_TPROG_Msk                0xFF000000UL           /*!< Program time value in cycles */

/*--  FTCERTR: Flash Timing Control register (Erase Recovery time) --------------------------------------------*/
typedef struct {
  uint32_t TRCVSECT               :16;                               /*!< Sector erase recovery time value in cycles */
  uint32_t TRCVCHIP               :16;                               /*!< Chip erase recovery time value in cycles */
} _FLASH_FTCERTR_bits;

/* Bit field positions: */
#define FLASH_FTCERTR_TRCVSECT_Pos            0                      /*!< Sector erase recovery time value in cycles */
#define FLASH_FTCERTR_TRCVCHIP_Pos            16                     /*!< Chip erase recovery time value in cycles */

/* Bit field masks: */
#define FLASH_FTCERTR_TRCVSECT_Msk            0x0000FFFFUL           /*!< Sector erase recovery time value in cycles */
#define FLASH_FTCERTR_TRCVCHIP_Msk            0xFFFF0000UL           /*!< Chip erase recovery time value in cycles */

/*--  FTCPRTR: Flash Timing Control register (Program Recovery time) ------------------------------------------*/
typedef struct {
  uint32_t TRCVPROG               :8;                                /*!< Program recovery time value in cycles */
} _FLASH_FTCPRTR_bits;

/* Bit field positions: */
#define FLASH_FTCPRTR_TRCVPROG_Pos            0                      /*!< Program recovery time value in cycles */

/* Bit field masks: */
#define FLASH_FTCPRTR_TRCVPROG_Msk            0x000000FFUL           /*!< Program recovery time value in cycles */

//Cluster DATA:
typedef struct {
  union {
  /*!< Data Register */
    __IO uint32_t DATA;                                              /*!< DATA : type used for word access */
    __IO _FLASH_DATA_bits DATA_bit;                                  /*!< DATA_bit: structure used for bit access */
  };
} _FLASH_DATA_TypeDef;
typedef struct {
  union {
    union {                                                            /*!< Address Register */
      __IO uint32_t ADDR;                                            /*!< ADDR    : type used for word access */
      __IO _FLASH_ADDR_bits  ADDR_bit;                               /*!< ADDR_bit: structure used for bit access */
    };
      union {                                                            /*!< Address Register for NVR access */
        __IO uint32_t NVR_ADDR;                                           /*!< NVR_ADDR    : type used for word access */
        __IO _FLASH_NVR_ADDR_bits  NVR_ADDR_bit;                     /*!< NVR_ADDR_bit: structure used for bit access */
      };
      union {                                                            /*!< Address Register for NVR_CFG access */
        __IO uint32_t NVRCFG_ADDR;                                           /*!< NVRCFG_ADDR    : type used for word access */
        __IO _FLASH_NVRCFG_ADDR_bits  NVRCFG_ADDR_bit;                /*!< NVRCFG_ADDR_bit: structure used for bit access */
      };
      union {                                                            /*!< Address Register with expanded fields */
        __IO uint32_t EXPAND_ADDR;                                           /*!< EXPAND_ADDR    : type used for word access */
        __IO _FLASH_EXPAND_ADDR_bits  EXPAND_ADDR_bit;                /*!< EXPAND_ADDR_bit: structure used for bit access */
      };
  };
    __IO uint32_t Reserved0[3];
  _FLASH_DATA_TypeDef DATA[2];
    __IO uint32_t Reserved1[10];
  union {                                                            /*!< Command Register */
    __IO uint32_t CMD;                                               /*!< CMD    : type used for word access */
    __IO _FLASH_CMD_bits  CMD_bit;                                   /*!< CMD_bit: structure used for bit access */
  };
  union {                                                            /*!< Status Register */
    __IO uint32_t STAT;                                              /*!< STAT    : type used for word access */
    __IO _FLASH_STAT_bits  STAT_bit;                                 /*!< STAT_bit: structure used for bit access */
  };
  union {                                                            /*!< Control Register */
    __IO uint32_t CTRL;                                              /*!< CTRL    : type used for word access */
    __IO _FLASH_CTRL_bits  CTRL_bit;                                 /*!< CTRL_bit: structure used for bit access */
  };
    __IO uint32_t Reserved2[45];
  union {                                                            /*!< Flash Timing Control register (Erase time) */
    __IO uint32_t FTCETR;                                            /*!< FTCETR    : type used for word access */
    __IO _FLASH_FTCETR_bits  FTCETR_bit;                             /*!< FTCETR_bit: structure used for bit access */
  };
  union {                                                            /*!< Flash Timing Control register (Program time) */
    __IO uint32_t FTCPRT;                                            /*!< FTCPRT    : type used for word access */
    __IO _FLASH_FTCPRT_bits  FTCPRT_bit;                             /*!< FTCPRT_bit: structure used for bit access */
  };
  union {                                                            /*!< Flash Timing Control register (Erase Recovery time) */
    __IO uint32_t FTCERTR;                                           /*!< FTCERTR    : type used for word access */
    __IO _FLASH_FTCERTR_bits  FTCERTR_bit;                           /*!< FTCERTR_bit: structure used for bit access */
  };
  union {                                                            /*!< Flash Timing Control register (Program Recovery time) */
    __IO uint32_t FTCPRTR;                                           /*!< FTCPRTR    : type used for word access */
    __IO _FLASH_FTCPRTR_bits  FTCPRTR_bit;                           /*!< FTCPRTR_bit: structure used for bit access */
  };
} FLASH_TypeDef;


/******************************************************************************/
/*                         GPIO registers                                     */
/******************************************************************************/

/*--  DATA: Data Input register -------------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Data input */
} _GPIO_DATA_bits;

/* Bit field positions: */
#define GPIO_DATA_VAL_Pos                     0                      /*!< Data input */

/* Bit field masks: */
#define GPIO_DATA_VAL_Msk                     0x0000FFFFUL           /*!< Data input */

/*--  DATAOUT: Data output register ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Data output */
} _GPIO_DATAOUT_bits;

/* Bit field positions: */
#define GPIO_DATAOUT_VAL_Pos                  0                      /*!< Data output */

/* Bit field masks: */
#define GPIO_DATAOUT_VAL_Msk                  0x0000FFFFUL           /*!< Data output */

/*--  DATAOUTSET: Data output set bits register ---------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Data output set bit 0 */
  uint32_t PIN1                   :1;                                /*!< Data output set bit 1 */
  uint32_t PIN2                   :1;                                /*!< Data output set bit 2 */
  uint32_t PIN3                   :1;                                /*!< Data output set bit 3 */
  uint32_t PIN4                   :1;                                /*!< Data output set bit 4 */
  uint32_t PIN5                   :1;                                /*!< Data output set bit 5 */
  uint32_t PIN6                   :1;                                /*!< Data output set bit 6 */
  uint32_t PIN7                   :1;                                /*!< Data output set bit 7 */
  uint32_t PIN8                   :1;                                /*!< Data output set bit 8 */
  uint32_t PIN9                   :1;                                /*!< Data output set bit 9 */
  uint32_t PIN10                  :1;                                /*!< Data output set bit 10 */
  uint32_t PIN11                  :1;                                /*!< Data output set bit 11 */
  uint32_t PIN12                  :1;                                /*!< Data output set bit 12 */
  uint32_t PIN13                  :1;                                /*!< Data output set bit 13 */
  uint32_t PIN14                  :1;                                /*!< Data output set bit 14 */
  uint32_t PIN15                  :1;                                /*!< Data output set bit 15 */
} _GPIO_DATAOUTSET_bits;

/* Bit field positions: */
#define GPIO_DATAOUTSET_PIN0_Pos              0                      /*!< Data output set bit 0 */
#define GPIO_DATAOUTSET_PIN1_Pos              1                      /*!< Data output set bit 1 */
#define GPIO_DATAOUTSET_PIN2_Pos              2                      /*!< Data output set bit 2 */
#define GPIO_DATAOUTSET_PIN3_Pos              3                      /*!< Data output set bit 3 */
#define GPIO_DATAOUTSET_PIN4_Pos              4                      /*!< Data output set bit 4 */
#define GPIO_DATAOUTSET_PIN5_Pos              5                      /*!< Data output set bit 5 */
#define GPIO_DATAOUTSET_PIN6_Pos              6                      /*!< Data output set bit 6 */
#define GPIO_DATAOUTSET_PIN7_Pos              7                      /*!< Data output set bit 7 */
#define GPIO_DATAOUTSET_PIN8_Pos              8                      /*!< Data output set bit 8 */
#define GPIO_DATAOUTSET_PIN9_Pos              9                      /*!< Data output set bit 9 */
#define GPIO_DATAOUTSET_PIN10_Pos             10                     /*!< Data output set bit 10 */
#define GPIO_DATAOUTSET_PIN11_Pos             11                     /*!< Data output set bit 11 */
#define GPIO_DATAOUTSET_PIN12_Pos             12                     /*!< Data output set bit 12 */
#define GPIO_DATAOUTSET_PIN13_Pos             13                     /*!< Data output set bit 13 */
#define GPIO_DATAOUTSET_PIN14_Pos             14                     /*!< Data output set bit 14 */
#define GPIO_DATAOUTSET_PIN15_Pos             15                     /*!< Data output set bit 15 */

/* Bit field masks: */
#define GPIO_DATAOUTSET_PIN0_Msk              0x00000001UL           /*!< Data output set bit 0 */
#define GPIO_DATAOUTSET_PIN1_Msk              0x00000002UL           /*!< Data output set bit 1 */
#define GPIO_DATAOUTSET_PIN2_Msk              0x00000004UL           /*!< Data output set bit 2 */
#define GPIO_DATAOUTSET_PIN3_Msk              0x00000008UL           /*!< Data output set bit 3 */
#define GPIO_DATAOUTSET_PIN4_Msk              0x00000010UL           /*!< Data output set bit 4 */
#define GPIO_DATAOUTSET_PIN5_Msk              0x00000020UL           /*!< Data output set bit 5 */
#define GPIO_DATAOUTSET_PIN6_Msk              0x00000040UL           /*!< Data output set bit 6 */
#define GPIO_DATAOUTSET_PIN7_Msk              0x00000080UL           /*!< Data output set bit 7 */
#define GPIO_DATAOUTSET_PIN8_Msk              0x00000100UL           /*!< Data output set bit 8 */
#define GPIO_DATAOUTSET_PIN9_Msk              0x00000200UL           /*!< Data output set bit 9 */
#define GPIO_DATAOUTSET_PIN10_Msk             0x00000400UL           /*!< Data output set bit 10 */
#define GPIO_DATAOUTSET_PIN11_Msk             0x00000800UL           /*!< Data output set bit 11 */
#define GPIO_DATAOUTSET_PIN12_Msk             0x00001000UL           /*!< Data output set bit 12 */
#define GPIO_DATAOUTSET_PIN13_Msk             0x00002000UL           /*!< Data output set bit 13 */
#define GPIO_DATAOUTSET_PIN14_Msk             0x00004000UL           /*!< Data output set bit 14 */
#define GPIO_DATAOUTSET_PIN15_Msk             0x00008000UL           /*!< Data output set bit 15 */

/*--  DATAOUTCLR: Data output clear bits register -------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Data output clear */
} _GPIO_DATAOUTCLR_bits;

/* Bit field positions: */
#define GPIO_DATAOUTCLR_VAL_Pos               0                      /*!< Data output clear */

/* Bit field masks: */
#define GPIO_DATAOUTCLR_VAL_Msk               0x0000FFFFUL           /*!< Data output clear */

/*--  DATAOUTTGL: Data output toggle bits register ------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Data output toggle */
} _GPIO_DATAOUTTGL_bits;

/* Bit field positions: */
#define GPIO_DATAOUTTGL_VAL_Pos               0                      /*!< Data output toggle */

/* Bit field masks: */
#define GPIO_DATAOUTTGL_VAL_Msk               0x0000FFFFUL           /*!< Data output toggle */

/*--  PULLMODE: Select pull mode register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Select pull mode for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Select pull mode for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Select pull mode for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Select pull mode for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Select pull mode for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Select pull mode for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Select pull mode for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Select pull mode for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Select pull mode for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Select pull mode for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Select pull mode for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Select pull mode for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Select pull mode for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Select pull mode for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Select pull mode for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Select pull mode for pin 15 */
} _GPIO_PULLMODE_bits;

/* Bit field positions: */
#define GPIO_PULLMODE_PIN0_Pos                0                      /*!< Select pull mode for pin 0 */
#define GPIO_PULLMODE_PIN1_Pos                1                      /*!< Select pull mode for pin 1 */
#define GPIO_PULLMODE_PIN2_Pos                2                      /*!< Select pull mode for pin 2 */
#define GPIO_PULLMODE_PIN3_Pos                3                      /*!< Select pull mode for pin 3 */
#define GPIO_PULLMODE_PIN4_Pos                4                      /*!< Select pull mode for pin 4 */
#define GPIO_PULLMODE_PIN5_Pos                5                      /*!< Select pull mode for pin 5 */
#define GPIO_PULLMODE_PIN6_Pos                6                      /*!< Select pull mode for pin 6 */
#define GPIO_PULLMODE_PIN7_Pos                7                      /*!< Select pull mode for pin 7 */
#define GPIO_PULLMODE_PIN8_Pos                8                      /*!< Select pull mode for pin 8 */
#define GPIO_PULLMODE_PIN9_Pos                9                      /*!< Select pull mode for pin 9 */
#define GPIO_PULLMODE_PIN10_Pos               10                     /*!< Select pull mode for pin 10 */
#define GPIO_PULLMODE_PIN11_Pos               11                     /*!< Select pull mode for pin 11 */
#define GPIO_PULLMODE_PIN12_Pos               12                     /*!< Select pull mode for pin 12 */
#define GPIO_PULLMODE_PIN13_Pos               13                     /*!< Select pull mode for pin 13 */
#define GPIO_PULLMODE_PIN14_Pos               14                     /*!< Select pull mode for pin 14 */
#define GPIO_PULLMODE_PIN15_Pos               15                     /*!< Select pull mode for pin 15 */

/* Bit field masks: */
#define GPIO_PULLMODE_PIN0_Msk                0x00000001UL           /*!< Select pull mode for pin 0 */
#define GPIO_PULLMODE_PIN1_Msk                0x00000002UL           /*!< Select pull mode for pin 1 */
#define GPIO_PULLMODE_PIN2_Msk                0x00000004UL           /*!< Select pull mode for pin 2 */
#define GPIO_PULLMODE_PIN3_Msk                0x00000008UL           /*!< Select pull mode for pin 3 */
#define GPIO_PULLMODE_PIN4_Msk                0x00000010UL           /*!< Select pull mode for pin 4 */
#define GPIO_PULLMODE_PIN5_Msk                0x00000020UL           /*!< Select pull mode for pin 5 */
#define GPIO_PULLMODE_PIN6_Msk                0x00000040UL           /*!< Select pull mode for pin 6 */
#define GPIO_PULLMODE_PIN7_Msk                0x00000080UL           /*!< Select pull mode for pin 7 */
#define GPIO_PULLMODE_PIN8_Msk                0x00000100UL           /*!< Select pull mode for pin 8 */
#define GPIO_PULLMODE_PIN9_Msk                0x00000200UL           /*!< Select pull mode for pin 9 */
#define GPIO_PULLMODE_PIN10_Msk               0x00000400UL           /*!< Select pull mode for pin 10 */
#define GPIO_PULLMODE_PIN11_Msk               0x00000800UL           /*!< Select pull mode for pin 11 */
#define GPIO_PULLMODE_PIN12_Msk               0x00001000UL           /*!< Select pull mode for pin 12 */
#define GPIO_PULLMODE_PIN13_Msk               0x00002000UL           /*!< Select pull mode for pin 13 */
#define GPIO_PULLMODE_PIN14_Msk               0x00004000UL           /*!< Select pull mode for pin 14 */
#define GPIO_PULLMODE_PIN15_Msk               0x00008000UL           /*!< Select pull mode for pin 15 */

/* Bit field enums: */
typedef enum {
  GPIO_PULLMODE_PIN0_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN0_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN0_Enum;

typedef enum {
  GPIO_PULLMODE_PIN1_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN1_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN1_Enum;

typedef enum {
  GPIO_PULLMODE_PIN2_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN2_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN2_Enum;

typedef enum {
  GPIO_PULLMODE_PIN3_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN3_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN3_Enum;

typedef enum {
  GPIO_PULLMODE_PIN4_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN4_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN4_Enum;

typedef enum {
  GPIO_PULLMODE_PIN5_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN5_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN5_Enum;

typedef enum {
  GPIO_PULLMODE_PIN6_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN6_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN6_Enum;

typedef enum {
  GPIO_PULLMODE_PIN7_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN7_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN7_Enum;

typedef enum {
  GPIO_PULLMODE_PIN8_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN8_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN8_Enum;

typedef enum {
  GPIO_PULLMODE_PIN9_Disable                 = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN9_PU                      = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN9_Enum;

typedef enum {
  GPIO_PULLMODE_PIN10_Disable                = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN10_PU                     = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN10_Enum;

typedef enum {
  GPIO_PULLMODE_PIN11_Disable                = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN11_PU                     = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN11_Enum;

typedef enum {
  GPIO_PULLMODE_PIN12_Disable                = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN12_PU                     = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN12_Enum;

typedef enum {
  GPIO_PULLMODE_PIN13_Disable                = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN13_PU                     = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN13_Enum;

typedef enum {
  GPIO_PULLMODE_PIN14_Disable                = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN14_PU                     = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN14_Enum;

typedef enum {
  GPIO_PULLMODE_PIN15_Disable                = 0x0UL,                /*!< Pull disabled */
  GPIO_PULLMODE_PIN15_PU                     = 0x1UL,                /*!< Pull-up */
} GPIO_PULLMODE_PIN15_Enum;

/*--  OUTMODE: Select output mode register --------------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :2;                                /*!< Select output mode for pin 0 */
  uint32_t PIN1                   :2;                                /*!< Select output mode for pin 1 */
  uint32_t PIN2                   :2;                                /*!< Select output mode for pin 2 */
  uint32_t PIN3                   :2;                                /*!< Select output mode for pin 3 */
  uint32_t PIN4                   :2;                                /*!< Select output mode for pin 4 */
  uint32_t PIN5                   :2;                                /*!< Select output mode for pin 5 */
  uint32_t PIN6                   :2;                                /*!< Select output mode for pin 6 */
  uint32_t PIN7                   :2;                                /*!< Select output mode for pin 7 */
  uint32_t PIN8                   :2;                                /*!< Select output mode for pin 8 */
  uint32_t PIN9                   :2;                                /*!< Select output mode for pin 9 */
  uint32_t PIN10                  :2;                                /*!< Select output mode for pin 10 */
  uint32_t PIN11                  :2;                                /*!< Select output mode for pin 11 */
  uint32_t PIN12                  :2;                                /*!< Select output mode for pin 12 */
  uint32_t PIN13                  :2;                                /*!< Select output mode for pin 13 */
  uint32_t PIN14                  :2;                                /*!< Select output mode for pin 14 */
  uint32_t PIN15                  :2;                                /*!< Select output mode for pin 15 */
} _GPIO_OUTMODE_bits;

/* Bit field positions: */
#define GPIO_OUTMODE_PIN0_Pos                 0                      /*!< Select output mode for pin 0 */
#define GPIO_OUTMODE_PIN1_Pos                 2                      /*!< Select output mode for pin 1 */
#define GPIO_OUTMODE_PIN2_Pos                 4                      /*!< Select output mode for pin 2 */
#define GPIO_OUTMODE_PIN3_Pos                 6                      /*!< Select output mode for pin 3 */
#define GPIO_OUTMODE_PIN4_Pos                 8                      /*!< Select output mode for pin 4 */
#define GPIO_OUTMODE_PIN5_Pos                 10                     /*!< Select output mode for pin 5 */
#define GPIO_OUTMODE_PIN6_Pos                 12                     /*!< Select output mode for pin 6 */
#define GPIO_OUTMODE_PIN7_Pos                 14                     /*!< Select output mode for pin 7 */
#define GPIO_OUTMODE_PIN8_Pos                 16                     /*!< Select output mode for pin 8 */
#define GPIO_OUTMODE_PIN9_Pos                 18                     /*!< Select output mode for pin 9 */
#define GPIO_OUTMODE_PIN10_Pos                20                     /*!< Select output mode for pin 10 */
#define GPIO_OUTMODE_PIN11_Pos                22                     /*!< Select output mode for pin 11 */
#define GPIO_OUTMODE_PIN12_Pos                24                     /*!< Select output mode for pin 12 */
#define GPIO_OUTMODE_PIN13_Pos                26                     /*!< Select output mode for pin 13 */
#define GPIO_OUTMODE_PIN14_Pos                28                     /*!< Select output mode for pin 14 */
#define GPIO_OUTMODE_PIN15_Pos                30                     /*!< Select output mode for pin 15 */

/* Bit field masks: */
#define GPIO_OUTMODE_PIN0_Msk                 0x00000003UL           /*!< Select output mode for pin 0 */
#define GPIO_OUTMODE_PIN1_Msk                 0x0000000CUL           /*!< Select output mode for pin 1 */
#define GPIO_OUTMODE_PIN2_Msk                 0x00000030UL           /*!< Select output mode for pin 2 */
#define GPIO_OUTMODE_PIN3_Msk                 0x000000C0UL           /*!< Select output mode for pin 3 */
#define GPIO_OUTMODE_PIN4_Msk                 0x00000300UL           /*!< Select output mode for pin 4 */
#define GPIO_OUTMODE_PIN5_Msk                 0x00000C00UL           /*!< Select output mode for pin 5 */
#define GPIO_OUTMODE_PIN6_Msk                 0x00003000UL           /*!< Select output mode for pin 6 */
#define GPIO_OUTMODE_PIN7_Msk                 0x0000C000UL           /*!< Select output mode for pin 7 */
#define GPIO_OUTMODE_PIN8_Msk                 0x00030000UL           /*!< Select output mode for pin 8 */
#define GPIO_OUTMODE_PIN9_Msk                 0x000C0000UL           /*!< Select output mode for pin 9 */
#define GPIO_OUTMODE_PIN10_Msk                0x00300000UL           /*!< Select output mode for pin 10 */
#define GPIO_OUTMODE_PIN11_Msk                0x00C00000UL           /*!< Select output mode for pin 11 */
#define GPIO_OUTMODE_PIN12_Msk                0x03000000UL           /*!< Select output mode for pin 12 */
#define GPIO_OUTMODE_PIN13_Msk                0x0C000000UL           /*!< Select output mode for pin 13 */
#define GPIO_OUTMODE_PIN14_Msk                0x30000000UL           /*!< Select output mode for pin 14 */
#define GPIO_OUTMODE_PIN15_Msk                0xC0000000UL           /*!< Select output mode for pin 15 */

/* Bit field enums: */
typedef enum {
  GPIO_OUTMODE_PIN0_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN0_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN0_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN0_Enum;

typedef enum {
  GPIO_OUTMODE_PIN1_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN1_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN1_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN1_Enum;

typedef enum {
  GPIO_OUTMODE_PIN2_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN2_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN2_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN2_Enum;

typedef enum {
  GPIO_OUTMODE_PIN3_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN3_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN3_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN3_Enum;

typedef enum {
  GPIO_OUTMODE_PIN4_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN4_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN4_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN4_Enum;

typedef enum {
  GPIO_OUTMODE_PIN5_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN5_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN5_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN5_Enum;

typedef enum {
  GPIO_OUTMODE_PIN6_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN6_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN6_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN6_Enum;

typedef enum {
  GPIO_OUTMODE_PIN7_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN7_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN7_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN7_Enum;

typedef enum {
  GPIO_OUTMODE_PIN8_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN8_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN8_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN8_Enum;

typedef enum {
  GPIO_OUTMODE_PIN9_PP                       = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN9_OD                       = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN9_OS                       = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN9_Enum;

typedef enum {
  GPIO_OUTMODE_PIN10_PP                      = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN10_OD                      = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN10_OS                      = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN10_Enum;

typedef enum {
  GPIO_OUTMODE_PIN11_PP                      = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN11_OD                      = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN11_OS                      = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN11_Enum;

typedef enum {
  GPIO_OUTMODE_PIN12_PP                      = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN12_OD                      = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN12_OS                      = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN12_Enum;

typedef enum {
  GPIO_OUTMODE_PIN13_PP                      = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN13_OD                      = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN13_OS                      = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN13_Enum;

typedef enum {
  GPIO_OUTMODE_PIN14_PP                      = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN14_OD                      = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN14_OS                      = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN14_Enum;

typedef enum {
  GPIO_OUTMODE_PIN15_PP                      = 0x0UL,                /*!< Push-pull output */
  GPIO_OUTMODE_PIN15_OD                      = 0x1UL,                /*!< Open drain output */
  GPIO_OUTMODE_PIN15_OS                      = 0x2UL,                /*!< Open source output */
} GPIO_OUTMODE_PIN15_Enum;

/*--  OUTENSET: Output enable register ------------------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Output enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Output enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Output enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Output enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Output enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Output enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Output enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Output enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Output enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Output enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Output enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Output enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Output enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Output enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Output enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Output enable for pin 15 */
} _GPIO_OUTENSET_bits;

/* Bit field positions: */
#define GPIO_OUTENSET_PIN0_Pos                0                      /*!< Output enable for pin 0 */
#define GPIO_OUTENSET_PIN1_Pos                1                      /*!< Output enable for pin 1 */
#define GPIO_OUTENSET_PIN2_Pos                2                      /*!< Output enable for pin 2 */
#define GPIO_OUTENSET_PIN3_Pos                3                      /*!< Output enable for pin 3 */
#define GPIO_OUTENSET_PIN4_Pos                4                      /*!< Output enable for pin 4 */
#define GPIO_OUTENSET_PIN5_Pos                5                      /*!< Output enable for pin 5 */
#define GPIO_OUTENSET_PIN6_Pos                6                      /*!< Output enable for pin 6 */
#define GPIO_OUTENSET_PIN7_Pos                7                      /*!< Output enable for pin 7 */
#define GPIO_OUTENSET_PIN8_Pos                8                      /*!< Output enable for pin 8 */
#define GPIO_OUTENSET_PIN9_Pos                9                      /*!< Output enable for pin 9 */
#define GPIO_OUTENSET_PIN10_Pos               10                     /*!< Output enable for pin 10 */
#define GPIO_OUTENSET_PIN11_Pos               11                     /*!< Output enable for pin 11 */
#define GPIO_OUTENSET_PIN12_Pos               12                     /*!< Output enable for pin 12 */
#define GPIO_OUTENSET_PIN13_Pos               13                     /*!< Output enable for pin 13 */
#define GPIO_OUTENSET_PIN14_Pos               14                     /*!< Output enable for pin 14 */
#define GPIO_OUTENSET_PIN15_Pos               15                     /*!< Output enable for pin 15 */

/* Bit field masks: */
#define GPIO_OUTENSET_PIN0_Msk                0x00000001UL           /*!< Output enable for pin 0 */
#define GPIO_OUTENSET_PIN1_Msk                0x00000002UL           /*!< Output enable for pin 1 */
#define GPIO_OUTENSET_PIN2_Msk                0x00000004UL           /*!< Output enable for pin 2 */
#define GPIO_OUTENSET_PIN3_Msk                0x00000008UL           /*!< Output enable for pin 3 */
#define GPIO_OUTENSET_PIN4_Msk                0x00000010UL           /*!< Output enable for pin 4 */
#define GPIO_OUTENSET_PIN5_Msk                0x00000020UL           /*!< Output enable for pin 5 */
#define GPIO_OUTENSET_PIN6_Msk                0x00000040UL           /*!< Output enable for pin 6 */
#define GPIO_OUTENSET_PIN7_Msk                0x00000080UL           /*!< Output enable for pin 7 */
#define GPIO_OUTENSET_PIN8_Msk                0x00000100UL           /*!< Output enable for pin 8 */
#define GPIO_OUTENSET_PIN9_Msk                0x00000200UL           /*!< Output enable for pin 9 */
#define GPIO_OUTENSET_PIN10_Msk               0x00000400UL           /*!< Output enable for pin 10 */
#define GPIO_OUTENSET_PIN11_Msk               0x00000800UL           /*!< Output enable for pin 11 */
#define GPIO_OUTENSET_PIN12_Msk               0x00001000UL           /*!< Output enable for pin 12 */
#define GPIO_OUTENSET_PIN13_Msk               0x00002000UL           /*!< Output enable for pin 13 */
#define GPIO_OUTENSET_PIN14_Msk               0x00004000UL           /*!< Output enable for pin 14 */
#define GPIO_OUTENSET_PIN15_Msk               0x00008000UL           /*!< Output enable for pin 15 */

/*--  OUTENCLR: Output disable register -----------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Output disable */
} _GPIO_OUTENCLR_bits;

/* Bit field positions: */
#define GPIO_OUTENCLR_VAL_Pos                 0                      /*!< Output disable */

/* Bit field masks: */
#define GPIO_OUTENCLR_VAL_Msk                 0x0000FFFFUL           /*!< Output disable */

/*--  ALTFUNCSET: Alternative function enable register --------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Alternative function enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Alternative function enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Alternative function enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Alternative function enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Alternative function enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Alternative function enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Alternative function enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Alternative function enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Alternative function enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Alternative function enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Alternative function enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Alternative function enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Alternative function enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Alternative function enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Alternative function enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Alternative function enable for pin 15 */
} _GPIO_ALTFUNCSET_bits;

/* Bit field positions: */
#define GPIO_ALTFUNCSET_PIN0_Pos              0                      /*!< Alternative function enable for pin 0 */
#define GPIO_ALTFUNCSET_PIN1_Pos              1                      /*!< Alternative function enable for pin 1 */
#define GPIO_ALTFUNCSET_PIN2_Pos              2                      /*!< Alternative function enable for pin 2 */
#define GPIO_ALTFUNCSET_PIN3_Pos              3                      /*!< Alternative function enable for pin 3 */
#define GPIO_ALTFUNCSET_PIN4_Pos              4                      /*!< Alternative function enable for pin 4 */
#define GPIO_ALTFUNCSET_PIN5_Pos              5                      /*!< Alternative function enable for pin 5 */
#define GPIO_ALTFUNCSET_PIN6_Pos              6                      /*!< Alternative function enable for pin 6 */
#define GPIO_ALTFUNCSET_PIN7_Pos              7                      /*!< Alternative function enable for pin 7 */
#define GPIO_ALTFUNCSET_PIN8_Pos              8                      /*!< Alternative function enable for pin 8 */
#define GPIO_ALTFUNCSET_PIN9_Pos              9                      /*!< Alternative function enable for pin 9 */
#define GPIO_ALTFUNCSET_PIN10_Pos             10                     /*!< Alternative function enable for pin 10 */
#define GPIO_ALTFUNCSET_PIN11_Pos             11                     /*!< Alternative function enable for pin 11 */
#define GPIO_ALTFUNCSET_PIN12_Pos             12                     /*!< Alternative function enable for pin 12 */
#define GPIO_ALTFUNCSET_PIN13_Pos             13                     /*!< Alternative function enable for pin 13 */
#define GPIO_ALTFUNCSET_PIN14_Pos             14                     /*!< Alternative function enable for pin 14 */
#define GPIO_ALTFUNCSET_PIN15_Pos             15                     /*!< Alternative function enable for pin 15 */

/* Bit field masks: */
#define GPIO_ALTFUNCSET_PIN0_Msk              0x00000001UL           /*!< Alternative function enable for pin 0 */
#define GPIO_ALTFUNCSET_PIN1_Msk              0x00000002UL           /*!< Alternative function enable for pin 1 */
#define GPIO_ALTFUNCSET_PIN2_Msk              0x00000004UL           /*!< Alternative function enable for pin 2 */
#define GPIO_ALTFUNCSET_PIN3_Msk              0x00000008UL           /*!< Alternative function enable for pin 3 */
#define GPIO_ALTFUNCSET_PIN4_Msk              0x00000010UL           /*!< Alternative function enable for pin 4 */
#define GPIO_ALTFUNCSET_PIN5_Msk              0x00000020UL           /*!< Alternative function enable for pin 5 */
#define GPIO_ALTFUNCSET_PIN6_Msk              0x00000040UL           /*!< Alternative function enable for pin 6 */
#define GPIO_ALTFUNCSET_PIN7_Msk              0x00000080UL           /*!< Alternative function enable for pin 7 */
#define GPIO_ALTFUNCSET_PIN8_Msk              0x00000100UL           /*!< Alternative function enable for pin 8 */
#define GPIO_ALTFUNCSET_PIN9_Msk              0x00000200UL           /*!< Alternative function enable for pin 9 */
#define GPIO_ALTFUNCSET_PIN10_Msk             0x00000400UL           /*!< Alternative function enable for pin 10 */
#define GPIO_ALTFUNCSET_PIN11_Msk             0x00000800UL           /*!< Alternative function enable for pin 11 */
#define GPIO_ALTFUNCSET_PIN12_Msk             0x00001000UL           /*!< Alternative function enable for pin 12 */
#define GPIO_ALTFUNCSET_PIN13_Msk             0x00002000UL           /*!< Alternative function enable for pin 13 */
#define GPIO_ALTFUNCSET_PIN14_Msk             0x00004000UL           /*!< Alternative function enable for pin 14 */
#define GPIO_ALTFUNCSET_PIN15_Msk             0x00008000UL           /*!< Alternative function enable for pin 15 */

/*--  ALTFUNCCLR: Alternative function disable register -------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Alternative function disable */
} _GPIO_ALTFUNCCLR_bits;

/* Bit field positions: */
#define GPIO_ALTFUNCCLR_VAL_Pos               0                      /*!< Alternative function disable */

/* Bit field masks: */
#define GPIO_ALTFUNCCLR_VAL_Msk               0x0000FFFFUL           /*!< Alternative function disable */

/*--  ALTFUNCNUM: Alternative function number register --------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :2;                                /*!< Select altfunc number for pin 0 */
  uint32_t PIN1                   :2;                                /*!< Select altfunc number for pin 1 */
  uint32_t PIN2                   :2;                                /*!< Select altfunc number for pin 2 */
  uint32_t PIN3                   :2;                                /*!< Select altfunc number for pin 3 */
  uint32_t PIN4                   :2;                                /*!< Select altfunc number for pin 4 */
  uint32_t PIN5                   :2;                                /*!< Select altfunc number for pin 5 */
  uint32_t PIN6                   :2;                                /*!< Select altfunc number for pin 6 */
  uint32_t PIN7                   :2;                                /*!< Select altfunc number for pin 7 */
  uint32_t PIN8                   :2;                                /*!< Select altfunc number for pin 8 */
  uint32_t PIN9                   :2;                                /*!< Select altfunc number for pin 9 */
  uint32_t PIN10                  :2;                                /*!< Select altfunc number for pin 10 */
  uint32_t PIN11                  :2;                                /*!< Select altfunc number for pin 11 */
  uint32_t PIN12                  :2;                                /*!< Select altfunc number for pin 12 */
  uint32_t PIN13                  :2;                                /*!< Select altfunc number for pin 13 */
  uint32_t PIN14                  :2;                                /*!< Select altfunc number for pin 14 */
  uint32_t PIN15                  :2;                                /*!< Select altfunc number for pin 15 */
} _GPIO_ALTFUNCNUM_bits;

/* Bit field positions: */
#define GPIO_ALTFUNCNUM_PIN0_Pos              0                      /*!< Select altfunc number for pin 0 */
#define GPIO_ALTFUNCNUM_PIN1_Pos              2                      /*!< Select altfunc number for pin 1 */
#define GPIO_ALTFUNCNUM_PIN2_Pos              4                      /*!< Select altfunc number for pin 2 */
#define GPIO_ALTFUNCNUM_PIN3_Pos              6                      /*!< Select altfunc number for pin 3 */
#define GPIO_ALTFUNCNUM_PIN4_Pos              8                      /*!< Select altfunc number for pin 4 */
#define GPIO_ALTFUNCNUM_PIN5_Pos              10                     /*!< Select altfunc number for pin 5 */
#define GPIO_ALTFUNCNUM_PIN6_Pos              12                     /*!< Select altfunc number for pin 6 */
#define GPIO_ALTFUNCNUM_PIN7_Pos              14                     /*!< Select altfunc number for pin 7 */
#define GPIO_ALTFUNCNUM_PIN8_Pos              16                     /*!< Select altfunc number for pin 8 */
#define GPIO_ALTFUNCNUM_PIN9_Pos              18                     /*!< Select altfunc number for pin 9 */
#define GPIO_ALTFUNCNUM_PIN10_Pos             20                     /*!< Select altfunc number for pin 10 */
#define GPIO_ALTFUNCNUM_PIN11_Pos             22                     /*!< Select altfunc number for pin 11 */
#define GPIO_ALTFUNCNUM_PIN12_Pos             24                     /*!< Select altfunc number for pin 12 */
#define GPIO_ALTFUNCNUM_PIN13_Pos             26                     /*!< Select altfunc number for pin 13 */
#define GPIO_ALTFUNCNUM_PIN14_Pos             28                     /*!< Select altfunc number for pin 14 */
#define GPIO_ALTFUNCNUM_PIN15_Pos             30                     /*!< Select altfunc number for pin 15 */

/* Bit field masks: */
#define GPIO_ALTFUNCNUM_PIN0_Msk              0x00000003UL           /*!< Select altfunc number for pin 0 */
#define GPIO_ALTFUNCNUM_PIN1_Msk              0x0000000CUL           /*!< Select altfunc number for pin 1 */
#define GPIO_ALTFUNCNUM_PIN2_Msk              0x00000030UL           /*!< Select altfunc number for pin 2 */
#define GPIO_ALTFUNCNUM_PIN3_Msk              0x000000C0UL           /*!< Select altfunc number for pin 3 */
#define GPIO_ALTFUNCNUM_PIN4_Msk              0x00000300UL           /*!< Select altfunc number for pin 4 */
#define GPIO_ALTFUNCNUM_PIN5_Msk              0x00000C00UL           /*!< Select altfunc number for pin 5 */
#define GPIO_ALTFUNCNUM_PIN6_Msk              0x00003000UL           /*!< Select altfunc number for pin 6 */
#define GPIO_ALTFUNCNUM_PIN7_Msk              0x0000C000UL           /*!< Select altfunc number for pin 7 */
#define GPIO_ALTFUNCNUM_PIN8_Msk              0x00030000UL           /*!< Select altfunc number for pin 8 */
#define GPIO_ALTFUNCNUM_PIN9_Msk              0x000C0000UL           /*!< Select altfunc number for pin 9 */
#define GPIO_ALTFUNCNUM_PIN10_Msk             0x00300000UL           /*!< Select altfunc number for pin 10 */
#define GPIO_ALTFUNCNUM_PIN11_Msk             0x00C00000UL           /*!< Select altfunc number for pin 11 */
#define GPIO_ALTFUNCNUM_PIN12_Msk             0x03000000UL           /*!< Select altfunc number for pin 12 */
#define GPIO_ALTFUNCNUM_PIN13_Msk             0x0C000000UL           /*!< Select altfunc number for pin 13 */
#define GPIO_ALTFUNCNUM_PIN14_Msk             0x30000000UL           /*!< Select altfunc number for pin 14 */
#define GPIO_ALTFUNCNUM_PIN15_Msk             0xC0000000UL           /*!< Select altfunc number for pin 15 */

/* Bit field enums: */
typedef enum {
  GPIO_ALTFUNCNUM_PIN0_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN0_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN0_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN0_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN0_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN1_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN1_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN1_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN1_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN1_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN2_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN2_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN2_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN2_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN2_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN3_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN3_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN3_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN3_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN3_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN4_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN4_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN4_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN4_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN4_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN5_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN5_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN5_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN5_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN5_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN6_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN6_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN6_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN6_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN6_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN7_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN7_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN7_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN7_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN7_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN8_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN8_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN8_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN8_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN8_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN9_Disable               = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN9_AF1                   = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN9_AF2                   = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN9_AF3                   = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN9_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN10_Disable              = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN10_AF1                  = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN10_AF2                  = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN10_AF3                  = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN10_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN11_Disable              = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN11_AF1                  = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN11_AF2                  = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN11_AF3                  = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN11_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN12_Disable              = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN12_AF1                  = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN12_AF2                  = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN12_AF3                  = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN12_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN13_Disable              = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN13_AF1                  = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN13_AF2                  = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN13_AF3                  = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN13_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN14_Disable              = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN14_AF1                  = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN14_AF2                  = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN14_AF3                  = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN14_Enum;

typedef enum {
  GPIO_ALTFUNCNUM_PIN15_Disable              = 0x0UL,                /*!< Altfunc disabled */
  GPIO_ALTFUNCNUM_PIN15_AF1                  = 0x1UL,                /*!< Altfunc 1 enable */
  GPIO_ALTFUNCNUM_PIN15_AF2                  = 0x2UL,                /*!< Altfunc 2 enable */
  GPIO_ALTFUNCNUM_PIN15_AF3                  = 0x3UL,                /*!< Altfunc 3 enable */
} GPIO_ALTFUNCNUM_PIN15_Enum;

/*--  SYNCSET: Additional double flip-flop syncronization enable register -------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Additional double flip-flop syncronization buffer enable for pin 15 */
} _GPIO_SYNCSET_bits;

/* Bit field positions: */
#define GPIO_SYNCSET_PIN0_Pos                 0                      /*!< Additional double flip-flop syncronization buffer enable for pin 0 */
#define GPIO_SYNCSET_PIN1_Pos                 1                      /*!< Additional double flip-flop syncronization buffer enable for pin 1 */
#define GPIO_SYNCSET_PIN2_Pos                 2                      /*!< Additional double flip-flop syncronization buffer enable for pin 2 */
#define GPIO_SYNCSET_PIN3_Pos                 3                      /*!< Additional double flip-flop syncronization buffer enable for pin 3 */
#define GPIO_SYNCSET_PIN4_Pos                 4                      /*!< Additional double flip-flop syncronization buffer enable for pin 4 */
#define GPIO_SYNCSET_PIN5_Pos                 5                      /*!< Additional double flip-flop syncronization buffer enable for pin 5 */
#define GPIO_SYNCSET_PIN6_Pos                 6                      /*!< Additional double flip-flop syncronization buffer enable for pin 6 */
#define GPIO_SYNCSET_PIN7_Pos                 7                      /*!< Additional double flip-flop syncronization buffer enable for pin 7 */
#define GPIO_SYNCSET_PIN8_Pos                 8                      /*!< Additional double flip-flop syncronization buffer enable for pin 8 */
#define GPIO_SYNCSET_PIN9_Pos                 9                      /*!< Additional double flip-flop syncronization buffer enable for pin 9 */
#define GPIO_SYNCSET_PIN10_Pos                10                     /*!< Additional double flip-flop syncronization buffer enable for pin 10 */
#define GPIO_SYNCSET_PIN11_Pos                11                     /*!< Additional double flip-flop syncronization buffer enable for pin 11 */
#define GPIO_SYNCSET_PIN12_Pos                12                     /*!< Additional double flip-flop syncronization buffer enable for pin 12 */
#define GPIO_SYNCSET_PIN13_Pos                13                     /*!< Additional double flip-flop syncronization buffer enable for pin 13 */
#define GPIO_SYNCSET_PIN14_Pos                14                     /*!< Additional double flip-flop syncronization buffer enable for pin 14 */
#define GPIO_SYNCSET_PIN15_Pos                15                     /*!< Additional double flip-flop syncronization buffer enable for pin 15 */

/* Bit field masks: */
#define GPIO_SYNCSET_PIN0_Msk                 0x00000001UL           /*!< Additional double flip-flop syncronization buffer enable for pin 0 */
#define GPIO_SYNCSET_PIN1_Msk                 0x00000002UL           /*!< Additional double flip-flop syncronization buffer enable for pin 1 */
#define GPIO_SYNCSET_PIN2_Msk                 0x00000004UL           /*!< Additional double flip-flop syncronization buffer enable for pin 2 */
#define GPIO_SYNCSET_PIN3_Msk                 0x00000008UL           /*!< Additional double flip-flop syncronization buffer enable for pin 3 */
#define GPIO_SYNCSET_PIN4_Msk                 0x00000010UL           /*!< Additional double flip-flop syncronization buffer enable for pin 4 */
#define GPIO_SYNCSET_PIN5_Msk                 0x00000020UL           /*!< Additional double flip-flop syncronization buffer enable for pin 5 */
#define GPIO_SYNCSET_PIN6_Msk                 0x00000040UL           /*!< Additional double flip-flop syncronization buffer enable for pin 6 */
#define GPIO_SYNCSET_PIN7_Msk                 0x00000080UL           /*!< Additional double flip-flop syncronization buffer enable for pin 7 */
#define GPIO_SYNCSET_PIN8_Msk                 0x00000100UL           /*!< Additional double flip-flop syncronization buffer enable for pin 8 */
#define GPIO_SYNCSET_PIN9_Msk                 0x00000200UL           /*!< Additional double flip-flop syncronization buffer enable for pin 9 */
#define GPIO_SYNCSET_PIN10_Msk                0x00000400UL           /*!< Additional double flip-flop syncronization buffer enable for pin 10 */
#define GPIO_SYNCSET_PIN11_Msk                0x00000800UL           /*!< Additional double flip-flop syncronization buffer enable for pin 11 */
#define GPIO_SYNCSET_PIN12_Msk                0x00001000UL           /*!< Additional double flip-flop syncronization buffer enable for pin 12 */
#define GPIO_SYNCSET_PIN13_Msk                0x00002000UL           /*!< Additional double flip-flop syncronization buffer enable for pin 13 */
#define GPIO_SYNCSET_PIN14_Msk                0x00004000UL           /*!< Additional double flip-flop syncronization buffer enable for pin 14 */
#define GPIO_SYNCSET_PIN15_Msk                0x00008000UL           /*!< Additional double flip-flop syncronization buffer enable for pin 15 */

/*--  SYNCCLR: Additional double flip-flop syncronization disable register ------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Additional double flip-flop syncronization disable */
} _GPIO_SYNCCLR_bits;

/* Bit field positions: */
#define GPIO_SYNCCLR_VAL_Pos                  0                      /*!< Additional double flip-flop syncronization disable */

/* Bit field masks: */
#define GPIO_SYNCCLR_VAL_Msk                  0x0000FFFFUL           /*!< Additional double flip-flop syncronization disable */

/*--  QUALSET: Qualifier enable register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Qualifier enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Qualifier enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Qualifier enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Qualifier enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Qualifier enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Qualifier enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Qualifier enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Qualifier enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Qualifier enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Qualifier enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Qualifier enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Qualifier enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Qualifier enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Qualifier enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Qualifier enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Qualifier enable for pin 15 */
} _GPIO_QUALSET_bits;

/* Bit field positions: */
#define GPIO_QUALSET_PIN0_Pos                 0                      /*!< Qualifier enable for pin 0 */
#define GPIO_QUALSET_PIN1_Pos                 1                      /*!< Qualifier enable for pin 1 */
#define GPIO_QUALSET_PIN2_Pos                 2                      /*!< Qualifier enable for pin 2 */
#define GPIO_QUALSET_PIN3_Pos                 3                      /*!< Qualifier enable for pin 3 */
#define GPIO_QUALSET_PIN4_Pos                 4                      /*!< Qualifier enable for pin 4 */
#define GPIO_QUALSET_PIN5_Pos                 5                      /*!< Qualifier enable for pin 5 */
#define GPIO_QUALSET_PIN6_Pos                 6                      /*!< Qualifier enable for pin 6 */
#define GPIO_QUALSET_PIN7_Pos                 7                      /*!< Qualifier enable for pin 7 */
#define GPIO_QUALSET_PIN8_Pos                 8                      /*!< Qualifier enable for pin 8 */
#define GPIO_QUALSET_PIN9_Pos                 9                      /*!< Qualifier enable for pin 9 */
#define GPIO_QUALSET_PIN10_Pos                10                     /*!< Qualifier enable for pin 10 */
#define GPIO_QUALSET_PIN11_Pos                11                     /*!< Qualifier enable for pin 11 */
#define GPIO_QUALSET_PIN12_Pos                12                     /*!< Qualifier enable for pin 12 */
#define GPIO_QUALSET_PIN13_Pos                13                     /*!< Qualifier enable for pin 13 */
#define GPIO_QUALSET_PIN14_Pos                14                     /*!< Qualifier enable for pin 14 */
#define GPIO_QUALSET_PIN15_Pos                15                     /*!< Qualifier enable for pin 15 */

/* Bit field masks: */
#define GPIO_QUALSET_PIN0_Msk                 0x00000001UL           /*!< Qualifier enable for pin 0 */
#define GPIO_QUALSET_PIN1_Msk                 0x00000002UL           /*!< Qualifier enable for pin 1 */
#define GPIO_QUALSET_PIN2_Msk                 0x00000004UL           /*!< Qualifier enable for pin 2 */
#define GPIO_QUALSET_PIN3_Msk                 0x00000008UL           /*!< Qualifier enable for pin 3 */
#define GPIO_QUALSET_PIN4_Msk                 0x00000010UL           /*!< Qualifier enable for pin 4 */
#define GPIO_QUALSET_PIN5_Msk                 0x00000020UL           /*!< Qualifier enable for pin 5 */
#define GPIO_QUALSET_PIN6_Msk                 0x00000040UL           /*!< Qualifier enable for pin 6 */
#define GPIO_QUALSET_PIN7_Msk                 0x00000080UL           /*!< Qualifier enable for pin 7 */
#define GPIO_QUALSET_PIN8_Msk                 0x00000100UL           /*!< Qualifier enable for pin 8 */
#define GPIO_QUALSET_PIN9_Msk                 0x00000200UL           /*!< Qualifier enable for pin 9 */
#define GPIO_QUALSET_PIN10_Msk                0x00000400UL           /*!< Qualifier enable for pin 10 */
#define GPIO_QUALSET_PIN11_Msk                0x00000800UL           /*!< Qualifier enable for pin 11 */
#define GPIO_QUALSET_PIN12_Msk                0x00001000UL           /*!< Qualifier enable for pin 12 */
#define GPIO_QUALSET_PIN13_Msk                0x00002000UL           /*!< Qualifier enable for pin 13 */
#define GPIO_QUALSET_PIN14_Msk                0x00004000UL           /*!< Qualifier enable for pin 14 */
#define GPIO_QUALSET_PIN15_Msk                0x00008000UL           /*!< Qualifier enable for pin 15 */

/*--  QUALCLR: Qualifier disable register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Qualifier disable */
} _GPIO_QUALCLR_bits;

/* Bit field positions: */
#define GPIO_QUALCLR_VAL_Pos                  0                      /*!< Qualifier disable */

/* Bit field masks: */
#define GPIO_QUALCLR_VAL_Msk                  0x0000FFFFUL           /*!< Qualifier disable */

/*--  QUALMODESET: Qualifier mode set register ----------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Qualifier mode set for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Qualifier mode set for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Qualifier mode set for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Qualifier mode set for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Qualifier mode set for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Qualifier mode set for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Qualifier mode set for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Qualifier mode set for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Qualifier mode set for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Qualifier mode set for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Qualifier mode set for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Qualifier mode set for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Qualifier mode set for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Qualifier mode set for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Qualifier mode set for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Qualifier mode set for pin 15 */
} _GPIO_QUALMODESET_bits;

/* Bit field positions: */
#define GPIO_QUALMODESET_PIN0_Pos             0                      /*!< Qualifier mode set for pin 0 */
#define GPIO_QUALMODESET_PIN1_Pos             1                      /*!< Qualifier mode set for pin 1 */
#define GPIO_QUALMODESET_PIN2_Pos             2                      /*!< Qualifier mode set for pin 2 */
#define GPIO_QUALMODESET_PIN3_Pos             3                      /*!< Qualifier mode set for pin 3 */
#define GPIO_QUALMODESET_PIN4_Pos             4                      /*!< Qualifier mode set for pin 4 */
#define GPIO_QUALMODESET_PIN5_Pos             5                      /*!< Qualifier mode set for pin 5 */
#define GPIO_QUALMODESET_PIN6_Pos             6                      /*!< Qualifier mode set for pin 6 */
#define GPIO_QUALMODESET_PIN7_Pos             7                      /*!< Qualifier mode set for pin 7 */
#define GPIO_QUALMODESET_PIN8_Pos             8                      /*!< Qualifier mode set for pin 8 */
#define GPIO_QUALMODESET_PIN9_Pos             9                      /*!< Qualifier mode set for pin 9 */
#define GPIO_QUALMODESET_PIN10_Pos            10                     /*!< Qualifier mode set for pin 10 */
#define GPIO_QUALMODESET_PIN11_Pos            11                     /*!< Qualifier mode set for pin 11 */
#define GPIO_QUALMODESET_PIN12_Pos            12                     /*!< Qualifier mode set for pin 12 */
#define GPIO_QUALMODESET_PIN13_Pos            13                     /*!< Qualifier mode set for pin 13 */
#define GPIO_QUALMODESET_PIN14_Pos            14                     /*!< Qualifier mode set for pin 14 */
#define GPIO_QUALMODESET_PIN15_Pos            15                     /*!< Qualifier mode set for pin 15 */

/* Bit field masks: */
#define GPIO_QUALMODESET_PIN0_Msk             0x00000001UL           /*!< Qualifier mode set for pin 0 */
#define GPIO_QUALMODESET_PIN1_Msk             0x00000002UL           /*!< Qualifier mode set for pin 1 */
#define GPIO_QUALMODESET_PIN2_Msk             0x00000004UL           /*!< Qualifier mode set for pin 2 */
#define GPIO_QUALMODESET_PIN3_Msk             0x00000008UL           /*!< Qualifier mode set for pin 3 */
#define GPIO_QUALMODESET_PIN4_Msk             0x00000010UL           /*!< Qualifier mode set for pin 4 */
#define GPIO_QUALMODESET_PIN5_Msk             0x00000020UL           /*!< Qualifier mode set for pin 5 */
#define GPIO_QUALMODESET_PIN6_Msk             0x00000040UL           /*!< Qualifier mode set for pin 6 */
#define GPIO_QUALMODESET_PIN7_Msk             0x00000080UL           /*!< Qualifier mode set for pin 7 */
#define GPIO_QUALMODESET_PIN8_Msk             0x00000100UL           /*!< Qualifier mode set for pin 8 */
#define GPIO_QUALMODESET_PIN9_Msk             0x00000200UL           /*!< Qualifier mode set for pin 9 */
#define GPIO_QUALMODESET_PIN10_Msk            0x00000400UL           /*!< Qualifier mode set for pin 10 */
#define GPIO_QUALMODESET_PIN11_Msk            0x00000800UL           /*!< Qualifier mode set for pin 11 */
#define GPIO_QUALMODESET_PIN12_Msk            0x00001000UL           /*!< Qualifier mode set for pin 12 */
#define GPIO_QUALMODESET_PIN13_Msk            0x00002000UL           /*!< Qualifier mode set for pin 13 */
#define GPIO_QUALMODESET_PIN14_Msk            0x00004000UL           /*!< Qualifier mode set for pin 14 */
#define GPIO_QUALMODESET_PIN15_Msk            0x00008000UL           /*!< Qualifier mode set for pin 15 */

/*--  QUALMODECLR: Qualifier mode clear register --------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Qualifier mode clear */
} _GPIO_QUALMODECLR_bits;

/* Bit field positions: */
#define GPIO_QUALMODECLR_VAL_Pos              0                      /*!< Qualifier mode clear */

/* Bit field masks: */
#define GPIO_QUALMODECLR_VAL_Msk              0x0000FFFFUL           /*!< Qualifier mode clear */

/*--  QUALSAMPLE: Qualifier sample period register ------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :8;                                /*!< Qualifier sample period */
} _GPIO_QUALSAMPLE_bits;

/* Bit field positions: */
#define GPIO_QUALSAMPLE_VAL_Pos               0                      /*!< Qualifier sample period */

/* Bit field masks: */
#define GPIO_QUALSAMPLE_VAL_Msk               0x000000FFUL           /*!< Qualifier sample period */

/*--  INTENSET: Interrupt enable register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Interrupt enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Interrupt enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Interrupt enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Interrupt enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Interrupt enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Interrupt enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Interrupt enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Interrupt enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Interrupt enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Interrupt enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Interrupt enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Interrupt enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Interrupt enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Interrupt enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Interrupt enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Interrupt enable for pin 15 */
} _GPIO_INTENSET_bits;

/* Bit field positions: */
#define GPIO_INTENSET_PIN0_Pos                0                      /*!< Interrupt enable for pin 0 */
#define GPIO_INTENSET_PIN1_Pos                1                      /*!< Interrupt enable for pin 1 */
#define GPIO_INTENSET_PIN2_Pos                2                      /*!< Interrupt enable for pin 2 */
#define GPIO_INTENSET_PIN3_Pos                3                      /*!< Interrupt enable for pin 3 */
#define GPIO_INTENSET_PIN4_Pos                4                      /*!< Interrupt enable for pin 4 */
#define GPIO_INTENSET_PIN5_Pos                5                      /*!< Interrupt enable for pin 5 */
#define GPIO_INTENSET_PIN6_Pos                6                      /*!< Interrupt enable for pin 6 */
#define GPIO_INTENSET_PIN7_Pos                7                      /*!< Interrupt enable for pin 7 */
#define GPIO_INTENSET_PIN8_Pos                8                      /*!< Interrupt enable for pin 8 */
#define GPIO_INTENSET_PIN9_Pos                9                      /*!< Interrupt enable for pin 9 */
#define GPIO_INTENSET_PIN10_Pos               10                     /*!< Interrupt enable for pin 10 */
#define GPIO_INTENSET_PIN11_Pos               11                     /*!< Interrupt enable for pin 11 */
#define GPIO_INTENSET_PIN12_Pos               12                     /*!< Interrupt enable for pin 12 */
#define GPIO_INTENSET_PIN13_Pos               13                     /*!< Interrupt enable for pin 13 */
#define GPIO_INTENSET_PIN14_Pos               14                     /*!< Interrupt enable for pin 14 */
#define GPIO_INTENSET_PIN15_Pos               15                     /*!< Interrupt enable for pin 15 */

/* Bit field masks: */
#define GPIO_INTENSET_PIN0_Msk                0x00000001UL           /*!< Interrupt enable for pin 0 */
#define GPIO_INTENSET_PIN1_Msk                0x00000002UL           /*!< Interrupt enable for pin 1 */
#define GPIO_INTENSET_PIN2_Msk                0x00000004UL           /*!< Interrupt enable for pin 2 */
#define GPIO_INTENSET_PIN3_Msk                0x00000008UL           /*!< Interrupt enable for pin 3 */
#define GPIO_INTENSET_PIN4_Msk                0x00000010UL           /*!< Interrupt enable for pin 4 */
#define GPIO_INTENSET_PIN5_Msk                0x00000020UL           /*!< Interrupt enable for pin 5 */
#define GPIO_INTENSET_PIN6_Msk                0x00000040UL           /*!< Interrupt enable for pin 6 */
#define GPIO_INTENSET_PIN7_Msk                0x00000080UL           /*!< Interrupt enable for pin 7 */
#define GPIO_INTENSET_PIN8_Msk                0x00000100UL           /*!< Interrupt enable for pin 8 */
#define GPIO_INTENSET_PIN9_Msk                0x00000200UL           /*!< Interrupt enable for pin 9 */
#define GPIO_INTENSET_PIN10_Msk               0x00000400UL           /*!< Interrupt enable for pin 10 */
#define GPIO_INTENSET_PIN11_Msk               0x00000800UL           /*!< Interrupt enable for pin 11 */
#define GPIO_INTENSET_PIN12_Msk               0x00001000UL           /*!< Interrupt enable for pin 12 */
#define GPIO_INTENSET_PIN13_Msk               0x00002000UL           /*!< Interrupt enable for pin 13 */
#define GPIO_INTENSET_PIN14_Msk               0x00004000UL           /*!< Interrupt enable for pin 14 */
#define GPIO_INTENSET_PIN15_Msk               0x00008000UL           /*!< Interrupt enable for pin 15 */

/*--  INTENCLR: Interrupt disable register --------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Interrupt disable */
} _GPIO_INTENCLR_bits;

/* Bit field positions: */
#define GPIO_INTENCLR_VAL_Pos                 0                      /*!< Interrupt disable */

/* Bit field masks: */
#define GPIO_INTENCLR_VAL_Msk                 0x0000FFFFUL           /*!< Interrupt disable */

/*--  INTTYPESET: Interrupt type set register -----------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Interrupt type set for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Interrupt type set for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Interrupt type set for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Interrupt type set for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Interrupt type set for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Interrupt type set for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Interrupt type set for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Interrupt type set for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Interrupt type set for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Interrupt type set for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Interrupt type set for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Interrupt type set for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Interrupt type set for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Interrupt type set for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Interrupt type set for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Interrupt type set for pin 15 */
} _GPIO_INTTYPESET_bits;

/* Bit field positions: */
#define GPIO_INTTYPESET_PIN0_Pos              0                      /*!< Interrupt type set for pin 0 */
#define GPIO_INTTYPESET_PIN1_Pos              1                      /*!< Interrupt type set for pin 1 */
#define GPIO_INTTYPESET_PIN2_Pos              2                      /*!< Interrupt type set for pin 2 */
#define GPIO_INTTYPESET_PIN3_Pos              3                      /*!< Interrupt type set for pin 3 */
#define GPIO_INTTYPESET_PIN4_Pos              4                      /*!< Interrupt type set for pin 4 */
#define GPIO_INTTYPESET_PIN5_Pos              5                      /*!< Interrupt type set for pin 5 */
#define GPIO_INTTYPESET_PIN6_Pos              6                      /*!< Interrupt type set for pin 6 */
#define GPIO_INTTYPESET_PIN7_Pos              7                      /*!< Interrupt type set for pin 7 */
#define GPIO_INTTYPESET_PIN8_Pos              8                      /*!< Interrupt type set for pin 8 */
#define GPIO_INTTYPESET_PIN9_Pos              9                      /*!< Interrupt type set for pin 9 */
#define GPIO_INTTYPESET_PIN10_Pos             10                     /*!< Interrupt type set for pin 10 */
#define GPIO_INTTYPESET_PIN11_Pos             11                     /*!< Interrupt type set for pin 11 */
#define GPIO_INTTYPESET_PIN12_Pos             12                     /*!< Interrupt type set for pin 12 */
#define GPIO_INTTYPESET_PIN13_Pos             13                     /*!< Interrupt type set for pin 13 */
#define GPIO_INTTYPESET_PIN14_Pos             14                     /*!< Interrupt type set for pin 14 */
#define GPIO_INTTYPESET_PIN15_Pos             15                     /*!< Interrupt type set for pin 15 */

/* Bit field masks: */
#define GPIO_INTTYPESET_PIN0_Msk              0x00000001UL           /*!< Interrupt type set for pin 0 */
#define GPIO_INTTYPESET_PIN1_Msk              0x00000002UL           /*!< Interrupt type set for pin 1 */
#define GPIO_INTTYPESET_PIN2_Msk              0x00000004UL           /*!< Interrupt type set for pin 2 */
#define GPIO_INTTYPESET_PIN3_Msk              0x00000008UL           /*!< Interrupt type set for pin 3 */
#define GPIO_INTTYPESET_PIN4_Msk              0x00000010UL           /*!< Interrupt type set for pin 4 */
#define GPIO_INTTYPESET_PIN5_Msk              0x00000020UL           /*!< Interrupt type set for pin 5 */
#define GPIO_INTTYPESET_PIN6_Msk              0x00000040UL           /*!< Interrupt type set for pin 6 */
#define GPIO_INTTYPESET_PIN7_Msk              0x00000080UL           /*!< Interrupt type set for pin 7 */
#define GPIO_INTTYPESET_PIN8_Msk              0x00000100UL           /*!< Interrupt type set for pin 8 */
#define GPIO_INTTYPESET_PIN9_Msk              0x00000200UL           /*!< Interrupt type set for pin 9 */
#define GPIO_INTTYPESET_PIN10_Msk             0x00000400UL           /*!< Interrupt type set for pin 10 */
#define GPIO_INTTYPESET_PIN11_Msk             0x00000800UL           /*!< Interrupt type set for pin 11 */
#define GPIO_INTTYPESET_PIN12_Msk             0x00001000UL           /*!< Interrupt type set for pin 12 */
#define GPIO_INTTYPESET_PIN13_Msk             0x00002000UL           /*!< Interrupt type set for pin 13 */
#define GPIO_INTTYPESET_PIN14_Msk             0x00004000UL           /*!< Interrupt type set for pin 14 */
#define GPIO_INTTYPESET_PIN15_Msk             0x00008000UL           /*!< Interrupt type set for pin 15 */

/*--  INTTYPECLR: Interrupt type clear register ---------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Interrupt type clear */
} _GPIO_INTTYPECLR_bits;

/* Bit field positions: */
#define GPIO_INTTYPECLR_VAL_Pos               0                      /*!< Interrupt type clear */

/* Bit field masks: */
#define GPIO_INTTYPECLR_VAL_Msk               0x0000FFFFUL           /*!< Interrupt type clear */

/*--  INTPOLSET: Interrupt polarity set register --------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Interrupt polarity set for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Interrupt polarity set for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Interrupt polarity set for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Interrupt polarity set for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Interrupt polarity set for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Interrupt polarity set for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Interrupt polarity set for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Interrupt polarity set for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Interrupt polarity set for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Interrupt polarity set for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Interrupt polarity set for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Interrupt polarity set for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Interrupt polarity set for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Interrupt polarity set for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Interrupt polarity set for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Interrupt polarity set for pin 15 */
} _GPIO_INTPOLSET_bits;

/* Bit field positions: */
#define GPIO_INTPOLSET_PIN0_Pos               0                      /*!< Interrupt polarity set for pin 0 */
#define GPIO_INTPOLSET_PIN1_Pos               1                      /*!< Interrupt polarity set for pin 1 */
#define GPIO_INTPOLSET_PIN2_Pos               2                      /*!< Interrupt polarity set for pin 2 */
#define GPIO_INTPOLSET_PIN3_Pos               3                      /*!< Interrupt polarity set for pin 3 */
#define GPIO_INTPOLSET_PIN4_Pos               4                      /*!< Interrupt polarity set for pin 4 */
#define GPIO_INTPOLSET_PIN5_Pos               5                      /*!< Interrupt polarity set for pin 5 */
#define GPIO_INTPOLSET_PIN6_Pos               6                      /*!< Interrupt polarity set for pin 6 */
#define GPIO_INTPOLSET_PIN7_Pos               7                      /*!< Interrupt polarity set for pin 7 */
#define GPIO_INTPOLSET_PIN8_Pos               8                      /*!< Interrupt polarity set for pin 8 */
#define GPIO_INTPOLSET_PIN9_Pos               9                      /*!< Interrupt polarity set for pin 9 */
#define GPIO_INTPOLSET_PIN10_Pos              10                     /*!< Interrupt polarity set for pin 10 */
#define GPIO_INTPOLSET_PIN11_Pos              11                     /*!< Interrupt polarity set for pin 11 */
#define GPIO_INTPOLSET_PIN12_Pos              12                     /*!< Interrupt polarity set for pin 12 */
#define GPIO_INTPOLSET_PIN13_Pos              13                     /*!< Interrupt polarity set for pin 13 */
#define GPIO_INTPOLSET_PIN14_Pos              14                     /*!< Interrupt polarity set for pin 14 */
#define GPIO_INTPOLSET_PIN15_Pos              15                     /*!< Interrupt polarity set for pin 15 */

/* Bit field masks: */
#define GPIO_INTPOLSET_PIN0_Msk               0x00000001UL           /*!< Interrupt polarity set for pin 0 */
#define GPIO_INTPOLSET_PIN1_Msk               0x00000002UL           /*!< Interrupt polarity set for pin 1 */
#define GPIO_INTPOLSET_PIN2_Msk               0x00000004UL           /*!< Interrupt polarity set for pin 2 */
#define GPIO_INTPOLSET_PIN3_Msk               0x00000008UL           /*!< Interrupt polarity set for pin 3 */
#define GPIO_INTPOLSET_PIN4_Msk               0x00000010UL           /*!< Interrupt polarity set for pin 4 */
#define GPIO_INTPOLSET_PIN5_Msk               0x00000020UL           /*!< Interrupt polarity set for pin 5 */
#define GPIO_INTPOLSET_PIN6_Msk               0x00000040UL           /*!< Interrupt polarity set for pin 6 */
#define GPIO_INTPOLSET_PIN7_Msk               0x00000080UL           /*!< Interrupt polarity set for pin 7 */
#define GPIO_INTPOLSET_PIN8_Msk               0x00000100UL           /*!< Interrupt polarity set for pin 8 */
#define GPIO_INTPOLSET_PIN9_Msk               0x00000200UL           /*!< Interrupt polarity set for pin 9 */
#define GPIO_INTPOLSET_PIN10_Msk              0x00000400UL           /*!< Interrupt polarity set for pin 10 */
#define GPIO_INTPOLSET_PIN11_Msk              0x00000800UL           /*!< Interrupt polarity set for pin 11 */
#define GPIO_INTPOLSET_PIN12_Msk              0x00001000UL           /*!< Interrupt polarity set for pin 12 */
#define GPIO_INTPOLSET_PIN13_Msk              0x00002000UL           /*!< Interrupt polarity set for pin 13 */
#define GPIO_INTPOLSET_PIN14_Msk              0x00004000UL           /*!< Interrupt polarity set for pin 14 */
#define GPIO_INTPOLSET_PIN15_Msk              0x00008000UL           /*!< Interrupt polarity set for pin 15 */

/*--  INTPOLCLR: Interrupt polarity clear register ------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Interrupt polarity clear */
} _GPIO_INTPOLCLR_bits;

/* Bit field positions: */
#define GPIO_INTPOLCLR_VAL_Pos                0                      /*!< Interrupt polarity clear */

/* Bit field masks: */
#define GPIO_INTPOLCLR_VAL_Msk                0x0000FFFFUL           /*!< Interrupt polarity clear */

/*--  INTEDGESET: Interrupt every edge set register -----------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Interrupt every edge set for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Interrupt every edge set for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Interrupt every edge set for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Interrupt every edge set for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Interrupt every edge set for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Interrupt every edge set for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Interrupt every edge set for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Interrupt every edge set for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Interrupt every edge set for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Interrupt every edge set for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Interrupt every edge set for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Interrupt every edge set for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Interrupt every edge set for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Interrupt every edge set for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Interrupt every edge set for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Interrupt every edge set for pin 15 */
} _GPIO_INTEDGESET_bits;

/* Bit field positions: */
#define GPIO_INTEDGESET_PIN0_Pos              0                      /*!< Interrupt every edge set for pin 0 */
#define GPIO_INTEDGESET_PIN1_Pos              1                      /*!< Interrupt every edge set for pin 1 */
#define GPIO_INTEDGESET_PIN2_Pos              2                      /*!< Interrupt every edge set for pin 2 */
#define GPIO_INTEDGESET_PIN3_Pos              3                      /*!< Interrupt every edge set for pin 3 */
#define GPIO_INTEDGESET_PIN4_Pos              4                      /*!< Interrupt every edge set for pin 4 */
#define GPIO_INTEDGESET_PIN5_Pos              5                      /*!< Interrupt every edge set for pin 5 */
#define GPIO_INTEDGESET_PIN6_Pos              6                      /*!< Interrupt every edge set for pin 6 */
#define GPIO_INTEDGESET_PIN7_Pos              7                      /*!< Interrupt every edge set for pin 7 */
#define GPIO_INTEDGESET_PIN8_Pos              8                      /*!< Interrupt every edge set for pin 8 */
#define GPIO_INTEDGESET_PIN9_Pos              9                      /*!< Interrupt every edge set for pin 9 */
#define GPIO_INTEDGESET_PIN10_Pos             10                     /*!< Interrupt every edge set for pin 10 */
#define GPIO_INTEDGESET_PIN11_Pos             11                     /*!< Interrupt every edge set for pin 11 */
#define GPIO_INTEDGESET_PIN12_Pos             12                     /*!< Interrupt every edge set for pin 12 */
#define GPIO_INTEDGESET_PIN13_Pos             13                     /*!< Interrupt every edge set for pin 13 */
#define GPIO_INTEDGESET_PIN14_Pos             14                     /*!< Interrupt every edge set for pin 14 */
#define GPIO_INTEDGESET_PIN15_Pos             15                     /*!< Interrupt every edge set for pin 15 */

/* Bit field masks: */
#define GPIO_INTEDGESET_PIN0_Msk              0x00000001UL           /*!< Interrupt every edge set for pin 0 */
#define GPIO_INTEDGESET_PIN1_Msk              0x00000002UL           /*!< Interrupt every edge set for pin 1 */
#define GPIO_INTEDGESET_PIN2_Msk              0x00000004UL           /*!< Interrupt every edge set for pin 2 */
#define GPIO_INTEDGESET_PIN3_Msk              0x00000008UL           /*!< Interrupt every edge set for pin 3 */
#define GPIO_INTEDGESET_PIN4_Msk              0x00000010UL           /*!< Interrupt every edge set for pin 4 */
#define GPIO_INTEDGESET_PIN5_Msk              0x00000020UL           /*!< Interrupt every edge set for pin 5 */
#define GPIO_INTEDGESET_PIN6_Msk              0x00000040UL           /*!< Interrupt every edge set for pin 6 */
#define GPIO_INTEDGESET_PIN7_Msk              0x00000080UL           /*!< Interrupt every edge set for pin 7 */
#define GPIO_INTEDGESET_PIN8_Msk              0x00000100UL           /*!< Interrupt every edge set for pin 8 */
#define GPIO_INTEDGESET_PIN9_Msk              0x00000200UL           /*!< Interrupt every edge set for pin 9 */
#define GPIO_INTEDGESET_PIN10_Msk             0x00000400UL           /*!< Interrupt every edge set for pin 10 */
#define GPIO_INTEDGESET_PIN11_Msk             0x00000800UL           /*!< Interrupt every edge set for pin 11 */
#define GPIO_INTEDGESET_PIN12_Msk             0x00001000UL           /*!< Interrupt every edge set for pin 12 */
#define GPIO_INTEDGESET_PIN13_Msk             0x00002000UL           /*!< Interrupt every edge set for pin 13 */
#define GPIO_INTEDGESET_PIN14_Msk             0x00004000UL           /*!< Interrupt every edge set for pin 14 */
#define GPIO_INTEDGESET_PIN15_Msk             0x00008000UL           /*!< Interrupt every edge set for pin 15 */

/*--  INTEDGECLR: Interrupt every edge clear register ---------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Interrupt every edge clear */
} _GPIO_INTEDGECLR_bits;

/* Bit field positions: */
#define GPIO_INTEDGECLR_VAL_Pos               0                      /*!< Interrupt every edge clear */

/* Bit field masks: */
#define GPIO_INTEDGECLR_VAL_Msk               0x0000FFFFUL           /*!< Interrupt every edge clear */

/*--  INTSTATUS: Interrupt status -----------------------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Interrupt status of pin 0 */
  uint32_t PIN1                   :1;                                /*!< Interrupt status of pin 1 */
  uint32_t PIN2                   :1;                                /*!< Interrupt status of pin 2 */
  uint32_t PIN3                   :1;                                /*!< Interrupt status of pin 3 */
  uint32_t PIN4                   :1;                                /*!< Interrupt status of pin 4 */
  uint32_t PIN5                   :1;                                /*!< Interrupt status of pin 5 */
  uint32_t PIN6                   :1;                                /*!< Interrupt status of pin 6 */
  uint32_t PIN7                   :1;                                /*!< Interrupt status of pin 7 */
  uint32_t PIN8                   :1;                                /*!< Interrupt status of pin 8 */
  uint32_t PIN9                   :1;                                /*!< Interrupt status of pin 9 */
  uint32_t PIN10                  :1;                                /*!< Interrupt status of pin 10 */
  uint32_t PIN11                  :1;                                /*!< Interrupt status of pin 11 */
  uint32_t PIN12                  :1;                                /*!< Interrupt status of pin 12 */
  uint32_t PIN13                  :1;                                /*!< Interrupt status of pin 13 */
  uint32_t PIN14                  :1;                                /*!< Interrupt status of pin 14 */
  uint32_t PIN15                  :1;                                /*!< Interrupt status of pin 15 */
} _GPIO_INTSTATUS_bits;

/* Bit field positions: */
#define GPIO_INTSTATUS_PIN0_Pos               0                      /*!< Interrupt status of pin 0 */
#define GPIO_INTSTATUS_PIN1_Pos               1                      /*!< Interrupt status of pin 1 */
#define GPIO_INTSTATUS_PIN2_Pos               2                      /*!< Interrupt status of pin 2 */
#define GPIO_INTSTATUS_PIN3_Pos               3                      /*!< Interrupt status of pin 3 */
#define GPIO_INTSTATUS_PIN4_Pos               4                      /*!< Interrupt status of pin 4 */
#define GPIO_INTSTATUS_PIN5_Pos               5                      /*!< Interrupt status of pin 5 */
#define GPIO_INTSTATUS_PIN6_Pos               6                      /*!< Interrupt status of pin 6 */
#define GPIO_INTSTATUS_PIN7_Pos               7                      /*!< Interrupt status of pin 7 */
#define GPIO_INTSTATUS_PIN8_Pos               8                      /*!< Interrupt status of pin 8 */
#define GPIO_INTSTATUS_PIN9_Pos               9                      /*!< Interrupt status of pin 9 */
#define GPIO_INTSTATUS_PIN10_Pos              10                     /*!< Interrupt status of pin 10 */
#define GPIO_INTSTATUS_PIN11_Pos              11                     /*!< Interrupt status of pin 11 */
#define GPIO_INTSTATUS_PIN12_Pos              12                     /*!< Interrupt status of pin 12 */
#define GPIO_INTSTATUS_PIN13_Pos              13                     /*!< Interrupt status of pin 13 */
#define GPIO_INTSTATUS_PIN14_Pos              14                     /*!< Interrupt status of pin 14 */
#define GPIO_INTSTATUS_PIN15_Pos              15                     /*!< Interrupt status of pin 15 */

/* Bit field masks: */
#define GPIO_INTSTATUS_PIN0_Msk               0x00000001UL           /*!< Interrupt status of pin 0 */
#define GPIO_INTSTATUS_PIN1_Msk               0x00000002UL           /*!< Interrupt status of pin 1 */
#define GPIO_INTSTATUS_PIN2_Msk               0x00000004UL           /*!< Interrupt status of pin 2 */
#define GPIO_INTSTATUS_PIN3_Msk               0x00000008UL           /*!< Interrupt status of pin 3 */
#define GPIO_INTSTATUS_PIN4_Msk               0x00000010UL           /*!< Interrupt status of pin 4 */
#define GPIO_INTSTATUS_PIN5_Msk               0x00000020UL           /*!< Interrupt status of pin 5 */
#define GPIO_INTSTATUS_PIN6_Msk               0x00000040UL           /*!< Interrupt status of pin 6 */
#define GPIO_INTSTATUS_PIN7_Msk               0x00000080UL           /*!< Interrupt status of pin 7 */
#define GPIO_INTSTATUS_PIN8_Msk               0x00000100UL           /*!< Interrupt status of pin 8 */
#define GPIO_INTSTATUS_PIN9_Msk               0x00000200UL           /*!< Interrupt status of pin 9 */
#define GPIO_INTSTATUS_PIN10_Msk              0x00000400UL           /*!< Interrupt status of pin 10 */
#define GPIO_INTSTATUS_PIN11_Msk              0x00000800UL           /*!< Interrupt status of pin 11 */
#define GPIO_INTSTATUS_PIN12_Msk              0x00001000UL           /*!< Interrupt status of pin 12 */
#define GPIO_INTSTATUS_PIN13_Msk              0x00002000UL           /*!< Interrupt status of pin 13 */
#define GPIO_INTSTATUS_PIN14_Msk              0x00004000UL           /*!< Interrupt status of pin 14 */
#define GPIO_INTSTATUS_PIN15_Msk              0x00008000UL           /*!< Interrupt status of pin 15 */

/*--  DMATXREQSET: DMA TX request enable register -------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< DMA request enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< DMA request enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< DMA request enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< DMA request enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< DMA request enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< DMA request enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< DMA request enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< DMA request enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< DMA request enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< DMA request enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< DMA request enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< DMA request enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< DMA request enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< DMA request enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< DMA request enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< DMA request enable for pin 15 */
} _GPIO_DMATXREQSET_bits;

/* Bit field positions: */
#define GPIO_DMATXREQSET_PIN0_Pos             0                      /*!< DMA request enable for pin 0 */
#define GPIO_DMATXREQSET_PIN1_Pos             1                      /*!< DMA request enable for pin 1 */
#define GPIO_DMATXREQSET_PIN2_Pos             2                      /*!< DMA request enable for pin 2 */
#define GPIO_DMATXREQSET_PIN3_Pos             3                      /*!< DMA request enable for pin 3 */
#define GPIO_DMATXREQSET_PIN4_Pos             4                      /*!< DMA request enable for pin 4 */
#define GPIO_DMATXREQSET_PIN5_Pos             5                      /*!< DMA request enable for pin 5 */
#define GPIO_DMATXREQSET_PIN6_Pos             6                      /*!< DMA request enable for pin 6 */
#define GPIO_DMATXREQSET_PIN7_Pos             7                      /*!< DMA request enable for pin 7 */
#define GPIO_DMATXREQSET_PIN8_Pos             8                      /*!< DMA request enable for pin 8 */
#define GPIO_DMATXREQSET_PIN9_Pos             9                      /*!< DMA request enable for pin 9 */
#define GPIO_DMATXREQSET_PIN10_Pos            10                     /*!< DMA request enable for pin 10 */
#define GPIO_DMATXREQSET_PIN11_Pos            11                     /*!< DMA request enable for pin 11 */
#define GPIO_DMATXREQSET_PIN12_Pos            12                     /*!< DMA request enable for pin 12 */
#define GPIO_DMATXREQSET_PIN13_Pos            13                     /*!< DMA request enable for pin 13 */
#define GPIO_DMATXREQSET_PIN14_Pos            14                     /*!< DMA request enable for pin 14 */
#define GPIO_DMATXREQSET_PIN15_Pos            15                     /*!< DMA request enable for pin 15 */

/* Bit field masks: */
#define GPIO_DMATXREQSET_PIN0_Msk             0x00000001UL           /*!< DMA request enable for pin 0 */
#define GPIO_DMATXREQSET_PIN1_Msk             0x00000002UL           /*!< DMA request enable for pin 1 */
#define GPIO_DMATXREQSET_PIN2_Msk             0x00000004UL           /*!< DMA request enable for pin 2 */
#define GPIO_DMATXREQSET_PIN3_Msk             0x00000008UL           /*!< DMA request enable for pin 3 */
#define GPIO_DMATXREQSET_PIN4_Msk             0x00000010UL           /*!< DMA request enable for pin 4 */
#define GPIO_DMATXREQSET_PIN5_Msk             0x00000020UL           /*!< DMA request enable for pin 5 */
#define GPIO_DMATXREQSET_PIN6_Msk             0x00000040UL           /*!< DMA request enable for pin 6 */
#define GPIO_DMATXREQSET_PIN7_Msk             0x00000080UL           /*!< DMA request enable for pin 7 */
#define GPIO_DMATXREQSET_PIN8_Msk             0x00000100UL           /*!< DMA request enable for pin 8 */
#define GPIO_DMATXREQSET_PIN9_Msk             0x00000200UL           /*!< DMA request enable for pin 9 */
#define GPIO_DMATXREQSET_PIN10_Msk            0x00000400UL           /*!< DMA request enable for pin 10 */
#define GPIO_DMATXREQSET_PIN11_Msk            0x00000800UL           /*!< DMA request enable for pin 11 */
#define GPIO_DMATXREQSET_PIN12_Msk            0x00001000UL           /*!< DMA request enable for pin 12 */
#define GPIO_DMATXREQSET_PIN13_Msk            0x00002000UL           /*!< DMA request enable for pin 13 */
#define GPIO_DMATXREQSET_PIN14_Msk            0x00004000UL           /*!< DMA request enable for pin 14 */
#define GPIO_DMATXREQSET_PIN15_Msk            0x00008000UL           /*!< DMA request enable for pin 15 */

/*--  DMATXREQCLR: DMA TX request disable register ------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< DMA request disable */
} _GPIO_DMATXREQCLR_bits;

/* Bit field positions: */
#define GPIO_DMATXREQCLR_VAL_Pos              0                      /*!< DMA request disable */

/* Bit field masks: */
#define GPIO_DMATXREQCLR_VAL_Msk              0x0000FFFFUL           /*!< DMA request disable */

/*--  ADCSOCSET: ADC Start Of Conversion enable register ------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< ADC SOC enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< ADC SOC enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< ADC SOC enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< ADC SOC enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< ADC SOC enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< ADC SOC enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< ADC SOC enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< ADC SOC enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< ADC SOC enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< ADC SOC enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< ADC SOC enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< ADC SOC enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< ADC SOC enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< ADC SOC enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< ADC SOC enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< ADC SOC enable for pin 15 */
} _GPIO_ADCSOCSET_bits;

/* Bit field positions: */
#define GPIO_ADCSOCSET_PIN0_Pos               0                      /*!< ADC SOC enable for pin 0 */
#define GPIO_ADCSOCSET_PIN1_Pos               1                      /*!< ADC SOC enable for pin 1 */
#define GPIO_ADCSOCSET_PIN2_Pos               2                      /*!< ADC SOC enable for pin 2 */
#define GPIO_ADCSOCSET_PIN3_Pos               3                      /*!< ADC SOC enable for pin 3 */
#define GPIO_ADCSOCSET_PIN4_Pos               4                      /*!< ADC SOC enable for pin 4 */
#define GPIO_ADCSOCSET_PIN5_Pos               5                      /*!< ADC SOC enable for pin 5 */
#define GPIO_ADCSOCSET_PIN6_Pos               6                      /*!< ADC SOC enable for pin 6 */
#define GPIO_ADCSOCSET_PIN7_Pos               7                      /*!< ADC SOC enable for pin 7 */
#define GPIO_ADCSOCSET_PIN8_Pos               8                      /*!< ADC SOC enable for pin 8 */
#define GPIO_ADCSOCSET_PIN9_Pos               9                      /*!< ADC SOC enable for pin 9 */
#define GPIO_ADCSOCSET_PIN10_Pos              10                     /*!< ADC SOC enable for pin 10 */
#define GPIO_ADCSOCSET_PIN11_Pos              11                     /*!< ADC SOC enable for pin 11 */
#define GPIO_ADCSOCSET_PIN12_Pos              12                     /*!< ADC SOC enable for pin 12 */
#define GPIO_ADCSOCSET_PIN13_Pos              13                     /*!< ADC SOC enable for pin 13 */
#define GPIO_ADCSOCSET_PIN14_Pos              14                     /*!< ADC SOC enable for pin 14 */
#define GPIO_ADCSOCSET_PIN15_Pos              15                     /*!< ADC SOC enable for pin 15 */

/* Bit field masks: */
#define GPIO_ADCSOCSET_PIN0_Msk               0x00000001UL           /*!< ADC SOC enable for pin 0 */
#define GPIO_ADCSOCSET_PIN1_Msk               0x00000002UL           /*!< ADC SOC enable for pin 1 */
#define GPIO_ADCSOCSET_PIN2_Msk               0x00000004UL           /*!< ADC SOC enable for pin 2 */
#define GPIO_ADCSOCSET_PIN3_Msk               0x00000008UL           /*!< ADC SOC enable for pin 3 */
#define GPIO_ADCSOCSET_PIN4_Msk               0x00000010UL           /*!< ADC SOC enable for pin 4 */
#define GPIO_ADCSOCSET_PIN5_Msk               0x00000020UL           /*!< ADC SOC enable for pin 5 */
#define GPIO_ADCSOCSET_PIN6_Msk               0x00000040UL           /*!< ADC SOC enable for pin 6 */
#define GPIO_ADCSOCSET_PIN7_Msk               0x00000080UL           /*!< ADC SOC enable for pin 7 */
#define GPIO_ADCSOCSET_PIN8_Msk               0x00000100UL           /*!< ADC SOC enable for pin 8 */
#define GPIO_ADCSOCSET_PIN9_Msk               0x00000200UL           /*!< ADC SOC enable for pin 9 */
#define GPIO_ADCSOCSET_PIN10_Msk              0x00000400UL           /*!< ADC SOC enable for pin 10 */
#define GPIO_ADCSOCSET_PIN11_Msk              0x00000800UL           /*!< ADC SOC enable for pin 11 */
#define GPIO_ADCSOCSET_PIN12_Msk              0x00001000UL           /*!< ADC SOC enable for pin 12 */
#define GPIO_ADCSOCSET_PIN13_Msk              0x00002000UL           /*!< ADC SOC enable for pin 13 */
#define GPIO_ADCSOCSET_PIN14_Msk              0x00004000UL           /*!< ADC SOC enable for pin 14 */
#define GPIO_ADCSOCSET_PIN15_Msk              0x00008000UL           /*!< ADC SOC enable for pin 15 */

/*--  ADCSOCCLR: ADC Start Of Conversion disable register -----------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< ADC SOC disable */
} _GPIO_ADCSOCCLR_bits;

/* Bit field positions: */
#define GPIO_ADCSOCCLR_VAL_Pos                0                      /*!< ADC SOC disable */

/* Bit field masks: */
#define GPIO_ADCSOCCLR_VAL_Msk                0x0000FFFFUL           /*!< ADC SOC disable */

/*--  RXEVSET: Core RXEV request enable register --------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< RXEV enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< RXEV enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< RXEV enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< RXEV enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< RXEV enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< RXEV enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< RXEV enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< RXEV enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< RXEV enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< RXEV enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< RXEV enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< RXEV enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< RXEV enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< RXEV enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< RXEV enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< RXEV enable for pin 15 */
} _GPIO_RXEVSET_bits;

/* Bit field positions: */
#define GPIO_RXEVSET_PIN0_Pos                 0                      /*!< RXEV enable for pin 0 */
#define GPIO_RXEVSET_PIN1_Pos                 1                      /*!< RXEV enable for pin 1 */
#define GPIO_RXEVSET_PIN2_Pos                 2                      /*!< RXEV enable for pin 2 */
#define GPIO_RXEVSET_PIN3_Pos                 3                      /*!< RXEV enable for pin 3 */
#define GPIO_RXEVSET_PIN4_Pos                 4                      /*!< RXEV enable for pin 4 */
#define GPIO_RXEVSET_PIN5_Pos                 5                      /*!< RXEV enable for pin 5 */
#define GPIO_RXEVSET_PIN6_Pos                 6                      /*!< RXEV enable for pin 6 */
#define GPIO_RXEVSET_PIN7_Pos                 7                      /*!< RXEV enable for pin 7 */
#define GPIO_RXEVSET_PIN8_Pos                 8                      /*!< RXEV enable for pin 8 */
#define GPIO_RXEVSET_PIN9_Pos                 9                      /*!< RXEV enable for pin 9 */
#define GPIO_RXEVSET_PIN10_Pos                10                     /*!< RXEV enable for pin 10 */
#define GPIO_RXEVSET_PIN11_Pos                11                     /*!< RXEV enable for pin 11 */
#define GPIO_RXEVSET_PIN12_Pos                12                     /*!< RXEV enable for pin 12 */
#define GPIO_RXEVSET_PIN13_Pos                13                     /*!< RXEV enable for pin 13 */
#define GPIO_RXEVSET_PIN14_Pos                14                     /*!< RXEV enable for pin 14 */
#define GPIO_RXEVSET_PIN15_Pos                15                     /*!< RXEV enable for pin 15 */

/* Bit field masks: */
#define GPIO_RXEVSET_PIN0_Msk                 0x00000001UL           /*!< RXEV enable for pin 0 */
#define GPIO_RXEVSET_PIN1_Msk                 0x00000002UL           /*!< RXEV enable for pin 1 */
#define GPIO_RXEVSET_PIN2_Msk                 0x00000004UL           /*!< RXEV enable for pin 2 */
#define GPIO_RXEVSET_PIN3_Msk                 0x00000008UL           /*!< RXEV enable for pin 3 */
#define GPIO_RXEVSET_PIN4_Msk                 0x00000010UL           /*!< RXEV enable for pin 4 */
#define GPIO_RXEVSET_PIN5_Msk                 0x00000020UL           /*!< RXEV enable for pin 5 */
#define GPIO_RXEVSET_PIN6_Msk                 0x00000040UL           /*!< RXEV enable for pin 6 */
#define GPIO_RXEVSET_PIN7_Msk                 0x00000080UL           /*!< RXEV enable for pin 7 */
#define GPIO_RXEVSET_PIN8_Msk                 0x00000100UL           /*!< RXEV enable for pin 8 */
#define GPIO_RXEVSET_PIN9_Msk                 0x00000200UL           /*!< RXEV enable for pin 9 */
#define GPIO_RXEVSET_PIN10_Msk                0x00000400UL           /*!< RXEV enable for pin 10 */
#define GPIO_RXEVSET_PIN11_Msk                0x00000800UL           /*!< RXEV enable for pin 11 */
#define GPIO_RXEVSET_PIN12_Msk                0x00001000UL           /*!< RXEV enable for pin 12 */
#define GPIO_RXEVSET_PIN13_Msk                0x00002000UL           /*!< RXEV enable for pin 13 */
#define GPIO_RXEVSET_PIN14_Msk                0x00004000UL           /*!< RXEV enable for pin 14 */
#define GPIO_RXEVSET_PIN15_Msk                0x00008000UL           /*!< RXEV enable for pin 15 */

/*--  RXEVCLR: Core RXEV request disable register -------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< RXEV disable */
} _GPIO_RXEVCLR_bits;

/* Bit field positions: */
#define GPIO_RXEVCLR_VAL_Pos                  0                      /*!< RXEV disable */

/* Bit field masks: */
#define GPIO_RXEVCLR_VAL_Msk                  0x0000FFFFUL           /*!< RXEV disable */

/*--  LOCKKEY: Key register to unlock LOCKSET/LOCKCLR registers for write (KEY=0xADEADBEE) --------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!<  Key to unlock LOCKSET/LOCKCLR registers for write (KEY=0xADEADBEE) */
} _GPIO_LOCKKEY_bits;

/* Bit field positions: */
#define GPIO_LOCKKEY_VAL_Pos                  0                      /*!<  Key to unlock LOCKSET/LOCKCLR registers for write (KEY=0xADEADBEE) */

/* Bit field masks: */
#define GPIO_LOCKKEY_VAL_Msk                  0xFFFFFFFFUL           /*!<  Key to unlock LOCKSET/LOCKCLR registers for write (KEY=0xADEADBEE) */

/* Bit field enums: */
typedef enum {
  GPIO_LOCKKEY_VAL_LOCK                      = -286331154,           /*!< 0xEEEEEEEE, Example value to disable write to LOCKSET/LOCKCLR */
  GPIO_LOCKKEY_VAL_LOCK_0                    = 0x0UL,                /*!< Example value to disable write to LOCKSET/LOCKCLR */
  GPIO_LOCKKEY_VAL_LOCK_1                    = 0x1UL,                /*!< Example value to disable write to LOCKSET/LOCKCLR */
  GPIO_LOCKKEY_VAL_UNLOCK                    = -1377117202,          /*!< 0xADEADBEE, Key to unlock write to LOCKSET/LOCKCLR */
} GPIO_LOCKKEY_VAL_Enum;

/*--  LOCKSTAT: Write LOCKSET/LOCKCLR enable status register --------------------------------------------------*/
typedef struct {
  uint32_t WREN                   :1;                                /*!< Write LOCKSET/LOCKCLR enable status */
} _GPIO_LOCKSTAT_bits;

/* Bit field positions: */
#define GPIO_LOCKSTAT_WREN_Pos                0                      /*!< Write LOCKSET/LOCKCLR enable status */

/* Bit field masks: */
#define GPIO_LOCKSTAT_WREN_Msk                0x00000001UL           /*!< Write LOCKSET/LOCKCLR enable status */

/*--  LOCKSET: Lock pins configuration enable register --------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< Lock configuration enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< Lock configuration enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< Lock configuration enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< Lock configuration enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< Lock configuration enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< Lock configuration enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< Lock configuration enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< Lock configuration enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< Lock configuration enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< Lock configuration enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< Lock configuration enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< Lock configuration enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< Lock configuration enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< Lock configuration enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< Lock configuration enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< Lock configuration enable for pin 15 */
} _GPIO_LOCKSET_bits;

/* Bit field positions: */
#define GPIO_LOCKSET_PIN0_Pos                 0                      /*!< Lock configuration enable for pin 0 */
#define GPIO_LOCKSET_PIN1_Pos                 1                      /*!< Lock configuration enable for pin 1 */
#define GPIO_LOCKSET_PIN2_Pos                 2                      /*!< Lock configuration enable for pin 2 */
#define GPIO_LOCKSET_PIN3_Pos                 3                      /*!< Lock configuration enable for pin 3 */
#define GPIO_LOCKSET_PIN4_Pos                 4                      /*!< Lock configuration enable for pin 4 */
#define GPIO_LOCKSET_PIN5_Pos                 5                      /*!< Lock configuration enable for pin 5 */
#define GPIO_LOCKSET_PIN6_Pos                 6                      /*!< Lock configuration enable for pin 6 */
#define GPIO_LOCKSET_PIN7_Pos                 7                      /*!< Lock configuration enable for pin 7 */
#define GPIO_LOCKSET_PIN8_Pos                 8                      /*!< Lock configuration enable for pin 8 */
#define GPIO_LOCKSET_PIN9_Pos                 9                      /*!< Lock configuration enable for pin 9 */
#define GPIO_LOCKSET_PIN10_Pos                10                     /*!< Lock configuration enable for pin 10 */
#define GPIO_LOCKSET_PIN11_Pos                11                     /*!< Lock configuration enable for pin 11 */
#define GPIO_LOCKSET_PIN12_Pos                12                     /*!< Lock configuration enable for pin 12 */
#define GPIO_LOCKSET_PIN13_Pos                13                     /*!< Lock configuration enable for pin 13 */
#define GPIO_LOCKSET_PIN14_Pos                14                     /*!< Lock configuration enable for pin 14 */
#define GPIO_LOCKSET_PIN15_Pos                15                     /*!< Lock configuration enable for pin 15 */

/* Bit field masks: */
#define GPIO_LOCKSET_PIN0_Msk                 0x00000001UL           /*!< Lock configuration enable for pin 0 */
#define GPIO_LOCKSET_PIN1_Msk                 0x00000002UL           /*!< Lock configuration enable for pin 1 */
#define GPIO_LOCKSET_PIN2_Msk                 0x00000004UL           /*!< Lock configuration enable for pin 2 */
#define GPIO_LOCKSET_PIN3_Msk                 0x00000008UL           /*!< Lock configuration enable for pin 3 */
#define GPIO_LOCKSET_PIN4_Msk                 0x00000010UL           /*!< Lock configuration enable for pin 4 */
#define GPIO_LOCKSET_PIN5_Msk                 0x00000020UL           /*!< Lock configuration enable for pin 5 */
#define GPIO_LOCKSET_PIN6_Msk                 0x00000040UL           /*!< Lock configuration enable for pin 6 */
#define GPIO_LOCKSET_PIN7_Msk                 0x00000080UL           /*!< Lock configuration enable for pin 7 */
#define GPIO_LOCKSET_PIN8_Msk                 0x00000100UL           /*!< Lock configuration enable for pin 8 */
#define GPIO_LOCKSET_PIN9_Msk                 0x00000200UL           /*!< Lock configuration enable for pin 9 */
#define GPIO_LOCKSET_PIN10_Msk                0x00000400UL           /*!< Lock configuration enable for pin 10 */
#define GPIO_LOCKSET_PIN11_Msk                0x00000800UL           /*!< Lock configuration enable for pin 11 */
#define GPIO_LOCKSET_PIN12_Msk                0x00001000UL           /*!< Lock configuration enable for pin 12 */
#define GPIO_LOCKSET_PIN13_Msk                0x00002000UL           /*!< Lock configuration enable for pin 13 */
#define GPIO_LOCKSET_PIN14_Msk                0x00004000UL           /*!< Lock configuration enable for pin 14 */
#define GPIO_LOCKSET_PIN15_Msk                0x00008000UL           /*!< Lock configuration enable for pin 15 */

/*--  LOCKCLR: Lock pins configuration disable register -------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Lock configuration disable */
} _GPIO_LOCKCLR_bits;

/* Bit field positions: */
#define GPIO_LOCKCLR_VAL_Pos                  0                      /*!< Lock configuration disable */

/* Bit field masks: */
#define GPIO_LOCKCLR_VAL_Msk                  0x0000FFFFUL           /*!< Lock configuration disable */

/*--  DMARXREQSET: DMA RX request enable register -------------------------------------------------------------*/
typedef struct {
  uint32_t PIN0                   :1;                                /*!< DMA request enable for pin 0 */
  uint32_t PIN1                   :1;                                /*!< DMA request enable for pin 1 */
  uint32_t PIN2                   :1;                                /*!< DMA request enable for pin 2 */
  uint32_t PIN3                   :1;                                /*!< DMA request enable for pin 3 */
  uint32_t PIN4                   :1;                                /*!< DMA request enable for pin 4 */
  uint32_t PIN5                   :1;                                /*!< DMA request enable for pin 5 */
  uint32_t PIN6                   :1;                                /*!< DMA request enable for pin 6 */
  uint32_t PIN7                   :1;                                /*!< DMA request enable for pin 7 */
  uint32_t PIN8                   :1;                                /*!< DMA request enable for pin 8 */
  uint32_t PIN9                   :1;                                /*!< DMA request enable for pin 9 */
  uint32_t PIN10                  :1;                                /*!< DMA request enable for pin 10 */
  uint32_t PIN11                  :1;                                /*!< DMA request enable for pin 11 */
  uint32_t PIN12                  :1;                                /*!< DMA request enable for pin 12 */
  uint32_t PIN13                  :1;                                /*!< DMA request enable for pin 13 */
  uint32_t PIN14                  :1;                                /*!< DMA request enable for pin 14 */
  uint32_t PIN15                  :1;                                /*!< DMA request enable for pin 15 */
} _GPIO_DMARXREQSET_bits;

/* Bit field positions: */
#define GPIO_DMARXREQSET_PIN0_Pos             0                      /*!< DMA request enable for pin 0 */
#define GPIO_DMARXREQSET_PIN1_Pos             1                      /*!< DMA request enable for pin 1 */
#define GPIO_DMARXREQSET_PIN2_Pos             2                      /*!< DMA request enable for pin 2 */
#define GPIO_DMARXREQSET_PIN3_Pos             3                      /*!< DMA request enable for pin 3 */
#define GPIO_DMARXREQSET_PIN4_Pos             4                      /*!< DMA request enable for pin 4 */
#define GPIO_DMARXREQSET_PIN5_Pos             5                      /*!< DMA request enable for pin 5 */
#define GPIO_DMARXREQSET_PIN6_Pos             6                      /*!< DMA request enable for pin 6 */
#define GPIO_DMARXREQSET_PIN7_Pos             7                      /*!< DMA request enable for pin 7 */
#define GPIO_DMARXREQSET_PIN8_Pos             8                      /*!< DMA request enable for pin 8 */
#define GPIO_DMARXREQSET_PIN9_Pos             9                      /*!< DMA request enable for pin 9 */
#define GPIO_DMARXREQSET_PIN10_Pos            10                     /*!< DMA request enable for pin 10 */
#define GPIO_DMARXREQSET_PIN11_Pos            11                     /*!< DMA request enable for pin 11 */
#define GPIO_DMARXREQSET_PIN12_Pos            12                     /*!< DMA request enable for pin 12 */
#define GPIO_DMARXREQSET_PIN13_Pos            13                     /*!< DMA request enable for pin 13 */
#define GPIO_DMARXREQSET_PIN14_Pos            14                     /*!< DMA request enable for pin 14 */
#define GPIO_DMARXREQSET_PIN15_Pos            15                     /*!< DMA request enable for pin 15 */

/* Bit field masks: */
#define GPIO_DMARXREQSET_PIN0_Msk             0x00000001UL           /*!< DMA request enable for pin 0 */
#define GPIO_DMARXREQSET_PIN1_Msk             0x00000002UL           /*!< DMA request enable for pin 1 */
#define GPIO_DMARXREQSET_PIN2_Msk             0x00000004UL           /*!< DMA request enable for pin 2 */
#define GPIO_DMARXREQSET_PIN3_Msk             0x00000008UL           /*!< DMA request enable for pin 3 */
#define GPIO_DMARXREQSET_PIN4_Msk             0x00000010UL           /*!< DMA request enable for pin 4 */
#define GPIO_DMARXREQSET_PIN5_Msk             0x00000020UL           /*!< DMA request enable for pin 5 */
#define GPIO_DMARXREQSET_PIN6_Msk             0x00000040UL           /*!< DMA request enable for pin 6 */
#define GPIO_DMARXREQSET_PIN7_Msk             0x00000080UL           /*!< DMA request enable for pin 7 */
#define GPIO_DMARXREQSET_PIN8_Msk             0x00000100UL           /*!< DMA request enable for pin 8 */
#define GPIO_DMARXREQSET_PIN9_Msk             0x00000200UL           /*!< DMA request enable for pin 9 */
#define GPIO_DMARXREQSET_PIN10_Msk            0x00000400UL           /*!< DMA request enable for pin 10 */
#define GPIO_DMARXREQSET_PIN11_Msk            0x00000800UL           /*!< DMA request enable for pin 11 */
#define GPIO_DMARXREQSET_PIN12_Msk            0x00001000UL           /*!< DMA request enable for pin 12 */
#define GPIO_DMARXREQSET_PIN13_Msk            0x00002000UL           /*!< DMA request enable for pin 13 */
#define GPIO_DMARXREQSET_PIN14_Msk            0x00004000UL           /*!< DMA request enable for pin 14 */
#define GPIO_DMARXREQSET_PIN15_Msk            0x00008000UL           /*!< DMA request enable for pin 15 */

/*--  DMARXREQCLR: DMA RX request disable register ------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< DMA request disable */
} _GPIO_DMARXREQCLR_bits;

/* Bit field positions: */
#define GPIO_DMARXREQCLR_VAL_Pos              0                      /*!< DMA request disable */

/* Bit field masks: */
#define GPIO_DMARXREQCLR_VAL_Msk              0x0000FFFFUL           /*!< DMA request disable */

/*--  MASKLB: Mask register low byte of port ------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :8;                                /*!< Mask low byte */
} _GPIO_MASKLB_bits;

/* Bit field positions: */
#define GPIO_MASKLB_VAL_Pos                   0                      /*!< Mask low byte */

/* Bit field masks: */
#define GPIO_MASKLB_VAL_Msk                   0x000000FFUL           /*!< Mask low byte */

/*--  MASKHB: Mask register High byte of port -----------------------------------------------------------------*/
typedef struct {
  uint32_t                        :8;                                /*!< RESERVED */
  uint32_t VAL                    :8;                                /*!< Mask high byte */
} _GPIO_MASKHB_bits;

/* Bit field positions: */
#define GPIO_MASKHB_VAL_Pos                   8                      /*!< Mask high byte */

/* Bit field masks: */
#define GPIO_MASKHB_VAL_Msk                   0x0000FF00UL           /*!< Mask high byte */

//Cluster MASKLB:
typedef struct {
  union {
  /*!< Mask register low byte of port */
    __IO uint32_t MASKLB;                                            /*!< MASKLB : type used for word access */
    __IO _GPIO_MASKLB_bits MASKLB_bit;                               /*!< MASKLB_bit: structure used for bit access */
  };
} _GPIO_MASKLB_TypeDef;
//Cluster MASKHB:
typedef struct {
  union {
  /*!< Mask register High byte of port */
    __IO uint32_t MASKHB;                                            /*!< MASKHB : type used for word access */
    __IO _GPIO_MASKHB_bits MASKHB_bit;                               /*!< MASKHB_bit: structure used for bit access */
  };
} _GPIO_MASKHB_TypeDef;
typedef struct {
  union {                                                            /*!< Data Input register */
    __I uint32_t DATA;                                               /*!< DATA    : type used for word access */
    __I _GPIO_DATA_bits  DATA_bit;                                   /*!< DATA_bit: structure used for bit access */
  };
  union {                                                            /*!< Data output register */
    __IO uint32_t DATAOUT;                                           /*!< DATAOUT    : type used for word access */
    __IO _GPIO_DATAOUT_bits  DATAOUT_bit;                            /*!< DATAOUT_bit: structure used for bit access */
  };
  union {                                                            /*!< Data output set bits register */
    __O uint32_t DATAOUTSET;                                           /*!< DATAOUTSET    : type used for word access */
    __O _GPIO_DATAOUTSET_bits  DATAOUTSET_bit;                       /*!< DATAOUTSET_bit: structure used for bit access */
  };
  union {                                                            /*!< Data output clear bits register */
    __O uint32_t DATAOUTCLR;                                           /*!< DATAOUTCLR    : type used for word access */
    __O _GPIO_DATAOUTCLR_bits  DATAOUTCLR_bit;                       /*!< DATAOUTCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Data output toggle bits register */
    __O uint32_t DATAOUTTGL;                                           /*!< DATAOUTTGL    : type used for word access */
    __O _GPIO_DATAOUTTGL_bits  DATAOUTTGL_bit;                       /*!< DATAOUTTGL_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0[3];
  union {                                                            /*!< Select pull mode register */
    __IO uint32_t PULLMODE;                                           /*!< PULLMODE    : type used for word access */
    __IO _GPIO_PULLMODE_bits  PULLMODE_bit;                          /*!< PULLMODE_bit: structure used for bit access */
  };
  union {                                                            /*!< Select output mode register */
    __IO uint32_t OUTMODE;                                           /*!< OUTMODE    : type used for word access */
    __IO _GPIO_OUTMODE_bits  OUTMODE_bit;                            /*!< OUTMODE_bit: structure used for bit access */
  };
    __IO uint32_t Reserved1;
  union {                                                            /*!< Output enable register */
    __IO uint32_t OUTENSET;                                           /*!< OUTENSET    : type used for word access */
    __IO _GPIO_OUTENSET_bits  OUTENSET_bit;                          /*!< OUTENSET_bit: structure used for bit access */
  };
  union {                                                            /*!< Output disable register */
    __O uint32_t OUTENCLR;                                           /*!< OUTENCLR    : type used for word access */
    __O _GPIO_OUTENCLR_bits  OUTENCLR_bit;                           /*!< OUTENCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Alternative function enable register */
    __IO uint32_t ALTFUNCSET;                                           /*!< ALTFUNCSET    : type used for word access */
    __IO _GPIO_ALTFUNCSET_bits  ALTFUNCSET_bit;                      /*!< ALTFUNCSET_bit: structure used for bit access */
  };
  union {                                                            /*!< Alternative function disable register */
    __O uint32_t ALTFUNCCLR;                                           /*!< ALTFUNCCLR    : type used for word access */
    __O _GPIO_ALTFUNCCLR_bits  ALTFUNCCLR_bit;                       /*!< ALTFUNCCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Alternative function number register */
    __IO uint32_t ALTFUNCNUM;                                           /*!< ALTFUNCNUM    : type used for word access */
    __IO _GPIO_ALTFUNCNUM_bits  ALTFUNCNUM_bit;                      /*!< ALTFUNCNUM_bit: structure used for bit access */
  };
    __IO uint32_t Reserved2;
  union {                                                            /*!< Additional double flip-flop syncronization enable register */
    __IO uint32_t SYNCSET;                                           /*!< SYNCSET    : type used for word access */
    __IO _GPIO_SYNCSET_bits  SYNCSET_bit;                            /*!< SYNCSET_bit: structure used for bit access */
  };
  union {                                                            /*!< Additional double flip-flop syncronization disable register */
    __O uint32_t SYNCCLR;                                            /*!< SYNCCLR    : type used for word access */
    __O _GPIO_SYNCCLR_bits  SYNCCLR_bit;                             /*!< SYNCCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Qualifier enable register */
    __IO uint32_t QUALSET;                                           /*!< QUALSET    : type used for word access */
    __IO _GPIO_QUALSET_bits  QUALSET_bit;                            /*!< QUALSET_bit: structure used for bit access */
  };
  union {                                                            /*!< Qualifier disable register */
    __O uint32_t QUALCLR;                                            /*!< QUALCLR    : type used for word access */
    __O _GPIO_QUALCLR_bits  QUALCLR_bit;                             /*!< QUALCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Qualifier mode set register */
    __IO uint32_t QUALMODESET;                                           /*!< QUALMODESET    : type used for word access */
    __IO _GPIO_QUALMODESET_bits  QUALMODESET_bit;                    /*!< QUALMODESET_bit: structure used for bit access */
  };
  union {                                                            /*!< Qualifier mode clear register */
    __O uint32_t QUALMODECLR;                                           /*!< QUALMODECLR    : type used for word access */
    __O _GPIO_QUALMODECLR_bits  QUALMODECLR_bit;                     /*!< QUALMODECLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Qualifier sample period register */
    __IO uint32_t QUALSAMPLE;                                           /*!< QUALSAMPLE    : type used for word access */
    __IO _GPIO_QUALSAMPLE_bits  QUALSAMPLE_bit;                      /*!< QUALSAMPLE_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt enable register */
    __IO uint32_t INTENSET;                                           /*!< INTENSET    : type used for word access */
    __IO _GPIO_INTENSET_bits  INTENSET_bit;                          /*!< INTENSET_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt disable register */
    __O uint32_t INTENCLR;                                           /*!< INTENCLR    : type used for word access */
    __O _GPIO_INTENCLR_bits  INTENCLR_bit;                           /*!< INTENCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt type set register */
    __IO uint32_t INTTYPESET;                                           /*!< INTTYPESET    : type used for word access */
    __IO _GPIO_INTTYPESET_bits  INTTYPESET_bit;                      /*!< INTTYPESET_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt type clear register */
    __O uint32_t INTTYPECLR;                                           /*!< INTTYPECLR    : type used for word access */
    __O _GPIO_INTTYPECLR_bits  INTTYPECLR_bit;                       /*!< INTTYPECLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt polarity set register */
    __IO uint32_t INTPOLSET;                                           /*!< INTPOLSET    : type used for word access */
    __IO _GPIO_INTPOLSET_bits  INTPOLSET_bit;                        /*!< INTPOLSET_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt polarity clear register */
    __O uint32_t INTPOLCLR;                                           /*!< INTPOLCLR    : type used for word access */
    __O _GPIO_INTPOLCLR_bits  INTPOLCLR_bit;                         /*!< INTPOLCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt every edge set register */
    __IO uint32_t INTEDGESET;                                           /*!< INTEDGESET    : type used for word access */
    __IO _GPIO_INTEDGESET_bits  INTEDGESET_bit;                      /*!< INTEDGESET_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt every edge clear register */
    __O uint32_t INTEDGECLR;                                           /*!< INTEDGECLR    : type used for word access */
    __O _GPIO_INTEDGECLR_bits  INTEDGECLR_bit;                       /*!< INTEDGECLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt status */
    __IO uint32_t INTSTATUS;                                           /*!< INTSTATUS    : type used for word access */
    __IO _GPIO_INTSTATUS_bits  INTSTATUS_bit;                        /*!< INTSTATUS_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA TX request enable register */
    __IO uint32_t DMATXREQSET;                                           /*!< DMATXREQSET    : type used for word access */
    __IO _GPIO_DMATXREQSET_bits  DMATXREQSET_bit;                    /*!< DMATXREQSET_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA TX request disable register */
    __O uint32_t DMATXREQCLR;                                           /*!< DMATXREQCLR    : type used for word access */
    __O _GPIO_DMATXREQCLR_bits  DMATXREQCLR_bit;                     /*!< DMATXREQCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< ADC Start Of Conversion enable register */
    __IO uint32_t ADCSOCSET;                                           /*!< ADCSOCSET    : type used for word access */
    __IO _GPIO_ADCSOCSET_bits  ADCSOCSET_bit;                        /*!< ADCSOCSET_bit: structure used for bit access */
  };
  union {                                                            /*!< ADC Start Of Conversion disable register */
    __O uint32_t ADCSOCCLR;                                           /*!< ADCSOCCLR    : type used for word access */
    __O _GPIO_ADCSOCCLR_bits  ADCSOCCLR_bit;                         /*!< ADCSOCCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Core RXEV request enable register */
    __IO uint32_t RXEVSET;                                           /*!< RXEVSET    : type used for word access */
    __IO _GPIO_RXEVSET_bits  RXEVSET_bit;                            /*!< RXEVSET_bit: structure used for bit access */
  };
  union {                                                            /*!< Core RXEV request disable register */
    __O uint32_t RXEVCLR;                                            /*!< RXEVCLR    : type used for word access */
    __O _GPIO_RXEVCLR_bits  RXEVCLR_bit;                             /*!< RXEVCLR_bit: structure used for bit access */
  };
  union {
    union {                                                            /*!< Key register to unlock LOCKSET/LOCKCLR registers for write (KEY=0xADEADBEE) */
      __O uint32_t LOCKKEY;                                           /*!< LOCKKEY    : type used for word access */
      __O _GPIO_LOCKKEY_bits  LOCKKEY_bit;                           /*!< LOCKKEY_bit: structure used for bit access */
    };
    struct {
      union {                                                            /*!< Write LOCKSET/LOCKCLR enable status register */
        __I uint32_t LOCKSTAT;                                           /*!< LOCKSTAT    : type used for word access */
        __I _GPIO_LOCKSTAT_bits  LOCKSTAT_bit;                       /*!< LOCKSTAT_bit: structure used for bit access */
      };
    };
  };
  union {                                                            /*!< Lock pins configuration enable register */
    __IO uint32_t LOCKSET;                                           /*!< LOCKSET    : type used for word access */
    __IO _GPIO_LOCKSET_bits  LOCKSET_bit;                            /*!< LOCKSET_bit: structure used for bit access */
  };
  union {                                                            /*!< Lock pins configuration disable register */
    __O uint32_t LOCKCLR;                                            /*!< LOCKCLR    : type used for word access */
    __O _GPIO_LOCKCLR_bits  LOCKCLR_bit;                             /*!< LOCKCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA RX request enable register */
    __IO uint32_t DMARXREQSET;                                           /*!< DMARXREQSET    : type used for word access */
    __IO _GPIO_DMARXREQSET_bits  DMARXREQSET_bit;                    /*!< DMARXREQSET_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA RX request disable register */
    __O uint32_t DMARXREQCLR;                                           /*!< DMARXREQCLR    : type used for word access */
    __O _GPIO_DMARXREQCLR_bits  DMARXREQCLR_bit;                     /*!< DMARXREQCLR_bit: structure used for bit access */
  };
    __IO uint32_t Reserved3[212];
  _GPIO_MASKLB_TypeDef MASKLB[256];
  _GPIO_MASKHB_TypeDef MASKHB[256];
} GPIO_TypeDef;


/******************************************************************************/
/*                         I2C registers                                      */
/******************************************************************************/

/*--  SDA: Data register --------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t DATA                   :8;                                /*!< Data field */
} _I2C_SDA_bits;

/* Bit field positions: */
#define I2C_SDA_DATA_Pos                      0                      /*!< Data field */

/* Bit field masks: */
#define I2C_SDA_DATA_Msk                      0x000000FFUL           /*!< Data field */

/*--  ST: Status register -------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t MODE                   :6;                                /*!< Status code */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t INT                    :1;                                /*!< Interrupt flag */
} _I2C_ST_bits;

/* Bit field positions: */
#define I2C_ST_MODE_Pos                       0                      /*!< Status code */
#define I2C_ST_INT_Pos                        7                      /*!< Interrupt flag */

/* Bit field masks: */
#define I2C_ST_MODE_Msk                       0x0000003FUL           /*!< Status code */
#define I2C_ST_INT_Msk                        0x00000080UL           /*!< Interrupt flag */

/* Bit field enums: */
typedef enum {
  I2C_ST_MODE_IDLE                           = 0x0UL,                /*!< General - Idle, no valid status information available */
  I2C_ST_MODE_STDONE                         = 0x1UL,                /*!< FS master - Start condition generated */
  I2C_ST_MODE_RSDONE                         = 0x2UL,                /*!< FS master - Repeated start condition generated */
  I2C_ST_MODE_IDLARL                         = 0x3UL,                /*!< FS master - Arbitration lost, unaddressed slave mode entered */
  I2C_ST_MODE_MTADPA                         = 0x4UL,                /*!< FS master transmit - Slave address sent, positive ACK */
  I2C_ST_MODE_MTADNA                         = 0x5UL,                /*!< FS master transmit - Slave address sent, negative ACK */
  I2C_ST_MODE_MTDAPA                         = 0x6UL,                /*!< FS master transmit - Data byte sent, positive ACK */
  I2C_ST_MODE_MTDANA                         = 0x7UL,                /*!< FS master transmit - Data byte sent, negative ACK */
  I2C_ST_MODE_MRADPA                         = 0x8UL,                /*!< FS master receive - Slave addres sent, positive ACK */
  I2C_ST_MODE_MRADNA                         = 0x9UL,                /*!< FS master receive - Slave addres sent, negative ACK */
  I2C_ST_MODE_MRDAPA                         = 0xAUL,                /*!< FS master receive - Data byte received, positive ACK */
  I2C_ST_MODE_MRDANA                         = 0xBUL,                /*!< FS master receive - Data byte received, negative ACK */
  I2C_ST_MODE_MTMCER                         = 0xCUL,                /*!< FS master - Mastercode transmitted, error detected (positive ACK) */
  I2C_ST_MODE_SRADPA                         = 0x10UL,               /*!< FS slave receive - Slave address received, positive ACK */
  I2C_ST_MODE_SRAAPA                         = 0x11UL,               /*!< FS slave receive - Slave address received after arbitration loss, positive ACK */
  I2C_ST_MODE_SRDAPA                         = 0x12UL,               /*!< FS slave receive - Data byte received, positive ACK */
  I2C_ST_MODE_SRDANA                         = 0x13UL,               /*!< FS slave receive - Data byte received, negative ACK */
  I2C_ST_MODE_STADPA                         = 0x14UL,               /*!< FS slave transmit - Slave address received, positive ACK */
  I2C_ST_MODE_STAAPA                         = 0x15UL,               /*!< FS slave transmit - Slave address received, negative ACK */
  I2C_ST_MODE_STDAPA                         = 0x16UL,               /*!< FS slave transmit - Data byte sent, positive ACK */
  I2C_ST_MODE_STDANA                         = 0x17UL,               /*!< FS slave transmit - Data byte sent, negative ACK */
  I2C_ST_MODE_SATADP                         = 0x18UL,               /*!< FS slave transmit alert response - Alert response address received, positive ACK */
  I2C_ST_MODE_SATAAP                         = 0x19UL,               /*!< FS slave transmit alert response - Alert response address received after arbitration loss, positive ACK */
  I2C_ST_MODE_SATDAP                         = 0x1AUL,               /*!< FS slave transmit alert response - Alert response data byte sent, positive ACK */
  I2C_ST_MODE_SATDAN                         = 0x1BUL,               /*!< FS slave transmit alert response - Alert response data byte sent, negative ACK */
  I2C_ST_MODE_SSTOP                          = 0x1CUL,               /*!< FS slave - Slave mode stop condition detected */
  I2C_ST_MODE_SGADPA                         = 0x1DUL,               /*!< FS slave - Global call address received, positive ACK */
  I2C_ST_MODE_SDAAPA                         = 0x1EUL,               /*!< FS slave - Global call address received after arbitration loss, positive ACK */
  I2C_ST_MODE_BERROR                         = 0x1FUL,               /*!< General - Bus error detected (invalid start or stop condition */
  I2C_ST_MODE_HMTMCOK                        = 0x21UL,               /*!< HS master - Master code transmitted OK - switched to HS mode */
  I2C_ST_MODE_HRSDONE                        = 0x22UL,               /*!< HS master - Repeated start condition generated */
  I2C_ST_MODE_HIDLARL                        = 0x23UL,               /*!< HS master - Arbitration lost, HS unaddressed slave mode entered */
  I2C_ST_MODE_HMTADPA                        = 0x24UL,               /*!< HS master transmit - Slave address sent, positive ACK */
  I2C_ST_MODE_HMTADNA                        = 0x25UL,               /*!< HS master transmit - Slave address sent, negative ACK */
  I2C_ST_MODE_HMTDAPA                        = 0x26UL,               /*!< HS master transmit - Data byte sent, positive ACK */
  I2C_ST_MODE_HMTDANA                        = 0x27UL,               /*!< HS master transmit - Data byte sent, negative ACK */
  I2C_ST_MODE_HMRADPA                        = 0x28UL,               /*!< HS master receive - Slave address sent, positive ACK */
  I2C_ST_MODE_HMRADNA                        = 0x29UL,               /*!< HS master receive - Slave address sent, negative ACK */
  I2C_ST_MODE_HMRDAPA                        = 0x2AUL,               /*!< HS master receive - Data byte received, positive ACK */
  I2C_ST_MODE_HMRDANA                        = 0x2BUL,               /*!< HS master receive - Data byte received, negative ACK */
  I2C_ST_MODE_HSRADPA                        = 0x30UL,               /*!< HS slave receive - Slave address received, positive ACK */
  I2C_ST_MODE_HSRDAPA                        = 0x32UL,               /*!< HS slave receive - Data byte received, positive ACK */
  I2C_ST_MODE_HSRDANA                        = 0x33UL,               /*!< HS slave receive - Data byte received, negative ACK */
  I2C_ST_MODE_HSTADPA                        = 0x34UL,               /*!< HS slave transmit - Slave address received, positive ACK */
  I2C_ST_MODE_HSTDAPA                        = 0x36UL,               /*!< HS slave transmit - Data byte sent, positive ACK */
  I2C_ST_MODE_HSTDANA                        = 0x37UL,               /*!< HS slave transmit - Data byte sent, negative ACK */
} I2C_ST_MODE_Enum;

/*--  CST: Status and control register ------------------------------------------------------------------------*/
typedef struct {
  uint32_t BB                     :1;                                /*!< Flag employment bus */
  uint32_t TOCDIV                 :2;                                /*!< Coeff. div */
  uint32_t TOERR                  :1;                                /*!< Flag error simple bus */
  uint32_t TSDA                   :1;                                /*!< Bit test SDA */
  uint32_t TGSCL                  :1;                                /*!< Bit switch SCL */
  uint32_t PECNEXT                :1;                                /*!< Bit control transmit CRC */
  uint32_t PECFAULT               :1;                                /*!< Error flag */
} _I2C_CST_bits;

/* Bit field positions: */
#define I2C_CST_BB_Pos                        0                      /*!< Flag employment bus */
#define I2C_CST_TOCDIV_Pos                    1                      /*!< Coeff. div */
#define I2C_CST_TOERR_Pos                     3                      /*!< Flag error simple bus */
#define I2C_CST_TSDA_Pos                      4                      /*!< Bit test SDA */
#define I2C_CST_TGSCL_Pos                     5                      /*!< Bit switch SCL */
#define I2C_CST_PECNEXT_Pos                   6                      /*!< Bit control transmit CRC */
#define I2C_CST_PECFAULT_Pos                  7                      /*!< Error flag */

/* Bit field masks: */
#define I2C_CST_BB_Msk                        0x00000001UL           /*!< Flag employment bus */
#define I2C_CST_TOCDIV_Msk                    0x00000006UL           /*!< Coeff. div */
#define I2C_CST_TOERR_Msk                     0x00000008UL           /*!< Flag error simple bus */
#define I2C_CST_TSDA_Msk                      0x00000010UL           /*!< Bit test SDA */
#define I2C_CST_TGSCL_Msk                     0x00000020UL           /*!< Bit switch SCL */
#define I2C_CST_PECNEXT_Msk                   0x00000040UL           /*!< Bit control transmit CRC */
#define I2C_CST_PECFAULT_Msk                  0x00000080UL           /*!< Error flag */

/* Bit field enums: */
typedef enum {
  I2C_CST_TOCDIV_Disable                     = 0x0UL,                /*!< disable clock */
  I2C_CST_TOCDIV_Div4                        = 0x1UL,                /*!< clock divided by 4 */
  I2C_CST_TOCDIV_Div8                        = 0x2UL,                /*!< clock divided by 8 */
  I2C_CST_TOCDIV_Div16                       = 0x3UL,                /*!< clock divided by 16 */
} I2C_CST_TOCDIV_Enum;

/*--  CTL0: Control register 0 --------------------------------------------------------------------------------*/
typedef struct {
  uint32_t START                  :1;                                /*!< Start bit */
  uint32_t STOP                   :1;                                /*!< Stop bit */
  uint32_t INTEN                  :1;                                /*!< Interrupt enable bit */
  uint32_t UNADDR                 :1;                                /*!< Unaddress mode, slave response to any address */
  uint32_t ACK                    :1;                                /*!< Acknowledgment bit reception */
  uint32_t GCMEN                  :1;                                /*!< Control bit part a response to the general call address */
  uint32_t SMBARE                 :1;                                /*!< Control bit part a response to the response address */
  uint32_t CLRST                  :1;                                /*!< Bit reset flag interrupt */
} _I2C_CTL0_bits;

/* Bit field positions: */
#define I2C_CTL0_START_Pos                    0                      /*!< Start bit */
#define I2C_CTL0_STOP_Pos                     1                      /*!< Stop bit */
#define I2C_CTL0_INTEN_Pos                    2                      /*!< Interrupt enable bit */
#define I2C_CTL0_UNADDR_Pos                   3                      /*!< Unaddress mode, slave response to any address */
#define I2C_CTL0_ACK_Pos                      4                      /*!< Acknowledgment bit reception */
#define I2C_CTL0_GCMEN_Pos                    5                      /*!< Control bit part a response to the general call address */
#define I2C_CTL0_SMBARE_Pos                   6                      /*!< Control bit part a response to the response address */
#define I2C_CTL0_CLRST_Pos                    7                      /*!< Bit reset flag interrupt */

/* Bit field masks: */
#define I2C_CTL0_START_Msk                    0x00000001UL           /*!< Start bit */
#define I2C_CTL0_STOP_Msk                     0x00000002UL           /*!< Stop bit */
#define I2C_CTL0_INTEN_Msk                    0x00000004UL           /*!< Interrupt enable bit */
#define I2C_CTL0_UNADDR_Msk                   0x00000008UL           /*!< Unaddress mode, slave response to any address */
#define I2C_CTL0_ACK_Msk                      0x00000010UL           /*!< Acknowledgment bit reception */
#define I2C_CTL0_GCMEN_Msk                    0x00000020UL           /*!< Control bit part a response to the general call address */
#define I2C_CTL0_SMBARE_Msk                   0x00000040UL           /*!< Control bit part a response to the response address */
#define I2C_CTL0_CLRST_Msk                    0x00000080UL           /*!< Bit reset flag interrupt */

/*--  ADDR: Register own address ------------------------------------------------------------------------------*/
typedef struct {
  uint32_t ADDR                   :7;                                /*!< Own 7-bit address */
  uint32_t SAEN                   :1;                                /*!< Enable bit address recognition */
} _I2C_ADDR_bits;

/* Bit field positions: */
#define I2C_ADDR_ADDR_Pos                     0                      /*!< Own 7-bit address */
#define I2C_ADDR_SAEN_Pos                     7                      /*!< Enable bit address recognition */

/* Bit field masks: */
#define I2C_ADDR_ADDR_Msk                     0x0000007FUL           /*!< Own 7-bit address */
#define I2C_ADDR_SAEN_Msk                     0x00000080UL           /*!< Enable bit address recognition */

/*--  CTL1: Control register 1 --------------------------------------------------------------------------------*/
typedef struct {
  uint32_t ENABLE                 :1;                                /*!< Enable I2C */
  uint32_t SCLFRQ                 :7;                                /*!< Field frequency selection signal at pin SCL in master mode (bits [6:0]) */
} _I2C_CTL1_bits;

/* Bit field positions: */
#define I2C_CTL1_ENABLE_Pos                   0                      /*!< Enable I2C */
#define I2C_CTL1_SCLFRQ_Pos                   1                      /*!< Field frequency selection signal at pin SCL in master mode (bits [6:0]) */

/* Bit field masks: */
#define I2C_CTL1_ENABLE_Msk                   0x00000001UL           /*!< Enable I2C */
#define I2C_CTL1_SCLFRQ_Msk                   0x000000FEUL           /*!< Field frequency selection signal at pin SCL in master mode (bits [6:0]) */

/*--  TOPR: Prescaler load register ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t SMBTOPR                :8;                                /*!< Prescaler reload value field */
} _I2C_TOPR_bits;

/* Bit field positions: */
#define I2C_TOPR_SMBTOPR_Pos                  0                      /*!< Prescaler reload value field */

/* Bit field masks: */
#define I2C_TOPR_SMBTOPR_Msk                  0x000000FFUL           /*!< Prescaler reload value field */

/*--  CTL2: Control register 2 --------------------------------------------------------------------------------*/
typedef struct {
  uint32_t S10ADR                 :3;                                /*!< Upper bits of 10-bit slave address */
  uint32_t S10EN                  :1;                                /*!< Bit enabled 10-bit addressing slave */
  uint32_t HSDIV                  :4;                                /*!< Field frequency selection signal at pin SCL in HS master mode (bits [3:0]) */
} _I2C_CTL2_bits;

/* Bit field positions: */
#define I2C_CTL2_S10ADR_Pos                   0                      /*!< Upper bits of 10-bit slave address */
#define I2C_CTL2_S10EN_Pos                    3                      /*!< Bit enabled 10-bit addressing slave */
#define I2C_CTL2_HSDIV_Pos                    4                      /*!< Field frequency selection signal at pin SCL in HS master mode (bits [3:0]) */

/* Bit field masks: */
#define I2C_CTL2_S10ADR_Msk                   0x00000007UL           /*!< Upper bits of 10-bit slave address */
#define I2C_CTL2_S10EN_Msk                    0x00000008UL           /*!< Bit enabled 10-bit addressing slave */
#define I2C_CTL2_HSDIV_Msk                    0x000000F0UL           /*!< Field frequency selection signal at pin SCL in HS master mode (bits [3:0]) */

/*--  CTL3: Control register 3 --------------------------------------------------------------------------------*/
typedef struct {
  uint32_t SCLFRQ                 :8;                                /*!< Field frequency selection signal at pin SCL in master mode (bits [14:7]) */
} _I2C_CTL3_bits;

/* Bit field positions: */
#define I2C_CTL3_SCLFRQ_Pos                   0                      /*!< Field frequency selection signal at pin SCL in master mode (bits [14:7]) */

/* Bit field masks: */
#define I2C_CTL3_SCLFRQ_Msk                   0x000000FFUL           /*!< Field frequency selection signal at pin SCL in master mode (bits [14:7]) */

/*--  CTL4: Control Register 4 --------------------------------------------------------------------------------*/
typedef struct {
  uint32_t HSDIV                  :8;                                /*!< Field frequency selection signal at pin SCL in HS master mode (bits [11:4]) */
} _I2C_CTL4_bits;

/* Bit field positions: */
#define I2C_CTL4_HSDIV_Pos                    0                      /*!< Field frequency selection signal at pin SCL in HS master mode (bits [11:4]) */

/* Bit field masks: */
#define I2C_CTL4_HSDIV_Msk                    0x000000FFUL           /*!< Field frequency selection signal at pin SCL in HS master mode (bits [11:4]) */

/*--  EADDR: Extended address Register ------------------------------------------------------------------------*/
typedef struct {
  uint32_t ADDR                   :10;                               /*!< Additional adress */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t SAEN                   :1;                                /*!< Enable bit address recognition */
} _I2C_EADDR_bits;

/* Bit field positions: */
#define I2C_EADDR_ADDR_Pos                    0                      /*!< Additional adress */
#define I2C_EADDR_SAEN_Pos                    15                     /*!< Enable bit address recognition */

/* Bit field masks: */
#define I2C_EADDR_ADDR_Msk                    0x000003FFUL           /*!< Additional adress */
#define I2C_EADDR_SAEN_Msk                    0x00008000UL           /*!< Enable bit address recognition */

//Cluster EADDR:
typedef struct {
  union {
  /*!< Extended address Register */
    __IO uint32_t EADDR;                                             /*!< EADDR : type used for word access */
    __IO _I2C_EADDR_bits EADDR_bit;                                  /*!< EADDR_bit: structure used for bit access */
  };
} _I2C_EADDR_TypeDef;
typedef struct {
  union {                                                            /*!< Data register */
    __IO uint32_t SDA;                                               /*!< SDA    : type used for word access */
    __IO _I2C_SDA_bits  SDA_bit;                                     /*!< SDA_bit: structure used for bit access */
  };
  union {                                                            /*!< Status register */
    __I uint32_t ST;                                                 /*!< ST    : type used for word access */
    __I _I2C_ST_bits  ST_bit;                                        /*!< ST_bit: structure used for bit access */
  };
  union {                                                            /*!< Status and control register */
    __IO uint32_t CST;                                               /*!< CST    : type used for word access */
    __IO _I2C_CST_bits  CST_bit;                                     /*!< CST_bit: structure used for bit access */
  };
  union {                                                            /*!< Control register 0 */
    __IO uint32_t CTL0;                                              /*!< CTL0    : type used for word access */
    __IO _I2C_CTL0_bits  CTL0_bit;                                   /*!< CTL0_bit: structure used for bit access */
  };
  union {                                                            /*!< Register own address */
    __IO uint32_t ADDR;                                              /*!< ADDR    : type used for word access */
    __IO _I2C_ADDR_bits  ADDR_bit;                                   /*!< ADDR_bit: structure used for bit access */
  };
  union {                                                            /*!< Control register 1 */
    __IO uint32_t CTL1;                                              /*!< CTL1    : type used for word access */
    __IO _I2C_CTL1_bits  CTL1_bit;                                   /*!< CTL1_bit: structure used for bit access */
  };
  union {                                                            /*!< Prescaler load register */
    __IO uint32_t TOPR;                                              /*!< TOPR    : type used for word access */
    __IO _I2C_TOPR_bits  TOPR_bit;                                   /*!< TOPR_bit: structure used for bit access */
  };
  union {                                                            /*!< Control register 2 */
    __IO uint32_t CTL2;                                              /*!< CTL2    : type used for word access */
    __IO _I2C_CTL2_bits  CTL2_bit;                                   /*!< CTL2_bit: structure used for bit access */
  };
  union {                                                            /*!< Control register 3 */
    __IO uint32_t CTL3;                                              /*!< CTL3    : type used for word access */
    __IO _I2C_CTL3_bits  CTL3_bit;                                   /*!< CTL3_bit: structure used for bit access */
  };
  union {                                                            /*!< Control Register 4 */
    __IO uint32_t CTL4;                                              /*!< CTL4    : type used for word access */
    __IO _I2C_CTL4_bits  CTL4_bit;                                   /*!< CTL4_bit: structure used for bit access */
  };
  _I2C_EADDR_TypeDef EADDR[8];
} I2C_TypeDef;


/******************************************************************************/
/*                         RCU registers                                      */
/******************************************************************************/

/*--  CGCFGAXI: Clockgate Config AHB register -----------------------------------------------------------------*/
typedef struct {
  uint32_t DMAEN                  :1;                                /*!< DMA AXI and APB clock enable */
  uint32_t SRAMEN                 :1;                                /*!< SRAM module clock enable */
  uint32_t FLASHEN                :1;                                /*!< Boot flash AXI and APB clock enable */
} _RCU_CGCFGAXI_bits;

/* Bit field positions: */
#define RCU_CGCFGAXI_DMAEN_Pos                0                      /*!< DMA AXI and APB clock enable */
#define RCU_CGCFGAXI_SRAMEN_Pos               1                      /*!< SRAM module clock enable */
#define RCU_CGCFGAXI_FLASHEN_Pos              2                      /*!< Boot flash AXI and APB clock enable */

/* Bit field masks: */
#define RCU_CGCFGAXI_DMAEN_Msk                0x00000001UL           /*!< DMA AXI and APB clock enable */
#define RCU_CGCFGAXI_SRAMEN_Msk               0x00000002UL           /*!< SRAM module clock enable */
#define RCU_CGCFGAXI_FLASHEN_Msk              0x00000004UL           /*!< Boot flash AXI and APB clock enable */

/*--  CGCFGAHB: Clockgate Config AHB register -----------------------------------------------------------------*/
typedef struct {
  uint32_t GPIOAEN                :1;                                /*!<  */
  uint32_t GPIOBEN                :1;                                /*!<  */
  uint32_t CANEN                  :1;                                /*!<  */
  uint32_t ADCEN                  :1;                                /*!<  */
} _RCU_CGCFGAHB_bits;

/* Bit field positions: */
#define RCU_CGCFGAHB_GPIOAEN_Pos              0                      /*!<  */
#define RCU_CGCFGAHB_GPIOBEN_Pos              1                      /*!<  */
#define RCU_CGCFGAHB_CANEN_Pos                2                      /*!<  */
#define RCU_CGCFGAHB_ADCEN_Pos                3                      /*!<  */

/* Bit field masks: */
#define RCU_CGCFGAHB_GPIOAEN_Msk              0x00000001UL           /*!<  */
#define RCU_CGCFGAHB_GPIOBEN_Msk              0x00000002UL           /*!<  */
#define RCU_CGCFGAHB_CANEN_Msk                0x00000004UL           /*!<  */
#define RCU_CGCFGAHB_ADCEN_Msk                0x00000008UL           /*!<  */

/*--  CGCFGAPB: Clockgate Config APB register -----------------------------------------------------------------*/
typedef struct {
  uint32_t DUMMY0                 :1;                                /*!<  */
  uint32_t DUMMY1                 :1;                                /*!<  */
  uint32_t SIUEN                  :1;                                /*!<  */
  uint32_t RCUEN                  :1;                                /*!<  */
  uint32_t RTCEN                  :1;                                /*!<  */
  uint32_t WDTEN                  :1;                                /*!<  */
  uint32_t I2C0EN                 :1;                                /*!<  */
  uint32_t I2C1EN                 :1;                                /*!<  */
  uint32_t TMR0EN                 :1;                                /*!< TMR32_0 clock enable */
  uint32_t TMR1EN                 :1;                                /*!< TMR32_1 clock enable */
  uint32_t TMR2EN                 :1;                                /*!< TMR16_0 clock enable */
  uint32_t TMR3EN                 :1;                                /*!< TMR16_1 clock enable */
  uint32_t TMR4EN                 :1;                                /*!< TMR16_2 clock enable */
  uint32_t SPI0EN                 :1;                                /*!<  */
  uint32_t SPI1EN                 :1;                                /*!<  */
  uint32_t SPI2EN                 :1;                                /*!<  */
  uint32_t UART0EN                :1;                                /*!<  */
  uint32_t UART1EN                :1;                                /*!<  */
  uint32_t DACEN                  :1;                                /*!<  */
} _RCU_CGCFGAPB_bits;

/* Bit field positions: */
#define RCU_CGCFGAPB_DUMMY0_Pos               0                      /*!<  */
#define RCU_CGCFGAPB_DUMMY1_Pos               1                      /*!<  */
#define RCU_CGCFGAPB_SIUEN_Pos                2                      /*!<  */
#define RCU_CGCFGAPB_RCUEN_Pos                3                      /*!<  */
#define RCU_CGCFGAPB_RTCEN_Pos                4                      /*!<  */
#define RCU_CGCFGAPB_WDTEN_Pos                5                      /*!<  */
#define RCU_CGCFGAPB_I2C0EN_Pos               6                      /*!<  */
#define RCU_CGCFGAPB_I2C1EN_Pos               7                      /*!<  */
#define RCU_CGCFGAPB_TMR0EN_Pos               8                      /*!< TMR32_0 clock enable */
#define RCU_CGCFGAPB_TMR1EN_Pos               9                      /*!< TMR32_1 clock enable */
#define RCU_CGCFGAPB_TMR2EN_Pos               10                     /*!< TMR16_0 clock enable */
#define RCU_CGCFGAPB_TMR3EN_Pos               11                     /*!< TMR16_1 clock enable */
#define RCU_CGCFGAPB_TMR4EN_Pos               12                     /*!< TMR16_2 clock enable */
#define RCU_CGCFGAPB_SPI0EN_Pos               13                     /*!<  */
#define RCU_CGCFGAPB_SPI1EN_Pos               14                     /*!<  */
#define RCU_CGCFGAPB_SPI2EN_Pos               15                     /*!<  */
#define RCU_CGCFGAPB_UART0EN_Pos              16                     /*!<  */
#define RCU_CGCFGAPB_UART1EN_Pos              17                     /*!<  */
#define RCU_CGCFGAPB_DACEN_Pos                18                     /*!<  */

/* Bit field masks: */
#define RCU_CGCFGAPB_DUMMY0_Msk               0x00000001UL           /*!<  */
#define RCU_CGCFGAPB_DUMMY1_Msk               0x00000002UL           /*!<  */
#define RCU_CGCFGAPB_SIUEN_Msk                0x00000004UL           /*!<  */
#define RCU_CGCFGAPB_RCUEN_Msk                0x00000008UL           /*!<  */
#define RCU_CGCFGAPB_RTCEN_Msk                0x00000010UL           /*!<  */
#define RCU_CGCFGAPB_WDTEN_Msk                0x00000020UL           /*!<  */
#define RCU_CGCFGAPB_I2C0EN_Msk               0x00000040UL           /*!<  */
#define RCU_CGCFGAPB_I2C1EN_Msk               0x00000080UL           /*!<  */
#define RCU_CGCFGAPB_TMR0EN_Msk               0x00000100UL           /*!< TMR32_0 clock enable */
#define RCU_CGCFGAPB_TMR1EN_Msk               0x00000200UL           /*!< TMR32_1 clock enable */
#define RCU_CGCFGAPB_TMR2EN_Msk               0x00000400UL           /*!< TMR16_0 clock enable */
#define RCU_CGCFGAPB_TMR3EN_Msk               0x00000800UL           /*!< TMR16_1 clock enable */
#define RCU_CGCFGAPB_TMR4EN_Msk               0x00001000UL           /*!< TMR16_2 clock enable */
#define RCU_CGCFGAPB_SPI0EN_Msk               0x00002000UL           /*!<  */
#define RCU_CGCFGAPB_SPI1EN_Msk               0x00004000UL           /*!<  */
#define RCU_CGCFGAPB_SPI2EN_Msk               0x00008000UL           /*!<  */
#define RCU_CGCFGAPB_UART0EN_Msk              0x00010000UL           /*!<  */
#define RCU_CGCFGAPB_UART1EN_Msk              0x00020000UL           /*!<  */
#define RCU_CGCFGAPB_DACEN_Msk                0x00040000UL           /*!<  */

/*--  RSTDISAXI: Reset Disable AXI register -------------------------------------------------------------------*/
typedef struct {
  uint32_t DMAEN                  :1;                                /*!< DMA reset disable */
  uint32_t SRAMEN                 :1;                                /*!< SRAM module reset disable */
  uint32_t FLASHEN                :1;                                /*!< Boot flash reset disable */
} _RCU_RSTDISAXI_bits;

/* Bit field positions: */
#define RCU_RSTDISAXI_DMAEN_Pos               0                      /*!< DMA reset disable */
#define RCU_RSTDISAXI_SRAMEN_Pos              1                      /*!< SRAM module reset disable */
#define RCU_RSTDISAXI_FLASHEN_Pos             2                      /*!< Boot flash reset disable */

/* Bit field masks: */
#define RCU_RSTDISAXI_DMAEN_Msk               0x00000001UL           /*!< DMA reset disable */
#define RCU_RSTDISAXI_SRAMEN_Msk              0x00000002UL           /*!< SRAM module reset disable */
#define RCU_RSTDISAXI_FLASHEN_Msk             0x00000004UL           /*!< Boot flash reset disable */

/*--  RSTDISAHB: Reset Disable AHB register -------------------------------------------------------------------*/
typedef struct {
  uint32_t GPIOAEN                :1;                                /*!<  */
  uint32_t GPIOBEN                :1;                                /*!<  */
  uint32_t CANEN                  :1;                                /*!<  */
  uint32_t ADCEN                  :1;                                /*!<  */
} _RCU_RSTDISAHB_bits;

/* Bit field positions: */
#define RCU_RSTDISAHB_GPIOAEN_Pos             0                      /*!<  */
#define RCU_RSTDISAHB_GPIOBEN_Pos             1                      /*!<  */
#define RCU_RSTDISAHB_CANEN_Pos               2                      /*!<  */
#define RCU_RSTDISAHB_ADCEN_Pos               3                      /*!<  */

/* Bit field masks: */
#define RCU_RSTDISAHB_GPIOAEN_Msk             0x00000001UL           /*!<  */
#define RCU_RSTDISAHB_GPIOBEN_Msk             0x00000002UL           /*!<  */
#define RCU_RSTDISAHB_CANEN_Msk               0x00000004UL           /*!<  */
#define RCU_RSTDISAHB_ADCEN_Msk               0x00000008UL           /*!<  */

/*--  RSTDISAPB: Reset Disable APB register -------------------------------------------------------------------*/
typedef struct {
  uint32_t DUMMY0                 :1;                                /*!<  */
  uint32_t DUMMY1                 :1;                                /*!<  */
  uint32_t SIUEN                  :1;                                /*!<  */
  uint32_t RCUEN                  :1;                                /*!<  */
  uint32_t RTCEN                  :1;                                /*!<  */
  uint32_t WDTEN                  :1;                                /*!<  */
  uint32_t I2C0EN                 :1;                                /*!<  */
  uint32_t I2C1EN                 :1;                                /*!<  */
  uint32_t TMR0EN                 :1;                                /*!< TMR32_0 reset disable */
  uint32_t TMR1EN                 :1;                                /*!< TMR32_1 reset disable */
  uint32_t TMR2EN                 :1;                                /*!< TMR16_0 reset disable */
  uint32_t TMR3EN                 :1;                                /*!< TMR16_1 reset disable */
  uint32_t TMR4EN                 :1;                                /*!< TMR16_2 clock enable */
  uint32_t SPI0EN                 :1;                                /*!<  */
  uint32_t SPI1EN                 :1;                                /*!<  */
  uint32_t SPI2EN                 :1;                                /*!<  */
  uint32_t UART0EN                :1;                                /*!<  */
  uint32_t UART1EN                :1;                                /*!<  */
  uint32_t DACEN                  :1;                                /*!<  */
} _RCU_RSTDISAPB_bits;

/* Bit field positions: */
#define RCU_RSTDISAPB_DUMMY0_Pos              0                      /*!<  */
#define RCU_RSTDISAPB_DUMMY1_Pos              1                      /*!<  */
#define RCU_RSTDISAPB_SIUEN_Pos               2                      /*!<  */
#define RCU_RSTDISAPB_RCUEN_Pos               3                      /*!<  */
#define RCU_RSTDISAPB_RTCEN_Pos               4                      /*!<  */
#define RCU_RSTDISAPB_WDTEN_Pos               5                      /*!<  */
#define RCU_RSTDISAPB_I2C0EN_Pos              6                      /*!<  */
#define RCU_RSTDISAPB_I2C1EN_Pos              7                      /*!<  */
#define RCU_RSTDISAPB_TMR0EN_Pos              8                      /*!< TMR32_0 reset disable */
#define RCU_RSTDISAPB_TMR1EN_Pos              9                      /*!< TMR32_1 reset disable */
#define RCU_RSTDISAPB_TMR2EN_Pos              10                     /*!< TMR16_0 reset disable */
#define RCU_RSTDISAPB_TMR3EN_Pos              11                     /*!< TMR16_1 reset disable */
#define RCU_RSTDISAPB_TMR4EN_Pos              12                     /*!< TMR16_2 clock enable */
#define RCU_RSTDISAPB_SPI0EN_Pos              13                     /*!<  */
#define RCU_RSTDISAPB_SPI1EN_Pos              14                     /*!<  */
#define RCU_RSTDISAPB_SPI2EN_Pos              15                     /*!<  */
#define RCU_RSTDISAPB_UART0EN_Pos             16                     /*!<  */
#define RCU_RSTDISAPB_UART1EN_Pos             17                     /*!<  */
#define RCU_RSTDISAPB_DACEN_Pos               18                     /*!<  */

/* Bit field masks: */
#define RCU_RSTDISAPB_DUMMY0_Msk              0x00000001UL           /*!<  */
#define RCU_RSTDISAPB_DUMMY1_Msk              0x00000002UL           /*!<  */
#define RCU_RSTDISAPB_SIUEN_Msk               0x00000004UL           /*!<  */
#define RCU_RSTDISAPB_RCUEN_Msk               0x00000008UL           /*!<  */
#define RCU_RSTDISAPB_RTCEN_Msk               0x00000010UL           /*!<  */
#define RCU_RSTDISAPB_WDTEN_Msk               0x00000020UL           /*!<  */
#define RCU_RSTDISAPB_I2C0EN_Msk              0x00000040UL           /*!<  */
#define RCU_RSTDISAPB_I2C1EN_Msk              0x00000080UL           /*!<  */
#define RCU_RSTDISAPB_TMR0EN_Msk              0x00000100UL           /*!< TMR32_0 reset disable */
#define RCU_RSTDISAPB_TMR1EN_Msk              0x00000200UL           /*!< TMR32_1 reset disable */
#define RCU_RSTDISAPB_TMR2EN_Msk              0x00000400UL           /*!< TMR16_0 reset disable */
#define RCU_RSTDISAPB_TMR3EN_Msk              0x00000800UL           /*!< TMR16_1 reset disable */
#define RCU_RSTDISAPB_TMR4EN_Msk              0x00001000UL           /*!< TMR16_2 clock enable */
#define RCU_RSTDISAPB_SPI0EN_Msk              0x00002000UL           /*!<  */
#define RCU_RSTDISAPB_SPI1EN_Msk              0x00004000UL           /*!<  */
#define RCU_RSTDISAPB_SPI2EN_Msk              0x00008000UL           /*!<  */
#define RCU_RSTDISAPB_UART0EN_Msk             0x00010000UL           /*!<  */
#define RCU_RSTDISAPB_UART1EN_Msk             0x00020000UL           /*!<  */
#define RCU_RSTDISAPB_DACEN_Msk               0x00040000UL           /*!<  */

/*--  SYSCLKCFG: System clock configuration register ----------------------------------------------------------*/
typedef struct {
  uint32_t SRC                    :2;                                /*!< System clock source */
  uint32_t                        :6;                                /*!< RESERVED */
  uint32_t SECEN                  :1;                                /*!<  */
} _RCU_SYSCLKCFG_bits;

/* Bit field positions: */
#define RCU_SYSCLKCFG_SRC_Pos                 0                      /*!< System clock source */
#define RCU_SYSCLKCFG_SECEN_Pos               8                      /*!<  */

/* Bit field masks: */
#define RCU_SYSCLKCFG_SRC_Msk                 0x00000003UL           /*!< System clock source */
#define RCU_SYSCLKCFG_SECEN_Msk               0x00000100UL           /*!<  */

/* Bit field enums: */
typedef enum {
  RCU_SYSCLKCFG_SRC_HSICLK                   = 0x0UL,                /*!< HSI 4MHz  */
  RCU_SYSCLKCFG_SRC_HSECLK                   = 0x1UL,                /*!< HSE(XTALL)  */
  RCU_SYSCLKCFG_SRC_PLLCLK               	 = 0x2UL,                /*!< Clock from PLL  */
  RCU_SYSCLKCFG_SRC_EXTCLK                   = 0x3UL,                /*!< external CLK from gpio pin */
} RCU_SYSCLKCFG_SRC_Enum;

/*--  SECCNT0: Security counter configuration 0 register ------------------------------------------------------*/
typedef struct {
  uint32_t VAL0                   :16;                               /*!<  */
  uint32_t VAL1                   :16;                               /*!<  */
} _RCU_SECCNT0_bits;

/* Bit field positions: */
#define RCU_SECCNT0_VAL0_Pos                  0                      /*!<  */
#define RCU_SECCNT0_VAL1_Pos                  16                     /*!<  */

/* Bit field masks: */
#define RCU_SECCNT0_VAL0_Msk                  0x0000FFFFUL           /*!<  */
#define RCU_SECCNT0_VAL1_Msk                  0xFFFF0000UL           /*!<  */

/*--  SECCNT1: Security counter configuration 1 register ------------------------------------------------------*/
typedef struct {
  uint32_t VAL2                   :16;                               /*!<  */
  uint32_t VAL3                   :16;                               /*!<  */
} _RCU_SECCNT1_bits;

/* Bit field positions: */
#define RCU_SECCNT1_VAL2_Pos                  0                      /*!<  */
#define RCU_SECCNT1_VAL3_Pos                  16                     /*!<  */

/* Bit field masks: */
#define RCU_SECCNT1_VAL2_Msk                  0x0000FFFFUL           /*!<  */
#define RCU_SECCNT1_VAL3_Msk                  0xFFFF0000UL           /*!<  */

/*--  CLKSTAT: System clock status register -------------------------------------------------------------------*/
typedef struct {
  uint32_t SRC                    :2;                                /*!< REFCLK:0:HSI 1MHz if CPE=0 or HSE(XTALL) if CPE=1;SRCCLK:1:HSE(XTALL) if CPE=0 or HSI 1MHz if CPE=1;SYSPLL0CLK:2: Clock from PLL OUT[0];EXTCLK:3: external CLK from gpio pin; */
  uint32_t                        :6;                                /*!< RESERVED */
  uint32_t CLKGOOD0               :1;                                /*!<  */
  uint32_t CLKGOOD1               :1;                                /*!<  */
  uint32_t CLKGOOD2               :1;                                /*!<  */
  uint32_t CLKGOOD3               :1;                                /*!<  */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t CLKERR0                :1;                                /*!<  */
  uint32_t CLKERR1                :1;                                /*!<  */
  uint32_t CLKERR2                :1;                                /*!<  */
  uint32_t CLKERR3                :1;                                /*!<  */
} _RCU_CLKSTAT_bits;

/* Bit field positions: */
#define RCU_CLKSTAT_SRC_Pos                   0                      /*!< REFCLK:0:HSI 1MHz if CPE=0 or HSE(XTALL) if CPE=1;SRCCLK:1:HSE(XTALL) if CPE=0 or HSI 1MHz if CPE=1;SYSPLL0CLK:2: Clock from PLL OUT[0];EXTCLK:3: external CLK from gpio pin; */
#define RCU_CLKSTAT_CLKGOOD0_Pos              8                      /*!<  */
#define RCU_CLKSTAT_CLKGOOD1_Pos              9                      /*!<  */
#define RCU_CLKSTAT_CLKGOOD2_Pos              10                     /*!<  */
#define RCU_CLKSTAT_CLKGOOD3_Pos              11                     /*!<  */
#define RCU_CLKSTAT_CLKERR0_Pos               16                     /*!<  */
#define RCU_CLKSTAT_CLKERR1_Pos               17                     /*!<  */
#define RCU_CLKSTAT_CLKERR2_Pos               18                     /*!<  */
#define RCU_CLKSTAT_CLKERR3_Pos               19                     /*!<  */

/* Bit field masks: */
#define RCU_CLKSTAT_SRC_Msk                   0x00000003UL           /*!< REFCLK:0:HSI 1MHz if CPE=0 or HSE(XTALL) if CPE=1;SRCCLK:1:HSE(XTALL) if CPE=0 or HSI 1MHz if CPE=1;SYSPLL0CLK:2: Clock from PLL OUT[0];EXTCLK:3: external CLK from gpio pin; */
#define RCU_CLKSTAT_CLKGOOD0_Msk              0x00000100UL           /*!<  */
#define RCU_CLKSTAT_CLKGOOD1_Msk              0x00000200UL           /*!<  */
#define RCU_CLKSTAT_CLKGOOD2_Msk              0x00000400UL           /*!<  */
#define RCU_CLKSTAT_CLKGOOD3_Msk              0x00000800UL           /*!<  */
#define RCU_CLKSTAT_CLKERR0_Msk               0x00010000UL           /*!<  */
#define RCU_CLKSTAT_CLKERR1_Msk               0x00020000UL           /*!<  */
#define RCU_CLKSTAT_CLKERR2_Msk               0x00040000UL           /*!<  */
#define RCU_CLKSTAT_CLKERR3_Msk               0x00080000UL           /*!<  */

/* Bit field enums: */
typedef enum {
  RCU_CLKSTAT_SRC_HSICLK                   = 0x0UL,                /*!< HSI 4MHz */
  RCU_CLKSTAT_SRC_HSECLK                   = 0x1UL,                /*!< HSE */
  RCU_CLKSTAT_SRC_PLLCLK               	   = 0x2UL,                /*!< Clock from PLL */
  RCU_CLKSTAT_SRC_EXTCLK                   = 0x3UL,                /*!< EXT clock from GPIO A.1 or A.14 */
} RCU_CLKSTAT_SRC_Enum;


/*--  RSTSYS: System Reset Register ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t RSTEN                  :1;                                /*!< Reset enable */
  uint32_t                        :15;                               /*!< RESERVED */
  uint32_t KEY                    :16;                               /*!< KEY 'A55A' in hexadecimal for unblocking */
} _RCU_RSTSYS_bits;

/* Bit field positions: */
#define RCU_RSTSYS_RSTEN_Pos                  0                      /*!< Reset enable */
#define RCU_RSTSYS_KEY_Pos                    16                     /*!< KEY 'A55A' in hexadecimal for unblocking */

/* Bit field masks: */
#define RCU_RSTSYS_RSTEN_Msk                  0x00000001UL           /*!< Reset enable */
#define RCU_RSTSYS_KEY_Msk                    0xFFFF0000UL           /*!< KEY 'A55A' in hexadecimal for unblocking */

/* Bit field enums: */
typedef enum {
  RCU_RSTSYS_KEY_VALID                       = 0xA55AUL,             /*!< Value that lead to chip reset if RSTEN = 1 */
  RCU_RSTSYS_KEY_DUMMY_0                     = 0x0UL,                /*!< Example value that prevents reset */
  RCU_RSTSYS_KEY_DUMMY_1                     = 0x1UL,                /*!< Example value that prevents reset */
} RCU_RSTSYS_KEY_Enum;

/*--  RSTSTAT: Reset Status Register --------------------------------------------------------------------------*/
typedef struct {
  uint32_t POR                    :1;                                /*!< PowerOn Reset status */
  uint32_t WDOG                   :1;                                /*!< WatchDog Reset status */
  uint32_t SYSRST                 :1;                                /*!< System Reset Status */
  uint32_t BOR                    :1;                                /*!< Brown-out reset status */
} _RCU_RSTSTAT_bits;

/* Bit field positions: */
#define RCU_RSTSTAT_POR_Pos                   0                      /*!< PowerOn Reset status */
#define RCU_RSTSTAT_WDOG_Pos                  1                      /*!< WatchDog Reset status */
#define RCU_RSTSTAT_SYSRST_Pos                2                      /*!< System Reset Status */
#define RCU_RSTSTAT_BOR_Pos                   3                      /*!< Brown-out reset status */

/* Bit field masks: */
#define RCU_RSTSTAT_POR_Msk                   0x00000001UL           /*!< PowerOn Reset status */
#define RCU_RSTSTAT_WDOG_Msk                  0x00000002UL           /*!< WatchDog Reset status */
#define RCU_RSTSTAT_SYSRST_Msk                0x00000004UL           /*!< System Reset Status */
#define RCU_RSTSTAT_BOR_Msk                   0x00000008UL           /*!< Brown-out reset status */

/*--  INTEN: Interrupt enable reigster ------------------------------------------------------------------------*/
typedef struct {
  uint32_t PLLLOCK                :1;                                /*!< Enable PLL lock interrupt */
  uint32_t PLLFAIL                :1;                                /*!< Enable PLL fail to lock interrupt */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t CLKGOOD1               :1;                                /*!<  */
  uint32_t CLKGOOD2               :1;                                /*!<  */
  uint32_t CLKGOOD3               :1;                                /*!<  */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t CLKERR1                :1;                                /*!<  */
  uint32_t CLKERR2                :1;                                /*!<  */
  uint32_t CLKERR3                :1;                                /*!<  */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t CLKSECERR1             :1;                                /*!<  */
  uint32_t CLKSECERR2             :1;                                /*!<  */
  uint32_t CLKSECERR3             :1;                                /*!<  */
} _RCU_INTEN_bits;

/* Bit field positions: */
#define RCU_INTEN_PLLLOCK_Pos                 0                      /*!< Enable PLL lock interrupt */
#define RCU_INTEN_PLLFAIL_Pos                 1                      /*!< Enable PLL fail to lock interrupt */
#define RCU_INTEN_CLKGOOD1_Pos                9                      /*!<  */
#define RCU_INTEN_CLKGOOD2_Pos                10                     /*!<  */
#define RCU_INTEN_CLKGOOD3_Pos                11                     /*!<  */
#define RCU_INTEN_CLKERR1_Pos                 17                     /*!<  */
#define RCU_INTEN_CLKERR2_Pos                 18                     /*!<  */
#define RCU_INTEN_CLKERR3_Pos                 19                     /*!<  */
#define RCU_INTEN_CLKSECERR1_Pos              25                     /*!<  */
#define RCU_INTEN_CLKSECERR2_Pos              26                     /*!<  */
#define RCU_INTEN_CLKSECERR3_Pos              27                     /*!<  */

/* Bit field masks: */
#define RCU_INTEN_PLLLOCK_Msk                 0x00000001UL           /*!< Enable PLL lock interrupt */
#define RCU_INTEN_PLLFAIL_Msk                 0x00000002UL           /*!< Enable PLL fail to lock interrupt */
#define RCU_INTEN_CLKGOOD1_Msk                0x00000200UL           /*!<  */
#define RCU_INTEN_CLKGOOD2_Msk                0x00000400UL           /*!<  */
#define RCU_INTEN_CLKGOOD3_Msk                0x00000800UL           /*!<  */
#define RCU_INTEN_CLKERR1_Msk                 0x00020000UL           /*!<  */
#define RCU_INTEN_CLKERR2_Msk                 0x00040000UL           /*!<  */
#define RCU_INTEN_CLKERR3_Msk                 0x00080000UL           /*!<  */
#define RCU_INTEN_CLKSECERR1_Msk              0x02000000UL           /*!<  */
#define RCU_INTEN_CLKSECERR2_Msk              0x04000000UL           /*!<  */
#define RCU_INTEN_CLKSECERR3_Msk              0x08000000UL           /*!<  */

/*--  INTSTAT: Interrupt status register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t PLLLOCK                :1;                                /*!< PLL lock signal raise occured */
  uint32_t PLLFAIL                :1;                                /*!< PLL lock signal drop occured */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t CLKGOOD1               :1;                                /*!<  */
  uint32_t CLKGOOD2               :1;                                /*!<  */
  uint32_t CLKGOOD3               :1;                                /*!<  */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t CLKERR1                :1;                                /*!<  */
  uint32_t CLKERR2                :1;                                /*!<  */
  uint32_t CLKERR3                :1;                                /*!<  */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t CLKSECERR1             :1;                                /*!<  */
  uint32_t CLKSECERR2             :1;                                /*!<  */
  uint32_t CLKSECERR3             :1;                                /*!<  */
} _RCU_INTSTAT_bits;

/* Bit field positions: */
#define RCU_INTSTAT_PLLLOCK_Pos               0                      /*!< PLL lock signal raise occured */
#define RCU_INTSTAT_PLLFAIL_Pos               1                      /*!< PLL lock signal drop occured */
#define RCU_INTSTAT_CLKGOOD1_Pos              9                      /*!<  */
#define RCU_INTSTAT_CLKGOOD2_Pos              10                     /*!<  */
#define RCU_INTSTAT_CLKGOOD3_Pos              11                     /*!<  */
#define RCU_INTSTAT_CLKERR1_Pos               17                     /*!<  */
#define RCU_INTSTAT_CLKERR2_Pos               18                     /*!<  */
#define RCU_INTSTAT_CLKERR3_Pos               19                     /*!<  */
#define RCU_INTSTAT_CLKSECERR1_Pos            25                     /*!<  */
#define RCU_INTSTAT_CLKSECERR2_Pos            26                     /*!<  */
#define RCU_INTSTAT_CLKSECERR3_Pos            27                     /*!<  */

/* Bit field masks: */
#define RCU_INTSTAT_PLLLOCK_Msk               0x00000001UL           /*!< PLL lock signal raise occured */
#define RCU_INTSTAT_PLLFAIL_Msk               0x00000002UL           /*!< PLL lock signal drop occured */
#define RCU_INTSTAT_CLKGOOD1_Msk              0x00000200UL           /*!<  */
#define RCU_INTSTAT_CLKGOOD2_Msk              0x00000400UL           /*!<  */
#define RCU_INTSTAT_CLKGOOD3_Msk              0x00000800UL           /*!<  */
#define RCU_INTSTAT_CLKERR1_Msk               0x00020000UL           /*!<  */
#define RCU_INTSTAT_CLKERR2_Msk               0x00040000UL           /*!<  */
#define RCU_INTSTAT_CLKERR3_Msk               0x00080000UL           /*!<  */
#define RCU_INTSTAT_CLKSECERR1_Msk            0x02000000UL           /*!<  */
#define RCU_INTSTAT_CLKSECERR2_Msk            0x04000000UL           /*!<  */
#define RCU_INTSTAT_CLKSECERR3_Msk            0x08000000UL           /*!<  */

/*--  PLLCFG: PLL Configuration Register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t PD                     :1;                                /*!< Powerdown enable */
  uint32_t BYPASS                 :1;                                /*!< Bypass enable */
  uint32_t FOUTEN                 :1;                                /*!< Fout enable */
  uint32_t CLKSEL                 :1;                                /*!< PLL reference clock source select */
  uint32_t SP                     :1;                                /*!< Song-Park mode */
  uint32_t ST                     :3;                                /*!< Sggma-delta modulator mode */
  uint32_t CP                     :4;                                /*!< Output current of current switch */
  uint32_t PFD                    :2;                                /*!< Mode of current switch */
  uint32_t LPF                    :2;                                /*!< Loop filter band */
  uint32_t VCOMODE                :4;                                /*!< Subband selection signal */
  uint32_t VCOMA                  :1;                                /*!< Ajust amplitude of GUN */
  uint32_t VCOMF                  :1;                                /*!< Ajust lower range of GUN */
  uint32_t DLDMODE                :1;                                /*!< Frequency detector delay */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t DT                     :2;                                /*!< fractional noise randomization mode */
} _RCU_PLLCFG_bits;

/* Bit field positions: */
#define RCU_PLLCFG_PD_Pos                     0                      /*!< Powerdown enable */
#define RCU_PLLCFG_BYPASS_Pos                 1                      /*!< Bypass enable */
#define RCU_PLLCFG_FOUTEN_Pos                 2                      /*!< Fout enable */
#define RCU_PLLCFG_CLKSEL_Pos                 3                      /*!< PLL reference clock source select */
#define RCU_PLLCFG_SP_Pos                     4                      /*!< Song-Park mode */
#define RCU_PLLCFG_ST_Pos                     5                      /*!< Sggma-delta modulator mode */
#define RCU_PLLCFG_CP_Pos                     8                      /*!< Output current of current switch */
#define RCU_PLLCFG_PFD_Pos                    12                     /*!< Mode of current switch */
#define RCU_PLLCFG_LPF_Pos                    14                     /*!< Loop filter band */
#define RCU_PLLCFG_VCOMODE_Pos                16                     /*!< Subband selection signal */
#define RCU_PLLCFG_VCOMA_Pos                  20                     /*!< Ajust amplitude of GUN */
#define RCU_PLLCFG_VCOMF_Pos                  21                     /*!< Ajust lower range of GUN */
#define RCU_PLLCFG_DLDMODE_Pos                22                     /*!< Frequency detector delay */
#define RCU_PLLCFG_DT_Pos                     24                     /*!< fractional noise randomization mode */

/* Bit field masks: */
#define RCU_PLLCFG_PD_Msk                     0x00000001UL           /*!< Powerdown enable */
#define RCU_PLLCFG_BYPASS_Msk                 0x00000002UL           /*!< Bypass enable */
#define RCU_PLLCFG_FOUTEN_Msk                 0x00000004UL           /*!< Fout enable */
#define RCU_PLLCFG_CLKSEL_Msk                 0x00000008UL           /*!< PLL reference clock source select */
#define RCU_PLLCFG_SP_Msk                     0x00000010UL           /*!< Song-Park mode */
#define RCU_PLLCFG_ST_Msk                     0x000000E0UL           /*!< Sggma-delta modulator mode */
#define RCU_PLLCFG_CP_Msk                     0x00000F00UL           /*!< Output current of current switch */
#define RCU_PLLCFG_PFD_Msk                    0x00003000UL           /*!< Mode of current switch */
#define RCU_PLLCFG_LPF_Msk                    0x0000C000UL           /*!< Loop filter band */
#define RCU_PLLCFG_VCOMODE_Msk                0x000F0000UL           /*!< Subband selection signal */
#define RCU_PLLCFG_VCOMA_Msk                  0x00100000UL           /*!< Ajust amplitude of GUN */
#define RCU_PLLCFG_VCOMF_Msk                  0x00200000UL           /*!< Ajust lower range of GUN */
#define RCU_PLLCFG_DLDMODE_Msk                0x00400000UL           /*!< Frequency detector delay */
#define RCU_PLLCFG_DT_Msk                     0x03000000UL           /*!< fractional noise randomization mode */

/* Bit field enums: */
typedef enum {
  RCU_PLLCFG_CLKSEL_HSE                      = 0x0UL,                /*!< external oscilator clock > 10 Mhz */
  RCU_PLLCFG_CLKSEL_EXTCLK                   = 0x1UL,                /*!< external clock from GPIO pin */
} RCU_PLLCFG_CLKSEL_Enum;

/*--  PLLDIV: PLL DIV Configuration Register ------------------------------------------------------------------*/
typedef struct {
  uint32_t DIV1A                  :3;                                /*!< Divider 1A (divide pre-divisor result by (DIV1A + 1)) */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t DIV1B                  :6;                                /*!< Divider 1B (divide divider 1A result by (DIV1B + 1)) */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t PREDIV                 :2;                                /*!< Pre-divisor coefficient. PREDIV = 0 | 1 | 2 | 3 -> divide Fvco by 1 | 1 | 2 | 4 */
  uint32_t NNCLR                  :1;                                /*!< N-divider enable */
  uint32_t RNCLR                  :1;                                /*!< R-divider enable */
  uint32_t RDIV                   :6;                                /*!< R-divider coefficient (divide Fin by (RDIV + 1)) */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t NDIV                   :8;                                /*!< Integer part of divider (divide pre-divisor result by NDIV) */
} _RCU_PLLDIV_bits;

/* Bit field positions: */
#define RCU_PLLDIV_DIV1A_Pos                  0                      /*!< Divider 1A (divide pre-divisor result by (DIV1A + 1)) */
#define RCU_PLLDIV_DIV1B_Pos                  4                      /*!< Divider 1B (divide divider 1A result by (DIV1B + 1)) */
#define RCU_PLLDIV_PREDIV_Pos                 12                     /*!< Pre-divisor coefficient. PREDIV = 0 | 1 | 2 | 3 -> divide Fvco by 1 | 1 | 2 | 4 */
#define RCU_PLLDIV_NNCLR_Pos                  14                     /*!< N-divider enable */
#define RCU_PLLDIV_RNCLR_Pos                  15                     /*!< R-divider enable */
#define RCU_PLLDIV_RDIV_Pos                   16                     /*!< R-divider coefficient (divide Fin by (RDIV + 1)) */
#define RCU_PLLDIV_NDIV_Pos                   24                     /*!< Integer part of divider (divide pre-divisor result by NDIV) */

/* Bit field masks: */
#define RCU_PLLDIV_DIV1A_Msk                  0x00000007UL           /*!< Divider 1A (divide pre-divisor result by (DIV1A + 1)) */
#define RCU_PLLDIV_DIV1B_Msk                  0x000003F0UL           /*!< Divider 1B (divide divider 1A result by (DIV1B + 1)) */
#define RCU_PLLDIV_PREDIV_Msk                 0x00003000UL           /*!< Pre-divisor coefficient. PREDIV = 0 | 1 | 2 | 3 -> divide Fvco by 1 | 1 | 2 | 4 */
#define RCU_PLLDIV_NNCLR_Msk                  0x00004000UL           /*!< N-divider enable */
#define RCU_PLLDIV_RNCLR_Msk                  0x00008000UL           /*!< R-divider enable */
#define RCU_PLLDIV_RDIV_Msk                   0x003F0000UL           /*!< R-divider coefficient (divide Fin by (RDIV + 1)) */
#define RCU_PLLDIV_NDIV_Msk                   0xFF000000UL           /*!< Integer part of divider (divide pre-divisor result by NDIV) */

/*--  PLLFRAC: PLL FRAC Configuration Register ----------------------------------------------------------------*/
typedef struct {
  uint32_t FRAC                   :24;                               /*!< numerator of fractional part */
} _RCU_PLLFRAC_bits;

/* Bit field positions: */
#define RCU_PLLFRAC_FRAC_Pos                  0                      /*!< numerator of fractional part */

/* Bit field masks: */
#define RCU_PLLFRAC_FRAC_Msk                  0x00FFFFFFUL           /*!< numerator of fractional part */

/*--  PLLMOD: PLL MOD Configuration Register ------------------------------------------------------------------*/
typedef struct {
  uint32_t MOD                    :24;                               /*!< denominator of fractional part */
} _RCU_PLLMOD_bits;

/* Bit field positions: */
#define RCU_PLLMOD_MOD_Pos                    0                      /*!< denominator of fractional part */

/* Bit field masks: */
#define RCU_PLLMOD_MOD_Msk                    0x00FFFFFFUL           /*!< denominator of fractional part */

/*--  UARTCFG: UART Clock and Reset Configuration Register ----------------------------------------------------*/
typedef struct {
  uint32_t CLKEN                  :1;                                /*!< Clock enable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t RSTDIS                 :1;                                /*!< Reset disable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t CLKSEL                 :2;                                /*!< Clock source select */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t DIVEN                  :1;                                /*!< Enable division by (2 * (DIVN + 1)) */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t DIVN                   :6;                                /*!< Divider coefficient */
} _RCU_UARTCFG_bits;

/* Bit field positions: */
#define RCU_UARTCFG_CLKEN_Pos                 0                      /*!< Clock enable */
#define RCU_UARTCFG_RSTDIS_Pos                4                      /*!< Reset disable */
#define RCU_UARTCFG_CLKSEL_Pos                8                      /*!< Clock source select */
#define RCU_UARTCFG_DIVEN_Pos                 12                     /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_UARTCFG_DIVN_Pos                  16                     /*!< Divider coefficient */

/* Bit field masks: */
#define RCU_UARTCFG_CLKEN_Msk                 0x00000001UL           /*!< Clock enable */
#define RCU_UARTCFG_RSTDIS_Msk                0x00000010UL           /*!< Reset disable */
#define RCU_UARTCFG_CLKSEL_Msk                0x00000300UL           /*!< Clock source select */
#define RCU_UARTCFG_DIVEN_Msk                 0x00001000UL           /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_UARTCFG_DIVN_Msk                  0x003F0000UL           /*!< Divider coefficient */

/* Bit field enums: */
typedef enum {
  RCU_UARTCFG_CLKSEL_REFCLK                  = 0x0UL,                /*!< HSI 4MHz if CPE=0 or HSE(XTALL) if CPE=1 */
  RCU_UARTCFG_CLKSEL_SRCCLK                  = 0x1UL,                /*!< HSE(XTALL) if CPE=0 or HSI 4MHz if CPE=1 */
  RCU_UARTCFG_CLKSEL_SYSPLL0CLK              = 0x2UL,                /*!< Clock from PLL OUT[0] */
  RCU_UARTCFG_CLKSEL_EXTCLK                  = 0x3UL,                /*!< external CLK from gpio pin */
} RCU_UARTCFG_CLKSEL_Enum;

/*--  SPICFG: SPI Clock and Reset Configuration Register ------------------------------------------------------*/
typedef struct {
  uint32_t CLKEN                  :1;                                /*!< Clock enable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t RSTDIS                 :1;                                /*!< Reset disable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t CLKSEL                 :2;                                /*!< Clock source select */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t DIVEN                  :1;                                /*!< Enable divider by (2 * (DIVN + 1)) */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t DIVN                   :6;                                /*!< Divider coefficient */
} _RCU_SPICFG_bits;

/* Bit field positions: */
#define RCU_SPICFG_CLKEN_Pos                  0                      /*!< Clock enable */
#define RCU_SPICFG_RSTDIS_Pos                 4                      /*!< Reset disable */
#define RCU_SPICFG_CLKSEL_Pos                 8                      /*!< Clock source select */
#define RCU_SPICFG_DIVEN_Pos                  12                     /*!< Enable divider by (2 * (DIVN + 1)) */
#define RCU_SPICFG_DIVN_Pos                   16                     /*!< Divider coefficient */

/* Bit field masks: */
#define RCU_SPICFG_CLKEN_Msk                  0x00000001UL           /*!< Clock enable */
#define RCU_SPICFG_RSTDIS_Msk                 0x00000010UL           /*!< Reset disable */
#define RCU_SPICFG_CLKSEL_Msk                 0x00000300UL           /*!< Clock source select */
#define RCU_SPICFG_DIVEN_Msk                  0x00001000UL           /*!< Enable divider by (2 * (DIVN + 1)) */
#define RCU_SPICFG_DIVN_Msk                   0x003F0000UL           /*!< Divider coefficient */

/* Bit field enums: */
typedef enum {
  RCU_SPICFG_CLKSEL_REFCLK                   = 0x0UL,                /*!< HSI 1MHz if CPE=0 or HSE(XTALL) if CPE=1 */
  RCU_SPICFG_CLKSEL_SRCCLK                   = 0x1UL,                /*!< HSE(XTALL) if CPE=0 or HSI 1MHz if CPE=1 */
  RCU_SPICFG_CLKSEL_SYSPLL0CLK               = 0x2UL,                /*!< Clock from PLL OUT[0] */
  RCU_SPICFG_CLKSEL_EXTCLK                   = 0x3UL,                /*!< external CLK from gpio pin */
} RCU_SPICFG_CLKSEL_Enum;

/*--  RTCCFG: RTC APB clock divider and reset -----------------------------------------------------------------*/
typedef struct {
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t RST                    :1;                                /*!< Reset active High */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t DIVEN                  :1;                                /*!< Enable APB clock division by (2 * (DIVN + 1)) */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t DIVN                   :6;                                /*!< APB clock divider coefficient */
} _RCU_RTCCFG_bits;

/* Bit field positions: */
#define RCU_RTCCFG_RST_Pos                    4                      /*!< Reset active High */
#define RCU_RTCCFG_DIVEN_Pos                  12                     /*!< Enable APB clock division by (2 * (DIVN + 1)) */
#define RCU_RTCCFG_DIVN_Pos                   16                     /*!< APB clock divider coefficient */

/* Bit field masks: */
#define RCU_RTCCFG_RST_Msk                    0x00000010UL           /*!< Reset active High */
#define RCU_RTCCFG_DIVEN_Msk                  0x00001000UL           /*!< Enable APB clock division by (2 * (DIVN + 1)) */
#define RCU_RTCCFG_DIVN_Msk                   0x003F0000UL           /*!< APB clock divider coefficient */

/*--  ADCCFG: ADC Clock and Reset Configuration Register ------------------------------------------------------*/
typedef struct {
  uint32_t CLKEN                  :1;                                /*!< Clock enable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t RSTDIS                 :1;                                /*!< Reset disable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t CLKSEL                 :2;                                /*!< Clock source select */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t DIVEN                  :1;                                /*!< Enable division by (2 * (DIVN + 1)) */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t DIVN                   :6;                                /*!< Divider coefficient */
} _RCU_ADCCFG_bits;

/* Bit field positions: */
#define RCU_ADCCFG_CLKEN_Pos                  0                      /*!< Clock enable */
#define RCU_ADCCFG_RSTDIS_Pos                 4                      /*!< Reset disable */
#define RCU_ADCCFG_CLKSEL_Pos                 8                      /*!< Clock source select */
#define RCU_ADCCFG_DIVEN_Pos                  12                     /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_ADCCFG_DIVN_Pos                   16                     /*!< Divider coefficient */

/* Bit field masks: */
#define RCU_ADCCFG_CLKEN_Msk                  0x00000001UL           /*!< Clock enable */
#define RCU_ADCCFG_RSTDIS_Msk                 0x00000010UL           /*!< Reset disable */
#define RCU_ADCCFG_CLKSEL_Msk                 0x00000300UL           /*!< Clock source select */
#define RCU_ADCCFG_DIVEN_Msk                  0x00001000UL           /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_ADCCFG_DIVN_Msk                   0x003F0000UL           /*!< Divider coefficient */

/* Bit field enums: */
typedef enum {
  RCU_ADCCFG_CLKSEL_REFCLK                   = 0x0UL,                /*!< HSI 4MHz if CPE=0 or HSE(XTALL) if CPE=1 */
  RCU_ADCCFG_CLKSEL_SRCCLK                   = 0x1UL,                /*!< HSE(XTALL) if CPE=0 or HSI 4MHz if CPE=1 */
  RCU_ADCCFG_CLKSEL_SYSPLL0CLK               = 0x2UL,                /*!< Clock from PLL OUT[0] */
  RCU_ADCCFG_CLKSEL_EXTCLK                   = 0x3UL,                /*!< external CLK from gpio pin */
} RCU_ADCCFG_CLKSEL_Enum;

/*--  WDTCFG: WatchDog Configuration Register -----------------------------------------------------------------*/
typedef struct {
  uint32_t CLKEN                  :1;                                /*!< Clock enable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t RSTDIS                 :1;                                /*!< Reset disable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t CLKSEL                 :2;                                /*!< Clock source select */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t DIVEN                  :1;                                /*!< Enable division by (2 * (DIVN + 1)) */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t DIVN                   :6;                                /*!< Divider coefficient */
} _RCU_WDTCFG_bits;

/* Bit field positions: */
#define RCU_WDTCFG_CLKEN_Pos                  0                      /*!< Clock enable */
#define RCU_WDTCFG_RSTDIS_Pos                 4                      /*!< Reset disable */
#define RCU_WDTCFG_CLKSEL_Pos                 8                      /*!< Clock source select */
#define RCU_WDTCFG_DIVEN_Pos                  12                     /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_WDTCFG_DIVN_Pos                   16                     /*!< Divider coefficient */

/* Bit field masks: */
#define RCU_WDTCFG_CLKEN_Msk                  0x00000001UL           /*!< Clock enable */
#define RCU_WDTCFG_RSTDIS_Msk                 0x00000010UL           /*!< Reset disable */
#define RCU_WDTCFG_CLKSEL_Msk                 0x00000300UL           /*!< Clock source select */
#define RCU_WDTCFG_DIVEN_Msk                  0x00001000UL           /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_WDTCFG_DIVN_Msk                   0x003F0000UL           /*!< Divider coefficient */

/* Bit field enums: */
typedef enum {
  RCU_WDTCFG_CLKSEL_REFCLK                   = 0x0UL,                /*!< HSI 4MHz if CPE=0 or HSE(XTALL) if CPE=1 */
  RCU_WDTCFG_CLKSEL_SRCCLK                   = 0x1UL,                /*!< HSE(XTALL) if CPE=0 or HSI 4MHz if CPE=1 */
  RCU_WDTCFG_CLKSEL_SYSPLL0CLK               = 0x2UL,                /*!< Clock from PLL OUT[0] */
  RCU_WDTCFG_CLKSEL_EXTCLK                   = 0x3UL,                /*!< external CLK from gpio pin */
} RCU_WDTCFG_CLKSEL_Enum;

/*--  CLKOUTCFG: Clockout Configuration Register --------------------------------------------------------------*/
typedef struct {
  uint32_t CLKEN                  :1;                                /*!< Clock enable */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t CLKSEL                 :2;                                /*!< Clock source select */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t DIVEN                  :1;                                /*!< Enable division by (2 * (DIVN + 1)) */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t DIVN                   :16;                               /*!< Divider coefficient */
} _RCU_CLKOUTCFG_bits;

/* Bit field positions: */
#define RCU_CLKOUTCFG_CLKEN_Pos               0                      /*!< Clock enable */
#define RCU_CLKOUTCFG_CLKSEL_Pos              8                      /*!< Clock source select */
#define RCU_CLKOUTCFG_DIVEN_Pos               12                     /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_CLKOUTCFG_DIVN_Pos                16                     /*!< Divider coefficient */

/* Bit field masks: */
#define RCU_CLKOUTCFG_CLKEN_Msk               0x00000001UL           /*!< Clock enable */
#define RCU_CLKOUTCFG_CLKSEL_Msk              0x00000300UL           /*!< Clock source select */
#define RCU_CLKOUTCFG_DIVEN_Msk               0x00001000UL           /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_CLKOUTCFG_DIVN_Msk                0xFFFF0000UL           /*!< Divider coefficient */

/* Bit field enums: */
typedef enum {
  RCU_CLKOUTCFG_CLKSEL_HSICLK                = 0x0UL,                /*!< HSI 4MHz */
  RCU_CLKOUTCFG_CLKSEL_HSECLK                = 0x1UL,                /*!< HSE(XTALL) */
  RCU_CLKOUTCFG_CLKSEL_PLLCLK            	 = 0x2UL,                /*!< Clock from PLL */
  RCU_CLKOUTCFG_CLKSEL_RTCCLK                = 0x3UL,                /*!< 32kHz oscilator */
} RCU_CLKOUTCFG_CLKSEL_Enum;

/*--  FLASHCFG: Flash Configuration Register ------------------------------------------------------------------*/
typedef struct {
  uint32_t CLKEN                  :1;                                /*!< Clock enable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t RSTDIS                 :1;                                /*!< Reset disable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t CLKSEL                 :2;                                /*!< Clock source select */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t DIVEN                  :1;                                /*!< Enable division by (2 * (DIVN + 1)) */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t DIVN                   :6;                                /*!< Divider coefficient */
} _RCU_FLASHCFG_bits;

/* Bit field positions: */
#define RCU_FLASHCFG_CLKEN_Pos                0                      /*!< Clock enable */
#define RCU_FLASHCFG_RSTDIS_Pos               4                      /*!< Reset disable */
#define RCU_FLASHCFG_CLKSEL_Pos               8                      /*!< Clock source select */
#define RCU_FLASHCFG_DIVEN_Pos                12                     /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_FLASHCFG_DIVN_Pos                 16                     /*!< Divider coefficient */

/* Bit field masks: */
#define RCU_FLASHCFG_CLKEN_Msk                0x00000001UL           /*!< Clock enable */
#define RCU_FLASHCFG_RSTDIS_Msk               0x00000010UL           /*!< Reset disable */
#define RCU_FLASHCFG_CLKSEL_Msk               0x00000300UL           /*!< Clock source select */
#define RCU_FLASHCFG_DIVEN_Msk                0x00001000UL           /*!< Enable division by (2 * (DIVN + 1)) */
#define RCU_FLASHCFG_DIVN_Msk                 0x003F0000UL           /*!< Divider coefficient */

/* Bit field enums: */
typedef enum {
  RCU_FLASHCFG_CLKSEL_REFCLK                 = 0x0UL,                /*!< HSI 4MHz if CPE=0 or HSE(XTALL) if CPE=1 */
  RCU_FLASHCFG_CLKSEL_SRCCLK                 = 0x1UL,                /*!< HSE(XTALL) if CPE=0 or HSI 4MHz if CPE=1 */
  RCU_FLASHCFG_CLKSEL_SYSPLL0CLK             = 0x2UL,                /*!< Clock from PLL OUT[0] */
  RCU_FLASHCFG_CLKSEL_EXTCLK                 = 0x3UL,                /*!< external CLK from gpio pin */
} RCU_FLASHCFG_CLKSEL_Enum;

/*--  BORCFG: Brown-Out Reset Configuration Register ----------------------------------------------------------*/
typedef struct {
  uint32_t EN                     :1;                                /*!< Enable BOR */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t TUNE                   :2;                                /*!< Tune BOR level */
} _RCU_BORCFG_bits;

/* Bit field positions: */
#define RCU_BORCFG_EN_Pos                     0                      /*!< Enable BOR */
#define RCU_BORCFG_TUNE_Pos                   4                      /*!< Tune BOR level */

/* Bit field masks: */
#define RCU_BORCFG_EN_Msk                     0x00000001UL           /*!< Enable BOR */
#define RCU_BORCFG_TUNE_Msk                   0x00000030UL           /*!< Tune BOR level */

/*--  LOCK: Lock configuration register -----------------------------------------------------------------------*/
typedef struct {
  uint32_t LOCK                   :1;                                /*!< Write with specific code to lock / unlock writing to other RCU registers */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t CODE                   :24;                               /*!< Write key  0xACCE55 to change LOCK bit value */
} _RCU_LOCK_bits;

/* Bit field positions: */
#define RCU_LOCK_LOCK_Pos                     0                      /*!< Write with specific code to lock / unlock writing to other RCU registers */
#define RCU_LOCK_CODE_Pos                     8                      /*!< Write key 0xACCE55 to change LOCK bit value */

/* Bit field masks: */
#define RCU_LOCK_LOCK_Msk                     0x00000001UL           /*!< Write with specific code to lock / unlock writing to other RCU registers */
#define RCU_LOCK_CODE_Msk                     0xFFFFFF00UL           /*!< Write key 0xACCE55 to change LOCK bit value */

/* Bit field enums: */
typedef enum {
  RCU_LOCK_CODE_CHANGE                       = 0xACCE55UL,           /*!< Value that allows the LOCK bit to be changed */
  RCU_LOCK_CODE_DUMMY_0                      = 0x0UL,                /*!< Example value that prevents the LOCK bit change */
  RCU_LOCK_CODE_DUMMY_1                      = 0x1UL,                /*!< Example value that prevents the LOCK bit change */
} RCU_LOCK_CODE_Enum;

/*--  HSECFG: HSE Configuration Register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t EN                     :1;                                /*!< Enable HSE pins */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t DS                     :2;                                /*!< Drive current select pins */
} _RCU_HSECFG_bits;

/* Bit field positions: */
#define RCU_HSECFG_EN_Pos                     0                      /*!< Enable HSE pins */
#define RCU_HSECFG_DS_Pos                     4                      /*!< Drive current select pins */

/* Bit field masks: */
#define RCU_HSECFG_EN_Msk                     0x00000001UL           /*!< Enable HSE pins */
#define RCU_HSECFG_DS_Msk                     0x00000030UL           /*!< Drive current select pins */

//Cluster UARTCFG:
typedef struct {
  union {
  /*!< UART Clock and Reset Configuration Register */
    __IO uint32_t UARTCFG;                                           /*!< UARTCFG : type used for word access */
    __IO _RCU_UARTCFG_bits UARTCFG_bit;                              /*!< UARTCFG_bit: structure used for bit access */
  };
} _RCU_UARTCFG_TypeDef;
//Cluster SPICFG:
typedef struct {
  union {
  /*!< SPI Clock and Reset Configuration Register */
    __IO uint32_t SPICFG;                                            /*!< SPICFG : type used for word access */
    __IO _RCU_SPICFG_bits SPICFG_bit;                                /*!< SPICFG_bit: structure used for bit access */
  };
} _RCU_SPICFG_TypeDef;
typedef struct {
  union {                                                            /*!< Clockgate Config AHB register */
    __IO uint32_t CGCFGAXI;                                           /*!< CGCFGAXI    : type used for word access */
    __IO _RCU_CGCFGAXI_bits  CGCFGAXI_bit;                           /*!< CGCFGAXI_bit: structure used for bit access */
  };
  union {                                                            /*!< Clockgate Config AHB register */
    __IO uint32_t CGCFGAHB;                                           /*!< CGCFGAHB    : type used for word access */
    __IO _RCU_CGCFGAHB_bits  CGCFGAHB_bit;                           /*!< CGCFGAHB_bit: structure used for bit access */
  };
  union {                                                            /*!< Clockgate Config APB register */
    __IO uint32_t CGCFGAPB;                                           /*!< CGCFGAPB    : type used for word access */
    __IO _RCU_CGCFGAPB_bits  CGCFGAPB_bit;                           /*!< CGCFGAPB_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0;
  union {                                                            /*!< Reset Disable AXI register */
    __IO uint32_t RSTDISAXI;                                           /*!< RSTDISAXI    : type used for word access */
    __IO _RCU_RSTDISAXI_bits  RSTDISAXI_bit;                         /*!< RSTDISAXI_bit: structure used for bit access */
  };
  union {                                                            /*!< Reset Disable AHB register */
    __IO uint32_t RSTDISAHB;                                           /*!< RSTDISAHB    : type used for word access */
    __IO _RCU_RSTDISAHB_bits  RSTDISAHB_bit;                         /*!< RSTDISAHB_bit: structure used for bit access */
  };
  union {                                                            /*!< Reset Disable APB register */
    __IO uint32_t RSTDISAPB;                                           /*!< RSTDISAPB    : type used for word access */
    __IO _RCU_RSTDISAPB_bits  RSTDISAPB_bit;                         /*!< RSTDISAPB_bit: structure used for bit access */
  };
    __IO uint32_t Reserved1;
  union {                                                            /*!< System clock configuration register */
    __IO uint32_t SYSCLKCFG;                                           /*!< SYSCLKCFG    : type used for word access */
    __IO _RCU_SYSCLKCFG_bits  SYSCLKCFG_bit;                         /*!< SYSCLKCFG_bit: structure used for bit access */
  };
  union {                                                            /*!< Security counter configuration 0 register */
    __IO uint32_t SECCNT0;                                           /*!< SECCNT0    : type used for word access */
    __IO _RCU_SECCNT0_bits  SECCNT0_bit;                             /*!< SECCNT0_bit: structure used for bit access */
  };
  union {                                                            /*!< Security counter configuration 1 register */
    __IO uint32_t SECCNT1;                                           /*!< SECCNT1    : type used for word access */
    __IO _RCU_SECCNT1_bits  SECCNT1_bit;                             /*!< SECCNT1_bit: structure used for bit access */
  };
  union {                                                            /*!< System clock status register */
    __I uint32_t CLKSTAT;                                            /*!< CLKSTAT    : type used for word access */
    __I _RCU_CLKSTAT_bits  CLKSTAT_bit;                              /*!< CLKSTAT_bit: structure used for bit access */
  };
  union {                                                            /*!< System Reset Register */
    __O uint32_t RSTSYS;                                             /*!< RSTSYS    : type used for word access */
    __O _RCU_RSTSYS_bits  RSTSYS_bit;                                /*!< RSTSYS_bit: structure used for bit access */
  };
  union {                                                            /*!< Reset Status Register */
    __IO uint32_t RSTSTAT;                                           /*!< RSTSTAT    : type used for word access */
    __IO _RCU_RSTSTAT_bits  RSTSTAT_bit;                             /*!< RSTSTAT_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt enable reigster */
    __IO uint32_t INTEN;                                             /*!< INTEN    : type used for word access */
    __IO _RCU_INTEN_bits  INTEN_bit;                                 /*!< INTEN_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt status register */
    __IO uint32_t INTSTAT;                                           /*!< INTSTAT    : type used for word access */
    __IO _RCU_INTSTAT_bits  INTSTAT_bit;                             /*!< INTSTAT_bit: structure used for bit access */
  };
  union {                                                            /*!< PLL Configuration Register */
    __IO uint32_t PLLCFG;                                            /*!< PLLCFG    : type used for word access */
    __IO _RCU_PLLCFG_bits  PLLCFG_bit;                               /*!< PLLCFG_bit: structure used for bit access */
  };
  union {                                                            /*!< PLL DIV Configuration Register */
    __IO uint32_t PLLDIV;                                            /*!< PLLDIV    : type used for word access */
    __IO _RCU_PLLDIV_bits  PLLDIV_bit;                               /*!< PLLDIV_bit: structure used for bit access */
  };
  union {                                                            /*!< PLL FRAC Configuration Register */
    __IO uint32_t PLLFRAC;                                           /*!< PLLFRAC    : type used for word access */
    __IO _RCU_PLLFRAC_bits  PLLFRAC_bit;                             /*!< PLLFRAC_bit: structure used for bit access */
  };
  union {                                                            /*!< PLL MOD Configuration Register */
    __IO uint32_t PLLMOD;                                            /*!< PLLMOD    : type used for word access */
    __IO _RCU_PLLMOD_bits  PLLMOD_bit;                               /*!< PLLMOD_bit: structure used for bit access */
  };
  _RCU_UARTCFG_TypeDef UARTCFG[2];
    __IO uint32_t Reserved2[6];
  _RCU_SPICFG_TypeDef SPICFG[3];
  union {                                                            /*!< RTC APB clock divider and reset */
    __IO uint32_t RTCCFG;                                            /*!< RTCCFG    : type used for word access */
    __IO _RCU_RTCCFG_bits  RTCCFG_bit;                               /*!< RTCCFG_bit: structure used for bit access */
  };
  union {                                                            /*!< ADC Clock and Reset Configuration Register */
    __IO uint32_t ADCCFG;                                            /*!< ADCCFG    : type used for word access */
    __IO _RCU_ADCCFG_bits  ADCCFG_bit;                               /*!< ADCCFG_bit: structure used for bit access */
  };
  union {                                                            /*!< WatchDog Configuration Register */
    __IO uint32_t WDTCFG;                                            /*!< WDTCFG    : type used for word access */
    __IO _RCU_WDTCFG_bits  WDTCFG_bit;                               /*!< WDTCFG_bit: structure used for bit access */
  };
  union {                                                            /*!< Clockout Configuration Register */
    __IO uint32_t CLKOUTCFG;                                           /*!< CLKOUTCFG    : type used for word access */
    __IO _RCU_CLKOUTCFG_bits  CLKOUTCFG_bit;                         /*!< CLKOUTCFG_bit: structure used for bit access */
  };
  union {                                                            /*!< Flash Configuration Register */
    __IO uint32_t FLASHCFG;                                           /*!< FLASHCFG    : type used for word access */
    __IO _RCU_FLASHCFG_bits  FLASHCFG_bit;                           /*!< FLASHCFG_bit: structure used for bit access */
  };
  union {                                                            /*!< Brown-Out Reset Configuration Register */
    __IO uint32_t BORCFG;                                            /*!< BORCFG    : type used for word access */
    __IO _RCU_BORCFG_bits  BORCFG_bit;                               /*!< BORCFG_bit: structure used for bit access */
  };
  union {                                                            /*!< Lock configuration register */
    __IO uint32_t LOCK;                                              /*!< LOCK    : type used for word access */
    __IO _RCU_LOCK_bits  LOCK_bit;                                   /*!< LOCK_bit: structure used for bit access */
  };
  union {                                                            /*!< HSE Configuration Register */
    __IO uint32_t HSECFG;                                            /*!< HSECFG    : type used for word access */
    __IO _RCU_HSECFG_bits  HSECFG_bit;                               /*!< HSECFG_bit: structure used for bit access */
  };
} RCU_TypeDef;


/******************************************************************************/
/*                         RTC registers                                      */
/******************************************************************************/

/*--  TIME: Time register -------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!<  */
} _RTC_TIME_bits;

/* Bit field positions: */
#define RTC_TIME_VAL_Pos                      0                      /*!<  */

/* Bit field masks: */
#define RTC_TIME_VAL_Msk                      0xFFFFFFFFUL           /*!<  */

/*--  ALARM1: Alarm 1 register --------------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!<  */
} _RTC_ALARM1_bits;

/* Bit field positions: */
#define RTC_ALARM1_VAL_Pos                    0                      /*!<  */

/* Bit field masks: */
#define RTC_ALARM1_VAL_Msk                    0xFFFFFFFFUL           /*!<  */

/*--  ALARM2: Alarm 2 register --------------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!<  */
} _RTC_ALARM2_bits;

/* Bit field positions: */
#define RTC_ALARM2_VAL_Pos                    0                      /*!<  */

/* Bit field masks: */
#define RTC_ALARM2_VAL_Msk                    0xFFFFFFFFUL           /*!<  */

/*--  CONTROL: Control register -------------------------------------------------------------------------------*/
typedef struct {
  uint32_t A1IE                   :1;                                /*!< ALARM1 = TIME interrupt enable */
  uint32_t A2IE                   :1;                                /*!< ALARM2 = TIME interrupt enable */
  uint32_t BIE                    :1;                                /*!< Switch to battery supply interrupt enable */
  uint32_t NPIE                   :1;                                /*!< Switch to normal power supply interrupt enable */
  uint32_t OIE                    :1;                                /*!< Timer overflow interrupt enable */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t DRC                    :1;                                /*!< Disable RC oscillator */
  uint32_t FCM                    :1;                                /*!< Use 32 kHz clock to time register increment */
} _RTC_CONTROL_bits;

/* Bit field positions: */
#define RTC_CONTROL_A1IE_Pos                  0                      /*!< ALARM1 = TIME interrupt enable */
#define RTC_CONTROL_A2IE_Pos                  1                      /*!< ALARM2 = TIME interrupt enable */
#define RTC_CONTROL_BIE_Pos                   2                      /*!< Switch to battery supply interrupt enable */
#define RTC_CONTROL_NPIE_Pos                  3                      /*!< Switch to normal power supply interrupt enable */
#define RTC_CONTROL_OIE_Pos                   4                      /*!< Timer overflow interrupt enable */
#define RTC_CONTROL_DRC_Pos                   8                      /*!< Disable RC oscillator */
#define RTC_CONTROL_FCM_Pos                   9                      /*!< Use 32 kHz clock to time register increment */

/* Bit field masks: */
#define RTC_CONTROL_A1IE_Msk                  0x00000001UL           /*!< ALARM1 = TIME interrupt enable */
#define RTC_CONTROL_A2IE_Msk                  0x00000002UL           /*!< ALARM2 = TIME interrupt enable */
#define RTC_CONTROL_BIE_Msk                   0x00000004UL           /*!< Switch to battery supply interrupt enable */
#define RTC_CONTROL_NPIE_Msk                  0x00000008UL           /*!< Switch to normal power supply interrupt enable */
#define RTC_CONTROL_OIE_Msk                   0x00000010UL           /*!< Timer overflow interrupt enable */
#define RTC_CONTROL_DRC_Msk                   0x00000100UL           /*!< Disable RC oscillator */
#define RTC_CONTROL_FCM_Msk                   0x00000200UL           /*!< Use 32 kHz clock to time register increment */

/* Bit field enums: */
typedef enum {
  RTC_CONTROL_FCM_NORMAL_MODE                = 0x0UL,                /*!< The time register is incremented each second */
  RTC_CONTROL_FCM_FAST_MODE                  = 0x1UL,                /*!< 32 kHz clock is used to increment the time register */
} RTC_CONTROL_FCM_Enum;

/*--  STATUS: Status register ---------------------------------------------------------------------------------*/
typedef struct {
  uint32_t A1F                    :1;                                /*!< ALARM1 = TIME front was detected */
  uint32_t A2F                    :1;                                /*!< ALARM2 = TIME front was detected */
  uint32_t BF                     :1;                                /*!< Switch to battery supply was detected */
  uint32_t NPF                    :1;                                /*!< Switch to normal power supply was detected */
  uint32_t OF                     :1;                                /*!< Timer overflow was detected */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t OSC_OK                 :1;                                /*!< RC oscillator state is ok */
  uint32_t                        :22;                               /*!< RESERVED */
  uint32_t BU                     :1;                                /*!< Battery supply is used status */
} _RTC_STATUS_bits;

/* Bit field positions: */
#define RTC_STATUS_A1F_Pos                    0                      /*!< ALARM1 = TIME front was detected */
#define RTC_STATUS_A2F_Pos                    1                      /*!< ALARM2 = TIME front was detected */
#define RTC_STATUS_BF_Pos                     2                      /*!< Switch to battery supply was detected */
#define RTC_STATUS_NPF_Pos                    3                      /*!< Switch to normal power supply was detected */
#define RTC_STATUS_OF_Pos                     4                      /*!< Timer overflow was detected */
#define RTC_STATUS_OSC_OK_Pos                 8                      /*!< RC oscillator state is ok */
#define RTC_STATUS_BU_Pos                     31                     /*!< Battery supply is used status */

/* Bit field masks: */
#define RTC_STATUS_A1F_Msk                    0x00000001UL           /*!< ALARM1 = TIME front was detected */
#define RTC_STATUS_A2F_Msk                    0x00000002UL           /*!< ALARM2 = TIME front was detected */
#define RTC_STATUS_BF_Msk                     0x00000004UL           /*!< Switch to battery supply was detected */
#define RTC_STATUS_NPF_Msk                    0x00000008UL           /*!< Switch to normal power supply was detected */
#define RTC_STATUS_OF_Msk                     0x00000010UL           /*!< Timer overflow was detected */
#define RTC_STATUS_OSC_OK_Msk                 0x00000100UL           /*!< RC oscillator state is ok */
#define RTC_STATUS_BU_Msk                     0x80000000UL           /*!< Battery supply is used status */

/*--  TRIM_RC: RC oscillator trim register --------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :7;                                /*!<  */
  uint32_t SIGN                   :1;                                /*!<  */
} _RTC_TRIM_RC_bits;

/* Bit field positions: */
#define RTC_TRIM_RC_VAL_Pos                   0                      /*!<  */
#define RTC_TRIM_RC_SIGN_Pos                  7                      /*!<  */

/* Bit field masks: */
#define RTC_TRIM_RC_VAL_Msk                   0x0000007FUL           /*!<  */
#define RTC_TRIM_RC_SIGN_Msk                  0x00000080UL           /*!<  */

/*--  TRIM_CLK1S: Clock 1s trim register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :10;                               /*!<  */
  uint32_t SIGN                   :1;                                /*!<  */
} _RTC_TRIM_CLK1S_bits;

/* Bit field positions: */
#define RTC_TRIM_CLK1S_VAL_Pos                0                      /*!<  */
#define RTC_TRIM_CLK1S_SIGN_Pos               10                     /*!<  */

/* Bit field masks: */
#define RTC_TRIM_CLK1S_VAL_Msk                0x000003FFUL           /*!<  */
#define RTC_TRIM_CLK1S_SIGN_Msk               0x00000400UL           /*!<  */

/*--  GPR: General purpose register ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!<  */
} _RTC_GPR_bits;

/* Bit field positions: */
#define RTC_GPR_VAL_Pos                       0                      /*!<  */

/* Bit field masks: */
#define RTC_GPR_VAL_Msk                       0xFFFFFFFFUL           /*!<  */

//Cluster GPR:
typedef struct {
  union {
  /*!< General purpose register */
    __IO uint32_t GPR;                                               /*!< GPR : type used for word access */
    __IO _RTC_GPR_bits GPR_bit;                                      /*!< GPR_bit: structure used for bit access */
  };
} _RTC_GPR_TypeDef;
typedef struct {
  union {                                                            /*!< Time register */
    __IO uint32_t TIME;                                              /*!< TIME    : type used for word access */
    __IO _RTC_TIME_bits  TIME_bit;                                   /*!< TIME_bit: structure used for bit access */
  };
  union {                                                            /*!< Alarm 1 register */
    __IO uint32_t ALARM1;                                            /*!< ALARM1    : type used for word access */
    __IO _RTC_ALARM1_bits  ALARM1_bit;                               /*!< ALARM1_bit: structure used for bit access */
  };
  union {                                                            /*!< Alarm 2 register */
    __IO uint32_t ALARM2;                                            /*!< ALARM2    : type used for word access */
    __IO _RTC_ALARM2_bits  ALARM2_bit;                               /*!< ALARM2_bit: structure used for bit access */
  };
  union {                                                            /*!< Control register */
    __IO uint32_t CONTROL;                                           /*!< CONTROL    : type used for word access */
    __IO _RTC_CONTROL_bits  CONTROL_bit;                             /*!< CONTROL_bit: structure used for bit access */
  };
  union {                                                            /*!< Status register */
    __IO uint32_t STATUS;                                            /*!< STATUS    : type used for word access */
    __IO _RTC_STATUS_bits  STATUS_bit;                               /*!< STATUS_bit: structure used for bit access */
  };
  union {                                                            /*!< RC oscillator trim register */
    __IO uint32_t TRIM_RC;                                           /*!< TRIM_RC    : type used for word access */
    __IO _RTC_TRIM_RC_bits  TRIM_RC_bit;                             /*!< TRIM_RC_bit: structure used for bit access */
  };
  union {                                                            /*!< Clock 1s trim register */
    __IO uint32_t TRIM_CLK1S;                                           /*!< TRIM_CLK1S    : type used for word access */
    __IO _RTC_TRIM_CLK1S_bits  TRIM_CLK1S_bit;                       /*!< TRIM_CLK1S_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0;
  _RTC_GPR_TypeDef GPR[16];
} RTC_TypeDef;


/******************************************************************************/
/*                         SIU registers                                      */
/******************************************************************************/

/*--  CHIPID: Chip identifier ---------------------------------------------------------------------------------*/
typedef struct {
  uint32_t REV                    :4;                                /*!< Revision number */
  uint32_t ID                     :28;                               /*!< Model ID */
} _SIU_CHIPID_bits;

/* Bit field positions: */
#define SIU_CHIPID_REV_Pos                    0                      /*!< Revision number */
#define SIU_CHIPID_ID_Pos                     4                      /*!< Model ID */

/* Bit field masks: */
#define SIU_CHIPID_REV_Msk                    0x0000000FUL           /*!< Revision number */
#define SIU_CHIPID_ID_Msk                     0xFFFFFFF0UL           /*!< Model ID */

/*--  SERVCTL: Service mode Register --------------------------------------------------------------------------*/
typedef struct {
  uint32_t SERVSTAT               :1;                                /*!< Service mode status */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t SERVCMD                :1;                                /*!< Service mode erase comand/status */
} _SIU_SERVCTL_bits;

/* Bit field positions: */
#define SIU_SERVCTL_SERVSTAT_Pos              0                      /*!< Service mode status */
#define SIU_SERVCTL_SERVCMD_Pos               8                      /*!< Service mode erase comand/status */

/* Bit field masks: */
#define SIU_SERVCTL_SERVSTAT_Msk              0x00000001UL           /*!< Service mode status */
#define SIU_SERVCTL_SERVCMD_Msk               0x00000100UL           /*!< Service mode erase comand/status */

/*--  TMRCFG: Timers external clock config --------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR0CLKMUX             :1;                                /*!< Select external clock source TMR32_0 */
  uint32_t TMR1CLKMUX             :1;                                /*!< Select external clock source TMR32_1 */
  uint32_t TMR2CLKMUX             :1;                                /*!< Select external clock source TMR16_1 */
  uint32_t TMR3CLKMUX             :1;                                /*!< Select external clock source TMR16_1 */
  uint32_t TMR4CLKMUX             :1;                                /*!< Select external clock source TMR16_2 */
} _SIU_TMRCFG_bits;

/* Bit field positions: */
#define SIU_TMRCFG_TMR0CLKMUX_Pos             0                      /*!< Select external clock source TMR32_0 */
#define SIU_TMRCFG_TMR1CLKMUX_Pos             1                      /*!< Select external clock source TMR32_1 */
#define SIU_TMRCFG_TMR2CLKMUX_Pos             2                      /*!< Select external clock source TMR16_1 */
#define SIU_TMRCFG_TMR3CLKMUX_Pos             3                      /*!< Select external clock source TMR16_1 */
#define SIU_TMRCFG_TMR4CLKMUX_Pos             4                      /*!< Select external clock source TMR16_2 */

/* Bit field masks: */
#define SIU_TMRCFG_TMR0CLKMUX_Msk             0x00000001UL           /*!< Select external clock source TMR32_0 */
#define SIU_TMRCFG_TMR1CLKMUX_Msk             0x00000002UL           /*!< Select external clock source TMR32_1 */
#define SIU_TMRCFG_TMR2CLKMUX_Msk             0x00000004UL           /*!< Select external clock source TMR16_1 */
#define SIU_TMRCFG_TMR3CLKMUX_Msk             0x00000008UL           /*!< Select external clock source TMR16_1 */
#define SIU_TMRCFG_TMR4CLKMUX_Msk             0x00000010UL           /*!< Select external clock source TMR16_2 */

/* Bit field enums: */
typedef enum {
  SIU_TMRCFG_TMR0CLKMUX_EXTPIN               = 0x0UL,                /*!< external controler pin */
  SIU_TMRCFG_TMR0CLKMUX_PRETIMER             = 0x1UL,                /*!< previous timer PWM-output */
} SIU_TMRCFG_TMR0CLKMUX_Enum;

typedef enum {
  SIU_TMRCFG_TMR1CLKMUX_EXTPIN               = 0x0UL,                /*!< external controler pin */
  SIU_TMRCFG_TMR1CLKMUX_PRETIMER             = 0x1UL,                /*!< previous timer PWM-output */
} SIU_TMRCFG_TMR1CLKMUX_Enum;

typedef enum {
  SIU_TMRCFG_TMR2CLKMUX_EXTPIN               = 0x0UL,                /*!< external controler pin */
  SIU_TMRCFG_TMR2CLKMUX_PRETIMER             = 0x1UL,                /*!< previous timer PWM-output */
} SIU_TMRCFG_TMR2CLKMUX_Enum;

typedef enum {
  SIU_TMRCFG_TMR3CLKMUX_EXTPIN               = 0x0UL,                /*!< external controler pin */
  SIU_TMRCFG_TMR3CLKMUX_PRETIMER             = 0x1UL,                /*!< previous timer PWM-output */
} SIU_TMRCFG_TMR3CLKMUX_Enum;

typedef enum {
  SIU_TMRCFG_TMR4CLKMUX_EXTPIN               = 0x0UL,                /*!< external controler pin */
  SIU_TMRCFG_TMR4CLKMUX_PRETIMER             = 0x1UL,                /*!< previous timer PWM-output */
} SIU_TMRCFG_TMR4CLKMUX_Enum;

/*--  TMREN: Timers counting enable register ------------------------------------------------------------------*/
typedef struct {
  uint32_t CNT0EN                 :1;                                /*!< TMR32_0 counting enable */
  uint32_t CNT1EN                 :1;                                /*!< TMR32_1 counting enable */
  uint32_t CNT2EN                 :1;                                /*!< TMR16_0 counting enable */
  uint32_t CNT3EN                 :1;                                /*!< TMR16_1 counting enable */
  uint32_t CNT4EN                 :1;                                /*!< TMR16_2 counting enable */
} _SIU_TMREN_bits;

/* Bit field positions: */
#define SIU_TMREN_CNT0EN_Pos                  0                      /*!< TMR32_0 counting enable */
#define SIU_TMREN_CNT1EN_Pos                  1                      /*!< TMR32_1 counting enable */
#define SIU_TMREN_CNT2EN_Pos                  2                      /*!< TMR16_0 counting enable */
#define SIU_TMREN_CNT3EN_Pos                  3                      /*!< TMR16_1 counting enable */
#define SIU_TMREN_CNT4EN_Pos                  4                      /*!< TMR16_2 counting enable */

/* Bit field masks: */
#define SIU_TMREN_CNT0EN_Msk                  0x00000001UL           /*!< TMR32_0 counting enable */
#define SIU_TMREN_CNT1EN_Msk                  0x00000002UL           /*!< TMR32_1 counting enable */
#define SIU_TMREN_CNT2EN_Msk                  0x00000004UL           /*!< TMR16_0 counting enable */
#define SIU_TMREN_CNT3EN_Msk                  0x00000008UL           /*!< TMR16_1 counting enable */
#define SIU_TMREN_CNT4EN_Msk                  0x00000010UL           /*!< TMR16_2 counting enable */

/*--  RAMCTRL: SRAM control register --------------------------------------------------------------------------*/
typedef struct {
  uint32_t RMEN                   :1;                                /*!< Enable to use Read-Write Margin */
  uint32_t RM                     :2;                                /*!< Read-Write Margin value */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t LS0                    :1;                                /*!< Ligth Sleep RAM part 0 (0..16k) */
  uint32_t LS1                    :1;                                /*!< Ligth Sleep RAM part 1 (16k..32k) */
} _SIU_RAMCTRL_bits;

/* Bit field positions: */
#define SIU_RAMCTRL_RMEN_Pos                  0                      /*!< Enable to use Read-Write Margin */
#define SIU_RAMCTRL_RM_Pos                    1                      /*!< Read-Write Margin value */
#define SIU_RAMCTRL_LS0_Pos                   8                      /*!< Ligth Sleep RAM part 0 (0..16k) */
#define SIU_RAMCTRL_LS1_Pos                   9                      /*!< Ligth Sleep RAM part 1 (16k..32k) */

/* Bit field masks: */
#define SIU_RAMCTRL_RMEN_Msk                  0x00000001UL           /*!< Enable to use Read-Write Margin */
#define SIU_RAMCTRL_RM_Msk                    0x00000006UL           /*!< Read-Write Margin value */
#define SIU_RAMCTRL_LS0_Msk                   0x00000100UL           /*!< Ligth Sleep RAM part 0 (0..16k) */
#define SIU_RAMCTRL_LS1_Msk                   0x00000200UL           /*!< Ligth Sleep RAM part 1 (16k..32k) */

/*--  TCMCTRL: Core Tightly-Coupled Memory SRAM control -------------------------------------------------------*/
typedef struct {
  uint32_t RMEN                   :1;                                /*!< Enable to use Read-Write Margin */
  uint32_t RM                     :2;                                /*!< Read-Write Margin value */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t LS0                    :1;                                /*!< Ligth Sleep TCM RAM part 0 (0..8k) */
  uint32_t LS1                    :1;                                /*!< Ligth Sleep TCM RAM part 1 (8k..16k) */
  uint32_t LS2                    :1;                                /*!< Ligth Sleep TCM RAM part 2 (16..24k) */
  uint32_t LS3                    :1;                                /*!< Ligth Sleep TCM RAM part 3 (24k..32k) */
} _SIU_TCMCTRL_bits;

/* Bit field positions: */
#define SIU_TCMCTRL_RMEN_Pos                  0                      /*!< Enable to use Read-Write Margin */
#define SIU_TCMCTRL_RM_Pos                    1                      /*!< Read-Write Margin value */
#define SIU_TCMCTRL_LS0_Pos                   8                      /*!< Ligth Sleep TCM RAM part 0 (0..8k) */
#define SIU_TCMCTRL_LS1_Pos                   9                      /*!< Ligth Sleep TCM RAM part 1 (8k..16k) */
#define SIU_TCMCTRL_LS2_Pos                   10                     /*!< Ligth Sleep TCM RAM part 2 (16..24k) */
#define SIU_TCMCTRL_LS3_Pos                   11                     /*!< Ligth Sleep TCM RAM part 3 (24k..32k) */

/* Bit field masks: */
#define SIU_TCMCTRL_RMEN_Msk                  0x00000001UL           /*!< Enable to use Read-Write Margin */
#define SIU_TCMCTRL_RM_Msk                    0x00000006UL           /*!< Read-Write Margin value */
#define SIU_TCMCTRL_LS0_Msk                   0x00000100UL           /*!< Ligth Sleep TCM RAM part 0 (0..8k) */
#define SIU_TCMCTRL_LS1_Msk                   0x00000200UL           /*!< Ligth Sleep TCM RAM part 1 (8k..16k) */
#define SIU_TCMCTRL_LS2_Msk                   0x00000400UL           /*!< Ligth Sleep TCM RAM part 2 (16..24k) */
#define SIU_TCMCTRL_LS3_Msk                   0x00000800UL           /*!< Ligth Sleep TCM RAM part 3 (24k..32k) */

/*--  CRAMCTRL: Core Cache SRAM control -----------------------------------------------------------------------*/
typedef struct {
  uint32_t RMEN                   :1;                                /*!< Enable to use Read-Write Margin */
  uint32_t RM                     :2;                                /*!< Read-Write Margin value */
  uint32_t                        :5;                                /*!< RESERVED */
  uint32_t L1ILS                  :1;                                /*!< Ligth Sleep L1 Instruction cache RAM */
  uint32_t L1DLS                  :1;                                /*!< Ligth Sleep L1 Data cache RAM */
} _SIU_CRAMCTRL_bits;

/* Bit field positions: */
#define SIU_CRAMCTRL_RMEN_Pos                 0                      /*!< Enable to use Read-Write Margin */
#define SIU_CRAMCTRL_RM_Pos                   1                      /*!< Read-Write Margin value */
#define SIU_CRAMCTRL_L1ILS_Pos                8                      /*!< Ligth Sleep L1 Instruction cache RAM */
#define SIU_CRAMCTRL_L1DLS_Pos                9                      /*!< Ligth Sleep L1 Data cache RAM */

/* Bit field masks: */
#define SIU_CRAMCTRL_RMEN_Msk                 0x00000001UL           /*!< Enable to use Read-Write Margin */
#define SIU_CRAMCTRL_RM_Msk                   0x00000006UL           /*!< Read-Write Margin value */
#define SIU_CRAMCTRL_L1ILS_Msk                0x00000100UL           /*!< Ligth Sleep L1 Instruction cache RAM */
#define SIU_CRAMCTRL_L1DLS_Msk                0x00000200UL           /*!< Ligth Sleep L1 Data cache RAM */

/*--  ADCCTRL: ADC level shifters and DP SRAM control ---------------------------------------------------------*/
typedef struct {
  uint32_t RMENA                  :1;                                /*!< Enable to use Read-Write Margin (Port A) */
  uint32_t RMA                    :2;                                /*!< Read-Write Margin value (Port A) */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t RMENB                  :1;                                /*!< Enable to use Read-Write Margin (Port B) */
  uint32_t RMB                    :2;                                /*!< Read-Write Margin value (Port B) */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t LS                     :1;                                /*!< Ligth Sleep ADC Dual Port RAM */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t LSHDIS                 :1;                                /*!< Disable Level-Shifters of ADC */
} _SIU_ADCCTRL_bits;

/* Bit field positions: */
#define SIU_ADCCTRL_RMENA_Pos                 0                      /*!< Enable to use Read-Write Margin (Port A) */
#define SIU_ADCCTRL_RMA_Pos                   1                      /*!< Read-Write Margin value (Port A) */
#define SIU_ADCCTRL_RMENB_Pos                 4                      /*!< Enable to use Read-Write Margin (Port B) */
#define SIU_ADCCTRL_RMB_Pos                   5                      /*!< Read-Write Margin value (Port B) */
#define SIU_ADCCTRL_LS_Pos                    8                      /*!< Ligth Sleep ADC Dual Port RAM */
#define SIU_ADCCTRL_LSHDIS_Pos                16                     /*!< Disable Level-Shifters of ADC */

/* Bit field masks: */
#define SIU_ADCCTRL_RMENA_Msk                 0x00000001UL           /*!< Enable to use Read-Write Margin (Port A) */
#define SIU_ADCCTRL_RMA_Msk                   0x00000006UL           /*!< Read-Write Margin value (Port A) */
#define SIU_ADCCTRL_RMENB_Msk                 0x00000010UL           /*!< Enable to use Read-Write Margin (Port B) */
#define SIU_ADCCTRL_RMB_Msk                   0x00000060UL           /*!< Read-Write Margin value (Port B) */
#define SIU_ADCCTRL_LS_Msk                    0x00000100UL           /*!< Ligth Sleep ADC Dual Port RAM */
#define SIU_ADCCTRL_LSHDIS_Msk                0x00010000UL           /*!< Disable Level-Shifters of ADC */

/*--  RCCTRL: RC generator control register -------------------------------------------------------------------*/
typedef struct {
  uint32_t TUNE                   :8;                                /*!< Tune RC generator period */
  uint32_t EN                     :1;                                /*!< Internal oscillator enable */
} _SIU_RCCTRL_bits;

/* Bit field positions: */
#define SIU_RCCTRL_TUNE_Pos                   0                      /*!< Tune RC generator period */
#define SIU_RCCTRL_EN_Pos                     8                      /*!< Internal oscillator enable */

/* Bit field masks: */
#define SIU_RCCTRL_TUNE_Msk                   0x000000FFUL           /*!< Tune RC generator period */
#define SIU_RCCTRL_EN_Msk                     0x00000100UL           /*!< Internal oscillator enable */

/*--  LDOCTRL: LDO control register ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t TUNE                   :4;                                /*!< Tune LDO output voltage */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t DISOSC                 :1;                                /*!< Disable oscillator 100kHz */
} _SIU_LDOCTRL_bits;

/* Bit field positions: */
#define SIU_LDOCTRL_TUNE_Pos                  0                      /*!< Tune LDO output voltage */
#define SIU_LDOCTRL_DISOSC_Pos                8                      /*!< Disable oscillator 100kHz */

/* Bit field masks: */
#define SIU_LDOCTRL_TUNE_Msk                  0x0000000FUL           /*!< Tune LDO output voltage */
#define SIU_LDOCTRL_DISOSC_Msk                0x00000100UL           /*!< Disable oscillator 100kHz */

/*--  TSENSCTRL: Temperature sensor control register ----------------------------------------------------------*/
typedef struct {
  uint32_t DIS                    :1;                                /*!< Disable temperature sensor */
  uint32_t SCALE                  :1;                                /*!< Scale out control */
} _SIU_TSENSCTRL_bits;

/* Bit field positions: */
#define SIU_TSENSCTRL_DIS_Pos                 0                      /*!< Disable temperature sensor */
#define SIU_TSENSCTRL_SCALE_Pos               1                      /*!< Scale out control */

/* Bit field masks: */
#define SIU_TSENSCTRL_DIS_Msk                 0x00000001UL           /*!< Disable temperature sensor */
#define SIU_TSENSCTRL_SCALE_Msk               0x00000002UL           /*!< Scale out control */

/* Bit field enums: */
typedef enum {
  SIU_TSENSCTRL_SCALE_OnePNJunction          = 0x0UL,                /*!< Output voltage 1.14..1.75 (125..-40 C) */
  SIU_TSENSCTRL_SCALE_TwoPNJunctions         = 0x1UL,                /*!< Output voltage 0.575..0.88 (125..-40 C) - best choice */
} SIU_TSENSCTRL_SCALE_Enum;

/*--  BGPCTRL: Bandgap control register -----------------------------------------------------------------------*/
typedef struct {
  uint32_t TUNE                   :12;                               /*!< Tune bandgap voltage */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t EN                     :1;                                /*!< Enable bandgap */
} _SIU_BGPCTRL_bits;

/* Bit field positions: */
#define SIU_BGPCTRL_TUNE_Pos                  0                      /*!< Tune bandgap voltage */
#define SIU_BGPCTRL_EN_Pos                    16                     /*!< Enable bandgap */

/* Bit field masks: */
#define SIU_BGPCTRL_TUNE_Msk                  0x00000FFFUL           /*!< Tune bandgap voltage */
#define SIU_BGPCTRL_EN_Msk                    0x00010000UL           /*!< Enable bandgap */

/*--  BOOTSELSTAT: BOOTSEL status register --------------------------------------------------------------------*/
typedef struct {
  uint32_t BOOTSEL                :1;                                /*!< BOOTSEL status */
} _SIU_BOOTSELSTAT_bits;

/* Bit field positions: */
#define SIU_BOOTSELSTAT_BOOTSEL_Pos           0                      /*!< BOOTSEL status */

/* Bit field masks: */
#define SIU_BOOTSELSTAT_BOOTSEL_Msk           0x00000001UL           /*!< BOOTSEL status */

/*--  TIMEOUTSTAT: Timeouts statust register ------------------------------------------------------------------*/
typedef struct {
  uint32_t APB                    :1;                                /*!<  */
  uint32_t AHB                    :1;                                /*!<  */
} _SIU_TIMEOUTSTAT_bits;

/* Bit field positions: */
#define SIU_TIMEOUTSTAT_APB_Pos               0                      /*!<  */
#define SIU_TIMEOUTSTAT_AHB_Pos               1                      /*!<  */

/* Bit field masks: */
#define SIU_TIMEOUTSTAT_APB_Msk               0x00000001UL           /*!<  */
#define SIU_TIMEOUTSTAT_AHB_Msk               0x00000002UL           /*!<  */

/*--  LOCK: Lock configuration register -----------------------------------------------------------------------*/
typedef struct {
  uint32_t LOCK                   :1;                                /*!< Write with specific code to lock / unlock writing to other SIU registers */
  uint32_t                        :7;                                /*!< RESERVED */
  uint32_t CODE                   :24;                               /*!< Write key  0xACCE55 to change LOCK bit value */
} _SIU_LOCK_bits;

/* Bit field positions: */
#define SIU_LOCK_LOCK_Pos                     0                      /*!< Write with specific code to lock / unlock writing to other SIU registers */
#define SIU_LOCK_CODE_Pos                     8                      /*!< Write key 0xACCE55 to change LOCK bit value */

/* Bit field masks: */
#define SIU_LOCK_LOCK_Msk                     0x00000001UL           /*!< Write with specific code to lock / unlock writing to other SIU registers */
#define SIU_LOCK_CODE_Msk                     0xFFFFFF00UL           /*!< Write key 0xACCE55 to change LOCK bit value */

/* Bit field enums: */
typedef enum {
  SIU_LOCK_CODE_CHANGE                       = 0xACCE55UL,           /*!< Value that allows the LOCK bit to be changed */
  SIU_LOCK_CODE_DUMMY_0                      = 0x0UL,                /*!< Example value that prevents the LOCK bit change */
  SIU_LOCK_CODE_DUMMY_1                      = 0x1UL,                /*!< Example value that prevents the LOCK bit change */
} SIU_LOCK_CODE_Enum;

/*--  APBTIMEOUT: APB timeout register ------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :12;                               /*!<  */
} _SIU_APBTIMEOUT_bits;

/* Bit field positions: */
#define SIU_APBTIMEOUT_VAL_Pos                0                      /*!<  */

/* Bit field masks: */
#define SIU_APBTIMEOUT_VAL_Msk                0x00000FFFUL           /*!<  */

/*--  AHBTIMEOUT: AHB timeout register ------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :12;                               /*!<  */
} _SIU_AHBTIMEOUT_bits;

/* Bit field positions: */
#define SIU_AHBTIMEOUT_VAL_Pos                0                      /*!<  */

/* Bit field masks: */
#define SIU_AHBTIMEOUT_VAL_Msk                0x00000FFFUL           /*!<  */

/*--  TMRMUX: TMRn capture/compare inputs select --------------------------------------------------------------*/
typedef struct {
  uint32_t CCIA                   :3;                                /*!< Select signal for TMRxx CCIA input */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t CCIB                   :3;                                /*!< Select signal for TMRxx CCIB input */
} _SIU_TMRMUX_bits;

/* Bit field positions: */
#define SIU_TMRMUX_CCIA_Pos                   0                      /*!< Select signal for TMRxx CCIA input */
#define SIU_TMRMUX_CCIB_Pos                   4                      /*!< Select signal for TMRxx CCIB input */

/* Bit field masks: */
#define SIU_TMRMUX_CCIA_Msk                   0x00000007UL           /*!< Select signal for TMRxx CCIA input */
#define SIU_TMRMUX_CCIB_Msk                   0x00000070UL           /*!< Select signal for TMRxx CCIB input */

/* Bit field enums: */
typedef enum {
  SIU_TMRMUX_CCIA_TMRIO_N                    = 0x0UL,                /*!< External pin tmr_io[n] */
  SIU_TMRMUX_CCIA_TMRIO_N_P1                 = 0x1UL,                /*!< External pin tmr_io[(n+1)%5] */
  SIU_TMRMUX_CCIA_TMRIO_N_P2                 = 0x2UL,                /*!< External pin tmr_io[(n+2)%5] */
  SIU_TMRMUX_CCIA_TMRIO_N_P3                 = 0x3UL,                /*!< External pin tmr_io[(n+3)%5] */
  SIU_TMRMUX_CCIA_TMRIO_N_P4                 = 0x4UL,                /*!< External pin tmr_io[(n+4)%5] */
  SIU_TMRMUX_CCIA_GPIOA                      = 0x5UL,                /*!< GPIOA adc soc impulse */
  SIU_TMRMUX_CCIA_GPIOB                      = 0x6UL,                /*!< GPIOB adc soc impulse */
} SIU_TMRMUX_CCIA_Enum;

typedef enum {
  SIU_TMRMUX_CCIB_TMRIO_N                    = 0x0UL,                /*!< External pin tmr_io[n] */
  SIU_TMRMUX_CCIB_TMRIO_N_P1                 = 0x1UL,                /*!< External pin tmr_io[(n+1)%5] */
  SIU_TMRMUX_CCIB_TMRIO_N_P2                 = 0x2UL,                /*!< External pin tmr_io[(n+2)%5] */
  SIU_TMRMUX_CCIB_TMRIO_N_P3                 = 0x3UL,                /*!< External pin tmr_io[(n+3)%5] */
  SIU_TMRMUX_CCIB_TMRIO_N_P4                 = 0x4UL,                /*!< External pin tmr_io[(n+4)%5] */
  SIU_TMRMUX_CCIB_GPIOA                      = 0x5UL,                /*!< GPIOA adc soc impulse */
  SIU_TMRMUX_CCIB_GPIOB                      = 0x6UL,                /*!< GPIOB adc soc impulse */
} SIU_TMRMUX_CCIB_Enum;

//Cluster TMRMUX:
typedef struct {
  union {
  /*!< TMRn capture/compare inputs select */
    __IO uint32_t TMRMUX;                                            /*!< TMRMUX : type used for word access */
    __IO _SIU_TMRMUX_bits TMRMUX_bit;                                /*!< TMRMUX_bit: structure used for bit access */
  };
} _SIU_TMRMUX_TypeDef;
typedef struct {
  union {                                                            /*!< Chip identifier */
    __I uint32_t CHIPID;                                             /*!< CHIPID    : type used for word access */
    __I _SIU_CHIPID_bits  CHIPID_bit;                                /*!< CHIPID_bit: structure used for bit access */
  };
  union {                                                            /*!< Service mode Register */
    __IO uint32_t SERVCTL;                                           /*!< SERVCTL    : type used for word access */
    __IO _SIU_SERVCTL_bits  SERVCTL_bit;                             /*!< SERVCTL_bit: structure used for bit access */
  };
  union {                                                            /*!< Timers external clock config */
    __IO uint32_t TMRCFG;                                            /*!< TMRCFG    : type used for word access */
    __IO _SIU_TMRCFG_bits  TMRCFG_bit;                               /*!< TMRCFG_bit: structure used for bit access */
  };
  union {                                                            /*!< Timers counting enable register */
    __IO uint32_t TMREN;                                             /*!< TMREN    : type used for word access */
    __IO _SIU_TMREN_bits  TMREN_bit;                                 /*!< TMREN_bit: structure used for bit access */
  };
  union {                                                            /*!< SRAM control register */
    __IO uint32_t RAMCTRL;                                           /*!< RAMCTRL    : type used for word access */
    __IO _SIU_RAMCTRL_bits  RAMCTRL_bit;                             /*!< RAMCTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< Core Tightly-Coupled Memory SRAM control */
    __IO uint32_t TCMCTRL;                                           /*!< TCMCTRL    : type used for word access */
    __IO _SIU_TCMCTRL_bits  TCMCTRL_bit;                             /*!< TCMCTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< Core Cache SRAM control */
    __IO uint32_t CRAMCTRL;                                           /*!< CRAMCTRL    : type used for word access */
    __IO _SIU_CRAMCTRL_bits  CRAMCTRL_bit;                           /*!< CRAMCTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< ADC level shifters and DP SRAM control */
    __IO uint32_t ADCCTRL;                                           /*!< ADCCTRL    : type used for word access */
    __IO _SIU_ADCCTRL_bits  ADCCTRL_bit;                             /*!< ADCCTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< RC generator control register */
    __IO uint32_t RCCTRL;                                            /*!< RCCTRL    : type used for word access */
    __IO _SIU_RCCTRL_bits  RCCTRL_bit;                               /*!< RCCTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< LDO control register */
    __IO uint32_t LDOCTRL;                                           /*!< LDOCTRL    : type used for word access */
    __IO _SIU_LDOCTRL_bits  LDOCTRL_bit;                             /*!< LDOCTRL_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0;
  union {                                                            /*!< Temperature sensor control register */
    __IO uint32_t TSENSCTRL;                                           /*!< TSENSCTRL    : type used for word access */
    __IO _SIU_TSENSCTRL_bits  TSENSCTRL_bit;                         /*!< TSENSCTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< Bandgap control register */
    __IO uint32_t BGPCTRL;                                           /*!< BGPCTRL    : type used for word access */
    __IO _SIU_BGPCTRL_bits  BGPCTRL_bit;                             /*!< BGPCTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< BOOTSEL status register */
    __I uint32_t BOOTSELSTAT;                                           /*!< BOOTSELSTAT    : type used for word access */
    __I _SIU_BOOTSELSTAT_bits  BOOTSELSTAT_bit;                      /*!< BOOTSELSTAT_bit: structure used for bit access */
  };
  union {                                                            /*!< Timeouts statust register */
    __I uint32_t TIMEOUTSTAT;                                           /*!< TIMEOUTSTAT    : type used for word access */
    __I _SIU_TIMEOUTSTAT_bits  TIMEOUTSTAT_bit;                      /*!< TIMEOUTSTAT_bit: structure used for bit access */
  };
  union {                                                            /*!< Lock configuration register */
    __IO uint32_t LOCK;                                              /*!< LOCK    : type used for word access */
    __IO _SIU_LOCK_bits  LOCK_bit;                                   /*!< LOCK_bit: structure used for bit access */
  };
  union {                                                            /*!< APB timeout register */
    __IO uint32_t APBTIMEOUT;                                           /*!< APBTIMEOUT    : type used for word access */
    __IO _SIU_APBTIMEOUT_bits  APBTIMEOUT_bit;                       /*!< APBTIMEOUT_bit: structure used for bit access */
  };
  union {                                                            /*!< AHB timeout register */
    __IO uint32_t AHBTIMEOUT;                                           /*!< AHBTIMEOUT    : type used for word access */
    __IO _SIU_AHBTIMEOUT_bits  AHBTIMEOUT_bit;                       /*!< AHBTIMEOUT_bit: structure used for bit access */
  };
    __IO uint32_t Reserved1[6];
  _SIU_TMRMUX_TypeDef TMRMUX[5];
} SIU_TypeDef;


/******************************************************************************/
/*                         SPI registers                                      */
/******************************************************************************/

/*--  CR: Control register ------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t DSS                    :5;                                /*!< Size of data is (value + 1) bits */
  uint32_t                        :3;                                /*!< RESERVED */
  uint32_t SCR                    :8;                                /*!< Value divider */
  uint32_t FRF                    :2;                                /*!< Select protocol */
  uint32_t SPO                    :1;                                /*!< Polarity SSPCLKOUT */
  uint32_t SPH                    :1;                                /*!< Phase SSPCLKOUT */
  uint32_t LBM                    :1;                                /*!< Test loopback mode */
  uint32_t SSE                    :1;                                /*!< Enable transceiver */
  uint32_t MS                     :1;                                /*!< Select mode */
  uint32_t SOD                    :1;                                /*!< Disable bit data */
  uint32_t RXIFLSEL               :4;                                /*!< Receive interrupt FIFO level select */
  uint32_t TXIFLSEL               :4;                                /*!< Transmit interrupt FIFO level select */
} _SPI_CR_bits;

/* Bit field positions: */
#define SPI_CR_DSS_Pos                        0                      /*!< Size of data is (value + 1) bits */
#define SPI_CR_SCR_Pos                        8                      /*!< Value divider */
#define SPI_CR_FRF_Pos                        16                     /*!< Select protocol */
#define SPI_CR_SPO_Pos                        18                     /*!< Polarity SSPCLKOUT */
#define SPI_CR_SPH_Pos                        19                     /*!< Phase SSPCLKOUT */
#define SPI_CR_LBM_Pos                        20                     /*!< Test loopback mode */
#define SPI_CR_SSE_Pos                        21                     /*!< Enable transceiver */
#define SPI_CR_MS_Pos                         22                     /*!< Select mode */
#define SPI_CR_SOD_Pos                        23                     /*!< Disable bit data */
#define SPI_CR_RXIFLSEL_Pos                   24                     /*!< Receive interrupt FIFO level select */
#define SPI_CR_TXIFLSEL_Pos                   28                     /*!< Transmit interrupt FIFO level select */

/* Bit field masks: */
#define SPI_CR_DSS_Msk                        0x0000001FUL           /*!< Size of data is (value + 1) bits */
#define SPI_CR_SCR_Msk                        0x0000FF00UL           /*!< Value divider */
#define SPI_CR_FRF_Msk                        0x00030000UL           /*!< Select protocol */
#define SPI_CR_SPO_Msk                        0x00040000UL           /*!< Polarity SSPCLKOUT */
#define SPI_CR_SPH_Msk                        0x00080000UL           /*!< Phase SSPCLKOUT */
#define SPI_CR_LBM_Msk                        0x00100000UL           /*!< Test loopback mode */
#define SPI_CR_SSE_Msk                        0x00200000UL           /*!< Enable transceiver */
#define SPI_CR_MS_Msk                         0x00400000UL           /*!< Select mode */
#define SPI_CR_SOD_Msk                        0x00800000UL           /*!< Disable bit data */
#define SPI_CR_RXIFLSEL_Msk                   0x0F000000UL           /*!< Receive interrupt FIFO level select */
#define SPI_CR_TXIFLSEL_Msk                   0xF0000000UL           /*!< Transmit interrupt FIFO level select */

/* Bit field enums: */
typedef enum {
  SPI_CR_DSS_4bit                            = 0x3UL,                /*!< data size 4 bits */
  SPI_CR_DSS_5bit                            = 0x4UL,                /*!< data size 5 bits */
  SPI_CR_DSS_6bit                            = 0x5UL,                /*!< data size 6 bits */
  SPI_CR_DSS_7bit                            = 0x6UL,                /*!< data size 7 bits */
  SPI_CR_DSS_8bit                            = 0x7UL,                /*!< data size 8 bits */
  SPI_CR_DSS_9bit                            = 0x8UL,                /*!< data size 9 bits */
  SPI_CR_DSS_10bit                           = 0x9UL,                /*!< data size 10 bits */
  SPI_CR_DSS_11bit                           = 0xAUL,                /*!< data size 11 bits */
  SPI_CR_DSS_12bit                           = 0xBUL,                /*!< data size 12 bits */
  SPI_CR_DSS_13bit                           = 0xCUL,                /*!< data size 13 bits */
  SPI_CR_DSS_14bit                           = 0xDUL,                /*!< data size 14 bits */
  SPI_CR_DSS_15bit                           = 0xEUL,                /*!< data size 15 bits */
  SPI_CR_DSS_16bit                           = 0xFUL,                /*!< data size 16 bits */
  SPI_CR_DSS_17bit                           = 0x10UL,               /*!< data size 17 bits */
  SPI_CR_DSS_18bit                           = 0x11UL,               /*!< data size 18 bits */
  SPI_CR_DSS_19bit                           = 0x12UL,               /*!< data size 19 bits */
  SPI_CR_DSS_20bit                           = 0x13UL,               /*!< data size 20 bits */
  SPI_CR_DSS_21bit                           = 0x14UL,               /*!< data size 21 bits */
  SPI_CR_DSS_22bit                           = 0x15UL,               /*!< data size 22 bits */
  SPI_CR_DSS_23bit                           = 0x16UL,               /*!< data size 23 bits */
  SPI_CR_DSS_24bit                           = 0x17UL,               /*!< data size 24 bits */
  SPI_CR_DSS_25bit                           = 0x18UL,               /*!< data size 25 bits */
  SPI_CR_DSS_26bit                           = 0x19UL,               /*!< data size 26 bits */
  SPI_CR_DSS_27bit                           = 0x1AUL,               /*!< data size 27 bits */
  SPI_CR_DSS_28bit                           = 0x1BUL,               /*!< data size 28 bits */
  SPI_CR_DSS_29bit                           = 0x1CUL,               /*!< data size 29 bits */
  SPI_CR_DSS_30bit                           = 0x1DUL,               /*!< data size 30 bits */
  SPI_CR_DSS_31bit                           = 0x1EUL,               /*!< data size 31 bits */
  SPI_CR_DSS_32bit                           = 0x1FUL,               /*!< data size 32 bits */
} SPI_CR_DSS_Enum;

typedef enum {
  SPI_CR_FRF_SPI                             = 0x0UL,                /*!< SPI of Motorola */
  SPI_CR_FRF_SSI                             = 0x1UL,                /*!< SSI of Texas Instruments */
  SPI_CR_FRF_Microwire                       = 0x2UL,                /*!< Microwire of National Semiconductor */
} SPI_CR_FRF_Enum;

typedef enum {
  SPI_CR_MS_MASTER                           = 0x0UL,                /*!< Master mode selected */
  SPI_CR_MS_SLAVE                            = 0x1UL,                /*!< Slave mode selected */
} SPI_CR_MS_Enum;

/*--  DR: Data register ---------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t DATA                   :32;                               /*!<  */
} _SPI_DR_bits;

/* Bit field positions: */
#define SPI_DR_DATA_Pos                       0                      /*!<  */

/* Bit field masks: */
#define SPI_DR_DATA_Msk                       0xFFFFFFFFUL           /*!<  */

/*--  SR: State register --------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t TFE                    :1;                                /*!< FIFO buffer empty flag transmitter */
  uint32_t TNF                    :1;                                /*!< Indicator the transmitter FIFO buffer is not full */
  uint32_t RNE                    :1;                                /*!< Indicate not empty receive buffer */
  uint32_t RFF                    :1;                                /*!< Indicate full receive buffer */
  uint32_t BSY                    :1;                                /*!< Activity flag */
} _SPI_SR_bits;

/* Bit field positions: */
#define SPI_SR_TFE_Pos                        0                      /*!< FIFO buffer empty flag transmitter */
#define SPI_SR_TNF_Pos                        1                      /*!< Indicator the transmitter FIFO buffer is not full */
#define SPI_SR_RNE_Pos                        2                      /*!< Indicate not empty receive buffer */
#define SPI_SR_RFF_Pos                        3                      /*!< Indicate full receive buffer */
#define SPI_SR_BSY_Pos                        4                      /*!< Activity flag */

/* Bit field masks: */
#define SPI_SR_TFE_Msk                        0x00000001UL           /*!< FIFO buffer empty flag transmitter */
#define SPI_SR_TNF_Msk                        0x00000002UL           /*!< Indicator the transmitter FIFO buffer is not full */
#define SPI_SR_RNE_Msk                        0x00000004UL           /*!< Indicate not empty receive buffer */
#define SPI_SR_RFF_Msk                        0x00000008UL           /*!< Indicate full receive buffer */
#define SPI_SR_BSY_Msk                        0x00000010UL           /*!< Activity flag */

/*--  CPSR: Clock division factor register --------------------------------------------------------------------*/
typedef struct {
  uint32_t CPSDVSR                :8;                                /*!< Clock division factor. Bit0 always 0 */
} _SPI_CPSR_bits;

/* Bit field positions: */
#define SPI_CPSR_CPSDVSR_Pos                  0                      /*!< Clock division factor. Bit0 always 0 */

/* Bit field masks: */
#define SPI_CPSR_CPSDVSR_Msk                  0x000000FFUL           /*!< Clock division factor. Bit0 always 0 */

/*--  IMSC: Mask interrupt register ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t RORIM                  :1;                                /*!< Interrupt mask bit SSPRORINTR buffer overflow receiver */
  uint32_t RTIM                   :1;                                /*!< Interrupt mask bit SSPRTINTR timeout receiver */
  uint32_t RXIM                   :1;                                /*!< SSPRXINTR interrupt mask bit to fill 50% or less of the receiver FIFO buffer */
  uint32_t TXIM                   :1;                                /*!< SSPTXINTR interrupt mask bit to fill 50% or less of the FIFO buffer of the transmitter */
} _SPI_IMSC_bits;

/* Bit field positions: */
#define SPI_IMSC_RORIM_Pos                    0                      /*!< Interrupt mask bit SSPRORINTR buffer overflow receiver */
#define SPI_IMSC_RTIM_Pos                     1                      /*!< Interrupt mask bit SSPRTINTR timeout receiver */
#define SPI_IMSC_RXIM_Pos                     2                      /*!< SSPRXINTR interrupt mask bit to fill 50% or less of the receiver FIFO buffer */
#define SPI_IMSC_TXIM_Pos                     3                      /*!< SSPTXINTR interrupt mask bit to fill 50% or less of the FIFO buffer of the transmitter */

/* Bit field masks: */
#define SPI_IMSC_RORIM_Msk                    0x00000001UL           /*!< Interrupt mask bit SSPRORINTR buffer overflow receiver */
#define SPI_IMSC_RTIM_Msk                     0x00000002UL           /*!< Interrupt mask bit SSPRTINTR timeout receiver */
#define SPI_IMSC_RXIM_Msk                     0x00000004UL           /*!< SSPRXINTR interrupt mask bit to fill 50% or less of the receiver FIFO buffer */
#define SPI_IMSC_TXIM_Msk                     0x00000008UL           /*!< SSPTXINTR interrupt mask bit to fill 50% or less of the FIFO buffer of the transmitter */

/*--  RIS: Status register interrupt without mask -------------------------------------------------------------*/
typedef struct {
  uint32_t RORRIS                 :1;                                /*!< Interrupt status before masking SSPRORINTR */
  uint32_t RTRIS                  :1;                                /*!< Interrupt status before masking SSPRTINTR */
  uint32_t RXRIS                  :1;                                /*!< Interrupt status before masking SSPRXINTR */
  uint32_t TXRIS                  :1;                                /*!< Interrupt status before masking SSPTXINTR */
} _SPI_RIS_bits;

/* Bit field positions: */
#define SPI_RIS_RORRIS_Pos                    0                      /*!< Interrupt status before masking SSPRORINTR */
#define SPI_RIS_RTRIS_Pos                     1                      /*!< Interrupt status before masking SSPRTINTR */
#define SPI_RIS_RXRIS_Pos                     2                      /*!< Interrupt status before masking SSPRXINTR */
#define SPI_RIS_TXRIS_Pos                     3                      /*!< Interrupt status before masking SSPTXINTR */

/* Bit field masks: */
#define SPI_RIS_RORRIS_Msk                    0x00000001UL           /*!< Interrupt status before masking SSPRORINTR */
#define SPI_RIS_RTRIS_Msk                     0x00000002UL           /*!< Interrupt status before masking SSPRTINTR */
#define SPI_RIS_RXRIS_Msk                     0x00000004UL           /*!< Interrupt status before masking SSPRXINTR */
#define SPI_RIS_TXRIS_Msk                     0x00000008UL           /*!< Interrupt status before masking SSPTXINTR */

/*--  MIS: Status register interrupt masking account ----------------------------------------------------------*/
typedef struct {
  uint32_t RORMIS                 :1;                                /*!< Masked interrupt status SSPRORINTR */
  uint32_t RTMIS                  :1;                                /*!< Masked interrupt status SSPRTINTR */
  uint32_t RXMIS                  :1;                                /*!< Masked interrupt status SSPRXINTR */
  uint32_t TXMIS                  :1;                                /*!< Masked interrupt status SSPTXINTR */
} _SPI_MIS_bits;

/* Bit field positions: */
#define SPI_MIS_RORMIS_Pos                    0                      /*!< Masked interrupt status SSPRORINTR */
#define SPI_MIS_RTMIS_Pos                     1                      /*!< Masked interrupt status SSPRTINTR */
#define SPI_MIS_RXMIS_Pos                     2                      /*!< Masked interrupt status SSPRXINTR */
#define SPI_MIS_TXMIS_Pos                     3                      /*!< Masked interrupt status SSPTXINTR */

/* Bit field masks: */
#define SPI_MIS_RORMIS_Msk                    0x00000001UL           /*!< Masked interrupt status SSPRORINTR */
#define SPI_MIS_RTMIS_Msk                     0x00000002UL           /*!< Masked interrupt status SSPRTINTR */
#define SPI_MIS_RXMIS_Msk                     0x00000004UL           /*!< Masked interrupt status SSPRXINTR */
#define SPI_MIS_TXMIS_Msk                     0x00000008UL           /*!< Masked interrupt status SSPTXINTR */

/*--  ICR: Register reset interrupt ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t RORIC                  :1;                                /*!< Reset interrupt SSPRORINTR */
  uint32_t RTIC                   :1;                                /*!< Reset interrupt SSPRTINTR */
} _SPI_ICR_bits;

/* Bit field positions: */
#define SPI_ICR_RORIC_Pos                     0                      /*!< Reset interrupt SSPRORINTR */
#define SPI_ICR_RTIC_Pos                      1                      /*!< Reset interrupt SSPRTINTR */

/* Bit field masks: */
#define SPI_ICR_RORIC_Msk                     0x00000001UL           /*!< Reset interrupt SSPRORINTR */
#define SPI_ICR_RTIC_Msk                      0x00000002UL           /*!< Reset interrupt SSPRTINTR */

/*--  DMACR: Control register DMA -----------------------------------------------------------------------------*/
typedef struct {
  uint32_t RXDMAE                 :1;                                /*!< DMA enable bit at reception */
  uint32_t TXDMAE                 :1;                                /*!< DMA enable bit transmission */
  uint32_t DMARXSTOP              :1;                                /*!< Automatic clear DMA RX request generation when channel ends all transactions */
  uint32_t DMATXSTOP              :1;                                /*!< Automatic clear DMA TX request generation when channel ends all transactions */
} _SPI_DMACR_bits;

/* Bit field positions: */
#define SPI_DMACR_RXDMAE_Pos                  0                      /*!< DMA enable bit at reception */
#define SPI_DMACR_TXDMAE_Pos                  1                      /*!< DMA enable bit transmission */
#define SPI_DMACR_DMARXSTOP_Pos               2                      /*!< Automatic clear DMA RX request generation when channel ends all transactions */
#define SPI_DMACR_DMATXSTOP_Pos               3                      /*!< Automatic clear DMA TX request generation when channel ends all transactions */

/* Bit field masks: */
#define SPI_DMACR_RXDMAE_Msk                  0x00000001UL           /*!< DMA enable bit at reception */
#define SPI_DMACR_TXDMAE_Msk                  0x00000002UL           /*!< DMA enable bit transmission */
#define SPI_DMACR_DMARXSTOP_Msk               0x00000004UL           /*!< Automatic clear DMA RX request generation when channel ends all transactions */
#define SPI_DMACR_DMATXSTOP_Msk               0x00000008UL           /*!< Automatic clear DMA TX request generation when channel ends all transactions */

typedef struct {
  union {                                                            /*!< Control register */
    __IO uint32_t CR;                                                /*!< CR    : type used for word access */
    __IO _SPI_CR_bits  CR_bit;                                       /*!< CR_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0;
  union {                                                            /*!< Data register */
    __IO uint32_t DR;                                                /*!< DR    : type used for word access */
    __IO _SPI_DR_bits  DR_bit;                                       /*!< DR_bit: structure used for bit access */
  };
  union {                                                            /*!< State register */
    __I uint32_t SR;                                                 /*!< SR    : type used for word access */
    __I _SPI_SR_bits  SR_bit;                                        /*!< SR_bit: structure used for bit access */
  };
  union {                                                            /*!< Clock division factor register */
    __IO uint32_t CPSR;                                              /*!< CPSR    : type used for word access */
    __IO _SPI_CPSR_bits  CPSR_bit;                                   /*!< CPSR_bit: structure used for bit access */
  };
  union {                                                            /*!< Mask interrupt register */
    __IO uint32_t IMSC;                                              /*!< IMSC    : type used for word access */
    __IO _SPI_IMSC_bits  IMSC_bit;                                   /*!< IMSC_bit: structure used for bit access */
  };
  union {                                                            /*!< Status register interrupt without mask */
    __I uint32_t RIS;                                                /*!< RIS    : type used for word access */
    __I _SPI_RIS_bits  RIS_bit;                                      /*!< RIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Status register interrupt masking account */
    __I uint32_t MIS;                                                /*!< MIS    : type used for word access */
    __I _SPI_MIS_bits  MIS_bit;                                      /*!< MIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Register reset interrupt */
    __O uint32_t ICR;                                                /*!< ICR    : type used for word access */
    __O _SPI_ICR_bits  ICR_bit;                                      /*!< ICR_bit: structure used for bit access */
  };
  union {                                                            /*!< Control register DMA */
    __IO uint32_t DMACR;                                             /*!< DMACR    : type used for word access */
    __IO _SPI_DMACR_bits  DMACR_bit;                                 /*!< DMACR_bit: structure used for bit access */
  };
} SPI_TypeDef;


/******************************************************************************/
/*                         TMR32 registers                                    */
/******************************************************************************/

/*--  CTRL: Timer control register ----------------------------------------------------------------------------*/
typedef struct {
  uint32_t FREESOFT               :2;                                /*!< Emulation mode bits - select the behavior of the time-base counter during emulation events */
  uint32_t CLR                    :1;                                /*!< Timer Clear */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t MODE                   :2;                                /*!< Count mode */
  uint32_t DMATXSTOP              :1;                                /*!< Stop Timer when TX DMA channel ends all transactions */
  uint32_t DMARXSTOP              :1;                                /*!< Stop Timer when RX DMA channel ends all transactions */
  uint32_t CLKSEL                 :1;                                /*!< Clock Source Select */
  uint32_t OUTEN                  :1;                                /*!< Output Enable */
} _TMR32_CTRL_bits;

/* Bit field positions: */
#define TMR32_CTRL_FREESOFT_Pos               0                      /*!< Emulation mode bits - select the behavior of the time-base counter during emulation events */
#define TMR32_CTRL_CLR_Pos                    2                      /*!< Timer Clear */
#define TMR32_CTRL_MODE_Pos                   4                      /*!< Count mode */
#define TMR32_CTRL_DMATXSTOP_Pos              6                      /*!< Stop Timer when TX DMA channel ends all transactions */
#define TMR32_CTRL_DMARXSTOP_Pos              7                      /*!< Stop Timer when RX DMA channel ends all transactions */
#define TMR32_CTRL_CLKSEL_Pos                 8                      /*!< Clock Source Select */
#define TMR32_CTRL_OUTEN_Pos                  9                      /*!< Output Enable */

/* Bit field masks: */
#define TMR32_CTRL_FREESOFT_Msk               0x00000003UL           /*!< Emulation mode bits - select the behavior of the time-base counter during emulation events */
#define TMR32_CTRL_CLR_Msk                    0x00000004UL           /*!< Timer Clear */
#define TMR32_CTRL_MODE_Msk                   0x00000030UL           /*!< Count mode */
#define TMR32_CTRL_DMATXSTOP_Msk              0x00000040UL           /*!< Stop Timer when TX DMA channel ends all transactions */
#define TMR32_CTRL_DMARXSTOP_Msk              0x00000080UL           /*!< Stop Timer when RX DMA channel ends all transactions */
#define TMR32_CTRL_CLKSEL_Msk                 0x00000100UL           /*!< Clock Source Select */
#define TMR32_CTRL_OUTEN_Msk                  0x00000200UL           /*!< Output Enable */

/* Bit field enums: */
typedef enum {
  TMR32_CTRL_FREESOFT_StopAtCLK              = 0x0UL,                /*!< stop timer at next CLK tact */
  TMR32_CTRL_FREESOFT_StopAtOverload         = 0x1UL,                /*!< stop timer when overload */
  TMR32_CTRL_FREESOFT_NoStop                 = 0x2UL,                /*!< endless count */
} TMR32_CTRL_FREESOFT_Enum;

typedef enum {
  TMR32_CTRL_MODE_Stop                       = 0x0UL,                /*!< Timer is Stopped */
  TMR32_CTRL_MODE_Up                         = 0x1UL,                /*!< Timer count Up */
  TMR32_CTRL_MODE_Multiple                   = 0x2UL,                /*!< Timer count is multiple Up */
  TMR32_CTRL_MODE_UpDown                     = 0x3UL,                /*!< Timer count is multiple Up - Down */
} TMR32_CTRL_MODE_Enum;

typedef enum {
  TMR32_CTRL_CLKSEL_SysClk                   = 0x0UL,                /*!< Select system Clk */
  TMR32_CTRL_CLKSEL_ExtClk                   = 0x1UL,                /*!< Select External Clk */
} TMR32_CTRL_CLKSEL_Enum;

/*--  COUNT: Current value timer register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!< Current value timer */
} _TMR32_COUNT_bits;

/* Bit field positions: */
#define TMR32_COUNT_VAL_Pos                   0                      /*!< Current value timer */

/* Bit field masks: */
#define TMR32_COUNT_VAL_Msk                   0xFFFFFFFFUL           /*!< Current value timer */

/*--  CLKDIV: Clock divider register --------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!<  */
} _TMR32_CLKDIV_bits;

/* Bit field positions: */
#define TMR32_CLKDIV_VAL_Pos                  0                      /*!<  */

/* Bit field masks: */
#define TMR32_CLKDIV_VAL_Msk                  0xFFFFFFFFUL           /*!<  */

/*--  PERIOD: Timer period register ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!<  */
} _TMR32_PERIOD_bits;

/* Bit field positions: */
#define TMR32_PERIOD_VAL_Pos                  0                      /*!<  */

/* Bit field masks: */
#define TMR32_PERIOD_VAL_Msk                  0xFFFFFFFFUL           /*!<  */

/*--  IM: Interrupt mask register -----------------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer Interrupt Enable */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 Interrupt Enable */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 Interrupt Enable */
} _TMR32_IM_bits;

/* Bit field positions: */
#define TMR32_IM_TMR_Pos                      0                      /*!< Timer Interrupt Enable */
#define TMR32_IM_CAPCOM0_0_Pos                1                      /*!< Capcom0 Interrupt Enable */
#define TMR32_IM_CAPCOM0_1_Pos                2                      /*!< Capcom1 Interrupt Enable */

/* Bit field masks: */
#define TMR32_IM_TMR_Msk                      0x00000001UL           /*!< Timer Interrupt Enable */
#define TMR32_IM_CAPCOM0_0_Msk                0x00000002UL           /*!< Capcom0 Interrupt Enable */
#define TMR32_IM_CAPCOM0_1_Msk                0x00000004UL           /*!< Capcom1 Interrupt Enable */

/*--  RIS: Raw Interrupt Status register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer Interrupt Status */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 Interrupt Status */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 Interrupt Status */
} _TMR32_RIS_bits;

/* Bit field positions: */
#define TMR32_RIS_TMR_Pos                     0                      /*!< Timer Interrupt Status */
#define TMR32_RIS_CAPCOM0_0_Pos               1                      /*!< Capcom0 Interrupt Status */
#define TMR32_RIS_CAPCOM0_1_Pos               2                      /*!< Capcom1 Interrupt Status */

/* Bit field masks: */
#define TMR32_RIS_TMR_Msk                     0x00000001UL           /*!< Timer Interrupt Status */
#define TMR32_RIS_CAPCOM0_0_Msk               0x00000002UL           /*!< Capcom0 Interrupt Status */
#define TMR32_RIS_CAPCOM0_1_Msk               0x00000004UL           /*!< Capcom1 Interrupt Status */

/*--  MIS: Masked Interrupt Status register -------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer Interrupt Status */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 Interrupt Status */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 Interrupt Status */
} _TMR32_MIS_bits;

/* Bit field positions: */
#define TMR32_MIS_TMR_Pos                     0                      /*!< Timer Interrupt Status */
#define TMR32_MIS_CAPCOM0_0_Pos               1                      /*!< Capcom0 Interrupt Status */
#define TMR32_MIS_CAPCOM0_1_Pos               2                      /*!< Capcom1 Interrupt Status */

/* Bit field masks: */
#define TMR32_MIS_TMR_Msk                     0x00000001UL           /*!< Timer Interrupt Status */
#define TMR32_MIS_CAPCOM0_0_Msk               0x00000002UL           /*!< Capcom0 Interrupt Status */
#define TMR32_MIS_CAPCOM0_1_Msk               0x00000004UL           /*!< Capcom1 Interrupt Status */

/*--  IC: Clear Interrupt Status register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer Interrupt Clear */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 Interrupt Clear */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 Interrupt Clear */
} _TMR32_IC_bits;

/* Bit field positions: */
#define TMR32_IC_TMR_Pos                      0                      /*!< Timer Interrupt Clear */
#define TMR32_IC_CAPCOM0_0_Pos                1                      /*!< Capcom0 Interrupt Clear */
#define TMR32_IC_CAPCOM0_1_Pos                2                      /*!< Capcom1 Interrupt Clear */

/* Bit field masks: */
#define TMR32_IC_TMR_Msk                      0x00000001UL           /*!< Timer Interrupt Clear */
#define TMR32_IC_CAPCOM0_0_Msk                0x00000002UL           /*!< Capcom0 Interrupt Clear */
#define TMR32_IC_CAPCOM0_1_Msk                0x00000004UL           /*!< Capcom1 Interrupt Clear */

/*--  DMA_TXIM: DMA TX request mask register ------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer DMA TX Request Enable */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 DMA TX Request Enable */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 DMA TX Request Enable */
} _TMR32_DMA_TXIM_bits;

/* Bit field positions: */
#define TMR32_DMA_TXIM_TMR_Pos                0                      /*!< Timer DMA TX Request Enable */
#define TMR32_DMA_TXIM_CAPCOM0_0_Pos          1                      /*!< Capcom0 DMA TX Request Enable */
#define TMR32_DMA_TXIM_CAPCOM0_1_Pos          2                      /*!< Capcom1 DMA TX Request Enable */

/* Bit field masks: */
#define TMR32_DMA_TXIM_TMR_Msk                0x00000001UL           /*!< Timer DMA TX Request Enable */
#define TMR32_DMA_TXIM_CAPCOM0_0_Msk          0x00000002UL           /*!< Capcom0 DMA TX Request Enable */
#define TMR32_DMA_TXIM_CAPCOM0_1_Msk          0x00000004UL           /*!< Capcom1 DMA TX Request Enable */

/*--  DMA_RXIM: DMA RX request mask register ------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer DMA RX Request Enable */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 DMA RX Request Enable */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 DMA RX Request Enable */
} _TMR32_DMA_RXIM_bits;

/* Bit field positions: */
#define TMR32_DMA_RXIM_TMR_Pos                0                      /*!< Timer DMA RX Request Enable */
#define TMR32_DMA_RXIM_CAPCOM0_0_Pos          1                      /*!< Capcom0 DMA RX Request Enable */
#define TMR32_DMA_RXIM_CAPCOM0_1_Pos          2                      /*!< Capcom1 DMA RX Request Enable */

/* Bit field masks: */
#define TMR32_DMA_RXIM_TMR_Msk                0x00000001UL           /*!< Timer DMA RX Request Enable */
#define TMR32_DMA_RXIM_CAPCOM0_0_Msk          0x00000002UL           /*!< Capcom0 DMA RX Request Enable */
#define TMR32_DMA_RXIM_CAPCOM0_1_Msk          0x00000004UL           /*!< Capcom1 DMA RX Request Enable */

/*--  EXTEVT_IM: External Event mask register -----------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer External Event Request Enable */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 External Event Request Enable */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 External Event Request Enable */
} _TMR32_EXTEVT_IM_bits;

/* Bit field positions: */
#define TMR32_EXTEVT_IM_TMR_Pos               0                      /*!< Timer External Event Request Enable */
#define TMR32_EXTEVT_IM_CAPCOM0_0_Pos         1                      /*!< Capcom0 External Event Request Enable */
#define TMR32_EXTEVT_IM_CAPCOM0_1_Pos         2                      /*!< Capcom1 External Event Request Enable */

/* Bit field masks: */
#define TMR32_EXTEVT_IM_TMR_Msk               0x00000001UL           /*!< Timer External Event Request Enable */
#define TMR32_EXTEVT_IM_CAPCOM0_0_Msk         0x00000002UL           /*!< Capcom0 External Event Request Enable */
#define TMR32_EXTEVT_IM_CAPCOM0_1_Msk         0x00000004UL           /*!< Capcom1 External Event Request Enable */

/*-- CAPCOM: CTRL: Capture / Compare Control register ---------------------------------------------------------*/
typedef struct {
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t OVF                    :1;                                /*!< Capture Overflow */
  uint32_t OUT                    :1;                                /*!< Output */
  uint32_t CCI                    :1;                                /*!< Capture / Compare Input */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t OUTMODE                :3;                                /*!< Output Mode */
  uint32_t CAP                    :1;                                /*!< Capture Mode */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t SCCI                   :1;                                /*!< Synchronized Capture / Compare Input */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t CCISEL                 :2;                                /*!< Capture / Compare Input Select */
  uint32_t CAPMODE                :2;                                /*!< Capture Mode */
} _TMR32_CAPCOM_CTRL_bits;

/* Bit field positions: */
#define TMR32_CAPCOM_CTRL_OVF_Pos             1                      /*!< Capture Overflow */
#define TMR32_CAPCOM_CTRL_OUT_Pos             2                      /*!< Output */
#define TMR32_CAPCOM_CTRL_CCI_Pos             3                      /*!< Capture / Compare Input */
#define TMR32_CAPCOM_CTRL_OUTMODE_Pos         5                      /*!< Output Mode */
#define TMR32_CAPCOM_CTRL_CAP_Pos             8                      /*!< Capture Mode */
#define TMR32_CAPCOM_CTRL_SCCI_Pos            10                     /*!< Synchronized Capture / Compare Input */
#define TMR32_CAPCOM_CTRL_CCISEL_Pos          12                     /*!< Capture / Compare Input Select */
#define TMR32_CAPCOM_CTRL_CAPMODE_Pos         14                     /*!< Capture Mode */

/* Bit field masks: */
#define TMR32_CAPCOM_CTRL_OVF_Msk             0x00000002UL           /*!< Capture Overflow */
#define TMR32_CAPCOM_CTRL_OUT_Msk             0x00000004UL           /*!< Output */
#define TMR32_CAPCOM_CTRL_CCI_Msk             0x00000008UL           /*!< Capture / Compare Input */
#define TMR32_CAPCOM_CTRL_OUTMODE_Msk         0x000000E0UL           /*!< Output Mode */
#define TMR32_CAPCOM_CTRL_CAP_Msk             0x00000100UL           /*!< Capture Mode */
#define TMR32_CAPCOM_CTRL_SCCI_Msk            0x00000400UL           /*!< Synchronized Capture / Compare Input */
#define TMR32_CAPCOM_CTRL_CCISEL_Msk          0x00003000UL           /*!< Capture / Compare Input Select */
#define TMR32_CAPCOM_CTRL_CAPMODE_Msk         0x0000C000UL           /*!< Capture Mode */

/* Bit field enums: */
typedef enum {
  TMR32_CAPCOM_CTRL_OUTMODE_Out              = 0x0UL,                /*!< Out bit value */
  TMR32_CAPCOM_CTRL_OUTMODE_Set              = 0x1UL,                /*!< Set output when COUNT = CAPCOM_i.VAL */
  TMR32_CAPCOM_CTRL_OUTMODE_ToggleReset      = 0x2UL,                /*!< Toggle output when COUNT = CAPCOM_i.VAL, reset output when COUNT = CAPCOM_0.VAL */
  TMR32_CAPCOM_CTRL_OUTMODE_SetReset         = 0x3UL,                /*!< Set output when COUNT = CAPCOM_i.VAL, reset output when COUNT = CAPCOM_0.VAL */
  TMR32_CAPCOM_CTRL_OUTMODE_Toggle           = 0x4UL,                /*!< Toggle output when COUNT = CAPCOM_i.VAL */
  TMR32_CAPCOM_CTRL_OUTMODE_Reset            = 0x5UL,                /*!< Reset output when COUNT = CAPCOM_i.VAL */
  TMR32_CAPCOM_CTRL_OUTMODE_ToggleSet        = 0x6UL,                /*!< Toggle output when COUNT = CAPCOM_i.VAL, set output when COUNT = CAPCOM_0.VAL */
  TMR32_CAPCOM_CTRL_OUTMODE_ResetSet         = 0x7UL,                /*!< Reset output when COUNT = CAPCOM_i.VAL, set output when COUNT = CAPCOM_0.VAL */
} TMR32_CAPCOM_CTRL_OUTMODE_Enum;

typedef enum {
  TMR32_CAPCOM_CTRL_CAP_Compare              = 0x0UL,                /*!< Compare mode */
  TMR32_CAPCOM_CTRL_CAP_Capture              = 0x1UL,                /*!< Capture mode */
} TMR32_CAPCOM_CTRL_CAP_Enum;

typedef enum {
  TMR32_CAPCOM_CTRL_CCISEL_CCIA              = 0x0UL,                /*!< Capture/Compare input A */
  TMR32_CAPCOM_CTRL_CCISEL_CCIB              = 0x1UL,                /*!< Capture/Compare input B */
  TMR32_CAPCOM_CTRL_CCISEL_Low               = 0x2UL,                /*!< Constant 0 */
  TMR32_CAPCOM_CTRL_CCISEL_High              = 0x3UL,                /*!< Constant 1 */
} TMR32_CAPCOM_CTRL_CCISEL_Enum;

typedef enum {
  TMR32_CAPCOM_CTRL_CAPMODE_NoCapture        = 0x0UL,                /*!< No capture */
  TMR32_CAPCOM_CTRL_CAPMODE_RisingEdge       = 0x1UL,                /*!< Capture on rising edge */
  TMR32_CAPCOM_CTRL_CAPMODE_FallingEdge      = 0x2UL,                /*!< Capture on falling edge */
  TMR32_CAPCOM_CTRL_CAPMODE_BothEdges        = 0x3UL,                /*!< Capture on both rising and falling edges */
} TMR32_CAPCOM_CTRL_CAPMODE_Enum;

/*-- CAPCOM: VAL0: Capture/Compare Value 0 register -----------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!<  */
} _TMR32_CAPCOM_VAL0_bits;

/* Bit field positions: */
#define TMR32_CAPCOM_VAL0_VAL_Pos             0                      /*!<  */

/* Bit field masks: */
#define TMR32_CAPCOM_VAL0_VAL_Msk             0xFFFFFFFFUL           /*!<  */

/*-- CAPCOM: VAL1: Capture/Compare Value 1 register -----------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!<  */
} _TMR32_CAPCOM_VAL1_bits;

/* Bit field positions: */
#define TMR32_CAPCOM_VAL1_VAL_Pos             0                      /*!<  */

/* Bit field masks: */
#define TMR32_CAPCOM_VAL1_VAL_Msk             0xFFFFFFFFUL           /*!<  */

//Cluster CAPCOM:
typedef struct {
  union {
  /*!< Capture / Compare Control register */
    __IO uint32_t CTRL;                                              /*!< CTRL : type used for word access */
    __IO _TMR32_CAPCOM_CTRL_bits CTRL_bit;                           /*!< CTRL_bit: structure used for bit access */
  };
  union {
  /*!< Capture/Compare Value 0 register */
    __IO uint32_t VAL0;                                              /*!< VAL0 : type used for word access */
    __IO _TMR32_CAPCOM_VAL0_bits VAL0_bit;                           /*!< VAL0_bit: structure used for bit access */
  };
  union {
  /*!< Capture/Compare Value 1 register */
    __IO uint32_t VAL1;                                              /*!< VAL1 : type used for word access */
    __IO _TMR32_CAPCOM_VAL1_bits VAL1_bit;                           /*!< VAL1_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0;
} _TMR32_CAPCOM_TypeDef;
typedef struct {
  union {                                                            /*!< Timer control register */
    __IO uint32_t CTRL;                                              /*!< CTRL    : type used for word access */
    __IO _TMR32_CTRL_bits  CTRL_bit;                                 /*!< CTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< Current value timer register */
    __IO uint32_t COUNT;                                             /*!< COUNT    : type used for word access */
    __IO _TMR32_COUNT_bits  COUNT_bit;                               /*!< COUNT_bit: structure used for bit access */
  };
  union {                                                            /*!< Clock divider register */
    __IO uint32_t CLKDIV;                                            /*!< CLKDIV    : type used for word access */
    __IO _TMR32_CLKDIV_bits  CLKDIV_bit;                             /*!< CLKDIV_bit: structure used for bit access */
  };
  union {                                                            /*!< Timer period register */
    __IO uint32_t PERIOD;                                            /*!< PERIOD    : type used for word access */
    __IO _TMR32_PERIOD_bits  PERIOD_bit;                             /*!< PERIOD_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt mask register */
    __IO uint32_t IM;                                                /*!< IM    : type used for word access */
    __IO _TMR32_IM_bits  IM_bit;                                     /*!< IM_bit: structure used for bit access */
  };
  union {                                                            /*!< Raw Interrupt Status register */
    __I uint32_t RIS;                                                /*!< RIS    : type used for word access */
    __I _TMR32_RIS_bits  RIS_bit;                                    /*!< RIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Masked Interrupt Status register */
    __I uint32_t MIS;                                                /*!< MIS    : type used for word access */
    __I _TMR32_MIS_bits  MIS_bit;                                    /*!< MIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Clear Interrupt Status register */
    __O uint32_t IC;                                                 /*!< IC    : type used for word access */
    __O _TMR32_IC_bits  IC_bit;                                      /*!< IC_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA TX request mask register */
    __IO uint32_t DMA_TXIM;                                           /*!< DMA_TXIM    : type used for word access */
    __IO _TMR32_DMA_TXIM_bits  DMA_TXIM_bit;                         /*!< DMA_TXIM_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA RX request mask register */
    __IO uint32_t DMA_RXIM;                                           /*!< DMA_RXIM    : type used for word access */
    __IO _TMR32_DMA_RXIM_bits  DMA_RXIM_bit;                         /*!< DMA_RXIM_bit: structure used for bit access */
  };
  union {                                                            /*!< External Event mask register */
    __IO uint32_t EXTEVT_IM;                                           /*!< EXTEVT_IM    : type used for word access */
    __IO _TMR32_EXTEVT_IM_bits  EXTEVT_IM_bit;                       /*!< EXTEVT_IM_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0[53];
  _TMR32_CAPCOM_TypeDef CAPCOM[2];
} TMR32_TypeDef;


/******************************************************************************/
/*                         TMR16 registers                                    */
/******************************************************************************/

/*--  CTRL: Timer control register ----------------------------------------------------------------------------*/
typedef struct {
  uint32_t FREESOFT               :2;                                /*!< Emulation mode bits - select the behavior of the time-base counter during emulation events */
  uint32_t CLR                    :1;                                /*!< Timer Clear */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t MODE                   :2;                                /*!< Count mode */
  uint32_t DMATXSTOP              :1;                                /*!< Stop Timer when TX DMA channel ends all transactions */
  uint32_t DMARXSTOP              :1;                                /*!< Stop Timer when RX DMA channel ends all transactions */
  uint32_t CLKSEL                 :1;                                /*!< Clock Source Select */
  uint32_t OUTEN                  :1;                                /*!< CAPCOM block output enable */
} _TMR16_CTRL_bits;

/* Bit field positions: */
#define TMR16_CTRL_FREESOFT_Pos               0                      /*!< Emulation mode bits - select the behavior of the time-base counter during emulation events */
#define TMR16_CTRL_CLR_Pos                    2                      /*!< Timer Clear */
#define TMR16_CTRL_MODE_Pos                   4                      /*!< Count mode */
#define TMR16_CTRL_DMATXSTOP_Pos              6                      /*!< Stop Timer when TX DMA channel ends all transactions */
#define TMR16_CTRL_DMARXSTOP_Pos              7                      /*!< Stop Timer when RX DMA channel ends all transactions */
#define TMR16_CTRL_CLKSEL_Pos                 8                      /*!< Clock Source Select */
#define TMR16_CTRL_OUTEN_Pos                  9                      /*!< CAPCOM block output enable */

/* Bit field masks: */
#define TMR16_CTRL_FREESOFT_Msk               0x00000003UL           /*!< Emulation mode bits - select the behavior of the time-base counter during emulation events */
#define TMR16_CTRL_CLR_Msk                    0x00000004UL           /*!< Timer Clear */
#define TMR16_CTRL_MODE_Msk                   0x00000030UL           /*!< Count mode */
#define TMR16_CTRL_DMATXSTOP_Msk              0x00000040UL           /*!< Stop Timer when TX DMA channel ends all transactions */
#define TMR16_CTRL_DMARXSTOP_Msk              0x00000080UL           /*!< Stop Timer when RX DMA channel ends all transactions */
#define TMR16_CTRL_CLKSEL_Msk                 0x00000100UL           /*!< Clock Source Select */
#define TMR16_CTRL_OUTEN_Msk                  0x00000200UL           /*!< CAPCOM block output enable */

/* Bit field enums: */
typedef enum {
  TMR16_CTRL_FREESOFT_StopAtCLK              = 0x0UL,                /*!< stop timer at next CLK tact */
  TMR16_CTRL_FREESOFT_StopAtOverload         = 0x1UL,                /*!< stop timer when overload */
  TMR16_CTRL_FREESOFT_NoStop                 = 0x2UL,                /*!< endless count */
} TMR16_CTRL_FREESOFT_Enum;

typedef enum {
  TMR16_CTRL_MODE_Stop                       = 0x0UL,                /*!< Timer is Stopped */
  TMR16_CTRL_MODE_Up                         = 0x1UL,                /*!< Timer count Up */
  TMR16_CTRL_MODE_Multiple                   = 0x2UL,                /*!< Timer count is multiple Up */
  TMR16_CTRL_MODE_UpDown                     = 0x3UL,                /*!< Timer count is multiple Up - Down */
} TMR16_CTRL_MODE_Enum;

typedef enum {
  TMR16_CTRL_CLKSEL_SysClk                   = 0x0UL,                /*!< Select system Clk */
  TMR16_CTRL_CLKSEL_ExtClk                   = 0x1UL,                /*!< Select External Clk */
} TMR16_CTRL_CLKSEL_Enum;

/*--  COUNT: Current value timer register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!< Current value timer */
} _TMR16_COUNT_bits;

/* Bit field positions: */
#define TMR16_COUNT_VAL_Pos                   0                      /*!< Current value timer */

/* Bit field masks: */
#define TMR16_COUNT_VAL_Msk                   0x0000FFFFUL           /*!< Current value timer */

/*--  CLKDIV: Clock divider register --------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!<  */
} _TMR16_CLKDIV_bits;

/* Bit field positions: */
#define TMR16_CLKDIV_VAL_Pos                  0                      /*!<  */

/* Bit field masks: */
#define TMR16_CLKDIV_VAL_Msk                  0x0000FFFFUL           /*!<  */

/*--  PERIOD: Timer period register ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!<  */
} _TMR16_PERIOD_bits;

/* Bit field positions: */
#define TMR16_PERIOD_VAL_Pos                  0                      /*!<  */

/* Bit field masks: */
#define TMR16_PERIOD_VAL_Msk                  0x0000FFFFUL           /*!<  */

/*--  IM: Interrupt mask register -----------------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer Interrupt Enable */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 Interrupt Enable */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 Interrupt Enable */
} _TMR16_IM_bits;

/* Bit field positions: */
#define TMR16_IM_TMR_Pos                      0                      /*!< Timer Interrupt Enable */
#define TMR16_IM_CAPCOM0_0_Pos                1                      /*!< Capcom0 Interrupt Enable */
#define TMR16_IM_CAPCOM0_1_Pos                2                      /*!< Capcom1 Interrupt Enable */

/* Bit field masks: */
#define TMR16_IM_TMR_Msk                      0x00000001UL           /*!< Timer Interrupt Enable */
#define TMR16_IM_CAPCOM0_0_Msk                0x00000002UL           /*!< Capcom0 Interrupt Enable */
#define TMR16_IM_CAPCOM0_1_Msk                0x00000004UL           /*!< Capcom1 Interrupt Enable */

/*--  RIS: Raw Interrupt Status register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer Interrupt Status */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 Interrupt Status */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 Interrupt Status */
} _TMR16_RIS_bits;

/* Bit field positions: */
#define TMR16_RIS_TMR_Pos                     0                      /*!< Timer Interrupt Status */
#define TMR16_RIS_CAPCOM0_0_Pos               1                      /*!< Capcom0 Interrupt Status */
#define TMR16_RIS_CAPCOM0_1_Pos               2                      /*!< Capcom1 Interrupt Status */

/* Bit field masks: */
#define TMR16_RIS_TMR_Msk                     0x00000001UL           /*!< Timer Interrupt Status */
#define TMR16_RIS_CAPCOM0_0_Msk               0x00000002UL           /*!< Capcom0 Interrupt Status */
#define TMR16_RIS_CAPCOM0_1_Msk               0x00000004UL           /*!< Capcom1 Interrupt Status */

/*--  MIS: Masked Interrupt Status register -------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer Interrupt Status */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 Interrupt Status */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 Interrupt Status */
} _TMR16_MIS_bits;

/* Bit field positions: */
#define TMR16_MIS_TMR_Pos                     0                      /*!< Timer Interrupt Status */
#define TMR16_MIS_CAPCOM0_0_Pos               1                      /*!< Capcom0 Interrupt Status */
#define TMR16_MIS_CAPCOM0_1_Pos               2                      /*!< Capcom1 Interrupt Status */

/* Bit field masks: */
#define TMR16_MIS_TMR_Msk                     0x00000001UL           /*!< Timer Interrupt Status */
#define TMR16_MIS_CAPCOM0_0_Msk               0x00000002UL           /*!< Capcom0 Interrupt Status */
#define TMR16_MIS_CAPCOM0_1_Msk               0x00000004UL           /*!< Capcom1 Interrupt Status */

/*--  IC: Clear Interrupt Status register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer Interrupt Clear */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 Interrupt Clear */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 Interrupt Clear */
} _TMR16_IC_bits;

/* Bit field positions: */
#define TMR16_IC_TMR_Pos                      0                      /*!< Timer Interrupt Clear */
#define TMR16_IC_CAPCOM0_0_Pos                1                      /*!< Capcom0 Interrupt Clear */
#define TMR16_IC_CAPCOM0_1_Pos                2                      /*!< Capcom1 Interrupt Clear */

/* Bit field masks: */
#define TMR16_IC_TMR_Msk                      0x00000001UL           /*!< Timer Interrupt Clear */
#define TMR16_IC_CAPCOM0_0_Msk                0x00000002UL           /*!< Capcom0 Interrupt Clear */
#define TMR16_IC_CAPCOM0_1_Msk                0x00000004UL           /*!< Capcom1 Interrupt Clear */

/*--  DMA_TXIM: DMA TX request mask register ------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer DMA TX Request Enable */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 DMA TX Request Enable */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 DMA TX Request Enable */
} _TMR16_DMA_TXIM_bits;

/* Bit field positions: */
#define TMR16_DMA_TXIM_TMR_Pos                0                      /*!< Timer DMA TX Request Enable */
#define TMR16_DMA_TXIM_CAPCOM0_0_Pos          1                      /*!< Capcom0 DMA TX Request Enable */
#define TMR16_DMA_TXIM_CAPCOM0_1_Pos          2                      /*!< Capcom1 DMA TX Request Enable */

/* Bit field masks: */
#define TMR16_DMA_TXIM_TMR_Msk                0x00000001UL           /*!< Timer DMA TX Request Enable */
#define TMR16_DMA_TXIM_CAPCOM0_0_Msk          0x00000002UL           /*!< Capcom0 DMA TX Request Enable */
#define TMR16_DMA_TXIM_CAPCOM0_1_Msk          0x00000004UL           /*!< Capcom1 DMA TX Request Enable */

/*--  DMA_RXIM: DMA RX request mask register ------------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer DMA RX Request Enable */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 DMA RX Request Enable */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 DMA RX Request Enable */
} _TMR16_DMA_RXIM_bits;

/* Bit field positions: */
#define TMR16_DMA_RXIM_TMR_Pos                0                      /*!< Timer DMA RX Request Enable */
#define TMR16_DMA_RXIM_CAPCOM0_0_Pos          1                      /*!< Capcom0 DMA RX Request Enable */
#define TMR16_DMA_RXIM_CAPCOM0_1_Pos          2                      /*!< Capcom1 DMA RX Request Enable */

/* Bit field masks: */
#define TMR16_DMA_RXIM_TMR_Msk                0x00000001UL           /*!< Timer DMA RX Request Enable */
#define TMR16_DMA_RXIM_CAPCOM0_0_Msk          0x00000002UL           /*!< Capcom0 DMA RX Request Enable */
#define TMR16_DMA_RXIM_CAPCOM0_1_Msk          0x00000004UL           /*!< Capcom1 DMA RX Request Enable */

/*--  EXTEVT_IM: External Event mask register -----------------------------------------------------------------*/
typedef struct {
  uint32_t TMR                    :1;                                /*!< Timer External Event Request Enable */
  uint32_t CAPCOM0_0              :1;                                /*!< Capcom0 External Event Request Enable */
  uint32_t CAPCOM0_1              :1;                                /*!< Capcom1 External Event Request Enable */
} _TMR16_EXTEVT_IM_bits;

/* Bit field positions: */
#define TMR16_EXTEVT_IM_TMR_Pos               0                      /*!< Timer External Event Request Enable */
#define TMR16_EXTEVT_IM_CAPCOM0_0_Pos         1                      /*!< Capcom0 External Event Request Enable */
#define TMR16_EXTEVT_IM_CAPCOM0_1_Pos         2                      /*!< Capcom1 External Event Request Enable */

/* Bit field masks: */
#define TMR16_EXTEVT_IM_TMR_Msk               0x00000001UL           /*!< Timer External Event Request Enable */
#define TMR16_EXTEVT_IM_CAPCOM0_0_Msk         0x00000002UL           /*!< Capcom0 External Event Request Enable */
#define TMR16_EXTEVT_IM_CAPCOM0_1_Msk         0x00000004UL           /*!< Capcom1 External Event Request Enable */

/*-- CAPCOM: CTRL: Capture / Compare Control register ---------------------------------------------------------*/
typedef struct {
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t OVF                    :1;                                /*!< Capture Overflow */
  uint32_t OUT                    :1;                                /*!< Output */
  uint32_t CCI                    :1;                                /*!< Capture / Compare Input */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t OUTMODE                :3;                                /*!< Output Mode */
  uint32_t CAP                    :1;                                /*!< Capture Mode */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t SCCI                   :1;                                /*!< Synchronized Capture / Compare Input */
  uint32_t                        :1;                                /*!< RESERVED */
  uint32_t CCISEL                 :2;                                /*!< Capture / Compare Input Select */
  uint32_t CAPMODE                :2;                                /*!< Capture Mode */
} _TMR16_CAPCOM_CTRL_bits;

/* Bit field positions: */
#define TMR16_CAPCOM_CTRL_OVF_Pos             1                      /*!< Capture Overflow */
#define TMR16_CAPCOM_CTRL_OUT_Pos             2                      /*!< Output */
#define TMR16_CAPCOM_CTRL_CCI_Pos             3                      /*!< Capture / Compare Input */
#define TMR16_CAPCOM_CTRL_OUTMODE_Pos         5                      /*!< Output Mode */
#define TMR16_CAPCOM_CTRL_CAP_Pos             8                      /*!< Capture Mode */
#define TMR16_CAPCOM_CTRL_SCCI_Pos            10                     /*!< Synchronized Capture / Compare Input */
#define TMR16_CAPCOM_CTRL_CCISEL_Pos          12                     /*!< Capture / Compare Input Select */
#define TMR16_CAPCOM_CTRL_CAPMODE_Pos         14                     /*!< Capture Mode */

/* Bit field masks: */
#define TMR16_CAPCOM_CTRL_OVF_Msk             0x00000002UL           /*!< Capture Overflow */
#define TMR16_CAPCOM_CTRL_OUT_Msk             0x00000004UL           /*!< Output */
#define TMR16_CAPCOM_CTRL_CCI_Msk             0x00000008UL           /*!< Capture / Compare Input */
#define TMR16_CAPCOM_CTRL_OUTMODE_Msk         0x000000E0UL           /*!< Output Mode */
#define TMR16_CAPCOM_CTRL_CAP_Msk             0x00000100UL           /*!< Capture Mode */
#define TMR16_CAPCOM_CTRL_SCCI_Msk            0x00000400UL           /*!< Synchronized Capture / Compare Input */
#define TMR16_CAPCOM_CTRL_CCISEL_Msk          0x00003000UL           /*!< Capture / Compare Input Select */
#define TMR16_CAPCOM_CTRL_CAPMODE_Msk         0x0000C000UL           /*!< Capture Mode */

/* Bit field enums: */
typedef enum {
  TMR16_CAPCOM_CTRL_OUTMODE_Out              = 0x0UL,                /*!< Out bit value */
  TMR16_CAPCOM_CTRL_OUTMODE_Set              = 0x1UL,                /*!< Set output when COUNT = CAPCOM_i.VAL */
  TMR16_CAPCOM_CTRL_OUTMODE_ToggleReset      = 0x2UL,                /*!< Toggle output when COUNT = CAPCOM_i.VAL, reset output when COUNT = CAPCOM_0.VAL */
  TMR16_CAPCOM_CTRL_OUTMODE_SetReset         = 0x3UL,                /*!< Set output when COUNT = CAPCOM_i.VAL, reset output when COUNT = CAPCOM_0.VAL */
  TMR16_CAPCOM_CTRL_OUTMODE_Toggle           = 0x4UL,                /*!< Toggle output when COUNT = CAPCOM_i.VAL */
  TMR16_CAPCOM_CTRL_OUTMODE_Reset            = 0x5UL,                /*!< Reset output when COUNT = CAPCOM_i.VAL */
  TMR16_CAPCOM_CTRL_OUTMODE_ToggleSet        = 0x6UL,                /*!< Toggle output when COUNT = CAPCOM_i.VAL, set output when COUNT = CAPCOM_0.VAL */
  TMR16_CAPCOM_CTRL_OUTMODE_ResetSet         = 0x7UL,                /*!< Reset output when COUNT = CAPCOM_i.VAL, set output when COUNT = CAPCOM_0.VAL */
} TMR16_CAPCOM_CTRL_OUTMODE_Enum;

typedef enum {
  TMR16_CAPCOM_CTRL_CAP_Compare              = 0x0UL,                /*!< Compare mode */
  TMR16_CAPCOM_CTRL_CAP_Capture              = 0x1UL,                /*!< Capture mode */
} TMR16_CAPCOM_CTRL_CAP_Enum;

typedef enum {
  TMR16_CAPCOM_CTRL_CCISEL_CCIA              = 0x0UL,                /*!< Capture/Compare input A */
  TMR16_CAPCOM_CTRL_CCISEL_CCIB              = 0x1UL,                /*!< Capture/Compare input B */
  TMR16_CAPCOM_CTRL_CCISEL_Low               = 0x2UL,                /*!< Constant 0 */
  TMR16_CAPCOM_CTRL_CCISEL_High              = 0x3UL,                /*!< Constant 1 */
} TMR16_CAPCOM_CTRL_CCISEL_Enum;

typedef enum {
  TMR16_CAPCOM_CTRL_CAPMODE_NoCapture        = 0x0UL,                /*!< No capture */
  TMR16_CAPCOM_CTRL_CAPMODE_RisingEdge       = 0x1UL,                /*!< Capture on rising edge */
  TMR16_CAPCOM_CTRL_CAPMODE_FallingEdge      = 0x2UL,                /*!< Capture on falling edge */
  TMR16_CAPCOM_CTRL_CAPMODE_BothEdges        = 0x3UL,                /*!< Capture on both rising and falling edges */
} TMR16_CAPCOM_CTRL_CAPMODE_Enum;

/*-- CAPCOM: VAL0: Capture/Compare Value 0 register -----------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!<  */
} _TMR16_CAPCOM_VAL0_bits;

/* Bit field positions: */
#define TMR16_CAPCOM_VAL0_VAL_Pos             0                      /*!<  */

/* Bit field masks: */
#define TMR16_CAPCOM_VAL0_VAL_Msk             0x0000FFFFUL           /*!<  */

/*-- CAPCOM: VAL1: Capture/Compare Value 1 register -----------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :16;                               /*!<  */
} _TMR16_CAPCOM_VAL1_bits;

/* Bit field positions: */
#define TMR16_CAPCOM_VAL1_VAL_Pos             0                      /*!<  */

/* Bit field masks: */
#define TMR16_CAPCOM_VAL1_VAL_Msk             0x0000FFFFUL           /*!<  */

//Cluster CAPCOM:
typedef struct {
  union {
  /*!< Capture / Compare Control register */
    __IO uint32_t CTRL;                                              /*!< CTRL : type used for word access */
    __IO _TMR16_CAPCOM_CTRL_bits CTRL_bit;                           /*!< CTRL_bit: structure used for bit access */
  };
  union {
  /*!< Capture/Compare Value 0 register */
    __IO uint32_t VAL0;                                              /*!< VAL0 : type used for word access */
    __IO _TMR16_CAPCOM_VAL0_bits VAL0_bit;                           /*!< VAL0_bit: structure used for bit access */
  };
  union {
  /*!< Capture/Compare Value 1 register */
    __IO uint32_t VAL1;                                              /*!< VAL1 : type used for word access */
    __IO _TMR16_CAPCOM_VAL1_bits VAL1_bit;                           /*!< VAL1_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0;
} _TMR16_CAPCOM_TypeDef;
typedef struct {
  union {                                                            /*!< Timer control register */
    __IO uint32_t CTRL;                                              /*!< CTRL    : type used for word access */
    __IO _TMR16_CTRL_bits  CTRL_bit;                                 /*!< CTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< Current value timer register */
    __IO uint32_t COUNT;                                             /*!< COUNT    : type used for word access */
    __IO _TMR16_COUNT_bits  COUNT_bit;                               /*!< COUNT_bit: structure used for bit access */
  };
  union {                                                            /*!< Clock divider register */
    __IO uint32_t CLKDIV;                                            /*!< CLKDIV    : type used for word access */
    __IO _TMR16_CLKDIV_bits  CLKDIV_bit;                             /*!< CLKDIV_bit: structure used for bit access */
  };
  union {                                                            /*!< Timer period register */
    __IO uint32_t PERIOD;                                            /*!< PERIOD    : type used for word access */
    __IO _TMR16_PERIOD_bits  PERIOD_bit;                             /*!< PERIOD_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt mask register */
    __IO uint32_t IM;                                                /*!< IM    : type used for word access */
    __IO _TMR16_IM_bits  IM_bit;                                     /*!< IM_bit: structure used for bit access */
  };
  union {                                                            /*!< Raw Interrupt Status register */
    __I uint32_t RIS;                                                /*!< RIS    : type used for word access */
    __I _TMR16_RIS_bits  RIS_bit;                                    /*!< RIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Masked Interrupt Status register */
    __I uint32_t MIS;                                                /*!< MIS    : type used for word access */
    __I _TMR16_MIS_bits  MIS_bit;                                    /*!< MIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Clear Interrupt Status register */
    __O uint32_t IC;                                                 /*!< IC    : type used for word access */
    __O _TMR16_IC_bits  IC_bit;                                      /*!< IC_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA TX request mask register */
    __IO uint32_t DMA_TXIM;                                           /*!< DMA_TXIM    : type used for word access */
    __IO _TMR16_DMA_TXIM_bits  DMA_TXIM_bit;                         /*!< DMA_TXIM_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA RX request mask register */
    __IO uint32_t DMA_RXIM;                                           /*!< DMA_RXIM    : type used for word access */
    __IO _TMR16_DMA_RXIM_bits  DMA_RXIM_bit;                         /*!< DMA_RXIM_bit: structure used for bit access */
  };
  union {                                                            /*!< External Event mask register */
    __IO uint32_t EXTEVT_IM;                                           /*!< EXTEVT_IM    : type used for word access */
    __IO _TMR16_EXTEVT_IM_bits  EXTEVT_IM_bit;                       /*!< EXTEVT_IM_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0[53];
  _TMR16_CAPCOM_TypeDef CAPCOM[2];
} TMR16_TypeDef;


/******************************************************************************/
/*                         UART registers                                     */
/******************************************************************************/

/*--  DR: Data Register ---------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t DATA                   :8;                                /*!< Received/Transmitted data character */
  uint32_t FE                     :1;                                /*!< Framing error */
  uint32_t PE                     :1;                                /*!< Parity error */
  uint32_t BE                     :1;                                /*!< Break error */
  uint32_t OE                     :1;                                /*!< Overrun error */
} _UART_DR_bits;

/* Bit field positions: */
#define UART_DR_DATA_Pos                      0                      /*!< Received/Transmitted data character */
#define UART_DR_FE_Pos                        8                      /*!< Framing error */
#define UART_DR_PE_Pos                        9                      /*!< Parity error */
#define UART_DR_BE_Pos                        10                     /*!< Break error */
#define UART_DR_OE_Pos                        11                     /*!< Overrun error */

/* Bit field masks: */
#define UART_DR_DATA_Msk                      0x000000FFUL           /*!< Received/Transmitted data character */
#define UART_DR_FE_Msk                        0x00000100UL           /*!< Framing error */
#define UART_DR_PE_Msk                        0x00000200UL           /*!< Parity error */
#define UART_DR_BE_Msk                        0x00000400UL           /*!< Break error */
#define UART_DR_OE_Msk                        0x00000800UL           /*!< Overrun error */

/*--  RSR: Receive Status Register/Error Clear Register -------------------------------------------------------*/
typedef struct {
  uint32_t FE                     :1;                                /*!< Framing error */
  uint32_t PE                     :1;                                /*!< Parity error */
  uint32_t BE                     :1;                                /*!< Break error */
  uint32_t OE                     :1;                                /*!< Overrun error */
} _UART_RSR_bits;

/* Bit field positions: */
#define UART_RSR_FE_Pos                       0                      /*!< Framing error */
#define UART_RSR_PE_Pos                       1                      /*!< Parity error */
#define UART_RSR_BE_Pos                       2                      /*!< Break error */
#define UART_RSR_OE_Pos                       3                      /*!< Overrun error */

/* Bit field masks: */
#define UART_RSR_FE_Msk                       0x00000001UL           /*!< Framing error */
#define UART_RSR_PE_Msk                       0x00000002UL           /*!< Parity error */
#define UART_RSR_BE_Msk                       0x00000004UL           /*!< Break error */
#define UART_RSR_OE_Msk                       0x00000008UL           /*!< Overrun error */

/*--  FR: Flag Register ---------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t CTS                    :1;                                /*!< Clear to send */
  uint32_t DSR                    :1;                                /*!< Data set ready */
  uint32_t DCD                    :1;                                /*!< Data carrier detect */
  uint32_t BUSY                   :1;                                /*!< UART busy */
  uint32_t RXFE                   :1;                                /*!< Receive FIFO empty */
  uint32_t TXFF                   :1;                                /*!< Transmit FIFO full */
  uint32_t RXFF                   :1;                                /*!< Receive FIFO full */
  uint32_t TXFE                   :1;                                /*!< Transmit FIFO empty */
  uint32_t RI                     :1;                                /*!< Ring indicator */
} _UART_FR_bits;

/* Bit field positions: */
#define UART_FR_CTS_Pos                       0                      /*!< Clear to send */
#define UART_FR_DSR_Pos                       1                      /*!< Data set ready */
#define UART_FR_DCD_Pos                       2                      /*!< Data carrier detect */
#define UART_FR_BUSY_Pos                      3                      /*!< UART busy */
#define UART_FR_RXFE_Pos                      4                      /*!< Receive FIFO empty */
#define UART_FR_TXFF_Pos                      5                      /*!< Transmit FIFO full */
#define UART_FR_RXFF_Pos                      6                      /*!< Receive FIFO full */
#define UART_FR_TXFE_Pos                      7                      /*!< Transmit FIFO empty */
#define UART_FR_RI_Pos                        8                      /*!< Ring indicator */

/* Bit field masks: */
#define UART_FR_CTS_Msk                       0x00000001UL           /*!< Clear to send */
#define UART_FR_DSR_Msk                       0x00000002UL           /*!< Data set ready */
#define UART_FR_DCD_Msk                       0x00000004UL           /*!< Data carrier detect */
#define UART_FR_BUSY_Msk                      0x00000008UL           /*!< UART busy */
#define UART_FR_RXFE_Msk                      0x00000010UL           /*!< Receive FIFO empty */
#define UART_FR_TXFF_Msk                      0x00000020UL           /*!< Transmit FIFO full */
#define UART_FR_RXFF_Msk                      0x00000040UL           /*!< Receive FIFO full */
#define UART_FR_TXFE_Msk                      0x00000080UL           /*!< Transmit FIFO empty */
#define UART_FR_RI_Msk                        0x00000100UL           /*!< Ring indicator */

/*--  ILPR: IrDA Low-Power Counter Register -------------------------------------------------------------------*/
typedef struct {
  uint32_t ILPDVSR                :8;                                /*!< 8-bit low-power divisor value */
} _UART_ILPR_bits;

/* Bit field positions: */
#define UART_ILPR_ILPDVSR_Pos                 0                      /*!< 8-bit low-power divisor value */

/* Bit field masks: */
#define UART_ILPR_ILPDVSR_Msk                 0x000000FFUL           /*!< 8-bit low-power divisor value */

/*--  IBRD: Integer Baud Rate Register ------------------------------------------------------------------------*/
typedef struct {
  uint32_t DIVINT                 :16;                               /*!< The integer baud rate divisor */
} _UART_IBRD_bits;

/* Bit field positions: */
#define UART_IBRD_DIVINT_Pos                  0                      /*!< The integer baud rate divisor */

/* Bit field masks: */
#define UART_IBRD_DIVINT_Msk                  0x0000FFFFUL           /*!< The integer baud rate divisor */

/*--  FBRD: Fractional Baud Rate Register ---------------------------------------------------------------------*/
typedef struct {
  uint32_t DIVFRAC                :6;                                /*!< The fractional baud rate divisor */
} _UART_FBRD_bits;

/* Bit field positions: */
#define UART_FBRD_DIVFRAC_Pos                 0                      /*!< The fractional baud rate divisor */

/* Bit field masks: */
#define UART_FBRD_DIVFRAC_Msk                 0x0000003FUL           /*!< The fractional baud rate divisor */

/*--  LCRH: Line Control Register -----------------------------------------------------------------------------*/
typedef struct {
  uint32_t BRK                    :1;                                /*!< Send break */
  uint32_t PEN                    :1;                                /*!< Parity enable */
  uint32_t EPS                    :1;                                /*!< Even parity select */
  uint32_t STP2                   :1;                                /*!< Two stop bits select */
  uint32_t FEN                    :1;                                /*!< Enable FIFOs */
  uint32_t WLEN                   :2;                                /*!< Word length */
  uint32_t SPS                    :1;                                /*!< Stick parity select */
} _UART_LCRH_bits;

/* Bit field positions: */
#define UART_LCRH_BRK_Pos                     0                      /*!< Send break */
#define UART_LCRH_PEN_Pos                     1                      /*!< Parity enable */
#define UART_LCRH_EPS_Pos                     2                      /*!< Even parity select */
#define UART_LCRH_STP2_Pos                    3                      /*!< Two stop bits select */
#define UART_LCRH_FEN_Pos                     4                      /*!< Enable FIFOs */
#define UART_LCRH_WLEN_Pos                    5                      /*!< Word length */
#define UART_LCRH_SPS_Pos                     7                      /*!< Stick parity select */

/* Bit field masks: */
#define UART_LCRH_BRK_Msk                     0x00000001UL           /*!< Send break */
#define UART_LCRH_PEN_Msk                     0x00000002UL           /*!< Parity enable */
#define UART_LCRH_EPS_Msk                     0x00000004UL           /*!< Even parity select */
#define UART_LCRH_STP2_Msk                    0x00000008UL           /*!< Two stop bits select */
#define UART_LCRH_FEN_Msk                     0x00000010UL           /*!< Enable FIFOs */
#define UART_LCRH_WLEN_Msk                    0x00000060UL           /*!< Word length */
#define UART_LCRH_SPS_Msk                     0x00000080UL           /*!< Stick parity select */

/* Bit field enums: */
typedef enum {
  UART_LCRH_WLEN_5bit                        = 0x0UL,                /*!< 5 bit in informational word */
  UART_LCRH_WLEN_6bit                        = 0x1UL,                /*!< 6 bit in informational word */
  UART_LCRH_WLEN_7bit                        = 0x2UL,                /*!< 7 bit in informational word */
  UART_LCRH_WLEN_8bit                        = 0x3UL,                /*!< 8 bit in informational word */
} UART_LCRH_WLEN_Enum;

/*--  CR: Control Register ------------------------------------------------------------------------------------*/
typedef struct {
  uint32_t UARTEN                 :1;                                /*!< UART enable */
  uint32_t SIREN                  :1;                                /*!< Enable IrDA SIR ENDEC */
  uint32_t SIRLP                  :1;                                /*!< Enable SIR low-power IrDA mode */
  uint32_t                        :4;                                /*!< RESERVED */
  uint32_t LBE                    :1;                                /*!< Loopback enable */
  uint32_t TXE                    :1;                                /*!< Transmit enable */
  uint32_t RXE                    :1;                                /*!< Receive enable */
  uint32_t DTR                    :1;                                /*!< Data transmit ready */
  uint32_t RTS                    :1;                                /*!< Request to send */
  uint32_t                        :2;                                /*!< RESERVED */
  uint32_t RTSEN                  :1;                                /*!< RTS hardware flow control enable */
  uint32_t CTSEN                  :1;                                /*!< CTS hardware flow control enable */
} _UART_CR_bits;

/* Bit field positions: */
#define UART_CR_UARTEN_Pos                    0                      /*!< UART enable */
#define UART_CR_SIREN_Pos                     1                      /*!< Enable IrDA SIR ENDEC */
#define UART_CR_SIRLP_Pos                     2                      /*!< Enable SIR low-power IrDA mode */
#define UART_CR_LBE_Pos                       7                      /*!< Loopback enable */
#define UART_CR_TXE_Pos                       8                      /*!< Transmit enable */
#define UART_CR_RXE_Pos                       9                      /*!< Receive enable */
#define UART_CR_DTR_Pos                       10                     /*!< Data transmit ready */
#define UART_CR_RTS_Pos                       11                     /*!< Request to send */
#define UART_CR_RTSEN_Pos                     14                     /*!< RTS hardware flow control enable */
#define UART_CR_CTSEN_Pos                     15                     /*!< CTS hardware flow control enable */

/* Bit field masks: */
#define UART_CR_UARTEN_Msk                    0x00000001UL           /*!< UART enable */
#define UART_CR_SIREN_Msk                     0x00000002UL           /*!< Enable IrDA SIR ENDEC */
#define UART_CR_SIRLP_Msk                     0x00000004UL           /*!< Enable SIR low-power IrDA mode */
#define UART_CR_LBE_Msk                       0x00000080UL           /*!< Loopback enable */
#define UART_CR_TXE_Msk                       0x00000100UL           /*!< Transmit enable */
#define UART_CR_RXE_Msk                       0x00000200UL           /*!< Receive enable */
#define UART_CR_DTR_Msk                       0x00000400UL           /*!< Data transmit ready */
#define UART_CR_RTS_Msk                       0x00000800UL           /*!< Request to send */
#define UART_CR_RTSEN_Msk                     0x00004000UL           /*!< RTS hardware flow control enable */
#define UART_CR_CTSEN_Msk                     0x00008000UL           /*!< CTS hardware flow control enable */

/*--  IFLS: Interrupt FIFO Level Select Register --------------------------------------------------------------*/
typedef struct {
  uint32_t TXIFLSEL               :6;                                /*!< Transmit interrupt FIFO level select */
  uint32_t RXIFLSEL               :6;                                /*!< Receive interrupt FIFO level select */
} _UART_IFLS_bits;

/* Bit field positions: */
#define UART_IFLS_TXIFLSEL_Pos                0                      /*!< Transmit interrupt FIFO level select */
#define UART_IFLS_RXIFLSEL_Pos                6                      /*!< Receive interrupt FIFO level select */

/* Bit field masks: */
#define UART_IFLS_TXIFLSEL_Msk                0x0000003FUL           /*!< Transmit interrupt FIFO level select */
#define UART_IFLS_RXIFLSEL_Msk                0x00000FC0UL           /*!< Receive interrupt FIFO level select */

/* Bit field enums: */
typedef enum {
  UART_IFLS_TXIFLSEL_LVL18                   = 0x4UL,                /*!< interrupt on 1/8 */
  UART_IFLS_TXIFLSEL_LVL14                   = 0x8UL,                /*!< interrupt on 1/4 */
  UART_IFLS_TXIFLSEL_LVL12                   = 0x10UL,               /*!< interrupt on 1/2 */
  UART_IFLS_TXIFLSEL_LVL34                   = 0x18UL,               /*!< interrupt on 3/4 */
  UART_IFLS_TXIFLSEL_LVL78                   = 0x1CUL,               /*!< interrupt on 7/8 */
  UART_IFLS_TXIFLSEL_LVL88                   = 0x20UL,               /*!< interrupt on full fifo */
} UART_IFLS_TXIFLSEL_Enum;

typedef enum {
  UART_IFLS_RXIFLSEL_LVL18                   = 0x4UL,                /*!< interrupt on 1/8 */
  UART_IFLS_RXIFLSEL_LVL14                   = 0x8UL,                /*!< interrupt on 1/4 */
  UART_IFLS_RXIFLSEL_LVL12                   = 0x10UL,               /*!< interrupt on 1/2 */
  UART_IFLS_RXIFLSEL_LVL34                   = 0x18UL,               /*!< interrupt on 3/4 */
  UART_IFLS_RXIFLSEL_LVL78                   = 0x1CUL,               /*!< interrupt on 7/8 */
  UART_IFLS_RXIFLSEL_LVL88                   = 0x20UL,               /*!< interrupt on full fifo */
} UART_IFLS_RXIFLSEL_Enum;

/*--  IMSC: Interrupt Mask Set/Clear Register -----------------------------------------------------------------*/
typedef struct {
  uint32_t RIMIM                  :1;                                /*!< nUARTRI modem interrupt mask */
  uint32_t CTSMIM                 :1;                                /*!< nUARTCTS modem interrupt mask */
  uint32_t DCDMIM                 :1;                                /*!< nUARTDCD modem interrupt mask */
  uint32_t DSRMIM                 :1;                                /*!< nUARTDSR modem interrupt mask */
  uint32_t RXIM                   :1;                                /*!< Receive interrupt mask */
  uint32_t TXIM                   :1;                                /*!< Transmit interrupt mask */
  uint32_t RTIM                   :1;                                /*!< Receive timeout interrupt mask */
  uint32_t FERIM                  :1;                                /*!< Framing error interrupt mask */
  uint32_t PERIM                  :1;                                /*!< Parity error interrupt mask */
  uint32_t BERIM                  :1;                                /*!< Break error interrupt mask */
  uint32_t OERIM                  :1;                                /*!< Overrun error interrupt mask */
  uint32_t TDIM                   :1;                                /*!< Transmit done interrupt mask */
} _UART_IMSC_bits;

/* Bit field positions: */
#define UART_IMSC_RIMIM_Pos                   0                      /*!< nUARTRI modem interrupt mask */
#define UART_IMSC_CTSMIM_Pos                  1                      /*!< nUARTCTS modem interrupt mask */
#define UART_IMSC_DCDMIM_Pos                  2                      /*!< nUARTDCD modem interrupt mask */
#define UART_IMSC_DSRMIM_Pos                  3                      /*!< nUARTDSR modem interrupt mask */
#define UART_IMSC_RXIM_Pos                    4                      /*!< Receive interrupt mask */
#define UART_IMSC_TXIM_Pos                    5                      /*!< Transmit interrupt mask */
#define UART_IMSC_RTIM_Pos                    6                      /*!< Receive timeout interrupt mask */
#define UART_IMSC_FERIM_Pos                   7                      /*!< Framing error interrupt mask */
#define UART_IMSC_PERIM_Pos                   8                      /*!< Parity error interrupt mask */
#define UART_IMSC_BERIM_Pos                   9                      /*!< Break error interrupt mask */
#define UART_IMSC_OERIM_Pos                   10                     /*!< Overrun error interrupt mask */
#define UART_IMSC_TDIM_Pos                    11                     /*!< Transmit done interrupt mask */

/* Bit field masks: */
#define UART_IMSC_RIMIM_Msk                   0x00000001UL           /*!< nUARTRI modem interrupt mask */
#define UART_IMSC_CTSMIM_Msk                  0x00000002UL           /*!< nUARTCTS modem interrupt mask */
#define UART_IMSC_DCDMIM_Msk                  0x00000004UL           /*!< nUARTDCD modem interrupt mask */
#define UART_IMSC_DSRMIM_Msk                  0x00000008UL           /*!< nUARTDSR modem interrupt mask */
#define UART_IMSC_RXIM_Msk                    0x00000010UL           /*!< Receive interrupt mask */
#define UART_IMSC_TXIM_Msk                    0x00000020UL           /*!< Transmit interrupt mask */
#define UART_IMSC_RTIM_Msk                    0x00000040UL           /*!< Receive timeout interrupt mask */
#define UART_IMSC_FERIM_Msk                   0x00000080UL           /*!< Framing error interrupt mask */
#define UART_IMSC_PERIM_Msk                   0x00000100UL           /*!< Parity error interrupt mask */
#define UART_IMSC_BERIM_Msk                   0x00000200UL           /*!< Break error interrupt mask */
#define UART_IMSC_OERIM_Msk                   0x00000400UL           /*!< Overrun error interrupt mask */
#define UART_IMSC_TDIM_Msk                    0x00000800UL           /*!< Transmit done interrupt mask */

/*--  RIS: Raw Interrupt Status Register ----------------------------------------------------------------------*/
typedef struct {
  uint32_t RIRMIS                 :1;                                /*!< nUARTRI modem interrupt status */
  uint32_t CTSRMIS                :1;                                /*!< nUARTCTS modem interrupt status */
  uint32_t DCDRMIS                :1;                                /*!< nUARTDCD modem interrupt status */
  uint32_t DSRRMIS                :1;                                /*!< nUARTDSR modem interrupt status */
  uint32_t RXRIS                  :1;                                /*!< Receive interrupt status */
  uint32_t TXRIS                  :1;                                /*!< Transmit interrupt status */
  uint32_t RTRIS                  :1;                                /*!< Receive timeout interrupt status */
  uint32_t FERIS                  :1;                                /*!< Framing error interrupt status */
  uint32_t PERIS                  :1;                                /*!< Parity error interrupt status */
  uint32_t BERIS                  :1;                                /*!< Break error interrupt status */
  uint32_t OERIS                  :1;                                /*!< Overrun error interrupt status */
  uint32_t TDRIS                  :1;                                /*!< Transmit done raw interrupt status */
} _UART_RIS_bits;

/* Bit field positions: */
#define UART_RIS_RIRMIS_Pos                   0                      /*!< nUARTRI modem interrupt status */
#define UART_RIS_CTSRMIS_Pos                  1                      /*!< nUARTCTS modem interrupt status */
#define UART_RIS_DCDRMIS_Pos                  2                      /*!< nUARTDCD modem interrupt status */
#define UART_RIS_DSRRMIS_Pos                  3                      /*!< nUARTDSR modem interrupt status */
#define UART_RIS_RXRIS_Pos                    4                      /*!< Receive interrupt status */
#define UART_RIS_TXRIS_Pos                    5                      /*!< Transmit interrupt status */
#define UART_RIS_RTRIS_Pos                    6                      /*!< Receive timeout interrupt status */
#define UART_RIS_FERIS_Pos                    7                      /*!< Framing error interrupt status */
#define UART_RIS_PERIS_Pos                    8                      /*!< Parity error interrupt status */
#define UART_RIS_BERIS_Pos                    9                      /*!< Break error interrupt status */
#define UART_RIS_OERIS_Pos                    10                     /*!< Overrun error interrupt status */
#define UART_RIS_TDRIS_Pos                    11                     /*!< Transmit done raw interrupt status */

/* Bit field masks: */
#define UART_RIS_RIRMIS_Msk                   0x00000001UL           /*!< nUARTRI modem interrupt status */
#define UART_RIS_CTSRMIS_Msk                  0x00000002UL           /*!< nUARTCTS modem interrupt status */
#define UART_RIS_DCDRMIS_Msk                  0x00000004UL           /*!< nUARTDCD modem interrupt status */
#define UART_RIS_DSRRMIS_Msk                  0x00000008UL           /*!< nUARTDSR modem interrupt status */
#define UART_RIS_RXRIS_Msk                    0x00000010UL           /*!< Receive interrupt status */
#define UART_RIS_TXRIS_Msk                    0x00000020UL           /*!< Transmit interrupt status */
#define UART_RIS_RTRIS_Msk                    0x00000040UL           /*!< Receive timeout interrupt status */
#define UART_RIS_FERIS_Msk                    0x00000080UL           /*!< Framing error interrupt status */
#define UART_RIS_PERIS_Msk                    0x00000100UL           /*!< Parity error interrupt status */
#define UART_RIS_BERIS_Msk                    0x00000200UL           /*!< Break error interrupt status */
#define UART_RIS_OERIS_Msk                    0x00000400UL           /*!< Overrun error interrupt status */
#define UART_RIS_TDRIS_Msk                    0x00000800UL           /*!< Transmit done raw interrupt status */

/*--  MIS: Masked Interrupt Status Register -------------------------------------------------------------------*/
typedef struct {
  uint32_t RIMMIS                 :1;                                /*!< nUARTRI modem masked interrupt status */
  uint32_t CTSMMIS                :1;                                /*!< nUARTCTS modem masked interrupt status */
  uint32_t DCDMMIS                :1;                                /*!< nUARTDCD modem masked interrupt status */
  uint32_t DSRMMIS                :1;                                /*!< nUARTDSR modem masked interrupt status */
  uint32_t RXMIS                  :1;                                /*!< Receive masked interrupt status */
  uint32_t TXMIS                  :1;                                /*!< Transmit masked interrupt status */
  uint32_t RTMIS                  :1;                                /*!< Receive timeout masked interrupt status */
  uint32_t FEMIS                  :1;                                /*!< Framing error masked interrupt status */
  uint32_t PEMIS                  :1;                                /*!< Parity error masked interrupt status */
  uint32_t BEMIS                  :1;                                /*!< Break error masked interrupt status */
  uint32_t OEMIS                  :1;                                /*!< Overrun error masked interrupt status */
  uint32_t TDMIS                  :1;                                /*!< Transmit done masked interrupt status */
} _UART_MIS_bits;

/* Bit field positions: */
#define UART_MIS_RIMMIS_Pos                   0                      /*!< nUARTRI modem masked interrupt status */
#define UART_MIS_CTSMMIS_Pos                  1                      /*!< nUARTCTS modem masked interrupt status */
#define UART_MIS_DCDMMIS_Pos                  2                      /*!< nUARTDCD modem masked interrupt status */
#define UART_MIS_DSRMMIS_Pos                  3                      /*!< nUARTDSR modem masked interrupt status */
#define UART_MIS_RXMIS_Pos                    4                      /*!< Receive masked interrupt status */
#define UART_MIS_TXMIS_Pos                    5                      /*!< Transmit masked interrupt status */
#define UART_MIS_RTMIS_Pos                    6                      /*!< Receive timeout masked interrupt status */
#define UART_MIS_FEMIS_Pos                    7                      /*!< Framing error masked interrupt status */
#define UART_MIS_PEMIS_Pos                    8                      /*!< Parity error masked interrupt status */
#define UART_MIS_BEMIS_Pos                    9                      /*!< Break error masked interrupt status */
#define UART_MIS_OEMIS_Pos                    10                     /*!< Overrun error masked interrupt status */
#define UART_MIS_TDMIS_Pos                    11                     /*!< Transmit done masked interrupt status */

/* Bit field masks: */
#define UART_MIS_RIMMIS_Msk                   0x00000001UL           /*!< nUARTRI modem masked interrupt status */
#define UART_MIS_CTSMMIS_Msk                  0x00000002UL           /*!< nUARTCTS modem masked interrupt status */
#define UART_MIS_DCDMMIS_Msk                  0x00000004UL           /*!< nUARTDCD modem masked interrupt status */
#define UART_MIS_DSRMMIS_Msk                  0x00000008UL           /*!< nUARTDSR modem masked interrupt status */
#define UART_MIS_RXMIS_Msk                    0x00000010UL           /*!< Receive masked interrupt status */
#define UART_MIS_TXMIS_Msk                    0x00000020UL           /*!< Transmit masked interrupt status */
#define UART_MIS_RTMIS_Msk                    0x00000040UL           /*!< Receive timeout masked interrupt status */
#define UART_MIS_FEMIS_Msk                    0x00000080UL           /*!< Framing error masked interrupt status */
#define UART_MIS_PEMIS_Msk                    0x00000100UL           /*!< Parity error masked interrupt status */
#define UART_MIS_BEMIS_Msk                    0x00000200UL           /*!< Break error masked interrupt status */
#define UART_MIS_OEMIS_Msk                    0x00000400UL           /*!< Overrun error masked interrupt status */
#define UART_MIS_TDMIS_Msk                    0x00000800UL           /*!< Transmit done masked interrupt status */

/*--  ICR: Interrupt Clear Register ---------------------------------------------------------------------------*/
typedef struct {
  uint32_t RIMIC                  :1;                                /*!< nUARTRI modem interrupt clear */
  uint32_t CTSMIC                 :1;                                /*!< nUARTCTS modem interrupt clear */
  uint32_t DCDMIC                 :1;                                /*!< nUARTDCD modem interrupt clear */
  uint32_t DSRMIC                 :1;                                /*!< nUARTDSR modem interrupt clear */
  uint32_t RXIC                   :1;                                /*!< Receive interrupt clear */
  uint32_t TXIC                   :1;                                /*!< Transmit interrupt clear */
  uint32_t RTIC                   :1;                                /*!< Receive timeout interrupt clear */
  uint32_t FEIC                   :1;                                /*!< Framing error interrupt clear */
  uint32_t PEIC                   :1;                                /*!< Parity error interrupt clear */
  uint32_t BEIC                   :1;                                /*!< Break error interrupt clear */
  uint32_t OEIC                   :1;                                /*!< Overrun error interrupt clear */
  uint32_t TDIC                   :1;                                /*!< Transmit done interrupt clear */
} _UART_ICR_bits;

/* Bit field positions: */
#define UART_ICR_RIMIC_Pos                    0                      /*!< nUARTRI modem interrupt clear */
#define UART_ICR_CTSMIC_Pos                   1                      /*!< nUARTCTS modem interrupt clear */
#define UART_ICR_DCDMIC_Pos                   2                      /*!< nUARTDCD modem interrupt clear */
#define UART_ICR_DSRMIC_Pos                   3                      /*!< nUARTDSR modem interrupt clear */
#define UART_ICR_RXIC_Pos                     4                      /*!< Receive interrupt clear */
#define UART_ICR_TXIC_Pos                     5                      /*!< Transmit interrupt clear */
#define UART_ICR_RTIC_Pos                     6                      /*!< Receive timeout interrupt clear */
#define UART_ICR_FEIC_Pos                     7                      /*!< Framing error interrupt clear */
#define UART_ICR_PEIC_Pos                     8                      /*!< Parity error interrupt clear */
#define UART_ICR_BEIC_Pos                     9                      /*!< Break error interrupt clear */
#define UART_ICR_OEIC_Pos                     10                     /*!< Overrun error interrupt clear */
#define UART_ICR_TDIC_Pos                     11                     /*!< Transmit done interrupt clear */

/* Bit field masks: */
#define UART_ICR_RIMIC_Msk                    0x00000001UL           /*!< nUARTRI modem interrupt clear */
#define UART_ICR_CTSMIC_Msk                   0x00000002UL           /*!< nUARTCTS modem interrupt clear */
#define UART_ICR_DCDMIC_Msk                   0x00000004UL           /*!< nUARTDCD modem interrupt clear */
#define UART_ICR_DSRMIC_Msk                   0x00000008UL           /*!< nUARTDSR modem interrupt clear */
#define UART_ICR_RXIC_Msk                     0x00000010UL           /*!< Receive interrupt clear */
#define UART_ICR_TXIC_Msk                     0x00000020UL           /*!< Transmit interrupt clear */
#define UART_ICR_RTIC_Msk                     0x00000040UL           /*!< Receive timeout interrupt clear */
#define UART_ICR_FEIC_Msk                     0x00000080UL           /*!< Framing error interrupt clear */
#define UART_ICR_PEIC_Msk                     0x00000100UL           /*!< Parity error interrupt clear */
#define UART_ICR_BEIC_Msk                     0x00000200UL           /*!< Break error interrupt clear */
#define UART_ICR_OEIC_Msk                     0x00000400UL           /*!< Overrun error interrupt clear */
#define UART_ICR_TDIC_Msk                     0x00000800UL           /*!< Transmit done interrupt clear */

/*--  DMACR: DMA Control Register -----------------------------------------------------------------------------*/
typedef struct {
  uint32_t RXDMAE                 :1;                                /*!< Receive DMA enable */
  uint32_t TXDMAE                 :1;                                /*!< Transmit DMA enable */
  uint32_t DMAONERR               :1;                                /*!< DMA on error */
} _UART_DMACR_bits;

/* Bit field positions: */
#define UART_DMACR_RXDMAE_Pos                 0                      /*!< Receive DMA enable */
#define UART_DMACR_TXDMAE_Pos                 1                      /*!< Transmit DMA enable */
#define UART_DMACR_DMAONERR_Pos               2                      /*!< DMA on error */

/* Bit field masks: */
#define UART_DMACR_RXDMAE_Msk                 0x00000001UL           /*!< Receive DMA enable */
#define UART_DMACR_TXDMAE_Msk                 0x00000002UL           /*!< Transmit DMA enable */
#define UART_DMACR_DMAONERR_Msk               0x00000004UL           /*!< DMA on error */

typedef struct {
  union {                                                            /*!< Data Register */
    __IO uint32_t DR;                                                /*!< DR    : type used for word access */
    __IO _UART_DR_bits  DR_bit;                                      /*!< DR_bit: structure used for bit access */
  };
  union {                                                            /*!< Receive Status Register/Error Clear Register */
    __IO uint32_t RSR;                                               /*!< RSR    : type used for word access */
    __IO _UART_RSR_bits  RSR_bit;                                    /*!< RSR_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0[4];
  union {                                                            /*!< Flag Register */
    __I uint32_t FR;                                                 /*!< FR    : type used for word access */
    __I _UART_FR_bits  FR_bit;                                       /*!< FR_bit: structure used for bit access */
  };
    __IO uint32_t Reserved1;
  union {                                                            /*!< IrDA Low-Power Counter Register */
    __IO uint32_t ILPR;                                              /*!< ILPR    : type used for word access */
    __IO _UART_ILPR_bits  ILPR_bit;                                  /*!< ILPR_bit: structure used for bit access */
  };
  union {                                                            /*!< Integer Baud Rate Register */
    __IO uint32_t IBRD;                                              /*!< IBRD    : type used for word access */
    __IO _UART_IBRD_bits  IBRD_bit;                                  /*!< IBRD_bit: structure used for bit access */
  };
  union {                                                            /*!< Fractional Baud Rate Register */
    __IO uint32_t FBRD;                                              /*!< FBRD    : type used for word access */
    __IO _UART_FBRD_bits  FBRD_bit;                                  /*!< FBRD_bit: structure used for bit access */
  };
  union {                                                            /*!< Line Control Register */
    __IO uint32_t LCRH;                                              /*!< LCRH    : type used for word access */
    __IO _UART_LCRH_bits  LCRH_bit;                                  /*!< LCRH_bit: structure used for bit access */
  };
  union {                                                            /*!< Control Register */
    __IO uint32_t CR;                                                /*!< CR    : type used for word access */
    __IO _UART_CR_bits  CR_bit;                                      /*!< CR_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt FIFO Level Select Register */
    __IO uint32_t IFLS;                                              /*!< IFLS    : type used for word access */
    __IO _UART_IFLS_bits  IFLS_bit;                                  /*!< IFLS_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt Mask Set/Clear Register */
    __IO uint32_t IMSC;                                              /*!< IMSC    : type used for word access */
    __IO _UART_IMSC_bits  IMSC_bit;                                  /*!< IMSC_bit: structure used for bit access */
  };
  union {                                                            /*!< Raw Interrupt Status Register */
    __I uint32_t RIS;                                                /*!< RIS    : type used for word access */
    __I _UART_RIS_bits  RIS_bit;                                     /*!< RIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Masked Interrupt Status Register */
    __I uint32_t MIS;                                                /*!< MIS    : type used for word access */
    __I _UART_MIS_bits  MIS_bit;                                     /*!< MIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Interrupt Clear Register */
    __O uint32_t ICR;                                                /*!< ICR    : type used for word access */
    __O _UART_ICR_bits  ICR_bit;                                     /*!< ICR_bit: structure used for bit access */
  };
  union {                                                            /*!< DMA Control Register */
    __IO uint32_t DMACR;                                             /*!< DMACR    : type used for word access */
    __IO _UART_DMACR_bits  DMACR_bit;                                /*!< DMACR_bit: structure used for bit access */
  };
} UART_TypeDef;


/******************************************************************************/
/*                         WDT registers                                      */
/******************************************************************************/

/*--  LOAD: Watchdog Load Register ----------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!< Begin value counter */
} _WDT_LOAD_bits;

/* Bit field positions: */
#define WDT_LOAD_VAL_Pos                      0                      /*!< Begin value counter */

/* Bit field masks: */
#define WDT_LOAD_VAL_Msk                      0xFFFFFFFFUL           /*!< Begin value counter */

/*--  VALUE: Watchdog Value Register --------------------------------------------------------------------------*/
typedef struct {
  uint32_t VAL                    :32;                               /*!< Current value counter */
} _WDT_VALUE_bits;

/* Bit field positions: */
#define WDT_VALUE_VAL_Pos                     0                      /*!< Current value counter */

/* Bit field masks: */
#define WDT_VALUE_VAL_Msk                     0xFFFFFFFFUL           /*!< Current value counter */

/*--  CTRL: Watchdog Control Register -------------------------------------------------------------------------*/
typedef struct {
  uint32_t INTEN                  :1;                                /*!< Enable the interrupt event */
  uint32_t RESEN                  :1;                                /*!< Enable watchdog reset output */
} _WDT_CTRL_bits;

/* Bit field positions: */
#define WDT_CTRL_INTEN_Pos                    0                      /*!< Enable the interrupt event */
#define WDT_CTRL_RESEN_Pos                    1                      /*!< Enable watchdog reset output */

/* Bit field masks: */
#define WDT_CTRL_INTEN_Msk                    0x00000001UL           /*!< Enable the interrupt event */
#define WDT_CTRL_RESEN_Msk                    0x00000002UL           /*!< Enable watchdog reset output */

/*--  INTCLR: Watchdog Clear Interrupt Register ---------------------------------------------------------------*/
typedef struct {
  uint32_t WDTCLR                 :32;                               /*!< Reset interrupt WDT */
} _WDT_INTCLR_bits;

/* Bit field positions: */
#define WDT_INTCLR_WDTCLR_Pos                 0                      /*!< Reset interrupt WDT */

/* Bit field masks: */
#define WDT_INTCLR_WDTCLR_Msk                 0xFFFFFFFFUL           /*!< Reset interrupt WDT */

/*--  RIS: Watchdog Raw Interrupt Status Register -------------------------------------------------------------*/
typedef struct {
  uint32_t RAWWDTINT              :1;                                /*!< Raw interrupt status from the counter */
} _WDT_RIS_bits;

/* Bit field positions: */
#define WDT_RIS_RAWWDTINT_Pos                 0                      /*!< Raw interrupt status from the counter */

/* Bit field masks: */
#define WDT_RIS_RAWWDTINT_Msk                 0x00000001UL           /*!< Raw interrupt status from the counter */

/*--  MIS: Watchdog Interrupt Status Register -----------------------------------------------------------------*/
typedef struct {
  uint32_t WDTINT                 :1;                                /*!< Enabled interrupt status from the counter */
} _WDT_MIS_bits;

/* Bit field positions: */
#define WDT_MIS_WDTINT_Pos                    0                      /*!< Enabled interrupt status from the counter */

/* Bit field masks: */
#define WDT_MIS_WDTINT_Msk                    0x00000001UL           /*!< Enabled interrupt status from the counter */

/*--  LOCK: Watchdog Lock Register (write) --------------------------------------------------------------------*/
typedef struct {
  uint32_t CODE                   :32;                               /*!< Enable write access to all other registers by writing LOCK = 0x1ACCE551. Disable write to any othr registers of Watchdog by writing any other value */
} _WDT_LOCK_bits;

/* Bit field positions: */
#define WDT_LOCK_CODE_Pos                     0                      /*!< Enable write access to all other registers by writing LOCK = 0x1ACCE551. Disable write to any othr registers of Watchdog by writing any other value */

/* Bit field masks: */
#define WDT_LOCK_CODE_Msk                     0xFFFFFFFFUL           /*!< Enable write access to all other registers by writing LOCK = 0x1ACCE551. Disable write to any othr registers of Watchdog by writing any other value */

/* Bit field enums: */
typedef enum {
  WDT_LOCK_CODE_UNLOCK                       = 0x1ACCE551UL,         /*!< Value that clear LOCKSTAT.REGWRDIS bit */
  WDT_LOCK_CODE_LOCK_0                       = 0x0UL,                /*!< Example value that set LOCKSTAT.REGWRDIS (write to all registers except LOCK is disabled) */
  WDT_LOCK_CODE_LOCK_1                       = 0x1UL,                /*!< Example value that set LOCKSTAT.REGWRDIS (write to all registers except LOCK is disabled) */
} WDT_LOCK_CODE_Enum;

/*--  LOCKSTAT: Watchdog Lock Register (read) -----------------------------------------------------------------*/
typedef struct {
  uint32_t REGWRDIS               :1;                                /*!< Write to all registers of Watchdog is disabled */
} _WDT_LOCKSTAT_bits;

/* Bit field positions: */
#define WDT_LOCKSTAT_REGWRDIS_Pos             0                      /*!< Write to all registers of Watchdog is disabled */

/* Bit field masks: */
#define WDT_LOCKSTAT_REGWRDIS_Msk             0x00000001UL           /*!< Write to all registers of Watchdog is disabled */

typedef struct {
  union {                                                            /*!< Watchdog Load Register */
    __IO uint32_t LOAD;                                              /*!< LOAD    : type used for word access */
    __IO _WDT_LOAD_bits  LOAD_bit;                                   /*!< LOAD_bit: structure used for bit access */
  };
  union {                                                            /*!< Watchdog Value Register */
    __I uint32_t VALUE;                                              /*!< VALUE    : type used for word access */
    __I _WDT_VALUE_bits  VALUE_bit;                                  /*!< VALUE_bit: structure used for bit access */
  };
  union {                                                            /*!< Watchdog Control Register */
    __IO uint32_t CTRL;                                              /*!< CTRL    : type used for word access */
    __IO _WDT_CTRL_bits  CTRL_bit;                                   /*!< CTRL_bit: structure used for bit access */
  };
  union {                                                            /*!< Watchdog Clear Interrupt Register */
    __O uint32_t INTCLR;                                             /*!< INTCLR    : type used for word access */
    __O _WDT_INTCLR_bits  INTCLR_bit;                                /*!< INTCLR_bit: structure used for bit access */
  };
  union {                                                            /*!< Watchdog Raw Interrupt Status Register */
    __I uint32_t RIS;                                                /*!< RIS    : type used for word access */
    __I _WDT_RIS_bits  RIS_bit;                                      /*!< RIS_bit: structure used for bit access */
  };
  union {                                                            /*!< Watchdog Interrupt Status Register */
    __I uint32_t MIS;                                                /*!< MIS    : type used for word access */
    __I _WDT_MIS_bits  MIS_bit;                                      /*!< MIS_bit: structure used for bit access */
  };
    __IO uint32_t Reserved0[762];
  union {
    union {                                                            /*!< Watchdog Lock Register (write) */
      __O uint32_t LOCK;                                             /*!< LOCK    : type used for word access */
      __O _WDT_LOCK_bits  LOCK_bit;                                  /*!< LOCK_bit: structure used for bit access */
    };
    struct {
      union {                                                            /*!< Watchdog Lock Register (read) */
        __I uint32_t LOCKSTAT;                                           /*!< LOCKSTAT    : type used for word access */
        __I _WDT_LOCKSTAT_bits  LOCKSTAT_bit;                        /*!< LOCKSTAT_bit: structure used for bit access */
      };
    };
  };
} WDT_TypeDef;




/******************************************************************************/
/*                          Peripheral memory map                             */
/******************************************************************************/
#define GPIOA_BASE             (0x40000000UL)
#define GPIOB_BASE             (0x40001000UL)
#define CAN_BASE               (0x40010000UL)
#define CANMSG_BASE            (0x40011000UL)
#define ADC_BASE               (0x40020000UL)
#define DMA_BASE               (0x50000000UL)
#define FLASH_BASE             (0x50002000UL)
#define SIU_BASE               (0x50003000UL)
#define RCU_BASE               (0x50004000UL)
#define RTC_BASE               (0x50005000UL)
#define WDT_BASE               (0x50006000UL)
#define TMR32_0_BASE           (0x50007000UL)
#define TMR32_1_BASE           (0x50008000UL)
#define TMR16_0_BASE           (0x50009000UL)
#define TMR16_1_BASE           (0x5000A000UL)
#define TMR16_2_BASE           (0x5000B000UL)
#define I2C0_BASE              (0x5000C000UL)
#define I2C1_BASE              (0x5000D000UL)
#define UART0_BASE             (0x5000E000UL)
#define UART1_BASE             (0x5000F000UL)
#define SPI0_BASE              (0x50010000UL)
#define SPI1_BASE              (0x50011000UL)
#define SPI2_BASE              (0x50012000UL)
#define DAC_BASE               (0x50013000UL)

/******************************************************************************/
/*                          Peripheral declaration                            */
/******************************************************************************/
#define GPIOA                ((GPIO_TypeDef                *) GPIOA_BASE)
#define GPIOB                ((GPIO_TypeDef                *) GPIOB_BASE)
#define CAN                  ((CAN_TypeDef                 *) CAN_BASE)
#define CANMSG               ((CANMSG_TypeDef              *) CANMSG_BASE)
#define ADC                  ((ADC_TypeDef                 *) ADC_BASE)
#define DMA                  ((DMA_TypeDef                 *) DMA_BASE)
#define FLASH                ((FLASH_TypeDef               *) FLASH_BASE)
#define SIU                  ((SIU_TypeDef                 *) SIU_BASE)
#define RCU                  ((RCU_TypeDef                 *) RCU_BASE)
#define RTC                  ((RTC_TypeDef                 *) RTC_BASE)
#define WDT                  ((WDT_TypeDef                 *) WDT_BASE)
#define TMR32_0              ((TMR32_TypeDef               *) TMR32_0_BASE)
#define TMR32_1              ((TMR32_TypeDef               *) TMR32_1_BASE)
#define TMR16_0              ((TMR16_TypeDef               *) TMR16_0_BASE)
#define TMR16_1              ((TMR16_TypeDef               *) TMR16_1_BASE)
#define TMR16_2              ((TMR16_TypeDef               *) TMR16_2_BASE)
#define I2C0                 ((I2C_TypeDef                 *) I2C0_BASE)
#define I2C1                 ((I2C_TypeDef                 *) I2C1_BASE)
#define UART0                ((UART_TypeDef                *) UART0_BASE)
#define UART1                ((UART_TypeDef                *) UART1_BASE)
#define SPI0                 ((SPI_TypeDef                 *) SPI0_BASE)
#define SPI1                 ((SPI_TypeDef                 *) SPI1_BASE)
#define SPI2                 ((SPI_TypeDef                 *) SPI2_BASE)
#define DAC                  ((DAC_TypeDef                 *) DAC_BASE)

/******************************************************************************/
/*                          Peripheral capabilities                           */
/******************************************************************************/
#define GPIO_PRESENT
#define GPIO_TOTAL    2
typedef enum {
  GPIOA_Num,
  GPIOB_Num
} GPIO_Num_TypeDef;

#define CAN_PRESENT
#define CAN_TOTAL     1
typedef enum {
  CAN_Num
} CAN_Num_TypeDef;

#define CANMSG_PRESENT
#define CANMSG_TOTAL  1
typedef enum {
  CANMSG_Num
} CANMSG_Num_TypeDef;

#define ADC_PRESENT
#define ADC_TOTAL     1
typedef enum {
  ADC_Num
} ADC_Num_TypeDef;

#define DMA_PRESENT
#define DMA_TOTAL     1
typedef enum {
  DMA_Num
} DMA_Num_TypeDef;

#define FLASH_PRESENT
#define FLASH_TOTAL   1
typedef enum {
  FLASH_Num
} FLASH_Num_TypeDef;

#define SIU_PRESENT
#define SIU_TOTAL     1
typedef enum {
  SIU_Num
} SIU_Num_TypeDef;

#define RCU_PRESENT
#define RCU_TOTAL     1
typedef enum {
  RCU_Num
} RCU_Num_TypeDef;

#define RTC_PRESENT
#define RTC_TOTAL     1
typedef enum {
  RTC_Num
} RTC_Num_TypeDef;

#define WDT_PRESENT
#define WDT_TOTAL     1
typedef enum {
  WDT_Num
} WDT_Num_TypeDef;

#define TMR32_PRESENT
#define TMR32_TOTAL   2
typedef enum {
  TMR32_0_Num,
  TMR32_1_Num
} TMR32_Num_TypeDef;

#define TMR16_PRESENT
#define TMR16_TOTAL   3
typedef enum {
  TMR16_0_Num,
  TMR16_1_Num,
  TMR16_2_Num
} TMR16_Num_TypeDef;

#define I2C_PRESENT
#define I2C_TOTAL     2
typedef enum {
  I2C0_Num,
  I2C1_Num
} I2C_Num_TypeDef;

#define UART_PRESENT
#define UART_TOTAL    2
typedef enum {
  UART0_Num,
  UART1_Num
} UART_Num_TypeDef;

#define SPI_PRESENT
#define SPI_TOTAL     3
typedef enum {
  SPI0_Num,
  SPI1_Num,
  SPI2_Num
} SPI_Num_TypeDef;

#define DAC_PRESENT
#define DAC_TOTAL     1
typedef enum {
  DAC_Num
} DAC_Num_TypeDef;

/******************************************************************************/
/*                          Peripheral assertions                             */
/******************************************************************************/
#define IS_GPIO_PERIPH(PERIPH)                   (((PERIPH) == GPIOA) || \
                                                  ((PERIPH) == GPIOB))
#define IS_CAN_PERIPH(PERIPH)                    (((PERIPH) == CAN))
#define IS_CANMSG_PERIPH(PERIPH)                 (((PERIPH) == CANMSG))
#define IS_ADC_PERIPH(PERIPH)                    (((PERIPH) == ADC))
#define IS_DMA_PERIPH(PERIPH)                    (((PERIPH) == DMA))
#define IS_FLASH_PERIPH(PERIPH)                  (((PERIPH) == FLASH))
#define IS_SIU_PERIPH(PERIPH)                    (((PERIPH) == SIU))
#define IS_RCU_PERIPH(PERIPH)                    (((PERIPH) == RCU))
#define IS_RTC_PERIPH(PERIPH)                    (((PERIPH) == RTC))
#define IS_WDT_PERIPH(PERIPH)                    (((PERIPH) == WDT))
#define IS_TMR32_PERIPH(PERIPH)                  (((PERIPH) == TMR32_0) || \
                                                  ((PERIPH) == TMR32_1))
#define IS_TMR16_PERIPH(PERIPH)                  (((PERIPH) == TMR16_0) || \
                                                  ((PERIPH) == TMR16_1) || \
                                                  ((PERIPH) == TMR16_2))
#define IS_I2C_PERIPH(PERIPH)                    (((PERIPH) == I2C0) || \
                                                  ((PERIPH) == I2C1))
#define IS_UART_PERIPH(PERIPH)                   (((PERIPH) == UART0) || \
                                                  ((PERIPH) == UART1))
#define IS_SPI_PERIPH(PERIPH)                    (((PERIPH) == SPI0) || \
                                                  ((PERIPH) == SPI1) || \
                                                  ((PERIPH) == SPI2))
#define IS_DAC_PERIPH(PERIPH)                    (((PERIPH) == DAC))

#ifdef __cplusplus
}
#endif

#endif /* __K1921VG7T_H */

/************************** (C) COPYRIGHT 2026 NIIET ***************************
*
* END OF FILE K1921VG7T.h */
