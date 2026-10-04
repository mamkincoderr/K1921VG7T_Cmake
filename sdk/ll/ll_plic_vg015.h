/**
 * @file ll_plic_vg015.h
 * @brief PLIC backend for k1921vg015 (Cloudbear BM-310).
 *
 * Standard/compact PLIC at 0x0C000000. Single hart, two contexts exposed as
 * named registers: M-mode {MIEM0, MTHR, MICC} and U-mode {UIEM0, UTHR, UICC}.
 * 31 interrupt lines (all in enable word 0). Source priority PRI[line] is
 * global. Do not include directly — include <ll_plic.h>.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ll_assert.h>
#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Capabilities ───────────────────────────────────────────────────────── */
#define LL_PLIC_HART_COUNT     1U
#define LL_PLIC_CTX_COUNT      2U  /* M, U */
#define LL_PLIC_LINE_MAX       31U /* IsrVect_IRQ_PMURTC */
#define LL_PLIC_PRIO_MAX       7U  /* confirm vs 015 datasheet; 3-bit PRI field */
#define LL_PLIC_HAS_SW_PENDING 0
#define LL_PLIC_HAS_IRQ_MODES  0 /* BM-310 IGW is hardware-fixed; no SRC_MODE reg */

/* ── Trigger mode (NOT configurable on BM-310) ──────────────────────────── */
/*
 * Unlike the Syntacore banked PLIC (ll_plic_xt.h), the BM-310 has no
 * per-source SRC_MODE register. Its interrupt gateways (IGW) are hardware
 * fixed: int_global lines are edge-sensitive and one-shot, held until
 * interrupt-completion (UM K1921VG015 §9.2). Trigger mode is therefore NOT
 * software-selectable — there are no rising/falling/level options to pick.
 *
 * Consequences, mirroring the SDK's capability-flag convention:
 *   - LL_PLIC_HAS_IRQ_MODES == 0 lets portable code guard mode selection.
 *   - No ll_plic_set_mode()/ll_plic_get_mode() is provided: the operation has
 *     no hardware target on this part (these accessors are an xt-only
 *     extension, absent from ll_plic.h's shared public-API list).
 *
 * The enum still exists so the shared irq_setup_isr() prototype in
 * core/common/inc/irq_handler.h compiles for this SoC; only the fixed default
 * is meaningful, and irq_setup_isr() ignores it (see LL_PLIC_HAS_IRQ_MODES
 * guard there).
 */
typedef enum {
    LL_PLIC_IRQ_MODE_OFF     = 0, /* source masked (use ll_plic_enable) */
    LL_PLIC_IRQ_MODE_DEFAULT = 1, /* the fixed BM-310 gateway mode */
} ll_plic_irq_mode_t;

/* ── Context model ──────────────────────────────────────────────────────── */
typedef enum {
    LL_PLIC_MODE_M = 0,
    LL_PLIC_MODE_S = 1, /* not present on BM-310 */
    LL_PLIC_MODE_U = 2,
} ll_plic_mode_t;

#define LL_PLIC_CTX_M 0U
#define LL_PLIC_CTX_U 1U

/* Resolve (hart, mode) -> context index. hart must be 0; M->0, U->1.
 * S-mode is invalid on this part. Asserts in debug builds. */
static inline uint32_t ll_plic_ctx(uint32_t hart, ll_plic_mode_t mode)
{
    LL_ASSERT(hart == 0U);
    LL_ASSERT(mode == LL_PLIC_MODE_M || mode == LL_PLIC_MODE_U);
    return (mode == LL_PLIC_MODE_U) ? LL_PLIC_CTX_U : LL_PLIC_CTX_M;
}
#define LL_PLIC_CTX(hart, mode) ll_plic_ctx((hart), (mode))

/* ── Register-map drift guards ──────────────────────────────────────────── */
_Static_assert(offsetof(PLIC_TypeDef, PRI) == 0x000000U, "PLIC PRI offset drift");
_Static_assert(offsetof(PLIC_TypeDef, MIEM0) == 0x002000U, "PLIC MIEM0 offset drift");
_Static_assert(offsetof(PLIC_TypeDef, UIEM0) == 0x002080U, "PLIC UIEM0 offset drift");
_Static_assert(offsetof(PLIC_TypeDef, MTHR) == 0x200000U, "PLIC MTHR offset drift");
_Static_assert(offsetof(PLIC_TypeDef, MICC) == 0x200004U, "PLIC MICC offset drift");
_Static_assert(offsetof(PLIC_TypeDef, UTHR) == 0x201000U, "PLIC UTHR offset drift");
_Static_assert(offsetof(PLIC_TypeDef, UICC) == 0x201004U, "PLIC UICC offset drift");

/* ── Global, per-source ─────────────────────────────────────────────────── */
static inline void ll_plic_set_priority(uint32_t line, uint32_t prio)
{
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    LL_ASSERT(prio <= LL_PLIC_PRIO_MAX);
    PLIC->PRI[line] = prio;
}

static inline uint32_t ll_plic_get_priority(uint32_t line)
{
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    return PLIC->PRI[line];
}

static inline bool ll_plic_is_pending(uint32_t line)
{
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    /* Pending word 0 lives at IPM0 (0x1000). */
    const volatile uint32_t *pend = &PLIC->IPM0;
    return (pend[line >> 5] & (1U << (line & 31U))) != 0U;
}

/* ── Per-context: enable bitmap ─────────────────────────────────────────── */
static inline volatile uint32_t *ll_plic_enable_word(uint32_t ctx, uint32_t line)
{
    /* M-mode enable word 0 = MIEM0; U-mode enable word 0 = UIEM0. Only 1 word
     * needed (31 lines). */
    volatile uint32_t *base = (ctx == LL_PLIC_CTX_U) ? &PLIC->UIEM0 : &PLIC->MIEM0;
    return base + (line >> 5);
}

static inline void ll_plic_enable(uint32_t ctx, uint32_t line, bool on)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    volatile uint32_t *w = ll_plic_enable_word(ctx, line);
    uint32_t bit         = 1U << (line & 31U);
    if (on) {
        *w |= bit;
    } else {
        *w &= ~bit;
    }
}

static inline bool ll_plic_is_enabled(uint32_t ctx, uint32_t line)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    return (*ll_plic_enable_word(ctx, line) & (1U << (line & 31U))) != 0U;
}

/* ── Per-context: threshold + claim/complete ────────────────────────────── */
static inline void ll_plic_set_threshold(uint32_t ctx, uint32_t thr)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    if (ctx == LL_PLIC_CTX_U) {
        PLIC->UTHR = thr;
    } else {
        PLIC->MTHR = thr;
    }
}

static inline uint32_t ll_plic_get_threshold(uint32_t ctx)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    return (ctx == LL_PLIC_CTX_U) ? PLIC->UTHR : PLIC->MTHR;
}

static inline uint32_t ll_plic_claim(uint32_t ctx)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    return (ctx == LL_PLIC_CTX_U) ? PLIC->UICC : PLIC->MICC;
}

static inline void ll_plic_complete(uint32_t ctx, uint32_t id)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    if (ctx == LL_PLIC_CTX_U) {
        PLIC->UICC = id;
    } else {
        PLIC->MICC = id;
    }
}

#ifdef __cplusplus
}
#endif
