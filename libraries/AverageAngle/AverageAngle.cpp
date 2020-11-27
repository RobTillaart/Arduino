//
//    FILE: AverageAngle.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: class for averaging angles
//     URL: https://github.com/RobTillaart/AverageAngle
//
// HISTORY:
//
// 0.1.0 2017-11-21 initial version
// 0.1.1 2017-12-09 fixed negative values of average
// 0.1.2 2018-03-30 added getAverageLength, getTotalLength + zero-test
// 0.1.3 2020-03-26 #pragma once; removed pre 1.00 support; readme.md
// 0.1.4 2020-05-27 update library.json

#include "AverageAngle.h"


AverageAngle::AverageAngle(const enum AngleType type)
{
  _type = type;
  reset();
}

void AverageAngle::add(float alpha, float length)
{
  if (_type == AverageAngle::DEGREES )
  {
    alpha *= DEG_TO_RAD; 				// (PI / 180.0);
  }
  _sumx += (cos(alpha) * length);
  _sumy += (sin(alpha) * length);
  _count++;
}

void AverageAngle::reset()
{
  _sumx = 0;
  _sumy = 0;
  _count = 0;
}

float AverageAngle::getAverage()
{
  float angle = atan2(_sumy, _sumx);
  if (angle < 0) angle += TWO_PI;		//	(PI * 2);
  if (_type == AverageAngle::DEGREES )
  {
    angle *=  RAD_TO_DEG; 				// (180.0 / PI);
  }
  return angle;
}

float AverageAngle::getTotalLength()
{
  if (_count == 0) return 0;
  return hypot(_sumy, _sumx);
}

float AverageAngle::getAverageLength()
{
  if (_count == 0) return 0;
  return hypot(_sumy, _sumx) / _count;
}

// -- END OF FILE --
