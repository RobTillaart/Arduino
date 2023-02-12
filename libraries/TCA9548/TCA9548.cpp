//
//    FILE: TCA9548.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
//    DATE: 2021-03-16
// PURPOSE: Library for TCA9548 I2C multiplexer


#include "TCA9548.h"


TCA9548::TCA9548(const uint8_t deviceAddress, TwoWire *wire)
{
  _address  = deviceAddress;
  _wire     = wire;
  _mask     = 0x00;
  _resetPin = -1;
  _forced   = false;
  _error    = TCA9548_OK;
}


#if defined (ESP8266) || defined(ESP32)
bool TCA9548::begin(uint8_t dataPin, uint8_t clockPin, uint8_t mask)
{
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  setChannelMask(mask);
  return true;
}
#endif


bool TCA9548::begin(uint8_t mask)
{
  _wire->begin();
  if (! isConnected()) return false;
  setChannelMask(mask);
  return true;
}


bool TCA9548::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


bool TCA9548::isConnected(uint8_t address)
{
  _wire->beginTransmission(address);
  return ( _wire->endTransmission() == 0);
}



bool TCA9548::enableChannel(uint8_t channel)
{
  if (channel > 7) return false;
  if (!isEnabled(channel))
  {
    setChannelMask(_mask | (0x01 << channel));
  }
  return true;
}


bool TCA9548::disableChannel(uint8_t channel)
{
  if (channel > 7) return false;
  if (!isEnabled(channel))
  {
    setChannelMask(_mask & ~(0x01 << channel));
  }
  return true;
}


bool TCA9548::selectChannel(uint8_t channel)
{
  if (channel > 7) return false;
  setChannelMask(0x01 << channel);
  return true;
}


bool TCA9548::isEnabled(uint8_t channel)
{
  if (channel > 7) return false;
  return (_mask & (0x01 << channel));
}


bool TCA9548::disableAllChannels()
{
  return setChannelMask(0x00);
}


bool TCA9548::setChannelMask(uint8_t mask)
{
  if ((_mask == mask) && (! _forced)) return true;
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


//  -- END OF FILE --

