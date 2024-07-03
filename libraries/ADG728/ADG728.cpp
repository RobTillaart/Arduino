//
//    FILE: ADG728.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-07-03
// PURPOSE: Arduino Library for I2C ADG728 matrix switch. 1x8 Multiplexer.
//     URL: https://github.com/RobTillaart/ADG728
//          https://www.adafruit.com/product/5899


#include "ADG728.h"


ADG728::ADG728(uint8_t deviceAddress, TwoWire *wire)
{
  _address  = deviceAddress;
  _wire     = wire;
  _mask     = 0x00;
  _resetPin = -1;
  _forced   = false;
  _error    = ADG728_OK;
  _channels = 8;
}


bool ADG728::begin(uint8_t mask)
{
  if (! isConnected()) return false;
  setChannelMask(mask);
  return true;
}


bool ADG728::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t ADG728::channelCount()
{
  return _channels;
}


bool ADG728::enableChannel(uint8_t channel)
{
  if (channel >= _channels) return false;
  return setChannelMask(_mask | (0x01 << channel));
}


bool ADG728::disableChannel(uint8_t channel)
{
  if (channel >= _channels) return false;
  return setChannelMask(_mask & ~(0x01 << channel));
}


bool ADG728::selectChannel(uint8_t channel)
{
  if (channel >= _channels) return false;
  return setChannelMask(0x01 << channel);
}


bool ADG728::isEnabled(uint8_t channel)
{
  if (channel >= _channels) return false;
  return (_mask & (0x01 << channel));
}


bool ADG728::disableAllChannels()
{
  return setChannelMask(0x00);
}


bool ADG728::setChannelMask(uint8_t mask)
{
  if ((_mask == mask) && (not _forced)) return true;
  _mask = mask;
  _wire->beginTransmission(_address);
  _wire->write(_mask);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t ADG728::getChannelMask()
{
  if (_forced)  //  read from device.
  {
    _wire->requestFrom(_address, (uint8_t)1);
    _mask = _wire->read();
  }
  return _mask;
}


void ADG728::setResetPin(uint8_t resetPin)
{
  _resetPin = resetPin;
  pinMode(_resetPin, OUTPUT);
  digitalWrite(_resetPin, HIGH);  //  page 3 HIGH is normal operation
}


void ADG728::reset()
{
  if (_resetPin != -1)
  {
    digitalWrite(_resetPin, LOW);
    delayMicroseconds(1);
    digitalWrite(_resetPin, HIGH);
  }
}


void ADG728::setForced(bool forced)
{
  _forced = forced;
}


bool ADG728::getForced()
{
  return _forced;
}


int ADG728::getError()
{
  int error = _error;
  _error = ADG728_OK;
  return error;
}


//  -- END OF FILE --

