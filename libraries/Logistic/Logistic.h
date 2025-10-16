#pragma once
//
//    FILE: logistic.h
//  AUTHOR: Rob.Tillaart
// VERSION: 0.2.0
//    DATE: 2024-01-03
// PURPOSE: Arduino library to explore the logistic formula. (chaos, bifurcation)
//     URL: https://github.com/RobTillaart/Logistic


#include "Arduino.h"

#define LOGISTIC_LIB_VERSION      (F("0.2.0"))

//  https://en.wikipedia.org/wiki/Feigenbaum_constants
const double FEIGENBAUM = 4.66920160910299067185320382046620161;


class Logistic
{
public:
  //  rate = reproduction rate = 0.0 - 4.0
  //  in   = input population = 0.0 - 1.0
  Logistic(double rate = 2.0, double in = 0.5)
  {
    _rate = constrain(rate, 0, 4);
    _in = in;
    _count = 0;
  }

  void setRate(double rate)
  {
    _rate = constrain(rate, 0, 4);
  }

  double getRate()
  {
    return _rate;
  }

  double iterate(double in)
  {
    //  range check
    _out = constrain(in, 0.0, 1.0);
    return iterate();
  }

  double iterate()
  {
    _count++;
    _in = _out;
    _previous = _in;
    _out = _rate * _in * (1.0 - _in);
    return _out;
  }


  void setCount(uint32_t count = 0)
  {
    _count = count;
  }

  uint32_t getCount()
  {
    return _count;
  }

  //  0.2.0
  double getDelta()
  {
    return _out - _previous;
  }

  double getPrevious()
  {
    return _previous;
  }

  bool isStable(double epsilon = 0.0)
  {
    return getDelta() < epsilon;
  }

protected:

  double   _rate;
  double   _in;
  double   _out;
  double   _previous;
  uint32_t _count;
};


//  -- END OF FILE --

