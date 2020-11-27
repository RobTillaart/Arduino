//
//    FILE: AnalogPin.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.3
//    DATE: 2013-09-09
// PURPOSE: wrapper for analogRead with smoothing and noise filtering
//
// HISTORY:
// 0.1.00 - 2013-09-09 initial version
// 0.1.01 - 2013-11-09 added some comments
// 0.1.02 - 2014-10-05 changed signatures datatypes
// 0.1.03 - 2014-12-07 some refactor
// 0.1.04 - 2015-03-06 refactor smaller footprint
// 0.2.00 - 2015-05-14 added prescale support
// 0.2.01 - 2015-12-19 breaking interface; big refactor;
// 0.2.2    2020-03-25 refactor AVR specific code; bugfix
// 0.2.3    2020-05-27 update library.json
//
// Released to the public domain
//

#include "AnalogPin.h"

AnalogPin::AnalogPin(const uint8_t pin)
{
    _pin = pin;
    _prescale = 7;
    _alpha = 0;
    _noise = 0;
    rawRead();
    _prevValue = _value;
}

int AnalogPin::read(const bool twice)
{
	if (twice) rawRead();
    rawRead();
    if (_noise == 0 || ((_value - _prevValue) & 0x7FFF) > _noise)
    {
        _prevValue = _value;
    }
    return _prevValue;
}

int AnalogPin::readSmoothed()
{
    rawRead();
    if (_alpha > 0)
    {
        _value = _value + (_alpha * (_prevValue - _value)) / 32;
    }
    _prevValue = _value;
    return _value;
}

void AnalogPin::rawRead()
{
#if defined(ARDUINO_ARCH_AVR)
	// remember old register value
    uint8_t ADCSRA_TMP = ADCSRA;
    ADCSRA = (ADCSRA | 0x07) & (0xF8 | _prescale);
#elif defined(ARDUINO_ARCH_SAM)
#else
#endif	

    _value = analogRead(_pin);
	
#if defined(ARDUINO_ARCH_AVR)
	// restore register
    ADCSRA = ADCSRA_TMP;
#elif defined(ARDUINO_ARCH_SAM)
#else
#endif	
}

// -- END OF FILE --
