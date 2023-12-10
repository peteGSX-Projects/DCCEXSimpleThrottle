// Example config_wifi.h file
// Copy this to config_wifi.h and update to suit

#ifndef CONFIG_WIFI_H
#define CONFIG_WIFI_H

#include "defines.h"

#if defined(ARDUINO_ARCH_ESP32)

// Define number of WiFi networks and EX-CommandStation entries
const int WIFI_NETWORKS=2;
const int CS_SERVERS=2;

WiFiNetwork* wifiNetworks=new WiFiNetwork[WIFI_NETWORKS]{
  {"EX-CommandStation", "SSID1", "PASSWORD1"},    // First WiFi network's details
  {"Home WiFi", "SSID2", "PASSWORD2"},            // Second WiFi network's details
};

EXCommandStation* csServers=new EXCommandStation[CS_SERVERS]{
  {"Testing CS", IPAddress(192, 168, 4, 1), 2560},    // First EX-CommandStation's details
  {"Layout CS", IPAddress(192, 168, 0, 10), 2560},    // Second EX-CommandStation's details
};

#endif  // ESP32
#endif  // CONFIG_WIFI_H
