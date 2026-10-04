#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ll_assert.h>
#include <ll_pll.h>
#include <ll_rcu.h>
#include <prelude_macros.h>
#include <soc.h>

#if !defined K1921VG3T && !defined K1921VG1T
#error "ll_eth_vgxt.h: no implementation for the selected SoC"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    ETH_TypeDef *eth;
    ll_rcu_periph_t rcu;
    uint32_t isr_vector;
} ll_eth_t;

#define LL_ETH0 ((ll_eth_t){ETH, LL_RCU_ETH, IsrVect_IRQ_ETH})

typedef enum __attribute__((packed)) {
    LL_ETH_SPEED_10M   = 0,
    LL_ETH_SPEED_100M  = 1,
    LL_ETH_SPEED_1000M = 2,
} ll_eth_speed_t;

typedef enum __attribute__((packed)) {
    LL_ETH_DUPLEX_HALF = 0,
    LL_ETH_DUPLEX_FULL = 1,
} ll_eth_duplex_t;

typedef struct {
    ll_eth_speed_t speed;
    ll_eth_duplex_t duplex;
    bool burst_mode;  /// CTRL.BM, имеет смысл только для 1000M half-duplex
} ll_eth_link_t;

typedef enum __attribute__((packed)) {
    LL_ETH_IRQ_NONE = 0,
    LL_ETH_IRQ_TX   = 1 << 0,  /// CTRL.TXINT
    LL_ETH_IRQ_RX   = 1 << 1,  /// CTRL.RXINT
    LL_ETH_IRQ_PHY  = 1 << 2,  /// CTRL.PI
    LL_ETH_IRQ_ALL  = LL_ETH_IRQ_TX | LL_ETH_IRQ_RX | LL_ETH_IRQ_PHY,
} ll_eth_irq_t;

typedef enum __attribute__((packed)) {
    LL_ETH_STATUS_RX_ERR     = ETH_STATUS_RXERR_Msk,
    LL_ETH_STATUS_TX_ERR     = ETH_STATUS_TXERR_Msk,
    LL_ETH_STATUS_RX_OK      = ETH_STATUS_RXSUC_Msk,
    LL_ETH_STATUS_TX_OK      = ETH_STATUS_TXSUC_Msk,
    LL_ETH_STATUS_RX_DMA_ERR = ETH_STATUS_RXAHBERR_Msk,
    LL_ETH_STATUS_TX_DMA_ERR = ETH_STATUS_TXAHBERR_Msk,
    LL_ETH_STATUS_TOOSMALL   = ETH_STATUS_TOOSMALL_Msk,
    LL_ETH_STATUS_INV_ADR    = ETH_STATUS_IA_Msk,
    LL_ETH_STATUS_PHYSTAT    = ETH_STATUS_PHYSTAT_Msk,
} ll_eth_status_flag_t;

#define LL_ETH_STATUS_ALL                                                                                      \
    LL_ETH_STATUS_RX_ERR | LL_ETH_STATUS_TX_ERR | LL_ETH_STATUS_RX_OK | LL_ETH_STATUS_TX_OK |                  \
        LL_ETH_STATUS_RX_DMA_ERR | LL_ETH_STATUS_TX_DMA_ERR | LL_ETH_STATUS_TOOSMALL | LL_ETH_STATUS_INV_ADR | \
        LL_ETH_STATUS_PHYSTAT

#define LL_ETH_MAX_PACKET_LEN 1518

typedef struct {
    bool promiscuous;
    bool multicast_enable;
    bool use_builtin_phy;  /// NOTE: встроенный phy имеет проблемы (см Errata)
    ll_eth_irq_t irq;
    /// Клоки PHY/RGMII конвертера (ETHCFG.CLKSEL/DIVN).
    /// Актуально в основном для генерации GTX_CLK в режиме 1000M.
    /// В режиме 10/100M с внешним PHY RXCLK/TXCLK приходят от самой микросхемы PHY и эта настройка не требуется - в
    /// этом случае можно передать pll с number, который не будет использоваться (clk_divider = 0 отключит делитель).
    ll_pll_t pll;
    uint8_t clk_divider;  /// 0 - делитель выключен
} ll_eth_init_t;

static inline void ll_eth_reset(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->CTRL_bit.RST = 1U;
}

static inline bool ll_eth_reset_done(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->CTRL_bit.RST == 0U;
}

static inline bool ll_eth_wait_reset(ll_eth_t eth, int32_t spins)
{
    const bool forever = (spins < 0);
    while (forever || --spins) {
        if (ll_eth_reset_done(eth)) {
            return true;
        }
    }
    return false;
}

static inline void ll_eth_apply_link(ll_eth_t eth, ll_eth_link_t link)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    ETH_TypeDef *e = eth.eth;
    LL_ASSERT(link.speed <= LL_ETH_SPEED_1000M);

    const uint32_t speed_mask = ETH_CTRL_SPEED_Msk | ETH_CTRL_GB_Msk;

    uint32_t ctrl = e->CTRL;
    ctrl &= ~speed_mask;
    ctrl |= ((uint32_t)link.speed << ETH_CTRL_SPEED_Pos) & speed_mask;

    ctrl &= ~ETH_CTRL_FD_Msk;
    ctrl |= link.duplex ? ETH_CTRL_FD_Msk : 0U;

    const bool bm_valid = ((link.speed == LL_ETH_SPEED_1000M) && (link.duplex == LL_ETH_DUPLEX_HALF)) != 0;
    ctrl &= ~ETH_CTRL_BM_Msk;
    ctrl |= (bm_valid && link.burst_mode) ? ETH_CTRL_BM_Msk : 0U;

    e->CTRL = ctrl;
}

static inline void ll_eth_set_promiscuous(ll_eth_t eth, bool enable)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->CTRL_bit.PR = (int)enable ? 1U : 0U;
}

static inline void ll_eth_set_multicast_enable(ll_eth_t eth, bool enable)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->CTRL_bit.ME = (int)enable ? 1U : 0U;
}

static inline bool ll_eth_multicast_available(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->CTRL_bit.MC != 0U;
}

static inline bool ll_eth_mdio_irq_available(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->CTRL_bit.MDIOEN != 0U;
}

static inline bool ll_eth_gigabit_available(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->CTRL_bit.GA != 0U;
}

static inline void ll_eth_irq_mask_set(ll_eth_t eth, ll_eth_irq_t irq)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    ETH_TypeDef *e    = eth.eth;
    e->CTRL_bit.TXINT = (irq & LL_ETH_IRQ_TX) ? 1U : 0U;
    e->CTRL_bit.RXINT = (irq & LL_ETH_IRQ_RX) ? 1U : 0U;
    e->CTRL_bit.PI    = (irq & LL_ETH_IRQ_PHY) ? 1U : 0U;
}

static inline void ll_eth_tx_kick(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->CTRL_bit.TXEN = 1U;
}

static inline void ll_eth_tx_stop(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->CTRL_bit.TXEN = 0U;
}

static inline bool ll_eth_tx_active(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->CTRL_bit.TXEN != 0U;
}

static inline void ll_eth_rx_kick(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->CTRL_bit.RXEN = 1U;
}

static inline void ll_eth_rx_stop(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->CTRL_bit.RXEN = 0U;
}

static inline bool ll_eth_rx_active(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->CTRL_bit.RXEN != 0U;
}

static inline uint32_t ll_eth_status(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->STATUS;
}

static inline bool ll_eth_status_is_set(ll_eth_t eth, ll_eth_status_flag_t flags)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return (eth.eth->STATUS & (uint32_t)flags) != 0U;
}

static inline void ll_eth_status_clear(ll_eth_t eth, ll_eth_status_flag_t flags)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->STATUS = (uint32_t)flags;
}

static inline void ll_eth_set_mac(ll_eth_t eth, const uint8_t mac[6])
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    LL_ASSERT(mac != NULL);
    eth.eth->MACMSB = ((uint32_t)mac[0] << 8U) | (uint32_t)mac[1];
    eth.eth->MACLSB =
        ((uint32_t)mac[2] << 24U) | ((uint32_t)mac[3] << 16U) | ((uint32_t)mac[4] << 8U) | (uint32_t)mac[5];
}

static inline void ll_eth_get_mac(ll_eth_t eth, uint8_t mac[6])
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    LL_ASSERT(mac != NULL);
    const uint32_t msb = eth.eth->MACMSB;
    const uint32_t lsb = eth.eth->MACLSB;

    mac[0] = (uint8_t)(msb >> 8U);
    mac[1] = (uint8_t)(msb);
    mac[2] = (uint8_t)(lsb >> 24U);
    mac[3] = (uint8_t)(lsb >> 16U);
    mac[4] = (uint8_t)(lsb >> 8U);
    mac[5] = (uint8_t)(lsb);
}

static inline void ll_eth_set_tx_base(ll_eth_t eth, void *base)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    LL_ASSERT(SDK_IS_ALIGNED(base, 1024));
    eth.eth->TXBASE = (uint32_t)base & ETH_TXBASE_BADDR_Msk;
}

static inline void *ll_eth_get_tx_base(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return (void *)(eth.eth->TXBASE & ETH_TXBASE_BADDR_Msk);
}

static inline uint32_t ll_eth_get_tx_dpnt(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return (eth.eth->TXBASE & ETH_TXBASE_DPNT_Msk) >> ETH_RXBASE_DPNT_Pos;
}

static inline void ll_eth_set_rx_base(ll_eth_t eth, void *base)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    LL_ASSERT(SDK_IS_ALIGNED(base, 1024));
    eth.eth->RXBASE = (uint32_t)base & ETH_RXBASE_BADDR_Msk;
}

static inline void *ll_eth_get_rx_base(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return (void *)(eth.eth->RXBASE & ETH_RXBASE_BADDR_Msk);
}

static inline uint32_t ll_eth_get_rx_dpnt(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return (eth.eth->RXBASE & ETH_RXBASE_DPNT_Msk) >> ETH_RXBASE_DPNT_Pos;
}

static inline void ll_eth_mdio_read_start(ll_eth_t eth, uint8_t phy_addr, uint8_t reg_addr)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->MDIOCSR = ((uint32_t)phy_addr << ETH_MDIOCSR_PADDR_Pos) | ((uint32_t)reg_addr << ETH_MDIOCSR_RADDR_Pos) |
                       ETH_MDIOCSR_RD_Msk;
}

static inline void ll_eth_mdio_write_start(ll_eth_t eth, uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->MDIOCSR = ((uint32_t)data << ETH_MDIOCSR_DATA_Pos) | ((uint32_t)phy_addr << ETH_MDIOCSR_PADDR_Pos) |
                       ((uint32_t)reg_addr << ETH_MDIOCSR_RADDR_Pos) | ETH_MDIOCSR_WR_Msk;
}

static inline bool ll_eth_mdio_busy(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->MDIOCSR_bit.BUSY != 0U;
}

static inline bool ll_eth_mdio_link_fail(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->MDIOCSR_bit.LINKFAIL != 0U;
}

static inline uint16_t ll_eth_mdio_data(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return (uint16_t)eth.eth->MDIOCSR_bit.DATA;
}

static inline bool ll_eth_mdio_wait(ll_eth_t eth, int32_t spins)
{
    const bool forever = (spins < 0);
    while (forever || --spins) {
        if (!ll_eth_mdio_busy(eth)) {
            return true;
        }
    }
    return false;
}

static inline uint16_t ll_eth_mdio_read(ll_eth_t eth, uint8_t phy_addr, uint8_t reg_addr, int32_t spins)
{
    ll_eth_mdio_read_start(eth, phy_addr, reg_addr);
    LL_ASSERT(ll_eth_mdio_wait(eth, spins));
    LL_ASSERT(!ll_eth_mdio_link_fail(eth));
    return ll_eth_mdio_data(eth);
}

static inline void ll_eth_mdio_clear(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->MDIOCSR = 0U;
}

static inline bool ll_eth_mdio_write(ll_eth_t eth, uint8_t phy_addr, uint8_t reg_addr, uint16_t data, int32_t spins)
{
    ll_eth_mdio_write_start(eth, phy_addr, reg_addr, data);
    if (!ll_eth_mdio_wait(eth, spins)) {
        return false;
    }
    const bool link_success = !ll_eth_mdio_link_fail(eth);
    ll_eth_mdio_clear(eth);
    return link_success;
}

static inline void ll_eth_phy_select(ll_eth_t eth, bool use_ext_phy)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->PHYCFG_bit.EXTPHY = (int)use_ext_phy ? 1U : 0U;
}

static inline bool ll_eth_phy_is_external(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->PHYCFG_bit.EXTPHY != 0U;
}

static inline void ll_eth_phycfg_rgmii_enable(ll_eth_t eth, bool enable)
{
#ifdef K1921VG3T
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->PHYCFG_bit.RGMII = (int)enable ? 1U : 0U;
#else
    (void)eth;
    (void)enable;
#endif
}

static inline uint32_t ll_eth_rgmii_status(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->RGMII_STAT;
}

static inline bool ll_eth_rgmii_link_up(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->RGMII_STAT_bit.LS != 0U;
}

static inline ll_eth_speed_t ll_eth_rgmii_get_speed(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    if (eth.eth->RGMII_STAT_bit.GB) {
        return LL_ETH_SPEED_1000M;
    }
    return eth.eth->RGMII_STAT_bit.SPEED ? LL_ETH_SPEED_100M : LL_ETH_SPEED_10M;
}

static inline ll_eth_duplex_t ll_eth_rgmii_get_duplex(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->RGMII_STAT_bit.DS ? LL_ETH_DUPLEX_FULL : LL_ETH_DUPLEX_HALF;
}

static inline uint32_t ll_eth_rgmii_irq_flags(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->RGMII_IF; /* read-only, семантика очистки не описана */
}

static inline uint32_t ll_eth_rgmii_irq_mask(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    return eth.eth->RGMII_IM;
}

static inline void ll_eth_rgmii_irq_mask_set(ll_eth_t eth, uint32_t mask)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->RGMII_IM = mask;
}

static inline void ll_eth_rgmii_irq_enable(ll_eth_t eth, uint32_t mask)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->RGMII_IM |= mask;
}

static inline void ll_eth_rgmii_irq_disable(ll_eth_t eth, uint32_t mask)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    eth.eth->RGMII_IM &= ~mask;
}

static inline void ll_eth_init(ll_eth_t eth, const ll_eth_init_t *init)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));
    LL_ASSERT(init != NULL);
    LL_ASSERT(!init->use_builtin_phy);

    ll_rcu_clock_enable(eth.rcu);
    ll_rcu_reset_release(eth.rcu);

    if (eth.rcu.clkcfg) {
        ll_rcu_set_source(eth.rcu, (ll_rcu_clksel_t)init->pll.number);
        if (init->clk_divider == 0U) {
            ll_rcu_set_divider(eth.rcu, false, 0U);
        } else {
            ll_rcu_set_divider(eth.rcu, true, (init->clk_divider - 1U));
        }
        ll_rcu_clkcfg_enable(eth.rcu);
    }
}

static inline void ll_eth_apply_config(ll_eth_t eth, const ll_eth_init_t init)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));

    ll_eth_set_promiscuous(eth, init.promiscuous);
    ll_eth_set_multicast_enable(eth, init.multicast_enable);
    ll_eth_irq_mask_set(eth, init.irq);
}

static inline void ll_eth_deinit(ll_eth_t eth)
{
    LL_ASSERT(IS_ETH_PERIPH(eth.eth));

    ll_eth_tx_stop(eth);
    ll_eth_rx_stop(eth);
    ll_eth_irq_mask_set(eth, LL_ETH_IRQ_NONE);

    if (eth.rcu.clkcfg) {
        ll_rcu_clkcfg_disable(eth.rcu);
    }
    ll_rcu_reset_assert(eth.rcu);
    ll_rcu_clock_disable(eth.rcu);
}

typedef struct {
    volatile uint32_t WORD0;
    volatile uint32_t WORD1;
} ll_eth_dsc_t;

#define LL_ETH_DESC_ALIGN       4U
#define LL_ETH_DESC_TABLE_ALIGN 1024U
#define LL_ETH_TX_MAX_LEN       1514U
#define LL_ETH_RX_MAX_LEN       1518U

#define LL_ETH_DESC_LENGTH_Msk 0x7FFUL
#define LL_ETH_DESC_EN_Msk     (1UL << 11U)
#define LL_ETH_DESC_WR_Msk     (1UL << 12U)
#define LL_ETH_DESC_IE_Msk     (1UL << 13U)
#define LL_ETH_DESC_ADDR_Msk   0xFFFFFFFCUL

#define LL_ETH_TXDESC_UE_Msk  (1UL << 14U)
#define LL_ETH_TXDESC_AL_Msk  (1UL << 15U)
#define LL_ETH_TXDESC_LC_Msk  (1UL << 16U)
#define LL_ETH_TXDESC_MO_Msk  (1UL << 17U)
#define LL_ETH_TXDESC_IC_Msk  (1UL << 18U)
#define LL_ETH_TXDESC_TC_Msk  (1UL << 19U)
#define LL_ETH_TXDESC_UC_Msk  (1UL << 20U)
#define LL_ETH_TXDESC_ERR_Msk (LL_ETH_TXDESC_UE_Msk | LL_ETH_TXDESC_AL_Msk | LL_ETH_TXDESC_LC_Msk)

#define LL_ETH_RXDESC_AE_Msk (1UL << 14U)
#define LL_ETH_RXDESC_FT_Msk (1UL << 15U)
#define LL_ETH_RXDESC_CE_Msk (1UL << 16U)
#define LL_ETH_RXDESC_OE_Msk (1UL << 17U)
#define LL_ETH_RXDESC_LE_Msk (1UL << 18U)
#define LL_ETH_RXDESC_ID_Msk (1UL << 19U)
#define LL_ETH_RXDESC_IR_Msk (1UL << 20U)
#define LL_ETH_RXDESC_UD_Msk (1UL << 21U)
#define LL_ETH_RXDESC_UR_Msk (1UL << 22U)
#define LL_ETH_RXDESC_TD_Msk (1UL << 23U)
#define LL_ETH_RXDESC_TR_Msk (1UL << 24U)
#define LL_ETH_RXDESC_IF_Msk (1UL << 25U)
#define LL_ETH_RXDESC_MC_Msk (1UL << 26U)
#define LL_ETH_RXDESC_ERR_Msk \
    (LL_ETH_RXDESC_AE_Msk | LL_ETH_RXDESC_CE_Msk | LL_ETH_RXDESC_OE_Msk | LL_ETH_RXDESC_LE_Msk)

typedef struct {
    bool irq;
    bool wrap;
    bool more;
    bool csum_ip;
    bool csum_tcp;
    bool csum_udp;
} ll_eth_tx_desc_cfg_t;

typedef struct {
    bool irq;
    bool wrap;
} ll_eth_rx_desc_cfg_t;

static inline void ll_eth_dsc_set_buf(ll_eth_dsc_t *desc, const void *buf)
{
    LL_ASSERT(SDK_IS_ALIGNED_4(buf));
    LL_ASSERT(desc != NULL);
    desc->WORD1 = (uint32_t)buf & LL_ETH_DESC_ADDR_Msk;
}

static inline void *ll_eth_dsc_get_buf(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (void *)(desc->WORD1 & LL_ETH_DESC_ADDR_Msk);
}

static inline void ll_eth_dsc_set_len(ll_eth_dsc_t *desc, uint16_t len)
{
    LL_ASSERT(desc != NULL);
    desc->WORD0 = (desc->WORD0 & ~LL_ETH_DESC_LENGTH_Msk) | ((uint32_t)len & LL_ETH_DESC_LENGTH_Msk);
}

static inline uint16_t ll_eth_dsc_get_len(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (uint16_t)(desc->WORD0 & LL_ETH_DESC_LENGTH_Msk);
}

static inline void ll_eth_dsc_set_en(ll_eth_dsc_t *desc, bool en)
{
    LL_ASSERT(desc != NULL);
    if (en) {
        desc->WORD0 |= LL_ETH_DESC_EN_Msk;
    } else {
        desc->WORD0 &= ~LL_ETH_DESC_EN_Msk;
    }
}

static inline bool ll_eth_dsc_is_busy(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_DESC_EN_Msk) != 0U;
}

static inline void ll_eth_dsc_set_wrap(ll_eth_dsc_t *desc, bool wrap)
{
    LL_ASSERT(desc != NULL);
    if (wrap) {
        desc->WORD0 |= LL_ETH_DESC_WR_Msk;
    } else {
        desc->WORD0 &= ~LL_ETH_DESC_WR_Msk;
    }
}

static inline void ll_eth_dsc_set_irq(ll_eth_dsc_t *desc, bool irq)
{
    LL_ASSERT(desc != NULL);
    if (irq) {
        desc->WORD0 |= LL_ETH_DESC_IE_Msk;
    } else {
        desc->WORD0 &= ~LL_ETH_DESC_IE_Msk;
    }
}

static inline void ll_eth_tx_dsc_link(ll_eth_dsc_t *desc, bool more)
{
    LL_ASSERT(desc != NULL);
    if (more) {
        desc->WORD0 |= LL_ETH_TXDESC_MO_Msk;
    } else {
        desc->WORD0 &= ~LL_ETH_TXDESC_MO_Msk;
    }
}

static inline void ll_eth_dsc_prep_tx(ll_eth_dsc_t *desc, const void *buf, uint16_t len, ll_eth_tx_desc_cfg_t cfg)
{
    LL_ASSERT(desc != NULL);
    LL_ASSERT(buf != NULL);
    LL_ASSERT(SDK_IS_ALIGNED_4((void *)desc));
    LL_ASSERT(len <= LL_ETH_TX_MAX_LEN);

    uint32_t w0 = (uint32_t)len & LL_ETH_DESC_LENGTH_Msk;
    if (cfg.irq) {
        w0 |= LL_ETH_DESC_IE_Msk;
    }
    if (cfg.wrap) {
        w0 |= LL_ETH_DESC_WR_Msk;
    }
    if (cfg.more) {
        w0 |= LL_ETH_TXDESC_MO_Msk;
    }
    if (cfg.csum_ip) {
        w0 |= LL_ETH_TXDESC_IC_Msk;
    }
    if (cfg.csum_tcp) {
        w0 |= LL_ETH_TXDESC_TC_Msk;
    }
    if (cfg.csum_udp) {
        w0 |= LL_ETH_TXDESC_UC_Msk;
    }

    desc->WORD1 = (uint32_t)buf & LL_ETH_DESC_ADDR_Msk;
    desc->WORD0 = w0;
    desc->WORD0 = w0 | LL_ETH_DESC_EN_Msk;
}

static inline bool ll_eth_tx_desc_has_error(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_TXDESC_ERR_Msk) != 0U;
}

static inline bool ll_eth_tx_desc_underflow(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_TXDESC_UE_Msk) != 0U;
}

static inline bool ll_eth_tx_desc_attempt_limit(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_TXDESC_AL_Msk) != 0U;
}

static inline bool ll_eth_tx_desc_late_collision(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_TXDESC_LC_Msk) != 0U;
}

static inline void ll_eth_dsc_prep_rx(ll_eth_dsc_t *desc, void *buf, ll_eth_rx_desc_cfg_t cfg)
{
    LL_ASSERT(desc != NULL);
    LL_ASSERT(buf != NULL);
    LL_ASSERT(SDK_IS_ALIGNED_4((void *)desc));

    uint32_t w0 = 0U;
    if (cfg.irq) {
        w0 |= LL_ETH_DESC_IE_Msk;
    }
    if (cfg.wrap) {
        w0 |= LL_ETH_DESC_WR_Msk;
    }

    desc->WORD1 = (uint32_t)buf & LL_ETH_DESC_ADDR_Msk;
    desc->WORD0 = w0;
    desc->WORD0 = w0 | LL_ETH_DESC_EN_Msk;
}

static inline bool ll_eth_rx_desc_has_error(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_ERR_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_crc_error(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_CE_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_overflow(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_OE_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_alignment_error(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_AE_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_frame_too_long(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_FT_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_length_mismatch(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_LE_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_multicast(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_MC_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_fragmented_ip(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_IF_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_ip_detected(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_ID_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_ip_csum_error(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_IR_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_udp_detected(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_UD_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_udp_csum_error(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_UR_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_tcp_detected(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_TD_Msk) != 0U;
}

static inline bool ll_eth_rx_desc_tcp_csum_error(const ll_eth_dsc_t *desc)
{
    LL_ASSERT(desc != NULL);
    return (desc->WORD0 & LL_ETH_RXDESC_TR_Msk) != 0U;
}

#ifdef __cplusplus
}
#endif
