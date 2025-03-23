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

#include "Button.h"
#include "Defines.h"

Button::Button() {
  _button = new Switch(BUTTON_PIN, BUTTON_PIN_MODE, BUTTON_PIN_POLARITY, BUTTON_DEBOUNCE_PERIOD,
                       BUTTON_LONG_PRESS_PERIOD, BUTTON_DOUBLE_CLICK_PERIOD, BUTTON_DEGLITCH_PERIOD);
}

void Button::begin() {}

UserConfirmationAction Button::getUserConfirmationAction() {
  if (!_button)
    return UserConfirmationAction::None;
  UserConfirmationAction action = UserConfirmationAction::None;
  _button->poll();
  if (_button->singleClick()) {
    CONSOLE.println("Single Click");
    action = UserConfirmationAction::SingleClick;
  } else if (_button->doubleClick()) {
    action = UserConfirmationAction::DoubleClick;
  } else if (_button->longPress()) {
    action = UserConfirmationAction::LongPress;
  }
  return action;
}
