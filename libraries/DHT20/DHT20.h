#pragma once
//
//    FILE: DHT20.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino library for DHT20 I2C temperature and humidity sensor.
// VERSION: 0.1.2
// HISTORY: See DHT20.cpp
//     URL: https://github.com/RobTillaart/DHT20
//

//  Always check datasheet - front view
//
//          +--------------+
//  VDD ----| 1            |
//  SDA ----| 2    DHT20   |
//  GND ----| 3            |
//  SCL ----| 4            |
//          +--------------+


#include "Arduino.h"
#include "Wire.h"

#define DHT20_LIB_VERSION                    (F("0.1.2"))

#define DHT20_OK                             0
#define DHT20_ERROR_CHECKSUM                -10
#define DHT20_ERROR_CONNECT                 -11
#define DHT20_MISSING_BYTES                 -12
#define DHT20_ERROR_BYTES_ALL_ZERO          -13


#define DHT20_ACQUISITION_TIME               85


class DHT20
{
public:
  DHT20(TwoWire *wire = &Wire);        // to be tested explicitly

#if defined(ESP8266) || defined(ESP32)
  bool     begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  bool     begin();
  bool     isConnected();

  //  ASYNCHRONUOUS CALL
  int      requestData() { return _requestData(); };
  int      readData()    { return _readData(); };
  int      convert();

  //  SYNCHRONUOUS CALL
  int      read();
  float    getHumidity()    { return _humidity    + _humOffset; };
  float    getTemperature() { return _temperature + _tempOffset; };

  //  allows 1st order calibration
  void     setHumOffset(float offset)  { _humOffset  = offset; };
  void     setTempOffset(float offset) { _tempOffset = offset; };
  float    getHumOffset()              { return _humOffset; };
  float    getTempOffset()             { return _tempOffset; };

  //  OTHER
  uint32_t lastRead()       { return _lastRead; };
  uint32_t lastRequest()    { return _lastRequest; };
  int      internalStatus() { return _status; };
  //  forced read status
  uint8_t  readStatus()     { return _readStatus(); };

private:
  float    _humidity;
  float    _temperature;
  float    _humOffset;
  float    _tempOffset;
  uint8_t  _status;
  uint32_t _lastRequest;
  uint32_t _lastRead;

  int      _requestData();
  int      _readData();
  uint8_t  _readStatus();
  uint8_t  _bits[7];

  uint8_t  _crc8(uint8_t *ptr, uint8_t len);

  TwoWire* _wire;
};


// -- END OF FILE --

