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

#include "MenuManager.h"

MenuManager::MenuManager() {
  _selectActionMenu = new SelectActionMenu("Select action");
  _selectLocoMenu = new SelectLocoMenu("Select loco");
  _selectServerMenu = new SelectServerMenu("Select server");
}

SelectActionMenu *MenuManager::getSelectActionMenu() { return _selectActionMenu; }

SelectLocoMenu *MenuManager::getSelectLocoMenu() { return _selectLocoMenu; }

SelectServerMenu *MenuManager::getSelectServerMenu() { return _selectServerMenu; }

#ifdef WIFI_ENABLED
void MenuManager::setupServerMenu(CommandStationDetails *commandStationList, uint8_t commandStationCount) {
  if (!_selectServerMenu)
    return;
  for (uint8_t i = 0; i < commandStationCount; i++) {
    ServerMenuItem *item = new ServerMenuItem(commandStationList[i]);
    _selectServerMenu->addItem(item);
  }
}
#endif // WIFI_ENABLED
