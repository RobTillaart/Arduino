#pragma once
//
//    FILE: RunningAverage.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.6
//    DATE: 2011-01-30
// PURPOSE: Arduino library to calculate the running average by means of a circular buffer
//     URL: https://github.com/RobTillaart/RunningAverage
//
//  The library stores N individual values in a circular buffer,
//  to calculate the running average.


#include "Arduino.h"


#define RUNNINGAVERAGE_LIB_VERSION    (F("0.4.6"))


class RunningAverage
{
public:
  explicit RunningAverage(const uint16_t size);
  ~RunningAverage();

  //  return false if internal buffer not allocated.
  bool     clear();
  bool     add(const float value)    { return addValue(value); };
  bool     addValue(const float value);
  bool     fillValue(const float value, const uint16_t number);
  float    getValue(const uint16_t position);

  float    getAverage();            //  iterates over all elements.
  float    getFastAverage() const;  //  reuses previous calculated values.

  //  return statistical characteristics of the running average
  float    getStandardDeviation() const;
  float    getStandardError() const;

  //  returns min/max added to the data-set since last clear
  float    getMin() const { return _min; };
  float    getMax() const { return _max; };

  //  returns min/max/sum from the values in the internal buffer
  float    getMinInBuffer() const;
  float    getMaxInBuffer() const;
  float    getSum() const { return _sum; };

  //  return true if buffer is full
  bool     bufferIsFull() const { return _count == _size; };

  float    getElement(uint16_t index) const;

  uint16_t getSize() const { return _size; }
  uint16_t getCount() const { return _count; }

  //  use not all elements just a part from 0..partial-1
  //  (re)setting partial will clear the internal buffer.
  bool     setPartial(const uint16_t partial = 0);  //  0 ==> use all
  uint16_t getPartial()   { return _partial; };


  //  get some stats from the last count additions.
  float    getAverageLast(uint16_t count);
  float    getStandardDeviationLast(uint16_t count);
  float    getMinInBufferLast(uint16_t count);
  float    getMaxInBufferLast(uint16_t count);

  //       Experimental 0.4.3
  float    getAverageSubset(uint16_t start, uint16_t count);


protected:
  uint16_t _size;
  uint16_t _count;
  uint16_t _index;
  uint16_t _partial;
  float    _sum;
  float*   _array;
  float    _min;
  float    _max;
};


//  -- END OF FILE --

