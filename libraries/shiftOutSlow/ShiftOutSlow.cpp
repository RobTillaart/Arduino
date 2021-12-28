//
//    FILE: ShiftOutSlow.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for shiftOut with build-in delay
//    DATE: 2021-05-11
//     URL: https://github.com/RobTillaart/ShiftOutSlow
//
// HISTORY
//  0.1.0   2021-05-11  initial version
//  0.1.1   2021-08-16  add write(buffer, size) = print interface.
//                      improve delay math; update readme.md
//  0.1.2   2021-12-28  update library.json, readme, license, minor edits"


#include "ShiftOutSlow.h"


ShiftOutSlow::ShiftOutSlow(const uint8_t dataPin, const uint8_t clockPin, const uint8_t bitOrder)
{
  _clockPin = clockPin;
  _dataPin  = dataPin;
  _bitOrder = bitOrder;
  _value    = 0;
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  // https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftin/
  digitalWrite(_clockPin, LOW);  // assume rising pulses from clock
}


size_t ShiftOutSlow::write(const uint8_t data)
{
  uint8_t   val = data;
  uint16_t  d1  = _delay/2;
  uint16_t  d2  = _delay - d1;
  for (uint8_t i = 0; i < 8; ++i)
  {
    if (d1) delayMicroseconds(d1);
    if (_bitOrder == LSBFIRST) {
      digitalWrite(_dataPin, val & 0x01);
      val >>= 1;
    } else {
      digitalWrite(_dataPin, (val & 0x80) != 0);
      val <<= 1;
    }
    digitalWrite(_clockPin, HIGH);
    if (d2) delayMicroseconds(d2);
    yield();
    digitalWrite(_clockPin, LOW);
  }
  _value = data;
  return 1;
}


size_t ShiftOutSlow::write(const uint8_t *buffer, size_t size)
{
  for (uint8_t i = 0; i < size; ++i)
  {
    write(buffer[i]);
  }
  return size;
}


bool ShiftOutSlow::setBitOrder(const uint8_t bitOrder)
{
  if ((bitOrder == LSBFIRST) || (bitOrder == MSBFIRST))
  {
    _bitOrder = bitOrder;
    return true;
  };
  return false;
}


// -- END OF FILE --

