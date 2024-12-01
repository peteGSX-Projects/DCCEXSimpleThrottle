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

#include "Defines.h"
#include "ThrottleScreen.h"

ThrottleScreen::ThrottleScreen(DCCEXProtocol *dccexProtocolClient, uint8_t throttleStep, uint8_t throttleStepFaster,
                               uint8_t throttleStepFastest)
    : _dccexProtocolClient(dccexProtocolClient), _throttleStep(throttleStep), _throttleStepFaster(throttleStepFaster),
      _throttleStepFastest(throttleStepFastest) {
  _speed = 0;
  _speedChanged = false;
  _direction = Direction::Forward;
  _directionChanged = false;
  _loco = nullptr;
}

void ThrottleScreen::handleUserConfirmationAction(UserConfirmationAction action) {
  switch (action) {
  case UserConfirmationAction::SingleClick:
    if (_speed == 0) {
      _directionChanged = true;
      if (_direction == Direction::Forward) {
        _direction = Direction::Reverse;
        _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
      } else {
        _direction = Direction::Forward;
        _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
      }
    } else {
      _speed = 0;
      _speedChanged = true;
    }
    break;
  case UserConfirmationAction::DoubleClick:
    CONSOLE.println("Toggle lights on|off");
    break;
  case UserConfirmationAction::LongPress:
    if (_speed > 0) {
      CONSOLE.println("Emergency stop");
    }
    break;
  default:
    _directionChanged = false;
    break;
  }
}

void ThrottleScreen::handleUserSelectionAction(UserSelectionAction action, bool throttleInverted) {
  if (throttleInverted) {
    if (action == UserSelectionAction::Up) {
      action = UserSelectionAction::Down;
    } else if (action == UserSelectionAction::UpFaster) {
      action = UserSelectionAction::DownFaster;
    } else if (action == UserSelectionAction::UpFastest) {
      action = UserSelectionAction::DownFastest;
    } else if (action == UserSelectionAction::Down) {
      action = UserSelectionAction::Up;
    } else if (action == UserSelectionAction::DownFaster) {
      action = UserSelectionAction::UpFaster;
    } else if (action == UserSelectionAction::DownFastest) {
      action = UserSelectionAction::UpFastest;
    }
  }
  switch (action) {
  case UserSelectionAction::Up:
    if (_speed < 128) {
      _speed += _throttleStep;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
    }
    break;
  case UserSelectionAction::UpFaster:
    if (_speed < 128) {
      _speed += _throttleStepFaster;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
    }
    break;
  case UserSelectionAction::UpFastest:
    if (_speed < 128) {
      _speed += _throttleStepFastest;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
    }
    break;
  case UserSelectionAction::Down:
    if (_speed > 0) {
      _speed -= _throttleStep;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
    }
    break;
  case UserSelectionAction::DownFaster:
    if (_speed > 0) {
      _speed -= _throttleStepFaster;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
    }
    break;
  case UserSelectionAction::DownFastest:
    if (_speed > 0) {
      _speed -= _throttleStepFastest;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, _speed, _direction);
    }
    break;
  default:
    _speedChanged = false;
    break;
  }
}

void ThrottleScreen::drawScreen(DisplayInterface *display) {
  if (_speedChanged) {
    display->updateSpeed(_speed);
  }
  if (_directionChanged) {
    display->updateLocoDirection(_direction);
  }
  if (!display->needsRedraw())
    return;
  display->setNeedsRedraw(false);
  display->clear();
  if (_loco) {
    display->updateSpeed(_loco->getSpeed());
    display->updateLocoName(_loco->getName());
    display->updateLocoDirection(_loco->getDirection());
  } else {
    display->updateSpeed(0);
    display->updateLocoName("No Loco Selected");
    display->updateLocoDirection(Direction::Forward);
  }
  display->updateTrackPowerState(TrackPower::PowerOff);
}

void ThrottleScreen::setLoco(Loco *loco) { _loco = loco; }

void ThrottleScreen::locoUpdateReceived(Loco *loco) {
  if (_loco != loco)
    return;
  CONSOLE.print("Loco update speed|direction: ");
  CONSOLE.print(_loco->getSpeed());
  CONSOLE.print("|");
  CONSOLE.println(_loco->getDirection());
}

uint8_t ThrottleScreen::getSpeed() { return _speed; }
