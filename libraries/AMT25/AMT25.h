#pragma once
//
//    FILE: AMT25.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for SPI based AMT25 series rotary encoder.
//    DATE: 2025-02-08
//     URL: https://github.com/RobTillaart/AMT25
//          https://www.sameskydevices.com/
//          16384 steps rotary encoder  14 bit 360°
//


#include "Arduino.h"
#include "SPI.h"

#define AMT25_LIB_VERSION         (F("0.1.1"))



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


class AMT25
{
public:
  //  HARDWARE SPI
  AMT25(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AMT25(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  //  bits == 12 => steps = 4096
  //          14 => steps = 16384
  bool     begin(uint8_t bits = 14);  // default 14 bit.

  uint16_t getRawValue();
  float    getAngle();
  void     setOffset(float offset = 0);
  float    getOffset();

  uint16_t setZero();
  //  warning blocking function (duration depends on SPI speed).
  uint16_t getTurns();

  uint32_t lastRead();

  //  SPI
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();


protected:
  uint8_t  _select;
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;

  uint32_t _lastRead = 0;
  float    _offset = 0;
  uint8_t  _bits = 14;
  uint16_t _steps = 16384;

  //  SPI
  bool     _hwSPI;
  uint32_t _SPIspeed = 2000000;  //  max 2MHz

  uint16_t readDevice(uint16_t command);
  bool     checkParity(uint16_t raw);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


/////////////////////////////////////////////////////
//
//  DERIVED CLASSES TODO
//
class AMT22 : public AMT25
{
public:
  AMT22(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  AMT22(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


//  to verify (if and how far) it is compatible
class AMT23 : public AMT25
{
public:
  AMT23(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  AMT23(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


//  -- END OF FILE --

