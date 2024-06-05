#pragma once
//
//    FILE: MCP_ADC.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.1
//    DATE: 2019-10-24
// PURPOSE: Arduino library for MCP3001, MCP3002, MCP3004, MCP3008, MCP3201, MCP3202, MCP3204, MCP3208
//     URL: https://github.com/RobTillaart/MCP_ADC
//


// #if defined(BOARD_HAS_PIN_REMAP) && !defined(BOARD_USES_HW_GPIO_NUMBERS)
// #error please read readme.md for Arduino NANO ESP32 bug
// #endif


#include "Arduino.h"
#include "SPI.h"


#define MCP_ADC_LIB_VERSION       (F("0.5.1"))


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


class MCP_ADC
{
public:
  //       HARDWARE SPI
  MCP_ADC(__SPI_CLASS__ * mySPI = &SPI);
  //       SOFTWARE SPI
  MCP_ADC(uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  void     begin(uint8_t select);

  uint8_t  channels();
  int16_t  maxValue();

  int16_t  read(uint8_t channel);
  void     readMultiple(uint8_t channels[], uint8_t numChannels, int16_t readings[]);
  int16_t  differentialRead(uint8_t channel);
  int16_t  deltaRead(uint8_t channel);

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
  //  1 MHz is a safe value (datasheet); in a test 4 MHz worked.
  uint32_t _SPIspeed = 1000000;

  //  derived classes must implement buildRequest() function.
  virtual uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data) = 0;

  int16_t  readADC(uint8_t channel, bool single);
  void     readADCMultiple(uint8_t channels[], uint8_t numChannels, int16_t readings[]);

  uint8_t  swSPI_transfer(uint8_t d);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;

  uint32_t _count;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class MCP3001 : public MCP_ADC
{
public:
  MCP3001(__SPI_CLASS__ * mySPI = &SPI);
  MCP3001(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3002 : public MCP_ADC
{
public:
  MCP3002(__SPI_CLASS__ * mySPI = &SPI);
  MCP3002(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3004 : public MCP_ADC
{
public:
  MCP3004(__SPI_CLASS__ * mySPI = &SPI);
  MCP3004(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3008 : public MCP_ADC
{
public:
  MCP3008(__SPI_CLASS__ * mySPI = &SPI);
  MCP3008(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3201 : public MCP_ADC
{
public:
  MCP3201(__SPI_CLASS__ * mySPI = &SPI);
  MCP3201(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3202 : public MCP_ADC
{
public:
  MCP3202(__SPI_CLASS__ * mySPI = &SPI);
  MCP3202(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3204 : public MCP_ADC
{
public:
  MCP3204(__SPI_CLASS__ * mySPI = &SPI);
  MCP3204(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3208 : public MCP_ADC
{
public:
  MCP3208(__SPI_CLASS__ * mySPI = &SPI);
  MCP3208(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


//  -- END OF FILE --

