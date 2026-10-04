/**
 * @file ll_rcu.h
 * @brief Low-level Reset and Clock Unit (RCU) driver for the K1921VG family.
 *
 * Two layers of clock-and-reset state need to be controlled to bring a
 * peripheral up on these MCUs:
 *
 *  1. **Bus-level gate.** Every peripheral lives on AHB or one of the APB
 *     bridges; that bus has a clock-gate register (`CGCFG*`) and a
 *     reset-disable register (`RSTDIS*`). The bus split differs per SoC:
 *
 *     | SoC     | Buses                               |
 *     |---------|-------------------------------------|
 *     | VG015   | AHB / APB                           |
 *     | VG1T    | AHB / APB0 / APB1 / APB2            |
 *     | VG3T    | AHB / APB0 / APB1                   |
 *     | VG5T    | AHB / APB                           |
 *     | VG7T    | AXI / AHB / APB                     |
 *
 *  2. **Per-instance clock generator.** Each UART and SPI has its own
 *     `*CFG[i]` (or `*CLKCFG[i]` on VG015) packing `CLKEN`, `RSTDIS`,
 *     `CLKSEL`, `DIVEN`, `DIVN`. The bit positions of those fields are
 *     different between VG015 and the VG1T-family:
 *
 *     | SoC family | CLKEN | RSTDIS | CLKSEL | DIVEN | DIVN |
 *     |------------|-------|--------|--------|-------|------|
 *     | VG015      |   0   |   8    |   16   |  20   |  24  |
 *     | VG1T/3T/5T/7T | 0  |   4    |   8    |  12   |  16  |
 *
 * The intermediate layer makes both layers callable through the same API:
 * each `LL_RCU_<peri>` macro expands to a @ref ll_rcu_periph_t literal that
 * carries pointers to *that SoC's* concrete `CGCFG*` / `RSTDIS*` / `*CFG[i]`
 * registers along with the field positions. GPIO and other peripherals
 * without a per-instance generator get @c clkcfg=NULL, in which case the
 * generator helpers become no-ops.
 *
 * Typical bring-up:
 * @code
 *     ll_rcu_peripheral_init(LL_RCU_GPIOA);
 *     ll_rcu_peripheral_init_with_source(LL_RCU_UART0, LL_RCU_CLKSEL_PLL0);
 * @endcode
 *
 * Out of scope: SYSCLK source selection, PLL configuration, secure
 * counters — those vary too much per SoC.
 *
 * @defgroup ll_rcu LL RCU
 * @{
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ll_assert.h>
#include <ll_pll.h>
#include <soc.h>

#if !defined(K1921VG015) && !defined(K1921VG1T) && !defined(K1921VG3T) && !defined(K1921VG5T) && !defined(K1921VG7T)
#error "ll_rcu.h: no implementation for the selected SoC"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Two-bit clock-source selector codes.
 *
 * These compatibility names match the UART/SPI-style mux on most supported
 * SoCs. Other generators reuse the same 0-3 encodings for different sources;
 * check the selected SoC's `RCU_<peripheral>CFG_CLKSEL_*` enum before calling
 * @ref ll_rcu_set_source.
 */
typedef enum {
    LL_RCU_CLKSEL_HSI  = 0,
    LL_RCU_CLKSEL_HSE  = 1,
    LL_RCU_CLKSEL_PLL0 = 2,
    LL_RCU_CLKSEL_EXT  = 3,
} ll_rcu_clksel_t;

/**
 * @brief Opaque descriptor for the full RCU footprint of one peripheral.
 *
 * Construct one via the per-SoC `LL_RCU_*` macros below; never fill the
 * fields by hand. `clkcfg` is @c NULL for peripherals that do not have a
 * per-instance clock generator (GPIO, etc.), in which case the @c *_pos
 * fields are unused and the clkcfg helpers are no-ops.
 */
typedef struct {
    volatile uint32_t *cgcfg;  /**< Bus clock-gate register pointer. */
    volatile uint32_t *rstdis; /**< Bus reset-disable register pointer. */
    uint32_t bus_mask;         /**< Single-bit mask within both bus registers. */
    volatile uint32_t *clkcfg; /**< Per-instance clkcfg register, or @c NULL. */
    uint8_t clken_pos;         /**< Bit position of CLKEN within @c clkcfg. */
    uint8_t rstdis_pos;        /**< Bit position of RSTDIS within @c clkcfg. */
    uint8_t clksel_pos;        /**< Bit position of CLKSEL within @c clkcfg. */
    uint8_t divn_pos;          /**< Bit position of DIVN within @c clkcfg. */
} ll_rcu_periph_t;

/**
 * @name Bus-clock-gate operations
 * @{
 */

/**
 * @brief Ungate the bus clock to the peripheral.
 * @param p  Peripheral descriptor.
 */
static inline void ll_rcu_clock_enable(ll_rcu_periph_t p)
{
    *p.cgcfg |= p.bus_mask;
}

/**
 * @brief Gate the bus clock to the peripheral.
 * @param p  Peripheral descriptor.
 */
static inline void ll_rcu_clock_disable(ll_rcu_periph_t p)
{
    *p.cgcfg &= ~p.bus_mask;
}

/**
 * @brief Release the peripheral from reset (sets its @c RSTDIS* bus bit).
 * @param p  Peripheral descriptor.
 */
static inline void ll_rcu_reset_release(ll_rcu_periph_t p)
{
    *p.rstdis |= p.bus_mask;
}

/**
 * @brief Hold the peripheral in reset (clears its @c RSTDIS* bus bit).
 * @param p  Peripheral descriptor.
 */
static inline void ll_rcu_reset_assert(ll_rcu_periph_t p)
{
    *p.rstdis &= ~p.bus_mask;
}

/** @} */

/**
 * @name Per-instance clock-generator operations
 *
 * No-ops for peripherals where @c p.clkcfg is @c NULL (e.g. GPIO).
 * @{
 */
#define _LL_RCU_NO_RSTDIS 0xFFU  // NOLINT
/**
 * @brief Some clkcfg registers doesnt have RSTDIS bit
 * @return RSTDIS mask
 */
static inline uint32_t _ll_rcu_rstdis_msk(ll_rcu_periph_t p)  // NOLINT
{
    return (p.rstdis_pos == _LL_RCU_NO_RSTDIS) ? 0U : (1U << p.rstdis_pos);
}

/**
 * @brief Enable the per-instance clock generator (sets CLKEN and RSTDIS in clkcfg).
 * @param p  Peripheral descriptor.
 */
static inline void ll_rcu_clkcfg_enable(ll_rcu_periph_t p)
{
    if (p.clkcfg) {
        *p.clkcfg |= (1U << p.clken_pos) | _ll_rcu_rstdis_msk(p);
    }
}

/**
 * @brief Enable the per-instance clock generator (sets CLKEN and RSTDIS in clkcfg) and sets source. Clears dividers.
 * @param p       Peripheral descriptor.
 * @param source  Clock source selector.
 */
static inline void ll_rcu_clkcfg_enable_and_source(ll_rcu_periph_t p, ll_rcu_clksel_t source)
{
    if (p.clkcfg) {
        *p.clkcfg = (1U << p.clken_pos) | _ll_rcu_rstdis_msk(p) | (source << p.clksel_pos);
    }
}

/**
 * @brief Disable the per-instance clock generator.
 * @param p  Peripheral descriptor.
 */
static inline void ll_rcu_clkcfg_disable(ll_rcu_periph_t p)
{
    if (p.clkcfg) {
        *p.clkcfg &= ~((1U << p.clken_pos) | _ll_rcu_rstdis_msk(p));
    }
}

/**
 * @brief Program the clock source for the per-instance generator.
 *
 * Writes the 2-bit CLKSEL field at @c p.clksel_pos. No-op when the
 * peripheral has no clkcfg register.
 *
 * @param p    Peripheral descriptor.
 * @param src  Clock source selector.
 */
static inline void ll_rcu_set_source(ll_rcu_periph_t p, ll_rcu_clksel_t src)
{
    if (p.clkcfg) {
        const uint32_t mask = 0x3U << p.clksel_pos;
        *p.clkcfg           = (*p.clkcfg & ~mask) | (((uint32_t)src & 0x3U) << p.clksel_pos);
    }
}

/**
 * @brief Program the post-divider for the per-instance generator.
 *
 * The dividing factor on most SoCs is `2 * (divn + 1)`; consult the
 * specific SoC manual for the exact formula. Pass @c divn=0 with
 * @c enable=false to leave the divider disabled.
 *
 * @param p       Peripheral descriptor.
 * @param enable  Set DIVEN.
 * @param divn    Divider coefficient (low 6 bits used).
 */
static inline void ll_rcu_set_divider(ll_rcu_periph_t p, bool enable, uint8_t divn)
{
    if (!p.clkcfg) {
        return;
    }

    /* DIVEN sits one nibble below DIVN on every variant (positions 20/24 on
     * VG015 and 12/16 on the VG1T family), so we don't carry a separate
     * field for it. */
    const uint8_t diven_pos  = (uint8_t)(p.divn_pos - 4U);
    const uint32_t divn_mask = 0x3FU << p.divn_pos;
    uint32_t v               = *p.clkcfg;
    v &= ~(divn_mask | (1U << diven_pos));
    v |= ((uint32_t)divn & 0x3FU) << p.divn_pos;
    if (enable) {
        v |= 1U << diven_pos;
    }
    *p.clkcfg = v;
}

/** @} */

/**
 * @name Composite bring-up
 * @{
 */

/**
 * @brief Full peripheral bring-up using whatever source is currently programmed.
 *
 * Equivalent to: @ref ll_rcu_clock_enable + @ref ll_rcu_reset_release +
 * @ref ll_rcu_clkcfg_enable (if a clkcfg exists).
 *
 * @param p  Peripheral descriptor.
 */
static inline void ll_rcu_peripheral_init(ll_rcu_periph_t p)
{
    ll_rcu_clock_enable(p);
    ll_rcu_reset_release(p);
    ll_rcu_clkcfg_enable(p);
}

/**
 * @brief Full peripheral bring-up with explicit clock-source selection.
 *
 * Equivalent to: @ref ll_rcu_clock_enable + @ref ll_rcu_reset_release +
 * @ref ll_rcu_set_source + @ref ll_rcu_clkcfg_enable.
 *
 * For peripherals without a per-instance generator (GPIO etc.) the
 * @p src argument is ignored — only the bus-level operations are
 * applied.
 *
 * @param p    Peripheral descriptor.
 * @param src  Clock source selector.
 */
static inline void ll_rcu_peripheral_init_with_source(ll_rcu_periph_t p, ll_rcu_clksel_t src)
{
    ll_rcu_clock_enable(p);
    ll_rcu_reset_release(p);
    if (p.clkcfg) {
        const uint32_t sel_mask = 0x3U << p.clksel_pos;
        const uint32_t en_mask  = (1U << p.clken_pos) | _ll_rcu_rstdis_msk(p);
        uint32_t v              = *p.clkcfg;
        v &= ~sel_mask;
        v |= (((uint32_t)src & 0x3U) << p.clksel_pos) | en_mask;
        *p.clkcfg = v;
    }
}

/**
 * @brief Tear-down: disable clkcfg, gate bus clock, hold in reset.
 * @param p  Peripheral descriptor.
 */
static inline void ll_rcu_peripheral_deinit(ll_rcu_periph_t p)
{
    if (p.clkcfg) {
        *p.clkcfg &= ~((1U << p.clken_pos) | _ll_rcu_rstdis_msk(p));
    }
    *p.rstdis &= ~p.bus_mask;
    *p.cgcfg &= ~p.bus_mask;
}

static inline bool ll_rcu_sys_wait_select(int32_t spins)
{
    const bool forever = (spins < 0);
    while (forever || --spins) {
        if (RCU->CLKSTAT_bit.SRC == RCU->SYSCLKCFG_bit.SRC) {
            return true;
        }
    }
    return false;
}

static inline void ll_rcu_sys_select_src(ll_rcu_clksel_t src, uint32_t spins)
{
    RCU->SYSCLKCFG_bit.SRC = src;
    LL_ASSERT(ll_rcu_sys_wait_select(spins));
}

/** @} */

/* ─────────────────────────────────────────────────────────────────────────
 *  Per-SoC intermediate layer.
 *
 *  Each peripheral macro expands to a @ref ll_rcu_periph_t compound literal
 *  built from the SoC header's own @c RCU_*_Msk and field-position symbols.
 *  Peripherals with no per-instance generator pass @c NULL for @c clkcfg
 *  and zeroes for the field-position bytes — the generator helpers then
 *  fall through as no-ops.
 * ───────────────────────────────────────────────────────────────────────── */

/**
 * @warning Infrastructure descriptors are raw hardware controls. Gating or
 * resetting a default-on or execution-critical block can halt or destabilize
 * the MCU. On K1921VG7T this especially applies to FLASH, SRAM, DMA, GPIOA,
 * RCU, and SIU. Execute from a safe memory domain and account for exception
 * handlers and active bus masters before changing those descriptors.
 */

#define _LL_RCU_NO_CFG NULL, 0U, 0U, 0U, 0U

#define _LL_RCU_BUS(cgcfg_, rstdis_, mask_) ((ll_rcu_periph_t){&(cgcfg_), &(rstdis_), (mask_), _LL_RCU_NO_CFG})

#define _LL_RCU_CFG(cgcfg_, rstdis_, mask_, clkcfg_, clken_, cfg_rstdis_, clksel_, divn_) \
    ((ll_rcu_periph_t){&(cgcfg_), &(rstdis_), (mask_), &(clkcfg_), (clken_), (cfg_rstdis_), (clksel_), (divn_)})

#if defined(K1921VG015)

/* Register-layout invariants: detect header changes at compile time. */
_Static_assert(offsetof(RCU_TypeDef, CGCFGAHB) == 0x00U, "RCU CGCFGAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, CGCFGAPB) == 0x08U, "RCU CGCFGAPB offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAHB) == 0x10U, "RCU RSTDISAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAPB) == 0x18U, "RCU RSTDISAPB offset drift");

#define _LL_RCU_V015_CLKEN_POS  0U
#define _LL_RCU_V015_RSTDIS_POS 8U
#define _LL_RCU_V015_CLKSEL_POS 16U
#define _LL_RCU_V015_DIVN_POS   24U

#define _LL_RCU_V015_UART(i_, mask_)                                                                            \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, (mask_), RCU->UARTCLKCFG[i_].UARTCLKCFG, _LL_RCU_V015_CLKEN_POS, \
                _LL_RCU_V015_RSTDIS_POS, _LL_RCU_V015_CLKSEL_POS, _LL_RCU_V015_DIVN_POS)

#define _LL_RCU_V015_SPI(i_, mask_)                                                                           \
    _LL_RCU_CFG(RCU->CGCFGAHB, RCU->RSTDISAHB, (mask_), RCU->SPICLKCFG[i_].SPICLKCFG, _LL_RCU_V015_CLKEN_POS, \
                _LL_RCU_V015_RSTDIS_POS, _LL_RCU_V015_CLKSEL_POS, _LL_RCU_V015_DIVN_POS)

#define LL_RCU_CAN    _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CANEN_Msk)
#define LL_RCU_USB    _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_USBEN_Msk)
#define LL_RCU_CRYPTO _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CRYPTOEN_Msk)
#define LL_RCU_HASH   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_HASHEN_Msk)
#define LL_RCU_QSPI   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_QSPIEN_Msk)
#define LL_RCU_SPI0   _LL_RCU_V015_SPI(0, RCU_CGCFGAHB_SPI0EN_Msk)
#define LL_RCU_SPI1   _LL_RCU_V015_SPI(1, RCU_CGCFGAHB_SPI1EN_Msk)
#define LL_RCU_GPIOA  _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOAEN_Msk)
#define LL_RCU_GPIOB  _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOBEN_Msk)
#define LL_RCU_GPIOC  _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOCEN_Msk)
#define LL_RCU_CRC0   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CRC0EN_Msk)
#define LL_RCU_CRC1   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CRC1EN_Msk)

#define LL_RCU_TMR32 _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR32EN_Msk)
#define LL_RCU_TMR0  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR0EN_Msk)
#define LL_RCU_TMR1  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR1EN_Msk)
#define LL_RCU_TMR2  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR2EN_Msk)
#define LL_RCU_TRNG  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TRNGEN_Msk)
#define LL_RCU_I2C   _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_I2CEN_Msk)
#define LL_RCU_UART0 _LL_RCU_V015_UART(0, RCU_CGCFGAPB_UART0EN_Msk)
#define LL_RCU_UART1 _LL_RCU_V015_UART(1, RCU_CGCFGAPB_UART1EN_Msk)
#define LL_RCU_UART2 _LL_RCU_V015_UART(2, RCU_CGCFGAPB_UART2EN_Msk)
#define LL_RCU_UART3 _LL_RCU_V015_UART(3, RCU_CGCFGAPB_UART3EN_Msk)
#define LL_RCU_UART4 _LL_RCU_V015_UART(4, RCU_CGCFGAPB_UART4EN_Msk)
#define LL_RCU_WDT                                                                                                \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_WDTEN_Msk, RCU->WDOGCLKCFG, RCU_WDOGCLKCFG_CLKEN_Pos, \
                RCU_WDOGCLKCFG_RSTDIS_Pos, RCU_WDOGCLKCFG_CLKSEL_Pos, RCU_WDOGCLKCFG_DIVN_Pos)
#define LL_RCU_ADCSD                                                                                                  \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_ADCSDEN_Msk, RCU->ADCSDCLKCFG, RCU_ADCSDCLKCFG_CLKEN_Pos, \
                RCU_ADCSDCLKCFG_RSTDIS_Pos, RCU_ADCSDCLKCFG_CLKSEL_Pos, RCU_ADCSDCLKCFG_DIVN_Pos)
#define LL_RCU_ADCSAR                                                                                 \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_ADCSAREN_Msk, RCU->ADCSARCLKCFG,          \
                RCU_ADCSARCLKCFG_CLKEN_Pos, RCU_ADCSARCLKCFG_RSTDIS_Pos, RCU_ADCSARCLKCFG_CLKSEL_Pos, \
                RCU_ADCSARCLKCFG_DIVN_Pos)
#define LL_RCU_CMP _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_CMPEN_Msk)

#elif defined(K1921VG1T)

/* Register-layout invariants for K1921VG1T. */
_Static_assert(offsetof(RCU_TypeDef, CGCFGAHB) == 0x00U, "RCU CGCFGAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, CGCFGAPB0) == 0x04U, "RCU CGCFGAPB0 offset drift");
_Static_assert(offsetof(RCU_TypeDef, CGCFGAPB1) == 0x08U, "RCU CGCFGAPB1 offset drift");
_Static_assert(offsetof(RCU_TypeDef, CGCFGAPB2) == 0x0CU, "RCU CGCFGAPB2 offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAHB) == 0x10U, "RCU RSTDISAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAPB0) == 0x14U, "RCU RSTDISAPB0 offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAPB1) == 0x18U, "RCU RSTDISAPB1 offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAPB2) == 0x1CU, "RCU RSTDISAPB2 offset drift");

#define _LL_RCU_VGT_UART(i_, mask_)                                                                        \
    _LL_RCU_CFG(RCU->CGCFGAPB2, RCU->RSTDISAPB2, (mask_), RCU->UARTCFG[i_].UARTCFG, RCU_UARTCFG_CLKEN_Pos, \
                RCU_UARTCFG_RSTDIS_Pos, RCU_UARTCFG_CLKSEL_Pos, RCU_UARTCFG_DIVN_Pos)
#define _LL_RCU_VGT_SPI(i_, mask_)                                                                      \
    _LL_RCU_CFG(RCU->CGCFGAPB2, RCU->RSTDISAPB2, (mask_), RCU->SPICFG[i_].SPICFG, RCU_SPICFG_CLKEN_Pos, \
                RCU_SPICFG_RSTDIS_Pos, RCU_SPICFG_CLKSEL_Pos, RCU_SPICFG_DIVN_Pos)
#define _LL_RCU_V1T_USB(i_, mask_)                                                                    \
    _LL_RCU_CFG(RCU->CGCFGAHB, RCU->RSTDISAHB, (mask_), RCU->USBCFG[i_].USBCFG, RCU_USBCFG_CLKEN_Pos, \
                _LL_RCU_NO_RSTDIS, RCU_USBCFG_CLKSEL_Pos, RCU_USBCFG_DIVN_Pos)
#define _LL_RCU_V1T_I2S(i_, mask_)                                                                      \
    _LL_RCU_CFG(RCU->CGCFGAPB1, RCU->RSTDISAPB1, (mask_), RCU->I2SCFG[i_].I2SCFG, RCU_I2SCFG_CLKEN_Pos, \
                _LL_RCU_NO_RSTDIS, RCU_I2SCFG_CLKSEL_Pos, RCU_I2SCFG_DIVN_Pos)

/**
 * @name K1921VG1T peripherals
 * @{
 */
#define LL_RCU_GPIOA _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOAEN_Msk)
#define LL_RCU_GPIOB _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOBEN_Msk)
#define LL_RCU_GPIOC _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOCEN_Msk)
#define LL_RCU_GPIOD _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIODEN_Msk)
#define LL_RCU_GPIOE _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOEEN_Msk)
#define LL_RCU_GPIOF _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOFEN_Msk)
#define LL_RCU_GPIOG _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOGEN_Msk)
#define LL_RCU_CANFD                                                                                            \
    _LL_RCU_CFG(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CANFDEN_Msk, RCU->CANFDCFG, RCU_CANFDCFG_CLKEN_Pos, \
                RCU_CANFDCFG_RSTDIS_Pos, RCU_CANFDCFG_CLKSEL_Pos, RCU_CANFDCFG_DIVN_Pos)
#define LL_RCU_CANFD0 LL_RCU_CANFD
#define LL_RCU_CANFD1 LL_RCU_CANFD
#define LL_RCU_CANFD2 LL_RCU_CANFD
#define LL_RCU_CANFD3 LL_RCU_CANFD
#define LL_RCU_CAN    _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CANEN_Msk)
#define LL_RCU_ADC                                                                                        \
    _LL_RCU_CFG(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_ADCEN_Msk, RCU->ADCCFG, RCU_ADCCFG_CLKEN_Pos, \
                RCU_ADCCFG_RSTDIS_Pos, RCU_ADCCFG_CLKSEL_Pos, RCU_ADCCFG_DIVN_Pos)
#define LL_RCU_QSPI0  _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_QSPI0EN_Msk)
#define LL_RCU_QSPI1  _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_QSPI1EN_Msk)
#define LL_RCU_CRC    _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CRCEN_Msk)
#define LL_RCU_CRYPTO _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CRYPTOEN_Msk)
#define LL_RCU_HASH   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_HASHEN_Msk)
#define LL_RCU_USBD0  _LL_RCU_V1T_USB(0, RCU_CGCFGAHB_USB0DEN_Msk)
#define LL_RCU_USBH0  _LL_RCU_V1T_USB(0, RCU_CGCFGAHB_USB0HEN_Msk)
#define LL_RCU_USBD1  _LL_RCU_V1T_USB(1, RCU_CGCFGAHB_USB1DEN_Msk)
#define LL_RCU_USBH1  _LL_RCU_V1T_USB(1, RCU_CGCFGAHB_USB1HEN_Msk)

#define LL_RCU_DMA _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_DMAEN_Msk)
#define LL_RCU_RTC _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_RTCEN_Msk)
#define LL_RCU_WDT                                                                                           \
    _LL_RCU_CFG(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_WDTEN_Msk, RCU->WDTCFG, RCU_WDTCFG_CLKEN_Pos, \
                RCU_WDTCFG_RSTDIS_Pos, RCU_WDTCFG_CLKSEL_Pos, RCU_WDTCFG_DIVN_Pos)
#define LL_RCU_TRNG _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TRNGEN_Msk)
#define LL_RCU_EMC  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_EMCEN_Msk)
#define LL_RCU_SDRAM                                                                                               \
    _LL_RCU_CFG(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_SDRAMEN_Msk, RCU->SDRAMCFG, RCU_SDRAMCFG_CLKEN_Pos, \
                RCU_SDRAMCFG_RSTDIS_Pos, RCU_SDRAMCFG_CLKSEL_Pos, RCU_SDRAMCFG_DIVN_Pos)
#define LL_RCU_ETH                                                                                           \
    _LL_RCU_CFG(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_ETHEN_Msk, RCU->ETHCFG, RCU_ETHCFG_CLKEN_Pos, \
                RCU_ETHCFG_RSTDIS_Pos, RCU_ETHCFG_CLKSEL_Pos, RCU_ETHCFG_DIVN_Pos)
#define LL_RCU_PWM0  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM0EN_Msk)
#define LL_RCU_PWM1  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM1EN_Msk)
#define LL_RCU_PWM2  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM2EN_Msk)
#define LL_RCU_PWM3  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM3EN_Msk)
#define LL_RCU_PWM4  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM4EN_Msk)
#define LL_RCU_PWM5  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM5EN_Msk)
#define LL_RCU_PWM6  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM6EN_Msk)
#define LL_RCU_PWM7  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM7EN_Msk)
#define LL_RCU_PWM8  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM8EN_Msk)
#define LL_RCU_PWM9  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM9EN_Msk)
#define LL_RCU_PWM10 _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM10EN_Msk)
#define LL_RCU_PWM11 _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM11EN_Msk)
#define LL_RCU_PWM12 _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM12EN_Msk)
#define LL_RCU_PWM13 _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM13EN_Msk)
#define LL_RCU_PWM14 _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM14EN_Msk)
#define LL_RCU_PWM15 _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_PWM15EN_Msk)

#define LL_RCU_ACMP0 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_ACMP0EN_Msk)
#define LL_RCU_ACMP1 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_ACMP1EN_Msk)
#define LL_RCU_ACMP2 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_ACMP2EN_Msk)
#define LL_RCU_ACMP3 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_ACMP3EN_Msk)
#define LL_RCU_DAC0  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_DAC0EN_Msk)
#define LL_RCU_DAC1  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_DAC1EN_Msk)
#define LL_RCU_I2S0  _LL_RCU_V1T_I2S(0, RCU_CGCFGAPB1_I2S0EN_Msk)
#define LL_RCU_I2S1  _LL_RCU_V1T_I2S(1, RCU_CGCFGAPB1_I2S1EN_Msk)
#define LL_RCU_TMR0  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR0EN_Msk)
#define LL_RCU_TMR1  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR1EN_Msk)
#define LL_RCU_TMR2  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR2EN_Msk)
#define LL_RCU_TMR3  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR3EN_Msk)
#define LL_RCU_TMR4  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR4EN_Msk)
#define LL_RCU_TMR5  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR5EN_Msk)
#define LL_RCU_TMR6  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR6EN_Msk)
#define LL_RCU_TMR7  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR7EN_Msk)
#define LL_RCU_TMR8  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR8EN_Msk)
#define LL_RCU_TMR9  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR9EN_Msk)
#define LL_RCU_TMR10 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR10EN_Msk)
#define LL_RCU_TMR11 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR11EN_Msk)
#define LL_RCU_TMR12 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR12EN_Msk)
#define LL_RCU_TMR13 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR13EN_Msk)
#define LL_RCU_TMR14 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR14EN_Msk)
#define LL_RCU_TMR15 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_TMR15EN_Msk)

#define LL_RCU_LIN0  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_LIN0EN_Msk)
#define LL_RCU_LIN1  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_LIN1EN_Msk)
#define LL_RCU_LIN2  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_LIN2EN_Msk)
#define LL_RCU_LIN3  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_LIN3EN_Msk)
#define LL_RCU_LIN4  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_LIN4EN_Msk)
#define LL_RCU_LIN5  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_LIN5EN_Msk)
#define LL_RCU_LIN6  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_LIN6EN_Msk)
#define LL_RCU_LIN7  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_LIN7EN_Msk)
#define LL_RCU_SPI0  _LL_RCU_VGT_SPI(0, RCU_CGCFGAPB2_SPI0EN_Msk)
#define LL_RCU_SPI1  _LL_RCU_VGT_SPI(1, RCU_CGCFGAPB2_SPI1EN_Msk)
#define LL_RCU_SPI2  _LL_RCU_VGT_SPI(2, RCU_CGCFGAPB2_SPI2EN_Msk)
#define LL_RCU_SPI3  _LL_RCU_VGT_SPI(3, RCU_CGCFGAPB2_SPI3EN_Msk)
#define LL_RCU_SPI4  _LL_RCU_VGT_SPI(4, RCU_CGCFGAPB2_SPI4EN_Msk)
#define LL_RCU_SPI5  _LL_RCU_VGT_SPI(5, RCU_CGCFGAPB2_SPI5EN_Msk)
#define LL_RCU_SPI6  _LL_RCU_VGT_SPI(6, RCU_CGCFGAPB2_SPI6EN_Msk)
#define LL_RCU_SPI7  _LL_RCU_VGT_SPI(7, RCU_CGCFGAPB2_SPI7EN_Msk)
#define LL_RCU_UART0 _LL_RCU_VGT_UART(0, RCU_CGCFGAPB2_UART0EN_Msk)
#define LL_RCU_UART1 _LL_RCU_VGT_UART(1, RCU_CGCFGAPB2_UART1EN_Msk)
#define LL_RCU_UART2 _LL_RCU_VGT_UART(2, RCU_CGCFGAPB2_UART2EN_Msk)
#define LL_RCU_UART3 _LL_RCU_VGT_UART(3, RCU_CGCFGAPB2_UART3EN_Msk)
#define LL_RCU_UART4 _LL_RCU_VGT_UART(4, RCU_CGCFGAPB2_UART4EN_Msk)
#define LL_RCU_UART5 _LL_RCU_VGT_UART(5, RCU_CGCFGAPB2_UART5EN_Msk)
#define LL_RCU_UART6 _LL_RCU_VGT_UART(6, RCU_CGCFGAPB2_UART6EN_Msk)
#define LL_RCU_UART7 _LL_RCU_VGT_UART(7, RCU_CGCFGAPB2_UART7EN_Msk)
#define LL_RCU_I2C0  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_I2C0EN_Msk)
#define LL_RCU_I2C1  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_I2C1EN_Msk)
#define LL_RCU_I2C2  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_I2C2EN_Msk)
#define LL_RCU_I2C3  _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_I2C3EN_Msk)
#define LL_RCU_MSC   _LL_RCU_BUS(RCU->CGCFGAPB2, RCU->RSTDISAPB2, RCU_CGCFGAPB2_MSCEN_Msk)

/** @} */

#elif defined(K1921VG3T)

/* Register-layout invariants for K1921VG3T. */
_Static_assert(offsetof(RCU_TypeDef, CGCFGAHB) == 0x00U, "RCU CGCFGAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, CGCFGAPB0) == 0x04U, "RCU CGCFGAPB0 offset drift");
_Static_assert(offsetof(RCU_TypeDef, CGCFGAPB1) == 0x08U, "RCU CGCFGAPB1 offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAHB) == 0x10U, "RCU RSTDISAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAPB0) == 0x14U, "RCU RSTDISAPB0 offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAPB1) == 0x18U, "RCU RSTDISAPB1 offset drift");

#define _LL_RCU_VGT_UART(i_, mask_)                                                                        \
    _LL_RCU_CFG(RCU->CGCFGAPB1, RCU->RSTDISAPB1, (mask_), RCU->UARTCFG[i_].UARTCFG, RCU_UARTCFG_CLKEN_Pos, \
                RCU_UARTCFG_RSTDIS_Pos, RCU_UARTCFG_CLKSEL_Pos, RCU_UARTCFG_DIVN_Pos)
#define _LL_RCU_VGT_SPI(i_, mask_)                                                                      \
    _LL_RCU_CFG(RCU->CGCFGAPB1, RCU->RSTDISAPB1, (mask_), RCU->SPICFG[i_].SPICFG, RCU_SPICFG_CLKEN_Pos, \
                RCU_SPICFG_RSTDIS_Pos, RCU_SPICFG_CLKSEL_Pos, RCU_SPICFG_DIVN_Pos)
#define _LL_RCU_V3T_USB(mask_)                                                                                    \
    _LL_RCU_CFG(RCU->CGCFGAHB, RCU->RSTDISAHB, (mask_), RCU->USBCFG, RCU_USBCFG_CLKEN_Pos, RCU_USBCFG_RSTDIS_Pos, \
                RCU_USBCFG_CLKSEL_Pos, RCU_USBCFG_DIVN_Pos)
#define _LL_RCU_V3T_CANFD(mask_)                                                               \
    _LL_RCU_CFG(RCU->CGCFGAHB, RCU->RSTDISAHB, (mask_), RCU->CANFDCFG, RCU_CANFDCFG_CLKEN_Pos, \
                RCU_CANFDCFG_RSTDIS_Pos, RCU_CANFDCFG_CLKSEL_Pos, RCU_CANFDCFG_DIVN_Pos)

/**
 * @name K1921VG3T peripherals
 * @{
 */
#define LL_RCU_GPIOA _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOAEN_Msk)
#define LL_RCU_GPIOB _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOBEN_Msk)
#define LL_RCU_GPIOC _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOCEN_Msk)
#define LL_RCU_GPIOD _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIODEN_Msk)
#define LL_RCU_GPIOE _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOEEN_Msk)
#define LL_RCU_GPIOF _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOFEN_Msk)
#define LL_RCU_GPIOG _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOGEN_Msk)
#define LL_RCU_GPIOH _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOHEN_Msk)
#define LL_RCU_CAN   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CANEN_Msk)
#define LL_RCU_ADC                                                                                        \
    _LL_RCU_CFG(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_ADCEN_Msk, RCU->ADCCFG, RCU_ADCCFG_CLKEN_Pos, \
                RCU_ADCCFG_RSTDIS_Pos, RCU_ADCCFG_CLKSEL_Pos, RCU_ADCCFG_DIVN_Pos)
#define LL_RCU_QSPI   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_QSPIEN_Msk)
#define LL_RCU_CRC    _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CRCEN_Msk)
#define LL_RCU_HASH   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_HASHEN_Msk)
#define LL_RCU_CRYPTO _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CRYPTOEN_Msk)
#define LL_RCU_USBD0  _LL_RCU_V3T_USB(RCU_CGCFGAHB_USBDEN_Msk)
#define LL_RCU_USBH0  _LL_RCU_V3T_USB(RCU_CGCFGAHB_USBHEN_Msk)
#define LL_RCU_CANFD0 _LL_RCU_V3T_CANFD(RCU_CGCFGAHB_CANFD0EN_Msk)
#define LL_RCU_CANFD1 _LL_RCU_V3T_CANFD(RCU_CGCFGAHB_CANFD1EN_Msk)

#define LL_RCU_DMA _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_DMAEN_Msk)
#define LL_RCU_FLASH                                                                                               \
    _LL_RCU_CFG(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_FLASHEN_Msk, RCU->FLASHCFG, RCU_FLASHCFG_CLKEN_Pos, \
                _LL_RCU_NO_RSTDIS, RCU_FLASHCFG_CLKSEL_Pos, RCU_FLASHCFG_DIVN_Pos)
#define LL_RCU_SRAM _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_RAMEN_Msk)
#define LL_RCU_RAM  LL_RCU_SRAM
#define LL_RCU_RTC  _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_RTCEN_Msk)
#define LL_RCU_WDT                                                                                           \
    _LL_RCU_CFG(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_WDTEN_Msk, RCU->WDTCFG, RCU_WDTCFG_CLKEN_Pos, \
                RCU_WDTCFG_RSTDIS_Pos, RCU_WDTCFG_CLKSEL_Pos, RCU_WDTCFG_DIVN_Pos)
#define LL_RCU_TRNG     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TRNGEN_Msk)
#define LL_RCU_EMC      _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_EMCEN_Msk)
#define LL_RCU_CAP0     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_CAP0EN_Msk)
#define LL_RCU_CAP1     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_CAP1EN_Msk)
#define LL_RCU_CAP2     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_CAP2EN_Msk)
#define LL_RCU_CAP3     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_CAP3EN_Msk)
#define LL_RCU_CAP4     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_CAP4EN_Msk)
#define LL_RCU_CAP5     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_CAP5EN_Msk)
#define LL_RCU_DAC0     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_DAC0EN_Msk)
#define LL_RCU_DAC1     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_DAC1EN_Msk)
#define LL_RCU_TMR0     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR0EN_Msk)
#define LL_RCU_TMR1     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR1EN_Msk)
#define LL_RCU_TMR2     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR2EN_Msk)
#define LL_RCU_TMR3     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR3EN_Msk)
#define LL_RCU_TMR4     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR4EN_Msk)
#define LL_RCU_TMR5     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR5EN_Msk)
#define LL_RCU_TMR6     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR6EN_Msk)
#define LL_RCU_TMR7     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR7EN_Msk)
#define LL_RCU_TMR8     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR8EN_Msk)
#define LL_RCU_TMR9     _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR9EN_Msk)
#define LL_RCU_TMR10    _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR10EN_Msk)
#define LL_RCU_TMR11    _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR11EN_Msk)
#define LL_RCU_TMR12    _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR12EN_Msk)
#define LL_RCU_TMR13    _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR13EN_Msk)
#define LL_RCU_TMR14    _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR14EN_Msk)
#define LL_RCU_TMR15    _LL_RCU_BUS(RCU->CGCFGAPB0, RCU->RSTDISAPB0, RCU_CGCFGAPB0_TMR15EN_Msk)
#define LL_RCU_TMR_32_0 LL_RCU_TMR0

#define LL_RCU_ACMP0 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_ACMP0EN_Msk)
#define LL_RCU_ACMP1 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_ACMP1EN_Msk)
#define LL_RCU_ACMP2 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_ACMP2EN_Msk)
#define LL_RCU_SDRAM                                                                                               \
    _LL_RCU_CFG(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_SDRAMEN_Msk, RCU->SDRAMCFG, RCU_SDRAMCFG_CLKEN_Pos, \
                RCU_SDRAMCFG_RSTDIS_Pos, RCU_SDRAMCFG_CLKSEL_Pos, RCU_SDRAMCFG_DIVN_Pos)
#define LL_RCU_LIN0  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_LIN0EN_Msk)
#define LL_RCU_LIN1  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_LIN1EN_Msk)
#define LL_RCU_LIN2  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_LIN2EN_Msk)
#define LL_RCU_LIN3  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_LIN3EN_Msk)
#define LL_RCU_SPI0  _LL_RCU_VGT_SPI(0, RCU_CGCFGAPB1_SPI0EN_Msk)
#define LL_RCU_SPI1  _LL_RCU_VGT_SPI(1, RCU_CGCFGAPB1_SPI1EN_Msk)
#define LL_RCU_SPI2  _LL_RCU_VGT_SPI(2, RCU_CGCFGAPB1_SPI2EN_Msk)
#define LL_RCU_SPI3  _LL_RCU_VGT_SPI(3, RCU_CGCFGAPB1_SPI3EN_Msk)
#define LL_RCU_I2C0  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_I2C0EN_Msk)
#define LL_RCU_I2C1  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_I2C1EN_Msk)
#define LL_RCU_QEP0  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_QEP0EN_Msk)
#define LL_RCU_QEP1  _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_QEP1EN_Msk)
#define LL_RCU_UART0 _LL_RCU_VGT_UART(0, RCU_CGCFGAPB1_UART0EN_Msk)
#define LL_RCU_UART1 _LL_RCU_VGT_UART(1, RCU_CGCFGAPB1_UART1EN_Msk)
#define LL_RCU_UART2 _LL_RCU_VGT_UART(2, RCU_CGCFGAPB1_UART2EN_Msk)
#define LL_RCU_UART3 _LL_RCU_VGT_UART(3, RCU_CGCFGAPB1_UART3EN_Msk)
#define LL_RCU_UART4 _LL_RCU_VGT_UART(4, RCU_CGCFGAPB1_UART4EN_Msk)
#define LL_RCU_UART5 _LL_RCU_VGT_UART(5, RCU_CGCFGAPB1_UART5EN_Msk)
#define LL_RCU_ETH                                                                                           \
    _LL_RCU_CFG(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_ETHEN_Msk, RCU->ETHCFG, RCU_ETHCFG_CLKEN_Pos, \
                RCU_ETHCFG_RSTDIS_Pos, RCU_ETHCFG_CLKSEL_Pos, RCU_ETHCFG_DIVN_Pos)
#define LL_RCU_PWM0 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_PWM0EN_Msk)
#define LL_RCU_PWM1 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_PWM1EN_Msk)
#define LL_RCU_PWM2 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_PWM2EN_Msk)
#define LL_RCU_PWM3 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_PWM3EN_Msk)
#define LL_RCU_PWM4 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_PWM4EN_Msk)
#define LL_RCU_PWM5 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_PWM5EN_Msk)
#define LL_RCU_PWM6 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_PWM6EN_Msk)
#define LL_RCU_PWM7 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_PWM7EN_Msk)
#define LL_RCU_PWM8 _LL_RCU_BUS(RCU->CGCFGAPB1, RCU->RSTDISAPB1, RCU_CGCFGAPB1_PWM8EN_Msk)

/** @} */

#elif defined(K1921VG5T)

/* Register-layout invariants for K1921VG5T. */
_Static_assert(offsetof(RCU_TypeDef, CGCFGAHB) == 0x00U, "RCU CGCFGAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, CGCFGAPB) == 0x08U, "RCU CGCFGAPB offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAHB) == 0x10U, "RCU RSTDISAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAPB) == 0x18U, "RCU RSTDISAPB offset drift");

#define _LL_RCU_VGT_UART(i_, mask_)                                                                      \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, (mask_), RCU->UARTCFG[i_].UARTCFG, RCU_UARTCFG_CLKEN_Pos, \
                RCU_UARTCFG_RSTDIS_Pos, RCU_UARTCFG_CLKSEL_Pos, RCU_UARTCFG_DIVN_Pos)
#define _LL_RCU_VGT_SPI(i_, mask_)                                                                    \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, (mask_), RCU->SPICFG[i_].SPICFG, RCU_SPICFG_CLKEN_Pos, \
                RCU_SPICFG_RSTDIS_Pos, RCU_SPICFG_CLKSEL_Pos, RCU_SPICFG_DIVN_Pos)

/**
 * @name K1921VG5T peripherals
 * @{
 */
#define LL_RCU_GPIOA _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOAEN_Msk)
#define LL_RCU_GPIOB _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOBEN_Msk)
#define LL_RCU_CAN   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CANEN_Msk)
#define LL_RCU_ADC                                                                                        \
    _LL_RCU_CFG(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_ADCEN_Msk, RCU->ADCCFG, RCU_ADCCFG_CLKEN_Pos, \
                RCU_ADCCFG_RSTDIS_Pos, RCU_ADCCFG_CLKSEL_Pos, RCU_ADCCFG_DIVN_Pos)

#define LL_RCU_DMA _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_DMAEN_Msk)
#define LL_RCU_RTC _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_RTCEN_Msk)
#define LL_RCU_WDT                                                                                        \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_WDTEN_Msk, RCU->WDTCFG, RCU_WDTCFG_CLKEN_Pos, \
                RCU_WDTCFG_RSTDIS_Pos, RCU_WDTCFG_CLKSEL_Pos, RCU_WDTCFG_DIVN_Pos)
#define LL_RCU_CAP0  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_CAP0EN_Msk)
#define LL_RCU_CAP1  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_CAP1EN_Msk)
#define LL_RCU_CAP2  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_CAP2EN_Msk)
#define LL_RCU_TMR0  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR0EN_Msk)
#define LL_RCU_TMR1  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR1EN_Msk)
#define LL_RCU_TMR2  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR2EN_Msk)
#define LL_RCU_TMR3  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR3EN_Msk)
#define LL_RCU_SPI0  _LL_RCU_VGT_SPI(0, RCU_CGCFGAPB_SPI0EN_Msk)
#define LL_RCU_SPI1  _LL_RCU_VGT_SPI(1, RCU_CGCFGAPB_SPI1EN_Msk)
#define LL_RCU_UART0 _LL_RCU_VGT_UART(0, RCU_CGCFGAPB_UART0EN_Msk)
#define LL_RCU_UART1 _LL_RCU_VGT_UART(1, RCU_CGCFGAPB_UART1EN_Msk)
#define LL_RCU_PWM0  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_PWM0EN_Msk)
#define LL_RCU_PWM1  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_PWM1EN_Msk)
#define LL_RCU_PWM2  _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_PWM2EN_Msk)
#define LL_RCU_I2C   _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_I2CEN_Msk)
#define LL_RCU_QEP   _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_QEPEN_Msk)
/** @} */

#elif defined(K1921VG7T)

_Static_assert(offsetof(RCU_TypeDef, CGCFGAXI) == 0x00U, "RCU CGCFGAXI offset drift");
_Static_assert(offsetof(RCU_TypeDef, CGCFGAHB) == 0x04U, "RCU CGCFGAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, CGCFGAPB) == 0x08U, "RCU CGCFGAPB offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAXI) == 0x10U, "RCU RSTDISAXI offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAHB) == 0x14U, "RCU RSTDISAHB offset drift");
_Static_assert(offsetof(RCU_TypeDef, RSTDISAPB) == 0x18U, "RCU RSTDISAPB offset drift");

#define _LL_RCU_VGT_UART(i_, mask_)                                                                      \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, (mask_), RCU->UARTCFG[i_].UARTCFG, RCU_UARTCFG_CLKEN_Pos, \
                RCU_UARTCFG_RSTDIS_Pos, RCU_UARTCFG_CLKSEL_Pos, RCU_UARTCFG_DIVN_Pos)
#define _LL_RCU_VGT_SPI(i_, mask_)                                                                    \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, (mask_), RCU->SPICFG[i_].SPICFG, RCU_SPICFG_CLKEN_Pos, \
                RCU_SPICFG_RSTDIS_Pos, RCU_SPICFG_CLKSEL_Pos, RCU_SPICFG_DIVN_Pos)

/**
 * @name K1921VG7T peripherals
 * @{
 */
#define LL_RCU_DMA  _LL_RCU_BUS(RCU->CGCFGAXI, RCU->RSTDISAXI, RCU_CGCFGAXI_DMAEN_Msk)
#define LL_RCU_SRAM _LL_RCU_BUS(RCU->CGCFGAXI, RCU->RSTDISAXI, RCU_CGCFGAXI_SRAMEN_Msk)
#define LL_RCU_FLASH                                                                                            \
    _LL_RCU_CFG(RCU->CGCFGAXI, RCU->RSTDISAXI, RCU_CGCFGAXI_FLASHEN_Msk, RCU->FLASHCFG, RCU_FLASHCFG_CLKEN_Pos, \
                RCU_FLASHCFG_RSTDIS_Pos, RCU_FLASHCFG_CLKSEL_Pos, RCU_FLASHCFG_DIVN_Pos)

#define LL_RCU_GPIOA _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOAEN_Msk)
#define LL_RCU_GPIOB _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_GPIOBEN_Msk)
#define LL_RCU_CAN   _LL_RCU_BUS(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_CANEN_Msk)
#define LL_RCU_ADC                                                                                        \
    _LL_RCU_CFG(RCU->CGCFGAHB, RCU->RSTDISAHB, RCU_CGCFGAHB_ADCEN_Msk, RCU->ADCCFG, RCU_ADCCFG_CLKEN_Pos, \
                RCU_ADCCFG_RSTDIS_Pos, RCU_ADCCFG_CLKSEL_Pos, RCU_ADCCFG_DIVN_Pos)

#define LL_RCU_SIU _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_SIUEN_Msk)
#define LL_RCU_RCU _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_RCUEN_Msk)
#define LL_RCU_RTC _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_RTCEN_Msk)
#define LL_RCU_WDT                                                                                        \
    _LL_RCU_CFG(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_WDTEN_Msk, RCU->WDTCFG, RCU_WDTCFG_CLKEN_Pos, \
                RCU_WDTCFG_RSTDIS_Pos, RCU_WDTCFG_CLKSEL_Pos, RCU_WDTCFG_DIVN_Pos)
#define LL_RCU_I2C0    _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_I2C0EN_Msk)
#define LL_RCU_I2C1    _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_I2C1EN_Msk)
#define LL_RCU_TMR32_0 _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR0EN_Msk)
#define LL_RCU_TMR32_1 _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR1EN_Msk)
#define LL_RCU_TMR16_0 _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR2EN_Msk)
#define LL_RCU_TMR16_1 _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR3EN_Msk)
#define LL_RCU_TMR16_2 _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_TMR4EN_Msk)
#define LL_RCU_SPI0    _LL_RCU_VGT_SPI(0, RCU_CGCFGAPB_SPI0EN_Msk)
#define LL_RCU_SPI1    _LL_RCU_VGT_SPI(1, RCU_CGCFGAPB_SPI1EN_Msk)
#define LL_RCU_SPI2    _LL_RCU_VGT_SPI(2, RCU_CGCFGAPB_SPI2EN_Msk)
#define LL_RCU_UART0   _LL_RCU_VGT_UART(0, RCU_CGCFGAPB_UART0EN_Msk)
#define LL_RCU_UART1   _LL_RCU_VGT_UART(1, RCU_CGCFGAPB_UART1EN_Msk)
#define LL_RCU_DAC     _LL_RCU_BUS(RCU->CGCFGAPB, RCU->RSTDISAPB, RCU_CGCFGAPB_DACEN_Msk)
/** @} */

#endif

#ifdef __cplusplus
}
#endif

/** @} */ /* end of ll_rcu group */
