#pragma once
//
//    FILE: AD5660.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-10-29
// PURPOSE: Arduino library for AD5660 Digital Analog Convertor (16 bit).


#include "Arduino.h"
#include "SPI.h"


#define AD5660_LIB_VERSION        (F("0.1.1"))

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


class AD5660
{
public:
  //  HARDWARE SPI
  AD5660(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5660(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);

  void     begin();
  uint8_t  getType();

  //  SET DAC
  //  sets output immediately = prepare + update.
  bool     setValue(uint16_t value = 0);
  uint16_t getValue();
  uint16_t getMaxValue();
  bool     setPercentage(float percentage);
  float    getPercentage();

  //  POWER DOWN
  bool     setPowerDownMode(uint8_t mode);
  uint8_t  getPowerDownMode();

  //  SPI
  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();


protected:
  uint8_t  _type;  //  #bits
  uint16_t _maxValue;
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;

  uint16_t _value       = 0;
  //  power down mode P19.
  uint8_t  _powerMode   = 0;

  bool     _hwSPI       = false;
  uint32_t _SPIspeed    = 16000000;

  void     updateDevice(uint32_t data);
  void     swSPI_transfer(uint32_t data);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


//  -- END OF FILE --
