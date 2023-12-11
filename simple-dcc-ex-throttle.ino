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
#include "defines.h"
#include "DisplayFunctions.h"
#include "EncoderFunctions.h"
#include "DCCEXFunctions.h"
#include "DeviceFunctions.h"

bool connected=false;

void setup() {
#if defined(ARDUINO_BLUEPILL_F103C8)
  disableJTAG();
#endif
  CONSOLE.begin(115200);
  setupDisplay();
  setupButton();
  displayStartupInfo();
#if defined(ARDUINO_BLUEPILL_F103C8) || defined(ARDUINO_BLACKPILL_F411CE)
  CLIENT.begin(115200);
  connected=true;
#elif defined(ARDUINO_ARCH_ESP32)
  setupWiFi();
#endif
  if (connected) {
    dccexProtocol.setLogStream(&CONSOLE);
    dccexProtocol.setDelegate(&dccexCallbacks);
    dccexProtocol.connect(&CLIENT);
  }
}

void loop() {
  if (connected) {
    dccexProtocol.check();
    getRoster();
    displayRuntime();
    processEncoder();
  }
}
