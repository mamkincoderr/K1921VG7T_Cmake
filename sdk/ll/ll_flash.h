#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <ll_assert.h>
#include <soc.h>

#if !defined(K1921VG015) && !defined(K1921VG1T) && !defined(K1921VG3T) && !defined(K1921VG5T) && !defined(K1921VG7T)
#error "ll_flash.h: no implementation for the selected SoC"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    volatile uint32_t *ctrl;
    uint32_t lat_pos;
    uint32_t lat_msk;
    volatile uint32_t *stat;
    uint32_t busy_msk;
} ll_flash_periph_t;

static inline void ll_flash_set_latency(ll_flash_periph_t p, uint8_t latency)
{
    LL_ASSERT(((uint32_t)latency << p.lat_pos) <= p.lat_msk);
    uint32_t v = *p.ctrl;
    v &= ~p.lat_msk;
    v |= ((uint32_t)latency << p.lat_pos) & p.lat_msk;
    *p.ctrl = v;
}

static inline uint8_t ll_flash_get_latency(ll_flash_periph_t p)
{
    return (uint8_t)((*p.ctrl & p.lat_msk) >> p.lat_pos);
}

static inline bool ll_flash_is_busy(ll_flash_periph_t p)
{
    return (*p.stat & p.busy_msk) != 0U;
}

static inline bool ll_flash_wait_ready(ll_flash_periph_t p, int32_t spins)
{
    const bool forever = (spins < 0);
    while (forever || --spins) {
        if (!ll_flash_is_busy(p)) {
            return true;
        }
    }
    return false;
}

// NOLINTBEGIN
static inline uint8_t ll_flash_latency_from_freq(uint32_t freq_khz)
{
#ifdef K1921VG015
    return ((freq_khz < 30000UL)    ? 0U
            : (freq_khz < 60000UL)  ? 1U
            : (freq_khz < 90000UL)  ? 2U
            : (freq_khz < 120000UL) ? 3U
            : (freq_khz < 150000UL) ? 4U
                                    : 5U);
#else
    return ((freq_khz < 40000UL)    ? 0U
            : (freq_khz < 80000UL)  ? 1U
            : (freq_khz < 120000UL) ? 2U
            : (freq_khz < 160000UL) ? 3U
            : (freq_khz < 200000UL) ? 4U
                                    : 5U);
#endif
}
// NOLINTEND

static inline void ll_flash_set_latency_for_freq(ll_flash_periph_t p, uint32_t freq_khz)
{
    ll_flash_set_latency(p, ll_flash_latency_from_freq(freq_khz));
}

#define _LL_FLASH(ctrl_, lat_pos_, lat_msk_, stat_, busy_msk_) \
    ((ll_flash_periph_t){&(ctrl_), (lat_pos_), (lat_msk_), &(stat_), (busy_msk_)})

#if defined(K1921VG015)

#define LL_FLASH _LL_FLASH(FLASH->CTRL, FLASH_CTRL_LAT_Pos, FLASH_CTRL_LAT_Msk, FLASH->STAT, FLASH_STAT_BUSY_Msk)

#elif defined(K1921VG1T)

#define LL_FLASH_MAIN \
    _LL_FLASH(FLASHM->CTRL, FLASHM_CTRL_LAT_Pos, FLASHM_CTRL_LAT_Msk, FLASHM->STAT, FLASHM_STAT_BUSY_Msk)
#define LL_FLASH_DATA \
    _LL_FLASH(FLASHD->CTRL, FLASHD_CTRL_LAT_Pos, FLASHD_CTRL_LAT_Msk, FLASHD->STAT, FLASHD_STAT_BUSY_Msk)
#define LL_FLASH LL_FLASH_MAIN

#elif defined(K1921VG3T) || defined(K1921VG5T) || defined(K1921VG7T)

#define LL_FLASH _LL_FLASH(FLASH->CTRL, FLASH_CTRL_LAT_Pos, FLASH_CTRL_LAT_Msk, FLASH->STAT, FLASH_STAT_BUSY_Msk)

#endif

#ifdef __cplusplus
}
#endif

/** @} */
