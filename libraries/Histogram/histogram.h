#ifndef Histogram_h
#define Histogram_h
//
//    FILE: Histogram.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: Histogram library for Arduino
//    DATE: 2012-11-10
//
// Released to the public domain
//

#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define HISTOGRAM_LIB_VERSION "0.1.03"

class Histogram
{
public:
    Histogram(int len, double *bounds);
    ~Histogram();

    void clear();
    void add(double val);
    void sub(double val);

    uint8_t size();
    unsigned long count();
    long bucket(uint8_t idx);

    double frequency(uint8_t idx);
    double PMF(double val);
    double CDF(double val);
    double VAL(double prob);
    uint8_t find(double f);
    // void strategy();

protected:
    double * _bounds;
    long * _data;
    uint8_t _len;
    unsigned long _cnt;
};

#endif
// END OF FILE