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

#ifndef USERCONFIRMATIONINTERFACE_H
#define USERCONFIRMATIONINTERFACE_H

/// @brief User confirmation action data types available
enum class UserConfirmationAction { None, SingleClick, DoubleClick, LongPress };

/// @brief Interface class to abstract user confirmation actions from physical implementations
/// All physical user confirmation classes must extend this
/// This allows the use of the button on a rotary encoder, other buttons, touch screens, and other user interface
/// methods that can trigger single click, double click, or long press type actions
class UserConfirmationInterface {
public:
  /// @brief Implement this to perform any initial startup methods or activities
  virtual void begin() = 0;

  /// @brief Implement this to check for any user confirmation actions
  /// This should be called at least once per main loop iteration
  /// @return UserSelectionConfirmation::[None|SingleClick|DoubleClick|LongPress]
  virtual UserConfirmationAction getUserConfirmationAction() = 0;

  /// @brief Destructor for the object
  virtual ~UserConfirmationInterface() = default;
};

#endif // USERCONFIRMATIONINTERFACE_H
