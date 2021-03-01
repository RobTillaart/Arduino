#pragma once
//
//    FILE: MCP23017.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for I2C MCP23017 16 channel port expander
//    DATE: 2019-10-12
//     URL: https://github.com/RobTillaart/MCP23017_RT


#include "Arduino.h"
#include "Wire.h"


#define MCP23017_LIB_VERSION    (F("0.2.1"))

#define MCP23017_OK              0x00
#define MCP23017_PIN_ERROR       0x81
#define MCP23017_I2C_ERROR       0x82
#define MCP23017_VALUE_ERROR     0x83
#define MCP23017_PORT_ERROR      0x84


class MCP23017
{
public:
  MCP23017(uint8_t addr, TwoWire *wire = &Wire);

#if defined(ESP8266) || defined(ESP32)
  bool    begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  bool    begin();
  bool    isConnected();
  
  // single pin interface
  bool    pinMode(uint8_t pin, uint8_t value);
  bool    digitalWrite(uint8_t pin, uint8_t value);
  uint8_t digitalRead(uint8_t pin);

  // 8 pins interface
  bool    pinMode8(uint8_t port, uint8_t value);
  bool    write8(uint8_t port, uint8_t value);
  int     read8(uint8_t port);

  int     lastError();
  
private:
  bool    writeReg(uint8_t reg, uint8_t value);
  uint8_t readReg(uint8_t reg);

  uint8_t   _addr;
  TwoWire*  _wire;
  uint8_t   _error;
};

// -- END OF FILE --
