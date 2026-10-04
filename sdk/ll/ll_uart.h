/**
 * @file ll_uart.h
 * @brief Low-level UART driver for the K1921VG SoC family.
 *
 * @defgroup ll_uart LL UART
 * @{
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ll_assert.h>
#include <soc.h>

#if !defined(K1921VG015) && !defined(K1921VG1T) && !defined(K1921VG3T) && !defined(K1921VG5T) && !defined(K1921VG7T)
#error "ll_uart.h: no implementation for the selected SoC"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Depth of TX/RX FIFOs in bytes (PL011: 16 entries each). */
#define LL_UART_FIFO_DEPTH 16U

#ifndef DOXYGEN_SHOULD_SKIP_THIS
_Static_assert(offsetof(UART_TypeDef, DR) == 0x00, "UART DR offset drift");
_Static_assert(offsetof(UART_TypeDef, RSR) == 0x04, "UART RSR offset drift");
_Static_assert(offsetof(UART_TypeDef, FR) == 0x18, "UART FR offset drift");
_Static_assert(offsetof(UART_TypeDef, IBRD) == 0x24, "UART IBRD offset drift");
_Static_assert(offsetof(UART_TypeDef, FBRD) == 0x28, "UART FBRD offset drift");
_Static_assert(offsetof(UART_TypeDef, LCRH) == 0x2C, "UART LCRH offset drift");
_Static_assert(offsetof(UART_TypeDef, CR) == 0x30, "UART CR offset drift");
_Static_assert(offsetof(UART_TypeDef, IFLS) == 0x34, "UART IFLS offset drift");
_Static_assert(offsetof(UART_TypeDef, IMSC) == 0x38, "UART IMSC offset drift");
_Static_assert(offsetof(UART_TypeDef, RIS) == 0x3C, "UART RIS offset drift");
_Static_assert(offsetof(UART_TypeDef, MIS) == 0x40, "UART MIS offset drift");
_Static_assert(offsetof(UART_TypeDef, ICR) == 0x44, "UART ICR offset drift");
_Static_assert(offsetof(UART_TypeDef, DMACR) == 0x48, "UART DMACR offset drift");
#endif

/** @brief Frame word length (encoded into LCRH.WLEN, 2 bits). */
typedef enum {
    LL_UART_WORDLEN_5 = 0, /**< 5 data bits. */
    LL_UART_WORDLEN_6 = 1, /**< 6 data bits. */
    LL_UART_WORDLEN_7 = 2, /**< 7 data bits. */
    LL_UART_WORDLEN_8 = 3, /**< 8 data bits (typical). */
} ll_uart_wordlen_t;

/** @brief Parity mode (encoded into LCRH.PEN/EPS/SPS). */
typedef enum {
    LL_UART_PARITY_NONE  = 0, /**< No parity bit. */
    LL_UART_PARITY_ODD   = 1, /**< Odd parity. */
    LL_UART_PARITY_EVEN  = 2, /**< Even parity. */
    LL_UART_PARITY_MARK  = 3, /**< Forced 1 (stick parity, SPS=1, EPS=0). */
    LL_UART_PARITY_SPACE = 4, /**< Forced 0 (stick parity, SPS=1, EPS=1). */
} ll_uart_parity_t;

/** @brief Number of stop bits. */
typedef enum {
    LL_UART_STOP_1 = 0, /**< One stop bit. */
    LL_UART_STOP_2 = 1, /**< Two stop bits. */
} ll_uart_stop_t;

/** @brief Hardware flow-control mode. */
typedef enum {
    LL_UART_FLOW_NONE     = 0, /**< No RTS/CTS flow control. */
    LL_UART_FLOW_RTS_ONLY = 1, /**< Hardware RTS enabled. */
    LL_UART_FLOW_CTS_ONLY = 2, /**< Hardware CTS enabled. */
    LL_UART_FLOW_RTS_CTS  = 3, /**< Full hardware RTS+CTS. */
} ll_uart_flow_t;

/**
 * @brief FIFO trigger level for the TXIM/RXIM interrupts.
 *
 * Encoded into IFLS.TXIFLSEL or IFLS.RXIFLSEL (3 bits each)
 */
typedef enum {
    LL_UART_FIFO_LEVEL_1_8 = 0, /**< 1/8 full (TX) or 1/8 full (RX). */
    LL_UART_FIFO_LEVEL_1_4 = 1, /**< 1/4 full. */
    LL_UART_FIFO_LEVEL_1_2 = 2, /**< 1/2 full. */
    LL_UART_FIFO_LEVEL_3_4 = 3, /**< 3/4 full. */
    LL_UART_FIFO_LEVEL_7_8 = 4, /**< 7/8 full. */
} ll_uart_fifo_level_t;

/**
 * @brief Bitmap of UART interrupt sources.
 *
 * Values correspond to the bit positions in the IMSC, RIS, MIS, and ICR
 * registers (same layout). OR multiple values together to act on several
 * sources in one call.
 */
typedef enum {
    LL_UART_IRQ_RI  = 1U << 0,     /**< RI (ring indicator) modem interrupt. */
    LL_UART_IRQ_CTS = 1U << 1,     /**< CTS modem interrupt. */
    LL_UART_IRQ_DCD = 1U << 2,     /**< DCD modem interrupt. */
    LL_UART_IRQ_DSR = 1U << 3,     /**< DSR modem interrupt. */
    LL_UART_IRQ_RX  = 1U << 4,     /**< Receive interrupt. */
    LL_UART_IRQ_TX  = 1U << 5,     /**< Transmit interrupt. */
    LL_UART_IRQ_RT  = 1U << 6,     /**< Receive timeout. */
    LL_UART_IRQ_FE  = 1U << 7,     /**< Framing error. */
    LL_UART_IRQ_PE  = 1U << 8,     /**< Parity error. */
    LL_UART_IRQ_BE  = 1U << 9,     /**< Break error. */
    LL_UART_IRQ_OE  = 1U << 10,    /**< Overrun error. */
    LL_UART_IRQ_TD  = 1U << 11,    /**< Transmit done (line emptied). */
    LL_UART_IRQ_ALL = 0x00000FFFU, /**< Mask covering every interrupt source. */
} ll_uart_irq_t;

/**
 * @name FIFO flag helpers
 * @{
 */

/**
 * @brief Read the full Flag Register.
 * @param uart  UART instance.
 * @return Raw value of @c FR.
 */
static inline uint32_t ll_uart_flags(const UART_TypeDef *uart)
{
    return uart->FR;
}

/**
 * @brief Check whether the UART is busy.
 * @param uart  UART instance.
 * @return @c true if FR.BUSY is asserted.
 */
static inline bool ll_uart_is_busy(const UART_TypeDef *uart)
{
    return (uart->FR & UART_FR_BUSY_Msk) != 0U;
}

/**
 * @brief Check whether the RX FIFO has no characters waiting.
 * @param uart  UART instance.
 * @return @c true if FR.RXFE is asserted.
 */
static inline bool ll_uart_rx_empty(const UART_TypeDef *uart)
{
    return (uart->FR & UART_FR_RXFE_Msk) != 0U;
}

/**
 * @brief Check whether at least one character is pending in the RX FIFO.
 * @param uart  UART instance.
 * @return @c true if FR.RXFE is clear.
 */
static inline bool ll_uart_rx_ready(const UART_TypeDef *uart)
{
    return (uart->FR & UART_FR_RXFE_Msk) == 0U;
}

/**
 * @brief Check whether the RX FIFO is at its full mark.
 * @param uart  UART instance.
 * @return @c true if FR.RXFF is asserted (next byte may overrun).
 */
static inline bool ll_uart_rx_full(const UART_TypeDef *uart)
{
    return (uart->FR & UART_FR_RXFF_Msk) != 0U;
}

/**
 * @brief Check whether the TX FIFO has no space remaining.
 * @param uart  UART instance.
 * @return @c true if FR.TXFF is asserted (writes to DR will be lost).
 */
static inline bool ll_uart_tx_full(const UART_TypeDef *uart)
{
    return (uart->FR & UART_FR_TXFF_Msk) != 0U;
}

/**
 * @brief Check whether the TX FIFO has space for at least one more byte.
 * @param uart  UART instance.
 * @return @c true if FR.TXFF is clear.
 */
static inline bool ll_uart_tx_ready(const UART_TypeDef *uart)
{
    return (uart->FR & UART_FR_TXFF_Msk) == 0U;
}

/**
 * @brief Check whether the TX FIFO is drained.
 * @param uart  UART instance.
 * @return @c true if FR.TXFE is asserted.
 */
static inline bool ll_uart_tx_empty(const UART_TypeDef *uart)
{
    return (uart->FR & UART_FR_TXFE_Msk) != 0U;
}

/** @} */

/**
 * @name Byte-level transfer
 * @{
 */

/**
 * @brief Push a byte into the TX FIFO without checking @ref ll_uart_tx_ready.
 * @param uart  UART instance.
 * @param byte  Byte to transmit.
 * @warning Drops the byte if the TX FIFO is full. Gate with @ref ll_uart_tx_ready
 *          (or @ref ll_uart_write) unless you have already verified space.
 */
static inline void ll_uart_write_raw(UART_TypeDef *uart, uint8_t byte)
{
    uart->DR = byte;
}

/**
 * @brief Pop the next byte from the RX FIFO without checking @ref ll_uart_rx_ready.
 * @param uart  UART instance.
 * @return Byte read; error flags in DR[11:8] are discarded.
 */
static inline uint8_t ll_uart_read_raw(UART_TypeDef *uart)
{
    return (uint8_t)(uart->DR & UART_DR_DATA_Msk);
}

/**
 * @brief Pop a byte from the RX FIFO.
 * @param uart  UART instance.
 * @return Raw @c DR value (data in bits[7:0], FE/PE/BE/OE in bits[11:8]).
 */
static inline uint32_t ll_uart_read_raw_with_flags(UART_TypeDef *uart)
{
    return uart->DR;
}

/**
 * @brief Block until the TX FIFO has space, then write @p byte.
 * @param uart  UART instance.
 * @param byte  Byte to transmit.
 */
static inline void ll_uart_write(UART_TypeDef *uart, uint8_t byte)
{
    while (ll_uart_tx_full(uart)) {}
    uart->DR = byte;
}

/**
 * @brief Block until a byte is available, then return it.
 * @param uart  UART instance.
 * @return Received byte.
 */
static inline uint8_t ll_uart_read(UART_TypeDef *uart)
{
    while (ll_uart_rx_empty(uart)) {}
    return (uint8_t)(uart->DR & UART_DR_DATA_Msk);
}

/**
 * @brief Send a buffer one byte at a time using polling.
 * @param uart  UART instance.
 * @param data  Pointer to the bytes to send.
 * @param size  Number of bytes to send.
 *
 * Returns after the last byte has been shifted onto the line (waits on
 * @ref ll_uart_is_busy).
 */
static inline void ll_uart_write_buffer(UART_TypeDef *uart, const uint8_t *data, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        ll_uart_write(uart, data[i]);
    }
    while (ll_uart_is_busy(uart)) {}
}

/**
 * @brief Receive @p size bytes by polling.
 * @param uart  UART instance.
 * @param data  Destination buffer.
 * @param size  Number of bytes to receive.
 */
static inline void ll_uart_read_buffer(UART_TypeDef *uart, uint8_t *data, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        data[i] = ll_uart_read(uart);
    }
}

/**
 * @brief Wait for the transmit shifter to fully drain.
 *
 * Useful before re-configuring CR/LCRH or before tearing down clocks.
 *
 * @param uart  UART instance.
 */
static inline void ll_uart_flush_tx(UART_TypeDef *uart)
{
    while (ll_uart_is_busy(uart)) {}
}

/** @} */

/**
 * @name Enable / disable
 * @{
 */

/**
 * @brief Enable the UART (sets CR.UARTEN).
 * @param uart  UART instance.
 */
static inline void ll_uart_enable(UART_TypeDef *uart)
{
    uart->CR |= UART_CR_UARTEN_Msk;
}

/**
 * @brief Disable the UART (clears CR.UARTEN). Flush TX first if line state matters.
 * @param uart  UART instance.
 */
static inline void ll_uart_disable(UART_TypeDef *uart)
{
    uart->CR &= ~UART_CR_UARTEN_Msk;
}

/**
 * @brief Toggle the TX section of the UART.
 * @param uart    UART instance.
 * @param enable  @c true to set CR.TXE, @c false to clear it.
 */
static inline void ll_uart_tx_enable(UART_TypeDef *uart, bool enable)
{
    if (enable) {
        uart->CR |= UART_CR_TXE_Msk;
    } else {
        uart->CR &= ~UART_CR_TXE_Msk;
    }
}

/**
 * @brief Toggle the RX section of the UART.
 * @param uart    UART instance.
 * @param enable  @c true to set CR.RXE, @c false to clear it.
 */
static inline void ll_uart_rx_enable(UART_TypeDef *uart, bool enable)
{
    if (enable) {
        uart->CR |= UART_CR_RXE_Msk;
    } else {
        uart->CR &= ~UART_CR_RXE_Msk;
    }
}

/** @} */

/**
 * @name Baudrate and framing
 * @{
 */

/**
 * @brief Program IBRD/FBRD to hit @p baudrate from a @p uartclk_hz input clock.
 *
 * Uses the standard PL011 formula: divisor = uartclk / (16 * baudrate); the
 * 6-bit fractional part is the rounded remainder times 64.
 *
 * @param uart        UART instance. Must be disabled (CR.UARTEN=0) when called.
 * @param uartclk_hz  Input clock frequency feeding the UART.
 * @param baudrate    Target line rate.
 */
static inline void ll_uart_set_baudrate(UART_TypeDef *uart, uint32_t uartclk_hz, uint32_t baudrate)
{
    LL_ASSERT(uart != NULL);
    LL_ASSERT(baudrate != 0U);
    LL_ASSERT(uartclk_hz != 0U);
    const uint32_t div64 = (uartclk_hz * 4U + baudrate / 2U) / baudrate;
    uart->IBRD           = (div64 >> 6) & 0xFFFFU;
    uart->FBRD           = div64 & 0x3FU;
}

/**
 * @brief Program LCRH (word length, parity, stop bits, FIFO enable).
 *
 * @param uart         UART instance. Must be disabled when called.
 * @param wordlen      Number of data bits.
 * @param parity       Parity mode.
 * @param stop         Stop-bit count.
 * @param fifo_enable  @c true to enable the 16-deep FIFOs.
 */
static inline void ll_uart_set_framing(UART_TypeDef *uart, ll_uart_wordlen_t wordlen, ll_uart_parity_t parity,
                                       ll_uart_stop_t stop, bool fifo_enable)
{
    uint32_t lcrh = ((uint32_t)wordlen << UART_LCRH_WLEN_Pos) & UART_LCRH_WLEN_Msk;

    if (fifo_enable) {
        lcrh |= UART_LCRH_FEN_Msk;
    }
    if (stop == LL_UART_STOP_2) {
        lcrh |= UART_LCRH_STP2_Msk;
    }

    switch (parity) {
    case LL_UART_PARITY_NONE:
        break;
    case LL_UART_PARITY_ODD:
        lcrh |= UART_LCRH_PEN_Msk;
        break;
    case LL_UART_PARITY_EVEN:
        lcrh |= UART_LCRH_PEN_Msk | UART_LCRH_EPS_Msk;
        break;
    case LL_UART_PARITY_MARK:
        lcrh |= UART_LCRH_PEN_Msk | UART_LCRH_SPS_Msk;
        break;
    case LL_UART_PARITY_SPACE:
        lcrh |= UART_LCRH_PEN_Msk | UART_LCRH_EPS_Msk | UART_LCRH_SPS_Msk;
        break;
    }

    uart->LCRH = lcrh;
}

/**
 * @brief Configure RTS/CTS hardware flow control.
 * @param uart  UART instance.
 * @param flow  Flow control mode.
 */
static inline void ll_uart_set_flow_control(UART_TypeDef *uart, ll_uart_flow_t flow)
{
    uint32_t cr = uart->CR & ~(UART_CR_RTSEN_Msk | UART_CR_CTSEN_Msk);

    if (flow == LL_UART_FLOW_RTS_ONLY || flow == LL_UART_FLOW_RTS_CTS) {
        cr |= UART_CR_RTSEN_Msk;
    }
    if (flow == LL_UART_FLOW_CTS_ONLY || flow == LL_UART_FLOW_RTS_CTS) {
        cr |= UART_CR_CTSEN_Msk;
    }

    uart->CR = cr;
}

/**
 * @brief Enable or disable internal loopback (CR.LBE) for self-test.
 * @param uart    UART instance.
 * @param enable  @c true to loop TX to RX, @c false for normal operation.
 */
static inline void ll_uart_set_loopback(UART_TypeDef *uart, bool enable)
{
    if (enable) {
        uart->CR |= UART_CR_LBE_Msk;
    } else {
        uart->CR &= ~UART_CR_LBE_Msk;
    }
}

/**
 * @brief Force the TX line low (assert break).
 * @param uart    UART instance.
 * @param enable  @c true to assert break, @c false to release.
 */
static inline void ll_uart_set_break(UART_TypeDef *uart, bool enable)
{
    if (enable) {
        uart->LCRH |= UART_LCRH_BRK_Msk;
    } else {
        uart->LCRH &= ~UART_LCRH_BRK_Msk;
    }
}

/** @} */

/**
 * @name Interrupts
 * @{
 */

/**
 * @brief Set the FIFO fill levels that trigger TXIM/RXIM.
 * @param uart      UART instance.
 * @param tx_level  TX threshold.
 * @param rx_level  RX threshold.
 */
static inline void ll_uart_set_fifo_levels(UART_TypeDef *uart, ll_uart_fifo_level_t tx_level,
                                           ll_uart_fifo_level_t rx_level)
{
    uart->IFLS = (((uint32_t)tx_level << UART_IFLS_TXIFLSEL_Pos) & UART_IFLS_TXIFLSEL_Msk) |
                 (((uint32_t)rx_level << UART_IFLS_RXIFLSEL_Pos) & UART_IFLS_RXIFLSEL_Msk);
}

/**
 * @brief Unmask interrupt sources in IMSC.
 * @param uart  UART instance.
 * @param mask  Bitwise OR of @ref ll_uart_irq_t values.
 */
static inline void ll_uart_irq_enable(UART_TypeDef *uart, uint32_t mask)
{
    uart->IMSC |= mask;
}

/**
 * @brief Mask interrupt sources in IMSC.
 * @param uart  UART instance.
 * @param mask  Bitwise OR of @ref ll_uart_irq_t values.
 */
static inline void ll_uart_irq_disable(UART_TypeDef *uart, uint32_t mask)
{
    uart->IMSC &= ~mask;
}

/**
 * @brief Read the masked interrupt status (sources currently asserting an IRQ).
 * @param uart  UART instance.
 * @return Bitmap of asserted interrupts.
 */
static inline uint32_t ll_uart_irq_status(const UART_TypeDef *uart)
{
    return uart->MIS;
}

/**
 * @brief Read the raw interrupt status (pre-mask).
 * @param uart  UART instance.
 * @return Bitmap of pending interrupt sources before masking.
 */
static inline uint32_t ll_uart_irq_raw_status(const UART_TypeDef *uart)
{
    return uart->RIS;
}

/**
 * @brief Clear (acknowledge) interrupt sources.
 *
 * Note: the RX and TX interrupts on PL011 can also be cleared by reading or
 * writing the FIFO; @c ICR is only required for the modem/error sources.
 *
 * @param uart  UART instance.
 * @param mask  Bitmap of sources to clear.
 */
static inline void ll_uart_irq_clear(UART_TypeDef *uart, uint32_t mask)
{
    uart->ICR = mask;
}

/** @} */

/**
 * @name DMA
 * @{
 */

/**
 * @brief Enable or disable DMA request generation for the TX direction.
 * @param uart    UART instance.
 * @param enable  @c true to set DMACR.TXDMAE, @c false to clear it.
 */
static inline void ll_uart_dma_tx_enable(UART_TypeDef *uart, bool enable)
{
    if (enable) {
        uart->DMACR |= UART_DMACR_TXDMAE_Msk;
    } else {
        uart->DMACR &= ~UART_DMACR_TXDMAE_Msk;
    }
}

/**
 * @brief Enable or disable DMA request generation for the RX direction.
 * @param uart    UART instance.
 * @param enable  @c true to set DMACR.RXDMAE, @c false to clear it.
 */
static inline void ll_uart_dma_rx_enable(UART_TypeDef *uart, bool enable)
{
    if (enable) {
        uart->DMACR |= UART_DMACR_RXDMAE_Msk;
    } else {
        uart->DMACR &= ~UART_DMACR_RXDMAE_Msk;
    }
}

/**
 * @brief Toggle DMACR.DMAONERR — gate DMA RX requests while an error flag is set.
 * @param uart    UART instance.
 * @param enable  @c true to halt DMA on error.
 */
static inline void ll_uart_dma_on_error_enable(UART_TypeDef *uart, bool enable)
{
    if (enable) {
        uart->DMACR |= UART_DMACR_DMAONERR_Msk;
    } else {
        uart->DMACR &= ~UART_DMACR_DMAONERR_Msk;
    }
}

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
