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

/// @brief Provide default definitions that can be overridden by a user creating myConfig.h

#if __has_include("myConfig.h")
#include "myConfig.h"
#else
#warning myConfig.h not found, using defaults.
#endif

// If connection retries not defined, define default 20
#ifndef CONNECT_RETRIES
#define CONNECT_RETRIES 20
#endif

// Define the default console stream
#ifndef CONSOLE
#define CONSOLE Serial
#endif // CONSOLE

// Give OLED connection types a value
#define OLED_I2C 1
#define OLED_SPI 2

// Default display definitions
#ifndef OLED_CONNECTION
#define OLED_CONNECTION OLED_I2C
#endif // OLED_CONNECTION
#ifndef OLED_ADDRESS
#define OLED_ADDRESS 0x3c
#endif // OLED_ADDRESS

// Define the correct OLED type based on connection
#if (OLED_CONNECTION==OLED_I2C)
#define OLED_TYPE U8G2_SH1106_128X64_NONAME_F_HW_I2C
#elif (OLED_CONNECTION==OLED_SPI)
#define OLED_TYPE U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI
#else
#error Invalid OLED connection type specific, must be OLED_I2C or OLED_SPI
#endif // OLED_CONNECTION

// Default pin definitions for Bluepill/Blackpill
#if defined(ARDUINO_ARCH_STM32)
#ifndef ENCODER_DT_PIN
#define ENCODER_DT_PIN PC14
#endif // ENCODER_DT_PIN
#ifndef ENCODER_CLK_PIN
#define ENCODER_CLK_PIN PC15
#endif // ENCODER_CLK_PIN
#ifndef BUTTON_PIN
#define BUTTON_PIN PA0
#endif // BUTTON_PIN
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
// Default pin definitions for ESP32
#elif defined(ARDUINO_ARCH_ESP32)
#ifndef ENCODER_DT_PIN
#define ENCODER_DT_PIN 12
#endif // ENCODER_DT_PIN
#ifndef ENCODER_CLK_PIN
#define ENCODER_CLK_PIN 14
#endif // ENCODER_CLK_PIN
#ifndef BUTTON_PIN
#define BUTTON_PIN 13
#endif // BUTTON_PIN
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
#define DC_PIN 2
#endif // DC_PIN
// Reference:
// SCK - 18
// MISO - 19
// MOSI - 23
#endif // ARCH type

// Rotary encoder defaults
#ifndef BUTTON_PIN_MODE
#define BUTTON_PIN_MODE INPUT_PULLUP
#endif // BUTTON_PIN_MODE
#ifndef BUTTON_PIN_POLARITY
#define BUTTON_PIN_POLARITY LOW
#endif // BUTTON_PIN_POLARITY
#ifndef BUTTON_DEBOUNCE_PERIOD
#define BUTTON_DEBOUNCE_PERIOD 50
#endif // BUTTON_DEBOUNCE_PERIOD
#ifndef BUTTON_LONG_PRESS_PERIOD
#define BUTTON_LONG_PRESS_PERIOD 500
#endif // BUTTON_LONG_PRESS_PERIOD
#ifndef BUTTON_DOUBLE_CLICK_PERIOD
#define BUTTON_DOUBLE_CLICK_PERIOD 250
#endif // BUTTON_DOUBLE_CLICK_PERIOD
#ifndef BUTTON_DEGLITCH_PERIOD
#define BUTTON_DEGLITCH_PERIOD 10
#endif // BUTTON_DEGLITCH_PERIOD

// Define fonts in use
#define DEFAULT_FONT u8g2_font_NokiaSmallPlain_tr
#define MENU_FONT u8g2_font_5x8_mr
#define SPEED_FONT u8g2_font_spleen12x24_mn
#define DIRECTION_FONT u8g2_font_6x10_mr
#define ADDRESS_FONT u8g2_font_6x10_mr
#define ESTOP_FONT u8g2_font_6x12_mr
#define WIFI_FONT u8g2_font_open_iconic_www_1x_t      // use 0048
#define CS_FONT u8g2_font_streamline_transportation_t // use 0034
#define ERROR_FONT u8g2_font_emoticons21_tr           // use 0029 for error

#endif