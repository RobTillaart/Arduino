//
//    FILE: FastMap.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.8
// PURPOSE: class with fast map function - library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=276194
//
// HISTORY:
// 0.1.8  2017-07-27 revert double to float (issue 33)
// 0.1.7  2017-04-28 cleaned up, get examples working again
// 0.1.06 2015-03-08 replaced float by float (support ARM)
// 0.1.05 2014-11-02 stripped of bit mask experimental code
// 0.1.04 add back() - the inverse map
//        tested with bit mask for constrain code (Perfomance was killed)
// 0.1.03 proper name
// 0.1.02 sqeezed the code (first public version)
// 0.1.01 refactor
// 0.1.00 initial version
//

#include "FastMap.h"

/////////////////////////////////////////////////////
//
// PUBLIC
//
FastMap::FastMap()
{
    init(0, 1, 0, 1);
}

void FastMap::init(float in_min, float in_max, float out_min, float out_max)
{
    _in_min = in_min;
    _in_max = in_max;
    _out_min = out_min;
    _out_max = out_max;

    _factor = (out_max - out_min)/(in_max - in_min);
    _base = out_min - in_min * _factor;

    _backfactor = 1/_factor;
    _backbase = in_min - out_min * _backfactor;
}

float FastMap::constrainedMap(float value)
{
    if (value <= _in_min) return _out_min;
    if (value >= _in_max) return _out_max;
    return this->map(value);
}

float FastMap::lowerConstrainedMap(float value)
{
    if (value <= _in_min) return _out_min;
    return this->map(value);
}

float FastMap::upperConstrainedMap(float value)
{
    if (value >= _in_max) return _out_max;
    return this->map(value);
}

// END OF FILE