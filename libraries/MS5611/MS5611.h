#pragma once
//
//    FILE: MS5611.h
//  AUTHOR: Rob Tillaart
//          Erni - testing/fixes
// VERSION: 0.3.1
// PURPOSE: Arduino library for MS5611 temperature and pressure sensor
//     URL: https://github.com/RobTillaart/MS5611


#include "Arduino.h"
#include "Wire.h"


#define MS5611_LIB_VERSION                    (F("0.3.1"))


#define MS5611_READ_OK                        0
#define MS5611_ERROR_2                        2         // low level I2C error
#define MS5611_NOT_READ                       -999


class MS5611
{
public:
  explicit MS5611(uint8_t deviceAddress);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(uint8_t sda, uint8_t scl, TwoWire *wire = &Wire);
#endif
  bool     begin(TwoWire *wire = &Wire);
  bool     isConnected();

  // reset command + get constants
  void     reset();

  // the actual reading of the sensor;
  // returns MS5611_READ_OK upon success
  int      read(uint8_t bits = 8);

  // temperature is in ²C
  float    getTemperature() const { return _temperature * 0.01; };

  // pressure is in mBar
  float    getPressure() const    { return _pressure * 0.01; };

  // to check for failure
  int      getLastResult() const  { return _result; };

  // last time in millis() that the sensor has been read.
  uint32_t lastRead()             { return _lastRead; };


private:
  void     convert(const uint8_t addr, uint8_t bits);
  uint32_t readADC();
  uint16_t readProm(uint8_t reg);
  int      command(const uint8_t command);

  uint8_t  _address;
  int32_t  _temperature;
  int32_t  _pressure;
  int      _result;
  float    C[7];
  uint32_t _lastRead;

  TwoWire * _wire;
};


// -- END OF FILE --

