//
//    FILE: RunningAverage.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.2.11
//    DATE: 2015-sep-04
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

#define RUNNINGAVERAGE_LIB_VERSION "0.2.11"

#include "Arduino.h"

class RunningAverage
{
public:
    RunningAverage(void);
    explicit RunningAverage(const uint8_t);
    ~RunningAverage();

    void clear();
    void addValue(const double);
    void fillValue(const double, const uint8_t);

    double getAverage() const;      // does iterate over all elements.
    double getFastAverage() const;  // reuses previous values.

    // returns min/max added to the data-set since last clear
    double getMin() const { return _min; };
    double getMax() const { return _max; };

    // returns min/max from the values in the internal buffer
    double GetMinInBuffer() const;
    double GetMaxInBuffer() const;

    double getElement(uint8_t idx) const;

    uint8_t getSize() const { return _size; }
    uint8_t getCount() const { return _cnt; }

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