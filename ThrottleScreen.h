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

#ifndef THROTTLESCREEN_H
#define THROTTLESCREEN_H

#include "ScreenInterface.h"
#include <DCCEXProtocol.h>

class ThrottleScreen : public ScreenInterface {
public:
  /// @brief Constructor for the throttle screen, requires throttle step values
  /// @param dccexProtocolClient Pointer to the DCCEXProtocol client connection in use by the application
  /// @param throttleStep Normal throttle step change
  /// @param throttleStepFaster Faster throttle step change (eg. rotary encoder moves faster)
  /// @param throttleStepFastest Fastest throttle step change (eg. rotary encoder moves fastest)
  ThrottleScreen(DCCEXProtocol *dccexProtocolClient, uint8_t throttleStep, uint8_t throttleStepFaster,
                 uint8_t throttleStepFastest);

  /// @brief Implement this method to define what to do when user confirmation actions are performed
  /// @param action UserConfirmationAction::[None|SingleClick|DoubleClick|LongPress]
  void handleUserConfirmationAction(UserConfirmationAction action) override;

  /// @brief Implement this method to define what to do when user selection actions are performed
  /// @param action UserSelectionAction::[None|Up|UpFaster|UpFastest|Down|DownFaster|DownFastest]
  void handleUserSelectionAction(UserSelectionAction action, bool throttleInverted) override;

  /// @brief Implement this method to draw the associated screen object on the specified display
  /// @param display Pointer to the display object
  void drawScreen(DisplayInterface *display) override;

  /// @brief Set the loco currently being operated
  /// @param loco Pointer to the loco object
  void setLoco(Loco *loco);

  /// @brief Method to call when a loco update has been received
  /// @param loco Pointer to the loco that has been updated
  void locoUpdateReceived(Loco *loco);

  /// @brief Get the current speed
  /// @return Speed
  uint8_t getSpeed();

  /// @brief Method to call when a track power update has been received
  /// @param trackPower Track power state
  void trackPowerUpdateReceived(TrackPower trackPower);

private:
  uint8_t _speed;
  bool _speedChanged;
  Direction _direction;
  bool _directionChanged;
  Loco *_loco;
  TrackPower _trackPower;
  bool _trackPowerChanged;
  DCCEXProtocol *_dccexProtocolClient;
  uint8_t _throttleStep;
  uint8_t _throttleStepFaster;
  uint8_t _throttleStepFastest;
};

#endif // THROTTLESCREEN_H
