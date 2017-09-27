#ifndef Statistic_h
#define Statistic_h
//
//    FILE: Statistic.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
//          modified at 0.3 by Gil Ross at physics dot org
// VERSION: 0.3.5
// PURPOSE: Recursive Statistical library for Arduino
// HISTORY: See Statistic.cpp
//
// Released to the public domain
//

// the standard deviation increases the lib (<100 bytes)
// it can be in/excluded by un/commenting next line  (compile time)
#define STAT_USE_STDEV 1

#include <Arduino.h>
#include <math.h>

#define STATISTIC_LIB_VERSION "0.3.5"

class Statistic
{
public:
    Statistic();             // "switches on/off" stdev run time
    void clear();            // "switches on/off" stdev run time
    void add(const float);

    // returns the number of values added
    uint32_t count() const { return _cnt; }; // zero if empty
    float sum() const      { return _sum; }; // zero if empty
    float minimum() const  { return _min; }; // zero if empty
    float maximum() const  { return _max; }; // zero if empty
    float average() const;                   // NAN if empty

#ifdef STAT_USE_STDEV
    float variance() const;                  // NAN if empty
    float pop_stdev() const; // population stdev  // NAN if empty
    float unbiased_stdev() const;            // NAN if empty
#endif

protected:
    uint32_t _cnt;
    float    _sum;
    float    _min;
    float    _max;
#ifdef STAT_USE_STDEV
    float    _ssqdif;		    // sum of squares difference
#endif
};

#endif
// END OF FILE