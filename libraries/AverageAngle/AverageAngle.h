#pragma once
//
//    FILE: AverageAngle.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.4
//    DATE: 2017-11-21
// PURPOSE: Arduino library to calculate correctly the average of multiple angles.
//     URL: https://github.com/RobTillaart/AverageAngle


#include "math.h"
#include "Arduino.h"

#define AVERAGE_ANGLE_LIB_VERSION             (F("0.2.4"))


constexpr float GRADIAN_TO_RADIAN = (PI / 200.0);
constexpr float DEGREES_TO_RADIAN = (PI / 180.0);
constexpr float RADIAN_TO_GRADIAN = (200.0 / PI);
constexpr float RADIAN_TO_DEGREES = (180.0 / PI);


//  to be obsolete in 0.3.0
#define GRAD_TO_RAD                           (PI / 200.0)
#define RAD_TO_GRAD                           (200.0 / PI)


#define AVERAGE_ANGLE_OK                       0
#define AVERAGE_ANGLE_OVERFLOW                -10
#define AVERAGE_ANGLE_SINGULARITY             -20


class AverageAngle
{
public:
  enum AngleType { DEGREES = 0, RADIANS = 1, GRADIANS = 2 };

  AverageAngle(const enum AngleType type = DEGREES);

  uint32_t add(float alpha, float length = 1.0f);
  void     reset();
  uint32_t count();

  //  if there are no angles added (count == 0) or
  //  if the sum == (0,0) there is a singularity ==> no angle. NAN
  float    getAverage();

  //  if count == 0  total length == 0.
  float    getTotalLength();
  //  if count == 0  average length == 0.
  float    getAverageLength();
  float    getSumX();
  float    getSumY();

  AngleType type();
  bool      setType(AngleType type);

  int       lastError();

private:
  AngleType _type;
  float     _sumX;
  float     _sumY;
  uint32_t  _count;
  int       _error;
};


//  -- END OF FILE --

