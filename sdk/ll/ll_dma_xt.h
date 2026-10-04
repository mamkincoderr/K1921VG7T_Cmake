/**
 * @file ll_dma_xt.h
 * @brief DMA backend for k1921vg1t/3t/5t/7t (Syntacore SCR4/SCR5).
 *
 * Per-channel register block DMA->CH[ch]; controller-global bitmask registers
 * for start/enable/idle/priority. A v1 single-block transfer is written
 * directly into CH[ch] with CONFIG.CMD_LAST=1 (no RAM descriptor; chaining via
 * CONFIG.NEXT_ADDR is deferred). Do not include directly — include <ll_dma.h>.
 */

#pragma once

#include <ll_assert.h>
#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Capabilities ───────────────────────────────────────────────────────── */
/* Channel count, IRQ count (one PLIC line per channel) and the highest
 * hardware-requestor id differ per SoC; everything else is shared IP. */
#if defined(K1921VG1T)
#define LL_DMA_CH_COUNT 32U
#define LL_DMA_REQ_MAX  70U /* DAC1_DMA_REQUESTOR_IDX */
#elif defined(K1921VG3T)
#define LL_DMA_CH_COUNT 24U
#define LL_DMA_REQ_MAX  62U /* PWM9_DMA_REQUESTOR_IDX */
#elif defined(K1921VG5T)
#define LL_DMA_CH_COUNT 16U
#define LL_DMA_REQ_MAX  19U /* TMR2_DMA_REQUESTOR_IDX */
#elif defined(K1921VG7T)
#define LL_DMA_CH_COUNT 8U
#define LL_DMA_REQ_MAX  17U /* TMR0_DMA_REQUESTOR_IDX */
#else
#error "ll_dma_xt.h: unknown xT SoC — no DMA channel count"
#endif

#define LL_DMA_IRQ_COUNT          LL_DMA_CH_COUNT
#define LL_DMA_CH_PER_IRQ         1U
#define LL_DMA_MAX_COUNT          1023U /* NDTL.BUFFER_SIZE is in BYTES, 10-bit (max 1023) */
#define LL_DMA_PRIO_MAX           1U    /* RD/WR_PRIORITY: 1 bit per channel */
#define LL_DMA_HAS_PROG_REQUEST   1
#define LL_DMA_HAS_2D             1
#define LL_DMA_HAS_PINGPONG       0
#define LL_DMA_HAS_SCATTER_GATHER 1
#define LL_DMA_HAS_CIRCULAR       0

/** @brief Control table is unused on this backend (registers are direct). */
typedef struct {
    uint32_t reserved;
} ll_dma_ctrl_table_t;

#define LL_DMA_DEFINE_CTRL_TABLE(name) ll_dma_ctrl_table_t name

/* ── Register-map drift guards ──────────────────────────────────────────── */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
_Static_assert(offsetof(DMA_TypeDef, CH) == 0x000U, "DMA CH[] offset drift");
_Static_assert(offsetof(_DMA_CH_TypeDef, SRC_PTR) == 0x00U, "DMA SRC_PTR drift");
_Static_assert(offsetof(_DMA_CH_TypeDef, DST_PTR) == 0x04U, "DMA DST_PTR drift");
_Static_assert(sizeof(((DMA_TypeDef *)0)->CH) / sizeof(_DMA_CH_TypeDef) == LL_DMA_CH_COUNT,
               "LL_DMA_CH_COUNT disagrees with DMA->CH[] size for this SoC");
#endif

/* ── Internals ──────────────────────────────────────────────────────────── */
static inline volatile _DMA_CH_TypeDef *ll_dma_ch(uint32_t ch)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    return &DMA->CH[ch];
}

/* Byte step / element size for a width (byte/half/word = 1/2/4). */
static inline uint32_t ll_dma_width_bytes(ll_dma_width_t w)
{
    return 1U << (uint32_t)w;
}

/* ── Public API ─────────────────────────────────────────────────────────── */
static inline void ll_dma_init(ll_dma_ctrl_table_t *table)
{
    (void)table; /* per-channel programming needs no global table on vgXt */
}

static inline void ll_dma_set_priority(uint32_t ch, uint8_t prio)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    LL_ASSERT(prio <= LL_DMA_PRIO_MAX);
    uint32_t bit = 1U << ch;
    if (prio != 0U) {
        DMA->RD_PRIORITY |= bit;
        DMA->WR_PRIORITY |= bit;
    } else {
        DMA->RD_PRIORITY &= ~bit;
        DMA->WR_PRIORITY &= ~bit;
    }
}

static inline void ll_dma_setup(ll_dma_ctrl_table_t *table, uint32_t ch, const ll_dma_transfer_t *xfer)
{
    (void)table;
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    LL_ASSERT(xfer != NULL);
    LL_ASSERT(xfer->count > 0U);
    LL_ASSERT(xfer->request_src <= LL_DMA_REQ_MAX);

    volatile _DMA_CH_TypeDef *c = ll_dma_ch(ch);

    const uint32_t step  = ll_dma_width_bytes(xfer->width);
    const uint32_t bytes = xfer->count * step;       /* NDTL.BUFFER_SIZE is in bytes */
    LL_ASSERT(bytes <= DMA_CH_NDTL_BUFFER_SIZE_Msk); /* 10-bit field, <= 1023 */

    c->SRC_PTR = (uint32_t)(uintptr_t)xfer->src;
    c->DST_PTR = (uint32_t)(uintptr_t)xfer->dst;

    c->NDTL = (bytes << DMA_CH_NDTL_BUFFER_SIZE_Pos) & DMA_CH_NDTL_BUFFER_SIZE_Msk;

    uint32_t cfg = DMA_CH_CONFIG_CMD_LAST_Msk; /* single, non-chained command */
    if (xfer->irq_on_complete) {
        cfg |= DMA_CH_CONFIG_CMD_SET_INT_Msk;
    }
    c->CONFIG = cfg;

    /* STATIC0/1 reset to 0x80010000 (INCR=1, TOKENS=1). RD/WR_BURST_MAX resets
     * to 0, which would stall the channel, so it MUST be programmed: bytes per
     * AXI burst = element width (datasheet §14.4). Preserve TOKENS=1 and set
     * INCR per direction (set for memory, clear for a fixed peripheral FIFO). */
    uint32_t s0 = (1U << DMA_CH_STATIC0_RD_TOKENS_Pos) |
                  ((step << DMA_CH_STATIC0_RD_BURST_MAX_Pos) & DMA_CH_STATIC0_RD_BURST_MAX_Msk);
    if (xfer->src_increment) {
        s0 |= DMA_CH_STATIC0_RD_INCR_Msk;
    }
    c->STATIC0 = s0;

    uint32_t s1 = (1U << DMA_CH_STATIC1_WR_TOKENS_Pos) |
                  ((step << DMA_CH_STATIC1_WR_BURST_MAX_Pos) & DMA_CH_STATIC1_WR_BURST_MAX_Msk);
    if (xfer->dst_increment) {
        s1 |= DMA_CH_STATIC1_WR_INCR_Msk;
    }
    c->STATIC1 = s1;

    /* Programmable routing: the non-incrementing side is the peripheral; the
     * incrementing side reads/writes memory (requestor 0 = MEMORY). For
     * mem-to-mem (request_src == LL_DMA_REQ_SOFTWARE) both sides are MEMORY. */
    uint32_t rd_per = 0U;
    uint32_t wr_per = 0U;
    if (xfer->request_src != LL_DMA_REQ_SOFTWARE) {
        if (!xfer->src_increment) {
            rd_per = xfer->request_src; /* source is the peripheral */
        }
        if (!xfer->dst_increment) {
            wr_per = xfer->request_src; /* destination is the peripheral */
        }
    }
    c->STATIC4 = ((rd_per << DMA_CH_STATIC4_RD_PER_NUM_Pos) & DMA_CH_STATIC4_RD_PER_NUM_Msk) |
                 ((wr_per << DMA_CH_STATIC4_WR_PER_NUM_Pos) & DMA_CH_STATIC4_WR_PER_NUM_Msk);

    ll_dma_set_priority(ch, xfer->priority);
}

static inline void ll_dma_channel_enable(uint32_t ch, bool on)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    uint32_t bit = 1U << ch;
    if (on) {
        DMA->CH_ENABLE |= bit;
    } else {
        DMA->CH_ENABLE &= ~bit;
    }
}

static inline void ll_dma_sw_trigger(uint32_t ch)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    /* Step 5 of the channel start sequence (datasheet §14.15). */
    DMA->CH_START = 1U << ch;
}

static inline bool ll_dma_is_active(uint32_t ch)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    /* Active while a read or write is still in flight (datasheet §14.15:
     * CH_RD_ACTIVE/CH_WR_ACTIVE clear to 0 once the channel stops). */
    const uint32_t mask = DMA_CH_CH_STATUS_CH_RD_ACTIVE_Msk | DMA_CH_CH_STATUS_CH_WR_ACTIVE_Msk;
    return (ll_dma_ch(ch)->CH_STATUS & mask) != 0U;
}

static inline void ll_dma_irq_enable(uint32_t ch, bool on)
{
    /* Gate only the completion (CH_END) interrupt; leave the error/timeout
     * enables at their reset state (INT_ENABLE resets to 0x1FFF). */
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    if (on) {
        ll_dma_ch(ch)->INT_ENABLE |= DMA_CH_INT_ENABLE_CH_END_Msk;
    } else {
        ll_dma_ch(ch)->INT_ENABLE &= ~DMA_CH_INT_ENABLE_CH_END_Msk;
    }
}

static inline bool ll_dma_irq_is_pending(uint32_t ch)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    return (ll_dma_ch(ch)->INT_STATUS & DMA_CH_INT_STATUS_CH_END_Msk) != 0U;
}

static inline void ll_dma_irq_clear(uint32_t ch)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    ll_dma_ch(ch)->INT_CLEAR = DMA_CH_INT_CLEAR_CH_END_Msk;
}

static inline uint32_t ll_dma_remaining(uint32_t ch)
{
    /* The controller exposes no live bytes-remaining register (COUNT.BUFF_COUNT
     * is buffers *completed*, not items left). Report nonzero while the channel
     * is still running, matching the vg015 backend. */
    return ll_dma_is_active(ch) ? 1U : 0U;
}

#ifdef __cplusplus
}
#endif
