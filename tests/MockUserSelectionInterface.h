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

#ifndef MOCKUSERSELECTIONINTERFACE_H
#define MOCKUSERSELECTIONINTERFACE_H

#include "UserSelectionInterface.h"
#include <gmock/gmock.h>

/// @brief Mock class for UserSelectionInterface for testing user interaction
/// All class methods are mocked here
class MockUserSelectionInterface : public UserSelectionInterface {
public:
  MOCK_METHOD(void, begin, (), (override));

  MOCK_METHOD(UserSelectionAction, getUserSelectionAction, (), (override));
};

#endif
