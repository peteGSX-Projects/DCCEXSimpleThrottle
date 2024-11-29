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

#include "AppOrchestrator.h"
#include "ConnectionManager.h"
#include "EventManager.h"

EventManager::EventManager() : _firstEvent(nullptr), _firstEventType(nullptr) {}

void EventManager::registerEvent(const char *typeName, void (*function)(void *, EventData), void *instance) {
  EventType *eventType = _getEventType(typeName);
  if (eventType == nullptr) {
    eventType = _addEventType(typeName);
  }
  Event *newEvent = new Event(eventType, function, instance);
  if (_firstEvent == nullptr) {
    _firstEvent = newEvent;
  } else {
    Event *currentEvent = _firstEvent;
    while (currentEvent->next != nullptr) {
      currentEvent = currentEvent->next;
    }
    currentEvent->next = newEvent;
  }
}

void EventManager::triggerEvent(const char *typeName, EventData eventData) {
  CONSOLE.print("Received event ");
  CONSOLE.println(typeName);
  for (Event *event = _firstEvent; event; event = event->next) {
    if (event->eventType->name == typeName) {
      event->function(event->instance, eventData);
      break;
    }
  }
}

void EventManager::staticSelectCommandStation(void *connectionManagerInstance, EventData eventData) {
  if (eventData.dataType != EventData::DataType::Byte)
    return;
  uint8_t commandStationIndex = eventData.byteValue;
  ConnectionManager *connectionManager = static_cast<ConnectionManager *>(connectionManagerInstance);
  connectionManager->selectCommandStation(commandStationIndex);
}

void EventManager::staticReceivedRosterList(void *appOrchestratorInstance, EventData eventData) {
  AppOrchestrator *appOrchestrator = static_cast<AppOrchestrator *>(appOrchestratorInstance);
  appOrchestrator->setupSelectLocoMenu();
}

void EventManager::staticSelectLoco(void *appOrchestratorInstance, EventData eventData) {
  AppOrchestrator *appOrchestrator = static_cast<AppOrchestrator *>(appOrchestratorInstance);
  appOrchestrator->setThrottleLoco(eventData.locoValue);
}

void EventManager::staticReceivedLocoUpdate(void *appOrchestratorInstance, EventData eventData) {
  AppOrchestrator *appOrchestrator = static_cast<AppOrchestrator *>(appOrchestratorInstance);
  appOrchestrator->updateThrottleLoco(eventData.locoValue);
}

EventType *EventManager::_addEventType(const char *name) {
  EventType *newEventType = new EventType(name);
  if (_firstEventType == nullptr) {
    _firstEventType = newEventType;
  } else {
    EventType *currentEventType = _firstEventType;
    while (currentEventType->next != nullptr) {
      currentEventType = currentEventType->next;
    }
    currentEventType->next = newEventType;
  }
  return newEventType;
}

EventType *EventManager::_getEventType(const char *name) {
  for (EventType *eventType = _firstEventType; eventType; eventType = eventType->next) {
    if (eventType->name == name) {
      return eventType;
    }
  }
  return nullptr;
}
