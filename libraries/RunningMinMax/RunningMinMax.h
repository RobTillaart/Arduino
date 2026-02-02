#pragma once
//
//    FILE: RunningMinMax.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2026-02-01
// PURPOSE: Arduino library for a running Minimum and Maximum.
//     URL: https://github.com/RobTillaart/RunningMinMax


#include "Arduino.h"

#define RUNNING_MINMAX_LIB_VERSION        (F("0.2.0"))

const int RMM_MAX_SIZE = 250;


template <typename T=float>
class RunningMinMax
{
public:
  //  # elements in the internal buffer
  RunningMinMax(const uint8_t size)
  {
  _count = 0;
  _size = size;
  if (_size == 0) _size = 1;
  if (_size > RMM_MAX_SIZE) _size = RMM_MAX_SIZE;

  _values = (T *) malloc(_size * sizeof(T));
  }

  ~RunningMinMax()
  {
    if (_values) free(_values);
  }

  //  resets internal buffer and variables
  void reset()
  {
  _count = 0;
  _index = 0;
  }


  //  adds a new value to internal buffer, optionally replacing the oldest element.
  void add(const T value)
  {
    _values[_index++] = value;
    if (_index >= _size) _index = 0; //  wrap around
    if (_count < _size) _count++;
  }

  float getAverage()
  {
    if (_count == 0) return 0;

    float sum = 0;
    for (uint8_t i = 0; i < _count; i++)
    {
      sum += _values[i];
    }
    return sum / _count;
  }

  T getMinimum()
  {
    if (_count == 0) return 0;

    T minimum = _values[0];
    for (uint8_t i = 1; i < _count; i++)
    {
      if (_values[i] < minimum) minimum = _values[i];
    }
    return minimum;
  }

  T getMaximum()
  {
    if (_count == 0) return 0;

    T maximum = _values[0];
    for (uint8_t i = 1; i < _count; i++)
    {
      if (_values[i] > maximum) maximum = _values[i];
    }
    return maximum;
  }

  uint8_t getSize()    { return _size; };
  uint8_t getCount()   { return _count; };
  bool    isFull()     { return (_count >= _size); }
  //  bool    isEmpty()    { return (_count == 0); }

protected:
  uint8_t   _size;    //  max number of values
  uint8_t   _count;   //  current number of values <= size
  uint8_t   _index;   //  next index to add
  T       * _values;  //
};


//  -- END OF FILE --

