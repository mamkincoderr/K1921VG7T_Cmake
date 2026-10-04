#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <ll_assert.h>
#include <ll_eth_vgxt.h>
#include <ll_gpio.h>
#include <ll_rcu.h>
#include <soc.h>

#if !defined(K1921VG3T)
#error "ll_eth_vgxt_ext_phy.h: external PHY is not supported for the selected SoC"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GPIO_TypeDef *gpio;
    ll_rcu_periph_t rcu;
    uint32_t altfunc_mask;
    uint8_t altfunc_num;
} ll_eth_ext_phy_gpio_port_t;

#define LL_ETH_EXT_PHY_MAX_PORTS 2U

typedef struct {
    ll_eth_ext_phy_gpio_port_t ports[LL_ETH_EXT_PHY_MAX_PORTS];
    uint8_t port_count;
} ll_eth_ext_phy_t;

#define LL_ETH0_EXT_PHY                                  \
    ((ll_eth_ext_phy_t){                                 \
        .ports =                                         \
            {                                            \
                {GPIOA, LL_RCU_GPIOA, 0x0000FFFFU, 2U}, \
                {GPIOB, LL_RCU_GPIOB, 0x0000FFFFU, 2U}, \
            },                                           \
        .port_count = 2U,                                \
    })

static inline void ll_eth_ext_phy_gpio_init(ll_eth_ext_phy_t phy)
{
    LL_ASSERT(phy.port_count <= LL_ETH_EXT_PHY_MAX_PORTS);

    for (uint8_t i = 0U; i < phy.port_count; i++) {
        ll_eth_ext_phy_gpio_port_t *port = &phy.ports[i];

        ll_rcu_peripheral_init(port->rcu);

        uint32_t mask = port->altfunc_mask;
        while (mask) {
            const uint32_t pin = (uint32_t)__builtin_ctz(mask);
            ll_gpio_set_altfunc(port->gpio, pin, port->altfunc_num);
            mask &= mask - 1U;
        }

        ll_gpio_altfunc_enable(port->gpio, port->altfunc_mask);
    }
}

static inline void ll_eth_ext_phy_select(ll_eth_t eth)
{
    ll_eth_phy_select(eth, true);
    ll_eth_phycfg_rgmii_enable(eth, false);
}

static inline void ll_eth_ext_phy_init(ll_eth_t eth, ll_eth_ext_phy_t phy)
{
    ll_eth_ext_phy_gpio_init(phy);
    ll_eth_ext_phy_select(eth);
}

typedef struct {
    GPIO_TypeDef *gpio;
    ll_rcu_periph_t rcu;
    uint32_t pin_mask;
    bool active_low;
} ll_eth_ext_phy_rst_t;

#ifdef __cplusplus
}
#endif
