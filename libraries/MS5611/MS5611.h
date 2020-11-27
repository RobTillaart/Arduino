#pragma once
//
//    FILE: MS5611.h
//  AUTHOR: Rob Tillaart
//          Erni - testing/fixes
// VERSION: 0.2.1
// PURPOSE: Arduino library for MS5611 temperature and pressure sensor
//     URL: https://github.com/RobTillaart/MS5611
//
// HISTORY:
// see MS5611.cpp file
//

#include "Arduino.h"
#include "Wire.h"

#define MS5611_LIB_VERSION (F("0.2.1"))

#define MS5611_READ_OK  0

class MS5611
{
public:
  explicit  MS5611(uint8_t deviceAddress);

  void      begin();
  // init() will be obsolete in the future
  void      init()    { begin(); };

  // the actual reading of the sensor;
  // returns MS5611_READ_OK upon success
  int       read(uint8_t bits = 8);

  // temperature is in 1/100 of ²C
  int32_t   getTemperature() const { return _temperature; };

  // pressure is in 1/100 of a mBar
  int32_t   getPressure() const    { return _pressure; };

  // to check for failure
  int       getLastResult() const  { return _result; };

  // last time in millis() that the sensor has been read.
  uint32_t  lastRead()             { return _lastRead; };

private:
  void      convert(const uint8_t addr, uint8_t bits);
  uint32_t  readADC();
  uint16_t  readProm(uint8_t reg);
  void      command(const uint8_t command);

  uint8_t  _address;
  int32_t  _temperature;
  int32_t  _pressure;
  int      _result;
  float    C[7];
  uint32_t _lastRead;
};

// -- END OF FILE --
