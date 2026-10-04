/**
 * @file ll_pll_vg015.h
 * @brief PLL backend for K1921VG015 (include via <ll_pll.h>).
 *
 * Hardware: one PLLSYS block with a shared VCO and two independent
 * post-divider chains (FOUT0 / FOUT1).
 *
 *   fOUTn = fREF/REFDIV · (FBDIV + FRAC/2^24·DSMEN) / ((1+PDnA)(1+PDnB))
 *
 * Constraints (manual §4.2): REFDIV 1..63; FBDIV 16..160 (integer) or
 * 20..160 (fractional); PDnA 0..7; PDnB 0..63; fREF 10..30 MHz;
 * fVCO 200..1600 MHz; fOUT 390 kHz..60 MHz. Maximize PDnA within each
 * PDnA/PDnB pair. The manual's programming sequence (coefficients while
 * bypassed, then FOUTEN/PLLEN last, then wait PLLSYSSTAT.LOCK) maps onto
 * ll_pll_init().
 *
 * PLLSYSCFG0 layout used here:
 *   [0]      PLLEN
 *   [2:1]    BYP[1:0]   — one bit per output (bit1=OUT0, bit2=OUT1)
 *   [3]      DACEN
 *   [4]      DSMEN
 *   [6:5]    FOUTEN[1:0]— one bit per output (bit5=OUT0, bit6=OUT1)
 *   [12:7]   REFDIV
 *   [15:13]  PD0A
 *   [21:16]  PD0B
 *   [24:22]  PD1A
 *   [30:25]  PD1B
 *
 * `ll_pll_t` represents **one output**.  Both outputs share REFDIV/FBDIV/FRAC
 * in hardware; ll_pll_configure always rewrites them (caller must ensure
 * consistency across outputs — safe when done inside ll_pll_init with bypass).
 *
 * bypass_enable / bypass_disable operate only on the bit for *this* output so
 * that the two outputs can be brought up independently without disturbing each
 * other's bypass state.
 *
 * ll_pll_enable / disable operate only on the FOUTEN bit for this output and
 * manage PLLEN: enable sets PLLEN (idempotent); disable clears FOUTEN for this
 * output and clears PLLEN only when the other output's FOUTEN is also clear.
 *
 * ll_pll_is_locked / ll_pll_wait_lock read PLLSYSSTAT.LOCK — one shared bit.
 *
 * The USB PLL (USB->PLLUSBCFG*) is out of scope.
 */

#pragma once

#ifndef LL_PLL_INTERNAL_INCLUDE
#error "include <ll_pll.h> instead of ll_pll_vg015.h"
#endif

#include <ll_assert.h>
#include <soc.h>

/* Register-layout invariants: detect header drift at compile time. */
_Static_assert(offsetof(RCU_TypeDef, PLLSYSCFG0) == 0x50U, "RCU PLLSYSCFG0 offset drift");
_Static_assert(offsetof(RCU_TypeDef, PLLSYSCFG3) == 0x5CU, "RCU PLLSYSCFG3 offset drift");
_Static_assert(offsetof(RCU_TypeDef, PLLSYSSTAT) == 0x60U, "RCU PLLSYSSTAT offset drift");

/**
 * @brief Descriptor for one PLLSYS output.
 *
 * @c fouten_bit  : mask of this output's bit within the FOUTEN field.
 * @c byp_bit     : mask of this output's bit within the BYP field.
 * @c diva_pos    : shift of this output's PDnA field in PLLSYSCFG0.
 * @c divb_pos    : shift of this output's PDnB field in PLLSYSCFG0.
 * @c diva_msk    : mask of PDnA field.
 * @c divb_msk    : mask of PDnB field.
 */
typedef struct {
    RCU_TypeDef *rcu;
    uint32_t fouten_bit; /**< mask of this output's bit within the FOUTEN field. */
    uint32_t byp_bit;    /**< mask of this output's bit within the BYP field. */
    uint32_t diva_pos;   /**< shift of this output's PDnA field in PLLSYSCFG0. */
    uint32_t divb_pos;   /**< shift of this output's PDnB field in PLLSYSCFG0. */
    uint32_t diva_msk;   /**< mask of PDnA field. */
    uint32_t divb_msk;   /**< mask of PDnB field. */
    uint32_t number;
} ll_pll_t;

/* FOUTEN is a 2-bit field at bit 5; BYP is a 2-bit field at bit 1. */
#define _LL_PLL_VG015_FOUTEN0_BIT (1U << RCU_PLLSYSCFG0_FOUTEN_Pos) /* bit 5 */
#define _LL_PLL_VG015_FOUTEN1_BIT (2U << RCU_PLLSYSCFG0_FOUTEN_Pos) /* bit 6 */
#define _LL_PLL_VG015_BYP0_BIT    (1U << RCU_PLLSYSCFG0_BYP_Pos)    /* bit 1 */
#define _LL_PLL_VG015_BYP1_BIT    (2U << RCU_PLLSYSCFG0_BYP_Pos)    /* bit 2 */

#define LL_PLL0                                                                                  \
    ((ll_pll_t){RCU, _LL_PLL_VG015_FOUTEN0_BIT, _LL_PLL_VG015_BYP0_BIT, RCU_PLLSYSCFG0_PD0A_Pos, \
                RCU_PLLSYSCFG0_PD0B_Pos, RCU_PLLSYSCFG0_PD0A_Msk, RCU_PLLSYSCFG0_PD0B_Msk, 0})

#define LL_PLL1                                                                                  \
    ((ll_pll_t){RCU, _LL_PLL_VG015_FOUTEN1_BIT, _LL_PLL_VG015_BYP1_BIT, RCU_PLLSYSCFG0_PD1A_Pos, \
                RCU_PLLSYSCFG0_PD1B_Pos, RCU_PLLSYSCFG0_PD1A_Msk, RCU_PLLSYSCFG0_PD1B_Msk, 1})
#define LL_PLL_SYS LL_PLL0

#define LL_PLL_F_OUT_M(f_ref_khz, ref_div, fb_mult, frac_num, out_div_a, out_div_b)                               \
    ((unsigned long long)(f_ref_khz) * (((unsigned long long)(fb_mult) << 24) + (unsigned long long)(frac_num)) / \
     ((unsigned long long)(ref_div) * ((unsigned long long)(out_div_a) + 1U) *                                    \
      ((unsigned long long)(out_div_b) + 1U) * (1ULL << 24)))

#define LL_PLL_F_OUT(f_ref_khz, cfg_) \
    LL_PLL_F_OUT_M(f_ref_khz, (cfg_).ref_div, (cfg_).fb_mult, (cfg_).frac_num, (cfg_).out_div_a, (cfg_).out_div_b)

/**
 * @brief Program coefficients for this output.
 *        Rewrites REFDIV, FBDIV, FRAC (shared VCO fields)
 *        and the PDnA/PDnB pair belonging to this output.
 *        PLLEN and BYP are preserved.
 *        FOUTEN for this output is left unchanged; ll_pll_enable sets it.
 * @note frac_mod is ignored (VG015 hardware denominator is always 2²⁴).
 * @note Both outputs must use the same ref_div / fb_mult / frac_num.
 */
static inline void ll_pll_configure(ll_pll_t p, ll_pll_config_t cfg)
{
    bool dsmen = cfg.frac_num != 0U;
    LL_ASSERT(cfg.ref_div >= 1U && cfg.ref_div <= 63U);
    LL_ASSERT(cfg.fb_mult >= (dsmen ? 20U : 16U) && cfg.fb_mult <= 160U);
    LL_ASSERT(cfg.frac_num <= 0x00FFFFFFU);
    LL_ASSERT(cfg.out_div_a <= 7U && cfg.out_div_b <= 63U);

    /* Preserve PLLEN, BYP, and the *other* output's PDnA/PDnB/FOUTEN. */
    uint32_t keep_msk =
        RCU_PLLSYSCFG0_PLLEN_Msk | RCU_PLLSYSCFG0_BYP_Msk | RCU_PLLSYSCFG0_FOUTEN_Msk |
        (~p.diva_msk & ~p.divb_msk /* other output's dividers */
         & (RCU_PLLSYSCFG0_PD0A_Msk | RCU_PLLSYSCFG0_PD0B_Msk | RCU_PLLSYSCFG0_PD1A_Msk | RCU_PLLSYSCFG0_PD1B_Msk));

    uint32_t v = p.rcu->PLLSYSCFG0 & keep_msk;

    v |= ((uint32_t)cfg.ref_div << RCU_PLLSYSCFG0_REFDIV_Pos) | ((uint32_t)cfg.out_div_a << p.diva_pos) |
         ((uint32_t)cfg.out_div_b << p.divb_pos);

    if (dsmen) {
        v |= RCU_PLLSYSCFG0_DSMEN_Msk | RCU_PLLSYSCFG0_DACEN_Msk;
    } else {
        v &= ~(RCU_PLLSYSCFG0_DSMEN_Msk | RCU_PLLSYSCFG0_DACEN_Msk);
    }
    p.rcu->PLLSYSCFG0 = v;
    p.rcu->PLLSYSCFG1 = dsmen ? cfg.frac_num : 0U;
    p.rcu->PLLSYSCFG2 = cfg.fb_mult;
    p.rcu->PLLSYSCFG3 &= ~RCU_PLLSYSCFG3_REFSEL_Msk;
}

/**
 * @brief Enable this output and power up the VCO.
 *
 * Sets this output's FOUTEN bit and PLLEN.
 */
static inline void ll_pll_enable(ll_pll_t p)
{
    p.rcu->PLLSYSCFG0 |= p.fouten_bit | RCU_PLLSYSCFG0_PLLEN_Msk;
}

/**
 * @brief Disable this output; power down VCO only if no output remains active.
 */
static inline void ll_pll_disable(ll_pll_t p)
{
    uint32_t v = p.rcu->PLLSYSCFG0 & ~p.fouten_bit;
    /* Clear PLLEN when both FOUTEN bits are now zero. */
    if ((v & RCU_PLLSYSCFG0_FOUTEN_Msk) == 0U) {
        v &= ~RCU_PLLSYSCFG0_PLLEN_Msk;
    }
    p.rcu->PLLSYSCFG0 = v;
}

/** @brief Bypass this output (fREF → output). Does not affect the other output. */
static inline void ll_pll_bypass_enable(ll_pll_t p)
{
    p.rcu->PLLSYSCFG0 |= p.byp_bit;
}

/** @brief Stop bypassing this output. Does not affect the other output. */
static inline void ll_pll_bypass_disable(ll_pll_t p)
{
    p.rcu->PLLSYSCFG0 &= ~p.byp_bit;
}

/** @brief Sample PLLSYSSTAT.LOCK (shared level bit). */
static inline bool ll_pll_is_locked(ll_pll_t p)
{
    return (p.rcu->PLLSYSSTAT & RCU_PLLSYSSTAT_LOCK_Msk) != 0U;
}

/**
 * @brief Bounded busy-wait for lock (shared lock bit).

 * @return @c true once locked, @c false when @p spins expires.
 */
static inline bool ll_pll_wait_lock(ll_pll_t p, uint32_t spins)
{
    while (spins--) {
        if ((p.rcu->PLLSYSSTAT & RCU_PLLSYSSTAT_LOCK_Msk) != 0U) {
            return true;
        }
    }
    return false;
}
