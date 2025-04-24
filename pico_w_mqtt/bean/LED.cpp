//
// Created by zhiyo on 2025/4/13.
//

#include "LED.h"

#include <hardware/gpio.h>



LED::LED(std::string name, uint pin): name(name), pin(pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}


void LED::OPE(uint state) {
    gpio_put(pin, state);
}

int LED::getState() const {
    return gpio_get(pin);
}
