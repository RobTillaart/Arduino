//
//    FILE: TCA9548.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2021-03-16
// PURPOSE: Arduino Library for TCA9548 I2C multiplexer and compatibles.


#include "TCA9548.h"


TCA9548::TCA9548(uint8_t deviceAddress, TwoWire *wire)
{
  _address  = deviceAddress;
  _wire     = wire;
  _mask     = 0x00;
  _resetPin = -1;
  _forced   = false;
  _error    = TCA9548_OK;
  _channels = 8;
}


bool TCA9548::begin(uint8_t mask)
{
  if (! isConnected()) return false;
  setChannelMask(mask);
  return true;
}


bool TCA9548::isConnected()
{
  return isConnected(_address);
}


bool TCA9548::isConnected(uint8_t address)
{
  _wire->beginTransmission(address);
  return ( _wire->endTransmission() == 0);
}


bool TCA9548::isConnected(uint8_t address, uint8_t channel)
{
  if (!selectChannel(channel)) return false;
  return isConnected(address);
}


uint8_t TCA9548::find(uint8_t address)
{
  uint8_t mask = 0x00;
  for (uint8_t ch = 0; ch < _channels; ch++)
  {
    //  will work partially if MP is off line (by choice).
    selectChannel(ch);
    if (isConnected(address)) mask |= (1 << ch);
  }
  return mask;
}


uint8_t TCA9548::channelCount()
{
  return _channels;
}


bool TCA9548::enableChannel(uint8_t channel)
{
  if (channel >= _channels) return false;
  return setChannelMask(_mask | (0x01 << channel));
}


bool TCA9548::disableChannel(uint8_t channel)
{
  if (channel >= _channels) return false;
  return setChannelMask(_mask & ~(0x01 << channel));
}


bool TCA9548::selectChannel(uint8_t channel)
{
  if (channel >= _channels) return false;
  return setChannelMask(0x01 << channel);
}


bool TCA9548::isEnabled(uint8_t channel)
{
  if (channel >= _channels) return false;
  return (_mask & (0x01 << channel));
}


bool TCA9548::disableAllChannels()
{
  return setChannelMask(0x00);
}


bool TCA9548::setChannelMask(uint8_t mask)
{
  if ((_mask == mask) && (not _forced)) return true;
  _mask = mask;
  _wire->beginTransmission(_address);
  _wire->write(_mask);
  _error = _wire->endTransmission();
  return (_error == 0);
}


uint8_t TCA9548::getChannelMask()
{
  if (_forced)  //  read from device.
  {
    _wire->requestFrom(_address, (uint8_t)1);
    _mask = _wire->read();
  }
  return _mask;
}


void TCA9548::setResetPin(uint8_t resetPin)
{
  _resetPin = resetPin;
  pinMode(_resetPin, OUTPUT);
  digitalWrite(_resetPin, HIGH);  //  page 3 HIGH is normal operation
}


void TCA9548::reset()
{
  digitalWrite(_resetPin, LOW);
  delayMicroseconds(1);           //  datasheet page 6 & 7 - 500 ns
  digitalWrite(_resetPin, HIGH);
}


void TCA9548::setForced(bool forced)
{
  _forced = forced;
};


bool TCA9548::getForced()
{
  return _forced;
};


int TCA9548::getError()
{
  int error = _error;
  _error = TCA9548_OK;
  return error;
}


/////////////////////////////////////////////////////////////
//
//  PCA9548
//
PCA9548::PCA9548(uint8_t deviceAddress, TwoWire *wire) : TCA9548(deviceAddress, wire)
{
  _channels = 8;
}


/////////////////////////////////////////////////////////////
//
//  PCA9546
//
PCA9546::PCA9546(uint8_t deviceAddress, TwoWire *wire) : TCA9548(deviceAddress, wire)
{
  _channels = 4;
}

uint8_t PCA9546::getChannelMask()
{
  if (_forced)  //  read from device.
  {
    _wire->requestFrom(_address, (uint8_t)1);
    _mask = _wire->read();
  }
  return _mask &= 0x0F;
}


/////////////////////////////////////////////////////////////
//
//  PCA9545
//
PCA9545::PCA9545(uint8_t deviceAddress, TwoWire *wire) : TCA9548(deviceAddress, wire)
{
  _channels = 4;
}

uint8_t PCA9545::getChannelMask()
{
  if (_forced)  //  read from device.
  {
    _wire->requestFrom(_address, (uint8_t)1);
    _mask = _wire->read();
  }
  return _mask &= 0x0F;
}

uint8_t PCA9545::getInterruptMask()
{
  _wire->requestFrom(_address, (uint8_t)1);
  uint8_t mask = _wire->read();
  mask >>= 4;
  return mask;
}


/////////////////////////////////////////////////////////////
//
//  PCA9548
//
PCA9543::PCA9543(uint8_t deviceAddress, TwoWire *wire) : TCA9548(deviceAddress, wire)
{
  _channels = 2;
}

uint8_t PCA9543::getChannelMask()
{
  if (_forced)  //  read from device.
  {
    _wire->requestFrom(_address, (uint8_t)1);
    _mask = _wire->read();
  }
  return _mask &= 0x03;
}

uint8_t PCA9543::getInterruptMask()
{
  _wire->requestFrom(_address, (uint8_t)1);
  uint8_t mask = _wire->read();
  mask >>= 4;
  return mask;
}


//  -- END OF FILE --

