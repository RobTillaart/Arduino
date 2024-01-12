#pragma once
//
//    FILE: ADC081S.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2024-01-10
// PURPOSE: Arduino library for ADC081S 8 bit ADC (SPI)
//     URL: https://github.com/RobTillaart/ADC081S
//


#include "Arduino.h"
#include "SPI.h"


#define ADC081S_LIB_VERSION       (F("0.1.0"))


#ifndef __SPI_CLASS__
  #if defined(ARDUINO_ARCH_RP2040)
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

  uint16_t  maxValue();
  uint16_t  read();


  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();

  //       debugging
  bool     usesHWSPI();
  uint32_t count();  //  number of channels read.


protected:
  uint8_t  _dataIn;
  uint8_t  _clock;
  uint8_t  _select;

  bool     _hwSPI;
  uint16_t _maxValue;
  uint16_t readADC();

  uint16_t swSPI_transfer16();

  //  1 MHz is a safe value (datasheet); in a test 4 MHz worked.
  uint32_t        _SPIspeed = 1000000;
  __SPI_CLASS__ * _mySPI;
  SPISettings     _spi_settings;

  uint32_t _count;
};


//////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//

//  TODO


//  -- END OF FILE --