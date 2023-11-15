//
//    FILE: PinOutGroup.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.8
//    DATE: 2017-04-26
// PURPOSE: PinOutGroup library for Arduino
//          goal is to easily change a group of pins that logically
//          belong to each other e.g. 8 data pins of a parallel printer.
//          these pins can be in any order.
//     URL: https://github.com/RobTillaart/PinOutGroup
//          http://forum.arduino.cc/index.php?topic=469599.0


#include "PinOutGroup.h"


PinOutGroup::PinOutGroup()
{
  clear();
}


void PinOutGroup::clear()
{
  //  safety: set all to LOW before cleaning up.
  allLOW();
  _size = 0;
}


uint8_t PinOutGroup::add(uint8_t size, uint8_t* pinArray, uint8_t value)
{
  int n = 0;
  for (uint8_t i = 0; i < size; i++)
  {
    n += add(pinArray[i], value);
  }
  return n;
}


uint8_t PinOutGroup::add(uint8_t pin, uint8_t value)
{
  if (_size >= PINOUTGROUP_MAXSIZE) return 0;

  _pins[_size] = pin;
  pinMode(pin, OUTPUT);
  write(_size, value);   //  takes care of _lastValue
  _size++;
  return 1;
}


uint8_t PinOutGroup::isInGroup(uint8_t pin)
{
  uint8_t count = 0;
  for (uint8_t i = 0; i < _size; i++)
  {
    if (_pins[i] == pin) count++;
  }
  return count;
}


uint8_t PinOutGroup::write(uint16_t value)
{
  uint16_t changed = _lastValue ^ value;    //  detect pins that changed
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


uint8_t PinOutGroup::write(uint8_t index, uint8_t value)
{
  if (index >= _size) return 0;

  uint16_t mask = (1 << index);
  uint16_t lastValue = _lastValue & mask;

  if ((value > 0) == (lastValue > 0)) return 0;  //  no change

  digitalWrite(_pins[index], value);
  if (value == LOW) _lastValue &= ~mask;
  else _lastValue |= mask;

  return 1;
}


void PinOutGroup::allLOW()
{
  for (uint8_t i = 0; i < _size; i++)
  {
    digitalWrite(_pins[i], LOW);
  }
  _lastValue = 0;
}


void PinOutGroup::allHIGH()
{
  uint16_t value = 0;
  for (uint8_t i = 0; i < _size; i++)
  {
    digitalWrite(_pins[i], HIGH);
    value |= (1 << i);    //  set flags.
  }
  _lastValue = value;
}


uint8_t PinOutGroup::getPin(uint8_t index)
{
  if (index >= _size) return 0xFF;
  return _pins[index];
}


uint8_t PinOutGroup::getIndex(uint8_t pin)
{
  for (uint8_t i = 0; i < _size; i++)
  {
    if (_pins[i] == pin) return i;
  }
  return 0xFF;
}


//  -- END OF FILE --

