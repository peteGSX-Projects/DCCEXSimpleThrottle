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

#ifndef USERSELECTIONINTERFACE_H
#define USERSELECTIONINTERFACE_H

/// @brief User selection action data types available
enum class UserSelectionAction { None, Up, UpFaster, UpFastest, Down, DownFaster, DownFastest };

/// @brief Interface class to abstract user selection actions from physical implementations
/// All physical user selection classes must extend this
/// This allows for the use of physical buttons, rotary encoders, touch screens, and other user interface methods that
/// can move menu selections up and down, and increase or decrease throttle speeds
/// Note if using a rotary encoder, if up is counter clockwise for menu selections, this will also be a decrease in
/// speed, and vice versa for down with clockwise and an increase in speed
class UserSelectionInterface {
public:
  /// @brief Implement this to perform any initial startup methods or activities
  virtual void begin() = 0;

  /// @brief Implement this to check for any user selection actions
  /// This should be called at least once per main loop iteration
  /// @return UserSelectionAction::[None|Up|UpFaster|UpFastest|Down|DownFaster|DownFastest]
  virtual UserSelectionAction getUserSelectionAction() = 0;

  /// @brief Destructor for the object
  virtual ~UserSelectionInterface() = default;

  /// @brief Check if throttle is inverted compared to up/down
  /// @return True if UserSelectionAction::Up decreases speed, and Down increases speed
  /// Particularly useful for rotary encoders vs. physical push buttons or touch screens
  bool throttleInverted() { return _throttleInverted; }

  /// @brief Call this method to ensure throttle is inverted compared to selection options
  void setThrottleInverted() { _throttleInverted = true; }

private:
  bool _throttleInverted = false;
};

#endif // USERSELECTIONINTERFACE_H
