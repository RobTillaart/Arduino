#pragma once
//
//    FILE: AD9833.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for AD9833 function generator.
//    DATE: 2023-08-25
// VERSION: 0.4.5
//     URL: https://github.com/RobTillaart/AD9833


#include "Arduino.h"
#include "SPI.h"


#define AD9833_LIB_VERSION     (F("0.4.5"))


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


#define AD9833_MAX_FREQ             (12500000UL)  //  12.5 MHz.
#define AD9833_MAX_PHASE            (360.0)


//  MODE OPERANDI
#define AD9833_OFF                  0
#define AD9833_SINE                 1
#define AD9833_SQUARE1              2
#define AD9833_SQUARE2              3
#define AD9833_TRIANGLE             4


//  POWER CONSTANTS
#define AD9833_PWR_ON               0
#define AD9833_PWR_DISABLE_DAC      1
#define AD9833_PWR_DISABLE_CLOCK    2
#define AD9833_PWR_DISABLE_ALL      3


//  ERROR CODES  (TODO to be implemented ?)
#define AD9833_OK                   0
#define AD9833_ERR_CHANNEL          -1
#define AD9833_ERR_WAVE             -2
#define AD9833_ERR_FREQUENCY        -3
#define AD9833_ERR_PHASE            -4
#define AD9833_ERR_GENERIC          -99


//  CONTROL REGISTER BITS
#define AD9833_B28          (1 << 13)
#define AD9833_HLB          (1 << 12)
#define AD9833_FSELECT      (1 << 11)
#define AD9833_PSELECT      (1 << 10)
#define AD9833_RESET        (1 << 8)
#define AD9833_SLEEP1       (1 << 7)
#define AD9833_SLEEP12      (1 << 6)
#define AD9833_OPBITEN      (1 << 5)
#define AD9833_DIV2         (1 << 3)
#define AD9833_MODE         (1 << 1)


class AD9833
{
public:
  //       slaveSelect == selectPin == fsyncPin
  //  HARDWARE SPI
  AD9833(uint8_t slaveSelect, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD9833(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock);

  void     begin();

  void     reset();
  void     hardwareReset();
  //       mode = 0..3 (datasheet table 14)
  //       see AD9833_PWR_xxx above
  bool     setPowerMode(uint8_t mode = 0);
  uint8_t  getPowerMode();

  void     setWave(uint8_t waveform = AD9833_OFF);
  uint8_t  getWave();

  //       set/get the useRounding flag for setFrequency and setPhase.
  void     setUseRounding(bool flag = true);
  bool     getUseRounding();

  //       returns frequency set
  //       0 .. 12.5 MHz == AD9833_MAX_FREQ
  float    setFrequency(float frequency, uint8_t channel = 0);
  float    getFrequency(uint8_t channel = 0);
  float    getMaxFrequency();
  void     setFrequencyChannel(uint8_t channel);

  //       returns phase set (degrees)
  //       [0 .. 360>
  float    setPhase(float phase, uint8_t channel = 0);
  float    getPhase(uint8_t channel = 0);
  float    getMaxPhase();
  void     setPhaseChannel(uint8_t channel);
  //       returns phase set (radians)
  //       [0 .. 2 PI>
  float    setPhaseRadians(float phase, uint8_t channel = 0);
  float    getPhaseRadians(uint8_t channel = 0);


  //       Hardware SPI settings
  void     setSPIspeed(uint32_t speed);  //  speed in Hz
  uint32_t getSPIspeed();
  bool     usesHWSPI();


  //  LOW LEVEL API - Expert users only
  void     writeControlRegister(uint16_t value);
  uint16_t readControlRegisterCache();
  void     writeFrequencyRegister(uint8_t channel, uint32_t freq);
  void     writePhaseRegister(uint8_t channel, uint16_t value);


  //  EXPERIMENTAL adjust changed crystal
  void     setCrystalFrequency(float crystalFrequency = 25000000);
  float    getCrystalFrequency();


  //  EXPERIMENTAL HLB MODE (14 bit)
  void     writeFrequencyRegisterLSB(uint8_t channel, uint16_t LSB);
  void     writeFrequencyRegisterMSB(uint8_t channel, uint16_t MSB);


  //  ERROR (prep)
  //  int getLastError();


private:
  void     writeData(uint16_t data);
  void     writeData28(uint16_t LSB, uint16_t MSB);

  bool     _hwSPI    = true;
  uint32_t _SPIspeed = 8000000;

  __SPI_CLASS__ * _mySPI;
  SPISettings     _spi_settings;

  //  PINS
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)
  volatile uint8_t *_dataOutRegister;
  uint8_t  _dataOutBit;
  volatile uint8_t *_clockRegister;
  uint8_t  _clockBit;
#endif
  uint8_t  _dataPin;
  uint8_t  _clockPin;
  uint8_t  _selectPin = 0;
  bool     _useSelect = false;
  bool     _useRounding = true;

  //  SIGNAL
  uint16_t _control   = 0;
  uint8_t  _waveform  = AD9833_OFF;

  float    _freq[2]   = { 0, 0 };  //  Hz
  float    _phase[2]  = { 0, 0 };  //  angle 0..360

  //  POW2TO28 / 25 MHz
  float    _crystalFreqFactor = 268435456.0 / 25000000.0;
};


//  --  END OF FILE --

