//
//    FILE: MS5611.h
//  AUTHOR: Rob Tillaart
//          Erni - testing/fixes
// VERSION: 0.1.7
// PURPOSE: MS5611 Temperature & Pressure library for Arduino
//     URL:
//
// HISTORY:
// see MS5611.cpp file
//

#ifndef MS5611_h
#define MS5611_h

#if ARDUINO < 100
#error "VERSION NOT SUPPPORTED"
#else
#include <Arduino.h>
#endif

#define MS5611_LIB_VERSION (F("0.1.7"))

#define MS5611_READ_OK  0

class MS5611
{
public:
  explicit MS5611(uint8_t deviceAddress);

  void           init();
  int            read(uint8_t bits = 8);
  inline int32_t getTemperature() const { return _temperature; };
  inline int32_t getPressure() const { return _pressure; };
  inline int     getLastResult() const { return _result; };

private:
  void     reset();
  void     convert(const uint8_t addr, uint8_t bits);
  uint32_t readADC();
  uint16_t readProm(uint8_t reg);
  void     command(const uint8_t command);

  uint8_t  _address;
  int32_t  _temperature;
  int32_t  _pressure;
  int      _result;
  float    C[7];
};
#endif

// END OF FILE