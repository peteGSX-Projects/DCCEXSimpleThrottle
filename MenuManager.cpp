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
  // Disable action menu for now, available for future use
  // _selectActionMenu = new SelectActionMenu("Select action", _eventManager);
  _selectLocoMenu = new SelectLocoMenu("Select loco", _eventManager);
  _selectCommandStationMenu = new SelectCommandStationMenu("Select CommandStation", _eventManager);
}

SelectActionMenu *MenuManager::getSelectActionMenu() { return _selectActionMenu; }

SelectLocoMenu *MenuManager::getSelectLocoMenu() { return _selectLocoMenu; }

SelectCommandStationMenu *MenuManager::getSelectCommandStationMenu() { return _selectCommandStationMenu; }

#ifdef WIFI_ENABLED
void MenuManager::setupCommandStationMenu(CommandStationDetails *commandStationList, uint8_t commandStationCount) {
  if (!_selectCommandStationMenu)
    return;
  for (uint8_t i = 0; i < commandStationCount; i++) {
    CommandStationMenuItem *item = new CommandStationMenuItem(commandStationList[i].name, i);
    _selectCommandStationMenu->addItem(item);
  }
}
#endif // WIFI_ENABLED

void MenuManager::setupLocoMenu(Loco *firstRosterLoco) {
  if (!firstRosterLoco)
    return;
  for (Loco *rosterLoco = firstRosterLoco; rosterLoco; rosterLoco = rosterLoco->getNext()) {
    LocoMenuItem *locoItem = new LocoMenuItem(rosterLoco);
    _selectLocoMenu->addItem(locoItem);
  }
#if defined(LOCAL_ROSTER_COUNT)
  const uint8_t localRosterCount = LOCAL_ROSTER_COUNT;
  const char *rosterNames[] = LOCAL_ROSTER_NAMES;       // array to store names of local roster entries
  const int rosterAddresses[] = LOCAL_ROSTER_ADDRESSES; // array to store addresses of local roster entries
  for (uint8_t i = 0; i < localRosterCount; i++) {
    Loco *localLoco = new Loco(rosterAddresses[i], LocoSource::LocoSourceEntry);
    char tempName[strlen(rosterNames[i]) + 3];
    snprintf(tempName, sizeof(tempName), "* %s", rosterNames[i]);
    char *locoName = strdup(tempName);
    localLoco->setName(locoName);
    LocoMenuItem *locoItem = new LocoMenuItem(localLoco);
    _selectLocoMenu->addItem(locoItem);
  }
#endif // LOCAL_ROSTER_COUNT
}
