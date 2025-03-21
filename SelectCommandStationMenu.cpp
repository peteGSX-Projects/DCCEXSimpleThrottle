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

#include "SelectCommandStationMenu.h"

SelectCommandStationMenu::SelectCommandStationMenu(const char *name, EventManager *eventManager) {
  setMenuName(name);
  setEventManager(eventManager);
}

void SelectCommandStationMenu::handleUserConfirmationAction(UserConfirmationAction action) {
  switch (action) {
  case UserConfirmationAction::SingleClick: {
    uint8_t serverIndex = getSelectedItemIndex();
    _initiateCommandStationConnection(serverIndex);
    break;
  }
  default:
    break;
  }
}

void SelectCommandStationMenu::_initiateCommandStationConnection(uint8_t serverIndex) {
  EventManager *eventManager = getEventManager();
  if (eventManager) {
    EventData eventData(serverIndex);
    eventManager->publish(EventType::CommandStationSelected, eventData);
  }
}
