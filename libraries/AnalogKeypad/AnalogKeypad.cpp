//
//    FILE: AnalogKeypad.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
//    DATE: 2019-01-31
// PURPOSE: Class for (Robotdyn) 4x4 and 4x3 analog keypad
//
// HISTORY:
// 0.1.0   2019-01-31  initial version
// 0.1.1   2019-02-01  add pressed() event() last()
// 0.1.2   2019-02-01  refactored rawRead(), first stable version
// 0.1.3   2020-03-25  minor refactoring
// 0.1.4   2020-05-27  update library.json
// 0.1.5   2020-12-09  add arduino-ci
// 0.1.6   2021-05-27  fix arduino-lint


#include "AnalogKeypad.h"


// NOTE the MAGIC NUMBERS in rawRead() are for 8 BIT ADC
// (8 bit compares are fast)
//
// The AKP_SHIFT takes care if the ADC generates more
// than e.g. 10 bits. Change AKP_BITS to match your 
// build in ADC.
//
// Arduino UNO3 build in ==>  10  BITS
//         so AKP_SHIFT  ==>  2
//
#define AKP_BITS    10
#define AKP_SHIFT   (AKP_BITS - 8)


AnalogKeypad::AnalogKeypad(const uint8_t pin)
{
  _pin = pin;
  _lastKey = NOKEY;
}


uint8_t AnalogKeypad::event()
{
  int rv = NOKEY;
  uint8_t _key = rawRead();

  if (_key == 0 && _lastKey == 0)         rv = NOKEY;
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

  uint8_t _key = rawRead();
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
  _lastKey = rawRead();
  return _lastKey;
}


// Adjust numbers for other than 4x4 keypad
uint8_t AnalogKeypad::rawRead()
{
  // spends most time in analogRead (uno ~110 usec) 
  uint8_t val = analogRead(_pin) >> AKP_SHIFT;

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
