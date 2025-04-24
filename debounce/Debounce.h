//
// Created by zhiyo on 2025/4/13.
//

#ifndef DEBOUNCE_H
#define DEBOUNCE_H
#include <pico/types.h>
#include <sys/_stdint.h>


class Debounce {
private:
    absolute_time_t last_trigger{};
    uint32_t delay_us;

public:
    explicit Debounce(uint32_t delay);

    bool valid();
};


#endif //DEBOUNCE_H
