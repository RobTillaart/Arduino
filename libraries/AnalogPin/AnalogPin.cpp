//
//    FILE: AnalogPin.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.04
//    DATE: 2014-10-05
// PURPOSE: wrapper class for analogRead
//
// HISTORY:
// 0.1.00 - 2013-09-09 initial version
// 0.1.01 - 2013-11-09 added some comments
// 0.1.02 - 2014-10-05 changed signatures datatypes
// 0.1.03 - 2014-12-07 some refactor
// 0.1.04 - 2015-03-06 refactor smaller footprint
//
// Released to the public domain
//

#include "AnalogPin.h"

AnalogPin::AnalogPin(const uint8_t pin)
{
    _pin = pin;
    _prevValue = analogRead(pin);
}

int AnalogPin::read(const uint8_t noise)
{
    int value = analogRead(_pin);
    if (noise == 0 || ((value - _prevValue) & 0x7FFF) > noise)
    {
        _prevValue = value;
    }
    return _prevValue;
}

int AnalogPin::readSmoothed(uint8_t alpha)
{
    if (alpha > 31) alpha = 31;
    int value = analogRead(_pin);
    if (alpha > 0)
    {
        value = value + (alpha * (_prevValue - value)) / 32;
    }
    _prevValue = value;
    return value;
}

int AnalogPin::readPrevious()
{
    return _prevValue;
}
// -- END OF FILE --