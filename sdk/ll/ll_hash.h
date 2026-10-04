/**
 * @file ll_hash.h
 * @brief Low-level hash-engine driver for the K1921VG family.
 *
 * Hardware hash unit (ST-style HASH IP) is available on K1921VG015,
 * K1921VG1T and K1921VG3T. K1921VG5T and K1921VG7T do not ship this
 * peripheral and including this header on those targets is a compile
 * error.
 *
 * Supported algorithms: SHA-1, MD5, SHA-224, SHA-256 — selectable via
 * @c CR.ALGO. The block also has an HMAC mode (@c CR.MODE) and a 2-bit
 * datatype selector (@c CR.DATATYPE) that controls how each 32-bit
 * write into @c DATAIN is unpacked: word, half-word, byte or
 * bit-string. The host streams the message by writing words into
 * @c DATAIN; for the very last word it programs @c STR.NBLW with the
 * number of valid *bits* (0..31) and writes @c STR.DCAL to start the
 * final digest computation. The digest is read back from @c HR[0..N-1]
 * (N depends on algorithm: 5 for SHA-1, 4 for MD5, 7 for SHA-224, 8
 * for SHA-256).
 *
 * Typical synchronous use:
 * @code
 *     ll_rcu_peripheral_init(LL_RCU_HASH);
 *     const ll_hash_cfg_t cfg = {
 *         .algo     = LL_HASH_ALGO_SHA256,
 *         .mode     = LL_HASH_MODE_HASH,
 *         .datatype = LL_HASH_DATATYPE_BYTE,
 *     };
 *     ll_hash_init(HASH, &cfg);
 *     ll_hash_write_buffer(HASH, msg, msg_len);
 *     ll_hash_start_digest(HASH, last_word_valid_bits);
 *     ll_hash_wait_done(HASH);
 *     uint32_t digest[8];
 *     ll_hash_read_digest(HASH, digest, LL_HASH_DIGEST_WORDS_SHA256);
 * @endcode
 *
 * @defgroup ll_hash LL HASH
 * @{
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <soc.h>

#if !defined(K1921VG015) && !defined(K1921VG1T) && !defined(K1921VG3T)
#error "ll_hash.h: this SoC does not have a HASH peripheral"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
_Static_assert(offsetof(HASH_TypeDef, CR) == 0x00, "HASH CR offset drift");
_Static_assert(offsetof(HASH_TypeDef, DATAIN) == 0x04, "HASH DATAIN offset drift");
_Static_assert(offsetof(HASH_TypeDef, STR) == 0x08, "HASH STR offset drift");
_Static_assert(offsetof(HASH_TypeDef, IMR) == 0x0C, "HASH IMR offset drift");
_Static_assert(offsetof(HASH_TypeDef, SR) == 0x10, "HASH SR offset drift");
_Static_assert(offsetof(HASH_TypeDef, HR) == 0x40, "HASH HR[] offset drift");
#endif

/** @brief Algorithm selection (encoded into @c CR.ALGO). */
typedef enum {
    LL_HASH_ALGO_SHA1   = 0, /**< SHA-1, 160-bit digest (5 words). */
    LL_HASH_ALGO_MD5    = 1, /**< MD5, 128-bit digest (4 words). */
    LL_HASH_ALGO_SHA224 = 2, /**< SHA-224, 224-bit digest (7 words). */
    LL_HASH_ALGO_SHA256 = 3, /**< SHA-256, 256-bit digest (8 words). */
} ll_hash_algo_t;

/** @brief Operating mode (encoded into @c CR.MODE). */
typedef enum {
    LL_HASH_MODE_HASH = 0, /**< Plain hash. */
    LL_HASH_MODE_HMAC = 1, /**< HMAC; key driven through @c DATAIN before payload. */
} ll_hash_mode_t;

/**
 * @brief Input-data granularity (encoded into @c CR.DATATYPE).
 *
 * Each 32-bit write into @c DATAIN is decomposed into the chosen
 * unit count. Byte order within the word follows the manual's
 * convention: @ref LL_HASH_DATATYPE_BYTE feeds bytes most-significant
 * first.
 */
typedef enum {
    LL_HASH_DATATYPE_WORD  = 0, /**< One 32-bit word per @c DATAIN write. */
    LL_HASH_DATATYPE_HWORD = 1, /**< Two 16-bit halves per @c DATAIN write. */
    LL_HASH_DATATYPE_BYTE  = 2, /**< Four bytes per @c DATAIN write. */
    LL_HASH_DATATYPE_BIT   = 3, /**< Bit-string. */
} ll_hash_datatype_t;

/**
 * @name Digest word counts
 * Use as @c count for @ref ll_hash_read_digest.
 * @{
 */
#define LL_HASH_DIGEST_WORDS_MD5    4U /**< 128 bits / 32. */
#define LL_HASH_DIGEST_WORDS_SHA1   5U /**< 160 bits / 32. */
#define LL_HASH_DIGEST_WORDS_SHA224 7U /**< 224 bits / 32. */
#define LL_HASH_DIGEST_WORDS_SHA256 8U /**< 256 bits / 32. */
/** @} */

/**
 * @brief Composite configuration consumed by @ref ll_hash_init.
 */
typedef struct {
    ll_hash_algo_t algo;         /**< Algorithm. */
    ll_hash_mode_t mode;         /**< Hash or HMAC. */
    ll_hash_datatype_t datatype; /**< Input granularity. */
    bool long_key;               /**< For HMAC: set if the key is longer than the block size. */
} ll_hash_cfg_t;

/**
 * @name Configuration
 * @{
 */

/**
 * @brief Program the control register and pulse @c CR.INIT.
 *
 * Writes @c ALGO / @c MODE / @c DATATYPE / @c LKEY in @c CR, then sets
 * @c CR.INIT to load the IV into the message digest. After this call
 * the host can start streaming via @ref ll_hash_write_word /
 * @ref ll_hash_write_buffer.
 *
 * @param hash HASH instance.
 * @param cfg  Configuration; ignored if NULL.
 */
static inline void ll_hash_init(HASH_TypeDef *hash, const ll_hash_cfg_t *cfg)
{
    if (!cfg) {
        return;
    }

    uint32_t cr = hash->CR & ~(HASH_CR_ALGO_Msk | HASH_CR_MODE_Msk | HASH_CR_DATATYPE_Msk | HASH_CR_LKEY_Msk);
    cr |= ((uint32_t)cfg->algo << HASH_CR_ALGO_Pos) & HASH_CR_ALGO_Msk;
    cr |= ((uint32_t)cfg->mode << HASH_CR_MODE_Pos) & HASH_CR_MODE_Msk;
    cr |= ((uint32_t)cfg->datatype << HASH_CR_DATATYPE_Pos) & HASH_CR_DATATYPE_Msk;
    if (cfg->long_key) {
        cr |= HASH_CR_LKEY_Msk;
    }
    hash->CR = cr;

    /* INIT is self-clearing; setting it loads the algorithm's IV. */
    hash->CR = cr | HASH_CR_INIT_Msk;
}

/** @} */

/**
 * @name Streaming input
 * @{
 */

/**
 * @brief Push one 32-bit word into the engine.
 * @param hash HASH instance.
 * @param word Word to consume.
 */
static inline void ll_hash_write_word(HASH_TypeDef *hash, uint32_t word)
{
    hash->DATAIN = word;
}

/**
 * @brief Push an array of 32-bit words into the engine.
 * @param hash  HASH instance.
 * @param words Pointer to source words.
 * @param count Number of words.
 */
static inline void ll_hash_write_words(HASH_TypeDef *hash, const uint32_t *words, size_t count)
{
    if (!words) {
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        hash->DATAIN = words[i];
    }
}

/**
 * @brief Stream a byte buffer into the engine.
 *
 * Bytes are packed little-endian into 32-bit words and written to
 * @c DATAIN. A trailing partial word is padded with zeros; the host
 * must still program the correct bit count for the *last* word via
 * @ref ll_hash_start_digest so the engine drops the padding bits.
 *
 * This helper is useful with @ref LL_HASH_DATATYPE_BYTE (the most
 * common configuration for hashing arbitrary octet strings).
 *
 * @param hash HASH instance.
 * @param data Source buffer.
 * @param len  Length in bytes.
 */
static inline void ll_hash_write_buffer(HASH_TypeDef *hash, const uint8_t *data, size_t len)
{
    if (!data) {
        return;
    }
    size_t full_words = len / 4U;
    for (size_t i = 0; i < full_words; ++i) {
        uint32_t w = ((uint32_t)data[i * 4U + 0]) | ((uint32_t)data[i * 4U + 1] << 8) |
                     ((uint32_t)data[i * 4U + 2] << 16) | ((uint32_t)data[i * 4U + 3] << 24);
        hash->DATAIN = w;
    }
    size_t rem = len - full_words * 4U;
    if (rem > 0U) {
        uint32_t w = 0;
        for (size_t i = 0; i < rem; ++i) {
            w |= (uint32_t)data[full_words * 4U + i] << (i * 8U);
        }
        hash->DATAIN = w;
    }
}

/** @} */

/**
 * @name Digest computation
 * @{
 */

/**
 * @brief Kick off the final digest pass.
 *
 * Writes @c STR.NBLW with the number of valid bits in the last
 * @c DATAIN write (0..31; 0 means the message ended on a word boundary)
 * and then asserts @c STR.DCAL, which triggers padding + finalization.
 * The host should poll @ref ll_hash_is_done or wait for @c DCIS to
 * fire before reading @c HR[].
 *
 * @param hash             HASH instance.
 * @param last_word_bits   Valid-bit count in the trailing @c DATAIN word (0..31).
 */
static inline void ll_hash_start_digest(HASH_TypeDef *hash, uint8_t last_word_bits)
{
    uint32_t str = ((uint32_t)(last_word_bits & 0x1FU) << HASH_STR_NBLW_Pos) & HASH_STR_NBLW_Msk;
    hash->STR    = str | HASH_STR_DCAL_Msk;
}

/**
 * @brief Check whether the engine has finished (SR.DCIS=1 and SR.BUSY=0).
 * @param hash HASH instance.
 * @return @c true if the digest is ready to be read.
 */
static inline bool ll_hash_is_done(const HASH_TypeDef *hash)
{
    uint32_t sr = hash->SR;
    return ((sr & HASH_SR_DCIS_Msk) != 0U) && ((sr & HASH_SR_BUSY_Msk) == 0U);
}

/**
 * @brief Spin until @ref ll_hash_is_done returns @c true.
 * @param hash HASH instance.
 */
static inline void ll_hash_wait_done(const HASH_TypeDef *hash)
{
    while (!ll_hash_is_done(hash)) {}
}

/**
 * @brief Check whether the engine is currently processing data.
 * @param hash HASH instance.
 * @return @c true if @c SR.BUSY is set.
 */
static inline bool ll_hash_busy(const HASH_TypeDef *hash)
{
    return (hash->SR & HASH_SR_BUSY_Msk) != 0U;
}

/**
 * @brief Copy the digest out of @c HR[].
 *
 * @c count must match the algorithm in use — pass one of the
 * @c LL_HASH_DIGEST_WORDS_* constants. Words are returned in their
 * native @c HR[i] order.
 *
 * @param hash  HASH instance.
 * @param out   Destination array of at least @c count words.
 * @param count Number of words to read (clamped to 8).
 */
static inline void ll_hash_read_digest(const HASH_TypeDef *hash, uint32_t *out, size_t count)
{
    if (!out) {
        return;
    }

    if (count > 8U) {
        count = 8U;
    }

    for (size_t i = 0; i < count; ++i) {
        out[i] = hash->HR[i];
    }
}

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */ /* end of ll_hash group */
