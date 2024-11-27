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

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <Arduino.h>
#include <DCCEXProtocol.h>

/// @brief Enum of valid event types to register and trigger
enum class EventType { ServerSelected };

/// @brief Event structure for events without parameters
struct Event {
  EventType eventType;
  void (*function)(void *instance);
  void *instance;
};

/// @brief Event structure for events that accept a single int
struct IntEvent {
  EventType eventType;
  void (*function)(void *instance, int intParameter);
  void *instance;
};

/// @brief Event structure for events that accept a Loco pointer
struct LocoEvent {
  EventType eventType;
  void (*function)(void *instance, Loco *loco);
  void *instance;
};

class EventManager {
public:
  EventManager();

  void registerIntEvent(EventType eventType, void (*function)(void *, int), void *instance);

  void triggerIntEvent(EventType eventType, int intParameter);

private:
  static const uint8_t _maxEvents = 10;
  static const uint8_t _maxIntEvents = 10;
  static const uint8_t _maxLocoEvents = 1;
  Event _events[_maxEvents];
  IntEvent _intEvents[_maxIntEvents];
  LocoEvent _locoEvents[_maxLocoEvents];
  uint8_t _eventCount;
  uint8_t _intEventCount;
  uint8_t _locoEventCount;
};

#endif // EVENTMANAGER_H
