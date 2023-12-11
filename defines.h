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

#include <Arduino.h>

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

// Define console and client based on device type
#if defined(ARDUINO_BLUEPILL_F103C8) || defined(ARDUINO_BLACKPILL_F411CE)
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

struct WiFiNetwork {
  const char* label;
  const char* ssid;
  const char* password;
};

struct EXCommandStation {
  const char* label;
  IPAddress ipaddress;
  int port;
};

extern WiFiNetwork* wifiNetworks;
extern EXCommandStation* csServers;
extern const int WIFI_NETWORKS;
extern const int CS_SERVERS;
#endif

extern bool connected;

#endif
