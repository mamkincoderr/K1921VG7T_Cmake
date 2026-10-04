/**
 * @file ll_tmr_xt.h
 * @brief Timer backend for k1921vg1t/3t/5t/7t (modern layout). Include <ll_tmr.h>.
 */
#pragma once

#include <ll_assert.h>
#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Canonical instance type + capabilities ─────────────────────────────── */
#if defined(K1921VG7T)
typedef TMR32_TypeDef ll_tmr_t; /* TMR16_* and TMR32_* share this layout */
#define LL_TMR_CAPCOM_COUNT     2U
#define LL_TMR_CAPCOM_ELEM_SIZE sizeof(_TMR32_CAPCOM_TypeDef)
/* device-header field macros are TMR32_* on vg7t */
#define LL_TMR_CTRL_CLKSEL_Pos  TMR32_CTRL_CLKSEL_Pos
#define LL_TMR_CTRL_MODE_Pos    TMR32_CTRL_MODE_Pos
#define LL_TMR_CTRL_MODE_Msk    TMR32_CTRL_MODE_Msk
#define LL_TMR_IM_TMR_Msk       TMR32_IM_TMR_Msk
#define LL_TMR_CAPCOM_CAP_Msk   TMR32_CAPCOM_CTRL_CAP_Msk
#define LL_TMR_DMA_TXIM_TMR_Msk TMR32_DMA_TXIM_TMR_Msk
#define LL_TMR_DMA_RXIM_TMR_Msk TMR32_DMA_RXIM_TMR_Msk
#define LL_TMR_EXTEVT_TMR_Msk   TMR32_EXTEVT_IM_TMR_Msk
#else
typedef TMR_TypeDef ll_tmr_t; /* vg1t/3t/5t */
#if defined(K1921VG3T)
#define LL_TMR_CAPCOM_COUNT 2U
#elif defined(K1921VG5T)
#define LL_TMR_CAPCOM_COUNT 2U
#else /* K1921VG1T */
#define LL_TMR_CAPCOM_COUNT 4U
#endif
#define LL_TMR_CAPCOM_ELEM_SIZE sizeof(_TMR_CAPCOM_TypeDef)
#define LL_TMR_CTRL_CLKSEL_Pos  TMR_CTRL_CLKSEL_Pos
#define LL_TMR_CTRL_MODE_Pos    TMR_CTRL_MODE_Pos
#define LL_TMR_CTRL_MODE_Msk    TMR_CTRL_MODE_Msk
#define LL_TMR_IM_TMR_Msk       TMR_IM_TMR_Msk
#define LL_TMR_CAPCOM_CAP_Msk   TMR_CAPCOM_CTRL_CAP_Msk
#define LL_TMR_DMA_TXIM_TMR_Msk TMR_DMA_TXIM_TMR_Msk
#define LL_TMR_DMA_RXIM_TMR_Msk TMR_DMA_RXIM_TMR_Msk
#define LL_TMR_EXTEVT_TMR_Msk   TMR_EXTEVT_IM_TMR_Msk
#endif

#define LL_TMR_HAS_PERIOD_REG 1
#define LL_TMR_HAS_DMA_TXRX   1

/* ── Register-map drift guards ──────────────────────────────────────────── */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
_Static_assert(offsetof(ll_tmr_t, CTRL) == 0x00U, "TMR CTRL offset drift");
_Static_assert(offsetof(ll_tmr_t, COUNT) == 0x04U, "TMR COUNT offset drift");
_Static_assert(offsetof(ll_tmr_t, CLKDIV) == 0x08U, "TMR CLKDIV offset drift");
_Static_assert(offsetof(ll_tmr_t, PERIOD) == 0x0CU, "TMR PERIOD offset drift");
_Static_assert(offsetof(ll_tmr_t, IC) == 0x1CU, "TMR IC offset drift");
_Static_assert(offsetof(ll_tmr_t, CAPCOM) == 0x100U, "TMR CAPCOM offset drift");
/* Size-based (works whether CAPCOM is an array or, on vg3t, a single struct). */
_Static_assert(sizeof(((ll_tmr_t *)0)->CAPCOM) == LL_TMR_CAPCOM_COUNT * LL_TMR_CAPCOM_ELEM_SIZE,
               "LL_TMR_CAPCOM_COUNT disagrees with CAPCOM size");
#endif

/* ── Timebase ───────────────────────────────────────────────────────────── */
static inline void ll_tmr_init(ll_tmr_t *t, const ll_tmr_config_t *cfg)
{
    LL_ASSERT(t != NULL);
    LL_ASSERT(cfg != NULL);
    /* MODE field left at 0 (STOP); CLKSEL set; counter cleared. */
    t->CTRL   = ((uint32_t)cfg->clksel << LL_TMR_CTRL_CLKSEL_Pos);
    t->CLKDIV = cfg->divider;
    t->PERIOD = cfg->period;
    t->COUNT  = 0U;
}

static inline void ll_tmr_start(ll_tmr_t *t, ll_tmr_mode_t mode)
{
    LL_ASSERT(t != NULL);
    t->CTRL = (t->CTRL & ~LL_TMR_CTRL_MODE_Msk) | (((uint32_t)mode << LL_TMR_CTRL_MODE_Pos) & LL_TMR_CTRL_MODE_Msk);
}

static inline void ll_tmr_stop(ll_tmr_t *t)
{
    LL_ASSERT(t != NULL);
    t->CTRL &= ~LL_TMR_CTRL_MODE_Msk;
}

static inline void ll_tmr_set_period(ll_tmr_t *t, uint32_t period)
{
    LL_ASSERT(t != NULL);
    t->PERIOD = period;
}

static inline uint32_t ll_tmr_get_count(ll_tmr_t *t)
{
    LL_ASSERT(t != NULL);
    return t->COUNT;
}

static inline void ll_tmr_set_count(ll_tmr_t *t, uint32_t v)
{
    LL_ASSERT(t != NULL);
    t->COUNT = v;
}

/* ── Interrupts (IM mask / MIS status / IC clear) ───────────────────────── */
static inline void ll_tmr_irq_enable(ll_tmr_t *t, uint32_t mask, bool on)
{
    LL_ASSERT(t != NULL);
    if (on) {
        t->IM |= mask;
    } else {
        t->IM &= ~mask;
    }
}

static inline uint32_t ll_tmr_irq_pending(ll_tmr_t *t)
{
    LL_ASSERT(t != NULL);
    return t->MIS; /* masked interrupt status */
}

static inline void ll_tmr_irq_clear(ll_tmr_t *t, uint32_t mask)
{
    LL_ASSERT(t != NULL);
    t->IC = mask;
}

/* ── Capture / Compare ──────────────────────────────────────────────────── */
#if defined(K1921VG7T)
typedef _TMR32_CAPCOM_TypeDef ll_tmr_capcom_hw_t;
#else
typedef _TMR_CAPCOM_TypeDef ll_tmr_capcom_hw_t;
#endif

static inline volatile ll_tmr_capcom_hw_t *ll_tmr_capcom_ch(ll_tmr_t *t, uint32_t ch)
{
    LL_ASSERT(ch < LL_TMR_CAPCOM_COUNT);
    return &t->CAPCOM[ch];
}

/* Channel ch primary event (CAPCOMn_0) IM/RIS/MIS/IC bit. */
static inline uint32_t ll_tmr_capcom_irq_mask(uint32_t ch)
{
    return 1U << (1U + 2U * ch);
}

static inline void ll_tmr_capcom_config(ll_tmr_t *t, uint32_t ch, const ll_tmr_capcom_t *cc)
{
    LL_ASSERT(t != NULL);
    LL_ASSERT(cc != NULL);
    LL_ASSERT(ch < LL_TMR_CAPCOM_COUNT);

    volatile ll_tmr_capcom_hw_t *c = ll_tmr_capcom_ch(t, ch);
    c->CTRL                        = (cc->mode == LL_TMR_CAPCOM_CAPTURE) ? LL_TMR_CAPCOM_CAP_Msk : 0U;
    c->VAL0                        = cc->value;
    if (cc->irq_on_event) {
        t->IM |= ll_tmr_capcom_irq_mask(ch);
    }
}

static inline void ll_tmr_capcom_set(ll_tmr_t *t, uint32_t ch, uint32_t compare)
{
    LL_ASSERT(t != NULL);
    LL_ASSERT(ch < LL_TMR_CAPCOM_COUNT);
    ll_tmr_capcom_ch(t, ch)->VAL0 = compare;
}

static inline uint32_t ll_tmr_capcom_get(ll_tmr_t *t, uint32_t ch)
{
    LL_ASSERT(t != NULL);
    LL_ASSERT(ch < LL_TMR_CAPCOM_COUNT);
    return ll_tmr_capcom_ch(t, ch)->VAL0;
}

/* ── DMA / external-event trigger gating ────────────────────────────────── */
static inline void ll_tmr_dma_enable(ll_tmr_t *t, uint32_t mask, bool on)
{
    LL_ASSERT(t != NULL);
    if (on) {
        t->DMA_TXIM |= mask;
    } else {
        t->DMA_TXIM &= ~mask;
    }
}

static inline void ll_tmr_dma_rx_enable(ll_tmr_t *t, uint32_t mask, bool on)
{
    LL_ASSERT(t != NULL);
    if (on) {
        t->DMA_RXIM |= mask;
    } else {
        t->DMA_RXIM &= ~mask;
    }
}

/* ADC/DAC and other external-event triggers (EXTEVT_IM on this generation). */
static inline void ll_tmr_trigger_enable(ll_tmr_t *t, uint32_t mask, bool on)
{
    LL_ASSERT(t != NULL);
    if (on) {
        t->EXTEVT_IM |= mask;
    } else {
        t->EXTEVT_IM &= ~mask;
    }
}

#ifdef __cplusplus
}
#endif
