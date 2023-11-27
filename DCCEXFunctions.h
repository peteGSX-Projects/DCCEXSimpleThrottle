#ifndef DCCEXFUNCTIONS_H
#define DCCEXFUNCTIONS_H

#include <Arduino.h>
#include <DCCEXProtocol.h>
#include "defines.h"
#include "DCCEXCallbacks.h"
#include "DisplayFunctions.h"
#include "EncoderFunctions.h"

extern DCCEXProtocol dccexProtocol;
extern DCCEXCallbacks dccexCallbacks;

void getRoster();

#endif
