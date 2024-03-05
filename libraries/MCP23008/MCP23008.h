#pragma once
//
//    FILE: MCP23008.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: Arduino library for I2C MCP23008 8 channel port expander
//    DATE: 2022-01-10
//     URL: https://github.com/RobTillaart/MCP23008


#include "Arduino.h"
#include "Wire.h"


#define MCP23008_LIB_VERSION              (F("0.3.2"))

#define MCP23008_OK                       0x00
#define MCP23008_PIN_ERROR                0x81
#define MCP23008_I2C_ERROR                0x82
#define MCP23008_VALUE_ERROR              0x83
#define MCP23008_PORT_ERROR               0x84


#define MCP23008_INVALID_READ             -100


class MCP23008
{
public:
  MCP23008(uint8_t address, TwoWire *wire = &Wire);

  bool    begin(bool pullup = true);
  bool    isConnected();
  uint8_t getAddress();


  //      single pin interface
  //      mode =  INPUT,  OUTPUT or  INPUT_PULLUP (== INPUT)
  bool    pinMode1(uint8_t pin, uint8_t mode);
  bool    write1(uint8_t pin, uint8_t value);
  uint8_t read1(uint8_t pin);

  bool    setPolarity(uint8_t pin, bool reversed);
  bool    getPolarity(uint8_t pin, bool &reversed);
  bool    setPullup(uint8_t pin, bool pullup);
  bool    getPullup(uint8_t pin, bool &pullup);


  //      8 pins interface
  //      value = bit pattern
  bool    pinMode8(uint8_t value);
  bool    write8(uint8_t value);
  int     read8();

  bool    setPolarity8(uint8_t mask);
  bool    getPolarity8(uint8_t &mask);
  bool    setPullup8(uint8_t mask);
  bool    getPullup8(uint8_t &mask);


  int     lastError();

  //      DEBUG functions
  uint8_t getPinMode8();


private:
  bool    writeReg(uint8_t reg, uint8_t value);
  uint8_t readReg(uint8_t reg);

  uint8_t   _address;
  TwoWire*  _wire;
  uint8_t   _error;
};


//  -- END OF FILE --

