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
#include "SelectLocoMenu.h"

SelectLocoMenu::SelectLocoMenu(const char *name) {
  setMenuName(name);
}

void SelectLocoMenu::handleUserConfirmationAction(UserConfirmationAction action) {
  switch (action) {
  case UserConfirmationAction::SingleClick: {
    uint8_t locoIndex = getSelectedItemIndex();
    _selectLoco(locoIndex);
    break;
  }
  case UserConfirmationAction::LongPress: {
    CONSOLE.println("NOT IMPLEMENTED: trigger read loco address from PROG track");
    break;
  }
  default:
    break;
  }
}

void SelectLocoMenu::_selectLoco(uint8_t locoIndex) {
  LocoMenuItem *locoItem = static_cast<LocoMenuItem *>(getMenuItemAtIndex(locoIndex));
  Loco *loco = locoItem->getLoco();
  // EventManager *eventManager = getEventManager();
  // if (eventManager) {
  //   EventData EventData(loco);
  //   eventManager->triggerEvent("SelectedLoco", EventData);
  // }
}
