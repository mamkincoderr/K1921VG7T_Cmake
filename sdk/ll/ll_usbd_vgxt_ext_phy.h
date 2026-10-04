#pragma once
#include <stdint.h>

#include <ll_assert.h>
#include <ll_gpio.h>
#include <ll_rcu.h>
#include <prelude.h>
#include <soc.h>

#if !defined(K1921VG1T) && !defined(K1921VG3T)
#error "ll_usbd_ext_phy.h: external PHY is not supported for the selected SoC"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GPIO_TypeDef *gpio;
    ll_rcu_periph_t rcu;
    uint32_t altfunc_mask;
    uint8_t altfunc_num;
} ll_usbd_ext_phy_gpio_port_t;

typedef struct {
    GPIO_TypeDef *gpio;
    ll_rcu_periph_t rcu;
    uint32_t pin_mask;
} ll_usbd_ext_phy_rst_t;

#define LL_USBD_EXT_PHY_MAX_PORTS 3U

typedef struct {
    ll_usbd_ext_phy_rst_t rst;
    ll_usbd_ext_phy_gpio_port_t ports[LL_USBD_EXT_PHY_MAX_PORTS];
    uint8_t port_count;
} ll_usbd_ext_phy_t;

#if defined(K1921VG3T)

#define LL_USBD0_EXT_PHY                                \
    ((ll_usbd_ext_phy_t){                               \
        .rst = {GPIOA, LL_RCU_GPIOA, LL_GPIO_PIN_9},    \
        .ports =                                        \
            {                                           \
                {GPIOA, LL_RCU_GPIOA, 0x0000FFFFU, 1U}, \
                {GPIOB, LL_RCU_GPIOB, 0x00003FFFU, 1U}, \
            },                                          \
        .port_count = 2U,                               \
    })

#elif defined(K1921VG1T)

#define LL_USBD0_EXT_PHY                                   \
    ((ll_usbd_ext_phy_t){                                  \
        .rst = {GPIOF, LL_RCU_GPIOF, LL_GPIO_PIN_9},       \
        .ports =                                           \
            {                                              \
                {GPIOC, LL_RCU_GPIOC, LL_GPIO_PIN_13, 4U}, \
                {GPIOF, LL_RCU_GPIOF, 0x0000FFFFU, 4U},    \
                {GPIOG, LL_RCU_GPIOG, 0x0000FFFFU, 4U},    \
            },                                             \
        .port_count = 3U,                                  \
    })

#define LL_USBD1_EXT_PHY                                \
    ((ll_usbd_ext_phy_t){                               \
        .rst = {GPIOA, LL_RCU_GPIOA, LL_GPIO_PIN_0},    \
        .ports =                                        \
            {                                           \
                {GPIOA, LL_RCU_GPIOA, 0x0000FFFFU, 4U}, \
                {GPIOB, LL_RCU_GPIOB, 0x00003FFFU, 4U}, \
            },                                          \
        .port_count = 2U,                               \
    })

#endif /* K1921VG1T */

static inline void ll_usbd_ext_phy_reset(ll_usbd_ext_phy_t phy, sdk_clock_t clock, uint32_t wait_ms)
{
    ll_rcu_peripheral_init(phy.rst.rcu);
    ll_gpio_altfunc_disable(phy.rst.gpio, phy.rst.pin_mask);
    ll_gpio_set_dir_output(phy.rst.gpio, phy.rst.pin_mask);
    ll_gpio_clear(phy.rst.gpio, phy.rst.pin_mask);
    clock.sleep(wait_ms);
    ll_gpio_set(phy.rst.gpio, phy.rst.pin_mask);
    clock.sleep(wait_ms);
}

static inline void ll_usbd_ext_phy_gpio_init(ll_usbd_ext_phy_t phy)
{
    LL_ASSERT(phy.port_count <= LL_USBD_EXT_PHY_MAX_PORTS);

    for (uint8_t i = 0U; i < phy.port_count; i++) {
        ll_usbd_ext_phy_gpio_port_t *port = &phy.ports[i];

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

static inline void ll_usbd_ext_phy_init(ll_usbd_ext_phy_t phy, sdk_clock_t clock)
{
    ll_usbd_ext_phy_reset(phy, clock, 1);
    ll_usbd_ext_phy_gpio_init(phy);
}

#ifdef __cplusplus
}
#endif
