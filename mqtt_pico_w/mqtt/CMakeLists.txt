cmake_minimum_required(VERSION 3.20)

# Set board type because we are building for PicoW
set(PICO_BOARD pico_w)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C   standards
project(ex5 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

add_compile_options(
        -Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
)

file(GLOB MQTT_SOURCES "Tool/mqtt/paho.mqtt.embedded-c/MQTTPacket/src/*.c")

add_executable(ex5 main.cpp
        Tool/mqtt/mqtt/Countdown.h
        Tool/mqtt/mqtt/Countdown.cpp
        Tool/mqtt/mqtt/lwipopts.h
        Tool/mqtt/mqtt/IPStack.h
        Tool/mqtt/mqtt/IPStack.cpp
        ${MQTT_SOURCES}
        Tool/mqtt/Mqtt_tool.h
        Tool/mqtt/Mqtt_tool.cpp
        message_handler.h
        message_handler.cpp
        bean/LED.h
        bean/LED.cpp
        Tool/Debounce.h
        Tool/Debounce.cpp
        Tool/json/json_handler.h
        Tool/json/Json_handler.cpp
        Tool/json/core_json.c
        message_handler.cpp
        bean/CPU.h
        bean/CPU.cpp
        config/Device_map.h
        service/service.h
        service/service.cpp
        Tool/String_Tool_for_hardware.h
        Tool/String_Tool_for_hardware.cpp
)


# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        hardware_i2c
        hardware_spi
        hardware_gpio
        pico_cyw43_arch_lwip_poll
        hardware_adc
)

target_include_directories(ex5 PRIVATE
        Tool/mqtt/mqtt
        Tool/mqtt/paho.mqtt.embedded-c/MQTTPacket/src
        Tool/mqtt/paho.mqtt.embedded-c/MQTTClient/src
        Tool/json
)

# Disable usb output, enable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)