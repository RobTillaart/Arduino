#pragma once
//
//    FILE: AverageAngle.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.4
// PURPOSE: class for averaging angles
// HISTORY: See AverageAngle.cpp
//

#include "math.h"
#include "Arduino.h"

#define AVERAGE_ANGLE_LIB_VERSION "0.1.4"

class AverageAngle
{
public:
    enum AngleType { DEGREES, RADIANS };

    AverageAngle(const enum AngleType type = DEGREES);

    void 	 add(float alpha, float length = 1.0);
    void 	 reset();
    uint32_t count() { return _count; };
    float    getAverage();

    float    getTotalLength();
    float    getAverageLength();

    enum     AngleType type() { return _type; };

private:
    enum AngleType _type;
    float _sumx;
    float _sumy;
    uint32_t _count;
};

// -- END OF FILE --
