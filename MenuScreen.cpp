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

#include "MenuScreen.h"

MenuScreen::MenuScreen(Menu *initialMenu) : _currentMenu(initialMenu) {}

void MenuScreen::setMenu(Menu *menu) { _currentMenu = menu; }

void MenuScreen::update() {}

void MenuScreen::handleRotation(RotaryEncoderMovement movement) {
  switch (movement) {
  case RotaryEncoderMovement::Clockwise:
    CONSOLE.println("Move clockwise");
    break;
  case RotaryEncoderMovement::CounterClockwise:
    CONSOLE.println("Move counter clockwise");
    break;
  case RotaryEncoderMovement::None:
  default:
    break;
  }
}

void MenuScreen::handleButtonEvent(ButtonEvent buttonEvent) {
  switch (buttonEvent) {
  case ButtonEvent::SingleClick:
    CONSOLE.println("Single click");
    break;
  case ButtonEvent::DoubleClick:
    CONSOLE.println("Double click");
    break;
  case ButtonEvent::LongPress:
    CONSOLE.println("Long press");
    break;
  case ButtonEvent::None:
  default:
    break;
  }
}

void MenuScreen::drawScreen(DisplayInterface *displayInterface) {}