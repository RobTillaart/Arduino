#pragma once
//
//    FILE: AverageAngle.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.6
// PURPOSE: class for averaging angles.
// HISTORY: See AverageAngle.cpp
//


#include "math.h"
#include "Arduino.h"

#define AVERAGE_ANGLE_LIB_VERSION     (F("0.1.6"))

#define GRAD_TO_RAD     (PI / 200.0)
#define RAD_TO_GRAD     (200.0 / PI)


class AverageAngle
{
public:
  enum AngleType { DEGREES = 0, RADIANS = 1, GRADIANS = 2 };

  AverageAngle(const enum AngleType type = DEGREES);

  uint32_t add(float alpha, float length = 1.0);
  void     reset();
  uint32_t count() { return _count; };
  float    getAverage();

  float    getTotalLength();
  float    getAverageLength();

  AngleType type() { return _type; };
  void      setType(AngleType type) { _type = type; };


private:
  AngleType _type;
  float     _sumx;
  float     _sumy;
  uint32_t  _count;
};

// -- END OF FILE --
