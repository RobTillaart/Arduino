//
//    FILE: WaveMix.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: WaveMix library for Arduino
//     URL: https://github.com/RobTillaart/WaveMix
//


#include "WaveMix.h"


WaveMix::WaveMix()
{
  _w1 = 0.5;
  _w2 = 0.5;
}


void WaveMix::setWeight(float w1, float w2)
{
  float t = 1.0 / (w1 + w2);
  _w1 = w1 * t;
  _w2 = w2 * t;
}


void WaveMix::setPercentage(float p)
{
  if (p > 100)    p = 100;
  else if (p < 0) p = 0;
  _w1 = p * 0.01;
  _w2 = 1.0 - _w1;
}


float WaveMix::mix(float s1, float s2)
{
  // are these optimizations efficient?
  if (_w1 == 0) return s2;
  if (_w2 == 0) return s1;
  return _w1 * s1 + _w2 * s2;
  
}


// -- END OF FILE --
