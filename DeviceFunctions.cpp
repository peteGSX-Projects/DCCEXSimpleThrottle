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

#include <Arduino.h>
#include "DeviceFunctions.h"

// Disabling JTAG is required to avoid pin conflicts on Bluepill
#if defined(ARDUINO_BLUEPILL_F103C8)
void disableJTAG() {
  // Disable JTAG and enable SWD by clearing the SWJ_CFG bits
  // Assuming the register is named AFIO_MAPR or AFIO_MAPR2
  AFIO->MAPR &= ~(AFIO_MAPR_SWJ_CFG);
  // or
  // AFIO->MAPR2 &= ~(AFIO_MAPR2_SWJ_CFG);
}
#endif

#if defined(ARDUINO_ARCH_ESP32)

// If we haven't got a custom config_wifi.h, use the example
#if __has_include ( "config_wifi.h")
  #include "config_wifi.h"
#else
  #warning config_wifi.h not found. Using defaults from config_wifi.example.h
  #include "config_wifi.example.h"
#endif

WiFiClient wifiClient;

void setupWiFi() {
  // Connect to WiFi network
  CONSOLE.print("Connecting to WiFi network ");
  CONSOLE.println(wifiNetworks[0].label);
  WiFi.begin(wifiNetworks[0].ssid, wifiNetworks[0].password);
  while(WiFi.status()!=WL_CONNECTED) delay(1000);
  CONSOLE.print("Connected with IP: ");
  CONSOLE.println(WiFi.localIP());

  // Connect to the server
  CONSOLE.print("Connecting to server ");
  CONSOLE.println(csServers[0].label);
  if (!CLIENT.connect(csServers[0].ipaddress, csServers[0].port)) {
    CONSOLE.println("connection failed");
    while(true) delay(1000);
  }
  CONSOLE.println("Connected to the server");
}
#endif
