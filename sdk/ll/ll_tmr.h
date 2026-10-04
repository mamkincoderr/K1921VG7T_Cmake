/**
 * @file ll_tmr.h
 * @brief Low-level timer (TMR) driver — unified API over two register layouts.
 *
 * Same router pattern as ll_dma / ll_plic. Two backends:
 *   - k1921vg015 (Cloudbear BM-310): legacy layout — clock divider in CTRL.DIV,
 *     no PERIOD register (period lives in CAPCOM[0].VAL), combined DMA_IM, ADC_IM.
 *   - k1921vg1t/3t/5t/7t (Syntacore): modern layout — CLKDIV + PERIOD registers,
 *     split DMA_TXIM/DMA_RXIM, EXTEVT_IM external-event trigger.
 *
 * Within a SoC the 16-bit and 32-bit timer instances are layout-identical, so one
 * function family serves both; LL_TMR(inst) casts any timer instance pointer to
 * the backend's canonical ll_tmr_t. There is no separate enable bit: CTRL.MODE is
 * the run control, so ll_tmr_start() takes the mode and ll_tmr_init() leaves the
 * timer stopped.
 *
 * Backends are reached only through this header — do not include them directly.
 *
 * @defgroup ll_tmr LL TMR
 * @{
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Count mode — values equal CTRL.MODE on both generations. */
typedef enum {
    LL_TMR_MODE_STOP       = 0, /**< halted */
    LL_TMR_MODE_UP         = 1, /**< 0 -> period, then reload (period = PERIOD / CAPCOM[0].VAL) */
    LL_TMR_MODE_CONTINUOUS = 2, /**< free-run 0 -> 0xFFFFFFFF */
    LL_TMR_MODE_UPDOWN     = 3, /**< 0 -> period -> 0 */
} ll_tmr_mode_t;

/** @brief Clock source (CTRL.CLKSEL). */
typedef enum {
    LL_TMR_CLK_SYS = 0, /**< internal system clock */
    LL_TMR_CLK_EXT = 1, /**< external clock input */
} ll_tmr_clksel_t;

/** @brief CAPCOM channel direction (CAPCOM[ch].CTRL.CAP). */
typedef enum {
    LL_TMR_CAPCOM_COMPARE = 0, /**< output compare */
    LL_TMR_CAPCOM_CAPTURE = 1, /**< input capture */
} ll_tmr_capcom_mode_t;

/** @brief Static timebase setup. Applied by ll_tmr_init; does NOT start the timer. */
typedef struct {
    ll_tmr_clksel_t clksel; /**< CTRL.CLKSEL */
    uint32_t divider;       /**< CTRL.DIV field (legacy) or CLKDIV register (modern) */
    uint32_t period;        /**< PERIOD register (modern) or CAPCOM[0].VAL (legacy) */
} ll_tmr_config_t;

/** @brief One capture/compare channel configuration. */
typedef struct {
    ll_tmr_capcom_mode_t mode; /**< compare vs capture */
    uint32_t value;            /**< compare value -> CAPCOM[ch] value register */
    bool irq_on_event;         /**< also enable this channel's IRQ in IM */
} ll_tmr_capcom_t;

/** @brief Cast any timer instance (TMR0 / TMR32 / TMR16_0 ...) to ll_tmr_t*. */
#define LL_TMR(inst) ((ll_tmr_t *)(inst))

/** @brief Period (timer overflow) event bit — bit 0 of IM/RIS/MIS/IC/DMA_*IM. */
#define LL_TMR_EVT_PERIOD 0x1u

#ifdef __cplusplus
}
#endif

#if defined(K1921VG015)
#include <ll_tmr_vg015.h>
#elif defined(K1921VG1T) || defined(K1921VG3T) || defined(K1921VG5T) || defined(K1921VG7T)
#include <ll_tmr_xt.h>
#else
#error "ll_tmr.h: unsupported SoC — no timer backend"
#endif

/** @} */
