//
//    FILE: DHT12.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: I2C library for DHT12 for Arduino.
//
// HISTORY:
//  0.1.0   2017-12-11  initial version
//  0.1.1   2017-12-19  added ESP8266 - issue #86
//                      Verified by Viktor Balint
//  0.1.2   2018-09-02  fix negative temperature DHT12 - issue #111
//  0.2.0   2020-04-11  explicit constructors, select other Wire interface, 
//                      #pragma once
//  0.2.1   2020-06-07  fix library.json
//  0.3.0   2020-12-19  add Arduino-CI + unit test
//                      temperature and humidity made private
//  0.3.1   2021-10-25  add lastRead, update Arduino-CI, badges
//  0.3.2   2021-12-16  update library.json, license
//                      add isConnected()


#include "DHT12.h"

#define DHT12_ADDRESS           ((uint8_t)0x5C)


DHT12::DHT12(TwoWire *wire)
{
  _wire        = wire;
  _temperature = 0;
  _humidity    = 0;
  _humOffset   = 0;
  _tempOffset  = 0;
}


bool DHT12::begin()
{
  _wire->begin();
  return isConnected();
}


#if defined(ESP8266) || defined(ESP32)
bool DHT12::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  return isConnected();
}
#endif


bool DHT12::isConnected()
{
  _wire->beginTransmission(DHT12_ADDRESS);
  int rv = _wire->endTransmission();
  return rv == 0;
}


int8_t DHT12::read()
{
  // READ SENSOR
  int status = _readSensor();
  if (status < 0) return status;

  // CONVERT AND STORE
  _humidity    = _bits[0] + _bits[1] * 0.1;
  _temperature = _bits[2] + (_bits[3] & 0x7F) * 0.1;
  if (_bits[3] & 0x80)
  {
    _temperature = -_temperature;
  }

  // TEST CHECKSUM
  uint8_t checksum = _bits[0] + _bits[1] + _bits[2] + _bits[3];
  if (_bits[4] != checksum) return DHT12_ERROR_CHECKSUM;

  _lastRead = millis();

  return DHT12_OK;
}


int DHT12::_readSensor()
{
  // GET CONNECTION
  _wire->beginTransmission(DHT12_ADDRESS);
  _wire->write(0);
  int rv = _wire->endTransmission();
  if (rv < 0) return rv;

  // GET DATA
  const uint8_t length = 5;
  int bytes = _wire->requestFrom(DHT12_ADDRESS, length);

  if (bytes == 0)     return DHT12_ERROR_CONNECT;
  if (bytes < length) return DHT12_MISSING_BYTES;

  for (int i = 0; i < bytes; i++)
  {
    _bits[i] = _wire->read();
  }

  return bytes;
}


// -- END OF FILE --
