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
  _trackPower = TrackPower::PowerUnknown;
  _trackPowerChanged = false;
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
      _dccexProtocolClient->setThrottle(_loco, 0, _direction);
    }
    break;
  case UserConfirmationAction::DoubleClick:
    CONSOLE.println("Toggle lights on|off");
    break;
  case UserConfirmationAction::LongPress:
    if (_speed > 0) {
      _dccexProtocolClient->emergencyStop();
    }
    break;
  default:
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
  uint8_t speed = _loco->getSpeed();
  switch (action) {
  case UserSelectionAction::Up: {
    if (speed < 128) {
      speed += _throttleStep;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, speed, _direction);
    }
    break;
  }
  case UserSelectionAction::UpFaster: {
    if (speed < 128) {
      _speed += _throttleStepFaster;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, speed, _direction);
    }
    break;
  }
  case UserSelectionAction::UpFastest: {
    if (speed < 128) {
      speed += _throttleStepFastest;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, speed, _direction);
    }
    break;
  }
  case UserSelectionAction::Down: {
    if (speed > 0) {
      speed -= _throttleStep;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, speed, _direction);
    }
    break;
  }
  case UserSelectionAction::DownFaster: {
    if (speed > 0) {
      speed -= _throttleStepFaster;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, speed, _direction);
    }
    break;
  }
  case UserSelectionAction::DownFastest: {
    if (speed > 0) {
      speed -= _throttleStepFastest;
      _speedChanged = true;
      _dccexProtocolClient->setThrottle(_loco, speed, _direction);
    }
    break;
  }
  default:
    break;
  }
}

void ThrottleScreen::drawScreen(DisplayInterface *display) {
  display->displayThrottleScreen(_loco->getName(), _loco->getSpeed(), _loco->getDirection(), _trackPower, _speedChanged,
                                 _directionChanged, _trackPowerChanged);
  _speedChanged = false;
  _directionChanged = false;
  _trackPowerChanged = false;
}

void ThrottleScreen::setLoco(Loco *loco) { _loco = loco; }

void ThrottleScreen::locoUpdateReceived(Loco *loco) {
  if (_loco != loco)
    return;
  _speedChanged = true;
  _directionChanged = true;
  if (_loco->getSpeed() != _speed) {
    _speed = _loco->getSpeed();
  }
  if (_loco->getDirection() != _direction) {
    _direction = _loco->getDirection();
  }
}

uint8_t ThrottleScreen::getSpeed() { return _speed; }

void ThrottleScreen::trackPowerUpdateReceived(TrackPower trackPower) {
  if (trackPower != _trackPower) {
    _trackPower = trackPower;
    _trackPowerChanged = true;
  }
}

void ThrottleScreen::requestLocoUpdate() { _dccexProtocolClient->requestLocoUpdate(_loco->getAddress()); }

void ThrottleScreen::requestTrackPowerUpdate() { _dccexProtocolClient->requestServerVersion(); }
