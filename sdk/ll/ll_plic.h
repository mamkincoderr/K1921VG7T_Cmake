/**
 * @file ll_plic.h
 * @brief Low-level PLIC (Platform-Level Interrupt Controller) driver.
 *
 * The PLIC is implemented with two structurally different register maps on
 * this MCU family, so this header is a thin router (rulebook §5.2 fork):
 *
 *   - k1921vg015 (Cloudbear BM-310): standard/compact PLIC at 0x0C000000,
 *     two contexts (M-mode, U-mode) exposed as named registers.
 *   - k1921vg1t/3t/5t/7t (Syntacore SCR4/SCR5): banked PLIC at 0xFE000000,
 *     contexts as a 64-entry array indexed by (hart, mode).
 *
 * Both backends expose the identical public API below. Callers include only
 * this header. A "context" is a (hart, mode) consumer of interrupts; build a
 * context index with LL_PLIC_CTX(hart, mode) and pass it to the per-context
 * functions.
 *
 * Public API (see backend headers for the static inline definitions):
 *   void     ll_plic_set_priority(uint32_t line, uint32_t prio);
 *   uint32_t ll_plic_get_priority(uint32_t line);
 *   bool     ll_plic_is_pending(uint32_t line);
 *   void     ll_plic_enable(uint32_t ctx, uint32_t line, bool on);
 *   bool     ll_plic_is_enabled(uint32_t ctx, uint32_t line);
 *   void     ll_plic_set_threshold(uint32_t ctx, uint32_t thr);
 *   uint32_t ll_plic_get_threshold(uint32_t ctx);
 *   uint32_t ll_plic_claim(uint32_t ctx);
 *   void     ll_plic_complete(uint32_t ctx, uint32_t id);
 *
 * @defgroup ll_plic LL PLIC
 * @{
 */

#pragma once

#if defined(K1921VG015)
#include <ll_plic_vg015.h>
#elif defined(K1921VG1T) || defined(K1921VG3T) || defined(K1921VG5T) || defined(K1921VG7T)
#include <ll_plic_xt.h>
#else
#error "ll_plic.h: no implementation for the selected SoC"
#endif

/** @} */
