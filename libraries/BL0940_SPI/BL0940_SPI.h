#pragma once
//
//    FILE: BL0940_SPI.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-02-03
// VERSION: 0.1.0
// PURPOSE: Arduino library for BL0940 energy monitor, SPI interface.
//     URL: https://github.com/RobTillaart/BL0940_SPI
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
#ifdef BL0940_SPI_CALLBACK
#include <functional>
#endif


#define BL0940_SPI_LIB_VERSION         (F("0.1.0"))

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
const int BL0940_OK = 0;
const int BL0940_ERR_WRITE = -1;
const int BL0940_ERR_READ = -2;
const int BL0940_ERR_CHECKSUM = -3;


//
//  MODE REGISTER (0x18) BIT MASKS
//  read datasheet page 9 for details
//  other bits are reserved.
//
const int BL0940_MODE_RMS_UPDATE_400MS    = 0x0000;  //  default
const int BL0940_MODE_RMS_UPDATE_800MS    = 0x0100;
const int BL0940_MODE_AC_FREQUENCY_50HZ   = 0x0000;  //  default
const int BL0940_MODE_AC_FREQUENCY_60HZ   = 0x0200;
const int BL0940_MODE_CF_ENERGY           = 0x0000;  //  default
const int BL0940_MODE_CF_ALARM            = 0x1000;

//
//  TEMPERATURE CONTROL REGISTER (0x1B) BIT MASKS
//  read datasheet page 10 for details
//  TODO  5 fields.
//  for now RAW.
//
//  TODO - check select pin in constructor
//         does the device has such pin?



class BL0940_SPI
{
public:
  //  HARDWARE SPI
  BL0940_SPI(__SPI_CLASS__ * mySPI = &SPI);
  BL0940_SPI(uint8_t select, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI  (dataIn == "MISO", dataOut == "MOSI")
  BL0940_SPI(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  bool     begin();

  //  Open KNX extra API
#ifdef BL0940_SPI_CALLBACK
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
  float    getIRMSFast();
  float    getIWave();
  float    getVWave();
  float    getIRMS();
  float    getVRMS();
  //
  float    getWatt();
  uint32_t getCFPulseCount();
  float    getEnergy();       //  kWh
  float    getPhaseAngle();
  //  10 bits
  float    getIntTemperature();
  float    getExtTemperature();


  //  READ WRITE registers
  //  datasheet P.18/19
  //  15 bits fast RMS threshold time.
  uint16_t getFastRMSControl();
  //  0 = half cycle, 1 = full cycle.
  //  no getter for full/half cycle TODO?
  void     setFastRMSControl(uint16_t ctrl, bool half = false);
  //  offset in Amperes.
  float    getCurrentRMSOffset();
  void     setCurrentRMSOffset(float offset);

  //  watt = offset in Watt.
  float    getPowerOffset();
  void     setPowerOffset(float deltaWatt);
  //  watt = creep level in Watt.
  float    getPowerCreep();
  void     setPowerCreep(float watt);

  //  bit masks see above
  //  mode = 0x0000 .. 0xFFFF
  uint16_t getUserMode();
  void     setUserMode(uint16_t mode);
  //  reset
  void     softReset();
  //  true  = write protected
  //  false = write allowed
  uint8_t  getWriteProtect();
  void     setWriteProtect(bool wp);


  //  TODO bit masks? + doc.
  uint16_t getTemperatureControl();
  void     setTemperatureControl(uint16_t ctrl);
  //  TODO bit masks? + doc.
  uint16_t getExtTempGain();
  void     setExtTempGain(uint16_t gain);
  //  TODO bit masks? + doc.
  uint16_t getExtTempOffset();
  void     setExtTempOffset(uint16_t offset);


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

#ifdef BL0940_SPI_CALLBACK
  ChannelSelector _channelSelector = nullptr;
#endif
};


//  -- END OF FILE --

