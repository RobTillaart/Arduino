#pragma once
//
//    FILE: I2C_ABP2.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-05-27
// PURPOSE: Arduino library for the Honeywell I2C ABP2 pressure sensors.
//     URL: https://github.com/RobTillaart/I2C_ABP2
//          https://github.com/RobTillaart/pressure   (conversions)
//
//  https://forum.arduino.cc/t/honeywell-abp2-sensor-is-not-responding/1446097


#include "Arduino.h"
#include "Wire.h"


#define I2C_ABP2_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
constexpr int I2C_ABP2_OK            = 0;
constexpr int I2C_ABP2_NOT_READY     = -100;
constexpr int I2C_ABP2_REQUEST_ERROR = -101;

//  TODO state fields.


class I2C_ABP2
{
public:
  I2C_ABP2(uint8_t address, TwoWire *wire = &Wire);

  bool     begin(float minBar, float maxBar);
  bool     isConnected();
  uint8_t  getAddress();

  //  async interface
  int      request();
  int      read();
  //  timestamp of last good read
  uint32_t lastRead()    { return _lastRead; };

  //  access last good read values.
  uint8_t  getState()    { return _state; };
  float    getBar()      { return _Bar;   };
  float    getMilliBar() { return _Bar * 1e3;  };
  float    getCelsius()  { return _celsius; };

  //       DEBUG
  int      getLastError();


private:
  uint8_t  _address;
  TwoWire* _wire;

  uint32_t _lastRead;
  float    _minBar = 0;
  float    _maxBar = 1;
  float    _Bar;
  uint8_t  _state;
  float    _celsius;

  int      _error;
};


//  -- END OF FILE --





