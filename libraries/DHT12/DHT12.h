#ifndef DHT12_H
#define DHT12_H
//
//    FILE: DHT12.h
//  AUTHOR: Rob Tillaart
// PURPOSE: DHT_I2C library for Arduino .
// VERSION: 0.1.0
// HISTORY: See DHT12.cpp
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/
//
// Released to the public domain
//

#include "Wire.h"
#include "Arduino.h"

#define DHT12_VERSION "0.1.0"

#define DHT12_OK                0
#define DHT12_ERROR_CHECKSUM    -10
#define DHT12_ERROR_CONNECT     -11
#define DHT12_MISSING_BYTES     -12

#define DHT12_ADDRESS           0x5C

class DHT12
{
public:
  DHT12();

  int8_t read();

  float humidity;
  float temperature;

private:
  uint8_t _deviceAddress;
  uint8_t bits[5];
  int _readSensor();
};

#endif
// END OF FILE