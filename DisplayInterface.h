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

  /// @brief Display the startup screen
  /// @param headerText Header text to display
  /// @param version Software version to display
  virtual void displayStartupScreen(const char *headerText, const char *version) = 0;

  /// @brief Display progress screen for the specified activity
  /// @param activity Text of the activity in progress
  /// @param counter Counter of the current attempt
  virtual void displayProgressScreen(const char *activity, uint8_t counter) = 0;

  /// @brief Display error screen
  /// @param errorText Error text to display
  virtual void displayErrorScreen(const char *errorText) = 0;

  /// @brief Display a menu
  /// @param menuName Name of the menu being displayed
  /// @param firstMenuItem Pointer to the first menu item in the list of items
  /// @param selectedItemIndex Index of the currently selected item to be highlighted
  /// @param selectionChanged Flag if the user has changed the selection
  virtual void displayMenuScreen(const char *menuName, BaseMenuItem *firstMenuItem, uint8_t selectedItemIndex,
                                 bool selectionChanged) = 0;

  /// @brief Display the throttle screen
  /// @param locoName Name of the loco currently being operated
  /// @param speed Current speed of the loco
  /// @param direction Current direction of the loco
  /// @param trackPower Current track power state
  /// @param speedChanged Flag if the speed has changed
  /// @param directionChange Flag if the direction has changed
  /// @param trackPowerChanged Flag if the track power state has changed
  virtual void displayThrottleScreen(const char *locoName, uint8_t speed, Direction direction, TrackPower trackPower,
                                     bool speedChanged, bool directionChange, bool trackPowerChanged) = 0;

  /// @brief Check if the display needs to be redrawn to prevent unnecessary redraws and flicker
  /// @return True|False
  bool needsRedraw() { return _needsRedraw; }

  /// @brief Set the redraw flag for this display
  /// @param redraw True|False
  void setNeedsRedraw(bool redraw) { _needsRedraw = redraw; }

  /// @brief Check if the menu needs refreshing - avoids a complete redraw for menu screens
  /// @return True|False
  bool needsMenuRefresh() { return _needsMenuRefresh; }

  /// @brief Set the refresh menu flag for this display
  /// @param refresh True|False
  void setNeedsMenuRefresh(bool refresh) { _needsMenuRefresh = refresh; }

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
  bool _needsMenuRefresh = false;
  uint8_t _menuItemsPerPage = 0;
};

#endif // DISPLAYINTERFACE_H
