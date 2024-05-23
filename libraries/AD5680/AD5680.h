#pragma once
//
//    FILE: AD5680.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2023-09-19
// PURPOSE: Arduino library for AD5680 Digital Analog Convertor (18 bit).


#include "Arduino.h"
#include "SPI.h"

#define AD5680_LIB_VERSION        (F("0.3.1"))

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


class AD5680
{
public:
  //  HARDWARE SPI
  AD5680(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5680(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);

  void     begin();
  uint8_t  getType();


  //  SET DAC
  //  sets output immediately = prepare + update.
  bool     setValue(uint32_t value = 0);
  uint32_t getValue();
  bool     setPercentage(float percentage);
  float    getPercentage();

  //  SPI
  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();


protected:
  uint8_t  _type        = 18;      //  # bits
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;

  uint32_t _value       = 0;

  bool     _hwSPI       = false;
  uint32_t _SPIspeed    = 16000000;

  void     updateDevice(uint32_t value);
  void     swSPI_transfer(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


//  -- END OF FILE --
