/**
 * @file ll_pll_vgxt.h
 * @brief PLL backend for K1921VG1T/3T/5T/7T (include via <ll_pll.h>).
 *
 * One PLL IP, two register presentations:
 *  - VG1T/VG3T: three instances as cluster RCU->PLL[0..2] {CFG,DIV,FRAC,MOD},
 *    lock = level bits in RCU->PLLSTAT (bit n = instance n).
 *  - VG5T/VG7T: one instance as flat RCU->PLLCFG/PLLDIV/PLLFRAC/PLLMOD,
 *    lock = sticky RCU->INTSTAT.PLLLOCK (raise event, write-1-to-clear).
 *    ll_pll_wait_lock() clears the stale event first, then polls; calling
 *    it on an already-locked PLL therefore times out — use it only right
 *    after enabling the PLL (ll_pll_init does this).
 *
 * Frequency model (manual §4.2 of the VG1T RM):
 *   Fvco = Fref · N · PREDIV / RDIV,  N = NDIV + FRAC/MOD
 *   Fout = Fvco / (PREDIV · DIV1A · DIV1B)
 * where the *effective* divisors come from raw fields as: RDIV+1, DIV1A+1,
 * DIV1B+1; PREDIV raw 0|1|2|3 → 1|1|2|4; NDIV used directly.
 */

#pragma once

#ifndef LL_PLL_INTERNAL_INCLUDE
#error "include <ll_pll.h> instead of ll_pll_vgxt.h"
#endif

#include <ll_assert.h>
#include <soc.h>

/* Field positions are identical on all four SoCs; only the macro prefix
 * differs (cluster: RCU_PLL_CFG_* / flat: RCU_PLLCFG_*). Alias once. */
#if defined(K1921VG1T) || defined(K1921VG3T)
#define _LL_PLL_CFG_PD_MSK      RCU_PLL_CFG_PD_Msk
#define _LL_PLL_CFG_BYPASS_MSK  RCU_PLL_CFG_BYPASS_Msk
#define _LL_PLL_CFG_FOUTEN_MSK  RCU_PLL_CFG_FOUTEN_Msk
#define _LL_PLL_CFG_CLKSEL_POS  RCU_PLL_CFG_CLKSEL_Pos
#define _LL_PLL_CFG_ST_POS      RCU_PLL_CFG_ST_Pos
#define _LL_PLL_CFG_PFD_POS     RCU_PLL_CFG_PFD_Pos
#define _LL_PLL_CFG_CP_POS      RCU_PLL_CFG_CP_Pos
#define _LL_PLL_CFG_VCOMODE_POS RCU_PLL_CFG_VCOMODE_Pos
#define _LL_PLL_DIV_DIV1A_POS   RCU_PLL_DIV_DIV1A_Pos
#define _LL_PLL_DIV_DIV1B_POS   RCU_PLL_DIV_DIV1B_Pos
#define _LL_PLL_DIV_PREDIV_POS  RCU_PLL_DIV_PREDIV_Pos
#define _LL_PLL_DIV_NNCLR_POS   RCU_PLL_DIV_NNCLR_Pos
#define _LL_PLL_DIV_RNCLR_POS   RCU_PLL_DIV_RNCLR_Pos
#define _LL_PLL_DIV_RDIV_POS    RCU_PLL_DIV_RDIV_Pos
#define _LL_PLL_DIV_NDIV_POS    RCU_PLL_DIV_NDIV_Pos
#else /* K1921VG5T || K1921VG7T */
#define _LL_PLL_CFG_PD_MSK      RCU_PLLCFG_PD_Msk
#define _LL_PLL_CFG_BYPASS_MSK  RCU_PLLCFG_BYPASS_Msk
#define _LL_PLL_CFG_FOUTEN_MSK  RCU_PLLCFG_FOUTEN_Msk
#define _LL_PLL_CFG_CLKSEL_POS  RCU_PLLCFG_CLKSEL_Pos
#define _LL_PLL_CFG_ST_POS      RCU_PLLCFG_ST_Pos
#define _LL_PLL_CFG_PFD_POS     RCU_PLLCFG_PFD_Pos
#define _LL_PLL_CFG_CP_POS      RCU_PLLCFG_CP_Pos
#define _LL_PLL_CFG_VCOMODE_POS RCU_PLLCFG_VCOMODE_Pos
#define _LL_PLL_DIV_DIV1A_POS   RCU_PLLDIV_DIV1A_Pos
#define _LL_PLL_DIV_DIV1B_POS   RCU_PLLDIV_DIV1B_Pos
#define _LL_PLL_DIV_PREDIV_POS  RCU_PLLDIV_PREDIV_Pos
#define _LL_PLL_DIV_NNCLR_POS   RCU_PLLDIV_NNCLR_Pos
#define _LL_PLL_DIV_RNCLR_POS   RCU_PLLDIV_RNCLR_Pos
#define _LL_PLL_DIV_RDIV_POS    RCU_PLLDIV_RDIV_Pos
#define _LL_PLL_DIV_NDIV_POS    RCU_PLLDIV_NDIV_Pos
#endif

/* Register-layout invariants: detect header drift at compile time. */
#if defined(K1921VG1T)
_Static_assert(offsetof(RCU_TypeDef, PLL[0]) == 0x100U, "RCU PLL[0] offset drift");
_Static_assert(offsetof(RCU_TypeDef, PLL[1]) == 0x110U, "RCU PLL cluster stride drift");
_Static_assert(offsetof(RCU_TypeDef, PLLSTAT) == 0x130U, "RCU PLLSTAT offset drift");
#elif defined(K1921VG3T)
_Static_assert(offsetof(RCU_TypeDef, PLL[0]) == 0x100U, "RCU PLL[0] offset drift");
_Static_assert(offsetof(RCU_TypeDef, PLL[1]) == 0x110U, "RCU PLL cluster stride drift");
_Static_assert(offsetof(RCU_TypeDef, PLLSTAT) == 0xF0U, "RCU PLLSTAT offset drift");
#elif defined(K1921VG5T)
_Static_assert(offsetof(RCU_TypeDef, PLLCFG) == 0x40U, "RCU PLLCFG offset drift");
_Static_assert(offsetof(RCU_TypeDef, PLLMOD) == 0x4CU, "RCU PLLMOD offset drift");
_Static_assert(offsetof(RCU_TypeDef, INTSTAT) == 0xC4U, "RCU INTSTAT offset drift");
#elif defined(K1921VG7T)
_Static_assert(offsetof(RCU_TypeDef, PLLCFG) == 0x40U, "RCU PLLCFG offset drift");
_Static_assert(offsetof(RCU_TypeDef, PLLMOD) == 0x4CU, "RCU PLLMOD offset drift");
_Static_assert(offsetof(RCU_TypeDef, INTSTAT) == 0x3CU, "RCU INTSTAT offset drift");
#endif

/**
 * @brief PLL instance descriptor. Construct via the LL_PLL_* macros only.
 */
typedef struct {
    volatile uint32_t *cfg;     /**< CFG register. */
    volatile uint32_t *div;     /**< DIV register. */
    volatile uint32_t *frac;    /**< FRAC register. */
    volatile uint32_t *mod;     /**< MOD register. */
    volatile uint32_t *lockreg; /**< PLLSTAT (level) or INTSTAT (sticky). */
    uint32_t lock_msk;          /**< Lock bit within @c lockreg. */
    bool lock_is_sticky;        /**< INTSTAT event flag (W1C) vs level bit. */
    uint32_t number;
} ll_pll_t;

/* `ll_pll_config_t` and LL_PLL_CONFIG_DEFAULT are the portable definitions
 * in ll_pll.h; this backend only translates them. Vendor-recommended analog
 * tuning applied by ll_pll_configure (not exposed in the portable model). */
#define _LL_PLL_VGXT_CP                 9U      /**< Phase-detector current-switch mode. */
#define _LL_PLL_VGXT_PFD                3U      /**< Phase-detector current-switch mode. */
#define _LL_PLL_VGXT_VCOMODE            1U      /**< VCO subband select. */
#define _LL_PLL_VGXT_VCOMODE_USE_RPEDIV 0b1000U /**< Enable prediv*/
#define _LL_PLL_VGXT_PREDIV             1U      /**< Pre-divider raw 1 → ÷1 (output path). */
#define _LL_PLL_VGXT_ST_FRAC            1U      /**< Sigma-delta order selected in frac mode. */
#define _LL_PLL_VGXT_MOD_DEFAULT                                               \
    0x00FFFFFFU /**< Fractional denominator: 2²⁴−1 approximates the portable \
                 *   model's 2²⁴ to within <0.1 ppm. */

/* Instance descriptors. */
#if defined(K1921VG1T)
#define _LL_PLL_VGT(i, lockmsk)                                                          \
    ((ll_pll_t){&RCU->PLL[i].CFG, &RCU->PLL[i].DIV, &RCU->PLL[i].FRAC, &RCU->PLL[i].MOD, \
                (volatile uint32_t *)&RCU->PLLSTAT, (lockmsk), false, i})
#define LL_PLL0 _LL_PLL_VGT(0, RCU_PLLSTAT_SYSPLLLOCK_Msk)
#define LL_PLL1 _LL_PLL_VGT(1, RCU_PLLSTAT_PLL1LOCK_Msk)
#define LL_PLL2 _LL_PLL_VGT(2, RCU_PLLSTAT_PLL2LOCK_Msk)
#elif defined(K1921VG3T)
#define _LL_PLL_VGT(i, lockmsk)                                                          \
    ((ll_pll_t){&RCU->PLL[i].CFG, &RCU->PLL[i].DIV, &RCU->PLL[i].FRAC, &RCU->PLL[i].MOD, \
                (volatile uint32_t *)&RCU->PLLSTAT, (lockmsk), false, i})
#define LL_PLL0 _LL_PLL_VGT(0, RCU_PLLSTAT_PLL0LOCK_Msk)
#define LL_PLL1 _LL_PLL_VGT(1, RCU_PLLSTAT_PLL1LOCK_Msk)
#define LL_PLL2 _LL_PLL_VGT(2, RCU_PLLSTAT_PLL2LOCK_Msk)
#else /* K1921VG5T || K1921VG7T */
#define LL_PLL0                                                                                                        \
    ((ll_pll_t){&RCU->PLLCFG, &RCU->PLLDIV, &RCU->PLLFRAC, &RCU->PLLMOD, &RCU->INTSTAT, RCU_INTSTAT_PLLLOCK_Msk, true, \
                0U})
#endif
#define LL_PLL_SYS LL_PLL0

#define LL_PLL_F_OUT_M(f_ref_khz, ref_div, fb_mult, frac_num, frac_mod, out_div_a, out_div_b, prediv)      \
    ((unsigned long long)(f_ref_khz) * (unsigned long long)(prediv) *                                      \
     (((unsigned long long)(fb_mult) * (unsigned long long)(frac_mod)) + (unsigned long long)(frac_num)) / \
     ((unsigned long long)((ref_div) + 1U) * (unsigned long long)((out_div_a) + 1U) *                      \
      (unsigned long long)((out_div_b) + 1U) * (unsigned long long)(frac_mod)))

#define LL_PLL_F_OUT(f_ref_khz, cfg)                                                                         \
    LL_PLL_F_OUT_M(f_ref_khz, (cfg).ref_div, (cfg).fb_mult, (cfg).frac_num, (cfg).frac_mod, (cfg).out_div_a, \
                   (cfg).out_div_b, (cfg).prediv)

/**
 * @brief Translate the portable config into the CFG/DIV/FRAC/MOD registers.
 *        Preserves PD and BYPASS; does not enable the output (see
 *        ll_pll_enable) and clears FOUTEN if it was set — reconfiguring a
 *        running PLL stops its output until the next ll_pll_enable. Always
 *        sets NNCLR/RNCLR. Reference is HSE (CLKSEL=0); PREDIV is fixed at
 *        ÷1 and PFD/VCOMODE take vendor defaults. Fractional mode (frac_num
 *        ≠ 0) sets MOD (by default 2²⁴−1) and a 1st-order sigma-delta (ST=1).
 */
static inline void ll_pll_configure(ll_pll_t p, ll_pll_config_t cfg)
{
    LL_ASSERT(cfg.ref_div >= 1U && cfg.ref_div <= 64U);  /* RDIV = ref_div-1, 0..63 */
    LL_ASSERT(cfg.fb_mult >= 1U && cfg.fb_mult <= 255U); /* NDIV is 8-bit */
    LL_ASSERT(cfg.frac_mod <= 0x00FFFFFFU);
    LL_ASSERT(cfg.frac_num <= cfg.frac_mod);
    LL_ASSERT(cfg.out_div_a <= 7U);
    LL_ASSERT(cfg.out_div_b <= 63U);
    LL_ASSERT(cfg.prediv == 1U || cfg.prediv == 2U || cfg.prediv == 4U);
    const uint32_t mod_value = (cfg.frac_mod ? cfg.frac_mod : _LL_PLL_VGXT_MOD_DEFAULT);
    const uint32_t vcmode =
        cfg.prediv > 1U ? (_LL_PLL_VGXT_VCOMODE_USE_RPEDIV | _LL_PLL_VGXT_VCOMODE) : _LL_PLL_VGXT_VCOMODE;

    *p.div = ((uint32_t)cfg.out_div_a << _LL_PLL_DIV_DIV1A_POS) |  //
             ((uint32_t)cfg.out_div_b << _LL_PLL_DIV_DIV1B_POS) |  //
             ((uint32_t)cfg.prediv << _LL_PLL_DIV_PREDIV_POS) |    //
             (1U << _LL_PLL_DIV_NNCLR_POS) |                       //
             (1U << _LL_PLL_DIV_RNCLR_POS) |                       //
             ((uint32_t)(cfg.ref_div) << _LL_PLL_DIV_RDIV_POS) |   //
             ((uint32_t)cfg.fb_mult << _LL_PLL_DIV_NDIV_POS);

    *p.frac     = cfg.frac_num ? cfg.frac_num : 1U;
    *p.mod      = cfg.frac_num ? mod_value : 1U;
    uint32_t st = cfg.frac_num ? _LL_PLL_VGXT_ST_FRAC : 0U;

    uint32_t v = *p.cfg & (_LL_PLL_CFG_PD_MSK | _LL_PLL_CFG_BYPASS_MSK);
    v |= (st << _LL_PLL_CFG_ST_POS) |                 //
         (_LL_PLL_VGXT_PFD << _LL_PLL_CFG_PFD_POS) |  //
         (_LL_PLL_VGXT_CP << _LL_PLL_CFG_CP_POS) |    //
         (vcmode << _LL_PLL_CFG_VCOMODE_POS);
    *p.cfg = v;
}

/** @brief Power up the PLL and enable its output. */
static inline void ll_pll_enable(ll_pll_t p)
{
    *p.cfg &= ~_LL_PLL_CFG_PD_MSK;
    *p.cfg |= _LL_PLL_CFG_FOUTEN_MSK;
}

/** @brief Disable the output and power the PLL down. */
static inline void ll_pll_disable(ll_pll_t p)
{
    *p.cfg &= ~_LL_PLL_CFG_FOUTEN_MSK;
    *p.cfg |= _LL_PLL_CFG_PD_MSK;
}

/** @brief Route fREF straight through to the output. */
static inline void ll_pll_bypass_enable(ll_pll_t p)
{
    *p.cfg |= _LL_PLL_CFG_BYPASS_MSK;
}

/** @brief Stop bypassing; output follows the synthesizer. */
static inline void ll_pll_bypass_disable(ll_pll_t p)
{
    *p.cfg &= ~_LL_PLL_CFG_BYPASS_MSK;
}

/**
 * @brief Sample lock status.
 *
 * On VG5T/7T this reads the latched lock-*raise* event, not a level — it
 * stays set until cleared and never clears on lock loss.
 */
static inline bool ll_pll_is_locked(ll_pll_t p)
{
    return (*p.lockreg & p.lock_msk) != 0U;
}

/**
 * @brief Bounded busy-wait for lock.
 *
 * Sticky-flag SoCs (VG5T/7T): the stale event is cleared (W1C) before
 * polling, so call this only right after enabling the PLL.
 *
 * @return @c true once locked, @c false when @p spins expires.
 */
static inline bool ll_pll_wait_lock(ll_pll_t p, uint32_t spins)
{
    if (p.lock_is_sticky) {
        *p.lockreg = p.lock_msk; /* W1C: drop stale raise event */
    }
    while (spins--) {
        if ((*p.lockreg & p.lock_msk) != 0U) {
            return true;
        }
    }
    return false;
}
