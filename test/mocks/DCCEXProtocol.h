/*
 *  © 2024 Peter Cole
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

#ifndef DCCEXPROTOCOL_H
#define DCCEXPROTOCOL_H

/// @brief Mock DCCEXProtocol class to satisfy code dependencies

/// @brief Loco direction
enum Direction {
  Reverse = 0,
  Forward = 1,
};

/// @brief Loco source
enum LocoSource {
  LocoSourceRoster = 0,
  LocoSourceEntry = 1,
};

/// @brief Consist loco facing
enum Facing {
  FacingForward = 0,
  FacingReversed = 1,
};

/// @brief Track power states
enum TrackPower {
  PowerOff = 0,
  PowerOn = 1,
  PowerUnknown = 2,
};

// Valid TrackManager types
enum TrackManagerMode {
  MAIN, // Normal DCC track mode
  PROG, // Programming DCC track mode
  DC,   // DC mode
  DCX,  // Reverse polarity DC mode
  NONE, // Track is unused
};

/// @brief Route types
enum RouteType {
  RouteTypeRoute = 'R',
  RouteTypeAutomation = 'A',
};

/// @brief Turntable types
enum TurntableType {
  TurntableTypeDCC = 0,
  TurntableTypeEXTT = 1,
  TurntableTypeUnknown = 9,
};

class Loco {};

class DCCEXProtocol {};

#endif // DCCEXPROTOCOL_H
