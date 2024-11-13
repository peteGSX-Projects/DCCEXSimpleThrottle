// Example myConfig.h file
// Copy this to myConfig.h and update to suit

#ifndef MYCONFIG_H
#define MYCONFIG_H

/*
Define WiFi connection parameters here
*/
#define COMMANDSTATION_COUNT 2 // The number of EX-CommandStations to define

/*
Define connection options for each EX-CommandStation entry

Each line must have the exact same number of items as set in COMMANDSTATION_COUNT above
Each element must be surrounded by quotes "" and separated by a commad
Each list of elements must be surrounded by curly brackets {}

#define COMMANDSTATION_NAMES {"Example 1", "Example 2"}
#define COMMANDSTATION_IPS {"192.168.4.1", "192.168.0.1"}
#define COMMANDSTATION_PORTS {2560, 2560}
#define COMMANDSTATION_SSIDS {"SSID1", "SSID2"}
#define COMMANDSTATION_PASSWORDS {"Password1", "Password2"}
*/
#define COMMANDSTATION_NAMES {"CommandStation 1", "CommandStation 2"}
#define COMMANDSTATION_IPS {"192.168.4.1", "192.168.0.1"}
#define COMMANDSTATION_PORTS {2560, 2560}
#define COMMANDSTATION_SSIDS {"SSID1", "SSID2"}
#define COMMANDSTATION_PASSWORDS {"Password1", "Password2"}

// If necessary, define OLED type, address, and pins
// #define OLED_USE_I2C // Default to I2C
// #define OLED_USE_SPI
// #define OLED_ADDRESS 0x3c

// #define SCL_PIN PB6 // Default for Bluepill
// #define SCL_PIN 22 // Default for ESP32
// #define SDA_PIN PB7 // Default for Bluepill
// #define SDA_PIN 23 // Default for ESP32
// #define CS_PIN PA4 // Default for Bluepill
// #define CS_PIN 5 // Default for ESP32
// #define DC_PIN PA3 // Default for Bluepill
// #define DC_PIN ? // Default for ESP32

// If necessary, define pins for the rotary encoder
// #define ENCODER_DT PC14 // Default for Bluepill
// #define ENCODER_DT 12 // Default for ESP32
// #define ENCODER_CLK PC15 // Default for Bluepill
// #define ENCODER_CLK 14 // Default for ESP32
// #define ENCODER_SW PA0 // Default for Bluepill
// #define ENCODER_SW 13 // Default for ESP32

#endif // MYCONFIG_H
