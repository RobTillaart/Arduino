//
//    FILE: FastShiftOut.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: shiftout that implements the Print interface
//    DATE: 2013-08-22
//     URL:
//
// Released to the public domain
//

#include "FastShiftOut.h"

//
// Constructor
// prepares the digitalWrite()
FastShiftOut::FastShiftOut(uint8_t datapin, uint8_t clockpin, uint8_t bitOrder)
{
    _bitorder = bitOrder;
    _value = -1;
    pinMode(datapin, OUTPUT);
    pinMode(clockpin, OUTPUT);
    
    // uint8_t _datatimer  = digitalPinToTimer(datapin);
    // if (_datatimer != NOT_ON_TIMER) turnOffPWM(_datatimer); TODO
	uint8_t _dataport   = digitalPinToPort(datapin);
    _dataout = portOutputRegister(_dataport);
	_databit = digitalPinToBitMask(datapin);
    
    // uint8_t _clocktimer = digitalPinToTimer(clockpin);
    // if (_clocktimer != NOT_ON_TIMER) turnOffPWM(_clocktimer);
	uint8_t _clockport  = digitalPinToPort(clockpin);
    _clockout = portOutputRegister(_clockport);
	_clockbit   = digitalPinToBitMask(clockpin);
}

//
// write() must implement the virtual write of Print class
//
size_t FastShiftOut::write(uint8_t data)
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
    return 1;
}

//
// reads back the last value written.
//
int FastShiftOut::read()
{
    return _value;
}

// -- END OF FILE --