#pragma once
//
//    FILE: runningAngle.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Library to average angles by means of low pass filtering with wrapping.
//     URL: https://github.com/RobTillaart/runningAngle
// RELATED: https://github.com/RobTillaart/AverageAngle


#include "Arduino.h"
#include "math.h"


#define RUNNING_ANGLE_LIB_VERSION     (F("0.2.1"))


const float RA_DEFAULT_WEIGHT   = 0.80;
const float RA_MIN_WEIGHT       = 0.001;
const float RA_MAX_WEIGHT       = 1.0;


class runningAngle
{
public:
  enum AngleType { DEGREES = 0, RADIANS = 1, GRADIANS = 2 };

  runningAngle(const enum AngleType type = DEGREES);

  //  first value added will not use the weight to set the initial value.
  float   add(float angle);  //  returns new average
  void    reset();
  float   getAverage();

  bool    setWeight(float w = RA_DEFAULT_WEIGHT);
  float   getWeight();
  enum    AngleType type();

  //  reformat angle to -180..+180 (degrees) or  -PI..PI (radians)
  float   wrap(float angle);

  //  select the output
  void    setMode0();  //  -180..180
  void    setMode1();  //     0..360
  uint8_t getMode();

private:
  enum     AngleType _type;
  float    _average = 0;
  float    _weight;
  bool     _reset;
  uint16_t _mode = 0;
};


//  -- END OF FILE --

