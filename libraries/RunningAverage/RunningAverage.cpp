//
//    FILE: RunningAverage.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.04
// PURPOSE: RunningAverage library for Arduino
//
// The library stores the last N individual values in a circular buffer,
// to calculate the running average.
//
// HISTORY:
// 0.1.00 - 2011-01-30 initial version
// 0.1.01 - 2011-02-28 fixed missing destructor in .h
// 0.2.00 - 2012-??-?? Yuval Naveh added trimValue (found on web)
//          http://stromputer.googlecode.com/svn-history/r74/trunk/Arduino/Libraries/RunningAverage/RunningAverage.cpp
// 0.2.01 - 2012-11-21 refactored
// 0.2.02 - 2012-12-30 refactored trimValue -> fillValue
// 0.2.03 - 2013-11-31 getElement
// 0.2.04 - 2014-07-03 added memory protection
//
// Released to the public domain
//

#include "RunningAverage.h"
#include <stdlib.h>

RunningAverage::RunningAverage(int n)
{
    _size = n;
    _ar = (float*) malloc(_size * sizeof(float));
    if (_ar == NULL) _size = 0;
    clear();
}

RunningAverage::~RunningAverage()
{
    if (_ar != NULL) free(_ar);
}

// resets all counters
void RunningAverage::clear()
{
    _cnt = 0;
    _idx = 0;
    _sum = 0.0;
    for (int i = 0; i< _size; i++) _ar[i] = 0.0;  // needed to keep addValue simple
}

// adds a new value to the data-set
void RunningAverage::addValue(float f)
{
    if (_ar == NULL) return;
    _sum -= _ar[_idx];
    _ar[_idx] = f;
    _sum += _ar[_idx];
    _idx++;
    if (_idx == _size) _idx = 0;  // faster than %
    if (_cnt < _size) _cnt++;
}

// returns the average of the data-set added sofar
float RunningAverage::getAverage()
{
    if (_cnt == 0) return NAN;
    return _sum / _cnt;
}

// returns the value of an element if exist, 0 otherwise
float RunningAverage::getElement(uint8_t idx)
{
    if (idx >=_cnt ) return NAN;
    return _ar[idx];
}

// fill the average with a value
// the param number determines how often value is added (weight)
// number should preferably be between 1 and size
void RunningAverage::fillValue(float value, int number)
{
    clear();
    for (int i = 0; i < number; i++)
    {
        addValue(value);
    }
}
// END OF FILE