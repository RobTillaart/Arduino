#ifndef MCP4725_H
#define MCP4725_H
//
//    FILE: MCP4725.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple MCP4725 DAC library for Arduino
// VERSION: 1.0.01
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

#define MCP4725_VERSION         "1.0.01"

// regisiterMode
#define MCP4725_DAC             0x40
#define MCP4725_EEPROM          0x20

// constants
#define MCP4725_MAXVALUE        4095
#define MCP4725_TIMEOUT         1000

// errors
#define MCP4725_VALUE_ERROR     -999
#define MCP4725_REG_ERROR       -998


#define MCP4725_EXTENDED

class MCP4725
{
public:
    MCP4725(uint8_t deviceAddress);

    void begin();
    // uses writeFastMode
    int setValue(uint16_t value);
    // returns last value set - cached - much faster than readDAC();
    uint16_t getValue();  
    
#ifdef MCP4725_EXTENDED
    int smooth2Value(uint16_t value, uint8_t steps);
    int writeDAC(uint16_t value);
    uint16_t readDAC();
#endif

    
private:
    uint8_t _deviceAddress;

    int writeFastMode(uint16_t value);
    uint16_t _lastValue;
 
#ifdef MCP4725_EXTENDED
    int writeRegisterMode(uint16_t value, uint8_t reg);
    uint8_t readRegister(uint8_t* buffer, uint8_t length);
    uint8_t _PowerDownMode;      // DATASHEET P15?  
#endif
 
  
};

#endif
// END OF FILE