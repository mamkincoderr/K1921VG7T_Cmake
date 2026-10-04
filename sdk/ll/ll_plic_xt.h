/**
 * @file ll_plic_xt.h
 * @brief PLIC backend for the Syntacore SCR4/SCR5 family
 *        (k1921vg1t/3t/5t/7t).
 *
 * Banked PLIC at 0xFE000000 (standard RISC-V layout). Source priority lives in
 * SRC_PRI[line]; per-context enable bitmaps in INTEN_TARGET[ctx] (32 words
 * each); per-context threshold + claim/complete in PRI_SE[ctx]
 * {PRI_TRSHLD, START_END}. Contexts index (hart, mode). Only k1921vg1t is
 * dual-hart. Do not include directly — include <ll_plic.h>.
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

/* ── Per-SoC capabilities ───────────────────────────────────────────────── */
/* LINE_MAX = max IsrVect_IRQ_* in each header's Plic_IsrVect enum.
 * MODES_PER_HART / HART_COUNT confirmed against the datasheet PLIC context
 * table where available (see commit notes). */
#if defined(K1921VG1T)
#define LL_PLIC_HART_COUNT     2U
#define LL_PLIC_MODES_PER_HART 2U   /* confirm vs 1T.pdf */
#define LL_PLIC_LINE_MAX       254U /* IsrVect_IRQ_MSC_downstream = 254 */
#elif defined(K1921VG3T)
#define LL_PLIC_HART_COUNT     1U
#define LL_PLIC_MODES_PER_HART 2U   /* confirm vs 3T.pdf */
#define LL_PLIC_LINE_MAX       228U /* IsrVect_IRQ_CANFD1_ECCD = 228 (229 is empty placeholder) */
#elif defined(K1921VG5T)
#define LL_PLIC_HART_COUNT     1U
#define LL_PLIC_MODES_PER_HART 2U
#define LL_PLIC_LINE_MAX       100U /* IsrVect_IRQ_RTC_POWEROK = 100 (101 is empty placeholder) */
#elif defined(K1921VG7T)
#define LL_PLIC_HART_COUNT     1U
#define LL_PLIC_MODES_PER_HART 2U
#define LL_PLIC_LINE_MAX       124U /* IsrVect_IRQ_TMR16_2_CC = 124 */
#endif

#define LL_PLIC_CTX_COUNT      (LL_PLIC_HART_COUNT * LL_PLIC_MODES_PER_HART)
#define LL_PLIC_PRIO_MAX       7U /* confirm vs datasheet PRI field width */
#define LL_PLIC_HAS_SW_PENDING 0
#define LL_PLIC_HAS_IRQ_MODES  1

/* ── Context model ──────────────────────────────────────────────────────── */
typedef enum {
    LL_PLIC_MODE_M = 0,
    LL_PLIC_MODE_S = 1,
    LL_PLIC_MODE_U = 2,
} ll_plic_mode_t;

typedef enum {
    LL_PLIC_IRQ_MODE_OFF = 0,
    LL_PLIC_IRQ_MODE_HILEVEL,
    LL_PLIC_IRQ_MODE_LOLEVEL,
    LL_PLIC_IRQ_MODE_RISEDGE,
    LL_PLIC_IRQ_MODE_FALEDGE,
    LL_PLIC_IRQ_MODE_TWOEDGE
} ll_plic_irq_mode_t;

/* Mode position within a hart's context block. With MODES_PER_HART==2 the
 * exposed modes are M (index 0) and the secondary mode (index 1). Adjust per
 * datasheet if the ordering differs. */
static inline uint32_t ll_plic_mode_index(ll_plic_mode_t mode)
{
    return (mode == LL_PLIC_MODE_M) ? 0U : 1U;
}

static inline uint32_t ll_plic_ctx(uint32_t hart, ll_plic_mode_t mode)
{
    LL_ASSERT(hart < LL_PLIC_HART_COUNT);
    uint32_t idx = (hart * LL_PLIC_MODES_PER_HART) + ll_plic_mode_index(mode);
    LL_ASSERT(idx < LL_PLIC_CTX_COUNT);
    return idx;
}
#define LL_PLIC_CTX(hart, mode) ll_plic_ctx((hart), (mode))

/* ── Register-map drift guards ──────────────────────────────────────────── */
_Static_assert(offsetof(PLIC_TypeDef, SRC_PRI) == 0x000000U, "PLIC SRC_PRI offset drift");
_Static_assert(offsetof(PLIC_TypeDef, INT_PEND) == 0x001000U, "PLIC INT_PEND offset drift");
_Static_assert(offsetof(PLIC_TypeDef, INTEN_TARGET) == 0x002000U, "PLIC INTEN_TARGET offset drift");
_Static_assert(offsetof(PLIC_TypeDef, PRI_SE) == 0x200000U, "PLIC PRI_SE offset drift");
_Static_assert(sizeof(PLIC_INTEN_Bank_TypeDef) == 128U, "PLIC INTEN bank stride drift");
_Static_assert(sizeof(PLIC_PRI_SE_TypeDef) == 0x1000U, "PLIC PRI_SE stride drift");

/* ── Global, per-source ─────────────────────────────────────────────────── */
static inline void ll_plic_set_priority(uint32_t line, uint32_t prio)
{
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    LL_ASSERT(prio <= LL_PLIC_PRIO_MAX);
    PLIC->SRC_PRI[line] = prio;
}

static inline uint32_t ll_plic_get_priority(uint32_t line)
{
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    return PLIC->SRC_PRI[line];
}

static inline void ll_plic_set_mode(uint32_t line, ll_plic_irq_mode_t irq_mode)
{
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    LL_ASSERT(irq_mode >= LL_PLIC_IRQ_MODE_OFF);
    LL_ASSERT(irq_mode <= LL_PLIC_IRQ_MODE_TWOEDGE);

    PLIC->SRC_MODE[line] = irq_mode;
}

static inline ll_plic_irq_mode_t ll_plic_get_mode(uint32_t line)
{
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);

    return PLIC->SRC_MODE[line];
}

static inline bool ll_plic_is_pending(uint32_t line)
{
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    return (PLIC->INT_PEND[line >> 5] & (1U << (line & 31U))) != 0U;
}

/* ── Per-context: enable bitmap ─────────────────────────────────────────── */
static inline void ll_plic_enable(uint32_t ctx, uint32_t line, bool on)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    LL_ASSERT(line <= LL_PLIC_LINE_MAX);
    volatile uint32_t *w = &PLIC->INTEN_TARGET[ctx].INTEN_BANK[line >> 5];
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
    return (PLIC->INTEN_TARGET[ctx].INTEN_BANK[line >> 5] & (1U << (line & 31U))) != 0U;
}

/* ── Per-context: threshold + claim/complete ────────────────────────────── */
static inline void ll_plic_set_threshold(uint32_t ctx, uint32_t thr)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    PLIC->PRI_SE[ctx].PRI_TRSHLD = thr;
}

static inline uint32_t ll_plic_get_threshold(uint32_t ctx)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    return PLIC->PRI_SE[ctx].PRI_TRSHLD;
}

static inline uint32_t ll_plic_claim(uint32_t ctx)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    return PLIC->PRI_SE[ctx].START_END;
}

static inline void ll_plic_complete(uint32_t ctx, uint32_t id)
{
    LL_ASSERT(ctx < LL_PLIC_CTX_COUNT);
    PLIC->PRI_SE[ctx].START_END = id;
}

#ifdef __cplusplus
}
#endif
