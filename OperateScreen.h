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

#ifndef OPERATESCREEN_H
#define OPERATESCREEN_H

#include "ScreenInterface.h"

class OperateScreen : public ScreenInterface {
public:
  /// @brief Constructor for the operation screen
  OperateScreen();

  /// @brief Implement this method at least once per main loop iteraction to check for user selection and confirmation
  /// actions, and to ensure displays are updated
  void update();

  /// @brief Implement this method to define what to do when user confirmation actions are performed
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  void handleUserConfirmationAction(UserConfirmationAction action);

  /// @brief Implement this method to define what to do when user selection actions are performed
  /// @param action UserSelectionAction::[None|Up|Down]
  void handleUserSelectionAction(UserSelectionAction action);

  /// @brief Implement this method to draw the associated screen object on the specified display
  /// @param display Pointer to the display object
  void drawScreen(DisplayInterface *display);

private:
};

#endif // OPERATESCREEN_H
