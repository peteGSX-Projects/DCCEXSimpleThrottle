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

#ifndef SELECTLOCOMENU_H
#define SELECTLOCOMENU_H

#include "BaseMenu.h"

class SelectLocoMenu : public BaseMenu {
public:
  /// @brief Constructor for each menu
  /// @param name Pointer to the char array containing the name of the menu
  /// @param eventManager Pointer to the event manager used by the application
  SelectLocoMenu(const char *name, EventManager *eventManager);

  /// @brief Implement this method to respond to user confirmation actions
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  void handleUserConfirmationAction(UserConfirmationAction action) override;

private:
  /// @brief Trigger an event that sets the currently selected Loco and switches to the Throttle screen
  /// @param locoIndex Index of the currently selected Loco entry
  void _selectLoco(uint8_t locoIndex);
};

#endif // SELECTLOCOMENU_H
