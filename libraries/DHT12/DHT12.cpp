//
//    FILE: DHT12.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: I2C library for DHT12 for Arduino.
//
// HISTORY:
//   0.1.0: 2017-12-11 initial version
//   0.1.1: 2017-12-19 added ESP8266 - issue #86
//                     Verified by Viktor Balint
//   0.1.2: 2018-09-02 fix negative temperature DHT12 - issue #111
//   0.2.0  2020-04-11 explicit constructors, select other Wire interface, #pragma once
//   0.2.1  2020-06-07 fix library.json
//

#include <DHT12.h>

#define DHT12_ADDRESS  ((uint8_t)0x5C)


DHT12::DHT12()
{
  DHT12(Wire);
}


DHT12::DHT12(TwoWire *wire)
{
  _wire = wire;
}


void DHT12::begin()
{
  _wire->begin();
}


#if defined(ESP8266) || defined(ESP32)
void DHT12::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
}
#endif


int8_t DHT12::read()
{
  // READ SENSOR
  int status = _readSensor();
  if (status < 0) return status;

  // CONVERT AND STORE
  humidity = bits[0] + bits[1] * 0.1;
  temperature = bits[2] + (bits[3] & 0x7F) * 0.1;
  if (bits[3] & 0x80)
  {
    temperature = -temperature;
  }

  // TEST CHECKSUM
  uint8_t checksum = bits[0] + bits[1] + bits[2] + bits[3];
  if (bits[4] != checksum)
  {
    return DHT12_ERROR_CHECKSUM;
  }

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
  if (bytes == 0) return DHT12_ERROR_CONNECT;
  if (bytes < length) return DHT12_MISSING_BYTES;

  for (int i = 0; i < bytes; i++)
  {
    bits[i] = _wire->read();
  }

  return bytes;
}

// -- END OF FILE --
