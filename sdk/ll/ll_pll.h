/**
 * @file ll_pll.h
 * @brief Low-level PLL driver for the K1921VG family.
 *
 * `ll_pll_t` represents a **single output frequency** — the unit a caller
 * cares about. On VGxT each `ll_pll_t` maps 1-to-1 to a PLL hardware block.
 * On VG015 the single PLLSYS block has two independent post-divider chains
 * (FOUT0 / FOUT1) that share one VCO (common REFDIV and FBDIV); each chain
 * is its own `ll_pll_t`.
 *
 * Because the two VG015 outputs share N and R, calling `ll_pll_configure` on
 * either one rewrites the common REFDIV/FBDIV/FRAC fields — both outputs
 * must therefore use the same `ref_div`, `fb_mult`, and `frac_num` values.
 * The driver does not enforce cross-output consistency; it is the caller's
 * responsibility. Safe usage: configure both outputs while PLLSYS is in
 * bypass (i.e. inside `ll_pll_init` or with bypass engaged manually).
 *
 *   ll_pll_configure(p, cfg)   — program coefficients (PLL run-state kept)
 *   ll_pll_enable / disable    — start/stop the PLL and its output
 *   ll_pll_bypass_enable/disable — route fREF straight to the output
 *   ll_pll_is_locked           — sample lock status
 *   ll_pll_wait_lock(p, spins) — bounded busy-wait for lock
 *   ll_pll_init(p, cfg, spins) — composite bring-up (see below)
 *
 * `ll_pll_config_t` describes the parameters for **one output**:
 *
 *     fOUT = fREF / ref_div × (fb_mult + frac_num / frac_mod) / ((out_div_a+1)(out_div_b+1))
 *
 * `ref_div`, `fb_mult`, `frac_num`, `frac_mod` set the VCO frequency and are
 * shared between VG015 outputs (must match). `out_div_a` and `out_div_b` are
 * per-output. `frac_mod` is ignored on VG015 (hardware denominator fixed at
 * 2²⁴); pass 0 for the portable default (2²⁴ on VGxT, i.e. MOD=0xFFFFFF).
 *
 * The instance descriptors are:
 *
 *   | SoC        | Instances                    |
 *   |------------|------------------------------|
 *   | VG015      | LL_PLL0, LL_PLL1             |
 *   | VG1T, VG3T | LL_PLL0, LL_PLL1, LL_PLL2    |
 *   | VG5T, VG7T | LL_PLL0                      |

 LL_PLL_SYS is an alias for LL_PLL0.
 *
 * Out of scope: SYSCLK source switching, FLASH latency, the VG015 USB PLL
 * (lives in the USB block).
 *
 * @defgroup ll_pll LL PLL
 * @{
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

/**
 * @brief Parameters for one PLL output.
 *
 * fOUT = fREF / ref_div × (fb_mult + frac_num / frac_mod)
 *                        / ((out_div_a + 1)(out_div_b + 1))
 *
 * @note On VG015, `ref_div`, `fb_mult`, `frac_num` are shared between the
 *       two outputs and must be identical when configuring OUT0 and OUT1.
 *       `frac_mod` is unused on VG015 (fixed 2²⁴ denominator in hardware).
 *
 * @note On VGxT, `frac_mod` selects the sigma-delta modulus:
 *       0 or (1u<<24) → default MOD = 0xFFFFFF (≈2²⁴, <0.1 ppm deviation).
 *       Values 1..0xFFFFFF are written as MOD = frac_mod − 1.
 *       Ignored when frac_num == 0.
 */
typedef struct {
    uint8_t ref_div;   /**< Reference divisor ≥ 1. Shared on VG015. */
    uint16_t fb_mult;  /**< Integer feedback multiplier N. Shared on VG015. */
    uint32_t frac_num; /**< Fractional numerator; 0 = integer mode. Shared on VG015. */
    uint32_t frac_mod; /**< Fractional modulus (VGxT only); 0 = default (2²⁴). */
    uint8_t out_div_a; /**< Output divider A: effective = out_div_a + 1, range 0..7. */
    uint8_t out_div_b; /**< Output divider B: effective = out_div_b + 1, range 0..63. */
    uint8_t prediv;    /**< Pred divider (VGxT only). */
} ll_pll_config_t;

/** Integer mode, ÷1 reference, ÷1 outputs, N=16 (valid on every family). */
#define LL_PLL_CONFIG_DEFAULT {.ref_div = 1, .fb_mult = 16}

#define LL_PLL_INTERNAL_INCLUDE
#if defined(K1921VG015)
#include "ll_pll_vg015.h"
#elif defined(K1921VG1T) || defined(K1921VG3T) || defined(K1921VG5T) || defined(K1921VG7T)
#include "ll_pll_vgxt.h"
#else
#error "ll_pll.h: no implementation for the selected SoC"
#endif
#undef LL_PLL_INTERNAL_INCLUDE

/**
 * @brief Composite bring-up: bypass → configure → enable → wait lock → unbypass.
 *
 * On lock timeout returns @c false and leaves the bypass engaged, so
 * downstream consumers keep running on the reference clock.
 *
 * @param p     Instance descriptor.
 * @param cfg   Portable coefficient set (see @c ll_pll_config_t above).
 * @param spins Busy-wait budget for the lock poll (loop iterations).
 * @return @c true once locked, @c false on timeout.
 */
static inline bool ll_pll_init(ll_pll_t p, ll_pll_config_t cfg, uint32_t spins)
{
    ll_pll_bypass_enable(p);
    ll_pll_configure(p, cfg);
    ll_pll_enable(p);
    if (!ll_pll_wait_lock(p, spins)) {
        return false; /* still bypassed — system stays on fREF */
    }
    ll_pll_bypass_disable(p);
    return true;
}

#ifdef __cplusplus
}
#endif

/** @} */ /* end of ll_pll group */
