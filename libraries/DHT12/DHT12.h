#ifndef DHT12_H
#define DHT12_H
//
//    FILE: DHT12.h
//  AUTHOR: Rob Tillaart
// PURPOSE: DHT_I2C library for Arduino .
// VERSION: 0.1.1
// HISTORY: See DHT12.cpp
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/
//
// Released to the public domain
//

#include "Wire.h"
#include "Arduino.h"

#define DHT12_VERSION "0.1.1"

#define DHT12_OK               0
#define DHT12_ERROR_CHECKSUM  -10
#define DHT12_ERROR_CONNECT   -11
#define DHT12_MISSING_BYTES   -12

class DHT12
{
public:

  #ifdef ESP8266
  void begin(uint8_t sda, uint8_t scl);
  #endif
  void begin();

  int8_t read();

  float humidity;
  float temperature;

private:
  uint8_t bits[5];
  int _readSensor();
};

#endif
// END OF FILE