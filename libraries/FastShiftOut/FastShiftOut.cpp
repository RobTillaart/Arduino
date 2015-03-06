//
//    FILE: FastShiftOut.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.04
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
FastShiftOut::FastShiftOut(const uint8_t datapin, const uint8_t clockpin, const uint8_t bitOrder)
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
    _clockbit = digitalPinToBitMask(clockpin);
}

//
// write() must implement the virtual write of Print class
//
// approx 64us/byte
size_t FastShiftOut::write(const uint8_t data)
{
    _value = data;
    for (uint8_t i = 0; i < 8; i++)
    {
        uint8_t v;
        if (_bitorder == LSBFIRST)   v = (_value & (1 << i));
        else                         v = (_value & (1 << (7 - i)));

        uint8_t oldSREG = SREG;
        cli();
        if (v == 0) *_dataout &= ~_databit;
        else        *_dataout |= _databit;
        *_clockout |= _clockbit;
        *_clockout &= ~_clockbit;
        SREG = oldSREG;
    }
    return 1;
}

//
// this version is twice as fast,
// but it is in CLI() mode
// approx 32 us / byte
// size_t FastShiftOut::write(uint8_t data)
// {
// _value = data;
// // prep masks
// uint8_t dm1 = *_dataout | _databit;
// uint8_t dm0 = *_dataout & ~_databit;
// uint8_t cm1 = *_clockout | _clockbit;
// uint8_t cm0 = *_clockout & ~_clockbit;

// uint8_t oldSREG = SREG;
// cli();
// if (_bitorder == LSBFIRST)
// {
// for (uint8_t m = 0x01; m != 0x80; m <<= 1)
// {
// if (_value & m) *_dataout = dm1;
// else            *_dataout = dm0;
// *_clockout = cm1;
// *_clockout = cm0;
// }
// }
// else
// {
// for (uint8_t m = 0x80; m > 0; m >>= 1)
// {
// if (_value & m) *_dataout = dm1;
// else            *_dataout = dm0;
// *_clockout = cm1;
// *_clockout = cm0;
// }
// }
// SREG = oldSREG;
// return 1;
// }


//
// reads back the last value written.
//
int FastShiftOut::read()
{
    return _value;
}

// -- END OF FILE --