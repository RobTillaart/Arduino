//
//    FILE: DHT12.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: I2C library for DHT12 for Arduino.
//
// HISTORY:
//   0.1.0: 2017-12-11 initial version
//   0.1.1: 2017-12-19 added ESP8266 - issue #86
//                     Verified by Viktor Balint
//
// Released to the public domain
//

#include <Wire.h>
#include <DHT12.h>

#define DHT12_ADDRESS  ((uint8_t)0x5C)

////////////////////////////////////////////////////////////////////
//
// PUBLIC
//

#ifdef ESP8266
void DHT12::begin(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);
}
#endif

void DHT12::begin()
{
  Wire.begin();
}

int8_t DHT12::read()
{
  // READ SENSOR
  int status = _readSensor();
  if (status < 0) return status;

  // CONVERT AND STORE
  humidity = bits[0] + bits[1] * 0.1;
  temperature = (bits[2] & 0x7F) + bits[3] * 0.1;
  if (bits[2] & 0x80)
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

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// negative is error in communication
// 5 is OK
// 0..4 is too few bytes.
int DHT12::_readSensor()
{
  // GET CONNECTION
  Wire.beginTransmission(DHT12_ADDRESS);
  Wire.write(0);
  int rv = Wire.endTransmission();
  if (rv < 0) return rv;

  // GET DATA
  const uint8_t length = 5;
  int bytes = Wire.requestFrom(DHT12_ADDRESS, length);
  if (bytes == 0) return DHT12_ERROR_CONNECT;
  if (bytes < length) return DHT12_MISSING_BYTES;

  for (int i = 0; i < bytes; i++)
  {
    bits[i] = Wire.read();
  }

  return bytes;
}
// END OF FILE