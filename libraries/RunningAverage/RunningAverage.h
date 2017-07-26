//
//    FILE: RunningAverage.h
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.2.13
//    DATE: 2016-dec-01
// PURPOSE: RunningAverage library for Arduino
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/RunningAverage
// HISTORY: See RunningAverage.cpp
//
// Released to the public domain
//
// backwards compatibility
// clr()   clear()
// add(x)  addValue(x)
// avg()   getAverage()

#ifndef RunningAverage_h
#define RunningAverage_h

#define RUNNINGAVERAGE_LIB_VERSION "0.2.13"

#include "Arduino.h"

class RunningAverage
{
public:
  RunningAverage(void);
  explicit RunningAverage(const uint8_t);
  ~RunningAverage();

  void    clear();
  void    addValue(const float);
  void    fillValue(const float, const uint8_t);

  float   getAverage() const;      // does iterate over all elements.
  float   getFastAverage() const;  // reuses previous values.

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
  bool    bufferIsFull() const { return _cnt == _size; };

  float   getElement(uint8_t idx) const;

  uint8_t getSize() const { return _size; }
  uint8_t getCount() const { return _cnt; }



protected:
  uint8_t _size;
  uint8_t _cnt;
  uint8_t _idx;
  float   _sum;
  float*  _ar;
  float   _min;
  float   _max;
};

#endif
// END OF FILE