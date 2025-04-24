//
// Created by zhiyo on 2025/3/3.
//

#ifndef MQTT_TOOL_H
#define MQTT_TOOL_H
#include <MQTTClient.h>
#include <string.h>
#include "Countdown.h"
#include "IPStack.h"

using namespace std;

class Mqtt_tool {
private:
    IPStack ipstack;
    MQTT::Client<IPStack, Countdown> client;

public:
    Mqtt_tool(const char *ssid, const char *pw);

    void connect_MQTT(const char *hostname, int port, const char *clientID);

    void subscribe_MQTT(const char *mqtt_topic, MQTT::QoS qos_level);

    void publish_MQTT(MQTT::QoS qos_level, const char *mqtt_topic, void *mqtt_message,
                     int mqtt_message_len);

    int yield_MQTT(int yield_time);
};


#endif //MQTT_TOOL_H
