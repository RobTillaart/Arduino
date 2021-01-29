#pragma once
//
//    FILE: Statistic.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
//          modified at 0.3 by Gil Ross at physics dot org
// VERSION: 0.4.3
// PURPOSE: Recursive Statistical library for Arduino
// HISTORY: See Statistic.cpp
//


#include <Arduino.h>
#include <math.h>


#define STATISTIC_LIB_VERSION       (F("0.4.3"))

class Statistic
{
public:
  Statistic(bool useStdDev = true);                // "switches on/off" stdev run time
  void     clear(bool useStdDev = true);           // "switches on/off" stdev run time
  float    add(const float);                       // returns value actually added


  // returns the number of values added
  uint32_t count() const   { return _cnt; };       // zero if count == zero
  float    sum() const     { return _sum; };       // zero if count == zero
  float    minimum() const { return _min; };       // zero if count == zero
  float    maximum() const { return _max; };       // zero if count == zero
  float    average() const;                        // NAN  if count == zero


  // useStdDev must be true to use next three
  float    variance() const;                       // NAN if count == zero
  float    pop_stdev() const; // population stdev  // NAN if count == zero
  float    unbiased_stdev() const;                 // NAN if count == zero


protected:
  uint32_t _cnt;
  float    _sum;
  float    _min;
  float    _max;
  bool     _useStdDev;
  float    _ssqdif;    // sum of squares difference

};

// -- END OF FILE -- 
