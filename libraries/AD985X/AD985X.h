#pragma once
//
//    FILE: AD985X.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.7.1
//    DATE: 2019-02-08
// PURPOSE: Class for AD9850 and AD9851 function generator
//     URL: https://github.com/RobTillaart/AD985X


#include "Arduino.h"
#include "SPI.h"


#define AD985X_LIB_VERSION        (F("0.7.1"))


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


#define AD9850_MAX_FREQ           (40UL * 1000UL * 1000UL)
#define AD9851_MAX_FREQ           (70UL * 1000UL * 1000UL)

#define AD9851_ARC_CUTOFF_FREQ    (10000000UL)


/////////////////////////////////////////////////////////////////////
//
//  BASE CLASS AD9850
//
class AD9850
{
public:
  //  HARDWARE SPI
  //  spiClock needed for RESET(). TODO: nicer solution?
  AD9850(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, __SPI_CLASS__ * mySPI, uint8_t spiClock);
  //  SOFTWARE SPI
  AD9850(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, uint8_t spiData, uint8_t spiClock);

  void     begin();
  void     reset();
  void     powerDown();
  void     powerUp();


  //  returns false if limited to AD9850_MAX_FREQ
  bool     setFrequency(uint32_t freq);         //  0..AD9850_MAX_FREQ
  bool     setFrequencyF(float freq);           //  works best for low frequencies.
  float    getFrequency();
  uint32_t getMaxFrequency();

  //  0 .. 31  steps of 11.25 degrees
  //  returns false if phase > 31.
  bool     setPhase(uint8_t phase = 0);
  uint8_t  getPhase();


  //  offset to calibrate the frequency (internal counter)
  //  offset must be stored by the user.
  void     setCalibration(int32_t offset = 0) { _offset = offset; };
  int32_t  getCalibration() { return _offset; };


  //       autoUpdate is default true;
  void     setAutoUpdate(bool update = true) { _autoUpdate = update; };
  bool     getAutoUpdate() { return _autoUpdate; };
  void     update();


  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed() { return _SPIspeed; };

  //  debugging
  bool     usesHWSPI() { return _hwSPI; };
  //  internal chip factor used for frequency. (debugging only)
  uint32_t getFactor() { return _factor; };


protected:
  void     pulsePin(uint8_t pin);
  void     writeData();
  void     swSPI_transfer(uint8_t val);

  bool     _hwSPI    = true;
  uint32_t _SPIspeed = 2000000;

  __SPI_CLASS__ * _mySPI;
  SPISettings     _spi_settings;

  //  PINS
  uint8_t  _dataOut = 0;
  uint8_t  _clock   = 0;
  uint8_t  _select  = 0;
  uint8_t  _reset   = 0;
  uint8_t  _fqud    = 0;  //  frequency update

  //  SIGNAL
  float    _freq    = 1;
  uint32_t _factor  = 0;
  uint8_t  _config  = 0;
  int32_t  _offset  = 0;
  bool     _autoUpdate  = true;
  //  _factoryMask see PR #32,
  //  0xFD is safe value for both AD9850/51
  uint8_t _factoryMask = 0xFD;
};


/////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS AD9851
//
class AD9851 : public AD9850
{
public:
  //  HARDWARE SPI
  //  spiClock needed for RESET(). TODO: nicer solution?
  AD9851(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, __SPI_CLASS__ * mySPI, uint8_t spiClock);
  //  SOFTWARE SPI
  AD9851(uint8_t slaveSelect, uint8_t resetPin, uint8_t FQUDPin, uint8_t spiData, uint8_t spiClock);


  //  returns false if limited to AD9851_MAX_FREQ
  bool     setFrequency(uint32_t freq);    //  0..AD9851_MAX_FREQ
  bool     setFrequencyF(float freq);      //  works best for low frequencies.
  uint32_t getMaxFrequency();


  void     setRefClockHigh();              //  180 MHz
  void     setRefClockLow();               //   30 MHz
  uint8_t  getRefClock();                  //  returns 180 or 30


  void     setAutoRefClock(bool arc);
  bool     getAutoRefClock();


  //  10 MHz is default, set in Hz.
  //  will be kept <= 30 MHz as that is the freq of LOW mode.
  //  ARC = AutoRefClock
  void     setARCCutOffFreq(uint32_t Hz = AD9851_ARC_CUTOFF_FREQ);
  uint32_t getARCCutOffFreq();


protected:
  bool     _autoRefClock = false;
  uint32_t _ARCCutOffFreq = AD9851_ARC_CUTOFF_FREQ;

};


//  -- END OF FILE --

