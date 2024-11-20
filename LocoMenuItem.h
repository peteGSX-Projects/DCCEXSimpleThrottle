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

#ifndef LOCOMENUITEM_H
#define LOCOMENUITEM_H

#include "BaseMenuItem.h"
#include <DCCEXProtocol.h>

/// @brief Extension of the BaseMenuItem class to allow users to select a Loco
class LocoMenuItem : public BaseMenuItem {
public:
  /// @brief Constructor for the loco menu item objects
  /// @param object Pointer to the Loco object to associate with this menu item
  LocoMenuItem(Loco *loco);

  /// @brief Get the Loco object associated with this menu item
  /// @return Pointer to the Loco object
  Loco *getLoco();

private:
  Loco *_loco;
};

#endif // LOCOMENUITEM_H
