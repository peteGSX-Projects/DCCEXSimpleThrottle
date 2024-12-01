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

#ifndef ERRORSCREEN_H
#define ERRORSCREEN_H

#include "ScreenInterface.h"

class ErrorScreen : public ScreenInterface {
public:
  /// @brief Constructor for the error screen
  ErrorScreen();

  /// @brief Implement this method to define what to do when user confirmation actions are performed
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  void handleUserConfirmationAction(UserConfirmationAction action) override;

  /// @brief Implement this method to define what to do when user selection actions are performed
  /// throttleInverted enables an interface to decrease speed when moving up and vice versa, which is handy for a rotary
  /// encoder
  /// @param action UserSelectionAction::[None|Up|UpFaster|UpFastest|Down|DownFaster|DownFastest]
  /// @param throttleInverted True|False
  void handleUserSelectionAction(UserSelectionAction action, bool throttleInverted = false) override;

  /// @brief Implement this method to draw the associated screen object on the specified display
  /// @param display Pointer to the display object
  void drawScreen(DisplayInterface *display) override;

  /// @brief Set the error message to be displayed
  /// @param errorMessage Error message
  void setErrorMessage(const char *errorMessage);

private:
  const char *_errorMessage;
};

#endif // ERRORSCREEN_H
