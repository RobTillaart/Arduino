#ifndef MCP4725_H
#define MCP4725_H
//
//    FILE: MCP4725.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple MCP4725 DAC library for Arduino
// VERSION: 1.0.04
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

#define MCP4725_VERSION         "1.0.04"

// regisiterMode
#define MCP4725_DAC             0x40
#define MCP4725_DACEEPROM       0x60

// constants
#define MCP4725_MAXVALUE        4095
#define MCP4725_TIMEOUT         1000

// errors
#define MCP4725_VALUE_ERROR     -999
#define MCP4725_REG_ERROR       -998

// page 22
#define MCP4725_GC_RESET        0x06
#define MCP4725_GC_WAKEUP       0x09

// powerDown Mode - TODO ENUM?
#define MCP4725_PDMODE_NORMAL   0x00
#define MCP4725_PDMODE_1K       0x01
#define MCP4725_PDMODE_100K     0x02
#define MCP4725_PDMODE_500K     0x03

// conditional to minimize footprint.
//#define MCP4725_EXTENDED
//#define MCP4725_POWERDOWNMODE

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
    int writeDAC(uint16_t value, bool EEPROM = false);
    bool RDY();
    uint16_t readDAC();
    uint16_t readEEPROM();
#endif

#ifdef MCP4725_POWERDOWNMODE
    // experimental
    int writePowerDownMode(uint8_t PDM, bool EEPROM = false);
    uint8_t readPowerDownModeEEPROM();
    uint8_t readPowerDownModeDAC();
    int powerOnReset();
    int powerOnWakeUp();
#endif

private:
    uint8_t _deviceAddress;
    uint16_t _lastValue;
    uint8_t _powerDownMode;      // DATASHEET P15?
    int writeFastMode(uint16_t value);

#ifdef MCP4725_EXTENDED
    int writeRegisterMode(uint16_t value, uint8_t reg);
    uint8_t readRegister(uint8_t* buffer, uint8_t length);
#endif

#ifdef MCP4725_POWERDOWNMODE
    int generalCall(uint8_t gc);
#endif

};

#endif
// END OF FILE