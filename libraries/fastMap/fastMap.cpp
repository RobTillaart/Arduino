//
//    FILE: fastMap.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: class implementation of map function - library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=276194
//
// HISTORY:
// 0.1.02 squized the code (first public version)
// 0.1.01 refactor
// 0.1.00 initial version
//

#include "fastMap.h"

/////////////////////////////////////////////////////
//
// PUBLIC
//

void fastmap::init(float in_min, float in_max, float out_min, float out_max)
{
    _in_min = in_min;
    _in_max = in_max;
    _out_min = out_min;
    _out_max = out_max;
    _factor = (out_max - out_min)/(in_max - in_min);
    _base = out_min - in_min * _factor;
    //    Serial.println(_in_min);
    //    Serial.println(_in_max);
    //    Serial.println(_out_min);
    //    Serial.println(_out_max);
    //    Serial.println(_factor);
}
    
float fastmap::constrainedMap(float value)
{
    if (value <= _in_min) return _out_min;
    if (value >= _in_max) return _out_max;
    return this->map(value);
}

float fastmap::lowerConstrainedMap(float value)
{
    if (value <= _in_min) return _out_min;
    return this->map(value);
}

float fastmap::upperConstrainedMap(float value)
{
    if (value >= _in_max) return _out_max;
    return this->map(value);
}
//
// END OF FILE
//