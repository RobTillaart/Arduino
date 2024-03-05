#pragma once
//
//    FILE: MCP23017.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.6.2
// PURPOSE: Arduino library for I2C MCP23017 16 channel port expander
//    DATE: 2019-10-12
//     URL: https://github.com/RobTillaart/MCP23017_RT
//
// WARNING: please read REV D note in readme.md.


#include "Arduino.h"
#include "Wire.h"


#define MCP23017_LIB_VERSION              (F("0.6.2"))

#define MCP23017_OK                       0x00
#define MCP23017_PIN_ERROR                0x81
#define MCP23017_I2C_ERROR                0x82
#define MCP23017_VALUE_ERROR              0x83
#define MCP23017_PORT_ERROR               0x84


#define MCP23017_INVALID_READ             -100


class MCP23017
{
public:
  MCP23017(uint8_t address, TwoWire *wire = &Wire);

  bool     begin(bool pullup = true);
  bool     isConnected();
  uint8_t  getAddress();


  //       single pin interface
  //       mode = INPUT, OUTPUT or INPUT_PULLUP (==INPUT)
  bool     pinMode1(uint8_t pin, uint8_t mode);
  bool     write1(uint8_t pin, uint8_t value);
  uint8_t  read1(uint8_t pin);

  bool     setPolarity(uint8_t pin, bool reversed);
  bool     getPolarity(uint8_t pin, bool &reversed);
  bool     setPullup(uint8_t pin, bool pullup);
  bool     getPullup(uint8_t pin, bool &pullup);


  //       8 pins interface
  //       port  = 0..1
  //       value = bit pattern
  bool     pinMode8(uint8_t port, uint8_t value);
  bool     write8(uint8_t port, uint8_t value);
  int      read8(uint8_t port);

  bool     setPolarity8(uint8_t port, uint8_t mask);
  bool     getPolarity8(uint8_t port, uint8_t &mask);
  bool     setPullup8(uint8_t port, uint8_t mask);
  bool     getPullup8(uint8_t port, uint8_t &mask);


  //       16 pins interface
  //       value = bit pattern
  bool     pinMode16(uint16_t value);
  bool     write16(uint16_t value);
  uint16_t read16();

  bool     setPolarity16(uint16_t mask);
  bool     getPolarity16(uint16_t &mask);
  bool     setPullup16(uint16_t mask);
  bool     getPullup16(uint16_t &mask);

  int      lastError();

protected:
  bool     writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);

  uint8_t   _address;
  TwoWire*  _wire;
  uint8_t   _error;
};


/*  
TODO
- can it protect the user
- can we detect REV D chips (over I2C)

class MCP23017_REVD : public MCP23017
{
public:
  MCP23017_REVD(uint8_t address, TwoWire *wire = &Wire);
  
- GPA7 and GPB7 should be set to output in constructor
- GPA7 and GPB7 output mode may not change in any call
- GPA7 and GPB7 should return last written value for read.
- which functions are affected?  setMode  pullups etc.

};
*/


//  -- END OF FILE --

