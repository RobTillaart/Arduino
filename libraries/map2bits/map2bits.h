#pragma once
//
//    FILE: map2bits.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-01-02
// PURPOSE: Arduino library for mapping a float to a number of bits.
//     URL: https://github.com/RobTillaart/map2bits


#include "Arduino.h"


#define MAP2BITS_LIB_VERSION          (F("0.1.1"))


class map2bits
{
public:
  map2bits();

  bool     init(float inMin, float inMax, uint8_t size);

  uint32_t map(float value);
  uint16_t map16(float value);  //  slightly faster ~2.5%, max 16 bits!
  uint32_t map32(float value);  //  idem for consistency
  uint64_t map64(float value);  //  more bits possible

protected:
  uint8_t _outMax;
  //  uint32_t _maxPattern;  cache?
  float _inMin, _inMax;
  float _factor, _base;
};


//  -- END OF FILE --

