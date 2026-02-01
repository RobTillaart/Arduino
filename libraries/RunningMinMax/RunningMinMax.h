#pragma once
//
//    FILE: RunningMinMax.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-02-01
// PURPOSE: Arduino library for a running Minimum and Maximum.
//     URL: https://github.com/RobTillaart/RunningMinMax


#include "Arduino.h"

#define RUNNING_MINMAX_LIB_VERSION        (F("0.1.0"))

const int RMM_MAX_SIZE = 250;


class RunningMinMax
{
public:
  //  # elements in the internal buffer
  explicit RunningMinMax(const uint8_t size);
  ~RunningMinMax();

  //  resets internal buffer and variables
  void    reset();
  //  adds a new value to internal buffer, optionally replacing the oldest element.
  void    add(const float value);

  float   getAverage();
  float   getMinimum();
  float   getMaximum();

  uint8_t getSize()    { return _size; };
  uint8_t getCount()   { return _count; };
  bool    isFull()     { return (_count == _size); }

protected:
  uint8_t   _size;    //  max number of values
  uint8_t   _count;   //  current number of values <= size
  uint8_t   _index;   //  next index to add
  float *   _values;  //  
};


//  -- END OF FILE --

