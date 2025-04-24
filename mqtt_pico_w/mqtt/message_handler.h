//
// Created by zhiyo on 2025/3/3.
//

#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H
#include <MQTTClient.h>


class message_handler {
  public:
    static void messageHandler(MQTT::MessageData &md);

};



#endif //MESSAGE_HANDLER_H
