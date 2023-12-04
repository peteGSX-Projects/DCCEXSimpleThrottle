// Example config_wifi.h file
// Copy this to config_wifi.h and update to suit

#ifndef CONFIG_WIFI_H
#define CONFIG_WIFI_H

// Do not remove these lines
// Struct for WiFi and CS connection details (ESP32 only)
#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
struct WiFiNetwork {
  const char* SSID;
  const char* PASSWORD;
};

struct EXCommandStation {
  IPAddress ipaddress;
  int port;
};

// WiFi configuration (ESP32 only)
const int NETWORKS=2;
const int SERVERS=2;

WiFiNetwork wifiNetworks[NETWORKS]={
  
};

EXCommandStation servers[SERVERS]={

};

#endif  // ESP32
#endif  // CONFIG_WIFI_H
