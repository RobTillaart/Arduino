#pragma once
//
//    FILE: ADC081S.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2024-01-10
// PURPOSE: Arduino library for ADC081S 8 bit ADC (SPI)
//     URL: https://github.com/RobTillaart/ADC081S
//


#include "Arduino.h"
#include "SPI.h"


#define ADC081S_LIB_VERSION       (F("0.2.2"))


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


class ADC081S
{
public:
  //       HARDWARE SPI
  ADC081S(__SPI_CLASS__ * mySPI = &SPI);
  //       SOFTWARE SPI
  ADC081S(uint8_t dataIn, uint8_t clock);

  void     begin(uint8_t select);

  uint16_t maxValue();
  uint16_t read();

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
  uint8_t  _data;
  uint8_t  _clock;
  uint8_t  _select;
  bool     _hwSPI;

  uint16_t _maxValue;
  uint16_t readADC();
  void     shutDown();

  uint16_t swSPI_transfer16(uint16_t m = 0x8000);

  //  1 MHz is a safe value (datasheet); in a test 4 MHz worked.
  uint32_t        _SPIspeed = 1000000;
  __SPI_CLASS__ * _mySPI;
  SPISettings     _spi_settings;

  uint32_t _count;
  bool     _isLowPower;
};


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class ADC101S : public ADC081S
{
public:
  ADC101S(__SPI_CLASS__ * mySPI = &SPI);
  ADC101S(uint8_t data, uint8_t clock);
  uint16_t read();
};


class ADC121S : public ADC081S
{
public:
  ADC121S(__SPI_CLASS__ * mySPI = &SPI);
  ADC121S(uint8_t data, uint8_t clock);
  uint16_t read();
};


//  -- END OF FILE --

