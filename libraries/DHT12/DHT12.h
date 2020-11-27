#pragma once
//
//    FILE: DHT12.h
//  AUTHOR: Rob Tillaart
// PURPOSE: DHT_I2C library for Arduino .
// VERSION: 0.2.1
// HISTORY: See DHT12.cpp
//     URL: https://github.com/RobTillaart/DHT12
//

#include <Wire.h>

#define DHT12_LIB_VERSION "0.2.1"

#define DHT12_OK               0
#define DHT12_ERROR_CHECKSUM  -10
#define DHT12_ERROR_CONNECT   -11
#define DHT12_MISSING_BYTES   -12

class DHT12
{
public:
  explicit DHT12();
  explicit DHT12(TwoWire *wire);  		// to be tested explicitly

#if defined(ESP8266) || defined(ESP32)
  void begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  void begin();

  int8_t read();

  // preferred interface
  float getHumidity() { return humidity; };
  float getTemperature() { return temperature; };
  
  // members will become private in the future.
  float humidity;
  float temperature;

private:
  uint8_t bits[5];
  int _readSensor();
  TwoWire* _wire;
};

// -- END OF FILE --
