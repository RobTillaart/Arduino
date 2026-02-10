#pragma once
//
//    FILE: BL0942_SPI.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-12-29
// VERSION: 0.1.2
// PURPOSE: Arduino library for BL0942 energy monitor, SPI interface.
//     URL: https://github.com/RobTillaart/BL0942_SPI
//
//  uses MODE1, CPOL = 0, CPHA = 1
//
//  explain connections for SPI
//  UART/SPI mode selection (0==UART 1==SPI), internal pull-down resistor,
//  connected to GND is 0 level (UART == not supported in this library)
//  connected to VDD is high level (SPI)


#include "Arduino.h"
#include "SPI.h"


//  Open KNX extra API  (Andreas B.)
#ifdef BL0942_SPI_CALLBACK
#include <functional>
#endif


#define BL0942_SPI_LIB_VERSION         (F("0.1.2"))

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


//
//  ERROR CONSTANTS
//
const int BL0942_OK = 0;
const int BL0942_ERR_WRITE = -1;
const int BL0942_ERR_READ = -2;
const int BL0942_ERR_CHECKSUM = -3;


//
//  MODE REGISTER (0x19) BIT MASKS
//  read datasheet page 10 for details
//  bits 0,1,10..15 are reserved.
//
const int BL0942_MODE_CF_DISABLE          = 0x0000;
const int BL0942_MODE_CF_ENABLE           = 0x0004;
const int BL0942_MODE_RMS_UPDATE_400MS    = 0x0000;  //  default
const int BL0942_MODE_RMS_UPDATE_800MS    = 0x0008;
const int BL0942_MODE_RMS_WAVEFORM_FULL   = 0x0000;
const int BL0942_MODE_RMS_WAVEFORM_AC     = 0x0010;
const int BL0942_MODE_AC_FREQUENCY_50HZ   = 0x0000;
const int BL0942_MODE_AC_FREQUENCY_60HZ   = 0x0020;
const int BL0942_MODE_CNT_CLR_SEL_DISABLE = 0x0000;
const int BL0942_MODE_CNT_CLR_SEL_ENABLE  = 0x0040;
const int BL0942_MODE_ACCU_MODE_ALGEBRAIC = 0x0000;
const int BL0942_MODE_ACCU_MODE_ABSOLUTE  = 0x0080;
const int BL0942_MODE_UART_4800           = 0x0000;
const int BL0942_MODE_UART_9600           = 0x0100;
const int BL0942_MODE_UART_19200          = 0x0200;
const int BL0942_MODE_UART_38400          = 0x0300;


//
//  OUTPUT CONFIG REGISTER (0x18) BIT MASKS
//  read datasheet page 11 for details
//
const int BL0942_CF1_ACTIVE_ENERGY = 0x00;  //  default
const int BL0942_CF1_OVER_CURRENT  = 0x01;
const int BL0942_CF1_ZERO_CROSS_V  = 0x02;
const int BL0942_CF1_ZERO_CROSS_I  = 0x03;

const int BL0942_CF2_ACTIVE_ENERGY = 0x00;
const int BL0942_CF2_OVER_CURRENT  = 0x04;  //  default
const int BL0942_CF2_ZERO_CROSS_V  = 0x08;
const int BL0942_CF2_ZERO_CROSS_I  = 0x0C;

const int BL0942_ZX_ACTIVE_ENERGY  = 0x00;
const int BL0942_ZX_OVER_CURRENT   = 0x10;
const int BL0942_ZX_ZERO_CROSS_V   = 0x20;  //  default
const int BL0942_ZX_ZERO_CROSS_I   = 0x30;


//
//  STATUS REGISTER (0x09) BIT MASKS
//  read datasheet page 11 for details
//
const int BL0942_STAT_CF_REVP  = 0x0001;
const int BL0942_STAT_CREEP    = 0x0002;
const int BL0942_STAT_I_ZX_LTH = 0x0100;
const int BL0942_STAT_V_ZX_LTH = 0x0200;


//
//  GAIN REGISTER (0x1A) BIT MASKS
//  read datasheet page 11 for details
//
const int BL0942_GAIN_1  = 0x00;
const int BL0942_GAIN_4  = 0x01;
const int BL0942_GAIN_16 = 0x02;  //  default
const int BL0942_GAIN_24 = 0x03;


class BL0942_SPI
{
public:
  //  HARDWARE SPI
  BL0942_SPI(__SPI_CLASS__ * mySPI = &SPI);
  BL0942_SPI(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI  (dataIn == "MISO", dataOut == "MOSI")
  BL0942_SPI(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  bool     begin();

  //  Open KNX extra API
#ifdef BL0942_SPI_CALLBACK
  using ChannelSelector = std::function<void(bool active)>;
  void setChannelSelector(ChannelSelector selector);
#endif


  //  CALIBRATION
  void     calibrate(float shunt, float reductionFactor = 1.0f);
  //  direct calibration of the least significant bits per measurement.
  float    getVoltageLSB();
  void     setVoltageLSB(float voltageLSB);
  float    getCurrentLSB();
  void     setCurrentLSB(float currentLSB);
  float    getPowerLSB();
  void     setPowerLSB(float powerLSB);
  float    getEnergyLSB();
  void     setEnergyLSB(float energyLSB);
  //  GET MAXIMA
  //  derived from calibration data.
  float    getMaxCurrent();
  float    getMaxVoltage();
  float    getMaxCurrentRMS();
  float    getMaxVoltageRMS();


  //  READ ONLY registers
  float    getIWave();
  float    getVWave();
  float    getIRMS();
  float    getVRMS();
  float    getIRMSFast();     //  see setFastRMSThreshold()
  float    getWatt();
  uint32_t getCFPulseCount();
  float    getEnergy();       //  kWh
  float    getFrequency();

  //  status bit masks see above
  uint16_t getStatus();


  //  READ WRITE registers
  //  offset in Amperes.
  float    getCurrentRMSOffset();
  void     setCurrentRMSOffset(float offset);


  //  watt = creep level in Watt.
  float    getPowerCreep();
  void     setPowerCreep(float watt);


  //  threshold in Amperes (?)
  //  If I_FAST_RMS[23:8] >= I_FAST_RMS_TH[15:0] ==> flag
  //  ???  only 16 upper bits compared to 16 bit value
  //  ==> there must be a factor 256 somewhere.
  float    getFastRMSThreshold();
  void     setFastRMSThreshold(float threshold);


  //  cycles
  //  0    == 0.5 cycles
  //  1    == 1 cycles
  //  2    == 2 cycles
  //  3    == 4 cycles
  //  4..7 == 8 cycles  (values above 7 => 7)
  uint8_t  getFastRMSCycles();
  void     setFastRMSCycles(uint8_t cycles);


  //  cycles
  //  0 == 2 cycles
  //  1 == 4 cycles
  //  2 == 8 cycles
  //  3 == 16 cycles  (values above 3 => 3)
  uint8_t  getFrequencyCycles();
  void     setFrequencyCycles(uint8_t cycles);

  //  bit masks see above
  //  mask = 0..0x3F
  uint8_t  getOutputConfigMask();
  void     setOutputConfigMask(uint8_t mask);

  //  bit masks see above
  //  mode = 0x0000 .. 0x03FF
  uint16_t getUserMode();
  void     setUserMode(uint16_t mode);

  //  bit masks see above
  //  gain = 0..3
  //  0 == 1x
  //  1 == 4x
  //  2 == 16x
  //  3 == 24x  (values above 3 ==> 3)
  uint8_t  getCurrentGain();
  void     setCurrentGain(uint8_t gain);

  void     softReset();

  //  true  = write protected
  //  false = write allowed
  uint8_t  getWriteProtect();
  void     setWriteProtect(bool wp);


  //       SPI
  //       900 KHz max
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();
  //  datasheet 3.1.3 - to be tested.
  //  use with care as it resets configuration
  void     resetSPI();


  //       ERROR
  int      getLastError();
  uint32_t errorCount() { return _errorCount; };

  //  should be protected
  //  for now available for testing
  int      writeRegister(uint8_t regAddr, uint32_t value);
  uint32_t readRegister(uint8_t regAddr);


private:
  uint8_t  _dataOut;
  uint8_t  _dataIn;
  uint8_t  _select;
  uint8_t  _clock;
  int      _error;
  uint32_t _errorCount = 0;

  //  (semi) constants to set in calibrate() et al..
  float    _powerLSB      = 1.0;
  float    _voltageLSB    = 1.0;
  float    _currentLSB    = 1.0;
  float    _energyLSB     = 1.0;


  bool     _hwSPI;
  uint32_t _SPIspeed = 100000;
  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;

  // int      writeRegister(uint8_t regAddr, uint32_t value);
  // uint32_t readRegister(uint8_t regAddr);
  uint8_t  swSPI_transfer(uint8_t val);

  void select(bool active);

#ifdef BL0942_SPI_CALLBACK
  ChannelSelector _channelSelector = nullptr;
#endif
};


//  -- END OF FILE --

