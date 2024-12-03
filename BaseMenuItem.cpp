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

#include "BaseMenuItem.h"

BaseMenuItem::BaseMenuItem(const char *name) : _name(nullptr) {
  if (name != nullptr) {
    _name = strdup(name);
  }
  _next = nullptr;
  _index = 0;
}

const char *BaseMenuItem::getName() { return _name; }

void BaseMenuItem::setNext(BaseMenuItem *item) { _next = item; }

BaseMenuItem *BaseMenuItem::getNext() { return _next; }

void BaseMenuItem::setIndex(uint8_t index) { _index = index; }

uint8_t BaseMenuItem::getIndex() { return _index; }
