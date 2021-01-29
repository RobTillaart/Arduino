#pragma once
//
//    FILE: RunningAverage.h
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.3.2
//    DATE: 2016-dec-01
// PURPOSE: Arduino library to calculate the running average by means of a circular buffer
//     URL: https://github.com/RobTillaart/RunningAverage
//
// HISTORY: See RunningAverage.cpp


#include "Arduino.h"


#define RUNNINGAVERAGE_LIB_VERSION    (F("0.3.2"))


class RunningAverage
{
public:
  explicit RunningAverage(const uint8_t size);
  ~RunningAverage();

  void    clear();
  void    add(const float value)    { addValue(value); };
  void    addValue(const float);
  void    fillValue(const float, const uint8_t);
  float   getValue(const uint8_t);

  float   getAverage();      // iterates over all elements.
  float   getFastAverage() const;  // reuses previous calculated values.

  // return statistical characteristics of the running average
  float   getStandardDeviation() const;
  float   getStandardError() const;

  // returns min/max added to the data-set since last clear
  float   getMin() const { return _min; };
  float   getMax() const { return _max; };

  // returns min/max from the values in the internal buffer
  float   getMinInBuffer() const;
  float   getMaxInBuffer() const;

  // return true if buffer is full
  bool    bufferIsFull() const { return _count == _size; };

  float   getElement(uint8_t idx) const;

  uint8_t getSize() const { return _size; }
  uint8_t getCount() const { return _count; }


protected:
  uint8_t _size;
  uint8_t _count;
  uint8_t _index;
  float   _sum;
  float*  _array;
  float   _min;
  float   _max;
};

// -- END OF FILE --
