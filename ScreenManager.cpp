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

#include "ScreenManager.h"

ScreenInterface *ScreenManager::_first = nullptr;

ScreenManager::ScreenManager() {
  _next = nullptr;
  _currentScreen = nullptr;
}

void ScreenManager::addScreen(ScreenInterface *screen) {
  if (this->_first == nullptr) {
    this->_first = screen;
  } else {
    ScreenInterface *currentScreen = this->_first;
    while (currentScreen->getNext() != nullptr) {
      currentScreen = currentScreen->getNext();
    }
    currentScreen->setNext(screen);
  }
}

ScreenInterface *ScreenManager::getNext() { return _next; }

void ScreenManager::switchToScreen(ScreenInterface *screen) {}

ScreenInterface *ScreenManager::getCurrentScreen() { return _currentScreen; }
