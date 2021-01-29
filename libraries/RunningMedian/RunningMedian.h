#pragma once
//
//    FILE: RunningMedian.h
//  AUTHOR: Rob Tillaart
// PURPOSE: RunningMedian library for Arduino
// VERSION: 0.3.3
//     URL: https://github.com/RobTillaart/RunningMedian
//     URL: http://arduino.cc/playground/Main/RunningMedian
// HISTORY: See RunningMedian.cpp
//


#include "Arduino.h"

#define RUNNING_MEDIAN_VERSION        (F("0.3.3"))


// fall back to fixed storage for dynamic version => remove true
#define RUNNING_MEDIAN_USE_MALLOC     true


// MEDIAN_MIN_SIZE  should at least be 3 to be practical,
#define MEDIAN_MIN_SIZE               3


#ifdef RUNNING_MEDIAN_USE_MALLOC
// max 250 to not overflow uint8_t internal vars
#define MEDIAN_MAX_SIZE               255
#else
// using fixed memory will be limited to 19 elements.
#define MEDIAN_MAX_SIZE               19
#endif


class RunningMedian
{
public:
  // # elements in the internal buffer
  // odd sizes results in a 'real' middle element and will be a bit faster.
  // even sizes takes the average of the two middle elements as median
  explicit RunningMedian(const uint8_t size);
  ~RunningMedian();

  // resets internal buffer and var
  void    clear();
  // adds a new value to internal buffer, optionally replacing the oldest element.
  void    add(const float value);
  // returns the median == middle element
  float   getMedian();
  
  // returns the Quantile
  float   getQuantile(const float q);

  // returns average of the values in the internal buffer
  float   getAverage();
  // returns average of the middle nMedian values, removes noise from outliers
  float   getAverage(uint8_t nMedian);

  float   getHighest() { return getSortedElement(_count - 1); };
  float   getLowest()  { return getSortedElement(0); };

  // get n'th element from the values in time order
  float   getElement(const uint8_t n);
  // get n'th element from the values in size order
  float   getSortedElement(const uint8_t n);
  // predict the max change of median after n additions
  float   predict(const uint8_t n);

  uint8_t getSize()    { return _size; };
  // returns current used elements, getCount() <= getSize()
  uint8_t getCount()   { return _count; };
  bool    isFull()     { return (_count == _size); }


protected:
  boolean   _sorted;    // _sortIdx{} is up to date
  uint8_t   _size;      // max number of values
  uint8_t   _count;     // current number of values
  uint8_t   _index;     // next index to add.


  // _values holds the elements themself
  // _p  holds the index for sorted 
#ifdef RUNNING_MEDIAN_USE_MALLOC
  float *   _values;
  uint8_t * _sortIdx;
#else
  float   _values[MEDIAN_MAX_SIZE];
  uint8_t _p[MEDIAN_MAX_SIZE];
#endif
  void sort();
};

// END OF FILE