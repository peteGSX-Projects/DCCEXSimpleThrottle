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

#include "LocoMenuItem.h"
#include "MenuManager.h"

MenuManager::MenuManager(EventManager *eventManager) : _eventManager(eventManager) {
  _selectActionMenu = new SelectActionMenu("Select action", _eventManager);
  _selectLocoMenu = new SelectLocoMenu("Select loco", _eventManager);
  _selectServerMenu = new SelectServerMenu("Select server", _eventManager);
}

SelectActionMenu *MenuManager::getSelectActionMenu() { return _selectActionMenu; }

SelectLocoMenu *MenuManager::getSelectLocoMenu() { return _selectLocoMenu; }

SelectServerMenu *MenuManager::getSelectServerMenu() { return _selectServerMenu; }

#ifdef WIFI_ENABLED
void MenuManager::setupServerMenu(CommandStationDetails *commandStationList, uint8_t commandStationCount) {
  if (!_selectServerMenu)
    return;
  for (uint8_t i = 0; i < commandStationCount; i++) {
    ServerMenuItem *item = new ServerMenuItem(commandStationList[i].name, i);
    _selectServerMenu->addItem(item);
  }
}
#endif // WIFI_ENABLED

void MenuManager::setupLocoMenu(Loco *firstRosterLoco) {
  if (!firstRosterLoco)
    return;
  for (Loco *rosterLoco = firstRosterLoco; rosterLoco; rosterLoco = rosterLoco->getNext()) {
    _selectLocoMenu->addItem(new LocoMenuItem(rosterLoco));
  }
  // Need to ensure orchestrator knows it has been updated here
}
