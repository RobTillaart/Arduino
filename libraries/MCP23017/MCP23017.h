#pragma once
//
//    FILE: MCP23017.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for I2C MCP23017 16 channel port expander
//    DATE: 2019-10-12
//     URL: https://github.com/RobTillaart/MCP23017_RT
// LICENSE: MIT

#include "Arduino.h"
#include "Wire.h"

#define MCP23017_LIB_VERSION "0.1.1"

class MCP23017
{
public:
  MCP23017(uint8_t addr);

#if defined(ESP8266) || defined(ESP32)
  void begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  void begin();

  // single pin interface
  void pinMode(uint8_t pin, uint8_t value);
  void digitalWrite(uint8_t pin, uint8_t value);
  uint8_t digitalRead(uint8_t pin);

  // 8 pins interface
  void pinMode8(uint8_t port, uint8_t value);
  void write8(uint8_t port, uint8_t value);
  int  read8(uint8_t port);

private:
  void    writeReg(uint8_t reg, uint8_t value);
  uint8_t readReg(uint8_t reg);
  uint8_t _addr;
};

// -- END OF FILE --
