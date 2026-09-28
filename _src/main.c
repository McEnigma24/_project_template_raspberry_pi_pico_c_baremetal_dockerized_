#include "__preprocessor__.h"
#include "led.h"

int main()
{
    led_init();

    led_toggle_nt(3, 300);

    while (true)
    {
        led_toggle_t(1000);
    }

    return 0;
}
