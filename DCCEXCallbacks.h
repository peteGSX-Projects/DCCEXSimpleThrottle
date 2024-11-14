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

#ifndef DCCEXCALLBACKS_H
#define DCCEXCALLBACKS_H

#include "EncoderFunctions.h"
#include <Arduino.h>
#include <DCCEXProtocol.h>

/// @brief Class to manage callbacks from broadcasts and responses
class DCCEXCallbacks : public DCCEXProtocolDelegate {
public:
  /// @brief Callback method to respond to server version broadcasts
  /// @param major Major version number: X.y.z
  /// @param minor Minor version number: x.Y.z
  /// @param patch Patch version number: x.y.Z
  void receivedServerVersion(int major, int minor, int patch);

  /// @brief Callback method to respond to loco broadcasts
  /// @param loco Pointer to the loco object being updated
  void receivedLocoUpdate(Loco *loco);

  /// @brief Callback method to respond to track power broadcasts
  /// @param state TrackPower enum
  void receivedTrackPower(TrackPower state);

  /// @brief Callback method to respond to reading a loco from the prog track
  /// @param address DCC address read from the prog track
  void receivedReadLoco(int address);
};

#endif
