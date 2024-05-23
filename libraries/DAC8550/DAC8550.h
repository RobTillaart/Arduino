#pragma once
//
//    FILE: DAC8550.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8550 SPI Digital Analog Convertor
// VERSION: 0.3.1
//    DATE: 2021-02-04
//     URL: https://github.com/RobTillaart/DAC8550


#include "Arduino.h"
#include "SPI.h"


#define DAC8550_LIB_VERSION            (F("0.3.1"))


#define DAC8550_POWERDOWN_NORMAL        0
#define DAC8550_POWERDOWN_1K            1
#define DAC8550_POWERDOWN_100K          2
#define DAC8550_POWERDOWN_HIGH_IMP      3


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


class DAC8550
{
public:
  DAC8550(uint8_t select, __SPI_CLASS__ * spi = &SPI);
  DAC8550(uint8_t select, uint8_t spiData, uint8_t spiClock);

  void     begin();

  void     setValue(uint16_t value);
  uint16_t getValue();

  void     setPowerDown(uint8_t powerDownMode);
  uint8_t  getPowerDownMode();

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };

  bool     usesHWSPI() { return _hwSPI; };


protected:
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;

  bool     _hwSPI       = false;
  uint16_t _value       = 0;
  uint8_t  _register    = 0;

  uint32_t _SPIspeed    = 16000000;

  void     updateDevice();
  void     swSPI_transfer(uint8_t value);


  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


//  -- END OF FILE --

