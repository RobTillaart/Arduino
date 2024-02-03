#pragma once
//
//    FILE: map2bits.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for mapping a float to a number of bits.
//     URL: https://github.com/RobTillaart/map2bits


#include "Arduino.h"


#define MAP2BITS_LIB_VERSION          (F("0.1.0"))


class map2bits
{
  public:
    map2bits();

    bool     init(float in_min, float in_max, uint8_t size);
    uint32_t map(float value);

  protected:
    uint8_t _outMax;
    float _in_min, _in_max;
    float _factor, _base;
};


//  -- END OF FILE --

