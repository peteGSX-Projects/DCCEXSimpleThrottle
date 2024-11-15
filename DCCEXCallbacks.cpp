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

#include "DCCEXCallbacks.h"
#include "Defines.h"
#include <Arduino.h>

void DCCEXCallbacks::receivedServerVersion(int major, int minor, int patch) {
  CONSOLE.print(F("Received version: "));
  CONSOLE.print(major);
  CONSOLE.print(F("."));
  CONSOLE.print(minor);
  CONSOLE.print(F("."));
  CONSOLE.print(patch);
}

void DCCEXCallbacks::receivedLocoUpdate(Loco *loco) {
  if (selectedLoco != loco || menuDisplay)
    return;
  speedChanged = true;
  directionChanged = true;
}

void DCCEXCallbacks::receivedTrackPower(TrackPower state) {
  if (trackPower != state) {
    trackPower = state;
    trackPowerChanged = true;
  }
}

void DCCEXCallbacks::receivedReadLoco(int address) {
  Serial.print("Loco address read from prog track is: ");
  Serial.println(address);
}
