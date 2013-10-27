#ifndef RunningMedian_h
#define RunningMedian_h
//
//    FILE: RunningMedian.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// PURPOSE: RunningMedian library for Arduino
// VERSION: 0.1.08
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

#define RUNNING_MEDIAN_VERSION "0.1.08"

// prepare for dynamic version
// not tested use at own risk :)
// #define RUNNING_MEDIAN_USE_MALLOC

// conditional compile to minimize lib
// by removeing a lot of functions.
#define RUNNING_MEDIAN_ALL


// should at least be 5 to be practical
// odd size results in a 'real' middle element.
// even size takes the lower of the two middle elements (TODO)
#define MEDIAN_MIN_SIZE     1
#define MEDIAN_MAX_SIZE     19          // adjust if needed


class RunningMedian
{
public:
    RunningMedian(uint8_t size);        // # elements in the internal buffer
    ~RunningMedian();                   // destructor

    void clear();                       // resets internal buffer and var
    void add(float value);              // adds a new value to internal buffer, optionally replacing the oldest element.
    float getMedian();                  // returns the median == middle element

#ifdef RUNNING_MEDIAN_ALL
    float getAverage();                 // returns average of the values in the internal buffer
    float getAverage(uint8_t nMedian);  // returns average of the middle nMedian values, removes noise from outliers
    float getHighest();                 // returns highest element
    float getLowest();                  // return lowest element

    float getElement(uint8_t n);        // get n'th element from the values in time order
    float getSortedElement(uint8_t n);  // get n'th element from the values in size order
    float predict(uint8_t n);           // predict the max change of median after n additions

    uint8_t getSize();                  // returns size of internal buffer
    uint8_t getCount();                 // returns current used elements, getCount() <= getSize()
#endif

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

#endif
// END OF FILE