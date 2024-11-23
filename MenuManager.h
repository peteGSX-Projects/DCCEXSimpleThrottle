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
#include "SelectActionMenu.h"
#include "SelectLocoMenu.h"
#include "SelectServerMenu.h"
#include "ServerMenuItem.h"

class MenuManager {
public:
  /// @brief Constructor for the menu manager
  MenuManager();

  /// @brief Get the Select Action menu
  /// @return Menu
  SelectActionMenu *getSelectActionMenu();

  /// @brief Get the Select Loco menu
  /// @return Menu
  SelectLocoMenu *getSelectLocoMenu();

  /// @brief Get the Select Server menu
  /// @return Menu
  SelectServerMenu *getSelectServerMenu();

#ifdef WIFI_ENABLED
  /// @brief Add the list of CommandStations and WiFi networks to the server menu
  void setupServerMenu(CommandStationDetails *commandStationList, uint8_t commandStationCount);
#endif // WIFI_ENABLED

private:
  SelectActionMenu *_selectActionMenu;
  SelectLocoMenu *_selectLocoMenu;
  SelectServerMenu *_selectServerMenu;
};

#endif // MENUMANAGER_H
