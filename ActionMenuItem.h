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

#ifndef ACTIONMENUITEM_H
#define ACTIONMENUITEM_H

#include "BaseMenuItem.h"
#include "EventStructure.h"

/// @brief Extension of the BaseMenuItem class for users to select items that publish an event
/// Each action must generate an event to be published to the AppOrchestrator
class ActionMenuItem : public BaseMenuItem {
public:
  /// @brief Constructor for the action menu item objects
  /// @param name Pointer to the char array containing the item's name to display
  /// @param event Pointer to the Event to publish when this item is selected
  ActionMenuItem(const char *name, Event *event);

  /// @brief Get the Event associated with this item
  /// @return Pointer to the Event to publish
  Event *getEvent();

private:
  Event *_event;
};

#endif // ACTIONMENUITEM_H
