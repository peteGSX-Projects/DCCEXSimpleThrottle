// Example config.h file
// Copy this to config.h and update to suit

#ifndef MYCONFIG_H
#define MYCONFIG_H

/*
Define WiFi connection parameters here
*/
#define COMMANDSTATION_COUNT 2 // The number of EX-CommandStations to define

#define COMMANDSTATION_NAMES {"My CommandStation example", "My club"}
#define COMMANDSTATION_IPS {"192.168.4.1", "192.168.0.1"}
#define COMMANDSTATION_PORTS {2560, 2560}
#define COMMANDSTATION_SSIDS {"DCCEX_123456", "MY_CLUB_SSID"}
#define COMMANDSTATION_PASSWORDS {"PASS_123456", "MY_CLUB_PASSWORD"}

#define LOCAL_ROSTER_COUNT 3

#define LOCAL_ROSTER_NAMES {"Local Loco 1001", "Local Loco 1002", "Local Loco 1003"}
#define LOCAL_ROSTER_ADDRESSES {1001, 1002, 1003}

// Recommended rotary encoder pin definitions for Bluepill/Blackpill
// #define ENCODER_DT PC14
// #define ENCODER_CLK PC15
// #define ENCODER_SW PA0

// Recommended rotary encoder pin definitions for ESP32
// #define ENCODER_DT 12
// #define ENCODER_CLK 14
// #define ENCODER_SW 13

// OLED font
// #define OLED_FONT System5x7

// OLED connection and type
// #define OLED_USE_I2C
// #define OLED_USE_SPI
// #define OLED_TYPE &Adafruit128x64
// #define OLED_TYPE &SH1106_128x64
// #define OLED_ADDRESS 0x3c

// Recommended I2C pins for Bluepill/Blackpill
// #define SCL_PIN PB6
// #define SDA_PIN PB7

// Recommended I2C pins for ESP32
// #define SCL_PIN 22
// #define SDA_PIN 23

// Recommended SPI pins for Bluepill/Blackpill
// #define CS_PIN PA4
// #define DC_PIN PA3
// Reference:
// SCK - PA5
// MISO - PA6
// MOSI - PA7

// Recommended SPI pins for ESP32 (VSPI)
// #define CS_PIN 5
// #define DC_PIN 4
// Reference:
// SCK - 18
// MISO - 19
// MOSI - 23

#endif
