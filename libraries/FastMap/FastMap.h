#pragma once
//
//    FILE: FastMap.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.2
// PURPOSE: class with fast map function - library for Arduino
//     URL: https://github.com/RobTillaart/FastMap


#include "Arduino.h"

#define FASTMAP_LIB_VERSION           (F("0.4.2"))


class FastMap
{
public:
  FastMap();

  bool init(float in_min, float in_max, float out_min, float out_max);

  float inline map (const float value)  { return _base + value * _factor; }
  float inline back (const float value) { return _backbase + value * _backfactor; }

  float constrainedMap(const float value);
  float lowerConstrainedMap(const float value);
  float upperConstrainedMap(const float value);

private:
  float _in_min, _in_max, _out_min, _out_max;
  float _factor, _base;
  float _backfactor, _backbase;
};


class FastMapDouble
{
public:
  FastMapDouble();
  bool init(double in_min, double in_max, double out_min, double out_max);

  double inline map (const double value)  { return _base + value * _factor; }
  double inline back (const double value) { return _backbase + value * _backfactor; }

  double constrainedMap(const double value);
  double lowerConstrainedMap(const double value);
  double upperConstrainedMap(const double value);

private:
  double _in_min, _in_max, _out_min, _out_max;
  double _factor, _base;
  double _backfactor, _backbase;
};


//  -- END OF FILE --

