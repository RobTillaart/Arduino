#pragma once
//
//    FILE: AD568X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2023-09-18
// PURPOSE: Arduino library for AD568X series Digital Analog Convertor.
//     URL: https://github.com/RobTillaart/AD568X


#include "Arduino.h"
#include "SPI.h"

#define AD568X_LIB_VERSION        (F("0.3.1"))


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


#define AD568X_PWR_NORMAL         0x00
#define AD568X_PWR_1K             0x01
#define AD568X_PWR_100K           0x02
#define AD568X_PWR_TRI_STATE      0x03


class AD568X
{
public:
  //  HARDWARE SPI
  AD568X(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD568X(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);


  void     begin();
  uint8_t  getType();

  //  optional LDAC interface
  void     setLDACPin(uint8_t ldac);
  bool     triggerLDAC();  //  return false if pin not set.

  //  SET DAC
  //  sets output immediately = prepare + update.
  bool     setValue(uint16_t value);
  uint16_t getValue();
  bool     setPercentage(float percentage);
  float    getPercentage();


  //  prep & update separately
  bool     prepareValue(uint16_t value);
  bool     updateValue();


  //  CONTROL REGISTER (see datasheet)
  //  bit     meaning
  //   15     reset
  //   14     power down 1
  //   13     power down 0
  //   12     REFerence selection
  //   11     GAIN
  //   10     DCEN, Daisy Chain ENable
  //  other   0
  //  set register in one call.
  bool     setControlRegister(uint16_t value);
  uint16_t getControlRegister();

  bool     reset();
  bool     setPowerDownMode(uint8_t mode = AD568X_PWR_NORMAL);
  bool     disableReference(bool b);
  bool     enableGain(bool enable = false);
  bool     enableDaisyChain(bool enable = false);


  //  SPI
  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();


protected:
  uint8_t  _type        = 0;      //  # bits
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;
  uint8_t  _ldac        = 255;

  uint16_t _value       = 0;
  uint16_t _controlReg  = 0;

  bool     _hwSPI       = false;
  uint32_t _SPIspeed    = 16000000;

  void     updateDevice(uint8_t cmd, uint16_t value);
  void     updateDevice(uint8_t a, uint8_t b, uint8_t c);
  void     swSPI_transfer(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
// class AD5680 : public AD568X   need 32 bit value...etc
// {
// public:
  // AD5680(uint8_t slaveSelect);
  // AD5680(uint8_t spiData, uint8_t spiClock, uint8_t slaveSelect);
// };


class AD5681R : public AD568X
{
public:
  //  HARDWARE SPI
  AD5681R(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5681R(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);
};


class AD5682R : public AD568X
{
public:
  //  HARDWARE SPI
  AD5682R(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5682R(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);
};


class AD5683R : public AD568X
{
public:
  //  HARDWARE SPI
  AD5683R(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5683R(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);

};


class AD5683 : public AD568X
{
public:
  //  HARDWARE SPI
  AD5683(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5683(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);

};


//  -- END OF FILE --

