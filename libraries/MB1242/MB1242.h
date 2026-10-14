#pragma once
//
//    FILE: MB1242.h
//  AUTHOR: Rob Tillaart
//    DATE: 2026-10-13
// VERSION: 0.1.0
// PURPOSE: Arduino library for the MaxBotic I2C MB1242 distance sensor.
//     URL: https://github.com/RobTillaart/MB1242
//


#include "Arduino.h"
#include "Wire.h"


#define MB1242_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
const int MB1242_OK                 = 0x00;
const int MB1242_NOT_READY          = 0x10;  //  TODO
const int MB1242_REQUEST_ERROR      = 0x11;
const int MB1242_NO_REQUEST_PENDING = 0x12;  //  TODO


class MB1242
{
public:
  MB1242(uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //       ASYNC REQUEST
  bool     requestDistance();
  void     setStatusPin(uint8_t statusPin);
  bool     ready();

  //       ASYNC READ
  uint16_t readCM();
  float    readMeter();
  float    readInch();
  float    readFeet();
  uint32_t lastRead();

  //       ADDRESS
  bool     changeAddress(uint8_t address);

  //       DEBUG
  int      getLastError();


protected:
  uint8_t  _address = 0x2A;
  TwoWire* _wire;

  int      _write(uint8_t * arr, uint8_t size);
  int      _read(uint16_t &raw);

  uint32_t _lastRead;
  uint32_t _lastRequest;
  uint8_t  _statusPin = 255;
  bool     _requestInProgress;
  int      _error;
};


//////////////////////////////////////
//
//  DERIVED (wrappers for now)
//
class MB1202 : public MB1242
{
public:
  MB1202(uint8_t address, TwoWire *wire = &Wire)
    : MB1242(address, wire)
  {
  }
};

class MB1212 : public MB1242
{
public:
  MB1212(uint8_t address, TwoWire *wire = &Wire)
    : MB1242(address, wire)
  {
  }
};

class MB1222 : public MB1242
{
public:
  MB1222(uint8_t address, TwoWire *wire = &Wire)
    : MB1242(address, wire)
  {
  }
};

class MB1232 : public MB1242
{
public:
  MB1232(uint8_t address, TwoWire *wire = &Wire)
    : MB1242(address, wire)
  {
  }
};


//  -- END OF FILE --





