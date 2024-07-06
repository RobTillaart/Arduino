#pragma once
//
//    FILE: MCP23S17.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.4
// PURPOSE: Arduino library for SPI MCP23S17 16 channel port expander
//    DATE: 2021-12-30
//     URL: https://github.com/RobTillaart/MCP23S17


#include "Arduino.h"
#include "SPI.h"
#include "MCP23x17_registers.h"


#define MCP23S17_LIB_VERSION              (F("0.5.4"))

//  ERROR CODES
#define MCP23S17_OK                       0x00
#define MCP23S17_PIN_ERROR                0x81
#define MCP23S17_SPI_ERROR                0x82
#define MCP23S17_VALUE_ERROR              0x83
#define MCP23S17_PORT_ERROR               0x84
#define MCP23S17_REGISTER_ERROR           0xFF
#define MCP23S17_INVALID_READ             0xFF


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


const uint32_t MCP23S17_TYP_SPI_SPEED =  8000000;
const uint32_t MCP23S17_MAX_SPI_SPEED = 10000000;


class MCP23S17
{
public:
  //       SOFTWARE SPI
  MCP23S17(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address = 0x00);
  //       HARDWARE SPI
  MCP23S17(int select, __SPI_CLASS__ * spi);
  MCP23S17(int select, int address = 0x00, __SPI_CLASS__ * spi = &SPI);

  bool     begin(bool pullup = true);
  bool     isConnected();
  uint8_t  getAddress();   //  default returns 0x00


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
  //       port  = 0..1
  //       mask  = 0x00..0xFF  bit pattern, 
  //               bit 0 = output mode, bit 1 = input mode
  //       value = bit pattern.
  bool     pinMode8(uint8_t port, uint8_t mask);
  bool     write8(uint8_t port, uint8_t value);
  int      read8(uint8_t port);

  bool     setPolarity8(uint8_t port, uint8_t mask);
  bool     getPolarity8(uint8_t port, uint8_t &mask);
  bool     setPullup8(uint8_t port, uint8_t mask);
  bool     getPullup8(uint8_t port, uint8_t &mask);


  //       16 pins interface
  //       mask = 0x0000..0xFFFF bit pattern
  //              bit 0 = output mode, bit 1 = input mode
  //       value = bit pattern.
  bool     pinMode16(uint16_t mask);
  bool     write16(uint16_t value);
  uint16_t read16();

  bool     setPolarity16(uint16_t mask);
  bool     getPolarity16(uint16_t &mask);
  bool     setPullup16(uint16_t mask);
  bool     getPullup16(uint16_t &mask);


  //       INTERRUPTS (experimental)
  //       pin = 0..15, mode = { RISING, FALLING, CHANGE }
  bool     enableInterrupt(uint8_t pin, uint8_t mode);
  bool     disableInterrupt(uint8_t pin);
  
  //       mask = 0x0000..0xFFFF  (overrides all earlier settings.
  bool     enableInterrupt16(uint16_t mask, uint8_t mode);
  bool     disableInterrupt16(uint16_t mask);

  //       which pins caused the INT?
  uint16_t getInterruptFlagRegister();
  uint16_t getInterruptCaptureRegister();

  //       polarity: 0 = LOW, 1 = HIGH, 2 = NONE/ODR
  bool     setInterruptPolarity(uint8_t polarity);
  uint8_t  getInterruptPolarity();

  //       merge INTA and INTB
  bool     mirrorInterrupts(bool on);
  bool     isMirroredInterrupts();


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
  //       0.2.5 experimental
  bool     enableHardwareAddress();
  bool     disableHardwareAddress();


protected:
  //       access to low level registers (just make these functions public).
  //       USE WITH CARE !!!
  bool     writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);
  bool     writeReg16(uint8_t reg, uint16_t value);
  uint16_t readReg16(uint8_t reg);

  uint8_t  _address = 0;
  uint8_t  _select  = 0;
  uint8_t  _dataOut = 0;
  uint8_t  _dataIn  = 0;
  uint8_t  _clock   = 0;
  uint8_t  _error   = MCP23S17_OK;

  bool     _hwSPI = true;

  //       10 MHz is maximum, 8 is a better clock divider on AVR.
  uint32_t    _SPIspeed = MCP23S17_TYP_SPI_SPEED;
  __SPI_CLASS__ * _mySPI;
  SPISettings     _spi_settings;

  uint8_t  swSPI_transfer(uint8_t val);
};


//  -- END OF FILE --

