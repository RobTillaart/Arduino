#pragma once
//
//    FILE: logistic.h
//  AUTHOR: Rob.Tillaart
// VERSION: 0.1.0
//    DATE: 2024-01-03
// PURPOSE: Arduino library to explore the logistic formula. (chaos, bifurcation)
//     URL: https://github.com/RobTillaart/Logistic


#include "Arduino.h"

#define LOGISTIC_LIB_VERSION      (F("0.1.0"))

//  https://en.wikipedia.org/wiki/Feigenbaum_constants
#define FEIGENBAUM      4.66920160910299067185320382046620161


class Logistic
{
public:
  //  rate = reproduction rate = 0.0 - 4.0
  //  in   = input population = 0.0 - 1.0
  Logistic(float rate = 2.0, float in = 0.5)
  {
    _rate = constrain(rate, 0, 4);
    _in = in;
  }

  void setRate(float rate)
  {
    _rate = constrain(rate, 0, 4);
  }
  
  float getRate()
  {
    return _rate;
  }

  float iterate(float in)
  {
    //  range check
    _in = constrain(in, 0.0, 1.0);
    _out = _rate * _in * (1.0 - _in);
    return _out;
  } 

  float iterate()
  {
    _in = _out;
    _out = _rate * _in * (1.0 - _in);
    return _out;
  }

protected:

  float _rate;
  float _in;
  float _out;
};


//  -- END OF FILE --

