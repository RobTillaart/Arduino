//
//    FILE: runningAngle.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: Library to average angles by means of low pass filtering with wrapping.
//     URL: https://github.com/RobTillaart/runningAngle
// RELATED: https://github.com/RobTillaart/AverageAngle


#include "runningAngle.h"


runningAngle::runningAngle(const enum AngleType type)
{
  _type = type;
  reset();
}


void runningAngle::reset()
{
  _average = 0;
  _weight  = 0.80;
  _reset   = true;
}


float runningAngle::add(float angle)
{
  if (_reset)
  {
    _average = angle;
    _reset   = false;
  }
  else
  {
    _average = wrap(_average + _weight * wrap(angle - _average));
  }
  return _average;
}


float runningAngle::wrap(float angle)
{
  if (_type == DEGREES)
  {
    while (angle < -180) angle += 360;
    while (angle >= 180) angle -= 360;
  } 
  else if (_type == RADIANS) 
  {
    while (angle < -PI) angle += TWO_PI;
    while (angle >= PI) angle -= TWO_PI;
  }
  else  //  GRADIANS
  {
    while (angle < -200) angle += 400;
    while (angle >= 200) angle -= 400;
  }
  return angle;
}


//  -- END OF FILE --

