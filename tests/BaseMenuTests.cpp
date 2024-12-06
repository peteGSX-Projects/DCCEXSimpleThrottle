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

#include "BaseMenu.h"
#include "MockDisplayInterface.h"
#include "MockEventManager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

/// @brief Test menu class to implement virtual methods for testing
class TestMenu : public BaseMenu {
public:
  void handleUserConfirmationAction(UserConfirmationAction action) override {}
};

/// @brief Test fixture class for BaseMenu tests
class BaseMenuTests : public ::testing::Test {
protected:
  TestMenu *testMenu;                 // Pointer to the BaseMenu
  MockDisplayInterface *mockDisplay;  // Pointer to the mock display interface
  MockEventManager *mockEventManager; // Pointer to the mock event manager

  void SetUp() override {
    testMenu = new TestMenu();
    mockDisplay = new MockDisplayInterface();
    mockEventManager = new MockEventManager();
  }

  void TearDown() override {
    delete testMenu;
    delete mockDisplay;
    delete mockEventManager;
  }
};

/// @brief Validate menu name is set and returned correctly
TEST_F(BaseMenuTests, SetGetMenuName) {
  const char *name = "Test Menu Name";
  testMenu->setMenuName(name);

  EXPECT_STREQ(testMenu->getMenuName(), name);
}
