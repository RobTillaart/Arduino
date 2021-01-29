#pragma once
//
//    FILE: MCP4725.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for 12 bit I2C DAC - MCP4725 
// VERSION: 0.3.0
//     URL: https://github.com/RobTillaart/MCP4725
// HISTORY: See MCP4725.cpp
//


#include "Wire.h"
#include "Arduino.h"


#define MCP4725_VERSION         (F("0.3.0"))


// constants
#define MCP4725_MAXVALUE        4095


// errors
#define MCP4725_OK              0
#define MCP4725_VALUE_ERROR     -999
#define MCP4725_REG_ERROR       -998
#define MCP4725_NOT CONNECTED   -997


// powerDown Mode - TODO ENUM?
#define MCP4725_PDMODE_NORMAL   0x00
#define MCP4725_PDMODE_1K       0x01
#define MCP4725_PDMODE_100K     0x02
#define MCP4725_PDMODE_500K     0x03


class MCP4725
{
public:
  explicit MCP4725(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined(ESP8266) || defined(ESP32)
  bool     begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  bool     begin();
  bool     isConnected();


  // uses writeFastMode
  int      setValue(const uint16_t value = 0);
  // returns last value set - cached - much faster than readDAC();
  uint16_t getValue();


  // 0..100.0% - no input check.
  int      setPercentage(float perc = 0) { return setValue(round(perc * (0.01 * MCP4725_MAXVALUE))); };
  float    getPercentage() { return getValue() * (100.0 / MCP4725_MAXVALUE); };


  int      writeDAC(const uint16_t value, const bool EEPROM = false);
  // RDY isdepreciated in the future, use ready() instead.
  // inline bool RDY()  { return ready(); };
  bool     ready();
  uint32_t getLastWriteEEPROM()  { return _lastWriteEEPROM; };
  uint16_t readDAC();
  uint16_t readEEPROM();


  // experimental
  int      writePowerDownMode(const uint8_t PDM, const bool EEPROM = false);
  uint8_t  readPowerDownModeEEPROM();
  uint8_t  readPowerDownModeDAC();
  int      powerOnReset();
  int      powerOnWakeUp();


private:
  uint8_t  _deviceAddress;
  uint16_t _lastValue;
  uint8_t  _powerDownMode;      // DATASHEET P15?
  int      _writeFastMode(const uint16_t value);
  uint32_t _lastWriteEEPROM;

  int      _writeRegisterMode(const uint16_t value, uint8_t reg);
  uint8_t  _readRegister(uint8_t* buffer, const uint8_t length);

  int      _generalCall(const uint8_t gc);

  TwoWire*  _wire;
};

// -- END OF FILE --
