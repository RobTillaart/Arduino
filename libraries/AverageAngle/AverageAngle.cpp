//
//    FILE: AverageAngle.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2017-11-21
// PURPOSE: Arduino library to calculate correctly the average of multiple angles.
//     URL: https://github.com/RobTillaart/AverageAngle


#include "AverageAngle.h"


const float  AA_OVERFLOW_THRESHOLD = 10000;


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
  float dx = cos(alpha);
  float dy = sin(alpha);
  if (length != 1.0)
  {
    dx *= length;
    dy *= length;
  }
  _sumx += dx;
  _sumy += dy;
  _error = AVERAGE_ANGLE_OK;
  if ((abs(_sumx) > AA_OVERFLOW_THRESHOLD) || (abs(_sumy) > AA_OVERFLOW_THRESHOLD))
  {
    _error = AVERAGE_ANGLE_OVERFLOW;
  }
  _count++;
  return _count;
}


void AverageAngle::reset()
{
  _sumx  = 0;
  _sumy  = 0;
  _count = 0;
  _error = AVERAGE_ANGLE_OK;
}


uint32_t AverageAngle::count()
{
  return _count;
}


float AverageAngle::getAverage()
{
  float angle = atan2(_sumy, _sumx);
  if (isnan(angle))
  {
    _error = AVERAGE_ANGLE_SINGULARITY;
    return angle;
  }

  _error = AVERAGE_ANGLE_OK;
  if (angle < 0)
  {
    angle += TWO_PI;                   //  (PI * 2);
  }
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


float AverageAngle::getSumX()
{
  return _sumx;
}


float AverageAngle::getSumY()
{
  return _sumy;
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


int AverageAngle::lastError()
{
  int e = _error;
  _error = AVERAGE_ANGLE_OK;
  return e;
}


//  -- END OF FILE --

