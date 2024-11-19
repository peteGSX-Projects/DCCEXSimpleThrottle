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

#include "Defines.h"
#include "Rotary.h"
#include "UserSelectionInterface.h"

/// @brief Class to implement a physical rotary encoder for user selection activities
/// Clockwise moves down/increases speed, counter clockwise moves up/decreases speed
class RotaryEncoder : public UserSelectionInterface {
public:
  RotaryEncoder();

  void begin() override;

  UserSelectionAction getUserSelectionAction() override;

private:
  Rotary *_rotary;
};

#endif // ROTARYENCODER_H
