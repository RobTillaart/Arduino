#pragma once
//
//    FILE: AD524X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: I2C digital PotentioMeter AD5241 AD5242
//    DATE: 2013-10-12
//     URL: https://github.com/RobTillaart/AD524X
//

#include "Arduino.h"
#include "Wire.h"

#define AD524X_VERSION "0.2.1"

#define AS524X_OK       0
#define AS524X_ERROR    100

class AD524X
{
public:
    // address
    explicit AD524X(const uint8_t);

    uint8_t zeroAll();
    // rdac
    uint8_t read(const uint8_t);
    // for debugging
    uint8_t readBackRegister();  // returns the last value written in register.

    // rdac value
    uint8_t write(const uint8_t, const uint8_t);
    // rdac value O1 O2
    uint8_t write(const uint8_t, const uint8_t, const uint8_t, const uint8_t);

    uint8_t setO1(const uint8_t);  // HIGH / LOW
    uint8_t setO2(const uint8_t);  // HIGH / LOW
    uint8_t getO1();
    uint8_t getO2();

    // rdac
    uint8_t midScaleReset(const uint8_t);
    //
    // uint8_t shutDown();

private:
    uint8_t send(const uint8_t, const uint8_t);     // cmd value

    uint8_t _address;
    uint8_t _lastValue[2];
    uint8_t _O1;
    uint8_t _O2;
};

// -- END OF FILE --
