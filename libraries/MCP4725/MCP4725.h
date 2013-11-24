#ifndef MCP4725_H
#define MCP4725_H
//
//    FILE: MCP4725.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple MCP4725 DAC library for Arduino
// VERSION: 1.0.00
// HISTORY: See MCP4725.cpp
//     URL:
//
// Released to the public domain
//

#include <Wire.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "Wstring.h"
#include "Wiring.h"
#endif

#define MCP4725_VERSION         "1.0.00"

#define MCP4725_MAXVALUE        4095
#define MCP4725_VALUE_ERROR     -999

#define MCP4725_DAC             0x40

// #define MCP4725_EXTENDED

class MCP4725
{
public:
    MCP4725(uint8_t deviceAddress);

    void begin();
    int setValue(uint16_t value);
    int smooth2Value(uint16_t value, uint8_t steps);
    uint16_t getValue();

private:
    uint8_t  _deviceAddress;
    int writeFastMode(uint16_t value);
    uint16_t _lastValue;
};

#endif
// END OF FILE