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

#ifndef PROGRESSSCREEN_H
#define PROGRESSSCREEN_H

#include "ScreenInterface.h"

class ProgressScreen : public ScreenInterface {
public:
  /// @brief Constructor for the progress screen
  ProgressScreen();

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

  /// @brief Set the current activity in progress
  /// @param activity Activity text to display
  void setActivity(const char *activity);

  /// @brief Set the current attempt in progress
  /// @param counter Current attempt count
  void setCounter(uint8_t counter);

private:
  const char *_activity;
  uint8_t _counter;
};

#endif // PROGRESSSCREEN_H
