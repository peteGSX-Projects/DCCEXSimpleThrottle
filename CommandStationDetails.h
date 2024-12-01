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

#ifndef COMMANDSTATIONDETAILS_H
#define COMMANDSTATIONDETAILS_H

#include "Defines.h"
#include <Arduino.h>

#ifdef WIFI_ENABLED
#include <WiFi.h>

struct CommandStationDetails {
  const char *name;
  IPAddress ipAddress;
  uint16_t port;
  const char *ssid;
  const char *password;
};
#endif // WIFI_ENABLED

#endif // COMMANDSTATIONDETAILS_H
