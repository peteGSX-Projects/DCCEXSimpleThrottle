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

#include "ButtonInterface.h"
#include "avdweb_Switch.h"

/// @brief Class to manage user interaction with a button
class Button : public ButtonInterface {
public:
  /// @brief Constructor for this button object
  /// @param button Pointer to an existing switch object
  Button(Switch *button);

  /// @brief Start this button object
  void begin() override;

  /// @brief Monitor for button events
  /// @return None, SingleClick, DoubleClick, LongPress
  ButtonEvent getEvent() override;

private:
  Switch *_button;
};

#endif // BUTTON_H
