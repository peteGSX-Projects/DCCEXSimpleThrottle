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
};

// SINGLE EVENT TYPE
// /// @brief Event structure for events that accept a single int
// struct ByteEvent {
//   EventType eventType;
//   void (*function)(void *instance, uint8_t byteParameter);
//   void *instance;
// };

// SINGLE EVENT TYPE
// /// @brief Event structure for events that accept a Loco pointer
// struct LocoEvent {
//   EventType eventType;
//   void (*function)(void *instance, Loco *loco);
//   void *instance;
// };

class EventManager {
public:
  /// @brief Constructor for the event manager
  EventManager();

  /// @brief Register an event requiring a single integer as a parameter
  /// @param eventType Valid EventType enum
  /// @param function Function of the specified instance to call
  /// @param instance Pointer to the instance of the class containing the function
  // SINGLE EVENT TYPE
  // void registerByteEvent(EventType eventType, void (*function)(void *, uint8_t), void *instance);
  void registerEvent(EventType eventType, void (*function)(void *, EventData), void *instance);

  /// @brief Trigger the specified event
  /// @param eventType Valid EventType enum
  /// @param intParameter Integer parameter to pass
  // SINGLE EVENT TYPE
  // void triggerByteEvent(EventType eventType, uint8_t intParameter);
  void triggerEvent(EventType eventType, EventData eventData);

  /// @brief Static method to trigger selection of a CommandStation to connect to
  /// @param connectionManagerInstance Pointer to the ConnectionManager object
  /// @param commandStationIndex Index of the CommandStation list item to connect to
  // static void staticSelectCommandStation(void *connectionManagerInstance, uint8_t commandStationIndex);
  static void staticSelectCommandStation(void *connectionManagerInstance, EventData eventData);

  /// @brief Static method to trigger updating the SelectLocoMenu when the roster is received
  /// @param menuManagerInstance Pointer to the MenuManager object
  static void staticReceivedRoster(void *menuManagerInstance);

private:
  static const uint8_t _maxEvents = 10;
  // SINGLE EVENT TYPE
  // static const uint8_t _maxByteEvents = 10;
  // static const uint8_t _maxLocoEvents = 10;
  Event _events[_maxEvents];
  // SINGLE EVENT TYPE
  // ByteEvent _byteEvents[_maxByteEvents];
  // LocoEvent _locoEvents[_maxLocoEvents];
  uint8_t _eventCount;
  // SINGLE EVENT TYPE
  // uint8_t _byteEventCount;
  // uint8_t _locoEventCount;
};

#endif // EVENTMANAGER_H
