#pragma once
//
//    FILE: moduloMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for modulo mapping
//    DATE: 2022-10-15
//     URL: https://github.com/RobTillaart/moduloMap


#include "Arduino.h"


#define MODMAP_LIB_VERSION               (F("0.1.0"))


class MODMAP
{
public:
  MODMAP()
  {
  }

  void begin(float minimum, float maximum)
  {
    _minimum = minimum;
    _maximum = maximum;
    _range   = maximum - _minimum;
  }

  float map(float value)
  {
    if ((_minimum <= value) && (value < _maximum)) return value;
    float mm = fmod((value - _minimum), _range) + _minimum;
    if (mm < _minimum) mm += _range;
    return mm;
  }

/*  for debugging
  float reference(float value)
  {
    if ((_minimum <= value) && (value < _maximum)) return value;
    float mm = fmod((value - minimum), _range) + _minimum;
    if (mm < _minimum) mm += _range;
    return mm;
  }
*/


private:

  float _minimum = 0;
  float _maximum = 1;
  float _range   = 1;
};


//  ---  END OF FILE ---

