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

#ifndef MOCKDISPLAYINTERFACE_H
#define MOCKDISPLAYINTERFACE_H

#include "DisplayInterface.h"
#include <gmock/gmock.h>

/// @brief Mock class for DisplayInterface for testing display output
/// All class methods are mocked here
class MockDisplayInterface : public DisplayInterface {
public:
  MOCK_METHOD(void, begin, (), (override));

  MOCK_METHOD(void, clear, (), (override));

  MOCK_METHOD(void, displayStartupScreen, (const char *headerText, const char *version), (override));

  MOCK_METHOD(void, displayProgressScreen, (const char *activity, uint8_t counter), (override));

  MOCK_METHOD(void, displayErrorScreen, (const char *errorText), (override));

  MOCK_METHOD(void, displayMenuScreen,
              (const char *menuName, BaseMenuItem *firstMenuItem, uint8_t selectedItemIndex, bool selectionChanged),
              (override));

  MOCK_METHOD(void, displayThrottleScreen,
              (const char *locoName, uint8_t speed, Direction direction, TrackPower trackPower, bool speedChanged,
               bool directionChange, bool trackPowerChanged),
              (override));

  MOCK_METHOD(bool, needsMenuRefresh, ());

  MOCK_METHOD(void, setNeedsMenuRefresh, (bool refresh));

  MOCK_METHOD(uint8_t, getMenuItemsPerPage, ());

  MOCK_METHOD(void, setMenuItemsPerPage, (uint8_t getMenuItemsPerPage));
};

#endif
