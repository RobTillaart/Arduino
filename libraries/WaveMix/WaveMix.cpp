//
//    FILE: WaveMix.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library to mix two signals (A and B) with an adaptive weight.
//     URL: https://github.com/RobTillaart/WaveMix
//


#include "WaveMix.h"


WaveMix::WaveMix()
{
  _weight[0] = 0.5;
  _weight[1] = 0.5;
}


void WaveMix::setWeight(float weight1, float weight2)
{
  float factor = 1.0 / (weight1 + weight2);
  _weight[0] = weight1 * factor;
  _weight[1] = weight2 * factor;
}


void WaveMix::setPercentage(float percentage)
{
  _weight[0] = percentage * 0.01;
  _weight[1] = 1.0 - _weight[0];
}


float WaveMix::mix(float s1, float s2)
{
  if (_gain == 0) return 0;
  if (_weight[0] == 0) return s2 * _gain;
  if (_weight[1] == 0) return s1 * _gain;
  return ((_weight[0] * s1) + (_weight[1] * s2)) * _gain;
}


// -- END OF FILE --

