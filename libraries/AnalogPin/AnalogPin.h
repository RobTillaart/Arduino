//
//    FILE: AnalogPin.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
//    DATE: 2013-09-09
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

#define ANALOGPIN_LIB_VERSION "0.1.01"

class AnalogPin
{
public:
    AnalogPin(uint8_t);

    // noise 0..255; in practice 0..4
    uint16_t read(uint8_t noise = 0);

    // alpha 0..31;
    uint16_t readSmoothed(uint8_t alpha = 0);

    uint16_t readPrevious();

private:
    uint8_t _pin;
    uint16_t _prevValue;
};

#endif
// -- END OF FILE --