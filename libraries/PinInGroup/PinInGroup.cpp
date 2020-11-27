//
//    FILE: PinInGroup.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2017-04-26
// PURPOSE: PinInGroup library for Arduino
//          goal is to easily read a group of pins that logically
//          belong to each other.
//          The pins can be in any order.
//     URL: https://github.com/RobTillaart/PinInGroup
//          http://forum.arduino.cc/index.php?topic=469599.0
//
// 0.1.0   2017-08-20 initial version (based upon pinGroup)
// 0.1.1   2020-05-19 refactor; added clear(); 
//                    added param for INPUT or INPUT_PULLUP
// 0.1.2   2020-06-19 fix library.json

#include "PinInGroup.h"

PinInGroup::PinInGroup()
{
  clear();
}

void PinInGroup::clear()
{
  _size = 0;
}

uint8_t PinInGroup::add(uint8_t sz, uint8_t * ar, uint8_t value)
{
  int n = 0;
  for (uint8_t i = 0; i < sz; i++)
  {
    n += add(ar[i], value);
  }
  return n;
}

uint8_t PinInGroup::add(uint8_t pin, uint8_t value)
{
  if (_size >= PININGROUP_MAXSIZE) return 0;
  _pins[_size] = pin;
  pinMode(pin, value);
  _size++;
  return 1;
}

uint16_t PinInGroup::read()
{
  uint16_t value = 0;
  uint16_t mask = 0x01;
  for (uint8_t i = 0; i < _size; i++)
  {
    if (digitalRead(_pins[i])) value |= mask;
	mask <<= 1;
  }
  return value;
}

// --- END OF FILE ---
