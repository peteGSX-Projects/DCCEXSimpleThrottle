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

struct EventType {
  const char *name;
  EventType *next;

  /// @brief Constructor for each event type
  /// @param name Name of the event type
  EventType(const char *name) : name(name), next(nullptr) {}
};

/// @brief Struct to cater for events with different data types
struct EventData {
  enum class DataType { Byte, Integer, Loco, None };
  DataType dataType;

  union {
    uint8_t byteValue;
    int intValue;
    Loco *locoValue;
  };

  /// @brief Constructor for events with a uint8_t parameter
  /// @param value 8 bit integer
  EventData(uint8_t value) : dataType(DataType::Byte), byteValue(value) {}

  /// @brief Constructor for events with an int parameter
  /// @param value Signed integer
  EventData(int value) : dataType(DataType::Integer), intValue(value) {}

  /// @brief Constructor for events with a Loco pointer
  /// @param value Pointer to a loco object
  EventData(Loco *value) : dataType(DataType::Loco), locoValue(value) {}

  /// @brief Constructor for events with no data or parameters
  EventData() : dataType(DataType::None) {}
};

/// @brief Event structure for events using EventData structure
struct Event {
  EventType *eventType;
  void (*function)(void *instance, EventData eventData);
  void *instance;
  Event *next;

  /// @brief Constructor for each Event
  /// @param eventType Pointer to an event type
  /// @param function Function that this event calls
  /// @param instance Instance of the relevant class containing the function
  Event(EventType *eventType, void (*function)(void *, EventData), void *instance)
      : eventType(eventType), function(function), instance(instance), next(nullptr) {}
};

class EventManager {
public:
  /// @brief Constructor for the event manager
  EventManager();

  /// @brief Register an event with the provided type name
  /// @param typeName Name of the event type to register
  /// @param function Function of the specified instance to call
  /// @param instance Pointer to the instance of the class containing the function
  void registerEvent(const char *typeName, void (*function)(void *, EventData), void *instance);

  /// @brief Trigger the specified event by name
  /// @param typeName Name of the event type to trigger
  /// @param eventData Valid EventData structure
  void triggerEvent(const char *typeName, EventData eventData);

  /// @brief Static method to trigger selection of a CommandStation to connect to
  /// @param connectionManagerInstance Pointer to the ConnectionManager object
  /// @param commandStationIndex Index of the CommandStation list item to connect to
  /// @param eventData Valid EventData structure
  static void staticSelectCommandStation(void *connectionManagerInstance, EventData eventData);

  /// @brief Static method to trigger updating the SelectLocoMenu when the roster is received
  /// @param appOrchestratorInstance Pointer to the AppOrchestrator object
  /// @param eventData Valid EventData structure
  static void staticReceivedRoster(void *appOrchestratorInstance, EventData eventData);

private:
  Event *_firstEvent;
  EventType *_firstEventType;

  /// @brief Add a new event type by name
  /// @param name Name of the event type
  /// @return Pointer to the created event type
  EventType *_addEventType(const char *name);

  /// @brief Check if the named event type exists
  /// @param name Name of the event type
  /// @return Pointer to the event type
  EventType *_getEventType(const char *name);
};

#endif // EVENTMANAGER_H
