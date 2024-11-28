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

#include "CommandStationListener.h"

CommandStationListener::CommandStationListener(EventManager *eventManager) : _eventManager(eventManager) {}

void CommandStationListener::receivedRosterList() {
  if (!_eventManager)
    return;
  EventData eventData;
  _eventManager->triggerEvent("ReceivedRoster", eventData);
}

void CommandStationListener::receivedLocoUpdate(Loco *loco) {
  CONSOLE.print("Received loco update for ");
  CONSOLE.println(loco->getAddress());
}

void CommandStationListener::receivedTrackPower(TrackPower powerState) {
  CONSOLE.print("Received track power state: ");
  CONSOLE.println(powerState);
}

void CommandStationListener::receivedReadLoco(int address) {
  CONSOLE.print("Read loco address: ");
  CONSOLE.println(address);
}
