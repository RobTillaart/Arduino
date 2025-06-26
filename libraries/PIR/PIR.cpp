//
//    FILE: PIR.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2022-08-13
// PURPOSE: PIR library for Arduino.
//     URL: https://github.com/RobTillaart/PIR


#include "PIR.h"


PIR::PIR()
{
  reset();
}


uint8_t PIR::add(uint8_t pin)
{
  if (_count >= PIR_MAX_COUNT) return PIR_ERR_ARRAY_FULL;
  _pins[_count++] = pin;
  pinMode(pin, INPUT_PULLUP);
  return _count - 1;
}


uint8_t PIR::add(uint8_t * pins, uint8_t length)
{
  if ((_count + length) > PIR_MAX_COUNT) return PIR_ERR_ARRAY_FULL;
  for (int i = 0; i < length; i++)
  {
    add(pins[i]);
  }
  return _count - 1;
}


void PIR::reset()
{
  for (int i = 0; i < PIR_MAX_COUNT; i++)
  {
    _pins[i] = 0;
  }
  _count     = 0;
  _lastValue = 0;
}


uint8_t PIR::count()
{
  return _count;
}


uint8_t PIR::free()
{
  return PIR_MAX_COUNT - _count;
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

