//
//    FILE: MAX31855.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: MAX31855 - Thermocouple
//    DATE: 2014-01-01
//     URL:
//
// Released to the public domain
//

#include "MAX31855.h"

MAX31855::MAX31855(uint8_t sclk, uint8_t cs, uint8_t miso)
{
    _sclk = sclk;
    _cs = cs;
    _miso = miso;
}

void MAX31855::begin()
{
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);

    pinMode(_sclk, OUTPUT);
    pinMode(_miso, INPUT);
}

uint8_t MAX31855::read()
{
    uint32_t value = _read();

    // process status bit 0-2
    _status = value & 0x0007;
    value >>= 3;

    // reserved bit 3
    value >>= 1;

    // process internal bit 4-15
    _internal = (value & 0x07FF) * 0.0625;
    if (value & 0x0800) _internal *= -1;
    value >>= 12;

    // Fault bit ignored as we have the 3 status bits
    // _fault = value & 0x01;
    value >>= 1;

    // reserved bit 17
    value >>= 1;

    // process temperature bit 18-31
    _temperature = (value & 0x1FFF) * 0.25;
    if (value & 0x2000) _temperature *= -1;

    return _status;
}

uint32_t MAX31855::_read(void)
{
    uint32_t value = 0;

    digitalWrite(_cs, LOW);

    for (int8_t i = 31; i >= 0; i--)
    {
        value <<= 1;
        digitalWrite(_sclk, LOW);
        if ( digitalRead(_miso) ) value += 1;
        digitalWrite(_sclk, HIGH);
    }

    digitalWrite(_cs, HIGH);

    return value;
}

// END OF FILE
