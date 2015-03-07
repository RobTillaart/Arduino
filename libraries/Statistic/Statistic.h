#ifndef Statistic_h
#define Statistic_h
//
//    FILE: Statistic.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
//          modified at 0.3 by Gil Ross at physics dot org
// VERSION: 0.3.3
// PURPOSE: Recursive Statistical library for Arduino
// HISTORY: See Statistic.cpp
//
// Released to the public domain
//

// the standard deviation increases the lib (<100 bytes)
// it can be in/excluded by un/commenting next line
#define STAT_USE_STDEV

#include <math.h>

#define STATISTIC_LIB_VERSION "0.3.3"

class Statistic
{
public:
    Statistic();
    void clear();
    void add(double);

    // returns the number of values added
    unsigned long count()   { return _cnt; }; // zero if empty
    double sum()            { return _sum; }; // zero if empty
    double minimum()        { return _min; }; // zero if empty
    double maximum()        { return _max; }; // zero if empty
    double average();

#ifdef STAT_USE_STDEV
    double variance();
    double pop_stdev();	    // population stdev
    double unbiased_stdev();
#endif

protected:
    unsigned long _cnt;
    double _store;           // store to minimise computation
    double _sum;
    double _min;
    double _max;
#ifdef STAT_USE_STDEV
    double _ssqdif;		    // sum of squares difference
#endif
};

#endif
// END OF FILE