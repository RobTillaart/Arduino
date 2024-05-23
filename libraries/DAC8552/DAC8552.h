#pragma once
//
//    FILE: DAC8552.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8552 SPI Digital Analog Convertor  
// VERSION: 0.5.1
//    DATE: 2017-12-14
//     URL: https://github.com/RobTillaart/DAC8552


#include "Arduino.h"
#include "SPI.h"


#define DAC8552_LIB_VERSION           (F("0.5.1"))


#define DAC8552_POWERDOWN_NORMAL      0
#define DAC8552_POWERDOWN_1K          1
#define DAC8552_POWERDOWN_100K        2
#define DAC8552_POWERDOWN_HIGH_IMP    3


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


class DAC8552
{
public:
  DAC8552(uint8_t select, __SPI_CLASS__ * spi = &SPI);
  DAC8552(uint8_t select, uint8_t spiData, uint8_t spiClock);

  void     begin();

  void     bufferValue(uint8_t channel, uint16_t value);
  void     setValue(uint8_t channel, uint16_t value);
  uint16_t getValue(uint8_t channel);

  void     bufferPowerDown(uint8_t channel, uint8_t powerDownMode);
  void     setPowerDown(uint8_t channel, uint8_t powerDownMode);
  uint8_t  getPowerDownMode(uint8_t channel);

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };

  bool     usesHWSPI() { return _hwSPI; };


protected:
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;
  
  bool     _hwSPI       = false;
  uint16_t _value[2];
  uint8_t  _register[2];

  uint32_t _SPIspeed    = 16000000;

  void     updateDevice(uint8_t channel, bool directWrite);
  void     swSPI_transfer(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings    _spi_settings;
};


/////////////////////////////////////////////////////////
//
// DERIVED DAC8532
//

#define DAC8532_POWERDOWN_NORMAL       0
#define DAC8532_POWERDOWN_1K           1
#define DAC8532_POWERDOWN_100K         2
#define DAC8532_POWERDOWN_HIGH_IMP     3


class DAC8532 : public DAC8552
{
public:
  DAC8532(uint8_t select, __SPI_CLASS__ * spi = &SPI);
  DAC8532(uint8_t select, uint8_t spiData, uint8_t spiClock);
};


//  -- END OF FILE --

