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

#ifndef DEVICEFUNCTIONS_H
#define DEVICEFUNCTIONS_H

#include "Defines.h"
#include "DisplayFunctions.h"
#include <Arduino.h>

// Disabling JTAG is required to avoid pin conflicts on Bluepill
#if defined(ARDUINO_BLUEPILL_F103C8)
void disableJTAG();
#endif

#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>

extern const uint8_t numberofCommandStations; // Number of user defined CommandStations
extern EXCommandStation *csServers;           // Pointer to the array of user defined CommandStations

/// @brief Function to setup the menu of user defined CommandStations
void setupServerMenu();

/// @brief Function to connect to WiFi and the CommandStation once the user has selected one
/// @param server Index of the CommandStation array containing connection details
void setupWiFi(int server);

/// @brief Validates and converts an IP address from the preprocessor macro string to an IPAddress object
/// @param ipAddressString Preprocessor macro IP address string COMMANDSTATION_IP
/// @return IPAddress object
IPAddress convertIP(const char *ipAddressString);
#endif

/// @brief Setup items for the menu accessible via double clicking
void setupExtrasMenu();

#endif
