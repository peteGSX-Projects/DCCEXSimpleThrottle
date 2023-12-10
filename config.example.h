// Example config.h file
// Copy this to config.h and update to suit

#ifndef CONFIG_H
#define CONFIG_H

// Recommended rotary encoder pin definitions for Bluepill/Blackpill
#define ENCODER_DT PC14
#define ENCODER_CLK PC15
#define ENCODER_SW PA0

// Recommended rotary encoder pin definitions for ESP32
// #define ENCODER_DT 12
// #define ENCODER_CLK 14
// #define ENCODER_SW 13

// OLED connection and type
// #define OLED_USE_I2C
#define OLED_USE_SPI
#define OLED_ADDRESS 0x3c

// Recommended I2C pins for Bluepill/Blackpill
#define SCL_PIN PB6
#define SDA_PIN PB7

// Recommended I2C pins for ESP32
// #define SCL_PIN 22
// #define SDA_PIN 23

// Recommended SPI pins for Bluepill/Blackpill
#define CS_PIN PA4
#define DC_PIN PA3
// Reference:
// SCK - PA5
// MISO - PA6
// MOSI - PA7

// Recommended SPI pins for ESP32 (VSPI)
// #define CS_PIN 5
// #define DC_PIN ?
// Reference:
// SCK - 18
// MISO - 19
// MOSI - 23

#endif
