#include <atomic>
#include <cstdio>
#include <iostream>

#include "pico/stdlib.h"

#include "MQTTClient.h"
#include "Tool/mqtt/Mqtt_tool.h"
#include "IPStack.h"
#include "./bean/LED.h"
#include "Tool/Debounce.h"

#define SW_0 9
#define SW_1 8
#define SW_2 7

volatile std::atomic<int> sw_event{-1};

#if 1
void sw_init() {
    gpio_init(SW_0);
    gpio_init(SW_1);
    gpio_init(SW_2);
    gpio_set_dir(SW_0, GPIO_IN);
    gpio_set_dir(SW_1, GPIO_IN);
    gpio_set_dir(SW_2, GPIO_IN);
    gpio_pull_up(SW_0);
    gpio_pull_up(SW_1);
    gpio_pull_up(SW_2);
}

void gpio_callback(uint gpio, uint32_t events) {
    static Debounce debounce_sw0(200000); // bounce time 200ms
    static Debounce debounce_sw1(200000);
    static Debounce debounce_sw2(200000);
    if (events & GPIO_IRQ_EDGE_FALL) {
        if (gpio == SW_0 && debounce_sw0.valid()) sw_event = 0;
        else if (gpio == SW_1 && debounce_sw1.valid()) sw_event = 1;
        else if (gpio == SW_2 && debounce_sw2.valid()) sw_event = 2;
    }
}

int main() {
    stdio_init_all();
    // string wifi_ssid = "SmartIoTMQTT";
    // string wifi_pw = "SmartIoT";
    // string mqtt_ip = "192.168.50.113";
    // int mqtt_port = 1883;
    // char* wifi_ssid = "Redmi_138D";
    char wifi_ssid[20];
    strcpy(wifi_ssid, "Redmi_138D");

    char wifi_pw[20];
    strcpy(wifi_pw, "zzyzmy20272025888");

    char mqtt_ip[20];
    strcpy(mqtt_ip, "192.168.31.12");
    int mqtt_port = 2883;


    // string wifi_ssid = "zzy_phone";
    // string wifi_pw = "zzy88888";
    // string mqtt_ip = "172.20.10.2";
    // int mqtt_port = 2883;

    char mqtt_clientID[20];
    strcpy(mqtt_clientID, "PicoW-1234567");

    char mqtt_topic[20];
    strcpy(mqtt_topic, "zzy/LED");
    char msg[80];
    snprintf(msg, sizeof(msg), "{\"topic\":\"%s\", \"msg\":\"MQTT_CONNECTED\"}", mqtt_topic);
    sw_init();


    Mqtt_tool mqtt_tool(wifi_ssid, wifi_pw);
    mqtt_tool.connect_MQTT(mqtt_ip, mqtt_port, mqtt_clientID);
    mqtt_tool.subscribe_MQTT(mqtt_topic, MQTT::QOS1);
    mqtt_tool.publish_MQTT(MQTT::QOS1, mqtt_topic, msg, static_cast<int>(strlen(msg)));

    gpio_set_irq_enabled_with_callback(SW_0, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled(SW_1, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(SW_2, GPIO_IRQ_EDGE_FALL, true);

    while (true) {
        int rc = mqtt_tool.yield_MQTT(10);
        if (rc != 0) {
            printf("rc from yield is %d\n", rc);
        }
        if (sw_event != -1) {
            int id = sw_event;
            sw_event = -1;
            memset(msg, 0, sizeof(msg));
            switch (id) {
                case 0:
                    snprintf(msg, sizeof(msg), "{\"topic\":\"%s\", \"msg\":\"SW_0_PRESSED\"}", mqtt_topic);
                    break;
                case 1:
                    snprintf(msg, sizeof(msg), "{\"topic\":\"%s\", \"msg\":\"SW_1_PRESSED\"}", mqtt_topic);
                    break;
                case 2:
                    snprintf(msg, sizeof(msg), "{\"topic\":\"%s\", \"msg\":\"SW_2_PRESSED\"}", mqtt_topic);
                    break;
            }
            mqtt_tool.publish_MQTT(MQTT::QOS1, mqtt_topic, msg, strlen(msg));
        }
    }
}
#endif
