//
//    FILE: FastShiftIn.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: shiftin
//    DATE: 2013-09-29
//     URL:
//
// Released to the public domain
//

#include "FastShiftIn.h"

FastShiftIn::FastShiftIn(uint8_t datapin, uint8_t clockpin, uint8_t bitOrder)
{
    _bitorder = bitOrder;
    _value = -1;
    pinMode(datapin, INPUT);
    pinMode(clockpin, INPUT);
    
    // uint8_t _datatimer  = digitalPinToTimer(datapin);
    // if (_datatimer != NOT_ON_TIMER) turnOffPWM(_datatimer); TODO
	uint8_t _dataport   = digitalPinToPort(datapin);
    _datain = portOutputRegister(_dataport);
	_databit = digitalPinToBitMask(datapin);
    
    // uint8_t _clocktimer = digitalPinToTimer(clockpin);
    // if (_clocktimer != NOT_ON_TIMER) turnOffPWM(_clocktimer);
	uint8_t _clockport  = digitalPinToPort(clockpin);
    _clockin = portOutputRegister(_clockport);
	_clockbit = digitalPinToBitMask(clockpin);
}


int FastShiftIn::read()
{
    _value = 0;
    
    for (uint8_t i = 0; i < 8; i++)  
    {
        uint8_t oldSREG = SREG;
        cli();
    	*_clockin |= _clockbit;
        
        if ((*_datain & _databit) > 0) 
        {
            if (_bitorder == LSBFIRST)
                _value |= (1 << i);
            else
                _value |= (1 << (7 - i));
        }
		*_clockin |= _clockbit;
        SREG = oldSREG;
	}
    return _value;
}
// -- END OF FILE --