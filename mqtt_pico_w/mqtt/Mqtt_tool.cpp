#include "Mqtt_tool.h"

#include "../../message_handler.h"


Mqtt_tool::Mqtt_tool( const  char *ssid,  const char *pw): ipstack(ssid, pw), client(ipstack) {
}

void Mqtt_tool::connect_MQTT(const char *hostname, const int port,  const char *clientID) {
    int rc = ipstack.connect(hostname, port);
    if (rc != 1) {
        printf("rc from TCP connect is %d\n", rc);
    }
    printf("MQTT connecting\n");
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    char id_buf[32];
    strcpy(id_buf, clientID);
    data.clientID.cstring = id_buf;
    data.keepAliveInterval = 30;
    rc = client.connect(data);
    if (rc != 0) {
        printf("rc from MQTT connect is %d\n", rc);
        while (true) {
            tight_loop_contents();
        }
    }
    printf("MQTT connected\n");
}

void Mqtt_tool::subscribe_MQTT( const char *mqtt_topic, MQTT::QoS qos_level ) {
    int rc = client.subscribe(mqtt_topic, qos_level, message_handler::messageHandler);
    if (rc != 0) {
        printf("rc from MQTT subscribe is %d\n", rc);
    }
    printf("MQTT subscribe is successful\n");
}

void Mqtt_tool::publish_MQTT(MQTT::QoS qos_level , const char *mqtt_topic, void *mqtt_message, int mqtt_message_len) {
    MQTT::Message message;
    message.qos = qos_level;
    message.retained = false;
    message.dup = false;
    message.id = 0;
    message.payload = mqtt_message;
    message.payloadlen = mqtt_message_len;
    int rc = client.publish(mqtt_topic, message);
    if (rc != 0) {
        printf("rc from MQTT publish is %d\n", rc);
    }
    printf("send message: %s\n", (char *) mqtt_message);
}

int Mqtt_tool::yield_MQTT(int yield_time) {
    return client.yield(yield_time);
}
