#ifndef AVERAGEANGLE_H
#define AVERAGEANGLE_H
//
//    FILE: AverageAngle.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.2
// PURPOSE: class for averaging angles
// HISTORY: See AverageAngle.cpp
//
// Released to the public domain
//

#include <math.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define AVERAGE_ANGLE_LIB_VERSION "0.1.2"

class AverageAngle
{
public:
    enum AngleType { DEGREES, RADIANS };

    AverageAngle(const enum AngleType type = DEGREES);

    void add(float alpha, float length = 1.0);
    void reset();
    int  count() { return _count; };
    float getAverage();

    float getTotalLength();
    float getAverageLength();

    enum AngleType type() { return _type; };

private:
    enum AngleType _type;
    float _sumx;
    float _sumy;
    uint32_t _count;
};
#endif