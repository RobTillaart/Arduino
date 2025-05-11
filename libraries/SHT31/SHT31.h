#pragma once
//
//    FILE: SHT31.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.2
//    DATE: 2019-02-08
// PURPOSE: Arduino library for the SHT31 temperature and humidity sensor
//          https://www.adafruit.com/product/2857
//     URL: https://github.com/RobTillaart/SHT31


#include "Arduino.h"
#include "Wire.h"


#define SHT31_LIB_VERSION             (F("0.5.2"))

#ifndef SHT_DEFAULT_ADDRESS
#define SHT_DEFAULT_ADDRESS           0x44
#endif

//  fields readStatus
#define SHT31_STATUS_ALERT_PENDING    (1 << 15)
#define SHT31_STATUS_HEATER_ON        (1 << 13)
#define SHT31_STATUS_HUM_TRACK_ALERT  (1 << 11)
#define SHT31_STATUS_TEMP_TRACK_ALERT (1 << 10)
#define SHT31_STATUS_SYSTEM_RESET     (1 << 4)
#define SHT31_STATUS_COMMAND_STATUS   (1 << 1)
#define SHT31_STATUS_WRITE_CRC_STATUS (1 << 0)

//  error codes
#define SHT31_OK                      0x00
#define SHT31_ERR_WRITECMD            0x81
#define SHT31_ERR_READBYTES           0x82
#define SHT31_ERR_HEATER_OFF          0x83
#define SHT31_ERR_NOT_CONNECT         0x84
#define SHT31_ERR_CRC_TEMP            0x85
#define SHT31_ERR_CRC_HUM             0x86
#define SHT31_ERR_CRC_STATUS          0x87
#define SHT31_ERR_HEATER_COOLDOWN     0x88
#define SHT31_ERR_HEATER_ON           0x89
#define SHT31_ERR_SERIAL_NUMBER_CRC   0x8A


class SHT31
{
public:
  SHT31(uint8_t address = SHT_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

  bool    begin();
  uint8_t getAddress();

  //  check sensor is reachable over I2C
  virtual bool isConnected();

  //  blocks 15 milliseconds + actual read + math
  bool read(bool fast = true);

  //  details see datasheet; summary in SHT31.cpp file
  uint16_t readStatus();
  bool clearStatus();

  //  lastRead is in milliSeconds since start
  uint32_t lastRead() { return _lastRead; };

  bool reset(bool hard = false);

  //  do not use heater for long periods,
  //  use it for max 3 minutes to heat up
  //  and let it cool down at least 3 minutes.
  void setHeatTimeout(uint8_t seconds);
  uint8_t getHeatTimeout() { return _heatTimeout; };
  bool heatOn();
  bool heatOff();
  bool isHeaterOn();  // is the sensor still heating up?
  //  [[deprecated("Use isHeaterOn() instead")]]
  bool heatUp() { return isHeaterOn(); };   // will be obsolete

  //  0..100%
  float    getHumidity()       { return _rawHumidity    * (100.0 / 65535); };
  //  getTemperature returns Celsius
  float    getTemperature()    { return _rawTemperature * (175.0 / 65535) - 45; };
  float    getFahrenheit()     { return _rawTemperature * (63.0 /13107.0) - 49; };
  //  raw data e.g. debugging or efficient logging / transmit.
  uint16_t getRawHumidity()    { return _rawHumidity; };
  uint16_t getRawTemperature() { return _rawTemperature; };


  //  ASYNC INTERFACE
  bool requestData();
  bool dataReady();
  bool readData(bool fast = true);

  //  MISC
  int getError();  //  clears error flag
  //  fast == true, => skips CRC check
  bool getSerialNumber(uint32_t &serial, bool fast = true);


protected:
  uint8_t  _address;
  uint8_t  _heatTimeout;   //  seconds
  uint32_t _lastRead;
  uint32_t _lastRequest;   //  for async interface
  uint32_t _heaterStart;
  uint32_t _heaterStop;
  bool     _heaterOn;
  uint16_t _rawHumidity;
  uint16_t _rawTemperature;
  uint8_t  _error;

private:
  uint8_t crc8(const uint8_t *data, uint8_t len);
  virtual bool writeCmd(uint16_t cmd);
  virtual bool readBytes(uint8_t n, uint8_t *val);
  TwoWire* _wire;
};


//  -- END OF FILE --


