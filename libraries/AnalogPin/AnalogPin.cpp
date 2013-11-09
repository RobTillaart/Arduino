//
//    FILE: AnalogPin.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
//    DATE: 2013-11-06
// PURPOSE: wrapper class for analogRead
//
// HISTORY:
// 0.1.00 - 2013-09-09 initial version
// 0.1.01 - 2013-11-09 added some comments
//
// Released to the public domain
//

#include "AnalogPin.h"

AnalogPin::AnalogPin(uint8_t pin)
{
    _pin = pin;
    _prevValue = analogRead(pin);
}

uint16_t AnalogPin::read(uint8_t noise)
{
    uint16_t value = analogRead(_pin);
    if (noise == 0 || abs(value - _prevValue) > noise)
    {
        _prevValue = value;
    }
    return _prevValue;
}

uint16_t AnalogPin::readSmoothed(uint8_t alpha)
{
    alpha = constrain(alpha, 0, 31);
    uint16_t value = analogRead(_pin);
    value = (alpha*_prevValue + (32-alpha)*value)/32;
    _prevValue = value;
    return value;
}

uint16_t AnalogPin::readPrevious()
{
    return _prevValue;
}
// -- END OF FILE --