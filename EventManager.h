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
enum class EventType { SelectedCommandStation, ReceivedRoster };

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
  EventType eventType;
  void (*function)(void *instance, EventData eventData);
  void *instance;
  Event *next;

  /// @brief Constructor for each Event
  /// @param eventType Valid EventType enum
  /// @param function Function that this event calls
  /// @param instance Instance of the relevant class containing the function
  Event(EventType eventType, void (*function)(void *, EventData), void *instance)
      : eventType(eventType), function(function), instance(instance), next(nullptr) {}
};

class EventManager {
public:
  /// @brief Constructor for the event manager
  EventManager();

  /// @brief Register an event requiring a single integer as a parameter
  /// @param eventType Valid EventType enum
  /// @param function Function of the specified instance to call
  /// @param instance Pointer to the instance of the class containing the function
  void registerEvent(EventType eventType, void (*function)(void *, EventData), void *instance);

  /// @brief Trigger the specified event
  /// @param eventType Valid EventType enum
  /// @param eventData
  void triggerEvent(EventType eventType, EventData eventData);

  /// @brief Static method to trigger selection of a CommandStation to connect to
  /// @param connectionManagerInstance Pointer to the ConnectionManager object
  /// @param commandStationIndex Index of the CommandStation list item to connect to
  /// @param eventData
  static void staticSelectCommandStation(void *connectionManagerInstance, EventData eventData);

  /// @brief Static method to trigger updating the SelectLocoMenu when the roster is received
  /// @param appOrchestratorInstance Pointer to the AppOrchestrator object
  /// @param eventData
  static void staticReceivedRoster(void *appOrchestratorInstance, EventData eventData);

private:
  Event *_first;
};

#endif // EVENTMANAGER_H
