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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ButtonInterface.h"
#include "DisplayInterface.h"
#include "RotaryEncoderInterface.h"
#include "ScreenManager.h"

class Controller {
public:
  /// @brief Constructor for the controller object
  /// @param buttonInterface Pointer to the existing button interface
  /// @param displayInterface Pointer to the existing display interface
  /// @param rotaryEncoderInterface Pointer to the existing rotary encoder interface
  Controller(ButtonInterface *buttonInterface, DisplayInterface *displayInterface,
             RotaryEncoderInterface *rotaryEncoderInterface);

  /// @brief Add a screen to the controller and screen manager
  /// @param screenInterface Pointer to the screen interface object
  void addScreen(ScreenInterface *screenInterface);

  /// @brief Check for rotary encoder movements and button events
  void update();

private:
  ButtonInterface *_buttonInterface;
  DisplayInterface *_displayInterface;
  RotaryEncoderInterface *_rotaryEncoderInterface;
  ScreenManager _screenManager;
};

#endif // CONTROLLER_H
