/**
 * @file ll_tmr_vg015.h
 * @brief Timer backend for k1921vg015 (legacy layout). Include <ll_tmr.h>.
 *
 * No CLKDIV/PERIOD registers: the divider lives in CTRL.DIV and the period is
 * CAPCOM[0].VAL (the counter runs 0 -> CAPCOM[0].VAL in UP/UPDOWN). CAPCOM
 * channel 0 is therefore reserved for the timebase whenever a period is used;
 * user compare/capture should target channels 1..3.
 */
#pragma once

#include <ll_assert.h>
#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ll_tmr_t spans TMR0..2 (16-bit) and TMR32 (32-bit); identical layout. */
typedef TMR32_TypeDef ll_tmr_t;

#define LL_TMR_CAPCOM_COUNT     4U
#define LL_TMR_CAPCOM_ELEM_SIZE sizeof(_TMR32_CAPCOM_TypeDef)
#define LL_TMR_HAS_PERIOD_REG   0
#define LL_TMR_HAS_DMA_TXRX     0

/* ── Register-map drift guards ──────────────────────────────────────────── */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
_Static_assert(offsetof(ll_tmr_t, CTRL) == 0x00U, "TMR CTRL offset drift");
_Static_assert(offsetof(ll_tmr_t, COUNT) == 0x04U, "TMR COUNT offset drift");
_Static_assert(offsetof(ll_tmr_t, IC) == 0x14U, "TMR IC offset drift");
_Static_assert(offsetof(ll_tmr_t, CAPCOM) == 0x18U, "TMR CAPCOM offset drift");
_Static_assert(sizeof(((ll_tmr_t *)0)->CAPCOM) == LL_TMR_CAPCOM_COUNT * LL_TMR_CAPCOM_ELEM_SIZE,
               "LL_TMR_CAPCOM_COUNT disagrees with CAPCOM size");
#endif

/* ── Timebase ───────────────────────────────────────────────────────────── */
static inline void ll_tmr_init(ll_tmr_t *t, const ll_tmr_config_t *cfg)
{
    LL_ASSERT(t != NULL);
    LL_ASSERT(cfg != NULL);
    /* MODE=STOP; CLKSEL + DIV in CTRL. Period lives in CAPCOM[0].VAL. */
    t->CTRL =
        ((uint32_t)cfg->clksel << TMR32_CTRL_CLKSEL_Pos) | ((cfg->divider << TMR32_CTRL_DIV_Pos) & TMR32_CTRL_DIV_Msk);
    t->CAPCOM[0].VAL = cfg->period;
    t->COUNT         = 0U;
}

static inline void ll_tmr_start(ll_tmr_t *t, ll_tmr_mode_t mode)
{
    LL_ASSERT(t != NULL);
    t->CTRL = (t->CTRL & ~TMR32_CTRL_MODE_Msk) | (((uint32_t)mode << TMR32_CTRL_MODE_Pos) & TMR32_CTRL_MODE_Msk);
}

static inline void ll_tmr_stop(ll_tmr_t *t)
{
    LL_ASSERT(t != NULL);
    t->CTRL &= ~TMR32_CTRL_MODE_Msk;
}

static inline void ll_tmr_set_period(ll_tmr_t *t, uint32_t period)
{
    LL_ASSERT(t != NULL);
    t->CAPCOM[0].VAL = period; /* period register on this part */
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
/* Channel ch event (CAPn) IM/RIS/MIS/IC bit. */
static inline uint32_t ll_tmr_capcom_irq_mask(uint32_t ch)
{
    return 1U << (1U + ch);
}

static inline void ll_tmr_capcom_config(ll_tmr_t *t, uint32_t ch, const ll_tmr_capcom_t *cc)
{
    LL_ASSERT(t != NULL);
    LL_ASSERT(cc != NULL);
    LL_ASSERT(ch < LL_TMR_CAPCOM_COUNT);

    t->CAPCOM[ch].CTRL = (cc->mode == LL_TMR_CAPCOM_CAPTURE) ? TMR32_CAPCOM_CTRL_CAP_Msk : 0U;
    t->CAPCOM[ch].VAL  = cc->value;
    if (cc->irq_on_event) {
        t->IM |= ll_tmr_capcom_irq_mask(ch);
    }
}

static inline void ll_tmr_capcom_set(ll_tmr_t *t, uint32_t ch, uint32_t compare)
{
    LL_ASSERT(t != NULL);
    LL_ASSERT(ch < LL_TMR_CAPCOM_COUNT);
    t->CAPCOM[ch].VAL = compare;
}

static inline uint32_t ll_tmr_capcom_get(ll_tmr_t *t, uint32_t ch)
{
    LL_ASSERT(t != NULL);
    LL_ASSERT(ch < LL_TMR_CAPCOM_COUNT);
    return t->CAPCOM[ch].VAL;
}

/* ── DMA / ADC trigger gating ───────────────────────────────────────────── */
static inline void ll_tmr_dma_enable(ll_tmr_t *t, uint32_t mask, bool on)
{
    LL_ASSERT(t != NULL);
    if (on) {
        t->DMA_IM |= mask;
    } else {
        t->DMA_IM &= ~mask;
    }
}

/* ADC trigger (ADC_IM on this generation). */
static inline void ll_tmr_trigger_enable(ll_tmr_t *t, uint32_t mask, bool on)
{
    LL_ASSERT(t != NULL);
    if (on) {
        t->ADC_IM |= mask;
    } else {
        t->ADC_IM &= ~mask;
    }
}

#ifdef __cplusplus
}
#endif
