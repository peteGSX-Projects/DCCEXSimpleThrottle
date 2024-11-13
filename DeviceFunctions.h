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

// OLD WAY Define number of EX-CommandStation entries, including WiFi details
// const int CS_SERVERS = 2;

// EXCommandStation *csServers = new EXCommandStation[CS_SERVERS]{
//     // {"Name", IPAddress(a, b, c, d), "Port", "WiFi SSID", "WiFi password"}, // This format
//     {"Testing CS", IPAddress(192, 168, 4, 1), 2560, "SSID1", "PASSWORD1"}, // First EX-CommandStation's details
//     {"Layout CS", IPAddress(192, 168, 0, 10), 2560, "SSID2", "PASSWORD2"}, // Second EX-CommandStation's details
// };

extern const uint8_t numberofCommandStations;
extern EXCommandStation *csServers;

void setupServerMenu();

void setupWiFi(int server);

/// @brief Validates and converts an IP address from the preprocessor macro string to an IPAddress object
/// @param ipAddressString Preprocessor macro IP address string COMMANDSTATION_IP
/// @return IPAddress object
IPAddress convertIP(const char *ipAddressString);
#endif
void setupExtrasMenu();

#endif
