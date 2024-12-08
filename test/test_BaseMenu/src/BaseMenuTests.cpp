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
#include "MockEventManager.h"
#include "../include/MockBaseMenu.h"
#include "BaseMenu.h"
#include <gtest/gtest.h>

using ::testing::AtLeast;
TEST(BaseMenuTests, CanGetName) {
  MockBaseMenu *menu = new MockBaseMenu();

  const char *name = "Mock Test Menu name";
  menu->setMenuName(name);

  EXPECT_STREQ(menu->getMenuName(), name);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  // if you plan to use GMock, replace the line above with
  // ::testing::InitGoogleMock(&argc, argv);

  if (RUN_ALL_TESTS())
    ;

  // Always return zero-code and allow PlatformIO to parse results
  return 0;
}