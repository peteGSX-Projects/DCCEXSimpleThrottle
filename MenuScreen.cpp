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

MenuScreen::MenuScreen(BaseMenu *menu) : _menu(menu) {}

void MenuScreen::update() {}

void MenuScreen::handleUserConfirmationAction(UserConfirmationAction action) {
  if (!_menu)
    return;
  _menu->handleUserConfirmationAction(action);
}

void MenuScreen::handleUserSelectionAction(UserSelectionAction action, bool throttleInverted) {
  if (!_menu)
    return;
  _menu->handleUserSelectionAction(action);
}

void MenuScreen::drawScreen(DisplayInterface *display) {
  if (!_menu)
    return;
  if (!display->needsRedraw())
    return;
  _menu->displayMenu(display);
}
