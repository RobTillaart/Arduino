//
//    FILE: map2bits.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-01-02
// PURPOSE: Arduino library for mapping a float to a number of bits.
//     URL: https://github.com/RobTillaart/map2bits


#include "map2bits.h"

#define MB_MAX_SIZE       (64)

map2bits::map2bits()
{
  init(0, 100, 10);
}


bool map2bits::init(float inMin, float inMax, uint8_t size)
{
  float _inRange = inMax - inMin;
  if ((_inRange <= 0.0 ) || (size > MB_MAX_SIZE)) return false;

  _outMax = size;
  _inMin = inMin;
  _inMax = inMax;

  _factor = _outMax /_inRange;
  _base = - _inMin * _factor;
  return true;
}

//  old API
uint32_t map2bits::map(float value)
{
  if (value <= _inMin) return 0;
  if (value >= _inMax) return (uint32_t(1) << _outMax) - uint32_t(1);

  uint8_t count = round(_base + value * _factor);
  uint32_t bits = (uint32_t(1) << count) - uint32_t(1);
  return bits;
}

uint16_t map2bits::map16(float value)
{
  if (value <= _inMin) return 0;
  if (value >= _inMax) return (uint16_t(1) << _outMax) - uint16_t(1);

  uint8_t count = round(_base + value * _factor);
  uint16_t bits = (uint16_t(1) << count) - uint16_t(1);
  return bits;
}

uint32_t map2bits::map32(float value)
{
  if (value <= _inMin) return 0;
  if (value >= _inMax) return (uint32_t(1) << _outMax) - uint32_t(1);

  uint8_t count = round(_base + value * _factor);
  uint32_t bits = (uint32_t(1) << count) - uint32_t(1);
  return bits;
}

uint64_t map2bits::map64(float value)
{
  if (value <= _inMin) return 0;
  if (value >= _inMax) return (uint64_t(1) << _outMax) - uint64_t(1);

  uint8_t count = round(_base + value * _factor);
  uint64_t bits = (uint64_t(1) << count) - uint64_t(1);
  return bits;
}


//  -- END OF FILE --

