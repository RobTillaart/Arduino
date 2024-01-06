//
//    FILE: PinInGroup.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.10
//    DATE: 2017-04-26
// PURPOSE: PinInGroup library for Arduino
//          goal is to easily read a group of pins that logically
//          belong to each other.
//          The pins can be in any order, even duplicates are allowed.
//     URL: https://github.com/RobTillaart/PinInGroup
//          http://forum.arduino.cc/index.php?topic=469599.0


#include "PinInGroup.h"


PinInGroup::PinInGroup()
{
  clear();
}


void PinInGroup::clear()
{
  _size = 0;
}


uint8_t PinInGroup::add(uint8_t size, uint8_t * pinArray, uint8_t mode)
{
  int n = 0;
  for (uint8_t i = 0; i < size; i++)
  {
    n += add(pinArray[i], mode);
  }
  return n;
}


uint8_t PinInGroup::add(uint8_t pin, uint8_t mode)
{
  if (_size >= PININGROUP_MAXSIZE) return 0;

  _pins[_size] = pin;
  pinMode(pin, mode);
  _size++;
  return 1;
}


uint8_t PinInGroup::isInGroup(uint8_t pin)
{
  uint8_t count = 0;
  for (uint8_t i = 0; i < _size; i++)
  {
    if (_pins[i] == pin) count++;
  }
  return count;
}


uint16_t PinInGroup::read()
{
  uint16_t value = 0;
  uint16_t mask  = 0x0001;
  for (uint8_t i = 0; i < _size; i++)
  {
    if (digitalRead(_pins[i])) value |= mask;
    mask <<= 1;
  }
  return value;
}


uint16_t PinInGroup::read(uint8_t index)
{
  if (index >= _size) return 0xFFFF; // sort of error

  return (digitalRead(_pins[index])) ? 1 : 0;
}


uint8_t PinInGroup::getPin(uint8_t index)
{
  if (index >= _size) return 0xFF;
  return _pins[index];
}


uint8_t PinInGroup::getIndex(uint8_t pin)
{
  for (uint8_t i = 0; i < _size; i++)
  {
    if (_pins[i] == pin) return i;
  }
  return 0xFF;
}


//  --- END OF FILE ---

