#pragma once
//
//    FILE: MCP23S08.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.3
// PURPOSE: Arduino library for SPI MCP23S08 8 channel port expander
//    DATE: 2022-01-10
//     URL: https://github.com/RobTillaart/MCP23S08


#include "Arduino.h"
#include "SPI.h"
#include "MCP23x08_registers.h"


#define MCP23S08_LIB_VERSION              (F("0.5.3"))

//  ERROR CODES
#define MCP23S08_OK                       0x00
#define MCP23S08_PIN_ERROR                0x81
#define MCP23S08_SPI_ERROR                0x82
#define MCP23S08_VALUE_ERROR              0x83
#define MCP23S08_PORT_ERROR               0x84
#define MCP23S08_REGISTER_ERROR           0xFF
#define MCP23S08_INVALID_READ             0xFF


#ifndef __SPI_CLASS__
  //  MBED must be tested before RP2040
  #if defined(ARDUINO_ARCH_MBED)
  #define __SPI_CLASS__   SPIClass
  #elif defined(ARDUINO_ARCH_RP2040)
  #define __SPI_CLASS__   SPIClassRP2040
  #else
  #define __SPI_CLASS__   SPIClass
  #endif
#endif


const uint32_t MCP23S08_TYP_SPI_SPEED =  8000000;
const uint32_t MCP23S08_MAX_SPI_SPEED = 10000000;


class MCP23S08
{
public:
  //       SOFTWARE SPI
  MCP23S08(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address = 0x00);
  //       HARDWARE SPI
  MCP23S08(int select, __SPI_CLASS__* spi);
  MCP23S08(int select, int address = 0x00, __SPI_CLASS__* spi = &SPI);

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


  //       SPI
  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };

  //       debugging
  bool     usesHWSPI() { return _hwSPI; };
  int      lastError();

  //       set/clear IOCR bit fields
  bool     enableControlRegister(uint8_t mask);
  bool     disableControlRegister(uint8_t mask);
  //       0.2.0 experimental
  bool     enableHardwareAddress();
  bool     disableHardwareAddress();


protected:
  //       access to low level registers (just make these functions public).
  //       USE WITH CARE !!!
  bool     writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);

  uint8_t  _address = 0;
  uint8_t  _select  = 0;
  uint8_t  _dataOut = 0;
  uint8_t  _dataIn  = 0;
  uint8_t  _clock   = 0;
  uint8_t  _error   = MCP23S08_OK;

  bool     _hwSPI = true;

  //       10 MHz is maximum, 8 is a better clock divider on AVR.
  uint32_t    _SPIspeed = MCP23S08_TYP_SPI_SPEED;
  __SPI_CLASS__ * _mySPI;
  SPISettings     _spi_settings;

  uint8_t  swSPI_transfer(uint8_t val);
};


//  -- END OF FILE --

