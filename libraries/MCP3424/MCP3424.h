#pragma once
//
//    FILE: MCP3424.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: Arduino library for 18 bit ADC I2C MCP3424 and compatibles.
//     URL: https://github.com/RobTillaart/MCP3424


#include "Arduino.h"
#include "Wire.h"

#define MCP3424_LIB_VERSION               (F("0.1.4"))


class MCP3424
{
public:
  //  CONSTRUCTOR
  MCP3424(uint8_t address = 0x68, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();
  uint8_t  getMaxChannels();

  //  GET DATA
  int32_t  read();
  //  wrappers
  float    readVolts();
  float    readMilliVolts();
  float    readMicroVolts();

  //  CONFIG
  //  note that after changing a channel one has to wait before
  //       a valid measurement is available, see readme.md.
  bool     setChannel(uint8_t channel = 0);
  uint8_t  getChannel();

  bool     setGain(uint8_t gain = 1);
  uint8_t  getGain();

  bool     setResolution(uint8_t bits = 12);
  uint8_t  getResolution();
  uint16_t getConversionDelay();

  //  MODE
  void     setContinuousMode();  //  default
  void     setSingleShotMode();
  uint8_t  getMode();


protected:
  uint8_t   _maxChannels;
  uint8_t   _channel;
  uint8_t   _gain;
  uint8_t   _bits;
  uint8_t   _config;

  uint8_t   _address;
  TwoWire * _wire;

  int       writeConfig();
  int32_t   readRaw();
};


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class MCP3421 : public MCP3424
{
public:
  MCP3421(uint8_t address = 0x68, TwoWire *wire = &Wire);
};

class MCP3422 : public MCP3424
{
public:
  MCP3422(uint8_t address = 0x68, TwoWire *wire = &Wire);
};

class MCP3423 : public MCP3424
{
public:
  MCP3423(uint8_t address = 0x68, TwoWire *wire = &Wire);
};

//
//  max 16 bit
//
class MCP3426 : public MCP3424
{
public:
  MCP3426(uint8_t address = 0x68, TwoWire *wire = &Wire);
};

class MCP3427 : public MCP3424
{
public:
  MCP3427(uint8_t address = 0x68, TwoWire *wire = &Wire);
};

class MCP3428 : public MCP3424
{
public:
  MCP3428(uint8_t address = 0x68, TwoWire *wire = &Wire);
};


//  -- END OF FILE --

