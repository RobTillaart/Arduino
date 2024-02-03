//
//    FILE: FastMap.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.2
// PURPOSE: class with fast map function - library for Arduino
//     URL: https://github.com/RobTillaart/FastMap


#include "FastMap.h"


///////////////////////////////////////////////////////////////
//
//  FASTMAP
//
FastMap::FastMap()
{
  init(0, 1, 0, 1);
}


bool FastMap::init(float in_min, float in_max, float out_min, float out_max)
{
  float _inRange = in_max - in_min;
  float _outRange = out_max - out_min;
  if ((_inRange == 0.0 ) || (_outRange == 0.0)) return false;

  _in_min = in_min;
  _in_max = in_max;
  _out_min = out_min;
  _out_max = out_max;

  _factor = _outRange/_inRange;
  _base = _out_min - _in_min * _factor;

  _backfactor = _inRange/_outRange;
  _backbase = _in_min - _out_min * _backfactor;
  return true;
}


float FastMap::constrainedMap(float value)
{
    if (value <= _in_min) return _out_min;
    if (value >= _in_max) return _out_max;
    return this->map(value);
}


float FastMap::lowerConstrainedMap(float value)
{
    if (value <= _in_min) return _out_min;
    return this->map(value);
}


float FastMap::upperConstrainedMap(float value)
{
    if (value >= _in_max) return _out_max;
    return this->map(value);
}


///////////////////////////////////////////////////////////////
//
//  FASTMAP_DOUBLE
//
FastMapDouble::FastMapDouble()
{
    init(0, 1, 0, 1);
}


bool FastMapDouble::init(double in_min, double in_max, double out_min, double out_max)
{
  double _inRange = in_max - in_min;
  double _outRange = out_max - out_min;
  if ((_inRange == 0.0 ) || (_outRange == 0.0)) return false;

  _in_min = in_min;
  _in_max = in_max;
  _out_min = out_min;
  _out_max = out_max;

  _factor = _outRange/_inRange;
  _base = _out_min - _in_min * _factor;

  _backfactor = _inRange/_outRange;
  _backbase = _in_min - _out_min * _backfactor;
  return true;
}


double FastMapDouble::constrainedMap(double value)
{
    if (value <= _in_min) return _out_min;
    if (value >= _in_max) return _out_max;
    return this->map(value);
}


double FastMapDouble::lowerConstrainedMap(double value)
{
    if (value <= _in_min) return _out_min;
    return this->map(value);
}


double FastMapDouble::upperConstrainedMap(double value)
{
    if (value >= _in_max) return _out_max;
    return this->map(value);
}


//  -- END OF FILE --

