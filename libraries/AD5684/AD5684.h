#pragma once
//
//    FILE: AD5684.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-04-20
// PURPOSE: Arduino library for AD5684/5/6 4 channel SPI-DAC (12/14/16 bit).


#include "Arduino.h"
#include "SPI.h"


#define AD5684_LIB_VERSION        (F("0.1.0"))

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


//  not all "commands" implemented                  //  IMPLEMENTED
//  datasheet page 20, table 8
constexpr uint8_t AD5684_REG_NOP           = 0x00;  //
constexpr uint8_t AD5684_REG_WRITE         = 0x10;  //  YES
constexpr uint8_t AD5684_REG_UPDATE        = 0x20;  //  YES
constexpr uint8_t AD5684_REG_WRITE_UPDATE  = 0x30;  //  YES
constexpr uint8_t AD5684_REG_POWER_UPDOWN  = 0x40;  //  YES
constexpr uint8_t AD5684_REG_LDAC_MASK     = 0x50;  //
constexpr uint8_t AD5684_REG_SW_RESET      = 0x60;  //  YES
constexpr uint8_t AD5684_REG_SETUP_INT_REF = 0x70;  //
constexpr uint8_t AD5684_REG_SETUP_DCEN    = 0x80;  //
constexpr uint8_t AD5684_REG_READ_BACK     = 0x90;  //
constexpr uint8_t AD5684_REG_NOP_DC_MODE   = 0xF0;  //



//  setPowenMode()
constexpr uint8_t AD5684_PWR_NORMAL    = 0x00;
constexpr uint8_t AD5684_PWR_1K        = 0x01;
constexpr uint8_t AD5684_PWR_100K      = 0x02;
constexpr uint8_t AD5684_PWR_TRI_STATE = 0x03;



class AD5684
{
public:
  //  HARDWARE SPI
  AD5684(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5684(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);

  void     begin();
  uint8_t  getType();

  //  optional LDAC interface
  void     setLDACPin(uint8_t ldac);
  bool     triggerLDAC();  //  return false if pin not set.

  //  optional RESET interface
  //  optional RESETSELECT interface  zero or midscale
  //  optional GAIN interface


  //  SET DAC
  //  sets output immediately = prepare + update.
  //  channel = 0..3
  bool     setValue(uint8_t channel, uint16_t value);
  bool     setAll(uint16_t value);  //  table 9
  uint16_t getValue(uint8_t channel);  //  get from cache.
  uint16_t getMaxValue();
  //  wrapper around get/setValue
  bool     setPercentage(uint8_t channel, float percentage);
  float    getPercentage(uint8_t channel);


  //  prep separately and update simultaneously
  bool     prepareValue(uint8_t channel, uint16_t value);
  bool     updateAll();


  //  CONTROL REGISTERS - see datasheet for details.
  //
  //  generic command to control all registers
  //          not (fully) supported in the library yet.
  void     sendCommand(uint8_t command, uint8_t channel, uint16_t data);

  //  TODO - affects output values?
  bool     softwareReset();
  //  sets all channels power mode
  bool     setPowerDownMode(uint8_t mode = AD5684_PWR_NORMAL);



  //  SPI
  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();


protected:
  uint8_t  _type        = 12;    //  #bits
  uint16_t _maxValue    = 4095;  //  0x0FFF
  uint8_t  _dataOut     = 255;
  uint8_t  _clock       = 255;
  uint8_t  _select      = 255;
  uint8_t  _ldac        = 255;

  uint16_t _value[4]    = {0,0,0,0};

  bool     _hwSPI       = false;
  uint32_t _SPIspeed    = 16000000;

  void     updateDevice(uint8_t command, uint8_t channel, uint16_t data);
  void     swSPI_transfer(uint8_t data);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


///////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class AD5685 : public AD5684
{
public:
  //  HARDWARE SPI
  AD5685(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5685(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);
};

class AD5686 : public AD5684
{
public:
  //  HARDWARE SPI
  AD5686(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5686(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);
};

//  -- END OF FILE --
