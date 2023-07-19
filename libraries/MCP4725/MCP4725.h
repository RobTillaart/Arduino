#pragma once
//
//    FILE: MCP4725.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for 12 bit I2C DAC - MCP4725
// VERSION: 0.3.6
//     URL: https://github.com/RobTillaart/MCP4725
//


#include "Wire.h"
#include "Arduino.h"


#define MCP4725_VERSION         (F("0.3.6"))


//  CONSTANTS
#define MCP4725_MAXVALUE        4095


//  ERRORS
#define MCP4725_OK              0
#define MCP4725_VALUE_ERROR     -999
#define MCP4725_REG_ERROR       -998
#define MCP4725_NOT_CONNECTED   -997


//  powerDown Mode - TODO ENUM?
#define MCP4725_PDMODE_NORMAL   0x00
#define MCP4725_PDMODE_1K       0x01
#define MCP4725_PDMODE_100K     0x02
#define MCP4725_PDMODE_500K     0x03

#define MCP4725_MIDPOINT        2048


class MCP4725
{
public:
  explicit MCP4725(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined(ESP8266) || defined(ESP32)
  bool     begin(const uint8_t dataPin, const uint8_t clockPin);
#endif

#if defined (ARDUINO_ARCH_RP2040)

  bool     begin(int sda, int scl);

#endif

  bool     begin();
  bool     isConnected();


  //  uses writeFastMode
  int      setValue(const uint16_t value = 0);
  //  returns last value set - cached - much faster than readDAC();
  uint16_t getValue();


  //  0..100.0% - no input check.
  int      setPercentage(float percentage = 0);
  float    getPercentage();


  int      writeDAC(const uint16_t value, const bool EEPROM = false);
  bool     ready();
  uint16_t readDAC();
  uint16_t readEEPROM();
  uint32_t getLastWriteEEPROM();


  //  experimental
  int      writePowerDownMode(const uint8_t PDM, const bool EEPROM = false);
  uint8_t  readPowerDownModeEEPROM();
  uint8_t  readPowerDownModeDAC();
  int      powerOnReset();
  int      powerOnWakeUp();


private:
  uint8_t  _deviceAddress;
  uint16_t _lastValue;
  uint8_t  _powerDownMode;      //  DATASHEET P15?
  int      _writeFastMode(const uint16_t value);
  uint32_t _lastWriteEEPROM;

  int      _writeRegisterMode(const uint16_t value, uint8_t reg);
  uint8_t  _readRegister(uint8_t* buffer, const uint8_t length);

  int      _generalCall(const uint8_t gc);

  TwoWire*  _wire;
};


//  -- END OF FILE --

