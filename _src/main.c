#include "__preprocessor__.h"
#include "pico/stdlib.h"

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

int pico_led_init(void)
{
#if defined(PICO_DEFAULT_LED_PIN)
    gpio_init(PICO_DEFAULT_LED_PIN);                // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);   // so we can use normal GPIO functionality to turn the led on and off
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    return cyw43_arch_init(); // For Pico W devices we need to initialise the driver etc
#endif
}

void pico_set_led(bool led_on)
{
#if defined(PICO_DEFAULT_LED_PIN)
    gpio_put(PICO_DEFAULT_LED_PIN, led_on); // Just set the GPIO on or off
#elif defined(CYW43_WL_GPIO_LED_PIN)
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on); // Ask the wifi "driver" to set the GPIO on or off
#endif
}

#define my_time 100

int main()
{
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);

    while (true)
    {
        pico_set_led(true);
        sleep_ms(my_time);
        pico_set_led(false);
        sleep_ms(my_time);
    }

    return 0;
}
