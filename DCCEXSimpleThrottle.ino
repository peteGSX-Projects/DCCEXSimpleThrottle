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

#include "AppConfiguration.h"
#include "Defines.h"
#include "Version.h"
#include <Arduino.h>

AppConfiguration appConfig;

/// @brief Initial setup
void setup() {
  CONSOLE.begin(115200);
  CONSOLE.println("DCC-EX Simple Throttle");
  CONSOLE.print("Version: ");
  CONSOLE.println(VERSION);
  appConfig.initialise();
}

/// @brief Main loop
void loop() {
  AppOrchestrator *orchestrator = appConfig.getAppOrchestrator();
  orchestrator->update();
}
