#pragma once
//
//    FILE: SHT31.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
//    DATE: 2019-02-08
// PURPOSE: Arduino library for the SHT31 temperature and humidity sensor
//          https://www.adafruit.com/product/2857
//     URL: https://github.com/RobTillaart/SHT31
//

#include "Arduino.h"
#include "Wire.h"

#define SHT31_LIB_VERSION "0.2.2"

// fields readStatus
#define SHT31_STATUS_ALERT_PENDING    (1 << 15)
#define SHT31_STATUS_HEATER_ON        (1 << 13)
#define SHT31_STATUS_HUM_TRACK_ALERT  (1 << 11)
#define SHT31_STATUS_TEMP_TRACK_ALERT (1 << 10)
#define SHT31_STATUS_SYSTEM_RESET     (1 << 4)
#define SHT31_STATUS_COMMAND_STATUS   (1 << 1)
#define SHT31_STATUS_WRITE_CRC_STATUS (1 << 0)

class SHT31
{
public:
  SHT31();

#if defined(ESP8266) || defined(ESP32)
  bool begin(const uint8_t address, uint8_t dataPin, uint8_t clockPin);
#endif
  bool begin(const uint8_t address);
  bool begin(const uint8_t address,  TwoWire *wire);

  // blocks 15 milliseconds + actual read + math
  bool read(bool fast = true);

  // details see datasheet; summary in SHT31.cpp file
  uint16_t readStatus();

  // lastRead is in milliSeconds since start
  uint32_t lastRead() { return _lastRead; };

  void reset(bool hard = false);

  // do not use heater for long periods,
  // use it for max 3 minutes to heat up
  // and let it cool down an equal period.
  void setHeatTimeout(uint8_t seconds);
  void heatOn();
  void heatOff();
  bool heatUp();  // is the sensor still heating up?

  float getHumidity() { return humidity; };
  float getTemperature() { return temperature; };

  // ASYNC INTERFACE
  void requestData();
  bool dataReady();
  bool readData(bool fast = true);

private:
  uint8_t crc8(const uint8_t *data, int len);
  void writeCmd(uint16_t cmd);
  void readBytes(uint8_t n, uint8_t *val);
  TwoWire* _wire;

  uint8_t   _addr;
  uint8_t   _heatTimeOut;   // seconds
  uint32_t  _lastRead;
  uint32_t  _lastRequest;   // for async interface
  uint32_t  _heaterStart;

  float humidity;
  float temperature;
};

// -- END OF FILE --
