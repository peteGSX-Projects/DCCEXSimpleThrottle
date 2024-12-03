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
  /// @brief Constructor for the rotary encoder object
  RotaryEncoder();

  /// @brief Not implemented for this device type
  void begin() override;

  /// @brief Check for any user selection actions
  /// This should be called at least once per main loop iteration
  /// Note that with a rotary encoder, clockwise is down but also increases speed, and counter clockwise is up but also
  /// decreases speed
  /// @return UserSelectionAction::[None|Up|UpFaster|UpFastest|Down|DownFaster|DownFastest]
  UserSelectionAction getUserSelectionAction() override;

private:
  Rotary *_rotary;
  unsigned long _throttleStepFasterThreshold;
  unsigned long _throttleStepFastestThreshold;
  unsigned long _lastUpThrottleStep;
  unsigned long _lastDownThrottleStep;
};

#endif // ROTARYENCODER_H
