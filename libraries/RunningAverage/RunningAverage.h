#pragma once
//
//    FILE: RunningAverage.h
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.4.2
//    DATE: 2016-dec-01
// PURPOSE: Arduino library to calculate the running average by means of a circular buffer
//     URL: https://github.com/RobTillaart/RunningAverage
//
// HISTORY: See RunningAverage.cpp


#include "Arduino.h"


#define RUNNINGAVERAGE_LIB_VERSION    (F("0.4.2"))


class RunningAverage
{
public:
  explicit RunningAverage(const uint16_t size);
  ~RunningAverage();

  void     clear();
  void     add(const float value)    { addValue(value); };
  void     addValue(const float value);
  void     fillValue(const float value, const uint16_t number);
  float    getValue(const uint16_t position);

  float    getAverage();      // iterates over all elements.
  float    getFastAverage() const;  // reuses previous calculated values.

  // return statistical characteristics of the running average
  float    getStandardDeviation() const;
  float    getStandardError() const;

  // returns min/max added to the data-set since last clear
  float    getMin() const { return _min; };
  float    getMax() const { return _max; };

  // returns min/max from the values in the internal buffer
  float    getMinInBuffer() const;
  float    getMaxInBuffer() const;

  // return true if buffer is full
  bool     bufferIsFull() const { return _count == _size; };

  float    getElement(uint16_t index) const;

  uint16_t getSize() const { return _size; }
  uint16_t getCount() const { return _count; }

  // use not all elements just a part from 0..partial-1
  // (re)setting partial will clear the internal buffer.
  void     setPartial(const uint16_t partial = 0);  // 0 ==> use all
  uint16_t getPartial()   { return _partial; };


  // get some stats from the last count additions.
  float    getAverageLast(uint16_t count);
  float    getMinInBufferLast(uint16_t count);
  float    getMaxInBufferLast(uint16_t count);


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


// -- END OF FILE --

