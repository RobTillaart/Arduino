//
//    FILE: AnalogPin.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
//    DATE: 2014-10-05
// PURPOSE: wrapper class for analogRead
//
// HISTORY:
// 0.1.00 - 2013-09-09 initial version
// 0.1.01 - 2013-11-09 added some comments
// 0.1.02 - 2014-10-05 changed signatures datatypes
//
// Released to the public domain
//

#include "AnalogPin.h"

AnalogPin::AnalogPin(uint8_t pin)
{
    _pin = pin;
    _prevValue = analogRead(pin);
}

int AnalogPin::read(uint8_t noise)
{
    int value = analogRead(_pin);
    if (noise == 0 || abs(value - _prevValue) > noise)
    {
        _prevValue = value;
    }
    return _prevValue;
}

int AnalogPin::readSmoothed(uint8_t alpha)
{
    alpha = constrain(alpha, 0, 31);
    int value = analogRead(_pin);
    value = (alpha*_prevValue + (32-alpha)*value)/32;
    _prevValue = value;
    return value;
}

int AnalogPin::readPrevious()
{
    return _prevValue;
}
// -- END OF FILE --