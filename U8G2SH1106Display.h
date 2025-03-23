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

#ifndef U8G2SH1106DISPLAY_H
#define U8G2SH1106DISPLAY_H

#include "Defines.h"
#include "DisplayInterface.h"
#include <U8g2lib.h>
#if (OLED_CONNECTION == OLED_SPI)
#include <SPI.h>
#endif // OLED_CONNECTION

/// @brief Class to implement display on an SH1106 based OLED using the U8g2 library
class U8G2SH1106Display : public DisplayInterface {
public:
  /// @brief Constructor for the display object
  U8G2SH1106Display();

  /// @brief Start the display
  void begin() override;

  /// @brief Clear the display
  void clear() override;

  /// @brief Display the startup screen
  /// @param headerText Header text to display
  /// @param version Software version to display
  void displayStartupScreen(const char *headerText, const char *version) override;

  /// @brief Display progress screen for the specified activity
  /// @param activity Text of the activity in progress
  /// @param counter Counter of the current attempt
  void displayProgressScreen(const char *activity, uint8_t counter) override;

  /// @brief Display error screen
  /// @param errorText Error text to display
  void displayErrorScreen(const char *errorText) override;

  /// @brief Display a menu
  /// @param menuName Name of the menu being displayed
  /// @param firstMenuItem Pointer to the first menu item in the list of items
  /// @param selectedItemIndex Index of the currently selected item to be highlighted
  /// @param selectionChanged Flag if the user has changed the selection
  void displayMenuScreen(const char *menuName, BaseMenuItem *firstMenuItem, uint8_t selectedItemIndex,
                         bool selectionChanged) override;

  /// @brief Display the throttle screen
  /// @param locoName Name of the loco currently being operated
  /// @param speed Current speed of the loco
  /// @param direction Current direction of the loco
  /// @param trackPower Current track power state
  /// @param speedChanged Flag if the speed has changed
  /// @param directionChange Flag if the direction has changed
  /// @param trackPowerChanged Flag if the track power state has changed
  void displayThrottleScreen(const char *locoName, uint8_t speed, Direction direction, TrackPower trackPower,
                             bool speedChanged, bool directionChange, bool trackPowerChanged) override;

private:
  U8G2 *_oled;
  const uint8_t *_defaultFont;
  const uint8_t *_menuFont;
  const uint8_t *_speedFont;
  const uint8_t *_throttleFont;

  /// @brief Calculates the number of menu items that will fit on screen
  /// @return Number of items that will fit on screen
  uint8_t _calculateMenuItemsPerPage();

  /// @brief Calculates the height of the header area
  /// @return Header height
  uint16_t _calculateHeaderHeight();

  /// @brief Calculates the height of the menu item area
  /// @return Menu item height
  uint16_t _calculateMenuItemHeight();

  /// @brief Calculates the height of the footer area
  /// @return Footer height
  uint16_t _calculateMenuFooterHeight();

  /// @brief Clear the display
  void _clearDisplay();

  /// @brief Display the header text with a horizontal line separator
  /// @param headerText Text to display
  void _displayHeader(const char *headerText);

  /// @brief Display the software version below the header text
  /// @param version Pointer to the char array containing the version number
  void _displayStartupInfo(const char *version);

  /// @brief Display the list of menu items, paginated by the number that will fit on screen
  /// @param firstMenuItem Pointer to the first menu item in the list
  /// @param selectedItemIndex Index of the currently selected item to highlight
  /// @return Current page number
  uint8_t _displayMenuItems(BaseMenuItem *firstMenuItem, uint8_t selectedItemIndex);

  /// @brief Displays the horizontal line separator and Page # text
  void _displayMenuFooter();

  /// @brief Displays the provided page number within the menu footer
  /// @param pageNumber Page number
  void _displayPageNumber(uint8_t pageNumber);

  /// @brief Display progress bar
  /// @param counter Current attempt counter
  void _displayProgress(uint8_t counter);

  /// @brief Display an error message with emoji
  /// @param errorMessage Error message to display
  void _displayErrorMessage(const char *errorMessage);

  /// @brief Update the currenty selected loco's speed
  /// @param speed 8 bit integer of the speed
  void _displayLocoSpeed(uint8_t speed);

  /// @brief Update the currently selected loco's direction
  /// @param direction Forward|Reverse
  void _displayLocoDirection(Direction direction);

  /// @brief Update the address of the currently selected loco
  /// @param address Pointer to the char array containing the name
  void _displayLocoName(const char *name);

  /// @brief Update the current track power status
  /// @param trackPower PowerOff|PowerOn|PowerUnknown
  void _displayTrackPowerState(TrackPower trackPower);
};

#endif // U8G2SH1106DISPLAY_H
