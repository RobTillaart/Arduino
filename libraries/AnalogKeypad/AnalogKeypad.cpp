//
//    FILE: AnalogKeypad.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.5
//    DATE: 2019-01-31
// PURPOSE: Class for (Robotdyn) 4x4 and 4x3 analog keypad


#include "AnalogKeypad.h"


//  NOTE the MAGIC NUMBERS in rawRead() are for 8 BIT ADC
//  as 8 bit compares are fast
//
//  The _analogShift takes care if the ADC has more
//  than e.g. 10 bits.
//
//  Arduino UNO3 build in ==>  10 bits
//  Other may have 12 or even 16 bits.


AnalogKeypad::AnalogKeypad(const uint8_t analogPin, const uint8_t bitsADC)
{
  _analogPin   = analogPin;
  _analogShift = bitsADC - 8;
  _lastKey     = NOKEY;
}


uint8_t AnalogKeypad::event()
{
  int rv = NOKEY;
  uint8_t _key = _rawRead();

  if      (_key == 0 && _lastKey == 0)    rv = NOKEY;
  else if (_key != 0 && _lastKey == 0)    rv = PRESSED;
  else if (_key == 0 && _lastKey != 0)    rv = RELEASED;
  else if (_key != 0 && _lastKey != 0 && _key == _lastKey)  rv = REPEATED;
  else if (_key != 0 && _lastKey != 0 && _key != _lastKey)  rv = CHANGED;

  _lastKey = _key;

  return rv;
}


uint8_t AnalogKeypad::pressed()
{
  int rv = NOKEY;

  uint8_t _key = _rawRead();
  if (_key == _lastKey)           //  NOKEY OR REPEAT
  {
    rv = _lastKey;
  }
  else if (_key == 0 && _lastKey != 0)      //  RELEASE
  {
    _lastKey = _key;
    rv = _lastKey;
  }
  else if (_key != 0 && _lastKey == 0)      //  PRESS
  {
    _lastKey = _key;
    rv = _lastKey;
  }
  else if (_key != 0 && _lastKey != 0 && _key != _lastKey)  //  SUPPRESS CHANGE
  {
    rv = _lastKey;
  }

  return rv;
}


uint8_t AnalogKeypad::read()
{
  _lastKey = _rawRead();
  return _lastKey;
}


//  Adjust numbers for other than 4x4 keypad
uint8_t AnalogKeypad::_rawRead()
{
  //  spends most time in analogRead (UNO ~110 microseconds)
  uint8_t val = (analogRead(_analogPin) >> _analogShift);

  //  handle NOKEY first
  if (val < 57) return 0;

  //  reduce average # compares by 2  (4x4 keypad)
  if (val < 135)
  {
    if (val < 62) return 16;
    if (val < 75) return 15;
    if (val < 92) return 14;
    if (val < 106) return 13;
    if (val < 113) return 12;
    if (val < 119) return 11;
    if (val < 125) return 10;
    return 9;
  }
  if (val < 146) return 8;
  if (val < 155) return 7;
  if (val < 165) return 6;
  if (val < 187) return 5;
  if (val < 205) return 4;
  if (val < 222) return 3;
  if (val < 244) return 2;
  return 1;
}


uint8_t AnalogKeypad::key()
{
  return _lastKey;
}


//  -- END OF FILE --

