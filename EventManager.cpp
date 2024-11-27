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

#include "EventManager.h"

EventManager::EventManager() {
  _eventCount = 0;
  _intEventCount = 0;
  _locoEventCount = 0;
}

void EventManager::registerIntEvent(EventType eventType, void (*function)(void *, int), void *instance) {
  if (_intEventCount < _maxIntEvents) {
    _intEvents[_intEventCount] = {eventType, function, instance};
    _intEventCount++;
  }
}

void EventManager::triggerIntEvent(EventType eventType, int intParameter) {
  for (uint8_t i = 0; i < _intEventCount; i++) {
    if (_intEvents[i].eventType == eventType) {
      _intEvents[i].function(_intEvents[i].instance, intParameter);
    }
  }
}
