/*
 *  © 2024 Peter Cole
 *  © 2023 Peter Cole
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <Arduino.h>

// If we haven't got a custom myConfig.h, use the example
#if __has_include("myConfig.h")
#include "myConfig.h"
#else
#warning myConfig.h not found. Using defaults from myConfig.example.h
#include "myConfig.example.h"
#endif

// If connection retries not defined, define default 20
#ifndef CONNECT_RETRIES
#define CONNECT_RETRIES 20
#endif

// Define console and client based on device type
#if defined(ARDUINO_ARCH_STM32)
#undef CONSOLE
#undef CLIENT
#define CONSOLE Serial
#define CLIENT Serial1
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#undef CONSOLE
#undef CLIENT
#define CONSOLE Serial
extern WiFiClient wifiClient;
#define CLIENT wifiClient

struct EXCommandStation {
  const char *name;
  IPAddress ipAddress;
  uint16_t port;
  const char *ssid;
  const char *password;
};

#endif

extern bool connected;

enum EncoderMode {
  OPERATE_LOCO,
  SELECT_LOCO,
  SELECT_SERVER,
  SELECT_EXTRAS,
};

// Default pin and OLED definitions for Bluepill/Blackpill
#if defined(ARDUINO_ARCH_STM32)
#ifndef ENCODER_DT
#define ENCODER_DT PC14
#endif // ENCODER_DT
#ifndef ENCODER_CLK
#define ENCODER_CLK PC15
#endif // ENCODER_CLK
#ifndef ENCODER_SW
#define ENCODER_SW PA0
#endif // ENCODER_SW
#ifndef OLED_USE
#define OLED_USE_I2C // Default to I2C for Bluepill
#endif // OLED_USE
#ifndef OLED_ADDRESS
#define OLED_ADDRESS 0x3c
#endif // OLED_ADDRESS
#ifndef SCL_PIN
#define SCL_PIN PB6
#endif // SCL_PIN
#ifndef SDA_PIN
#define SDA_PIN PB7
#endif // SDA_PIN
#ifndef CS_PIN
#define CS_PIN PA4
#endif // CS_PIN
#ifndef DC_PIN
#define DC_PIN PA3
#endif // DC_PIN
// Reference:
// SCK - PA5
// MISO - PA6
// MOSI - PA7

// Default pin and OLED definitions for ESP32
#elif defined(ARDUINO_ARCH_ESP32)

#ifndef ENCODER_DT
#define ENCODER_DT 12
#endif // ENCODER_DT
#ifndef ENCODER_CLK
#define ENCODER_CLK 14
#endif // ENCODER_CLK
#ifndef ENCODER_SW
#define ENCODER_SW 13
#endif // ENCODER_SW
#ifndef OLED_USE
// #define OLED_USE_SPI // Default to SPI for ESP32
#define OLED_USE_I2C
#endif // OLED_USE
#ifndef OLED_ADDRESS
#define OLED_ADDRESS 0x3c
#endif // OLED_ADDRESS
#ifndef SCL_PIN
#define SCL_PIN 22
#endif // SCL_PIN
#ifndef SDA_PIN
#define SDA_PIN 23
#endif // SDA_PIN
#ifndef CS_PIN
#define CS_PIN 5
#endif // CS_PIN
#ifndef DC_PIN
// #define DC_PIN ?
#endif // DC_PIN
// Reference:
// SCK - 18
// MISO - 19
// MOSI - 23

/*
Macro to create CommandStation and WiFi configuration details
*/
#define CREATE_COMMANDSTATION_SERVER(index)                                                                            \
  {                                                                                                                    \
    COMMANDSTATION_LABEL_##index, convertIP(COMMANDSTATION_IP_##index), COMMANDSTATION_PORT_ #index,                   \
        COMMANDSTATION_SSID_ #index, COMMANDSTATION_PASSWORD_##index                                                   \
  }

#endif // ARCH type

#endif
