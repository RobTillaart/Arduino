//
//    FILE: TCA9548.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-03-16
// PURPOSE: Library for TCA9548 I2C multiplexer
//
//  HISTORY:
//  0.1.0   2021-03-16  initial version


#include "TCA9548.h"


TCA9548::TCA9548(const uint8_t deviceAddress, TwoWire *wire)
{
  _address  = deviceAddress;
  _wire     = wire;
  _mask     = 0x00;
  _resetPin = -1;
  _forced   = false;
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


bool TCA9548::isConnected(uint8_t addr)
{
  _wire->beginTransmission(addr);
  return ( _wire->endTransmission() == 0);
}



void TCA9548::enableChannel(uint8_t channel)
{
  if (isEnabled(channel)) return;
  setChannelMask(_mask | (0x01 << channel));
}


void TCA9548::disableChannel(uint8_t channel)
{
  if (!isEnabled(channel)) return;
  setChannelMask(_mask & ~(0x01 << channel));
}


void TCA9548::selectChannel(uint8_t channel)
{
  setChannelMask(0x01 << channel);
}


bool TCA9548::isEnabled(uint8_t channel)
{
  if (channel > 7) return false;
  return (_mask & (0x01 << channel));
}


void TCA9548::setChannelMask(uint8_t mask)
{
  if ((_mask == mask) && (! _forced)) return;
  _mask = mask;
  _wire->beginTransmission(_address);
  _wire->write(_mask);
  _error = _wire->endTransmission();
}


uint8_t TCA9548::getChannelMask()
{
  return _mask;
}


void TCA9548::setResetPin(uint8_t resetPin)
{
  _resetPin = resetPin;
  pinMode(_resetPin, OUTPUT);
  digitalWrite(_resetPin, LOW);  // CHECK
}


void TCA9548::reset()
{
  digitalWrite(_resetPin, HIGH);  // CHECK
  delay(1);
  digitalWrite(_resetPin, LOW);
}


int TCA9548::getError()
{
  int e = _error;
  _error = 0;
  return e;
}


// -- END OF FILE -- 


