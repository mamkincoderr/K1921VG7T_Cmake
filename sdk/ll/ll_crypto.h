/**
 * @file ll_crypto.h
 * @brief Low-level driver for the on-chip CRYPTO engine.
 *
 * Hardware symmetric-cipher block available on K1921VG015, K1921VG1T
 * and K1921VG3T. K1921VG5T and K1921VG7T do not ship this peripheral
 * and including this header on those targets is a compile error.
 *
 * Supported algorithms (encoded in @c CONTROL.ALGORITHM):
 *   - AES-128 / AES-256
 *   - Magma (GOST 28147-89 / 34.12-2018, 64-bit block)
 *   - Kuznechik (GOST 34.12-2018, 128-bit block)
 *
 * Supported modes of operation (@c CONTROL.MODE): ECB, CBC, CTR, GCM.
 * GCM has a per-phase state machine via @c CONTROL.GCM_PHASE
 * (INIT/HEADER/PAYLOAD/LAST_BLOCK). K1921VG015 additionally exposes
 * dedicated @c GCM_HASH[4] and @c GCM_TAG[4] register banks; that
 * capability is signalled by @c LL_CRYPTO_HAS_GCM_REGS.
 *
 * Single-block synchronous use (AES-128 ECB encrypt):
 * @code
 *     ll_rcu_peripheral_init(LL_RCU_CRYPTO);
 *     ll_crypto_set_key(CRYPTO, key, 4);   // 128-bit key → 4 words
 *
 *     const ll_crypto_cfg_t cfg = {
 *         .algorithm = LL_CRYPTO_ALG_AES_128,
 *         .mode      = LL_CRYPTO_MODE_ECB,
 *         .direction = LL_CRYPTO_DIR_ENCRYPT,
 *     };
 *     ll_crypto_configure(CRYPTO, &cfg);
 *
 *     ll_crypto_update_key(CRYPTO);                 // load KEY into engine
 *     ll_crypto_wait_keys_ready(CRYPTO);
 *
 *     ll_crypto_load_text_in(CRYPTO, plaintext);    // 4×u32
 *     ll_crypto_start(CRYPTO);
 *     ll_crypto_wait_out_valid(CRYPTO);
 *     ll_crypto_read_text_out(CRYPTO, ciphertext);
 * @endcode
 *
 * @defgroup ll_crypto LL CRYPTO
 * @{
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <soc.h>

#if defined(K1921VG015)
/** @brief 1 if the SoC exposes the dedicated @c GCM_HASH[4]/@c GCM_TAG[4] registers. */
#define LL_CRYPTO_HAS_GCM_REGS 1
#elif defined(K1921VG1T) || defined(K1921VG3T)
#define LL_CRYPTO_HAS_GCM_REGS 0
#else
#error "ll_crypto.h: this SoC does not have a CRYPTO peripheral"
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/* On VG3T the IV / TEXT_IN / KEY / TEXT_OUT arrays are wrapped in
 * intermediate single-field structs, so word access goes through a
 * trailing underscore member. The other two SoCs expose plain
 * `__IO uint32_t` arrays. Hide that asymmetry behind these macros. */
#if defined(K1921VG3T)
#define _LL_CRYPTO_IV_W(c, i, v) ((c)->IV[(i)].IV_ = (v))
#define _LL_CRYPTO_TI_W(c, i, v) ((c)->TEXT_IN[(i)].TEXT_IN_ = (v))
#define _LL_CRYPTO_KE_W(c, i, v) ((c)->KEY[(i)].KEY_ = (v))
#define _LL_CRYPTO_TO_R(c, i)    ((c)->TEXT_OUT[(i)].TEXT_OUT_)
#else
#define _LL_CRYPTO_IV_W(c, i, v) ((c)->IV[(i)] = (v))
#define _LL_CRYPTO_TI_W(c, i, v) ((c)->TEXT_IN[(i)] = (v))
#define _LL_CRYPTO_KE_W(c, i, v) ((c)->KEY[(i)] = (v))
#define _LL_CRYPTO_TO_R(c, i)    ((c)->TEXT_OUT[(i)])
#endif
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
_Static_assert(offsetof(CRYPTO_TypeDef, IV) == 0x00, "CRYPTO IV offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, TEXT_IN) == 0x10, "CRYPTO TEXT_IN offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, KEY) == 0x20, "CRYPTO KEY offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, IRQ_ENABLE) == 0x40, "CRYPTO IRQ_ENABLE offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, CONTROL) == 0x44, "CRYPTO CONTROL offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, BASE_DESCRIPTOR) == 0x48, "CRYPTO BASE_DESCRIPTOR offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, DMA_CONTROL) == 0x4C, "CRYPTO DMA_CONTROL offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, TERMINATE) == 0x50, "CRYPTO TERMINATE offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, IRQ) == 0x60, "CRYPTO IRQ offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, TEXT_OUT) == 0x70, "CRYPTO TEXT_OUT offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, STATUS) == 0x80, "CRYPTO STATUS offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, CURRENT_DESCRIPTOR) == 0x84, "CRYPTO CURRENT_DESCRIPTOR offset drift");
_Static_assert(offsetof(CRYPTO_TypeDef, NEXT_DESCRIPTOR) == 0x88, "CRYPTO NEXT_DESCRIPTOR offset drift");
#endif

/** @brief Cipher algorithm (encoded into @c CONTROL.ALGORITHM). */
typedef enum {
    LL_CRYPTO_ALG_AES_128   = 0, /**< AES with a 128-bit key (4 KEY words). */
    LL_CRYPTO_ALG_AES_256   = 1, /**< AES with a 256-bit key (8 KEY words). */
    LL_CRYPTO_ALG_MAGMA     = 2, /**< GOST 28147-89 / 34.12-2018 (64-bit block). */
    LL_CRYPTO_ALG_KUZNECHIK = 3, /**< GOST 34.12-2018 (128-bit block). */
} ll_crypto_alg_t;

/** @brief Mode of operation (encoded into @c CONTROL.MODE). */
typedef enum {
    LL_CRYPTO_MODE_ECB = 0, /**< Electronic Codebook. */
    LL_CRYPTO_MODE_CBC = 1, /**< Cipher Block Chaining (uses @c IV). */
    LL_CRYPTO_MODE_CTR = 2, /**< Counter mode (uses @c IV). */
    LL_CRYPTO_MODE_GCM = 3, /**< Galois/Counter mode; phase via @ref ll_crypto_set_gcm_phase. */
} ll_crypto_mode_t;

/** @brief Operation direction (encoded into @c CONTROL.DIRECTION). */
typedef enum {
    LL_CRYPTO_DIR_ENCRYPT = 0, /**< Encrypt. */
    LL_CRYPTO_DIR_DECRYPT = 1, /**< Decrypt. */
} ll_crypto_dir_t;

/** @brief GCM phase selector (encoded into @c CONTROL.GCM_PHASE). */
typedef enum {
    LL_CRYPTO_GCM_INIT       = 0, /**< Initialisation phase (load J0 / hash key). */
    LL_CRYPTO_GCM_HEADER     = 1, /**< Authenticated-data (AAD) phase. */
    LL_CRYPTO_GCM_PAYLOAD    = 2, /**< Encrypted payload phase. */
    LL_CRYPTO_GCM_LAST_BLOCK = 3, /**< Final block / tag generation. */
} ll_crypto_gcm_phase_t;

/**
 * @brief Composite configuration consumed by @ref ll_crypto_configure.
 */
typedef struct {
    ll_crypto_alg_t algorithm; /**< Algorithm. */
    ll_crypto_mode_t mode;     /**< Mode of operation. */
    ll_crypto_dir_t direction; /**< Encrypt or decrypt. */
} ll_crypto_cfg_t;

/**
 * @name Key, IV and text input/output
 * @{
 */

/**
 * @brief Load a key into @c KEY[0..len_words-1].
 *
 * AES-128 expects @c len_words=4, AES-256 expects 8. Magma and
 * Kuznechik take 8 words (256 bits). Excess slots in @c KEY are left
 * untouched; the engine ignores them based on @c CONTROL.ALGORITHM.
 *
 * @param crypto    CRYPTO instance.
 * @param key       Source key words (caller's endianness — match what
 *                  the algorithm spec mandates).
 * @param len_words Number of 32-bit words to copy (clamped to 8).
 */
static inline void ll_crypto_set_key(CRYPTO_TypeDef *crypto, const uint32_t *key, size_t len_words)
{
    if (!key) {
        return;
    }
    if (len_words > 8U) {
        len_words = 8U;
    }
    for (size_t i = 0; i < len_words; ++i) {
        _LL_CRYPTO_KE_W(crypto, i, key[i]);
    }
}

/**
 * @brief Load the 128-bit initialisation vector into @c IV[0..3].
 *
 * Used for CBC (initial chain value), CTR (counter seed) and GCM
 * (J0 / counter). For ECB the contents of @c IV are ignored.
 *
 * @param crypto CRYPTO instance.
 * @param iv     4-word IV.
 */
static inline void ll_crypto_set_iv(CRYPTO_TypeDef *crypto, const uint32_t iv[4])
{
    if (!iv) {
        return;
    }
    for (size_t i = 0; i < 4U; ++i) {
        _LL_CRYPTO_IV_W(crypto, i, iv[i]);
    }
}

/**
 * @brief Push one block into @c TEXT_IN[0..3].
 *
 * For Magma (64-bit block) only the first two words are used.
 *
 * @param crypto CRYPTO instance.
 * @param in     4-word input block.
 */
static inline void ll_crypto_load_text_in(CRYPTO_TypeDef *crypto, const uint32_t in[4])
{
    if (!in) {
        return;
    }
    for (size_t i = 0; i < 4U; ++i) {
        _LL_CRYPTO_TI_W(crypto, i, in[i]);
    }
}

/**
 * @brief Read the output block from @c TEXT_OUT[0..3].
 * @param crypto CRYPTO instance.
 * @param out    Destination, 4-word block.
 */
static inline void ll_crypto_read_text_out(const CRYPTO_TypeDef *crypto, uint32_t out[4])
{
    if (!out) {
        return;
    }
    for (size_t i = 0; i < 4U; ++i) {
        out[i] = _LL_CRYPTO_TO_R(crypto, i);
    }
}

/** @} */

/**
 * @name Configuration
 * @{
 */

/**
 * @brief Apply algorithm / mode / direction to @c CONTROL.
 *
 * Clears the @c UPDATE_KEY and @c START bits as a side-effect — they
 * have to be re-asserted via @ref ll_crypto_update_key and
 * @ref ll_crypto_start respectively for any pending operation.
 *
 * @param crypto CRYPTO instance.
 * @param cfg    Configuration; ignored if NULL.
 */
static inline void ll_crypto_configure(CRYPTO_TypeDef *crypto, const ll_crypto_cfg_t *cfg)
{
    if (!cfg) {
        return;
    }
    uint32_t ctrl =
        crypto->CONTROL & ~(CRYPTO_CONTROL_ALGORITHM_Msk | CRYPTO_CONTROL_MODE_Msk | CRYPTO_CONTROL_DIRECTION_Msk |
                            CRYPTO_CONTROL_UPDATE_KEY_Msk | CRYPTO_CONTROL_START_Msk);
    ctrl |= ((uint32_t)cfg->algorithm << CRYPTO_CONTROL_ALGORITHM_Pos) & CRYPTO_CONTROL_ALGORITHM_Msk;
    ctrl |= ((uint32_t)cfg->mode << CRYPTO_CONTROL_MODE_Pos) & CRYPTO_CONTROL_MODE_Msk;
    ctrl |= ((uint32_t)cfg->direction << CRYPTO_CONTROL_DIRECTION_Pos) & CRYPTO_CONTROL_DIRECTION_Msk;
    crypto->CONTROL = ctrl;
}

/**
 * @brief Set @c CONTROL.GCM_PHASE.
 * @param crypto CRYPTO instance.
 * @param phase  GCM state-machine phase.
 */
static inline void ll_crypto_set_gcm_phase(CRYPTO_TypeDef *crypto, ll_crypto_gcm_phase_t phase)
{
    uint32_t ctrl = crypto->CONTROL & ~CRYPTO_CONTROL_GCM_PHASE_Msk;
    ctrl |= ((uint32_t)phase << CRYPTO_CONTROL_GCM_PHASE_Pos) & CRYPTO_CONTROL_GCM_PHASE_Msk;
    crypto->CONTROL = ctrl;
}

/**
 * @brief Toggle @c CONTROL.SELF_UPDATE.
 *
 * When set, the engine auto-advances IV/state at the end of each block,
 * allowing back-to-back chained operations without host intervention.
 *
 * @param crypto      CRYPTO instance.
 * @param self_update @c true to enable.
 */
static inline void ll_crypto_set_self_update(CRYPTO_TypeDef *crypto, bool self_update)
{
    if (self_update) {
        crypto->CONTROL |= CRYPTO_CONTROL_SELF_UPDATE_Msk;
    } else {
        crypto->CONTROL &= ~CRYPTO_CONTROL_SELF_UPDATE_Msk;
    }
}

/** @} */

/**
 * @name Operation control
 * @{
 */

/**
 * @brief Pulse @c CONTROL.UPDATE_KEY.
 *
 * Tells the engine to expand the @c KEY registers into its internal
 * round-key schedule. The host must wait for @ref ll_crypto_keys_ready
 * (or its blocking helper) before issuing @ref ll_crypto_start.
 *
 * @param crypto CRYPTO instance.
 */
static inline void ll_crypto_update_key(CRYPTO_TypeDef *crypto)
{
    crypto->CONTROL |= CRYPTO_CONTROL_UPDATE_KEY_Msk;
}

/**
 * @brief Pulse @c CONTROL.START to begin processing the current block.
 * @param crypto CRYPTO instance.
 */
static inline void ll_crypto_start(CRYPTO_TypeDef *crypto)
{
    crypto->CONTROL |= CRYPTO_CONTROL_START_Msk;
}

/**
 * @brief Abort the running operation by writing the magic @c 0xD0 value.
 * @param crypto CRYPTO instance.
 */
static inline void ll_crypto_terminate(CRYPTO_TypeDef *crypto)
{
    crypto->TERMINATE = 0xD0U;
}

/** @} */

/**
 * @name Status
 * @{
 */

/** @brief Read raw @c STATUS.
 *  @param crypto CRYPTO instance.
 *  @return Current STATUS word. */
static inline uint32_t ll_crypto_status(const CRYPTO_TypeDef *crypto)
{
    return crypto->STATUS;
}

/** @brief @c true when the engine is idle (STATUS.READY=1).
 *  @param crypto CRYPTO instance.
 *  @return @c true if ready for a new command. */
static inline bool ll_crypto_ready(const CRYPTO_TypeDef *crypto)
{
    return (crypto->STATUS & CRYPTO_STATUS_READY_Msk) != 0U;
}

/** @brief @c true when round keys are loaded (STATUS.KEYS_READY=1).
 *  @param crypto CRYPTO instance.
 *  @return @c true if keys are expanded and usable. */
static inline bool ll_crypto_keys_ready(const CRYPTO_TypeDef *crypto)
{
    return (crypto->STATUS & CRYPTO_STATUS_KEYS_READY_Msk) != 0U;
}

/** @brief @c true when @c TEXT_OUT holds a freshly-produced block (STATUS.OUT_VALID=1).
 *  @param crypto CRYPTO instance.
 *  @return @c true if the output block is valid. */
static inline bool ll_crypto_out_valid(const CRYPTO_TypeDef *crypto)
{
    return (crypto->STATUS & CRYPTO_STATUS_OUT_VALID_Msk) != 0U;
}

/** @brief Spin until @ref ll_crypto_keys_ready returns @c true.
 *  @param crypto CRYPTO instance. */
static inline void ll_crypto_wait_keys_ready(const CRYPTO_TypeDef *crypto)
{
    while (!ll_crypto_keys_ready(crypto)) {}
}

/** @brief Spin until @ref ll_crypto_out_valid returns @c true.
 *  @param crypto CRYPTO instance. */
static inline void ll_crypto_wait_out_valid(const CRYPTO_TypeDef *crypto)
{
    while (!ll_crypto_out_valid(crypto)) {}
}

/** @brief Spin until @ref ll_crypto_ready returns @c true.
 *  @param crypto CRYPTO instance. */
static inline void ll_crypto_wait_ready(const CRYPTO_TypeDef *crypto)
{
    while (!ll_crypto_ready(crypto)) {}
}

/** @} */

/**
 * @name Interrupts
 * @{
 */

/** @brief Write @c IRQ_ENABLE (1 = enabled).
 *  @param crypto CRYPTO instance.
 *  @param mask Bitmask of CRYPTO_IRQ_* bits to enable. */
static inline void ll_crypto_irq_enable(CRYPTO_TypeDef *crypto, uint32_t mask)
{
    crypto->IRQ_ENABLE = mask;
}

/** @brief Read @c IRQ pending bits.
 *  @param crypto CRYPTO instance.
 *  @return Pending IRQ bits. */
static inline uint32_t ll_crypto_irq_pending(const CRYPTO_TypeDef *crypto)
{
    return crypto->IRQ;
}

/** @brief Clear @c IRQ bits by writing them back (W1C semantics).
 *  @param crypto CRYPTO instance.
 *  @param mask Bits to clear. */
static inline void ll_crypto_irq_clear(CRYPTO_TypeDef *crypto, uint32_t mask)
{
    crypto->IRQ = mask;
}

/** @} */

/**
 * @name DMA descriptor mode
 * @{
 */

/**
 * @brief Point the descriptor engine at a host-built descriptor list.
 *
 * The address must be 16-byte aligned (low 4 bits are reserved per the
 * @c BASE_DESCRIPTOR layout); the host is responsible for arranging
 * the linked list in memory.
 *
 * @param crypto CRYPTO instance.
 * @param addr   Address of the first descriptor (16-byte aligned).
 */
static inline void ll_crypto_set_base_descriptor(CRYPTO_TypeDef *crypto, uint32_t addr)
{
    crypto->BASE_DESCRIPTOR = addr & 0xFFFFFFF0U;
}

/**
 * @brief Trigger DMA descriptor processing (@c DMA_CONTROL.START), with optional byte/word swap.
 * @param crypto      CRYPTO instance.
 * @param bytes_swap  Reverse byte order inside each 32-bit word.
 * @param words_swap  Reverse word order inside each 128-bit block.
 */
static inline void ll_crypto_dma_start(CRYPTO_TypeDef *crypto, bool bytes_swap, bool words_swap)
{
    uint32_t dc = CRYPTO_DMA_CONTROL_START_Msk;
    if (bytes_swap) {
        dc |= CRYPTO_DMA_CONTROL_BYTES_SWAP_Msk;
    }
    if (words_swap) {
        dc |= CRYPTO_DMA_CONTROL_WORDS_SWAP_Msk;
    }
    crypto->DMA_CONTROL = dc;
}

/** @brief Read @c CURRENT_DESCRIPTOR (descriptor currently being processed).
 *  @param crypto CRYPTO instance.
 *  @return Address of the in-flight descriptor. */
static inline uint32_t ll_crypto_current_descriptor(const CRYPTO_TypeDef *crypto)
{
    return crypto->CURRENT_DESCRIPTOR;
}

/** @brief Read @c NEXT_DESCRIPTOR.
 *  @param crypto CRYPTO instance.
 *  @return Address of the next descriptor in the linked list. */
static inline uint32_t ll_crypto_next_descriptor(const CRYPTO_TypeDef *crypto)
{
    return crypto->NEXT_DESCRIPTOR;
}

/** @} */

#if LL_CRYPTO_HAS_GCM_REGS
/**
 * @name GCM HASH / TAG (VG015 only)
 * @{
 */

/**
 * @brief Read the running GCM Galois-hash accumulator (4 words).
 * @param crypto CRYPTO instance.
 * @param out    Destination, 4-word buffer.
 */
static inline void ll_crypto_read_gcm_hash(const CRYPTO_TypeDef *crypto, uint32_t out[4])
{
    if (!out) {
        return;
    }
    for (size_t i = 0; i < 4U; ++i) {
        out[i] = crypto->GCM_HASH[i];
    }
}

/**
 * @brief Read the final GCM authentication tag (4 words).
 * @param crypto CRYPTO instance.
 * @param out    Destination, 4-word buffer.
 */
static inline void ll_crypto_read_gcm_tag(const CRYPTO_TypeDef *crypto, uint32_t out[4])
{
    if (!out) {
        return;
    }
    for (size_t i = 0; i < 4U; ++i) {
        out[i] = crypto->GCM_TAG[i];
    }
}

/** @} */
#endif /* LL_CRYPTO_HAS_GCM_REGS */

#ifdef __cplusplus
}
#endif

/** @} */ /* end of ll_crypto group */
