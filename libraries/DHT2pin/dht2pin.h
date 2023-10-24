#pragma once
//
//    FILE: dht2pin.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: https://github.com/RobTillaart/DHT2pin
//          http://arduino.cc/playground/Main/DHTLib


#include <Arduino.h>


#define DHT2PIN_LIB_VERSION               (F("0.2.1"))


#define DHTLIB_OK                         0
#define DHTLIB_ERROR_CHECKSUM             -1
#define DHTLIB_ERROR_TIMEOUT              -2
#define DHTLIB_ERROR_CONNECT              -3
#define DHTLIB_ERROR_ACK_L                -4
#define DHTLIB_ERROR_ACK_H                -5
#define DHTLIB_INVALID_VALUE              -999

#define DHTLIB_DHT11_WAKEUP     18
#define DHTLIB_DHT_WAKEUP       1

//  max timeout is 100usec.
//  For a 16Mhz processor that is max 1600 clock cycles
//  loops using TIMEOUT use at least 4 clock cycles
//  so 100 us takes max 400 loops
//  so by dividing F_CPU by 40000 we "fail" as fast as possible
#ifdef F_CPU
#define DHTLIB_TIMEOUT (F_CPU/40000)
#else
#define DHTLIB_TIMEOUT (75000000/40000)
#endif


class DHT2pin
{
public:
  DHT2pin(uint8_t rpin, uint8_t wpin);

  void begin();

  //  return values:
  //  DHTLIB_OK
  //  DHTLIB_ERROR_CHECKSUM
  //  DHTLIB_ERROR_TIMEOUT
  int read11();
  int read();

  float humidity();
  float temperature();

private:
  uint8_t _rpin;
  uint8_t _wpin;
  uint8_t _bits[5];  //  buffer to receive data
  float   _humidity;
  float   _temperature;
  int     _readSensor(uint8_t wakeupDelay);
};


//  -- END OF FILE --

