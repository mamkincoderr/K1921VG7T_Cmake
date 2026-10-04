/**
 * @file ll_spi.h
 * @brief Low-level SPI driver for the K1921VG SoC family.
 *
 * Header-only inline driver covering the PrimeCell SSP-style SPI block present
 * on all five supported SoCs. Two register-layout variants are reconciled
 * behind one API:
 *
 *  - **Split-CR variant (K1921VG015):** control bits are spread across two
 *    16-bit registers @c CR0 and @c CR1 (DSS is 4 bits → 4..16 data bits, no
 *    loopback). Selected via @c LL_SPI_HAS_SPLIT_CR == 1.
 *
 *  - **Single-CR variant (K1921VG1T/3T/5T/7T):** every control field lives in
 *    one 32-bit @c CR (DSS is 5 bits → 4..32 data bits, has an LBM loopback
 *    bit). Selected via @c LL_SPI_HAS_SPLIT_CR == 0.
 *
 * Common bit-field constants — @c SPI_SR_*, @c SPI_CPSR_*, @c SPI_IMSC_*,
 * @c SPI_RIS_*, @c SPI_MIS_*, @c SPI_ICR_*, @c SPI_DMACR_*, @c SPI_DR_DATA_*
 * — are identical across all SoCs, so the FIFO/interrupt/DMA helpers compile
 * to the same code on every target.
 *
 * @defgroup ll_spi LL SPI
 * @{
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ll_assert.h>
#include <soc.h>

/**
 * @name SoC capability flags
 * @{
 */
#if defined(K1921VG015)
/** @brief 1 if the SoC splits the control fields across CR0/CR1 registers. */
#define LL_SPI_HAS_SPLIT_CR 1
/** @brief 0 if the IP does not implement the loopback (LBM) bit. */
#define LL_SPI_HAS_LOOPBACK 0
/** @brief Maximum supported data-size value (encoded into DSS field). */
#define LL_SPI_DSS_MAX 16U
#elif defined(K1921VG1T) || defined(K1921VG3T) || defined(K1921VG5T) || defined(K1921VG7T)
#define LL_SPI_HAS_SPLIT_CR 0
#define LL_SPI_HAS_LOOPBACK 1
#define LL_SPI_DSS_MAX      32U
#else
#error "ll_spi.h: no implementation for the selected SoC"
#endif
/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief PrimeCell SSP FIFO depth in entries (TX and RX each). */
#define LL_SPI_FIFO_DEPTH 8U

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if LL_SPI_HAS_SPLIT_CR
_Static_assert(offsetof(SPI_TypeDef, CR0) == 0x00, "SPI CR0 offset drift");
_Static_assert(offsetof(SPI_TypeDef, CR1) == 0x04, "SPI CR1 offset drift");
#else
_Static_assert(offsetof(SPI_TypeDef, CR) == 0x00, "SPI CR offset drift");
#endif
_Static_assert(offsetof(SPI_TypeDef, DR) == 0x08, "SPI DR offset drift");
_Static_assert(offsetof(SPI_TypeDef, SR) == 0x0C, "SPI SR offset drift");
_Static_assert(offsetof(SPI_TypeDef, CPSR) == 0x10, "SPI CPSR offset drift");
_Static_assert(offsetof(SPI_TypeDef, IMSC) == 0x14, "SPI IMSC offset drift");
_Static_assert(offsetof(SPI_TypeDef, RIS) == 0x18, "SPI RIS offset drift");
_Static_assert(offsetof(SPI_TypeDef, MIS) == 0x1C, "SPI MIS offset drift");
_Static_assert(offsetof(SPI_TypeDef, ICR) == 0x20, "SPI ICR offset drift");
_Static_assert(offsetof(SPI_TypeDef, DMACR) == 0x24, "SPI DMACR offset drift");
#endif

/** @brief Frame format programmed into the FRF field. */
typedef enum {
    LL_SPI_FRAME_MOTOROLA  = 0, /**< Motorola SPI (the common default). */
    LL_SPI_FRAME_TI        = 1, /**< Texas Instruments SSI. */
    LL_SPI_FRAME_MICROWIRE = 2, /**< National Semiconductor Microwire (master-only). */
} ll_spi_frame_format_t;

/** @brief Master/Slave role programmed into the MS bit. */
typedef enum {
    LL_SPI_ROLE_MASTER = 0, /**< Drive SCLK as a master. */
    LL_SPI_ROLE_SLAVE  = 1, /**< Receive SCLK from an external master. */
} ll_spi_role_t;

/**
 * @brief Clock polarity / phase pair, packed into the SPO and SPH bits.
 *
 * Numbering matches the canonical SPI mode chart (CPOL,CPHA).
 */
typedef enum {
    LL_SPI_MODE_0 = 0, /**< CPOL=0, CPHA=0 — idle low, sample leading. */
    LL_SPI_MODE_1 = 1, /**< CPOL=0, CPHA=1 — idle low, sample trailing. */
    LL_SPI_MODE_2 = 2, /**< CPOL=1, CPHA=0 — idle high, sample leading. */
    LL_SPI_MODE_3 = 3, /**< CPOL=1, CPHA=1 — idle high, sample trailing. */
} ll_spi_mode_t;

/**
 * @brief RX/TX FIFO trigger levels (PrimeCell SSP uses 4-bit fill markers).
 *
 * The numeric values are the standard 1/8, 1/4, 1/2, 3/4, 7/8 selectors.
 */
typedef enum {
    LL_SPI_FIFO_LEVEL_1_8 = 0, /**< Trigger at 1/8 fill. */
    LL_SPI_FIFO_LEVEL_1_4 = 1, /**< Trigger at 1/4 fill. */
    LL_SPI_FIFO_LEVEL_1_2 = 2, /**< Trigger at 1/2 fill. */
    LL_SPI_FIFO_LEVEL_3_4 = 3, /**< Trigger at 3/4 fill. */
    LL_SPI_FIFO_LEVEL_7_8 = 4, /**< Trigger at 7/8 fill. */
} ll_spi_fifo_level_t;

/**
 * @brief Bitmap of SPI interrupt sources (shared layout for IMSC/RIS/MIS).
 *
 * Note: only @ref LL_SPI_IRQ_OVERRUN and @ref LL_SPI_IRQ_RX_TIMEOUT can be
 * acknowledged via ICR; the RX/TX FIFO interrupts self-clear as the FIFOs
 * drain or fill past their thresholds.
 */
typedef enum {
    LL_SPI_IRQ_OVERRUN    = 1U << 0, /**< RX FIFO overflow (ROR). */
    LL_SPI_IRQ_RX_TIMEOUT = 1U << 1, /**< RX FIFO occupied but stalled (RT). */
    LL_SPI_IRQ_RX_HALF    = 1U << 2, /**< RX FIFO crossed its level mark (RX). */
    LL_SPI_IRQ_TX_HALF    = 1U << 3, /**< TX FIFO crossed its level mark (TX). */
    LL_SPI_IRQ_ALL        = 0x0FU,   /**< Mask covering all four sources. */
} ll_spi_irq_t;

/**
 * @name FIFO / status helpers
 * @{
 */

/**
 * @brief Read the full Status Register.
 * @param spi  SPI instance.
 * @return Raw @c SR value.
 */
static inline uint32_t ll_spi_status(const SPI_TypeDef *spi)
{
    return spi->SR;
}

/**
 * @brief Check whether the SPI is shifting a frame out.
 * @param spi  SPI instance.
 * @return @c true if SR.BSY is asserted.
 */
static inline bool ll_spi_is_busy(const SPI_TypeDef *spi)
{
    return (spi->SR & SPI_SR_BSY_Msk) != 0U;
}

/**
 * @brief Check whether the TX FIFO is fully drained.
 * @param spi  SPI instance.
 * @return @c true if SR.TFE is asserted.
 */
static inline bool ll_spi_tx_empty(const SPI_TypeDef *spi)
{
    return (spi->SR & SPI_SR_TFE_Msk) != 0U;
}

/**
 * @brief Check whether the TX FIFO has space for another frame.
 * @param spi  SPI instance.
 * @return @c true if SR.TNF is asserted.
 */
static inline bool ll_spi_tx_ready(const SPI_TypeDef *spi)
{
    return (spi->SR & SPI_SR_TNF_Msk) != 0U;
}

/**
 * @brief Check whether the RX FIFO has a frame ready to read.
 * @param spi  SPI instance.
 * @return @c true if SR.RNE is asserted.
 */
static inline bool ll_spi_rx_ready(const SPI_TypeDef *spi)
{
    return (spi->SR & SPI_SR_RNE_Msk) != 0U;
}

/**
 * @brief Check whether the RX FIFO has reached its full mark.
 * @param spi  SPI instance.
 * @return @c true if SR.RFF is asserted.
 */
static inline bool ll_spi_rx_full(const SPI_TypeDef *spi)
{
    return (spi->SR & SPI_SR_RFF_Msk) != 0U;
}

/**
 * @brief Wait for the shift register to drain.
 * @param spi  SPI instance.
 */
static inline void ll_spi_flush(SPI_TypeDef *spi)
{
    while (ll_spi_is_busy(spi)) {}
}

/**
 * @brief Discard every frame currently in the RX FIFO.
 * @param spi  SPI instance.
 */
static inline void ll_spi_drain_rx(SPI_TypeDef *spi)
{
    while (ll_spi_rx_ready(spi)) {
        (void)spi->DR;
    }
}

/** @} */

/**
 * @name Raw byte-level transfer
 * @{
 */

/**
 * @brief Push a frame into the TX FIFO without checking @ref ll_spi_tx_ready.
 * @param spi    SPI instance.
 * @param frame  Frame to transmit (low bits up to the programmed DSS width).
 */
static inline void ll_spi_write_raw(SPI_TypeDef *spi, uint32_t frame)
{
    spi->DR = frame;
}

/**
 * @brief Pop a frame from the RX FIFO without checking @ref ll_spi_rx_ready.
 * @param spi  SPI instance.
 * @return Received frame (high bits above DSS are returned as zero).
 */
static inline uint32_t ll_spi_read_raw(SPI_TypeDef *spi)
{
    return spi->DR;
}

/**
 * @brief Block until the TX FIFO has space, then write @p frame.
 * @param spi    SPI instance.
 * @param frame  Frame to transmit.
 */
static inline void ll_spi_write(SPI_TypeDef *spi, uint32_t frame)
{
    while (!ll_spi_tx_ready(spi)) {}
    spi->DR = frame;
}

/**
 * @brief Block until a frame is available, then return it.
 * @param spi  SPI instance.
 * @return Received frame.
 */
static inline uint32_t ll_spi_read(SPI_TypeDef *spi)
{
    while (!ll_spi_rx_ready(spi)) {}
    return spi->DR;
}

/**
 * @brief Send one frame and return the simultaneously received frame.
 *
 * Drains any stale RX entries, transmits @p frame, waits for the shifter to
 * idle, and returns whatever the slave clocked back. Use this for the
 * register-style transactions typical of SD cards / display controllers.
 *
 * @param spi    SPI instance (must be master, must be enabled).
 * @param frame  Frame to transmit.
 * @return Frame received concurrently.
 */
static inline uint32_t ll_spi_exchange(SPI_TypeDef *spi, uint32_t frame)
{
    ll_spi_drain_rx(spi);
    ll_spi_write(spi, frame);
    ll_spi_flush(spi);
    return ll_spi_read(spi);
}

/** @} */

/**
 * @name Enable / disable
 * @{
 */

/**
 * @brief Enable the SPI block (sets CR/CR1 SSE bit).
 * @param spi  SPI instance.
 */
static inline void ll_spi_enable(SPI_TypeDef *spi)
{
#if LL_SPI_HAS_SPLIT_CR
    spi->CR1 |= SPI_CR1_SSE_Msk;
#else
    spi->CR |= SPI_CR_SSE_Msk;
#endif
}

/**
 * @brief Disable the SPI block.
 *
 * Flushes the shift register before clearing SSE so the bus state stays
 * predictable.
 *
 * @param spi  SPI instance.
 */
static inline void ll_spi_disable(SPI_TypeDef *spi)
{
    ll_spi_flush(spi);
#if LL_SPI_HAS_SPLIT_CR
    spi->CR1 &= ~SPI_CR1_SSE_Msk;
#else
    spi->CR &= ~SPI_CR_SSE_Msk;
#endif
}

/**
 * @brief Set or clear the slave-output-disable (SOD) bit.
 *
 * Only meaningful in slave mode. When asserted the SPI keeps @c MISO Hi-Z so
 * multiple slaves can share the line.
 *
 * @param spi      SPI instance.
 * @param disable  @c true to Hi-Z @c MISO.
 */
static inline void ll_spi_slave_output_disable(SPI_TypeDef *spi, bool disable)
{
#if LL_SPI_HAS_SPLIT_CR
    if (disable) {
        spi->CR1 |= SPI_CR1_SOD_Msk;
    } else {
        spi->CR1 &= ~SPI_CR1_SOD_Msk;
    }
#else
    if (disable) {
        spi->CR |= SPI_CR_SOD_Msk;
    } else {
        spi->CR &= ~SPI_CR_SOD_Msk;
    }
#endif
}

#if LL_SPI_HAS_LOOPBACK
/**
 * @brief Enable or disable internal loopback (CR.LBM) for self-test.
 *
 * A no-op stub is provided on SoCs without the LBM bit (e.g. K1921VG015) so
 * callers do not need to guard calls with @c LL_SPI_HAS_LOOPBACK.
 *
 * @param spi     SPI instance.
 * @param enable  @c true to loop TX to RX internally.
 */
static inline void ll_spi_set_loopback(SPI_TypeDef *spi, bool enable)
{
    if (enable) {
        spi->CR |= SPI_CR_LBM_Msk;
    } else {
        spi->CR &= ~SPI_CR_LBM_Msk;
    }
}
#else
static inline void ll_spi_set_loopback(SPI_TypeDef *spi, bool enable)
{
    (void)spi;
    (void)enable;
    /* vg015: no LBM bit; loopback unsupported - no-op stub. */
}
#endif

/** @} */

/**
 * @name Bit-rate generator
 * @{
 */

/**
 * @brief Program CPSR and the SCR field to hit @p bit_rate_hz from @p spi_clk_hz.
 *
 * PrimeCell SSP divides the input clock as
 *   bit_rate = spi_clk / (CPSDVSR * (1 + SCR))
 * with CPSDVSR in 2..254 (even) and SCR in 0..255. This helper sweeps SCR
 * upward at increasing CPSDVSR values and picks the lowest divider pair that
 * produces a frequency at or below the target.
 *
 * @param spi          SPI instance (the SSE bit should be 0 when called).
 * @param spi_clk_hz   Frequency of the clock feeding the SPI block.
 * @param bit_rate_hz  Target SCK rate.
 */
static inline void ll_spi_set_bit_rate(SPI_TypeDef *spi, uint32_t spi_clk_hz, uint32_t bit_rate_hz)
{
    LL_ASSERT(spi != NULL);
    LL_ASSERT(spi_clk_hz > 0U);

    uint32_t cpsdvsr = 2U;
    uint32_t scr     = 0U;

    if (bit_rate_hz == 0U) {
        bit_rate_hz = 1U;
    }

    for (cpsdvsr = 2U; cpsdvsr <= 254U; cpsdvsr += 2U) {
        uint64_t denom = (uint64_t)cpsdvsr * bit_rate_hz;
        if (denom == 0U) {
            continue;
        }
        uint64_t scr_plus_one = (spi_clk_hz + denom - 1U) / denom;
        if (scr_plus_one == 0U) {
            scr_plus_one = 1U;
        }
        if (scr_plus_one <= 256U) {
            scr = (uint32_t)scr_plus_one - 1U;
            break;
        }
    }

    spi->CPSR = cpsdvsr & SPI_CPSR_CPSDVSR_Msk;

#if LL_SPI_HAS_SPLIT_CR
    spi->CR0 = (spi->CR0 & ~SPI_CR0_SCR_Msk) | ((scr << SPI_CR0_SCR_Pos) & SPI_CR0_SCR_Msk);
#else
    spi->CR = (spi->CR & ~SPI_CR_SCR_Msk) | ((scr << SPI_CR_SCR_Pos) & SPI_CR_SCR_Msk);
#endif
}

/**
 * @brief Program the frame format and mode (DSS, FRF, SPO, SPH).
 *
 * @param spi         SPI instance (must be disabled when called).
 * @param data_bits   Frame size, 4..@c LL_SPI_DSS_MAX.
 * @param frame       Frame format (Motorola/TI/Microwire).
 * @param mode        Clock polarity/phase.
 */
static inline void ll_spi_set_framing(SPI_TypeDef *spi, uint8_t data_bits, ll_spi_frame_format_t frame,
                                      ll_spi_mode_t mode)
{
    LL_ASSERT(spi != NULL);
    LL_ASSERT(data_bits >= 4U);
    LL_ASSERT(data_bits <= LL_SPI_DSS_MAX);

    if (data_bits < 4U) {
        data_bits = 4U;
    }
    if (data_bits > LL_SPI_DSS_MAX) {
        data_bits = (uint8_t)LL_SPI_DSS_MAX;
    }

    const uint32_t dss = (uint32_t)(data_bits - 1U);
    const bool spo     = (mode == LL_SPI_MODE_2) || (mode == LL_SPI_MODE_3);
    const bool sph     = (mode == LL_SPI_MODE_1) || (mode == LL_SPI_MODE_3);

#if LL_SPI_HAS_SPLIT_CR
    uint32_t cr0 = spi->CR0 & ~(SPI_CR0_DSS_Msk | SPI_CR0_FRF_Msk | SPI_CR0_SPO_Msk | SPI_CR0_SPH_Msk);
    cr0 |= (dss << SPI_CR0_DSS_Pos) & SPI_CR0_DSS_Msk;
    cr0 |= ((uint32_t)frame << SPI_CR0_FRF_Pos) & SPI_CR0_FRF_Msk;
    if (spo) {
        cr0 |= SPI_CR0_SPO_Msk;
    }
    if (sph) {
        cr0 |= SPI_CR0_SPH_Msk;
    }
    spi->CR0 = cr0;
#else
    uint32_t cr = spi->CR & ~(SPI_CR_DSS_Msk | SPI_CR_FRF_Msk | SPI_CR_SPO_Msk | SPI_CR_SPH_Msk);
    cr |= (dss << SPI_CR_DSS_Pos) & SPI_CR_DSS_Msk;
    cr |= ((uint32_t)frame << SPI_CR_FRF_Pos) & SPI_CR_FRF_Msk;
    if (spo) {
        cr |= SPI_CR_SPO_Msk;
    }
    if (sph) {
        cr |= SPI_CR_SPH_Msk;
    }
    spi->CR = cr;
#endif
}

/**
 * @brief Choose master/slave role (MS bit).
 * @param spi   SPI instance (must be disabled when called).
 * @param role  Role to apply.
 */
static inline void ll_spi_set_role(SPI_TypeDef *spi, ll_spi_role_t role)
{
#if LL_SPI_HAS_SPLIT_CR
    if (role == LL_SPI_ROLE_SLAVE) {
        spi->CR1 |= SPI_CR1_MS_Msk;
    } else {
        spi->CR1 &= ~SPI_CR1_MS_Msk;
    }
#else
    if (role == LL_SPI_ROLE_SLAVE) {
        spi->CR |= SPI_CR_MS_Msk;
    } else {
        spi->CR &= ~SPI_CR_MS_Msk;
    }
#endif
}

/**
 * @brief Set the RX FIFO and TX FIFO interrupt level marks.
 * @param spi       SPI instance.
 * @param rx_level  Threshold for the RX-half interrupt.
 * @param tx_level  Threshold for the TX-half interrupt.
 */
static inline void ll_spi_set_fifo_levels(SPI_TypeDef *spi, ll_spi_fifo_level_t rx_level, ll_spi_fifo_level_t tx_level)
{
#if LL_SPI_HAS_SPLIT_CR
    uint32_t cr1 = spi->CR1 & ~(SPI_CR1_RXIFLSEL_Msk | SPI_CR1_TXIFLSEL_Msk);
    cr1 |= ((uint32_t)rx_level << SPI_CR1_RXIFLSEL_Pos) & SPI_CR1_RXIFLSEL_Msk;
    cr1 |= ((uint32_t)tx_level << SPI_CR1_TXIFLSEL_Pos) & SPI_CR1_TXIFLSEL_Msk;
    spi->CR1 = cr1;
#else
    uint32_t cr = spi->CR & ~(SPI_CR_RXIFLSEL_Msk | SPI_CR_TXIFLSEL_Msk);
    cr |= ((uint32_t)rx_level << SPI_CR_RXIFLSEL_Pos) & SPI_CR_RXIFLSEL_Msk;
    cr |= ((uint32_t)tx_level << SPI_CR_TXIFLSEL_Pos) & SPI_CR_TXIFLSEL_Msk;
    spi->CR = cr;
#endif
}

/** @} */

/**
 * @name Interrupts
 * @{
 */

/**
 * @brief Unmask interrupt sources in IMSC.
 * @param spi   SPI instance.
 * @param mask  Bitwise OR of @ref ll_spi_irq_t values.
 */
static inline void ll_spi_irq_enable(SPI_TypeDef *spi, uint32_t mask)
{
    spi->IMSC |= mask;
}

/**
 * @brief Mask interrupt sources in IMSC.
 * @param spi   SPI instance.
 * @param mask  Bitwise OR of @ref ll_spi_irq_t values.
 */
static inline void ll_spi_irq_disable(SPI_TypeDef *spi, uint32_t mask)
{
    spi->IMSC &= ~mask;
}

/**
 * @brief Read the masked interrupt status.
 * @param spi  SPI instance.
 * @return Bitmap of asserting masked sources.
 */
static inline uint32_t ll_spi_irq_status(const SPI_TypeDef *spi)
{
    return spi->MIS;
}

/**
 * @brief Read the raw (pre-mask) interrupt status.
 * @param spi  SPI instance.
 * @return Bitmap of pending sources before IMSC.
 */
static inline uint32_t ll_spi_irq_raw_status(const SPI_TypeDef *spi)
{
    return spi->RIS;
}

/**
 * @brief Acknowledge interrupts.
 *
 * Only @ref LL_SPI_IRQ_OVERRUN and @ref LL_SPI_IRQ_RX_TIMEOUT honor ICR; the
 * RX/TX half-full sources auto-clear as the FIFO crosses its threshold.
 *
 * @param spi   SPI instance.
 * @param mask  Sources to clear (typically @c LL_SPI_IRQ_OVERRUN | @c LL_SPI_IRQ_RX_TIMEOUT).
 */
static inline void ll_spi_irq_clear(SPI_TypeDef *spi, uint32_t mask)
{
    spi->ICR = mask;
}

/** @} */

/**
 * @name DMA
 * @{
 */

/**
 * @brief Enable or disable DMA request generation for the TX direction.
 * @param spi     SPI instance.
 * @param enable  @c true to set DMACR.TXDMAE, @c false to clear it.
 */
static inline void ll_spi_dma_tx_enable(SPI_TypeDef *spi, bool enable)
{
    if (enable) {
        spi->DMACR |= SPI_DMACR_TXDMAE_Msk;
    } else {
        spi->DMACR &= ~SPI_DMACR_TXDMAE_Msk;
    }
}

/**
 * @brief Enable or disable DMA request generation for the RX direction.
 * @param spi     SPI instance.
 * @param enable  @c true to set DMACR.RXDMAE, @c false to clear it.
 */
static inline void ll_spi_dma_rx_enable(SPI_TypeDef *spi, bool enable)
{
    if (enable) {
        spi->DMACR |= SPI_DMACR_RXDMAE_Msk;
    } else {
        spi->DMACR &= ~SPI_DMACR_RXDMAE_Msk;
    }
}

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */ /* end of ll_spi group */
