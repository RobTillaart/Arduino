//
//    FILE: LC7822.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-12-20
// VERSION: 0.2.0
// PURPOSE: Arduino library for the LC7822 8 channel analogue switch.
//     URL: https://github.com/RobTillaart/LC7822


#include "LC7822.h"


LC782X::LC782X(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin, uint8_t resetPin)
{
  _address  = 0;
  _dataPin  = dataPin;
  _clockPin = clockPin;
  _cePin    = cePin;
  _sPin     = sPin;
  _resetPin = resetPin;
  _switches = 0;  //  all off by default.
}


bool LC782X::begin(uint8_t address)
{
  _address = address;

  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
  pinMode(_clockPin, OUTPUT);
  digitalWrite(_clockPin, LOW);
  pinMode(_cePin, OUTPUT);
  digitalWrite(_cePin, LOW);
  //  optional pins.
  if (_sPin != 255)
  {
    pinMode(_sPin, OUTPUT);
    digitalWrite(_sPin, LOW);
  }
  if (_resetPin != 255)
  {
    pinMode(_resetPin, OUTPUT);
    digitalWrite(_resetPin, LOW);  //  right polarity?
  }
  return true;
}


bool LC782X::reset()
{
  if (_resetPin != 255)
  {
    digitalWrite(_resetPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(_resetPin, LOW);
    //  force all off. needed? test...
    _switches = 0;
    _updateDevice();
    return true;
  }
  return false;
}


bool LC782X::setAll(uint8_t value)
{
  _switches = value;
  _updateDevice();
  return true;
}


uint8_t LC782X::getAll()
{
  return _switches;
}


bool LC782X::setSwitch(uint8_t sw, bool val)
{
  if (sw > 7) return false;
  if (val)  //  ON
  {
    _switches |= (1 << sw);
  }
  else
  {
    _switches &= ~(1 << sw);
  }
  _updateDevice();
  return true;
}


bool LC782X::getSwitch(uint8_t sw)
{
  if (sw > 7) return false;
  return _switches & (1 << sw);
}


//////////////////////////////////////////////////
//
//  PROTECTED
//
void LC782X::_updateDevice()
{
  //  select this device only if sPin is defined.
  if (_sPin != 255) digitalWrite(_sPin, HIGH);

  //  send address == 4 bits - A0 first
  for (uint8_t mask = 0x01; mask < 0x10; mask <<= 1)
  {
    digitalWrite(_dataPin, (_address & mask));
    if (_microDelay) delayMicroseconds(_microDelay);
    digitalWrite(_clockPin, HIGH);
    if (_microDelay) delayMicroseconds(_microDelay);
    digitalWrite(_clockPin, LOW);
  }

  // send data == 8 bits - SW1 first
  if (_microDelay) delayMicroseconds(_microDelay);
  digitalWrite(_cePin, HIGH);
  if (_microDelay) delayMicroseconds(_microDelay);

  for (uint8_t mask = 0x01; mask != 0x00; mask <<= 1)
  {
    digitalWrite(_dataPin, (_switches & mask));
    if (_microDelay) delayMicroseconds(_microDelay);
    digitalWrite(_clockPin, HIGH);
    if (_microDelay) delayMicroseconds(_microDelay);
    digitalWrite(_clockPin, LOW);
  }
  digitalWrite(_cePin, LOW);

  if (_sPin != 255) digitalWrite(_sPin, LOW);
}


//////////////////////////////////////////////////
//
//  DERIVED LC7821
//
LC7821::LC7821(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin, uint8_t resetPin)
        :LC782X(dataPin, clockPin, cePin, sPin, resetPin)
{
  _address = 0x0B;
}

bool LC7821::begin(uint8_t address)
{
  if ((address != 0x0A) && (address != 0x0B)) return false;
  return LC782X::begin(address);
}


//////////////////////////////////////////////////
//
//  DERIVED LC7822
//
LC7822::LC7822(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin, uint8_t resetPin)
        :LC782X(dataPin, clockPin, cePin, sPin, resetPin)
{
  _address = 0x0D;
}

bool LC7822::begin(uint8_t address)
{
  if ((address != 0x0C) && (address != 0x0D)) return false;
  return LC782X::begin(address);
}


//////////////////////////////////////////////////
//
//  DERIVED LC7823
//
LC7823::LC7823(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin, uint8_t resetPin)
        :LC782X(dataPin, clockPin, cePin, sPin, resetPin)
{
  _address = 0x0F;
}

bool LC7823::begin(uint8_t address)
{
  if ((address != 0x0E) && (address != 0x0F)) return false;
  return LC782X::begin(address);
}


//  -- END OF FILE --

