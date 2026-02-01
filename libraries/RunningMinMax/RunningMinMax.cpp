//
//    FILE: RunningMinMax.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-02-01
// PURPOSE: Arduino library for a running Minimum and Maximum.
//     URL: https://github.com/RobTillaart/RunningMinMax


#include "RunningMinMax.h"


RunningMinMax::RunningMinMax(const uint8_t size)
{
  _count = 0;
  _size = size;
  if (_size == 0) _size = 1;
  if (_size > RMM_MAX_SIZE) _size = RMM_MAX_SIZE;

  _values = (float *) malloc(_size * sizeof(float));
}


RunningMinMax::~RunningMinMax()
{
  if (_values) free(_values);
}


//  resets all internal counters
void RunningMinMax::reset()
{
  _count = 0;
  _index = 0;
}


//  adds a new value to the data-set
//  or overwrites the oldest if full.
void RunningMinMax::add(float value)
{
  _values[_index++] = value;
  if (_index >= _size) _index = 0; //  wrap around
  if (_count < _size) _count++;
}


float RunningMinMax::getAverage()
{
  if (_count == 0) return NAN;

  float sum = 0;
  for (uint8_t i = 0; i < _count; i++)
  {
    sum += _values[i];
  }
  return sum / _count;
}


float RunningMinMax::getMinimum()
{
  if (_count == 0) return NAN;

  float minimum = _values[0];
  for (uint8_t i = 1; i < _count; i++)
  {
    if (_values[i] < minimum) minimum = _values[i];
  }
  return minimum;
}


float RunningMinMax::getMaximum()
{
  if (_count == 0) return NAN;

  float maximum = _values[0];
  for (uint8_t i = 1; i < _count; i++)
  {
    if (_values[i] > maximum) maximum = _values[i];
  }
  return maximum;
}



//  -- END OF FILE --

