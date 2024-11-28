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

EventManager::EventManager() : _first(nullptr) {}

void EventManager::registerEvent(EventType eventType, void (*function)(void *, EventData), void *instance) {
  Event *newEvent = new Event(eventType, function, instance);
  if (_first == nullptr) {
    _first = newEvent;
  } else {
    Event *currentEvent = _first;
    while (currentEvent->next != nullptr) {
      currentEvent = currentEvent->next;
    }
    currentEvent->next = newEvent;
  }
}

void EventManager::triggerEvent(EventType eventType, EventData eventData) {
  for (Event *event = _first; event; event = event->next) {
    if (event->eventType == eventType) {
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

void EventManager::staticReceivedRoster(void *appOrchestratorInstance, EventData eventData) {
  CONSOLE.println("EventManager::staticReceivedRoster");
  AppOrchestrator *appOrchestrator = static_cast<AppOrchestrator *>(appOrchestratorInstance);
  appOrchestrator->setupSelectLocoMenu();
}
