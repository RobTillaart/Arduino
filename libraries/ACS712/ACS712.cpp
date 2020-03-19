//
//    FILE: ACS712.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2020-03-17
// PURPOSE: ACS712 library - current measurement
//
// HISTORY:
// 0.1.0    2020-03-17 initial version
// 0.1.1    2020-03-18 first release version
//
// Released to the public domain
//

#include "ACS712.h"

ACS712::ACS712(uint8_t analogPin, float volts, uint16_t maxADC, uint8_t mVperA)
{
    _pin = analogPin;
    // 1x 1000 for V -> mV
    _mVpstep = 1000.0 * volts / maxADC;
    _mVperAmpere = mVperA;
    _formFactor = 0.70710678119;  // 0.5 * sqrt(2);  TODO: should be smaller in practice 0.5 ?
    _midPoint = maxADC / 2;
}

int ACS712::mA_AC()
{
    uint32_t start = micros();
    int _min, _max;
    _min = _max = analogRead(_pin);
    while (micros() - start < 20000)  // UNO ~180 samples...
    {
        int val = analogRead(_pin);
        if (val < _min) _min = val;
        if (val > _max) _max = val;
    }
    int p2p = (_max - _min);
    // TODO determine _formFactor
    //      two counters, a threshold and math is needed
    //      D = (1.0 - #samples close to zero ) / #samples
    //      FF = D * 0.5 * sqrt(2);
    
    // math could be partially precalculated 
    return 1000.0 * 0.5 * p2p * _mVpstep * _formFactor / _mVperAmpere;
}

int ACS712::mA_DC()
{
    // read twice to stabilize...
    analogRead(_pin);
    int steps = analogRead(_pin) - _midPoint;
    return 1000.0 * steps * _mVpstep / _mVperAmpere;
}

// END OF FILE
