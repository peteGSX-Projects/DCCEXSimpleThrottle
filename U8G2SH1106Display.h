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

/// @brief Class to implement display on an SH1106 based OLED using the U8g2 library
class U8G2SH1106Display : public DisplayInterface {
public:
  /// @brief Constructor for the display object
  U8G2SH1106Display();

  /// @brief Start the display
  void begin() override;

  /// @brief Clear the display
  void clear() override;

  /// @brief Display the header text with horizontal line separator from other items
  /// @param headerText Pointer to the char array containing the header text
  void displayHeader(const char *headerText) override;

  /// @brief Implement this to display the menu item's text at the correct position on a display
  /// @param index Index of the item to be displayed
  /// @param itemText Pointer to the char array containing the item's text
  /// @param selected Flag if this item is selected or not so it can be highlighted
  void displayMenuItem(uint8_t index, const char *itemText, bool selected) override;

  /// @brief Display the software version below the header text
  /// @param version Pointer to the char array containing the version number
  void displaySoftwareVersion(const char *version) override;

  /// @brief Update the currenty selected loco's speed
  /// @param speed 8 bit integer of the speed
  void updateSpeed(uint8_t speed) override;

  /// @brief Update the address of the currently selected loco
  /// @param address Pointer to the char array containing the name
  void updateLocoName(const char *name) override;

  /// @brief Update the currently selected loco's direction
  /// @param direction Forward|Reverse
  void updateLocoDirection(Direction direction) override;

  /// @brief Update the current track power status
  /// @param trackPower PowerOff|PowerOn|PowerUnknown
  void updateTrackPowerState(TrackPower trackPower) override;

private:
  U8G2 *_oled;
  const uint8_t *_defaultFont;
  const uint8_t *_menuFont;
  const uint8_t *_speedFont;
  const uint8_t *_directionFont;
  const uint8_t *_addressFont;
  const uint8_t *_eStopFont;
  const uint8_t *_wifiFont;
  const uint8_t *_csFont;
  const uint8_t *_errorFont;
};

#endif // U8G2SH1106DISPLAY_H
