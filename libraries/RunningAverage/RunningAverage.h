//
//    FILE: RunningAverage.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.2.08
//    DATE: 2015-apr-10
// PURPOSE: RunningAverage library for Arduino
//     URL: http://arduino.cc/playground/Main/RunningAverage
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

#define RUNNINGAVERAGE_LIB_VERSION "0.2.08"

#include "Arduino.h"

class RunningAverage
{
public:
    RunningAverage(void);
    RunningAverage(uint8_t);
    ~RunningAverage();

    void clear();
    void addValue(double);
    void fillValue(double, uint8_t);

    double getAverage();
    // returns lowest value added to the data-set since last clear
    double getMin() { return _min; };
    // returns highest value added to the data-set since last clear
    double getMax() { return _max; };

    double getElement(uint8_t idx);
    uint8_t getSize() { return _size; }
    uint8_t getCount() { return _cnt; }

protected:
    uint8_t _size;
    uint8_t _cnt;
    uint8_t _idx;
    double _sum;
    double * _ar;
    double _min;
    double _max;
};

#endif
// END OF FILE