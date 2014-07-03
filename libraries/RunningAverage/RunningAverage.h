#ifndef RunningAverage_h
#define RunningAverage_h
//
//    FILE: RunningAverage.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// PURPOSE: RunningAverage library for Arduino
//     URL: http://arduino.cc/playground/Main/RunningAverage
// HISTORY: See RunningAverage.cpp
//
// Released to the public domain
//

// backwards compatibility
// clr() clear()
// add(x) addValue(x)
// avg() getAverage()

#define RUNNINGAVERAGE_LIB_VERSION "0.2.04"

#include "Arduino.h"

class RunningAverage
{
public:
    RunningAverage(void);
    RunningAverage(int);
    ~RunningAverage();

    void clear();
    void addValue(float);
    void fillValue(float, int);

    float getAverage();

    float getElement(uint8_t idx);
    uint8_t getSize() { return _size; }
    uint8_t getCount() { return _cnt; }

protected:
    uint8_t _size;
    uint8_t _cnt;
    uint8_t _idx;
    float   _sum;
    float * _ar;
};

#endif
// END OF FILE