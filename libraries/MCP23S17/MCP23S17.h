#pragma once
//
//    FILE: MCP23S17.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for SPI MCP23S17 16 channel port expander
//    DATE: 2021-12-30
//     URL: https://github.com/RobTillaart/MCP23S17_RT


#include "Arduino.h"
#include "SPI.h"


#define MCP23S17_LIB_VERSION              (F("0.1.0"))

#define MCP23S17_OK                       0x00
#define MCP23S17_PIN_ERROR                0x81
#define MCP23S17_SPI_ERROR                0x82
#define MCP23S17_VALUE_ERROR              0x83
#define MCP23S17_PORT_ERROR               0x84


#define MCP23S17_INVALID_READ             -100


class MCP23S17
{
public:
  // MCP23S17();
  
  MCP23S17(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address = 0x00);
  MCP23S17(uint8_t select, uint8_t address = 0x00);

  bool    begin();
  bool    isConnected();  // needed ?


  // single pin interface
  // mode = INPUT, OUTPUT or INPUT_PULLUP (==INPUT)
  bool    pinMode(uint8_t pin, uint8_t mode);
  bool    digitalWrite(uint8_t pin, uint8_t value);
  uint8_t digitalRead(uint8_t pin);

  bool    setPolarity(uint8_t pin, bool reversed);
  bool    getPolarity(uint8_t pin, bool &reversed);
  bool    setPullup(uint8_t pin, bool pullup);
  bool    getPullup(uint8_t pin, bool &pullup);


  // 8 pins interface
  // port  = 0..1
  // value = bit pattern
  bool    pinMode8(uint8_t port, uint8_t value);
  bool    write8(uint8_t port, uint8_t value);
  int     read8(uint8_t port);


  bool    setPolarity8(uint8_t port, uint8_t mask);
  bool    getPolarity8(uint8_t port, uint8_t &mask);
  bool    setPullup8(uint8_t port, uint8_t mask);
  bool    getPullup8(uint8_t port, uint8_t &mask);

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };

  // debugging
  bool     usesHWSPI() { return _hwSPI; };
  int      lastError();

private:
  bool    writeReg(uint8_t reg, uint8_t value);
  uint8_t readReg(uint8_t reg);

  uint8_t   _address = 0;
  uint8_t   _select  = 0;
  uint8_t   _dataOut = 0;
  uint8_t   _dataIn  = 0;
  uint8_t   _clock   = 0;
  uint8_t   _error   = MCP23S17_OK;

  bool        _hwSPI = false;
  uint32_t    _SPIspeed = 8000000UL;   // 1MHz is a safe value TODO CHECK datasheet
  SPIClass    * mySPI;
  SPISettings _spi_settings;

  uint8_t  swSPI_transfer(uint8_t val);
};


// -- END OF FILE --

