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

#include "DCCEXFunctions.h"
#include "DeviceFunctions.h"
#include "EncoderFunctions.h"
#include <Arduino.h>

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

const char *csNames[] = COMMANDSTATION_NAMES;         // array to store names of CommandStations
const char *csIPs[] = COMMANDSTATION_IPS;             // array to store IPs of CommandStations
const uint16_t csPorts[] = COMMANDSTATION_PORTS;      // array to store ports of CommandStations
const char *csSSIDs[] = COMMANDSTATION_SSIDS;         // array to store SSIDs of CommandStations
const char *csPasswords[] = COMMANDSTATION_PASSWORDS; // array to store passwords of CommandStations

const uint8_t numberOfCommandStations = COMMANDSTATION_COUNT;
EXCommandStation *csServers = new EXCommandStation[COMMANDSTATION_COUNT];
WiFiClient wifiClient;

/// @brief Initialise the array of user defined CommandStations from myConfig.h
void initialiseCSArray() {
  for (int i = 0; i < numberOfCommandStations; i++) {
    csServers[i].name = csNames[i];
    csServers[i].ipAddress = convertIP(csIPs[i]);
    csServers[i].port = csPorts[i];
    csServers[i].ssid = csSSIDs[i];
    csServers[i].password = csPasswords[i];
  }
}

void setupServerMenu() {
  initialiseCSArray();
  if (csServers) {
    for (int i = 0; i < numberOfCommandStations; i++) {
      serverMenu.addItem(new MenuItem(csServers[i].name));
    }
  }
}

void setupWiFi(int server) {
  // Connect to WiFi network
  int retries = CONNECT_RETRIES;
  oled.clear();
  oled.setFont(DEFAULT_FONT);
  oled.setCursor(0, 10);
  oled.print(F("Connecting to WiFi network: "));
  oled.setCursor(0, 20);
  oled.print(csServers[server].name);
  oled.setFont(WIFI_FONT);
  int X = 0;
  int Y = 30;
  oled.sendBuffer();
  CONSOLE.print("Connecting to WiFi network ");
  CONSOLE.println(csServers[server].name);
  CONSOLE.print("SSID|PASSWORD: ");
  CONSOLE.print(csServers[server].ssid);
  CONSOLE.print("|");
  CONSOLE.println(csServers[server].password);
  WiFi.begin(csServers[server].ssid, csServers[server].password);
  while (WiFi.status() != WL_CONNECTED && retries > 0) {
    oled.drawGlyph(X, Y, 0x0048);
    X += 9;
    if (X > 125) {
      X = 0;
      Y += 9;
    }
    oled.sendBuffer();
    retries--;
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED) {
    displayError("Failed WiFi connection");
  } else {
    CONSOLE.print("Connected with IP: ");
    CONSOLE.println(WiFi.localIP());

    // Connect to the server
    oled.clear();
    oled.setFont(DEFAULT_FONT);
    oled.setCursor(0, 10);
    oled.print(F("Connecting to server: "));
    oled.setCursor(0, 20);
    oled.print(csServers[server].name);
    oled.sendBuffer();
    oled.setCursor(0, 30);
    CONSOLE.print("Connecting to server ");
    CONSOLE.println(csServers[server].name);
    retries = CONNECT_RETRIES;
    while (!CLIENT.connect(csServers[server].ipAddress, csServers[server].port) && retries > 0) {
      oled.print(F("#"));
      oled.sendBuffer();
      retries--;
      delay(500);
    }
    if (retries == 0) {
      displayError("Failed server connection");
    } else {
      CONSOLE.println("Connected to the server");
      connected = true;
    }
  }
}

IPAddress convertIP(const char *ipAddressString) {
  int first;
  int second;
  int third;
  int fourth;
  if (sscanf(ipAddressString, "%d.%d.%d.%d", &first, &second, &third, &fourth) == 4) {
    if ((first >= 0 && first <= 255) && (second >= 0 && second <= 255) && (third >= 0 && third <= 255) &&
        (fourth >= 0 && fourth <= 255)) {
      return IPAddress(first, second, third, fourth);
    } else {
      CONSOLE.println("IP address is out of range");
    }
  } else {
    CONSOLE.println("Invalid IP address format");
  }
  return IPAddress(0, 0, 0, 0);
}
#endif

void setupExtrasMenu() {
  extrasMenu.addItem(new ActionMenuItem("Toggle track power", togglePower));
  extrasMenu.addItem(new ActionMenuItem("Forget loco/consist", forgetLoco));
}
