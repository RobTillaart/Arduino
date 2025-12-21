//
//    FILE: LC7822.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-12-20
// VERSION: 0.1.0
// PURPOSE: Arduino library for the LC7822 8 channel analogue switch.
//     URL: https://github.com/RobTillaart/LC7822


#include "LC7822.h"


LC7822::LC7822(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin, uint8_t resetPin)
{
  _address  = 11;
  _dataPin  = dataPin;
  _clockPin = clockPin;
  _cePin    = cePin;
  _sPin     = sPin;
  _resetPin = resetPin;
  _switches = 0;  //  all off by default.
}


bool LC7822::begin()
{
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
  pinMode(_clockPin, OUTPUT);
  digitalWrite(_clockPin, LOW);
  pinMode(_cePin, OUTPUT);
  digitalWrite(_cePin, LOW);
  pinMode(_sPin, OUTPUT);
  digitalWrite(_sPin, LOW);

  if (_resetPin != 255)
  {
    pinMode(_resetPin, OUTPUT);
    digitalWrite(_resetPin, LOW);  //  right polarity?
  }
  return true;
}


bool LC7822::reset()
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


bool LC7822::setAll(uint8_t value)
{
  _switches = value;
  _updateDevice();
  return true;
}


uint8_t LC7822::getAll()
{
  return _switches;
}


bool LC7822::setSwitch(uint8_t sw, bool val)
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


bool LC7822::getSwitch(uint8_t sw)
{
  if (sw > 7) return false;
  return _switches & (1 << sw);
}


//////////////////////////////////////////////////
//
//  PROTECTED
//
void LC7822::_updateDevice()
{
  //  select this device
  digitalWrite(_sPin, HIGH);

  //  send address == 4 bits
  for (uint8_t mask = 0x08; mask > 0x00; mask >>= 1)
  {
    digitalWrite(_dataPin, (_address & mask));
    if (_microDelay) delayMicroseconds(_microDelay);
    digitalWrite(_clockPin, HIGH);
    if (_microDelay) delayMicroseconds(_microDelay);
    digitalWrite(_clockPin, LOW);
  }

  // send data == 8 bits
  if (_microDelay) delayMicroseconds(_microDelay);
  digitalWrite(_cePin, HIGH);
  if (_microDelay) delayMicroseconds(_microDelay);

  for (uint8_t mask = 0x80; mask > 0x00; mask >>= 1)
  {
    digitalWrite(_dataPin, (_switches & mask));
    if (_microDelay) delayMicroseconds(_microDelay);
    digitalWrite(_clockPin, HIGH);
    if (_microDelay) delayMicroseconds(_microDelay);
    digitalWrite(_clockPin, LOW);
  }
  digitalWrite(_cePin, HIGH);

  digitalWrite(_sPin, LOW);
}


//////////////////////////////////////////////////
//
//  DERIVED
//
LC7821::LC7821(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin, uint8_t resetPin)
        :LC7822(dataPin, clockPin, cePin, sPin, resetPin)
{
  _address = 13;
}


LC7823::LC7823(uint8_t dataPin, uint8_t clockPin, uint8_t cePin, uint8_t sPin, uint8_t resetPin)
        :LC7822(dataPin, clockPin, cePin, sPin, resetPin)
{
  _address = 15;
}


//  -- END OF FILE --

