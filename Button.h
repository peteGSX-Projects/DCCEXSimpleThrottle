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

#ifndef BUTTON_H
#define BUTTON_H

#include "UserConfirmationInterface.h"
#include "avdweb_Switch.h"

class Button : public UserConfirmationInterface {
public:
  /// @brief Constructor for the button object
  Button();

  /// @brief
  void begin() override;

  /// @brief Check for any user confirmation actions
  /// This should be called at least once per main loop iteration
  /// @return UserSelectionConfirmation::[None|SingleClick|DoubleClick|LongPress]
  UserConfirmationAction getUserConfirmationAction();

private:
  Switch *_button;
};

#endif // BUTTON_H
