//
// Created by zhiyo on 2025/4/13.
//

#ifndef LED_H
#define LED_H
#include <string>
#include <sys/types.h>
#define D1 22
#define D2 21
#define D3 20

class LED {
private:
    std::string name = {};
    uint pin = 0;

    public:
    LED(std::string name, uint pin);
    void OPE(uint state);
    int getState() const;
};



#endif //LED_H
