#pragma once
//
//    FILE: AD5370.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-02-24
// VERSION: 0.1.0
// PURPOSE: Arduino library for
//     URL: https://github.com/RobTillaart/AD5370
//


#include "Arduino.h"
#include "SPI.h"

#define AD5370_LIB_VERSION         (F("0.1.0"))

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


class AD5370
{
public:
  /////////////////////////////////////////////
  //
  //  CONSTRUCTORS
  //
  //  HARDWARE SPI
  AD5370(uint8_t select, uint8_t reset, uint8_t clear, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD5370(uint8_t select, uint8_t reset, uint8_t clear, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  void     begin();
  void     setBusyPin(uint8_t busyPin);
  void     setLDACPin(uint8_t ldacPin);


  /////////////////////////////////////////////
  //
  //  BASE WRITE
  //
  //  channel = 0..39
  //  value   = 0..65535  (assumes 16 bit)
  bool     setDAC(uint8_t channel, uint16_t value);     //  AB register
  bool     setGain(uint8_t channel, uint16_t value);    //  M  register
  bool     setOffset(uint8_t channel, uint16_t value);  //  C  register


  /////////////////////////////////////////////
  //
  //  GROUP COMMANDS
  //
  //  Table 11  column 000
  bool     setAllAllDAC(uint16_t value);
  bool     setGroupAllChannelDAC(uint8_t group, uint16_t value);
  //  Table 11  column 110
  bool     setAllGroupChannelDAC(uint8_t channel, uint16_t value);
  //  Table 11  column 111
  //  TODO  find better name.
  bool     set1234GroupChannelDAC(uint8_t channel, uint16_t value);


  /////////////////////////////////////////////
  //
  //  SPECIAL FUNCTIONS
  //
  //  Table 12 + 13 + 14 + 15
  //  read datasheet for appropriate values to use.
  //  functions do not all work as they should yet.
  //  need hardware to verify and test.
  //
  uint32_t writeNOP();  //  used to read back
  bool     writeControlRegister(uint8_t mask);
  bool     writeOffset0Register(uint16_t value);   //  14 bit 0..16383
  bool     writeOffset1Register(uint16_t value);   //  14 bit 0..16383
  bool     selectReadBackRegister(uint16_t selection);
  bool     writeABSelectRegister(uint8_t reg, uint8_t value);
  bool     blockABSelectRegister(uint8_t value);


  /////////////////////////////////////////////
  //
  //  SPI
  //
  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();


  /////////////////////////////////////////////
  //
  //  CONTROL SIGNALS
  //
  bool     isBusy();
  void     pulseLDAC();
  void     reset();
  void     clear();


  //  control any register manually.
  //  public for now.
  uint32_t updateDevice(uint32_t value, uint8_t bytes);


protected:
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  uint8_t  _busy;
  uint8_t  _ldac;
  uint8_t  _reset;
  uint8_t  _clear;
  bool     _hwSPI;
  uint32_t _SPIspeed = 1000000;

  //  transfers 24 bit.

  uint32_t swSPI_transfer(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


//  -- END OF FILE --





