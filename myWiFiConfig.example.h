// Example myWiFiConfig.h file
// Copy this to myWiFiConfig.h and update to suit

#ifndef MYWIFICONFIG_H
#define MYWIFICONFIG_H

#include "defines.h"

#if defined(ARDUINO_ARCH_ESP32)

// Define number of EX-CommandStation entries, including WiFi details
const int CS_SERVERS = 2;

EXCommandStation *csServers = new EXCommandStation[CS_SERVERS]{
    // {"Name", IPAddress(a, b, c, d), "Port", "WiFi SSID", "WiFi password"}, // This format
    {"Testing CS", IPAddress(192, 168, 4, 1), 2560, "SSID1", "PASSWORD1"}, // First EX-CommandStation's details
    {"Layout CS", IPAddress(192, 168, 0, 10), 2560, "SSID2", "PASSWORD2"}, // Second EX-CommandStation's details
};

#endif // ESP32
#endif // MYWIFICONFIG_H
