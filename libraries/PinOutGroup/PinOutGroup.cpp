//
//    FILE: PinOutGroup.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2017-04-26
// PURPOSE: PinOutGroup library for Arduino
//          goal is to easily change a group of pins that logically 
//          belong to each other e.g. 8 data pins of a parallel printer.
//          these pins can be in any order.
//     URL: http://forum.arduino.cc/index.php?topic=469599.0
//
// Released to the public domain
//
// 0.1.0 - initial version (based upon experimental pinGroup)
// 

#include "PinOutGroup.h"

PinOutGroup::PinOutGroup()
{
  _size = 0;
}

bool PinOutGroup::add(uint8_t s, int* ar, uint8_t value) // value = HIGH LOW
{
  bool b = true;
  for (uint8_t i = 0; i < s; i++) 
  {
    b = b && add(ar[i], value);
  }
  return b;
}

bool PinOutGroup::add(uint8_t pin, uint8_t value)  // value = HIGH LOW
{
  if (_size < PINOUTGROUP_MAXSIZE)
  {
    _pins[_size] = pin;                   // BUG pin can be added multiple time.
    pinMode(pin, OUTPUT);
    digitalWrite(pin, value);
    _size++;
    return true;
  }
  return false;
}

uint8_t PinOutGroup::set(uint16_t value)
{
  uint16_t changed = _lastValue ^ value;    // detect pins that changed
  if (changed == 0) return 0;

  uint16_t bitMask = 1;
  uint8_t changeCount = 0;
  for (uint8_t i = 0; i < _size; i++)
  {
    if ((changed & bitMask) > 0) 
    {
      digitalWrite(_pins[i], (value & bitMask) > 0);
      changeCount++;
    }
    bitMask <<= 1;
  }
  _lastValue = value;
  return changeCount;
}

// --- END OF FILE ---