//
//    FILE: PinInGroup.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2017-04-26
// PURPOSE: PinInGroup library for Arduino
//          goal is to easily change a group of pins that logically 
//          belong to each other.
//          The pins can be in any order.
//     URL: http://forum.arduino.cc/index.php?topic=469599.0
//
// Released to the public domain
//
// 0.1.0 - initial version (based upon pinGroup)
// 

#include "PinInGroup.h"

PinInGroup::PinInGroup()
{
  _size = 0;
}

bool PinInGroup::add(uint8_t size, int* ar)
{
  bool b = true;
  for (uint8_t i = 0; i < size; i++) 
  {
    b = b && add(ar[i]);
  }
  return b;
}

bool PinInGroup::add(uint8_t pin)
{
  if (_size < PININGROUP_MAXSIZE)
  {
    _pins[_size] = pin;
    pinMode(pin, INPUT);
    _size++;
    return true;
  }
  return false;
}

uint16_t PinInGroup::read()
{
  uint16_t value = 0;
  for (uint8_t i = 0; i < _size; i++)
  {
    value <<= 1;
    value = value | (digitalRead(_pins[i]) > 0 ? 1: 0);
  }
  return value;
}

// --- END OF FILE ---