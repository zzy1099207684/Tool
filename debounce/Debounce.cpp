//
// Created by zhiyo on 2025/4/13.
//

#include "Debounce.h"

#include <pico/time.h>
#include <pico/types.h>
Debounce::Debounce(uint32_t delay): delay_us(delay) { last_trigger = get_absolute_time(); }

bool Debounce::valid() {
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_trigger, now) >= delay_us) {
        last_trigger = now;
        return true;
    }
    return false;
}


// using example
// void gpio_callback(uint gpio, uint32_t events) {
//     static Debounce debounce_sw0(200000); // bounce time 200ms
//     static Debounce debounce_sw1(200000);
//     static Debounce debounce_sw2(200000);
//     if (events & GPIO_IRQ_EDGE_FALL) {
//         if (gpio == SW_0 && debounce_sw0.valid()) sw_event = 0;
//         else if (gpio == SW_1 && debounce_sw1.valid()) sw_event = 1;
//         else if (gpio == SW_2 && debounce_sw2.valid()) sw_event = 2;
//     }
// }