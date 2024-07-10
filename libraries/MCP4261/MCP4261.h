#pragma once
//
//    FILE: MCP4261.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2024-02-21
// PURPOSE: Arduino library for MCP4261 SPI based digital potentiometers.
//     URL: https://github.com/RobTillaart/MCP4261


#include "Arduino.h"
#include "SPI.h"


#define MCP4261_LIB_VERSION           (F("0.2.0"))


#ifndef MCP41XX_MIDDLE_VALUE
#define MCP41XX_MIDDLE_VALUE          64
#endif

#ifndef MCP41XX_MAX_VALUE
#define MCP41XX_MAX_VALUE             128
#endif


#ifndef MCP42XX_MIDDLE_VALUE
#define MCP42XX_MIDDLE_VALUE          128
#endif

#ifndef MCP42XX_MAX_VALUE
#define MCP42XX_MAX_VALUE             256
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


class MCP4261
{
public:
  //       HARDWARE SPI
  MCP4261(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  //       SOFTWARE SPI
  MCP4261(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  void     begin();
  void     reset(uint16_t value);
  uint8_t  pmCount();

  //
  //  SET VOLATILE VALUE
  //
  //       set both potmeters (just a wrapper)
  bool     setValue(uint16_t value);
  //       set single potmeter (0 or 1)
  bool     setValue(uint8_t pm, uint16_t value);
  //       from cache or device
  uint16_t getValue(uint8_t pm = 0);
  uint16_t getValueDevice(uint8_t pm = 0);

  bool     incrValue(uint8_t pm = 0);
  bool     decrValue(uint8_t pm = 0);

  //
  //  SET NON-VOLATILE VALUE
  //
  bool     setValueNV(uint8_t pm, uint16_t value);
  uint16_t getValueNV(uint8_t pm);  //  always from device

  //
  //  TERMINAL CONTROL    (bit masks to elaborate)
  //
  void     setTCONMask(uint16_t mask);  //  only lower 9 bits used.
  uint16_t getTCONMask();

  //
  //  STATUS  read only (not implemented High Voltage commands).
  //
  //  BIT    Description
  //  --------------------------
  //   0     Write Protect
  //   1     Shut Down
  //   2     Wiper Lock 0
  //   3     Wiper Lock 1
  //   4     EEPROM Write Active
  uint16_t getStatusMask();

  //
  //  EEPROM
  //
  //  index = 0..9  value = 0..511
  bool     setEEPROM(uint8_t index, uint16_t value);
  uint16_t getEEPROM(uint8_t index);

  //
  //  POWER
  //
  void     powerOn();
  void     powerOff();
  bool     isPowerOn();

  //
  //  SPI
  //
  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();  //  debugging


protected:
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  uint8_t  _shutdown;
  bool     _hwSPI;
  uint32_t _SPIspeed;

  uint16_t _value[2] = { 0, 0 };
  uint8_t  _pmCount;
  uint16_t _maxValue;


  void     writeRegister1(uint8_t value1);
  void     writeRegister2(uint8_t value1, uint8_t value2);
  uint16_t readRegister(uint8_t reg);
  uint8_t  swSPI_write(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};



////////////////////////////////////////////////////
//
//  DERIVED CLASSES MCP41xx SERIES
//
class MCP4141 : public MCP4261
{
public:
  MCP4141(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP4141(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


class MCP4142 : public MCP4261
{
public:
  MCP4142(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP4142(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


class MCP4161 : public MCP4261
{
public:
  MCP4161(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP4161(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


class MCP4162 : public MCP4261
{
public:
  MCP4162(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP4162(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES MCP42xx SERIES
//
class MCP4241 : public MCP4261
{
public:
  MCP4241(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP4241(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


class MCP4242 : public MCP4261
{
public:
  MCP4242(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP4242(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


class MCP4262 : public MCP4261
{
public:
  MCP4262(uint8_t select, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP4262(uint8_t select, uint8_t shutdown, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};



//  -- END OF FILE --

