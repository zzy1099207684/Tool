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
    Mqtt_tool(const string &ssid, const string &pw);

    void connect_MQTT(const string &hostname, int port, const string &clientID);

    void subscribe_MQTT(const std::string &mqtt_topic, MQTT::QoS qos_level);

    void publish_MQTT(MQTT::QoS qos_level, std::string mqtt_topic, void *mqtt_message,
                     int mqtt_message_len);

    int yield_MQTT(int yield_time);
};


#endif //MQTT_TOOL_H
