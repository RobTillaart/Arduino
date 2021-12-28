#pragma once
//
//    FILE: runningAngle.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Library to average angles by means of low pass filtering with wrapping.



#include "Arduino.h"
#include "math.h"


#define RUNNING_ANGLE_LIB_VERSION     (F("0.1.3"))


class runningAngle
{
public:
  enum AngleType { DEGREES, RADIANS };

  runningAngle(const enum AngleType type = DEGREES);

  // first value added will not use the weight to set the initial value.
  float  add(float angle);  // returns new average
  void   reset();
  float  getAverage()       { return _average; };

  void   setWeight(float w) { _weight = constrain(w, 0.001, 1); };
  float  getWeight()        { return _weight; };
  enum   AngleType type()   { return _type; };

  // reformat angle to -180..+180 (degrees) or  -PI..PI (radians)
  float  wrap(float angle);

private:
  enum     AngleType _type;
  float    _average = 0;
  float    _weight;
  bool     _reset;
};


// -- END OF FILE --

