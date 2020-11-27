#pragma once
//
//    FILE: RunningMedian.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// PURPOSE: RunningMedian library for Arduino
// VERSION: 0.2.1
//     URL: https://github.com/RobTillaart/RunningMedian
//     URL: http://arduino.cc/playground/Main/RunningMedian
// HISTORY: See RunningMedian.cpp
//

#include "Arduino.h"

#define RUNNING_MEDIAN_VERSION "0.2.1"

// prepare for dynamic version
// not tested ==> use at own risk :)
#define RUNNING_MEDIAN_USE_MALLOC


// should at least be 5 to be practical,
// odd sizes results in a 'real' middle element and will be a bit faster.
// even sizes takes the average of the two middle elements as median
#define MEDIAN_MIN_SIZE     5
#define MEDIAN_MAX_SIZE     19


class RunningMedian
{
public:
  // # elements in the internal buffer
  explicit RunningMedian(const uint8_t size);
  ~RunningMedian();

  // resets internal buffer and var
  void clear();
  // adds a new value to internal buffer, optionally replacing the oldest element.
  void add(const float value);
  // returns the median == middle element
  float getMedian();
  
  // returns the Quantile
  float getQuantile(const float q);

  // returns average of the values in the internal buffer
  float getAverage();
  // returns average of the middle nMedian values, removes noise from outliers
  float getAverage(uint8_t nMedian);

  float getHighest() { return getSortedElement(_cnt - 1); };
  float getLowest()  { return getSortedElement(0); };

  // get n'th element from the values in time order
  float getElement(const uint8_t n);
  // get n'th element from the values in size order
  float getSortedElement(const uint8_t n);
  // predict the max change of median after n additions
  float predict(const uint8_t n);

  uint8_t getSize() { return _size; };
  // returns current used elements, getCount() <= getSize()
  uint8_t getCount() { return _cnt; };


protected:
  boolean _sorted;
  uint8_t _size;
  uint8_t _cnt;
  uint8_t _idx;

#ifdef RUNNING_MEDIAN_USE_MALLOC
  float * _ar;
  uint8_t * _p;
#else
  float _ar[MEDIAN_MAX_SIZE];
  uint8_t _p[MEDIAN_MAX_SIZE];
#endif
  void sort();
};

// END OF FILE