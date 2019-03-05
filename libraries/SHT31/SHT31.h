//
//    FILE: SHT31.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2019-02-08
// PURPOSE: Class for SHT31 I2C temperature humidity sensor
//          https://www.adafruit.com/product/2857
//     URL: https://github.com/RobTillaart/Arduino.git
//
// Released to the public domain
//

#ifndef SHT31_h
#define SHT31_h

#include "Arduino.h"
#include "Wire.h"

#define SHT31_LIB_VERSION "0.1.2"

class SHT31
{
public:
  SHT31();

  bool begin(const uint8_t address);
  bool read(bool fast = true);

  // details see datasheet
  uint16_t readStatus();

  // lastRead is in MilliSeconds since start sketch
  uint32_t lastRead() { return _lastRead; };

  void reset();

  // do not use heater for long periods,
  // use it for max 3 minutes to heat up
  // and let it cool down an equal period.
  void heatOn();
  void heatOff();

  float humidity;
  float temperature;

  // ASYNC INTERFACE
  void requestData();
  bool dataReady();
  void readData();

private:
  void writeCmd(uint16_t cmd);
  void readBytes(uint8_t n, uint8_t *val);

  uint8_t   _addr;
  uint32_t  _lastRead;
  uint32_t  _lastRequest;   // for async interface
};

#endif
// -- END OF FILE --