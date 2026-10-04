/**
 * @file ll_dma_vg015.h
 * @brief DMA backend for k1921vg015 (Cloudbear BM-310) — ARM PL230 µDMA.
 *
 * Channel control structures live in a caller-owned, 1 KB-aligned RAM table
 * (LL_DMA_DEFINE_CTRL_TABLE) that DMA->BASEPTR points at; the table is indexed
 * by channel number. 24 channels, fixed peripheral→channel map, 8 IRQs each
 * shared by 3 channels. Do not include directly — include <ll_dma.h>.
 */

#pragma once

#include <ll_assert.h>
#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Capabilities ───────────────────────────────────────────────────────── */
#define LL_DMA_CH_COUNT           24U
#define LL_DMA_IRQ_COUNT          8U
#define LL_DMA_CH_PER_IRQ         3U
#define LL_DMA_MAX_COUNT          1024U /* N_MINUS_1 is 10-bit → up to 1024 items */
#define LL_DMA_PRIO_MAX           1U    /* PRIORITYSET: 1 bit per channel */
#define LL_DMA_HAS_PROG_REQUEST   0     /* fixed peripheral→channel map */
#define LL_DMA_HAS_2D             0
#define LL_DMA_HAS_PINGPONG       1
#define LL_DMA_HAS_SCATTER_GATHER 1
#define LL_DMA_HAS_CIRCULAR       1

/** @brief PL230 primary control table: one descriptor slot per channel. */
typedef struct {
    DMA_Channel_TypeDef ch[LL_DMA_CH_COUNT];
} ll_dma_ctrl_table_t;

/* PL230 requires the control-data base aligned to its size; 1 KB is the
 * canonical safe alignment (covers a 32-entry primary+alternate region). */
#define LL_DMA_DEFINE_CTRL_TABLE(name) _Alignas(1024) ll_dma_ctrl_table_t name

/* ── Register-map drift guards ──────────────────────────────────────────── */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
_Static_assert(sizeof(DMA_Channel_TypeDef) == 16U, "PL230 descriptor size drift");
_Static_assert(offsetof(DMA_Channel_TypeDef, SRC_DATA_END_PTR) == 0x0U, "src end ptr drift");
_Static_assert(offsetof(DMA_Channel_TypeDef, DST_DATA_END_PTR) == 0x4U, "dst end ptr drift");
_Static_assert(offsetof(DMA_Channel_TypeDef, CHANNEL_CFG) == 0x8U, "cfg drift");
#endif

/* ── Internals ──────────────────────────────────────────────────────────── */

/* Map ll_dma_width_t → PL230 SRC/DST_SIZE field value (byte/half/word = 0/1/2). */
static inline uint32_t ll_dma_pl230_size(ll_dma_width_t w)
{
    return (uint32_t)w;
}

/* INC field: same encoding as SIZE when incrementing, else "none" = 3. */
static inline uint32_t ll_dma_pl230_inc(ll_dma_width_t w, bool increment)
{
    return increment ? (uint32_t)w : 3U;
}

/* Byte step for a width. */
static inline uint32_t ll_dma_width_bytes(ll_dma_width_t w)
{
    return 1U << (uint32_t)w;
}

/* ── Public API ─────────────────────────────────────────────────────────── */
static inline void ll_dma_init(ll_dma_ctrl_table_t *table)
{
    LL_ASSERT(table != NULL);
    LL_ASSERT(((uintptr_t)table & 0x3FFU) == 0U); /* 1 KB aligned */
    DMA->BASEPTR = (uint32_t)(uintptr_t)table;
    DMA->CFG     = (1U << DMA_CFG_MASTEREN_Pos); /* enable controller, CHPROT=0 */
}

static inline void ll_dma_set_priority(uint32_t ch, uint8_t prio)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    LL_ASSERT(prio <= LL_DMA_PRIO_MAX);
    if (prio != 0U) {
        DMA->PRIORITYSET = 1U << ch;
    } else {
        DMA->PRIORITYCLR = 1U << ch;
    }
}

static inline void ll_dma_setup(ll_dma_ctrl_table_t *table, uint32_t ch, const ll_dma_transfer_t *xfer)
{
    LL_ASSERT(table != NULL);
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    LL_ASSERT(xfer != NULL);
    LL_ASSERT(xfer->count > 0U && xfer->count <= LL_DMA_MAX_COUNT);

    DMA_Channel_TypeDef *d = &table->ch[ch];

    /* PL230 wants END pointers: base + (count-1)*step, or base when no inc. */
    uint32_t sstep      = xfer->src_increment ? ll_dma_width_bytes(xfer->width) : 0U;
    uint32_t dstep      = xfer->dst_increment ? ll_dma_width_bytes(xfer->width) : 0U;
    d->SRC_DATA_END_PTR = (uint32_t)(uintptr_t)xfer->src + (xfer->count - 1U) * sstep;
    d->DST_DATA_END_PTR = (uint32_t)(uintptr_t)xfer->dst + (xfer->count - 1U) * dstep;

    /* mem-to-mem uses AutoReq (SWREQ-triggered, runs to completion);
     * peripheral-driven uses Basic. VERIFY: datasheet cycle-mode choice. */
    uint32_t cycle = (xfer->request_src == LL_DMA_REQ_SOFTWARE) ? DMA_CHANNEL_CFG_CYCLE_CTRL_AutoReq
                                                                : DMA_CHANNEL_CFG_CYCLE_CTRL_Basic;

    uint32_t cfg = (cycle << DMA_CHANNEL_CFG_CYCLE_CTRL_Pos) |
                   (((xfer->count - 1U) << DMA_CHANNEL_CFG_N_MINUS_1_Pos) & DMA_CHANNEL_CFG_N_MINUS_1_Msk) |
                   (ll_dma_pl230_size(xfer->width) << DMA_CHANNEL_CFG_SRC_SIZE_Pos) |
                   (ll_dma_pl230_size(xfer->width) << DMA_CHANNEL_CFG_DST_SIZE_Pos) |
                   (ll_dma_pl230_inc(xfer->width, xfer->src_increment) << DMA_CHANNEL_CFG_SRC_INC_Pos) |
                   (ll_dma_pl230_inc(xfer->width, xfer->dst_increment) << DMA_CHANNEL_CFG_DST_INC_Pos);
    d->CHANNEL_CFG = cfg;

    /* On vg015 a peripheral channel IS the peripheral (fixed map); request_src,
     * when not software, names the channel and must match. */
    LL_ASSERT(xfer->request_src == LL_DMA_REQ_SOFTWARE || xfer->request_src == ch);

    ll_dma_set_priority(ch, xfer->priority);

    /* Route requests: software-driven channels mask hardware requests and run
     * off SWREQ; peripheral channels unmask. */
    if (xfer->request_src == LL_DMA_REQ_SOFTWARE) {
        DMA->REQMASKSET = 1U << ch;
    } else {
        DMA->REQMASKCLR = 1U << ch;
    }
}

static inline void ll_dma_channel_enable(uint32_t ch, bool on)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    if (on) {
        DMA->ENSET = 1U << ch;
    } else {
        DMA->ENCLR = 1U << ch;
    }
}

static inline void ll_dma_sw_trigger(uint32_t ch)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    DMA->SWREQ = 1U << ch;
}

static inline bool ll_dma_is_active(uint32_t ch)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    /* PL230 auto-clears the enable bit when a cycle completes. */
    return (DMA->ENSET & (1U << ch)) != 0U;
}

static inline void ll_dma_irq_enable(uint32_t ch, bool on)
{
    /* PL230 raises the (shared) DMA IRQ on cycle completion; there is no
     * per-channel IRQ enable. Completion reporting is via IRQSTAT (read in the
     * handler). Provided for API symmetry. */
    (void)ch;
    (void)on;
}

static inline bool ll_dma_irq_is_pending(uint32_t ch)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    return (DMA->IRQSTAT & (1U << ch)) != 0U;
}

static inline void ll_dma_irq_clear(uint32_t ch)
{
    LL_ASSERT(ch < LL_DMA_CH_COUNT);
    DMA->IRQSTATCLR = 1U << ch;
}

static inline uint32_t ll_dma_remaining(uint32_t ch)
{
    /* The live N counter is not exposed as a controller register on PL230; the
     * caller polls ll_dma_is_active() instead. Return 0 when idle. */
    return ll_dma_is_active(ch) ? 1U : 0U;
}

#ifdef __cplusplus
}
#endif
