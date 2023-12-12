//
//    FILE: PCA9549.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2023-12-12
// PURPOSE: Arduino Library for PCA9549 I2C octal bus switch.
//     URL: https://github.com/RobTillaart/PCA9549


#include "PCA9549.h"


PCA9549::PCA9549(uint8_t deviceAddress, TwoWire *wire)
{
  _address  = deviceAddress;
  _wire     = wire;
  _mask     = 0x00;
  _resetPin = -1;
  _forced   = false;
  _error    = PCA9549_OK;
}


bool PCA9549::begin(uint8_t mask)
{
  if (! isConnected()) return false;
  setChannelMask(mask);
  return true;
}


bool PCA9549::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


bool PCA9549::enableChannel(uint8_t channel)
{
  if (channel >= 8) return false;
  if (!isEnabled(channel))
  {
    setChannelMask(_mask | (0x01 << channel));
  }
  return true;
}


bool PCA9549::disableChannel(uint8_t channel)
{
  if (channel >= 8) return false;
  if (!isEnabled(channel))
  {
    setChannelMask(_mask & ~(0x01 << channel));
  }
  return true;
}


bool PCA9549::selectChannel(uint8_t channel)
{
  if (channel >= 8) return false;
  setChannelMask(0x01 << channel);
  return true;
}


bool PCA9549::isEnabled(uint8_t channel)
{
  if (channel >= 8) return false;
  return (_mask & (0x01 << channel));
}


bool PCA9549::disableAllChannels()
{
  return setChannelMask(0x00);
}


bool PCA9549::setChannelMask(uint8_t mask)
{
  if ((_mask == mask) && (not _forced)) return true;
  _mask = mask;
  _wire->beginTransmission(_address);
  _wire->write(_mask);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t PCA9549::getChannelMask()
{
  if (_forced)  //  read from device.
  {
    _wire->requestFrom(_address, (uint8_t)1);
    _mask = _wire->read();
  }
  return _mask;
}


void PCA9549::setResetPin(uint8_t resetPin)
{
  _resetPin = resetPin;
  pinMode(_resetPin, OUTPUT);
  digitalWrite(_resetPin, HIGH);
}


void PCA9549::reset()
{
  digitalWrite(_resetPin, LOW);
  delayMicroseconds(1);           //  TODO datasheet page ? - 500 ns
  digitalWrite(_resetPin, HIGH);
}


void PCA9549::setForced(bool forced)
{
  _forced = forced;
};


bool PCA9549::getForced()
{
  return _forced;
};


int PCA9549::getError()
{
  int error = _error;
  _error = PCA9549_OK;
  return error;
}


//  -- END OF FILE --

