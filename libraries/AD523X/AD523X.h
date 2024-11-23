#pragma once
//
//    FILE: AD523X.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-21
// VERSION: 0.1.0
// PURPOSE: Arduino library for SPI AD5231 and AD5235 10 bit digital potentiometers.
//     URL: https://github.com/RobTillaart/AD523X


#include "Arduino.h"
#include "SPI.h"


#define AD523X_LIB_VERSION              (F("0.1.0"))

#define AD523X_MIDDLE_VALUE             512
#define AD523X_MAX_VALUE                1023



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


class AD523X
{
public:
  //  HARDWARE SPI
  AD523X(uint8_t select, uint8_t reset, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD523X(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  void     begin(uint16_t value = AD523X_MIDDLE_VALUE);
  void     reset(uint16_t value = AD523X_MIDDLE_VALUE);
  void     resetDevice();
  uint8_t  pmCount();

  //  VALUE
  bool     setValue(uint16_t value);
  bool     setValue(uint8_t pm, uint16_t value);
  uint16_t getValue(uint8_t pm);
  bool     setAll(uint16_t value);  //  DUAL only

  //  PERCENTAGE
  bool     setPercentage(uint8_t pm, float percentage);
  float    getPercentage(uint8_t pm);
  bool     setPercentageAll(float percentage);

  //  incr/decr interface here TODO
  //  void     decrement6DB(uint8_t pm = 0);
  //  void     decrementOne(uint8_t pm = 0);
  //  void     increment6DB(uint8_t pm = 0);
  //  void     incrementOne(uint8_t pm = 0);

  //       EEMEM
  uint32_t rawRead();  //  needed by some commands.
  //  load wiper position from eemem
  void     loadWiperEEMEM(uint8_t pm = 0);
  //  store current wiper position.
  void     storeWiperEEMEM(uint8_t pm = 0);
  //  load previous stored value from eemem
  uint16_t loadEEMEM(uint8_t address);
  //  store address 0 from value iso wiper position (AD5231/5)
  //  store address 1 from value iso wiper position (AD5235)
  //  store address 1 from value to write O1, O2    (AD5231) P08
  void     storeEEMEM(uint8_t address, uint16_t value);


  //       SPI - speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();

protected:
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  uint8_t  _reset;
  bool     _hwSPI;
  uint32_t _SPIspeed = 16000000;

  uint16_t _value[2] = {0, 0 };
  uint8_t  _pmCount = 2;

  uint32_t updateDevice(uint8_t pm, uint16_t value);
  uint8_t  swSPI_transfer(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


/////////////////////////////////////////////////////////////////////////////
//
// DERIVED CLASSES
//
class AD5231 : public AD523X
{
public:
  AD5231(uint8_t select, uint8_t reset, __SPI_CLASS__ * mySPI = &SPI);
  AD5231(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


class AD5235 : public AD523X
{
public:
  AD5235(uint8_t select, uint8_t reset, __SPI_CLASS__ * mySPI = &SPI);
  AD5235(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


//  -- END OF FILE --
