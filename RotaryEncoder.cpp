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

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder() {
  _rotary = new Rotary(ENCODER_DT_PIN, ENCODER_CLK_PIN);
  setThrottleInverted();
}

void RotaryEncoder::begin() {}

UserSelectionAction RotaryEncoder::getUserSelectionAction() {
  if (!_rotary)
    return UserSelectionAction::None;
  UserSelectionAction action = UserSelectionAction::None;
  unsigned char result = _rotary->process();
  if (result == DIR_CW) {
    action = UserSelectionAction::Down;
  } else if (result == DIR_CCW) {
    action = UserSelectionAction::Up;
  }
  return action;
}
