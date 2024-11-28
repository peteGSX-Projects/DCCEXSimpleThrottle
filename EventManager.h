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

#include "ConnectionManager.h"
#include <Arduino.h>
#include <DCCEXProtocol.h>

/// @brief Enum of valid event types to register and trigger
enum class EventType { SelectedCommandStation, ReceivedRoster };

/// @brief Event structure for events without parameters
struct Event {
  EventType eventType;
  void (*function)(void *instance);
  void *instance;
};

/// @brief Event structure for events that accept a single int
struct ByteEvent {
  EventType eventType;
  void (*function)(void *instance, uint8_t byteParameter);
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
  /// @brief Constructor for the event manager
  EventManager();

  /// @brief Register an event requiring a single integer as a parameter
  /// @param eventType Valid EventType enum
  /// @param function Function of the specified instance to call
  /// @param instance Pointer to the instance of the class containing the function
  void registerByteEvent(EventType eventType, void (*function)(void *, uint8_t), void *instance);

  /// @brief Trigger the specified event
  /// @param eventType Valid EventType enum
  /// @param intParameter Integer parameter to pass
  void triggerByteEvent(EventType eventType, uint8_t intParameter);

  /// @brief Static method to trigger selection of a CommandStation to connect to
  /// @param instance Pointer to the ConnectionManager object
  /// @param commandStationIndex Index of the CommandStation list item to connect to
  static void staticSelectCommandStation(void *instance, uint8_t commandStationIndex);

private:
  static const uint8_t _maxEvents = 10;
  static const uint8_t _maxByteEvents = 10;
  static const uint8_t _maxLocoEvents = 10;
  Event _events[_maxEvents];
  ByteEvent _byteEvents[_maxByteEvents];
  LocoEvent _locoEvents[_maxLocoEvents];
  uint8_t _eventCount;
  uint8_t _byteEventCount;
  uint8_t _locoEventCount;
};

#endif // EVENTMANAGER_H
