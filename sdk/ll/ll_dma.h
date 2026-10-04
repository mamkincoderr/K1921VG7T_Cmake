/**
 * @file ll_dma.h
 * @brief Low-level DMA driver — unified API over two different controllers.
 *
 * The DMA IP differs structurally across the family, so this header is a thin
 * router (same pattern as ll_plic):
 *
 *   - k1921vg015 (Cloudbear BM-310): ARM PrimeCell PL230 µDMA. Channel control
 *     structures live in a caller-owned, 1 KB-aligned RAM table that
 *     DMA->BASEPTR points at; 24 channels with a fixed peripheral→channel map.
 *   - k1921vg1t/3t/5t/7t (Syntacore SCR4/SCR5): per-channel register block
 *     DMA->CH[ch]; 32 channels with programmable request routing.
 *
 * Both backends expose the identical API below. A transfer is described by
 * ll_dma_transfer_t (natural base address + item count; the LL converts to the
 * hardware's end-pointer/count form). The caller declares one control table per
 * program with LL_DMA_DEFINE_CTRL_TABLE and passes it to ll_dma_init /
 * ll_dma_setup (used by the PL230 backend; an ignored placeholder on the
 * Syntacore backend).
 *
 * Backends are reached only through this header — do not include them directly.
 *
 * Public API:
 *   void     ll_dma_init(ll_dma_ctrl_table_t *table);
 *   void     ll_dma_setup(ll_dma_ctrl_table_t *table, uint32_t ch,
 *                         const ll_dma_transfer_t *xfer);
 *   void     ll_dma_channel_enable(uint32_t ch, bool on);
 *   void     ll_dma_sw_trigger(uint32_t ch);
 *   bool     ll_dma_is_active(uint32_t ch);
 *   void     ll_dma_irq_enable(uint32_t ch, bool on);
 *   bool     ll_dma_irq_is_pending(uint32_t ch);
 *   void     ll_dma_irq_clear(uint32_t ch);
 *   void     ll_dma_set_priority(uint32_t ch, uint8_t prio);
 *   uint32_t ll_dma_remaining(uint32_t ch);
 *
 * @defgroup ll_dma LL DMA
 * @{
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Transfer unit width (both source and destination). */
typedef enum {
    LL_DMA_WIDTH_BYTE = 0,
    LL_DMA_WIDTH_HALF = 1,
    LL_DMA_WIDTH_WORD = 2,
} ll_dma_width_t;

/** @brief request_src value for a memory-to-memory (software-driven) transfer. */
#define LL_DMA_REQ_SOFTWARE 0u

/** @brief Single-block linear transfer descriptor (portable across backends). */
typedef struct {
    const volatile void *src; /**< source base address              */
    volatile void *dst;       /**< destination base address         */
    uint32_t count;           /**< number of items, <= LL_DMA_MAX_COUNT */
    ll_dma_width_t width;     /**< transfer unit, both sides        */
    bool src_increment;       /**< advance src by `width` per item  */
    bool dst_increment;       /**< advance dst by `width` per item  */
    uint32_t request_src;     /**< LL_DMA_REQ_SOFTWARE or a requestor id */
    uint8_t priority;         /**< 0 .. LL_DMA_PRIO_MAX             */
    bool irq_on_complete;     /**< raise channel IRQ when done      */
} ll_dma_transfer_t;

#ifdef __cplusplus
}
#endif

#if defined(K1921VG015)
#include <ll_dma_vg015.h>
#elif defined(K1921VG1T) || defined(K1921VG3T) || defined(K1921VG5T) || defined(K1921VG7T)
#include <ll_dma_xt.h>
#else
#error "ll_dma.h: no implementation for the selected SoC"
#endif

/** @} */
