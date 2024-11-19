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

#ifndef ROTARYENCODERINTERFACE_H
#define ROTARYENCODERINTERFACE_H

enum class RotaryEncoderMovement { None, Clockwise, CounterClockwise };

/// @brief Interface class to abstract retrieving physical rotary encoder movements for user interaction
class RotaryEncoderInterface {
public:
  /// @brief Start this interface
  virtual void begin() = 0;

  /// @brief Get the current rotary encoder movement
  /// @return RotaryEncoderMovement enum
  virtual RotaryEncoderMovement getMovement() = 0;

  /// @brief Destructor for this RotaryEncoderInterface object
  virtual ~RotaryEncoderInterface() = default;
};

#endif // ROTARYENCODERINTERFACE_H
