//
//    FILE: AnalogPin.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: wrapper class for analogRead
//     URL:
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
    alpha = constrain(alpha, 0, 32);
    uint16_t value = analogRead(_pin);
    value = (alpha*_prevValue + (32-alpha)*value)/32;
    _prevValue = value;
    return value;
}
// -- END OF FILE --