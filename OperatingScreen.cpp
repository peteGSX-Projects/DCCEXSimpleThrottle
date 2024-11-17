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

#include "OperatingScreen.h"

OperatingScreen::OperatingScreen() {}

void OperatingScreen::update() {}

void OperatingScreen::handleRotation(RotaryEncoderMovement movement) {
  switch (movement) {
  case RotaryEncoderMovement::Clockwise:
    break;
  case RotaryEncoderMovement::CounterClockwise:
    break;
  case RotaryEncoderMovement::None:
  default:
    break;
  }
}

void OperatingScreen::handleButtonEvent(ButtonEvent buttonEvent) {
  switch (buttonEvent) {
  case ButtonEvent::SingleClick:
    break;
  case ButtonEvent::DoubleClick:
    break;
  case ButtonEvent::LongPress:
    break;
  case ButtonEvent::None:
  default:
    break;
  }
}

void OperatingScreen::drawScreen(DisplayInterface *displayInterface) {}
