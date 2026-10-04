/**
 * @file ll_gpio.h
 * @brief Low-level GPIO driver for the K1921VG SoC family.
 *
 * Header-only inline driver covering the GPIO IP block present on
 * K1921VG015 (Cloudbear BM-310) and K1921VG1T/3T/5T/7T (Syntacore SCR4/SCR5).
 *
 * The driver targets a single GPIO port at a time — pass a pointer to the
 * desired @c GPIO_TypeDef (e.g. @c GPIOA, @c GPIOB) and a 16-bit pin mask.
 * Register-offset invariants are pinned with @c _Static_assert so a header
 * drift in @c soc.h breaks compilation rather than producing silent corruption.
 *
 * @defgroup ll_gpio LL GPIO
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
 *
 * Per-SoC feature switches resolved at compile time from the SoC define
 * (@c K1921VG*) supplied via CMake.
 * @{
 */
#if defined(K1921VG1T)
/** @brief 1 if the SoC splits ALTFUNCNUM into two 4-bit-per-pin registers. */
#define LL_GPIO_HAS_SPLIT_ALTFUNC 1
/** @brief 1 if the SoC has separate TX/RX DMA request registers. */
#define LL_GPIO_HAS_TXRX_DMA 1
/** @brief 1 if the SoC exposes the RXEV (receive-event) registers. */
#define LL_GPIO_HAS_RXEV 1
/** @brief Maximum legal alternate-function index for this SoC. */
#define LL_GPIO_ALTFUNC_MAX 15U
#elif defined(K1921VG3T) || defined(K1921VG5T) || defined(K1921VG7T)
#define LL_GPIO_HAS_SPLIT_ALTFUNC 0
#define LL_GPIO_HAS_TXRX_DMA      1
#define LL_GPIO_HAS_RXEV          1
#define LL_GPIO_ALTFUNC_MAX       3U
#elif defined(K1921VG015)
#define LL_GPIO_HAS_SPLIT_ALTFUNC 0
#define LL_GPIO_HAS_TXRX_DMA      0
#define LL_GPIO_HAS_RXEV          0
#define LL_GPIO_ALTFUNC_MAX       3U
#else
#error "ll_gpio.h: no implementation for the selected SoC"
#endif
/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Number of pins per GPIO port (all supported SoCs share this). */
#define LL_GPIO_PIN_COUNT 16U
/** @brief Mask covering all 16 pins of a port. */
#define LL_GPIO_PIN_MASK 0xFFFFU
/** @brief Magic value written to @c LOCKKEY to unlock the lock register set. */
#define LL_GPIO_LOCK_KEY 0xADEADBEEU

#ifndef DOXYGEN_SHOULD_SKIP_THIS
_Static_assert(offsetof(GPIO_TypeDef, DATA) == 0x00, "GPIO DATA offset drift");
_Static_assert(offsetof(GPIO_TypeDef, DATAOUT) == 0x04, "GPIO DATAOUT offset drift");
_Static_assert(offsetof(GPIO_TypeDef, DATAOUTSET) == 0x08, "GPIO DATAOUTSET offset drift");
_Static_assert(offsetof(GPIO_TypeDef, DATAOUTCLR) == 0x0C, "GPIO DATAOUTCLR offset drift");
_Static_assert(offsetof(GPIO_TypeDef, DATAOUTTGL) == 0x10, "GPIO DATAOUTTGL offset drift");
_Static_assert(offsetof(GPIO_TypeDef, PULLMODE) == 0x20, "GPIO PULLMODE offset drift");
_Static_assert(offsetof(GPIO_TypeDef, OUTMODE) == 0x24, "GPIO OUTMODE offset drift");
_Static_assert(offsetof(GPIO_TypeDef, OUTENSET) == 0x2C, "GPIO OUTENSET offset drift");
_Static_assert(offsetof(GPIO_TypeDef, OUTENCLR) == 0x30, "GPIO OUTENCLR offset drift");
_Static_assert(offsetof(GPIO_TypeDef, ALTFUNCSET) == 0x34, "GPIO ALTFUNCSET offset drift");
_Static_assert(offsetof(GPIO_TypeDef, ALTFUNCCLR) == 0x38, "GPIO ALTFUNCCLR offset drift");
#endif

/**
 * @brief Single-pin masks plus an all-pins convenience value.
 *
 * Values are bit positions, so they may be OR'd together to address a group
 * of pins in any of the mask-taking helpers below.
 */
typedef enum {
    LL_GPIO_PIN_0   = 1U << 0,          /**< Pin 0 mask. */
    LL_GPIO_PIN_1   = 1U << 1,          /**< Pin 1 mask. */
    LL_GPIO_PIN_2   = 1U << 2,          /**< Pin 2 mask. */
    LL_GPIO_PIN_3   = 1U << 3,          /**< Pin 3 mask. */
    LL_GPIO_PIN_4   = 1U << 4,          /**< Pin 4 mask. */
    LL_GPIO_PIN_5   = 1U << 5,          /**< Pin 5 mask. */
    LL_GPIO_PIN_6   = 1U << 6,          /**< Pin 6 mask. */
    LL_GPIO_PIN_7   = 1U << 7,          /**< Pin 7 mask. */
    LL_GPIO_PIN_8   = 1U << 8,          /**< Pin 8 mask. */
    LL_GPIO_PIN_9   = 1U << 9,          /**< Pin 9 mask. */
    LL_GPIO_PIN_10  = 1U << 10,         /**< Pin 10 mask. */
    LL_GPIO_PIN_11  = 1U << 11,         /**< Pin 11 mask. */
    LL_GPIO_PIN_12  = 1U << 12,         /**< Pin 12 mask. */
    LL_GPIO_PIN_13  = 1U << 13,         /**< Pin 13 mask. */
    LL_GPIO_PIN_14  = 1U << 14,         /**< Pin 14 mask. */
    LL_GPIO_PIN_15  = 1U << 15,         /**< Pin 15 mask. */
    LL_GPIO_PIN_ALL = LL_GPIO_PIN_MASK, /**< All sixteen pins. */
} ll_gpio_pin_mask_t;

/** @brief Pin direction (input or output). */
typedef enum {
    LL_GPIO_DIR_INPUT  = 0, /**< Pin drives the output enable low (Hi-Z input). */
    LL_GPIO_DIR_OUTPUT = 1, /**< Pin is driven by @c DATAOUT. */
} ll_gpio_dir_t;

/** @brief Pull-up configuration. */
typedef enum {
    LL_GPIO_PULL_NONE = 0, /**< No pull-up. */
    LL_GPIO_PULL_UP   = 1, /**< Internal pull-up enabled. */
} ll_gpio_pull_t;

/** @brief Output driver mode (encoded into @c OUTMODE, 2 bits per pin). */
typedef enum {
    LL_GPIO_DRIVE_PUSH_PULL   = 0, /**< Push-pull (totem-pole). */
    LL_GPIO_DRIVE_OPEN_DRAIN  = 1, /**< Open-drain — only drives low. */
    LL_GPIO_DRIVE_OPEN_SOURCE = 2, /**< Open-source — only drives high. */
} ll_gpio_drive_t;

/** @brief Input-qualification (glitch-filter) mode. */
typedef enum {
    LL_GPIO_QUAL_DISABLED = 0, /**< Qualification off; raw input. */
    LL_GPIO_QUAL_MODE_0   = 1, /**< Qualification on, mode 0 sampling. */
    LL_GPIO_QUAL_MODE_1   = 2, /**< Qualification on, mode 1 sampling. */
} ll_gpio_qual_t;

/** @brief Interrupt trigger condition. */
typedef enum {
    LL_GPIO_TRIG_LEVEL_LOW    = 0, /**< Active-low level trigger. */
    LL_GPIO_TRIG_LEVEL_HIGH   = 1, /**< Active-high level trigger. */
    LL_GPIO_TRIG_EDGE_FALLING = 2, /**< Falling-edge trigger. */
    LL_GPIO_TRIG_EDGE_RISING  = 3, /**< Rising-edge trigger. */
    LL_GPIO_TRIG_EDGE_BOTH    = 4, /**< Trigger on either edge. */
} ll_gpio_trig_t;

/**
 * @name Data read/write
 * @{
 */

/**
 * @brief Read all 16 input pins of a port.
 * @param gpio  GPIO port base.
 * @return Raw input value, masked to 16 bits.
 */
static inline uint32_t ll_gpio_read(const GPIO_TypeDef *gpio)
{
    return gpio->DATA & LL_GPIO_PIN_MASK;
}

/**
 * @brief Read the current output-register value (not the pin level).
 * @param gpio  GPIO port base.
 * @return Last value written to @c DATAOUT, masked to 16 bits.
 */
static inline uint32_t ll_gpio_read_output(const GPIO_TypeDef *gpio)
{
    return gpio->DATAOUT & LL_GPIO_PIN_MASK;
}

/**
 * @brief Read a single pin (or the OR of any pins in @p mask).
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to test.
 * @return @c true if any masked pin reads high, @c false otherwise.
 */
static inline bool ll_gpio_read_pin(const GPIO_TypeDef *gpio, uint32_t mask)
{
    return (gpio->DATA & mask) != 0U;
}

/**
 * @brief Write all 16 output pins at once.
 * @param gpio  GPIO port base.
 * @param value New @c DATAOUT value (low 16 bits used).
 */
static inline void ll_gpio_write(GPIO_TypeDef *gpio, uint32_t value)
{
    gpio->DATAOUT = value & LL_GPIO_PIN_MASK;
}

/**
 * @brief Atomically set the pins given by @p mask high.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to drive high.
 */
static inline void ll_gpio_set(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->DATAOUTSET = mask;
}

/**
 * @brief Atomically clear the pins given by @p mask low.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to drive low.
 */
static inline void ll_gpio_clear(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->DATAOUTCLR = mask;
}

/**
 * @brief Atomically toggle the pins given by @p mask via the dedicated XOR register.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to toggle.
 * @note Atomic against concurrent set/clear from another context, unlike a RMW on @c DATAOUT.
 */
static inline void ll_gpio_toggle(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->DATAOUTTGL = mask;
}

/** @} */

/**
 * @name Direction control
 * @{
 */

/**
 * @brief Configure the masked pins as inputs.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to switch to input.
 */
static inline void ll_gpio_set_dir_input(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->OUTENCLR = mask;
}

/**
 * @brief Configure the masked pins as outputs.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to switch to output.
 */
static inline void ll_gpio_set_dir_output(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->OUTENSET = mask;
}

/**
 * @brief Configure direction of the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to configure.
 * @param dir   Direction to apply.
 */
static inline void ll_gpio_set_dir(GPIO_TypeDef *gpio, uint32_t mask, ll_gpio_dir_t dir)
{
    if (dir == LL_GPIO_DIR_OUTPUT) {
        gpio->OUTENSET = mask;
    } else {
        gpio->OUTENCLR = mask;
    }
}

/** @} */

/**
 * @name Pad configuration
 * @{
 */

/**
 * @brief Enable or disable the internal pull-up on the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to configure.
 * @param pull  Pull setting to apply.
 */
static inline void ll_gpio_set_pull(GPIO_TypeDef *gpio, uint32_t mask, ll_gpio_pull_t pull)
{
    if (pull == LL_GPIO_PULL_UP) {
        gpio->PULLMODE |= mask;
    } else {
        gpio->PULLMODE &= ~mask;
    }
}

/**
 * @brief Set the output driver mode on the masked pins.
 *
 * Walks @p mask one bit at a time and writes the 2-bit @c OUTMODE field
 * for each selected pin.
 *
 * @param gpio   GPIO port base.
 * @param mask   Pin mask to configure.
 * @param drive  Driver mode (push-pull, open-drain, open-source).
 */
static inline void ll_gpio_set_drive(GPIO_TypeDef *gpio, uint32_t mask, ll_gpio_drive_t drive)
{
    _Static_assert((uint32_t)LL_GPIO_DRIVE_OPEN_SOURCE <= 0x3u, "ll_gpio_drive_t must fit in 2 bits");

    uint32_t reg = gpio->OUTMODE;
    while (mask) {
        const uint32_t pin   = (uint32_t)__builtin_ctz(mask);
        const uint32_t shift = pin * 2u;
        reg                  = (reg & ~(0x3u << shift)) | (((uint32_t)drive & 0x3u) << shift);
        mask &= mask - 1u;
    }
    gpio->OUTMODE = reg;
}

/** @} */

/**
 * @name Alternate function
 * @{
 */

/**
 * @brief Switch the masked pins to their alternate-function source.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to switch to alt-func.
 * @note Use @ref ll_gpio_set_altfunc first to pick the AF index.
 */
static inline void ll_gpio_altfunc_enable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->ALTFUNCSET = mask;
}

/**
 * @brief Switch the masked pins back to GPIO mode.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to return to GPIO mode.
 */
static inline void ll_gpio_altfunc_disable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->ALTFUNCCLR = mask;
}

/**
 * @brief Select the alternate-function index for a single pin.
 *
 * Hides the per-SoC encoding difference: the K1921VG1T/3T/5T/7T family uses
 * two split 4-bit-per-pin registers (@c ALTFUNCNUM0 / @c ALTFUNCNUM1) while
 * K1921VG015 packs all pins into a single 2-bit-per-pin register
 * (@c ALTFUNCNUM).
 *
 * @param gpio  GPIO port base.
 * @param pin   Pin index in @c [0, LL_GPIO_PIN_COUNT).
 * @param af    Alternate-function index; clamped to width by the encoding.
 */
static inline void ll_gpio_set_altfunc(GPIO_TypeDef *gpio, uint32_t pin, uint8_t af)
{
    _Static_assert(LL_GPIO_PIN_COUNT == 16U, "ll_gpio_set_altfunc: layout below assumes 16 pins/port");
    LL_ASSERT(gpio != NULL);
    LL_ASSERT(pin < LL_GPIO_PIN_COUNT);
    LL_ASSERT(af <= LL_GPIO_ALTFUNC_MAX);

#if LL_GPIO_HAS_SPLIT_ALTFUNC
    if (pin < 8u) {
        const uint32_t shift = pin * 4u;
        gpio->ALTFUNCNUM0    = (gpio->ALTFUNCNUM0 & ~(0xFU << shift)) | (((uint32_t)af & 0xFU) << shift);
    } else if (pin < LL_GPIO_PIN_COUNT) {
        const uint32_t shift = (pin - 8u) * 4U;
        gpio->ALTFUNCNUM1    = (gpio->ALTFUNCNUM1 & ~(0xFU << shift)) | (((uint32_t)af & 0xFU) << shift);
    }
#else
    if (pin < LL_GPIO_PIN_COUNT) {
        const uint32_t shift = pin * 2U;
        gpio->ALTFUNCNUM     = (gpio->ALTFUNCNUM & ~(0x3U << shift)) | (((uint32_t)af & 0x3U) << shift);
    }
#endif
}

/** @} */

/**
 * @name Input synchronizer and qualification
 * @{
 */

/**
 * @brief Enable the input synchronizer on the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to configure.
 */
static inline void ll_gpio_sync_enable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->SYNCSET = mask;
}

/**
 * @brief Disable the input synchronizer on the masked pins.
 *
 * Required for capture loops that sample on a fast external clock edge
 * (e.g. OV7670 PCLK), where the synchronizer adds an unacceptable delay
 * skew.
 *
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to configure.
 */
static inline void ll_gpio_sync_disable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->SYNCCLR = mask;
}

/**
 * @brief Configure the input qualification (glitch-filter) on the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to configure.
 * @param qual  Qualification mode.
 */
static inline void ll_gpio_set_qual(GPIO_TypeDef *gpio, uint32_t mask, ll_gpio_qual_t qual)
{
    switch (qual) {
    case LL_GPIO_QUAL_DISABLED:
        gpio->QUALCLR     = mask;
        gpio->QUALMODECLR = mask;
        break;
    case LL_GPIO_QUAL_MODE_0:
        gpio->QUALMODECLR = mask;
        gpio->QUALSET     = mask;
        break;
    case LL_GPIO_QUAL_MODE_1:
        gpio->QUALMODESET = mask;
        gpio->QUALSET     = mask;
        break;
    }
}

/**
 * @brief Set the sampling-period divider used by input qualification.
 * @param gpio    GPIO port base.
 * @param period  20-bit divider value; high bits are masked off.
 */
static inline void ll_gpio_set_qual_sample_period(GPIO_TypeDef *gpio, uint32_t period)
{
    gpio->QUALSAMPLE = period & 0x000FFFFFu;
}

/** @} */

/**
 * @name Pin interrupts
 * @{
 */

/**
 * @brief Enable per-pin interrupt generation.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to enable.
 */
static inline void ll_gpio_int_enable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->INTENSET = mask;
}

/**
 * @brief Disable per-pin interrupt generation.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to disable.
 */
static inline void ll_gpio_int_disable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->INTENCLR = mask;
}

/**
 * @brief Program the trigger condition for the masked pins.
 *
 * Writes the @c INTTYPE / @c INTPOL / @c INTEDGE register triplet according
 * to the requested mode.
 *
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to configure.
 * @param trig  Trigger condition.
 */
static inline void ll_gpio_int_set_trigger(GPIO_TypeDef *gpio, uint32_t mask, ll_gpio_trig_t trig)
{
    switch (trig) {
    case LL_GPIO_TRIG_LEVEL_LOW:
        gpio->INTEDGECLR = mask;
        gpio->INTTYPESET = mask;
        gpio->INTPOLCLR  = mask;
        break;
    case LL_GPIO_TRIG_LEVEL_HIGH:
        gpio->INTEDGECLR = mask;
        gpio->INTTYPESET = mask;
        gpio->INTPOLSET  = mask;
        break;
    case LL_GPIO_TRIG_EDGE_FALLING:
        gpio->INTEDGECLR = mask;
        gpio->INTTYPECLR = mask;
        gpio->INTPOLCLR  = mask;
        break;
    case LL_GPIO_TRIG_EDGE_RISING:
        gpio->INTEDGECLR = mask;
        gpio->INTTYPECLR = mask;
        gpio->INTPOLSET  = mask;
        break;
    case LL_GPIO_TRIG_EDGE_BOTH:
        gpio->INTTYPECLR = mask;
        gpio->INTEDGESET = mask;
        break;
    }
}

/**
 * @brief Read the pending-interrupt status register.
 * @param gpio  GPIO port base.
 * @return Pending-interrupt bitmap, masked to 16 bits.
 */
static inline uint32_t ll_gpio_int_get_status(const GPIO_TypeDef *gpio)
{
    return gpio->INTSTATUS & LL_GPIO_PIN_MASK;
}

/**
 * @brief Acknowledge pending interrupts (write-1-to-clear).
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to clear.
 */
static inline void ll_gpio_int_clear(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->INTSTATUS = mask;
}

/** @} */

/**
 * @name ADC start-of-conversion routing
 * @{
 */

/**
 * @brief Enable ADC start-of-conversion triggering from the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to route to ADC SoC.
 */
static inline void ll_gpio_adc_soc_enable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->ADCSOCSET = mask;
}

/**
 * @brief Disable ADC start-of-conversion triggering from the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to remove from ADC SoC.
 */
static inline void ll_gpio_adc_soc_disable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->ADCSOCCLR = mask;
}

/** @} */

/**
 * @name DMA request routing
 *
 * The Syntacore-based SoCs (VG1T/3T/5T/7T) split DMA requests into
 * transmit and receive directions; K1921VG015 has a single request register.
 * The matching subset of helpers is enabled at compile time via
 * @c LL_GPIO_HAS_TXRX_DMA.
 * @{
 */

#if LL_GPIO_HAS_TXRX_DMA
/**
 * @brief Enable transmit-direction DMA requests for the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to enable.
 * @note Only available when @c LL_GPIO_HAS_TXRX_DMA is 1.
 */
static inline void ll_gpio_dma_tx_enable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->DMATXREQSET = mask;
}

/**
 * @brief Disable transmit-direction DMA requests for the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to disable.
 * @note Only available when @c LL_GPIO_HAS_TXRX_DMA is 1.
 */
static inline void ll_gpio_dma_tx_disable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->DMATXREQCLR = mask;
}

/**
 * @brief Enable receive-direction DMA requests for the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to enable.
 * @note Only available when @c LL_GPIO_HAS_TXRX_DMA is 1.
 */
static inline void ll_gpio_dma_rx_enable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->DMARXREQSET = mask;
}

/**
 * @brief Disable receive-direction DMA requests for the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to disable.
 * @note Only available when @c LL_GPIO_HAS_TXRX_DMA is 1.
 */
static inline void ll_gpio_dma_rx_disable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->DMARXREQCLR = mask;
}
#else
/**
 * @brief Enable DMA requests for the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to enable.
 * @note Only available when @c LL_GPIO_HAS_TXRX_DMA is 0 (single request register).
 */
static inline void ll_gpio_dma_enable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->DMAREQSET = mask;
}

/**
 * @brief Disable DMA requests for the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to disable.
 * @note Only available when @c LL_GPIO_HAS_TXRX_DMA is 0.
 */
static inline void ll_gpio_dma_disable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->DMAREQCLR = mask;
}
#endif

/** @} */

#if LL_GPIO_HAS_RXEV
/**
 * @name Receive-event routing (VG1T family only)
 * @{
 */

/**
 * @brief Enable RXEV signalling for the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to enable.
 * @note Only available when @c LL_GPIO_HAS_RXEV is 1.
 */
static inline void ll_gpio_rxev_enable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->RXEVSET = mask;
}

/**
 * @brief Disable RXEV signalling for the masked pins.
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to disable.
 * @note Only available when @c LL_GPIO_HAS_RXEV is 1.
 */
static inline void ll_gpio_rxev_disable(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->RXEVCLR = mask;
}
/** @} */
#endif

/**
 * @name Configuration lock
 *
 * Three-step protection scheme: write @ref LL_GPIO_LOCK_KEY to @c LOCKKEY to
 * unlock the lock register set, then mark individual pins as locked via
 * @ref ll_gpio_lock_pins. Writing @c 0 to @c LOCKKEY re-locks the set.
 * @{
 */

/**
 * @brief Unlock the lock register set so individual pin locks can be edited.
 * @param gpio  GPIO port base.
 */
static inline void ll_gpio_lock_unlock_access(GPIO_TypeDef *gpio)
{
    gpio->LOCKKEY = LL_GPIO_LOCK_KEY;
}

/**
 * @brief Re-lock the lock register set.
 * @param gpio  GPIO port base.
 */
static inline void ll_gpio_lock_relock_access(GPIO_TypeDef *gpio)
{
    gpio->LOCKKEY = 0u;
}

/**
 * @brief Read the raw @c LOCKKEY register.
 *
 * The K1921VG015 header does not expose the @c LOCKSTAT field separately, so
 * the lock state is read straight from the same address. The low bit
 * indicates whether the register set is currently writable.
 *
 * @param gpio  GPIO port base.
 * @return Raw @c LOCKKEY value.
 */
static inline uint32_t ll_gpio_lock_get_status(const GPIO_TypeDef *gpio)
{
    return gpio->LOCKKEY;
}

/**
 * @brief Mark the masked pins as locked (config no longer writable).
 *
 * The lock register set must first be unlocked with
 * @ref ll_gpio_lock_unlock_access.
 *
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to lock.
 */
static inline void ll_gpio_lock_pins(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->LOCKSET = mask;
}

/**
 * @brief Clear the lock bit for the masked pins.
 *
 * The lock register set must first be unlocked with
 * @ref ll_gpio_lock_unlock_access.
 *
 * @param gpio  GPIO port base.
 * @param mask  Pin mask to unlock.
 */
static inline void ll_gpio_unlock_pins(GPIO_TypeDef *gpio, uint32_t mask)
{
    gpio->LOCKCLR = mask;
}

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */ /* end of ll_gpio group */
