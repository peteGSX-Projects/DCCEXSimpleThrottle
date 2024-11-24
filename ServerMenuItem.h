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

#ifndef SERVERMENUITEM_H
#define SERVERMENUITEM_H

#include "BaseMenuItem.h"
#include "CommandStationDetails.h"

class ServerMenuItem : public BaseMenuItem {
public:
#ifdef WIFI_ENABLED
  /// @brief Constructor for this menu item object
  /// @param name Pointer to the char array containing the name of this CommandStation
  /// @param commandStationIndex The index of this CommandStation entry in the list of CommandStations
  ServerMenuItem(const char *name, uint8_t commandStationIndex);

private:
  uint8_t _commandStationIndex;
#endif // WIFI_ENABLED
};

#endif // SERVERMENUITEM_H
