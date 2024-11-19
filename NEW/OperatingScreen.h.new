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

#ifndef OPERATINGSCREEN_H
#define OPERATINGSCREEN_H

#include "ScreenInterface.h"

/// @brief Class to display the loco operating screen and respond to rotary encoder and button events
class OperatingScreen : public ScreenInterface {
public:
  /// @brief Constructor for the operating screen object
  OperatingScreen();

  /// @brief Check for rotary encoder movements and button events
  void update() override;

  /// @brief Method to handle rotary encoder movements
  /// @param movement
  void handleRotation(RotaryEncoderMovement movement) override;

  /// @brief Method to handle button events
  /// @param buttonEvent None, SingleClick, DoubleClick, LongPress
  void handleButtonEvent(ButtonEvent buttonEvent) override;

  /// @brief Method to draw the current screen on a display
  /// @param displayInterface Pointer to the display interface object
  void drawScreen(DisplayInterface *displayInterface) override;

private:
};

#endif // OPERATINGSCREEN_H
