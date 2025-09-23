#pragma once
//
//    FILE: DCT532.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-06-03
// VERSION: 0.1.0
// PURPOSE: Arduino library for
//     URL: https://github.com/RobTillaart/DCT532
//          https://forum.arduino.cc/t/i2c-industrial-pressure-sensor-dct-532-with-arduino-uno-advice-required/1385075/11
//
//  TODO: need HW to develop /test


#include "Arduino.h"
#include "Wire.h"


#define DCT532_LIB_VERSION         (F("0.1.0"))


//  ERROR CODES
//  values <> 0 are errors.
#define DCT532_OK                   0
#define DCT532_REQUEST_ERROR       -1



class DCT532
{
public:
  DCT532(uint8_t address, TwoWire *wire = &Wire);

  bool     begin(float maxPressure, float minPressure = 0);
  bool     isConnected();
  uint8_t  getAddress();

  //       READ
  int      readSensor();      //  returns status
  float    getPressure();     //  Bar
  float    getTemperature();  //  Celsius
  uint32_t lastRead();

  //  DEBUG
  int      getLastError();

private:
  uint8_t  _address = 0x2A;
  TwoWire* _wire;

  uint32_t _lastRead;
  float    _pressure;
  float    _temperature;
  //  RAW data for develop,
  //  TODO remove after confirmed working/
  uint16_t P;
  uint16_t T;

  //  calibrate sensor type.
  float    _minPressure;
  float    _maxPressure;

  uint8_t  _error;
};


//  -- END OF FILE --





