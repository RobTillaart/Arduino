//
//    FILE: FastMap.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.06
// PURPOSE: class implementation of map function - library for Arduino
//     URL: http://forum.arduino.cc/index.php?topic=276194
//
// HISTORY:
// 0.1.06 2015-03-08 replaced double by double (support ARM)
// 0.1.05 2014-11-02 stripped of bit mask experimental code
// 0.1.04 add back() - the inverse map
//        tested with bit mask for constrain code (Perfomance was killed)
// 0.1.03 proper name
// 0.1.02 squized the code (first public version)
// 0.1.01 refactor
// 0.1.00 initial version
//

#include "FastMap.h"

/////////////////////////////////////////////////////
//
// PUBLIC
//
void FastMap::init(double in_min, double in_max, double out_min, double out_max)
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

double FastMap::constrainedMap(double value)
{
    if (value <= _in_min) return _out_min;
    if (value >= _in_max) return _out_max;
    return this->map(value);
}

double FastMap::lowerConstrainedMap(double value)
{
    if (value <= _in_min) return _out_min;
    return this->map(value);
}

double FastMap::upperConstrainedMap(double value)
{
    if (value >= _in_max) return _out_max;
    return this->map(value);
}
//
// END OF FILE
//