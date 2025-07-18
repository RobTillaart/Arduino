#pragma once
//
//    FILE: MCP330X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2025-04-16
// PURPOSE: Arduino library for MCP3302 and MCP3304 13-Bit Differential ADC, SPI
//     URL: https://github.com/RobTillaart/MCP330X
//


#include "Arduino.h"
#include "SPI.h"


#define MCP330X_LIB_VERSION       (F("0.2.0"))


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


//  BASE class
class MCP330X
{
public:
  //       HARDWARE SPI
  MCP330X(__SPI_CLASS__ * mySPI = &SPI);
  //       SOFTWARE SPI
  MCP330X(uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  void     begin(uint8_t select);

  //  return configuration values.
  uint8_t  channels();
  int16_t  maxValue();

  //  channel = 0..3 or 0..7
  int16_t  read(uint8_t channel);
  //  pair = 0..3 or 0..7
  int16_t  differentialRead(uint8_t pair);


  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();

  //       debugging
  bool     usesHWSPI();
  uint32_t count();  //  number of channels read.


protected:
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  bool     _hwSPI;
  uint8_t  _channels;
  int16_t  _maxValue;
  //  1 MHz is a safe value (datasheet);  in a test 4 MHz worked.
  uint32_t _SPIspeed = 1000000;

  int16_t  readADC(uint8_t channel, bool single);

  uint8_t  swSPI_transfer(uint8_t d);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;

  uint32_t _count;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class MCP3302 : public MCP330X
{
public:
  MCP3302(__SPI_CLASS__ * mySPI = &SPI);
  MCP3302(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


class MCP3304 : public MCP330X
{
public:
  MCP3304(__SPI_CLASS__ * mySPI = &SPI);
  MCP3304(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


//  -- END OF FILE --

