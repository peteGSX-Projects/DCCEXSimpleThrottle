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

#ifndef COMMANDSTATIONLISTENER_H
#define COMMANDSTATIONLISTENER_H

#include "Defines.h"
#include <DCCEXProtocol.h>

/// @brief Class to manage broadcasts and responses from the CommandStation
class CommandStationListener : public DCCEXProtocolDelegate {
public:
  /// @brief Consructor for the CommandStation listener
  CommandStationListener();

  /// @brief Respond to receiving the roster list which updates the roster menu
  void receivedRosterList() override;

  /// @brief Respond to receiving an update for a loco to update the throttle screen
  /// @param loco Pointer to the loco address the update is related to
  void receivedLocoUpdate(Loco *loco) override;

  /// @brief Respond to receiving a track power state broadcast to update the throttle screen
  /// @param powerState [PowerOff|PowerOn|PowerUnknown]
  void receivedTrackPower(TrackPower powerState) override;

  /// @brief Respond to receiving the loco address read from the programming track
  /// If valid (not -1), sets this as the loco controlled by the throttle
  /// @param address DCC address of the loco on the programming track, -1 if not read
  void receivedReadLoco(int address) override;

private:
};

#endif // COMMANDSTATIONLISTENER_H
