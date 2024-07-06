#pragma once
//
//    FILE: MCP23008.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.4
// PURPOSE: Arduino library for I2C MCP23008 8 channel port expander
//    DATE: 2022-01-10
//     URL: https://github.com/RobTillaart/MCP23008


#include "Arduino.h"
#include "Wire.h"
#include "MCP23x08_registers.h"


#define MCP23008_LIB_VERSION              (F("0.3.4"))

#define MCP23008_OK                       0x00
#define MCP23008_PIN_ERROR                0x81
#define MCP23008_I2C_ERROR                0x82
#define MCP23008_VALUE_ERROR              0x83
#define MCP23008_PORT_ERROR               0x84
#define MCP23008_REGISTER_ERROR           0xFF
#define MCP23008_INVALID_READ             0xFF


class MCP23008
{
public:
  MCP23008(uint8_t address, TwoWire *wire = &Wire);

  bool     begin(bool pullup = true);
  bool     isConnected();
  uint8_t  getAddress();


  //       single pin interface
  //       mode = INPUT, OUTPUT, INPUT_PULLUP (= same as INPUT)
  //             do not use 0, 1 for mode.
  bool     pinMode1(uint8_t pin, uint8_t mode);
  bool     write1(uint8_t pin, uint8_t value);
  uint8_t  read1(uint8_t pin);

  bool     setPolarity(uint8_t pin, bool reversed);
  bool     getPolarity(uint8_t pin, bool &reversed);
  bool     setPullup(uint8_t pin, bool pullup);
  bool     getPullup(uint8_t pin, bool &pullup);


  //       8 pins interface
  //       mask  = 0x00..0xFF  bit pattern, 
  //               bit 0 = output mode, bit 1 = input mode
  //       value = bit pattern.
  bool     pinMode8(uint8_t mask);
  bool     write8(uint8_t value);
  int      read8();

  bool     setPolarity8(uint8_t mask);
  bool     getPolarity8(uint8_t &mask);
  bool     setPullup8(uint8_t mask);
  bool     getPullup8(uint8_t &mask);


  //       INTERRUPTS (experimental)
  //       pin = 0..7, mode = { RISING, FALLING, CHANGE }
  bool     enableInterrupt(uint8_t pin, uint8_t mode);
  bool     disableInterrupt(uint8_t pin);

  //       which pins caused the INT?
  uint8_t  getInterruptFlagRegister();
  uint8_t  getInterruptCaptureRegister();

  //       polarity: 0 = LOW, 1 = HIGH, 2 = NONE/ODR
  bool     setInterruptPolarity(uint8_t polarity);
  uint8_t  getInterruptPolarity();

  //       debugging
  int      lastError();

  //       set/clear IOCR bit fields
  bool     enableControlRegister(uint8_t mask);
  bool     disableControlRegister(uint8_t mask);

  //       DEBUG functions
  uint8_t  getPinMode8();


protected:
  //       access to low level registers (just make these functions public).
  //       USE WITH CARE !!!
  bool     writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);

  uint8_t   _address;
  TwoWire*  _wire;
  uint8_t   _error;
};


//  -- END OF FILE --

