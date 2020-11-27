//
//    FILE: PinOutGroup.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2017-04-26
// PURPOSE: PinOutGroup library for Arduino
//          goal is to easily change a group of pins that logically
//          belong to each other e.g. 8 data pins of a parallel printer.
//          these pins can be in any order.
//     URL:
//          http://forum.arduino.cc/index.php?topic=469599.0
//

// 0.1.0 - 20-08-2017 initial version (based upon experimental pinGroup)
// 0.1.1 - 2020-05-19 main refactor;
//         added tests; added clear(); added write(idx, value)
//         renamed set to write() to be in line with digitalWrite()
// 0.1.2   2020-06-19 fix library.json
//

#include "PinOutGroup.h"

PinOutGroup::PinOutGroup()
{
  clear();
}

void PinOutGroup::clear()
{
  // safety: set all to LOW before cleaning up.
  for (uint8_t i = 0; i < _size; i++) digitalWrite(_pins[i], LOW);
  _size = 0;
}

bool PinOutGroup::add(uint8_t sz, uint8_t* ar, uint8_t value)
{
  bool b = true;
  for (uint8_t i = 0; i < sz && b; i++)
  {
    b = b && add(ar[i], value);
  }
  return b;
}

bool PinOutGroup::add(uint8_t pin, uint8_t value)
{
  if (_size >= PINOUTGROUP_MAXSIZE) return false;

  _pins[_size] = pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, value);
  _size++;
  return true;
}

uint8_t PinOutGroup::write(uint16_t value)
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
	
uint8_t PinOutGroup::write(uint8_t idx, uint8_t value)
{
  if (idx >= _size) return 0;
  uint16_t mask = (1 << idx);
  uint16_t lv = _lastValue & mask;

  if ((value > 0) == (lv > 0)) return 0;  // no change

  digitalWrite(_pins[idx], value);
  if (value == LOW) _lastValue &= ~mask;
  else _lastValue |= mask;
  return 1;
}

// --- END OF FILE ---
