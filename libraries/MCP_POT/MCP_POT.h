#pragma once
//
//    FILE: MCP_POT.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2023-12-21
// PURPOSE: Arduino library for MCP41xxx and MCP42xxx SPI based digital potentiometers.
//     URL: https://github.com/RobTillaart/MCP_POT


#include "Arduino.h"
#include "SPI.h"


#define MCP_POT_LIB_VERSION           (F("0.2.2"))

#ifndef MCP_POT_MIDDLE_VALUE
#define MCP_POT_MIDDLE_VALUE          128
#endif

#ifndef MCP_POT_MAX_VALUE
#define MCP_POT_MAX_VALUE             255
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


class MCP_POT
{
public:
  //       HARDWARE SPI
  MCP_POT(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  //       SOFTWARE SPI
  MCP_POT(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);

  void     begin(uint8_t value = MCP_POT_MIDDLE_VALUE);
  void     reset(uint8_t value = MCP_POT_MIDDLE_VALUE);

  //       set both potmeters to the same value
  bool     setValue(uint8_t value);
  //       set single potmeter, pm = 0 or 1
  bool     setValue(uint8_t pm, uint8_t value);
  uint8_t  getValue(uint8_t pm = 0);

  //  EXPERIMENTAL
  //  Ohm wrappers
  void     setMaxOhm(uint32_t maxOhm);
  uint32_t getMaxOhm();
  void     setOhm(uint8_t pm, uint32_t ohm);
  uint32_t getOhm(uint8_t pm);


  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  void     setSWSPIdelay(uint16_t del = 0);
  uint16_t getSWSPIdelay();

  //       MISC
  uint8_t  pmCount();
  void     powerOn();
  void     powerOff();
  bool     isPowerOn();

  //       debugging
  bool     usesHWSPI();


protected:
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  uint8_t  _reset;
  uint8_t  _shutdown;

  uint8_t  _value[2];
  uint8_t  _pmCount;
  uint32_t _maxOhm;

  void     updateDevice(uint8_t pm, uint8_t value, uint8_t cmd);
  void     swSPI_transfer(uint8_t value);

  bool     _hwSPI;
  uint16_t _swSPIdelay = 0;
  uint32_t _SPIspeed;
  __SPI_CLASS__ * _mySPI;
  SPISettings     _spi_settings;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES MCP41000 SERIES
//
class MCP41010 : public MCP_POT
{
public:
  MCP41010(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP41010(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};

class MCP41050 : public MCP_POT
{
public:
  MCP41050(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP41050(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};

class MCP41100 : public MCP_POT
{
public:
  MCP41100(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP41100(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES MCP42000 SERIES
//
class MCP42010 : public MCP_POT
{
public:
  MCP42010(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP42010(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};

class MCP42050 : public MCP_POT
{
public:
  MCP42050(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP42050(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};

class MCP42100 : public MCP_POT
{
public:
  MCP42100(uint8_t select, uint8_t reset, uint8_t shutdown, __SPI_CLASS__ * mySPI = &SPI);
  MCP42100(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock);
};


//  -- END OF FILE --

