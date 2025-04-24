//
// Created by zhiyo on 2025/3/3.
//
#include "message_handler.h"
#include <cstring>
#include <iostream>
#include "../json/core_json.h"
#include "../json/json_handler.h"

#include "../../bean/LED.h"
LED led_D1("D1", D1);
LED led_D2("D2", D2);
LED led_D3("D3", D3);



void message_handler::messageHandler(MQTT::MessageData &md) {
    MQTT::Message &message = md.message;

    char temp_buffer[256] = {0};
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
    char buffer[20];
    strcpy(buffer, msgs);
    char *led = strtok(buffer, ";");
    char *command = strtok(NULL, ";");

    LED *led_obj = nullptr;
    if (strcmp(led, "D1") == 0) {
        led_obj = &led_D1;
    } else if (strcmp(led, "D2") == 0) {
        led_obj = &led_D2;
    } else if (strcmp(led, "D3") == 0) {
        led_obj = &led_D3;
    }
    //
    //
    if (led_obj == nullptr) return;
    if (strcmp(command, "ON") == 0) {
        led_obj->OPE(1);
    } else if (strcmp(command, "OFF") == 0) {
        led_obj->OPE(0);
    } else if (strcmp(command, "TOGG") == 0) {
        led_obj->OPE(!led_obj->getState());
    }
}
