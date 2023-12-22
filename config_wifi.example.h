// Example config_wifi.h file
// Copy this to config_wifi.h and update to suit

#ifndef CONFIG_WIFI_H
#define CONFIG_WIFI_H

#include "defines.h"

#if defined(ARDUINO_ARCH_ESP32)

// Define number of EX-CommandStation entries, including WiFi details
const int CS_SERVERS=2;

EXCommandStation* csServers=new EXCommandStation[CS_SERVERS]{
// {"Name", IPAddress(a, b, c, d), "Port", "WiFi SSID", "WiFi password"}, // This format
  {"Testing CS", IPAddress(192, 168, 4, 1), 2560, "SSID1", "PASSWORD1"},    // First EX-CommandStation's details
  {"Layout CS", IPAddress(192, 168, 0, 10), 2560, "SSID2", "PASSWORD2"},    // Second EX-CommandStation's details
};

#endif  // ESP32
#endif  // CONFIG_WIFI_H
