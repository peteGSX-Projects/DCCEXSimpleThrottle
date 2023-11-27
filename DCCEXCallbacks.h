#ifndef DCCEXCALLBACKS_H
#define DCCEXCALLBACKS_H

#include <Arduino.h>
#include <DCCEXProtocol.h>
#include "defines.h"

class DCCEXCallbacks : public DCCEXProtocolDelegate {
public:
  void receivedServerVersion(int major, int minor, int patch);
  // void receivedSpeed(int throttleNo, int speed);
  // void receivedDirection(int throttleNo, Direction dir);
  // void receivedTrackPower(TrackPower state);
  // void receivedReadLoco(int address);

};

#endif
