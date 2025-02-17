#pragma once
//
//    FILE: ERCFS.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for SPI based ERCFS rotary encoder.
//    DATE: 2025-02-08
//     URL: https://github.com/RobTillaart/ERCFS
//          https://p3america.com/ercf-1-05spi-360-z/
//
//          16384 steps rotary encoder  14 bit 360²
//
// https://forum.arduino.cc/t/will-this-rotary-encoder-work-with-arduino/1351596
//


#include "Arduino.h"
#include "SPI.h"

#define ERCFS_LIB_VERSION         (F("0.1.2"))



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


class ERCFS
{
public:
  //  HARDWARE SPI
  ERCFS(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  ERCFS(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  bool     begin();

  uint16_t getRawValue();
  float    getAngle();
  void     setOffset(float offset = 0);
  float    getOffset();

  uint32_t lastRead();

  //  SPI
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();


private:
  uint8_t  _select;
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;

  uint32_t _lastRead = 0;
  float    _offset = 0;

  //  SPI
  bool     _hwSPI;
  uint32_t _SPIspeed = 1000000;

  uint16_t readDevice();

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};



//  -- END OF FILE --

