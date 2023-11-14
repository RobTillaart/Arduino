#pragma once
//
//    FILE: moduloMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for modulo mapping
//    DATE: 2022-10-15
//     URL: https://github.com/RobTillaart/moduloMap


#include "Arduino.h"


#define MODMAP_LIB_VERSION               (F("0.1.2"))


class MODMAP
{
public:
  MODMAP()
  {
  }

  bool begin(float minimum, float maximum)
  {
    if (minimum >= maximum) return false;
    _minimum = minimum;
    _maximum = maximum;
    _range   = maximum - _minimum;
    // _factor  = 1/_range;
    return true;
  }

  float getMinimum()
  {
    return _minimum;
  }

  float getMaximum()
  {
    return _maximum;
  }

  float getRange()
  {
    return _range;
  }

  //  AVR 36 us
  float map(float value)
  {
    //  add next line if most values are in range.
    //  if ((_minimum <= value) && (value < _maximum)) return value;
    float mm = fmod((value - _minimum), _range) + _minimum;
    if (mm < _minimum) mm += _range;  //  catch rounding errors
    return mm;
  }

  //  Think of it as how many rotations must a hoist make to free a rope of given length.
  //  Or how many rotations a cylinder has to make to roll up a rope of given length.
  //  This includes the minimum that already has rolled off.
  float rotations(float value)
  {
    return (value - _minimum) / _range;
  }


///////////////////////////////////////////
//
//  develop
//

/*  slower (AVR) = manual modulo.
  //  AVR 50 us
  float map(float value)
  {
    float v = value;
    int32_t t =  (v - _minimum) * _factor;
    float mm = v - t * _range;
    if (mm < _minimum) mm += _range;
    return mm;
  }
*/


//  for debugging / reference
  //  AVR 44 us
/*
  float map(float value)
  {
    if ((_minimum <= value) && (value < _maximum)) return value;
    float mm = fmod((value - _minimum), _range) + _minimum;
    if (mm < _minimum) mm += _range;  //  catch rounding errors
    return mm;
  }
*/


private:

  float _minimum = 0;
  float _maximum = 1;  //  not needed?
  float _range   = 1;
  //  float _factor  = 1/_range;
};


//  ---  END OF FILE ---

