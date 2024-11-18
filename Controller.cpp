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

#include "Controller.h"

Controller::Controller(ButtonInterface *buttonInterface, DisplayInterface *displayInterface,
                       RotaryEncoderInterface *rotaryEncoderInterface, ScreenManager *screenManager)
    : _buttonInterface(buttonInterface), _displayInterface(displayInterface),
      _rotaryEncoderInterface(rotaryEncoderInterface), _screenManager(screenManager) {}

void Controller::begin() {
  _buttonInterface->begin();
  _displayInterface->begin();
  _rotaryEncoderInterface->begin();
}

void Controller::addScreen(ScreenInterface *screenInterface) {}

void Controller::update() {
  ScreenInterface *currentScreen = _screenManager->getCurrentScreen();
  ButtonEvent event = _buttonInterface->getEvent();
  currentScreen->handleButtonEvent(event);
  RotaryEncoderMovement movement = _rotaryEncoderInterface->getMovement();
  currentScreen->handleRotation(movement);
  currentScreen->update();
}
