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

#include "SelectServerMenu.h"

SelectServerMenu::SelectServerMenu(const char *name, EventManager *eventManager) {
  setMenuName(name);
  setEventManager(eventManager);
}

void SelectServerMenu::handleUserConfirmationAction(UserConfirmationAction action) {
  switch (action) {
  case UserConfirmationAction::SingleClick: {
    BaseMenuItem *selectedItem = getMenuItemAtIndex(getSelectedItemIndex());
    _initiateServerConnection(selectedItem);
    break;
  }
  default:
    break;
  }
}

void SelectServerMenu::_initiateServerConnection(BaseMenuItem *item) {
  ServerMenuItem *serverItem = static_cast<ServerMenuItem *>(item);
  uint8_t index = serverItem->getIndex();
  EventManager *eventManager = getEventManager();
  EventData eventData(index);
  if (eventManager) {
    eventManager->triggerEvent("SelectedCommandStation", eventData);
  }
}
