//
//    FILE: AD524X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: I2C digital PotentioMeter AD5241 AD5242
//    DATE: 2013-10-12
//     URL:
//
// Released to the public domain
//

#ifndef AD524X_h
#define AD524X_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

#define AD524X_VERSION "0.1.02"

#define AS524X_OK       0
#define AS524X_ERROR    -10

class AD524X
{
public:
    AD524X(uint8_t address);
    
    uint8_t zeroAll();
    uint8_t read(uint8_t rdac);
    uint8_t write(uint8_t rdac, uint8_t value);
    uint8_t write(uint8_t rdac, uint8_t value, uint8_t O1, uint8_t O2);
    
    uint8_t setO1(uint8_t value);  // HIGH / LOW
    uint8_t setO2(uint8_t value);  // HIGH / LOW
    uint8_t getO1();
    uint8_t getO2();

    uint8_t midScaleReset(uint8_t rdac);
    //
    // uint8_t shutDown();

private:
    uint8_t send(uint8_t, uint8_t);     // cmd value

    uint8_t _address;
    uint8_t _lastValue[2];
    uint8_t _O1;
    uint8_t _O2;
};

#endif

// -- END OF FILE --