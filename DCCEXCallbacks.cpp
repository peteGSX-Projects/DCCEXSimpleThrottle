#include <Arduino.h>
#include "DCCEXCallbacks.h"

void DCCEXCallbacks::receivedServerVersion(int major, int minor, int patch) {
  CONSOLE.print(F("Received version: "));
  CONSOLE.print(major);
  CONSOLE.print(F("."));
  CONSOLE.print(minor);
  CONSOLE.print(F("."));
  CONSOLE.print(patch);
}

// void DCCEXCallbacks::receivedSpeed(int throttleNo, int speed) {

// }

// void receivedDirection(int throttleNo, Direction dir) {

// }

// void receivedTrackPower(TrackPower state) {

// }

// void receivedReadLoco(int address) {

// }
