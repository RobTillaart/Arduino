#pragma once
//
//    FILE: AD7390.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-06-14
// PURPOSE: Arduino library for AD7390/AD7391 12/10 bit SPI DAC.
//     URL: https://github.com/RobTillaart/AD7390

#include "Arduino.h"
#include "SPI.h"


#define AD7390_LIB_VERSION              (F("0.1.1"))


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


class AD7390
{
public:
  //  HARDWARE SPI
  //  select = LD, clear = CLR
  AD7390(uint8_t select, uint8_t clear, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  //  select = LD, clear = CLR, dataOut = SDI, clock = CLK
  AD7390(uint8_t select, uint8_t clear, uint8_t dataOut, uint8_t clock);

  void     begin(uint16_t value);

  bool     setValue(uint16_t value);
  uint16_t getValue();
  uint16_t getMaxValue();

  bool     setPercentage(float percentage);
  float    getPercentage();

  void     clear();  //  set DAC to zero.

  //       ref voltage API
  bool     setRefVoltage(float volts);
  float    getRefVoltage();
  bool     setVoltage(float volts);
  float    getVoltage();

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();

  //       Debugging
  bool     usesHWSPI();


protected:
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  uint8_t  _clear;

  bool     _hwSPI;
  uint32_t _SPIspeed = 16000000;

  uint16_t _value;
  uint16_t _maxValue;
  float    _refVoltage;

  void     updateDevice(uint16_t value);
  void     swSPI_transfer(uint16_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


/////////////////////////////////////////////////////////////////////////////
//
// DERIVED CLASSES
//
class AD7391 : public AD7390
{
public:
  AD7391(uint8_t select, uint8_t clear, __SPI_CLASS__ * mySPI = &SPI);
  AD7391(uint8_t select, uint8_t clear, uint8_t dataOut, uint8_t clock);
};


//  -- END OF FILE --
