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

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "Rotary.h"
#include "RotaryEncoderInterface.h"

/// @brief Class to manage user interaction with a rotary encoder
class RotaryEncoder : public RotaryEncoderInterface {
public:
  /// @brief Constructor for this rotary encoder object
  /// @param rotaryEncoder Pointer to an existing Rotary object
  RotaryEncoder(Rotary *rotaryEncoder);

  /// @brief Start this rotary encoder
  void begin() override;

  /// @brief Monitor for movements of the rotary encoder
  /// @return None, Clockwise, CounterClockwise
  RotaryEncoderMovement getMovement() override;

private:
  Rotary *_rotaryEncoder;
};

#endif // ROTARYENCODER_H
