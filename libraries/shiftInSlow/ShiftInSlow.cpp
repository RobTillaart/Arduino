//
//    FILE: ShiftInSlow.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: Arduino library for shiftIn with build-in delay
//    DATE: 2021-05-11
//     URL: https://github.com/RobTillaart/ShiftInSlow



#include "ShiftInSlow.h"


ShiftInSlow::ShiftInSlow(const uint8_t dataPin, const uint8_t clockPin, const uint8_t bitOrder)
{
  _clockPin = clockPin;
  _dataPin  = dataPin;
  _bitOrder = bitOrder;
  _value    = 0;
  pinMode(_dataPin, INPUT);
  pinMode(_clockPin, OUTPUT);
  //  https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftin/
  digitalWrite(_clockPin, LOW);  //  assume rising pulses from clock
}


int ShiftInSlow::read()
{
  _value = 0;
  for (uint8_t i = 0; i < 8; ++i)
  {
    digitalWrite(_clockPin, HIGH);
    if (_delay > 0) delayMicroseconds(_delay / 2);
    yield();
    if (_bitOrder == LSBFIRST)
      _value |= digitalRead(_dataPin) << i;
    else
      _value |= digitalRead(_dataPin) << (7 - i);
    digitalWrite(_clockPin, LOW);
    if (_delay > 0) delayMicroseconds(_delay / 2);
  }
  return _value;
}


int  ShiftInSlow::lastRead()
{
  return _value;
}


bool ShiftInSlow::setBitOrder(const uint8_t bitOrder)
{
  if ((bitOrder == LSBFIRST) || (bitOrder == MSBFIRST))
  {
    _bitOrder = bitOrder;
    return true;
  };
  return false;
}

uint8_t ShiftInSlow::getBitOrder()
{
  return _bitOrder;
}


void ShiftInSlow::setDelay(uint16_t microseconds)
{
  _delay = microseconds;
}


uint16_t ShiftInSlow::getDelay()
{
  return _delay;
}


//  -- END OF FILE --

