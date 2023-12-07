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

// If OLED font not defined, set it
#ifndef OLED_FONT
#define OLED_FONT System5x7
#endif

// If OLED type not defined, set it
#ifndef OLED_TYPE
#define OLED_TYPE &SH1106_128x64
#endif

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
