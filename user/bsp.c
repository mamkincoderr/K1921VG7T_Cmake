/* Светодиод и кнопка платы NIIET-MINI-K1921VG7T.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 */
#include "bsp.h"
#include "ll_gpio.h"
#include "ll_rcu.h"

void bsp_init(void)
{
    ll_rcu_peripheral_init(LL_RCU_GPIOB);
    ll_gpio_clear(LED_PORT, LED_PIN_MSK);
    ll_gpio_set_dir_output(LED_PORT, LED_PIN_MSK);
    /* USER BTN (SB2) замыкает B1 на землю. Без подтяжки вход плавает. */
    ll_gpio_set_dir_input(BTN_PORT, BTN_PIN_MSK);
    ll_gpio_set_pull(BTN_PORT, BTN_PIN_MSK, LL_GPIO_PULL_UP);
}

void bsp_led_on(void)     { ll_gpio_set(LED_PORT, LED_PIN_MSK); }
void bsp_led_off(void)    { ll_gpio_clear(LED_PORT, LED_PIN_MSK); }
void bsp_led_toggle(void) { ll_gpio_toggle(LED_PORT, LED_PIN_MSK); }

int bsp_button_pressed(void)
{
    return !ll_gpio_read_pin(BTN_PORT, BTN_PIN_MSK);
}
