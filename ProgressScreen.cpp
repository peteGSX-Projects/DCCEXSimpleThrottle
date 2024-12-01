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

#include "ProgressScreen.h"

ProgressScreen::ProgressScreen() {
  _activity = nullptr;
  _counter = 0;
}

void ProgressScreen::handleUserConfirmationAction(UserConfirmationAction action) {}

void ProgressScreen::handleUserSelectionAction(UserSelectionAction action, bool throttleInverted) {}

void ProgressScreen::drawScreen(DisplayInterface *display) { display->displayProgressScreen(_activity, _counter); }

void ProgressScreen::setActivity(const char *activity) { _activity = activity; }

void ProgressScreen::setCounter(uint8_t counter) { _counter = counter; }
