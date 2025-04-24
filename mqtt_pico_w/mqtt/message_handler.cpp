//
// Created by zhiyo on 2025/3/3.
//
#include "message_handler.h"
#include <cstring>
#include <iostream>
#include <MQTTClient.h>

#include "Tool/json/core_json.h"
#include "Tool/json/json_handler.h"
#include "bean/LED.h"
#include "config/Device_map.h"
#include "service/Service.h"
#include "Tool/String_Tool_for_hardware.h"

void message_handler::messageHandler(MQTT::MessageData &md) {
    MQTT::Message &message = md.message;
    char temp_buffer[LARGE_SIZE] = {0};

    memcpy(temp_buffer, message.payload, message.payloadlen);
    temp_buffer[message.payloadlen] = '\0';

    std::cout << "Message received [length: " << message.payloadlen
            << "]: '" << temp_buffer << "'" << std::endl;

    // Process the message as needed
    Json_handler json_handler;
    json_handler.get_value_from_key(temp_buffer, "msg");
    if (json_handler.get_result() != JSONSuccess) return;
    char *msgs = json_handler.get_final_result();
    printf("msg: %s\n", msgs);
    if(strlen(msgs)<2) return;
    char set[SMALL_SIZE] = {0};
    char num[SMALL_SIZE] = {0};
    split_string_by_symbol(msgs, set, num, ";");
    if (set[0] == 0) return;

    char msg[LARGE_SIZE] = {0};
    // apply temperature
    if (strcmp(set, "temp") == 0) {
        const float cpu_temperature = cpu.get_cpu_temp_value();
        snprintf(msg, sizeof(msg), "{\"topic\":\"%s\", \"msg\":\"%.2f°C\"}", MQTT_TOPIC, cpu_temperature);
    } else if (strcmp(set, "High") == 0 && num[0] != 0) {
        auto t = static_cast<float>(strtol(num, nullptr, 10));
        if(t > low_alarm_temperature) {
            high_alarm_temperature = t;
        } else {
            snprintf(msg, sizeof(msg), "{\"topic\":\"%s\", \"msg\":\"%s°C\"}", MQTT_TOPIC, "High temperature must be higher than low temperature");
            mqtt_tool.publish_MQTT(MQTT::QOS1, MQTT_TOPIC, msg, strlen(msg));
        }
    } else if (strcmp(set, "Low") == 0 && num[0] != 0) {
        auto t = static_cast<float>(strtol(num, nullptr, 10));
        if(t < high_alarm_temperature) {
            low_alarm_temperature = t;
        } else {
            snprintf(msg, sizeof(msg), "{\"topic\":\"%s\", \"msg\":\"%s°C\"}", MQTT_TOPIC, "Low temperature must be lower than high temperature");
            mqtt_tool.publish_MQTT(MQTT::QOS1, MQTT_TOPIC, msg, strlen(msg));
        }
    }
}
