//
//    FILE: PIR.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
//    DATE: 2022-08-13
// PURPOSE: PIR library for Arduino.
//     URL: https://github.com/RobTillaart/PIR


#include "PIR.h"


PIR::PIR()
{
  for (int i = 0; i < 8; i++)
  {
    _pins[i] = 0;
  }
  _count     = 0;
  _lastValue = 0;
}


uint8_t PIR::add(uint8_t pin)
{
  if (_count >= 8) return PIR_ERR_ARRAY_FULL;
  _pins[_count++] = pin;
  pinMode(pin, INPUT_PULLUP);
  return _count - 1;
}


uint8_t PIR::count()
{
  return _count;
}


uint8_t PIR::read()
{
  if (_count == 0) return 0;
  uint8_t rv = 0x00;
  int i = _count -1;
  uint8_t mask = 1 << i;
  for (; i >= 0; i--)
  {
     if (digitalRead(_pins[i]) == HIGH)
     {
       rv |= mask;
     }
     mask >>= 1;
  }
  _lastValue = rv;
  return rv;
}


uint8_t PIR::changed()
{
  uint8_t prev = _lastValue;
  read();
  return prev ^ _lastValue;
}


uint8_t PIR::read(uint8_t index)
{
  if (_count == 0)     return PIR_ERR_NO_SENSOR;
  if (_count <= index) return PIR_ERR_INDEX;
  return digitalRead(_pins[index]) == HIGH;  //  0 or 1
}


uint8_t PIR::lastValue()
{
  return _lastValue;
}


//  -- END OF FILE --

