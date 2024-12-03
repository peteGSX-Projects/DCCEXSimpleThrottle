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

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "CommandStationDetails.h"
#include "CommandStationMenuItem.h"
#include "EventManager.h"
#include "SelectActionMenu.h"
#include "SelectCommandStationMenu.h"
#include "SelectLocoMenu.h"
#include <DCCEXProtocol.h>

class MenuManager {
public:
  /// @brief Constructor for the menu manager
  /// @param eventManager Pointer to the event manager
  MenuManager(EventManager *eventManager);

  /// @brief Get the Select Action menu
  /// @return Menu
  SelectActionMenu *getSelectActionMenu();

  /// @brief Get the Select Loco menu
  /// @return Menu
  SelectLocoMenu *getSelectLocoMenu();

  /// @brief Get the Select CommandStation menu
  /// @return Menu
  SelectCommandStationMenu *getSelectCommandStationMenu();

#ifdef WIFI_ENABLED
  /// @brief Add the list of CommandStations and WiFi networks to the server menu
  void setupCommandStationMenu(CommandStationDetails *commandStationList, uint8_t commandStationCount);
#endif // WIFI_ENABLED

  /// @brief Set up the loco menu based on the provided roster linked list and (if enabled) the local roster
  /// @param firstRosterLoco Pointer to the first loco in the roster
  void setupLocoMenu(Loco *firstRosterLoco);

private:
  EventManager *_eventManager;
  SelectActionMenu *_selectActionMenu;
  SelectLocoMenu *_selectLocoMenu;
  SelectCommandStationMenu *_selectCommandStationMenu;
};

#endif // MENUMANAGER_H
