#pragma once
//
//    FILE: MCP_ADC.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2019-10-24
// PURPOSE: Arduino library for MCP_ADC
//     URL: https://github.com/RobTillaart/MCP_ADC
//


#include "Arduino.h"
#include "SPI.h"


#define MCP_ADC_LIB_VERSION       (F("0.2.0"))


class MCP_ADC
{
public:
  MCP_ADC(uint8_t dataIn = 255, uint8_t dataOut = 255, uint8_t clock = 255);
  void     begin(uint8_t select);

  uint8_t  channels() { return _channels; };
  int16_t  maxValue() { return _maxValue; };

  int16_t  analogRead(uint8_t channel);
  void     analogReadMultiple(uint8_t channels[], uint8_t numChannels, int16_t readings[]);
  int16_t  differentialRead(uint8_t channel);
  int16_t  deltaRead(uint8_t channel);

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed()               { return _SPIspeed; };

  //       debugging
  bool     usesHWSPI() { return _hwSPI; };
  uint32_t count();  //  number of channels read.

  //  ESP32 specific
  #if defined(ESP32)
  void     selectHSPI() { _useHSPI = true;  };
  void     selectVSPI() { _useHSPI = false; };
  bool     usesHSPI()   { return _useHSPI;  };
  bool     usesVSPI()   { return !_useHSPI; };

  //  to overrule ESP32 default hardware pins
  void     setGPIOpins(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t select);
  #endif


protected:
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  bool     _hwSPI;
  uint8_t  _channels;
  int16_t  _maxValue;
  //  1 MHz is a safe value (datasheet); in a test 4 MHz worked.
  uint32_t _SPIspeed = 1000000;

  //  derived classes must implement buildRequest() function.
  virtual uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data) = 0;

  int16_t  readADC(uint8_t channel, bool single);
  void     readADCMultiple(uint8_t channels[], uint8_t numChannels, int16_t readings[]);

  uint8_t  swSPI_transfer(uint8_t d);

  SPIClass    * mySPI;
  SPISettings _spi_settings;

  #if defined(ESP32)
  bool        _useHSPI = true;
  #endif

  uint32_t _count;
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class MCP3002 : public MCP_ADC
{
public:
  MCP3002(uint8_t dataIn = 255, uint8_t dataOut = 255, uint8_t clock = 255);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3004 : public MCP_ADC
{
public:
  MCP3004(uint8_t dataIn = 255, uint8_t dataOut = 255, uint8_t clock = 255);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3008 : public MCP_ADC
{
public:
  MCP3008(uint8_t dataIn = 255, uint8_t dataOut = 255, uint8_t clock = 255);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3201 : public MCP_ADC
{
public:
  MCP3201(uint8_t dataIn = 255, uint8_t dataOut = 255, uint8_t clock = 255);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3202 : public MCP_ADC
{
public:
  MCP3202(uint8_t dataIn = 255, uint8_t dataOut = 255, uint8_t clock = 255);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3204 : public MCP_ADC
{
public:
  MCP3204(uint8_t dataIn = 255, uint8_t dataOut = 255, uint8_t clock = 255);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


class MCP3208 : public MCP_ADC
{
public:
  MCP3208(uint8_t dataIn = 255, uint8_t dataOut = 255, uint8_t clock = 255);
  uint8_t  buildRequest(uint8_t channel, bool single, uint8_t * data);
};


// -- END OF FILE --

