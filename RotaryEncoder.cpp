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
  _throttleStepFasterThreshold = THROTTLE_STEP_FASTER_THRESHOLD;
  _throttleStepFastestThreshold = THROTTLE_STEP_FASTEST_THRESHOLD;
  _lastUpThrottleStep = 0;
  _lastDownThrottleStep = 0;
  setThrottleInverted();
}

void RotaryEncoder::begin() {}

UserSelectionAction RotaryEncoder::getUserSelectionAction() {
  if (!_rotary)
    return UserSelectionAction::None;
  UserSelectionAction action = UserSelectionAction::None;
  unsigned long currentMillis = millis();
  unsigned char result = _rotary->process();
  if (result == DIR_CW) {
    unsigned long timeDifference = currentMillis - _lastDownThrottleStep;
    if (timeDifference < _throttleStepFastestThreshold) {
      action = UserSelectionAction::DownFastest;
    } else if (timeDifference < _throttleStepFasterThreshold) {
      action = UserSelectionAction::DownFaster;
    } else {
      action = UserSelectionAction::Down;
    }
    _lastDownThrottleStep = currentMillis;
  } else if (result == DIR_CCW) {
    unsigned long timeDifference = currentMillis - _lastUpThrottleStep;
    if (timeDifference < _throttleStepFastestThreshold) {
      action = UserSelectionAction::UpFastest;
    } else if (timeDifference < _throttleStepFasterThreshold) {
      action = UserSelectionAction::UpFaster;
    } else {
      action = UserSelectionAction::Up;
    }
    _lastUpThrottleStep = currentMillis;
  }
  return action;
}
