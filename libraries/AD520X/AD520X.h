#pragma once
//
//    FILE: AD520X.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-24
// VERSION: 0.5.1
// PURPOSE: Arduino library for AD5204 and AD5206 digital potentiometers
//          (+ AD8400, AD8402, AD8403)
//     URL: https://github.com/RobTillaart/AD520X


#include "Arduino.h"
#include "SPI.h"


#define AD520X_LIB_VERSION              (F("0.5.1"))

#ifndef AD520X_MIDDLE_VALUE
#define AD520X_MIDDLE_VALUE             128
#endif


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


class AD520X
{
public:
  //  HARDWARE SPI
  AD520X(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD520X(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);

  void     begin(uint8_t value = AD520X_MIDDLE_VALUE);
  void     reset(uint8_t value = AD520X_MIDDLE_VALUE);

  //  MONO / SINGLE
  bool     setValue(uint8_t pm = 0, uint8_t value = AD520X_MIDDLE_VALUE);
  uint8_t  getValue(uint8_t pm = 0);
  //  STEREO / DOUBLE
  bool     setValue(uint8_t pmA, uint8_t pmB, uint8_t value);
  //  GROUP
  void     setAll(uint8_t value = AD520X_MIDDLE_VALUE);
  void     setGroupValue(uint8_t mask, uint8_t value = AD520X_MIDDLE_VALUE);


  //  MONO / SINGLE
  bool     setPercentage(uint8_t pm = 0, float percentage = 50);
  float    getPercentage(uint8_t pm = 0);
  //  STEREO / DOUBLE
  bool     setPercentage(uint8_t pmA, uint8_t pmB, float percentage);
  //  GROUP
  void     setGroupPercentage(uint8_t mask, float percentage);


  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();


  //       MISC
  uint8_t  pmCount();
  void     powerOn();
  void     powerOff();;
  bool     isPowerOn();


  //       Debugging
  bool     usesHWSPI();


protected:
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  uint8_t  _reset;
  uint8_t  _shutdown;
  bool     _hwSPI;
  uint32_t _SPIspeed = 16000000;

  uint8_t  _value[6];
  uint8_t  _pmCount = 6;

  void     updateDevice(uint8_t pm, uint8_t value);
  void     swSPI_transfer(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


/////////////////////////////////////////////////////////////////////////////
//
// DERIVED CLASSES
//
class AD5206 : public AD520X
{
public:
  AD5206(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  AD5206(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};


class AD5204 : public AD520X
{
public:
  AD5204(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  AD5204(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};


class AD8400 : public AD520X
{
public:
  AD8400(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  AD8400(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};


class AD8402 : public AD520X
{
public:
  AD8402(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  AD8402(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};


class AD8403 : public AD520X
{
public:
  AD8403(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  AD8403(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};

//  -- END OF FILE --
