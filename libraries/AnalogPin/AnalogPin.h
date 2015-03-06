//
//    FILE: AnalogPin.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.04
//    DATE: 2014-10-05
// PURPOSE: wrapper class for analogRead
//     URL:
//
// Released to the public domain
//

#ifndef AnalogPin_h
#define AnalogPin_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define ANALOGPIN_LIB_VERSION "0.1.04"

class AnalogPin
{
public:
    AnalogPin(const uint8_t);

    // noise 0..255; in practice 0..4
    int read(uint8_t noise = 0);

    // alpha 0..31;
    int readSmoothed(uint8_t alpha = 0);

    int readPrevious();

private:
    uint8_t _pin;
    int _prevValue;
};

#endif
// -- END OF FILE --