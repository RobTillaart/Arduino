//
//    FILE: FastShiftOut.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1
// PURPOSE: 
//     URL:
//
// Released to the public domain
//

#include "FastShiftOut.h"

FastShiftOut::FastShiftOut(uint8_t datapin, uint8_t clockpin, uint8_t bitOrder)
{
    _datapin = datapin;
    _clockpin = clockpin;
    _bitorder = bitOrder;
    _value = -1;
    pinMode(_datapin, OUTPUT);
    pinMode(_clockpin, OUTPUT);
    
    _datatimer  = digitalPinToTimer(_datapin);
	_databit    = digitalPinToBitMask(_datapin);
	_dataport   = digitalPinToPort(_datapin);
    // if (_datatimer != NOT_ON_TIMER) turnOffPWM(_datatimer);
    _dataout = portOutputRegister(_dataport);
    
    _clocktimer = digitalPinToTimer(_clockpin);
	_clockbit   = digitalPinToBitMask(_clockpin);
	_clockport  = digitalPinToPort(_clockpin);
    // if (_clocktimer != NOT_ON_TIMER) turnOffPWM(_clocktimer);
    _clockout = portOutputRegister(_clockport);
}

void FastShiftOut::write(uint8_t data)
{
    _value = data;
    for (uint8_t i = 0; i < 8; i++)  
    {
        uint8_t v;
        if (_bitorder == LSBFIRST)   v = !!(_value & (1 << i));
        else                        v = !!(_value & (1 << (7 - i)));
        
        uint8_t oldSREG = SREG;
        cli();
        if (v == LOW)  *_dataout &= ~_databit;
        else           *_dataout |= _databit;
        *_clockout |= _clockbit;
        *_clockout &= ~_clockbit;
        SREG = oldSREG;
    }
}

int FastShiftOut::read()
{
    return _value;
}

// -- END OF FILE --