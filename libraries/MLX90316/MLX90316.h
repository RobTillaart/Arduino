#pragma once
//
//    FILE: MLX90316.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for SPI based MLX90316 rotary encoder.
//    DATE: 2026-08-04
//     URL: https://github.com/RobTillaart/MLX90316
//
//          16384 steps rotary encoder  14 bit 360²
//


#include "Arduino.h"
#include "SPI.h"

#define MLX90316_LIB_VERSION         (F("0.1.0"))



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


class MLX90316
{
public:
  //  HARDWARE SPI
  MLX90316(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  MLX90316(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

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

  //  DEBUG
  uint16_t getStatus();

private:
  uint8_t  _select;
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;

  uint32_t _lastRead = 0;
  float    _offset = 0;

  //  SPI
  bool     _hwSPI;
  uint32_t _SPIspeed = 100000;  //  150 kbps max.

  uint16_t readDevice();
  uint8_t  SWSPI_byte(uint8_t data);

  uint16_t raw;
  uint16_t mlx;  //  TODO investigate meaning

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};



//  -- END OF FILE --

