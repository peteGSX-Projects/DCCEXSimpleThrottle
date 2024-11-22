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

#ifndef STARTUPSCREEN_H
#define STARTUPSCREEN_H

#include "ScreenInterface.h"

/// @brief Class to display startup information on screen and respond to user interactions
/// Displays the DCC-EX Simple Throttle header and the current software version
/// No user actions are implemented on this screen as it is static content
class StartupScreen : public ScreenInterface {
public:
  /// @brief Constructor for the object
  StartupScreen();

  /// @brief Update method is irrelevant in this context as content is static
  void update() override;

  /// @brief Respond to user confirmation actions
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  void handleUserConfirmationAction(UserConfirmationAction action) override;

  /// @brief Respond to user selection actions
  /// @param action UserSelectionAction::[None|Up|Down]
  void handleUserSelectionAction(UserSelectionAction action, bool throttleInverted) override;

  /// @brief Draw this screen on the specified display
  /// @param display Pointer to a display object
  void drawScreen(DisplayInterface *display) override;
};

#endif // STARTUPSCREEN_H
