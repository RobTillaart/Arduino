#pragma once
//
//    FILE: ADC08XS.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2024-01-13
// PURPOSE: Arduino library for ADC082S, ADC084S, ADC102S, ADC104S, ADC122S, ADC124S,
//                              8, 10, 12 bits, 2 or 4 channel ADC (SPI).
//     URL: https://github.com/RobTillaart/ADC08XS
//


#include "Arduino.h"
#include "SPI.h"


#define ADC08XS_LIB_VERSION       (F("0.2.2"))


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


class ADC08XS
{
public:
  //       HARDWARE SPI
  ADC08XS(__SPI_CLASS__ * mySPI = &SPI);
  //       SOFTWARE SPI
  ADC08XS(uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  void     begin(uint8_t select);

  uint16_t maxValue();
  uint8_t  maxChannel();
  uint16_t read(uint8_t channel);
  int      deltaRead(uint8_t chanA, uint8_t chanB);

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();

  //       debugging
  bool     usesHWSPI();
  uint32_t count();  //  number of channels read.

  void     lowPower();
  void     wakeUp();
  bool     isLowPower();

protected:
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  bool     _hwSPI;

  uint16_t _maxValue;
  uint8_t  _maxChannel;
  uint16_t readADC(uint8_t channel);
  void     shutDown();

  uint16_t swSPI_transfer16(uint16_t address, uint16_t m = 0x8000);

  //  1 MHz is a safe value (datasheet); in a test 4 MHz worked.
  uint32_t        _SPIspeed = 1000000;
  __SPI_CLASS__ * _mySPI;
  SPISettings     _spi_settings;

  uint32_t _count;
  bool     _isLowPower;
};


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES 2 channel
//
class ADC082S : public ADC08XS
{
public:
  ADC082S(__SPI_CLASS__ * mySPI = &SPI);
  ADC082S(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint16_t read(uint8_t channel);
};


class ADC102S : public ADC08XS
{
public:
  ADC102S(__SPI_CLASS__ * mySPI = &SPI);
  ADC102S(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint16_t read(uint8_t channel);
};


class ADC122S : public ADC08XS
{
public:
  ADC122S(__SPI_CLASS__ * mySPI = &SPI);
  ADC122S(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint16_t read(uint8_t channel);
};


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES 4 channel
//
class ADC084S : public ADC08XS
{
public:
  ADC084S(__SPI_CLASS__ * mySPI = &SPI);
  ADC084S(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint16_t read(uint8_t channel);
};


class ADC104S : public ADC08XS
{
public:
  ADC104S(__SPI_CLASS__ * mySPI = &SPI);
  ADC104S(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint16_t read(uint8_t channel);
};


class ADC124S : public ADC08XS
{
public:
  ADC124S(__SPI_CLASS__ * mySPI = &SPI);
  ADC124S(uint8_t dataIn, uint8_t dataOut, uint8_t clock);
  uint16_t read(uint8_t channel);
};


//  -- END OF FILE --

