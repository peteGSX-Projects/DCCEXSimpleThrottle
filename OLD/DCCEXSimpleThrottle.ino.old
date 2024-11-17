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
#include "Defines.h"
#include "DeviceFunctions.h"
#include "DisplayFunctions.h"
#include "EncoderFunctions.h"
#include <Arduino.h>

bool connected = false;     // flag for connection state
bool protocolSetup = false; // flag for setting up the DCCEXProtocol object

/// @brief Initial setup function
void setup() {
#if defined(ARDUINO_BLUEPILL_F103C8)
  disableJTAG();
#endif
  CONSOLE.begin(115200);
  setupDisplay();
  setupButton();
  setupExtrasMenu();
  displayStartupInfo();
#if defined(ARDUINO_BLUEPILL_F103C8) || defined(ARDUINO_BLACKPILL_F411CE)
  currentMenu = &rosterMenu;
  encoderMode = SELECT_LOCO;
  CLIENT.begin(115200);
  connected = true;
#elif defined(ARDUINO_ARCH_ESP32)
  setupServerMenu();
  currentMenu = &serverMenu;
  encoderMode = SELECT_SERVER;
  displayMenu();
#endif
}

/// @brief Main loop
void loop() {
  if (connected) {
    if (!protocolSetup) {
      dccexProtocol.setLogStream(&CONSOLE);
      dccexProtocol.setDelegate(&dccexCallbacks);
      dccexProtocol.connect(&CLIENT);
    }
    dccexProtocol.check();
    getRoster();
    displayRuntime();
  }
  processEncoder();
}
