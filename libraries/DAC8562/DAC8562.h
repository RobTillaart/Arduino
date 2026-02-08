#pragma once
//
//    FILE: DAC8562.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DAC8562 SPI 16 bit dual channel DAC.
// VERSION: 0.1.0
//    DATE: 2025-01-29
//     URL: https://github.com/RobTillaart/DAC8562
//


#include "Arduino.h"
#include "SPI.h"


#define DAC8562_LIB_VERSION            (F("0.1.0"))


#define DAC8562_POWERDOWN_NORMAL       0
#define DAC8562_POWERDOWN_1K           1
#define DAC8562_POWERDOWN_100K         2
#define DAC8562_POWERDOWN_HIGH_IMP     3


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


class DAC8562
{
public:
  //  select line == SYNC in datasheet.
  DAC8562(uint8_t select, __SPI_CLASS__ * spi = &SPI, uint8_t LDAC = 255, uint8_t CLR = 255);
  DAC8562(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC = 255, uint8_t CLR = 255);

  void     begin();

  void     setValue(uint16_t value);  //  both channels
  void     setValue(uint8_t channel, uint16_t value);  //  channel = 0, 1
  uint16_t getValue(uint8_t channel);  //  channel = 0, 1
  uint16_t getMaxValue();

  //  TODO LDAC pulse  HIGH LOW HIGH
  //  TODO CLR pulse   HIGH LOW HIGH

  //  TODO test, use with care
  void     setPowerDownMode(uint8_t powerDownMode);
  uint8_t  getPowerDownMode();

  //  TODO to be verified.
  void     enableInternalReference();
  void     disableInternalReference();

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };

  bool     usesHWSPI() { return _hwSPI; };


protected:
  uint8_t  _dataOut  = 255;
  uint8_t  _clock    = 255;
  uint8_t  _select   = 255;
  uint8_t  _LDAC     = 255;
  uint8_t  _CLR      = 255;

  bool     _hwSPI    = false;
  uint16_t _value[2];
  uint8_t  _bits     = 16;
  uint16_t _maxValue = 65535;

  bool     _midPoint = false;

  //  cache register
  //  0-1  power down bits
  uint8_t  _register = 0;


  uint32_t _SPIspeed = 16000000;

  void     updateDevice(uint32_t data, bool vref = false);
  void     swSPI_transfer(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};



////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class DAC7562 : public DAC8562
{
public:
  DAC7562(uint8_t select, __SPI_CLASS__ * spi = &SPI, uint8_t LDAC = 255, uint8_t CLR = 255);
  DAC7562(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC = 255, uint8_t CLR = 255);
};

class DAC7563 : public DAC8562
{
public:
  DAC7563(uint8_t select, __SPI_CLASS__ * spi = &SPI, uint8_t LDAC = 255, uint8_t CLR = 255);
  DAC7563(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC = 255, uint8_t CLR = 255);
};

class DAC8162 : public DAC8562
{
public:
  DAC8162(uint8_t select, __SPI_CLASS__ * spi = &SPI, uint8_t LDAC = 255, uint8_t CLR = 255);
  DAC8162(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC = 255, uint8_t CLR = 255);
};

class DAC8163 : public DAC8562
{
public:
  DAC8163(uint8_t select, __SPI_CLASS__ * spi = &SPI, uint8_t LDAC = 255, uint8_t CLR = 255);
  DAC8163(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC = 255, uint8_t CLR = 255);
};

class DAC8563 : public DAC8562
{
public:
  DAC8563(uint8_t select, __SPI_CLASS__ * spi = &SPI, uint8_t LDAC = 255, uint8_t CLR = 255);
  DAC8563(uint8_t select, uint8_t spiData, uint8_t spiClock, uint8_t LDAC = 255, uint8_t CLR = 255);
};


//  -- END OF FILE --

