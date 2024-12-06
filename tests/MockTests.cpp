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

#include "MockDisplayInterface.h"
#include "MockUserConfirmationInterface.h"
#include "MockUserSelectionInterface.h"
#include "Version.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;

// UserConfirmationInterfaceTests here

/// @brief Test UserConfirmationInterface.begin() is called once
TEST(UserConfirmationInterfaceTests, BeginCalledOnce) {
  MockUserConfirmationInterface mockUCI;

  EXPECT_CALL(mockUCI, begin()).Times(1);

  mockUCI.begin();
}

// UserSelectionInterfaceTests here

/// @brief Test UserSelectionInterface.begin() is called once
TEST(UserSelectionInterfaceTests, GetUserSelectionCalledOnce) {
  MockUserSelectionInterface mockUSI;

  EXPECT_CALL(mockUSI, begin()).Times(1);

  mockUSI.begin();
}

// DisplayInterfaceTests here

/// @brief Test DisplayInterface.begin() is called once
TEST(DisplayInterfaceTests, DisplayBeginCalledOnce) {
  MockDisplayInterface mockDisplay;

  EXPECT_CALL(mockDisplay, begin()).Times(1); // Expect 'begin' to be called once

  mockDisplay.begin(); // Call the method
}

TEST(DisplayInterfaceTests, DisplayStartupScreenCalled) {
  MockDisplayInterface mockDisplay;

  EXPECT_CALL(mockDisplay, displayStartupScreen("DCC-EX Simple Throttle", VERSION)).Times(1);

  mockDisplay.displayStartupScreen("DCC-EX Simple Throttle", VERSION);
}
