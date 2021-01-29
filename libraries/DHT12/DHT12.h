#pragma once
//
//    FILE: DHT12.h
//  AUTHOR: Rob Tillaart
// PURPOSE: DHT_I2C library for Arduino .
// VERSION: 0.3.0
// HISTORY: See DHT12.cpp
//     URL: https://github.com/RobTillaart/DHT12
//

#include "Arduino.h"
#include "Wire.h"

#define DHT12_LIB_VERSION      "0.3.0"

#define DHT12_OK               0
#define DHT12_ERROR_CHECKSUM  -10
#define DHT12_ERROR_CONNECT   -11
#define DHT12_MISSING_BYTES   -12

class DHT12
{
public:
  DHT12(TwoWire *wire);        // to be tested explicitly

#if defined(ESP8266) || defined(ESP32)
  void     begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  void     begin();

  int8_t   read();
  float    getHumidity()    { return _humidity    + _humOffset; };
  float    getTemperature() { return _temperature + _tempOffset; };

  // allows 1st order calibration
  void     setHumOffset(float offset)  { _humOffset  = offset; };
  void     setTempOffset(float offset) { _tempOffset = offset; };
  float    getHumOffset()              { return _humOffset; };
  float    getTempOffset()             { return _tempOffset; };

private:
  float    _humidity;
  float    _temperature;
  float    _humOffset;
  float    _tempOffset;
  uint8_t  _bits[5];
  
  int      _readSensor();
  TwoWire* _wire;
};

// -- END OF FILE --
