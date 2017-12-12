//
//    FILE: DHT12.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: I2C library for DHT12 for Arduino.
//
// HISTORY:
// 0.1.0 - 2017-12-11 initial version
//
// Released to the public domain
//

#include <DHT12.h>

////////////////////////////////////////////////////////////////////
//
// PUBLIC
//
DHT12::DHT12()
{
  _deviceAddress = DHT12_ADDRESS;
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
  Wire.beginTransmission(_deviceAddress);
  Wire.write(0);
  int rv = Wire.endTransmission();
  if (rv < 0) return rv;

  // GET DATA
  const uint8_t length = 5;
  int bytes = Wire.requestFrom(_deviceAddress, length);
  if (bytes == 0) return DHT12_ERROR_CONNECT;
  if (bytes < length) return DHT12_MISSING_BYTES;

  for (int i = 0; i < bytes; i++)
  {
    bits[i] = Wire.read();
  }

  return bytes;
}
// END OF FILE