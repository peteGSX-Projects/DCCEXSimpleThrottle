/*
 *  © 2024 Peter Cole
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

#ifndef MOCKEVENTMANAGER_H
#define MOCKEVENTMANAGER_H

#include "EventManager.h"
#include <gmock/gmock.h>

/// @brief Mock of the EventManager class for testing
/// All public methods are mocked here
class MockEventManager : public EventManager {
public:
  MOCK_METHOD(void, subscribe, (EventListener * eventListener, EventType eventType));

  MOCK_METHOD(void, unsubscribe, (EventListener * eventListener, EventType eventType));

  MOCK_METHOD(bool, isSubscribed, (EventListener * eventListener, EventType eventType));

  MOCK_METHOD(void, publish, (EventType eventType, EventData eventData));
};

#endif
