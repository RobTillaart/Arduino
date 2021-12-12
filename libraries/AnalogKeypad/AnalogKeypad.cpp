//
//    FILE: AnalogKeypad.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2019-01-31
// PURPOSE: Class for (Robotdyn) 4x4 and 4x3 analog keypad
//
//  HISTORY:
//  0.1.0  2019-01-31  initial version
//  0.1.1  2019-02-01  add pressed() event() last()
//  0.1.2  2019-02-01  refactored rawRead(), first stable version
//  0.1.3  2020-03-25  minor refactoring
//  0.1.4  2020-05-27  update library.json
//  0.1.5  2020-12-09  add Arduino-CI
//  0.1.6  2021-05-27  fix Arduino-lint
//  0.2.0  2021-10-17  update build-CI, readme,
//                     add bits as parameter in constructor.
//  0.2.1  2021-12-12  update library.json, license
//                     add test_constants to unit test.


#include "AnalogKeypad.h"


// NOTE the MAGIC NUMBERS in rawRead() are for 8 BIT ADC
// as 8 bit compares are fast
//
// The _analogShift takes care if the ADC has more
// than e.g. 10 bits. 
//
// Arduino UNO3 build in ==>  10 bits
// Other may have 12 or even 16 bits.


AnalogKeypad::AnalogKeypad(const uint8_t pin, const uint8_t bits)
{
  _analogPin   = pin;
  _analogShift = bits - 8;
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
  if (_key == _lastKey)           // NOKEY OR REPEAT
  {
    rv = _lastKey;
  }
  else if (_key == 0 && _lastKey != 0)      // RELEASE
  {
    _lastKey = _key;
    rv = _lastKey;
  }
  else if (_key != 0 && _lastKey == 0)      // PRESS
  {
    _lastKey = _key;
    rv = _lastKey;
  }
  else if (_key != 0 && _lastKey != 0 && _key != _lastKey)  // SUPPRESS CHANGE
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


// Adjust numbers for other than 4x4 keypad
uint8_t AnalogKeypad::_rawRead()
{
  // spends most time in analogRead (UNO ~110 microseconds) 
  uint8_t val = (analogRead(_analogPin) >> _analogShift);

  // handle NOKEY first
  if (val < 57) return 0;

  // reduce average # compares by 2  (4x4 keypad)
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


// -- END OF FILE --

