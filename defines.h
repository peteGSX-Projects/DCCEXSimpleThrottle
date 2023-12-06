/*
 *  © 2023 Peter Cole
 *
 *  This file is for a serially connected throttle for a DCC-EX EX-CommandStation.
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

#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif

// If we haven't got a custom config.h, use the example
#if __has_include ( "config.h")
  #include "config.h"
#else
  #warning config.h not found. Using defaults from config.example.h
  #include "config.example.h"
#endif

// If connection retries not defined, define default 20
#ifndef CONNECT_RETRIES
#define CONNECT_RETRIES 20
#endif

// If OLED font not defined, set it
#ifndef OLED_FONT
#define OLED_FONT System5x7
#endif

// Include the right libraries and set correct alias for connection type
#if defined(OLED_USE_I2C)
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#define OLED SSD1306AsciiWire
#ifndef OLED_ADDRESS
#define OLED_ADDRESS 0x3c
#endif
#elif defined(OLED_USE_SPI)
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"
#define OLED SSD1306AsciiSpi
#endif

// If OLED type not defined, set it
#ifndef OLED_TYPE
#define OLED_TYPE &SH1106_128x64
#endif

// Define console and client based on device type
#if defined(ARDUINO_BLUEPILL_F103C8) || defined(ARDUINO_BLACKPILL_F411CE)
#undef CONSOLE
#undef CLIENT
#define CONSOLE Serial
#define CLIENT Serial1
#elif defined(ARDUINO_ARCH_ESP32)
#undef CONSOLE
#undef CLIENT
#define CONSOLE Serial
extern WiFiClient client;
#define CLIENT client
// If we haven't got a custom config_wifi.h, use the example
#if __has_include ( "config_wifi.h")
  #include "config_wifi.h"
#else
  #warning config_wifi.h not found. Using defaults from config_wifi.example.h
  #include "config_wifi.example.h"
#endif
#endif

#endif
