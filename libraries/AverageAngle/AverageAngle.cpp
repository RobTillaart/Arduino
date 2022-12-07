//
//    FILE: AverageAngle.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.9
//    DATE: 2017-11-21
// PURPOSE: class for averaging angles
//     URL: https://github.com/RobTillaart/AverageAngle


#include "AverageAngle.h"


AverageAngle::AverageAngle(const enum AngleType type)
{
  _type = type;
  reset();
}


uint32_t AverageAngle::add(float alpha, float length)
{
  if (_type == AverageAngle::DEGREES )
  {
    alpha *= DEG_TO_RAD;              //  (PI / 180.0);
  }
  else if (_type == AverageAngle::GRADIANS )
  {
    alpha *= GRAD_TO_RAD;             //  (PI / 200.0);
  }
  _sumx += (cos(alpha) * length);
  _sumy += (sin(alpha) * length);
  _count++;
  return _count;
}


void AverageAngle::reset()
{
  _sumx = 0;
  _sumy = 0;
  _count = 0;
}


uint32_t AverageAngle::count()
{
  return _count;
};


float AverageAngle::getAverage()
{
  float angle = atan2(_sumy, _sumx);
  if (angle < 0) angle += TWO_PI;      //  (PI * 2);
  if (_type == AverageAngle::DEGREES )
  {
    angle *= RAD_TO_DEG;               //  (180.0 / PI);
  }
  else if (_type == AverageAngle::GRADIANS )
  {
    angle *= RAD_TO_GRAD;              //  (200.0 / PI);
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


AverageAngle::AngleType AverageAngle::type()
{
  return _type;
}


bool AverageAngle::setType(const enum AngleType type)
{
  if (type > GRADIANS) return false;
  _type = type;
  return true;
}


// -- END OF FILE --

