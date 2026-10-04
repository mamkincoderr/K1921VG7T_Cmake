/**
 * @file ll_crc.h
 * @brief Low-level CRC engine driver for the K1921VG family.
 *
 * Hardware CRC unit is present on K1921VG015 (two instances: @c CRC0 and
 * @c CRC1), K1921VG1T (single @c CRC) and K1921VG3T (single @c CRC).
 * K1921VG5T and K1921VG7T do not ship a CRC peripheral and including this
 * header on those targets is a compile error.
 *
 * The unit takes 32-bit words written to @c DR, runs them through a
 * programmable polynomial of width 7, 8, 16, or 32 bits, and exposes the
 * running remainder via @c POST.
 *
 * @defgroup ll_crc LL CRC
 * @{
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ll_assert.h>
#include <soc.h>

#if defined(K1921VG015)
#define LL_CRC_HAS_REV_IN     0
#define LL_CRC_HAS_DR_SUBWORD 1
#elif defined(K1921VG1T)
#define LL_CRC_HAS_REV_IN     1
#define LL_CRC_HAS_DR_SUBWORD 0
#elif defined(K1921VG3T)
#define LL_CRC_HAS_REV_IN     0
#define LL_CRC_HAS_DR_SUBWORD 0
#else
#error "ll_crc.h: this SoC does not have a CRC peripheral"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

_Static_assert(offsetof(CRC_TypeDef, DR) == 0x00, "CRC DR offset drift");
_Static_assert(offsetof(CRC_TypeDef, POST) == 0x04, "CRC POST offset drift");
_Static_assert(offsetof(CRC_TypeDef, CR) == 0x08, "CRC CR offset drift");
_Static_assert(offsetof(CRC_TypeDef, INIT) == 0x0C, "CRC INIT offset drift");
_Static_assert(offsetof(CRC_TypeDef, POL) == 0x10, "CRC POL offset drift");

#endif

#if LL_CRC_HAS_REV_IN

#ifndef CRC_CR_REV_IN_Pos
#define CRC_CR_REV_IN_Pos 5U
#endif

#ifndef CRC_CR_REV_IN_Msk
#define CRC_CR_REV_IN_Msk (0x3U << CRC_CR_REV_IN_Pos)
#endif

#endif

/** @brief Width of the CRC polynomial encoded in @c CR.POLYSIZE. */
typedef enum {
    LL_CRC_POLYSIZE_32 = 0,
    LL_CRC_POLYSIZE_16 = 1,
    LL_CRC_POLYSIZE_8  = 2,
    LL_CRC_POLYSIZE_7  = 3,
} ll_crc_polysize_t;

#if LL_CRC_HAS_REV_IN

/**
 * @brief Input bit-reversal mode encoded in @c CR.REV_IN.
 *
 * The names LL_CRC_INPUT_* are retained for API compatibility.
 */
typedef enum {
    LL_CRC_INPUT_WORD     = 0,
    LL_CRC_INPUT_BYTE     = 1,
    LL_CRC_INPUT_HALFWORD = 2,
    LL_CRC_INPUT_BIT      = 3,
} ll_crc_input_t;

#endif

/**
 * @name Configuration
 * @{
 */

/**
 * @brief Set the CRC polynomial value.
 *
 * @param crc  CRC instance.
 * @param poly Polynomial value.
 */
static inline void ll_crc_set_polynomial(CRC_TypeDef *crc, uint32_t poly)
{
    LL_ASSERT(crc != NULL);
    crc->POL = poly;
}

/**
 * @brief Set the initial accumulator value.
 *
 * The value is loaded into @c DR by the next reset operation.
 *
 * @param crc  CRC instance.
 * @param init Initial accumulator value.
 */
static inline void ll_crc_set_init_value(CRC_TypeDef *crc, uint32_t init)
{
    LL_ASSERT(crc != NULL);
    crc->INIT = init;
}

/**
 * @brief Set the polynomial width.
 *
 * @param crc  CRC instance.
 * @param size Polynomial width.
 */
static inline void ll_crc_set_polysize(CRC_TypeDef *crc, ll_crc_polysize_t size)
{
    LL_ASSERT(crc != NULL);

    crc->CR = (crc->CR & ~CRC_CR_POLYSIZE_Msk) | (((uint32_t)size << CRC_CR_POLYSIZE_Pos) & CRC_CR_POLYSIZE_Msk);
}

/**
 * @brief Enable or disable output XOR processing.
 *
 * @param crc    CRC instance.
 * @param enable @c true to enable XOR with @c 0xFFFFFFFF.
 */
static inline void ll_crc_set_xor_output(CRC_TypeDef *crc, bool enable)
{
    LL_ASSERT(crc != NULL);

    if (enable) {
        crc->CR |= CRC_CR_XOROUT_Msk;
    } else {
        crc->CR &= ~CRC_CR_XOROUT_Msk;
    }
}

/**
 * @brief Reload the accumulator from @c INIT.
 *
 * @param crc CRC instance.
 */
static inline void ll_crc_reset(CRC_TypeDef *crc)
{
    LL_ASSERT(crc != NULL);

    crc->CR |= CRC_CR_RESET_Msk;
    crc->CR &= ~CRC_CR_RESET_Msk;
}

#if LL_CRC_HAS_REV_IN

/**
 * @brief Set the input bit-reversal mode.
 *
 * @param crc   CRC instance.
 * @param width Input bit-reversal mode.
 */
static inline void ll_crc_set_input_width(CRC_TypeDef *crc, ll_crc_input_t width)
{
    LL_ASSERT(crc != NULL);

    crc->CR = (crc->CR & ~CRC_CR_REV_IN_Msk) | (((uint32_t)width << CRC_CR_REV_IN_Pos) & CRC_CR_REV_IN_Msk);
}

#endif

/** @} */

/**
 * @name Data input / output
 * @{
 */

/**
 * @brief Feed one 32-bit word into the CRC accumulator.
 *
 * @param crc   CRC instance.
 * @param value Input word.
 */
static inline void ll_crc_write_word(CRC_TypeDef *crc, uint32_t value)
{
    LL_ASSERT(crc != NULL);
    crc->DR = value;
}

#if LL_CRC_HAS_DR_SUBWORD

/**
 * @brief Feed one byte into the CRC accumulator.
 *
 * @param crc CRC instance.
 * @param b   Input byte.
 */
static inline void ll_crc_write_byte(CRC_TypeDef *crc, uint8_t b)
{
    LL_ASSERT(crc != NULL);
    crc->DR8 = b;
}

/**
 * @brief Feed one half-word into the CRC accumulator.
 *
 * @param crc CRC instance.
 * @param h   Input half-word.
 */
static inline void ll_crc_write_halfword(CRC_TypeDef *crc, uint16_t h)
{
    LL_ASSERT(crc != NULL);
    crc->DR16 = h;
}

#endif

/**
 * @brief Feed an array of 32-bit words into the CRC accumulator.
 *
 * @param crc   CRC instance.
 * @param words Input word buffer.
 * @param count Number of words.
 */
static inline void ll_crc_write_buffer(CRC_TypeDef *crc, const uint32_t *words, size_t count)
{
    LL_ASSERT(crc != NULL);
    LL_ASSERT(words != NULL || count == 0U);

    for (size_t i = 0; i < count; ++i) {
        crc->DR = words[i];
    }
}

/**
 * @brief Read the post-processed CRC value.
 *
 * @param crc CRC instance.
 * @return Post-processed CRC value.
 */
static inline uint32_t ll_crc_read(const CRC_TypeDef *crc)
{
    LL_ASSERT(crc != NULL);
    return crc->POST;
}

/**
 * @brief Read the raw accumulator value.
 *
 * @param crc CRC instance.
 * @return Raw CRC accumulator value.
 */
static inline uint32_t ll_crc_read_raw(const CRC_TypeDef *crc)
{
    LL_ASSERT(crc != NULL);
    return crc->DR;
}

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */ /* end of ll_crc group */
