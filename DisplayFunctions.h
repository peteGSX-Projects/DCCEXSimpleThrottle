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

#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include <Arduino.h>
#include <DCCEXProtocol.h>
#include "defines.h"
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

// Extern OLED declaration
extern OLED oled;

void setupDisplay();
void displayStartupInfo();
void switchDisplay();
void displayRuntime();
void displaySpeed();
void displayDirection();
void displayLoco();
void displayTrackPower();
void displayMenu();
void scrollMenu(int direction);

#endif
