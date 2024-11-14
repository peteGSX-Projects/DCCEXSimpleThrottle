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

#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include "Defines.h"
#include <Arduino.h>
#include <DCCEXProtocol.h>
#include <U8g2lib.h>

// Include the right libraries and set correct alias for connection type
#if defined(OLED_USE_I2C)
#define OLED U8G2_SH1106_128X64_NONAME_F_HW_I2C
#ifndef OLED_ADDRESS
#define OLED_ADDRESS 0x3c
#endif
#elif defined(OLED_USE_SPI)
#include <SPI.h>
#define OLED U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI
#endif

#define DEFAULT_FONT u8g2_font_NokiaSmallPlain_tr
#define MENU_FONT u8g2_font_5x8_mr
#define SPEED_FONT u8g2_font_spleen12x24_mn
#define DIRECTION_FONT u8g2_font_6x10_mr
#define ADDRESS_FONT u8g2_font_6x10_mr
#define ESTOP_FONT u8g2_font_6x12_mr
#define WIFI_FONT u8g2_font_open_iconic_www_1x_t      // use 0048
#define CS_FONT u8g2_font_streamline_transportation_t // use 0034
#define ERROR_FONT u8g2_font_emoticons21_tr           // use 0029 for error

// Extern OLED declaration
extern OLED oled;

/// @brief Setup the display object
void setupDisplay();

/// @brief Display software version for 2 seconds
void displayStartupInfo();

/// @brief Switch between displaying the current menu and displaying loco info
void switchDisplay();

/// @brief Update display with current loco info if not displaying a menu
void displayRuntime();

/// @brief Update the speed display of the current loco
void displaySpeed();

/// @brief Update the direction display of the current loco
void displayDirection();

/// @brief Update the DCC address of the current loco
void displayLoco();

/// @brief Update the current track power state
void displayTrackPower();

/// @brief Display the currently selected menu and items
void displayMenu();

/// @brief Scroll up or down when a list of menu items exceeds a full page
/// @param direction Direction to scroll: 1 for down, -1 for up
void scrollMenu(int direction);

/// @brief Display an error on screen
/// @param error Error text to display
void displayError(const char *error);

#endif
