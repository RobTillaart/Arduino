#ifndef RunningMedian_h
#define RunningMedian_h
//
//    FILE: RunningMedian.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// PURPOSE: RunningMedian library for Arduino
// VERSION: 0.1.04
//     URL: http://arduino.cc/playground/Main/RunningMedian
// HISTORY: See RunningMedian.cpp
//
// Released to the public domain
//

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

#define RUNNING_MEDIAN_VERSION "0.1.04"

// should at least be 5 to be practical
#define MEDIAN_MIN_SIZE     1
#define MEDIAN_MAX_SIZE     19
#define MEDIAN_DEF_SIZE     5

// conditional compile to minimize lib
#define RUNNING_MEDIAN_ALL

class RunningMedian
{
public:
    RunningMedian(uint8_t);
    RunningMedian();

    void clear();
    void add(float);
    float getMedian();

#ifdef RUNNING_MEDIAN_ALL
    float getAverage();
    float getAverage(uint8_t);
    float getHighest();
    float getLowest();

    uint8_t getSize();
    uint8_t getCount();
#endif

protected:
    boolean _sorted;
    uint8_t _size;
    uint8_t _cnt;
    uint8_t _idx;
    float _ar[MEDIAN_MAX_SIZE];
    float _as[MEDIAN_MAX_SIZE];
    void sort();
};

#endif
// END OF FILE