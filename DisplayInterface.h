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

#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H

#include "BaseMenuItem.h"
#include <Arduino.h>
#include <DCCEXProtocol.h>

/// @brief Interface class to abstract construction of what is displayed on screen from the physical implementations
/// All physical display classes must extend this
/// This allows for different display types and resolutions to be used
class DisplayInterface {
public:
  /// @brief Implement this to perform any initial startup methods or activities
  virtual void begin() = 0;

  /// @brief Implement this to entirely clear a display
  virtual void clear() = 0;

  /// @brief Implement this to display the header text with a horizontal line separator from other items
  /// @param headerText Pointer to the char array containing the header text
  virtual void displayHeader(const char *headerText) = 0;

  /// @brief Implement this method to display the menu items on screen
  /// @param firstItem Pointer to the first menu item to be displayed
  /// @param selectedIndex Index of the item currently selected by the user
  virtual void displayMenuItems(BaseMenuItem *firstItem, uint8_t selectedIndex) = 0;

  /// @brief Implement this method to display the page number of a menu on screen
  /// @param pageNumber Page number to display
  /// @param pageChanged True|False
  virtual void displayPageNumber(uint8_t pageNumber, bool pageChanged) = 0;

  virtual void displayMenu(const char *menuName, BaseMenuItem *menuItems, uint8_t selectedItemIndex) = 0;

  /// @brief Implement this to display the software version below the header text
  /// @param version Pointer to the char array containing the version number
  virtual void displaySoftwareVersion(const char *version) = 0;

  /// @brief Implement this to update the currenty selected loco's speed
  /// @param speed 8 bit integer of the speed
  virtual void updateSpeed(uint8_t speed) = 0;

  /// @brief Implement this to update the name of the currently selected loco
  /// @param name Pointer to the char array containing the name
  virtual void updateLocoName(const char *name) = 0;

  /// @brief Implement this to update the currently selected loco's direction
  /// @param direction Forward|Reverse
  virtual void updateLocoDirection(Direction direction) = 0;

  /// @brief Implement this to update the current track power status
  /// @param trackPower PowerOff|PowerOn|PowerUnknown
  virtual void updateTrackPowerState(TrackPower trackPower) = 0;

  /// @brief Check if the display needs to be redrawn to prevent unnecessary redraws and flicker
  /// @return True|False
  bool needsRedraw() { return _needsRedraw; }

  /// @brief Set the redraw flag for this display
  /// @param redraw True|False
  void setNeedsRedraw(bool redraw) { _needsRedraw = redraw; }

  /// @brief Get the number of menu items to be displayed per page for this display
  /// @return Number of items per page this display can handle
  uint8_t getMenuItemsPerPage() { return _menuItemsPerPage; }

  /// @brief Set the number of menu items per page this display can handle
  /// @param menuItemsPerPage Items per page
  void setMenuItemsPerPage(uint8_t menuItemsPerPage) { _menuItemsPerPage = menuItemsPerPage; }

  /// @brief Destructor for the object
  virtual ~DisplayInterface() = default;

private:
  bool _needsRedraw = false;
  uint8_t _menuItemsPerPage = 0;

  virtual void _displayHeader(const char *headerText) = 0;

  virtual uint8_t _displayMenuItems(BaseMenuItem *firstMenuItem, uint8_t selectedItemIndex) = 0;

  virtual void _displayPageNumber(uint8_t pageNumber) = 0;
  
  virtual void _displayMenuFooter() = 0;
};

#endif // DISPLAYINTERFACE_H
