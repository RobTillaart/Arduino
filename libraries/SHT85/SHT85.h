#pragma once
//
//    FILE: SHT85.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.3
//    DATE: 2021-02-10
// PURPOSE: Arduino library for the SHT85 temperature and humidity sensor
//          https://nl.rs-online.com/web/p/temperature-humidity-sensor-ics/1826530
//     URL: https://github.com/RobTillaart/SHT85
//
//  keep lib in sync with https://github.com/RobTillaart/SHT31
//
//    TOPVIEW      SHT85
//               +-------+
//    +-----\    | SDA 4 -----
//    | +-+  ----+ GND 3 -----
//    | +-+  ----+ +5V 2 -----
//    +-----/    | SCL 1 -----
//               +-------+


#include "Arduino.h"
#include "Wire.h"


#define SHT_LIB_VERSION                 (F("0.3.3"))
#define SHT85_LIB_VERSION               SHT_LIB_VERSION

#ifndef SHT_DEFAULT_ADDRESS   
#define SHT_DEFAULT_ADDRESS             0x44
#endif

//  fields readStatus
#define SHT_STATUS_ALERT_PENDING        (1 << 15)
#define SHT_STATUS_HEATER_ON            (1 << 13)
#define SHT_STATUS_HUM_TRACK_ALERT      (1 << 11)
#define SHT_STATUS_TEMP_TRACK_ALERT     (1 << 10)
#define SHT_STATUS_SYSTEM_RESET         (1 << 4)
#define SHT_STATUS_COMMAND_STATUS       (1 << 1)
#define SHT_STATUS_WRITE_CRC_STATUS     (1 << 0)

//  error codes
#define SHT_OK                          0x00
#define SHT_ERR_WRITECMD                0x81
#define SHT_ERR_READBYTES               0x82
#define SHT_ERR_HEATER_OFF              0x83
#define SHT_ERR_NOT_CONNECT             0x84
#define SHT_ERR_CRC_TEMP                0x85
#define SHT_ERR_CRC_HUM                 0x86
#define SHT_ERR_CRC_STATUS              0x87
#define SHT_ERR_HEATER_COOLDOWN         0x88
#define SHT_ERR_HEATER_ON               0x89


class SHT
{
public:
  SHT();

#if defined(ESP8266) || defined(ESP32)
  bool begin(const uint8_t address, uint8_t dataPin, uint8_t clockPin);
  //  use SHT_DEFAULT_ADDRESS
  bool begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  bool begin(const uint8_t address,  TwoWire *wire = &Wire);
  //  use SHT_DEFAULT_ADDRESS
  bool begin(TwoWire *wire = &Wire);

  uint8_t getType() { return _type; };

  // blocks 15 milliseconds + actual read + math
  bool read(bool fast = true);

  //  check sensor is reachable over I2C
  bool isConnected();

  //  details see datasheet; summary in SHT85.cpp file
  uint16_t readStatus();

  //  lastRead is in milliSeconds since start
  uint32_t lastRead() { return _lastRead; };

  bool reset(bool hard = false);


  //  do not use heater for long periods,
  //  use it for max 3 minutes to heat up
  //  and let it cool down at least 3 minutes.
  void    setHeatTimeout(uint8_t seconds);
  uint8_t getHeatTimeout() { return _heatTimeout; };
  bool    heatOn();
  bool    heatOff();
  bool    isHeaterOn();      //  is the sensor still heating up?


  float    getHumidity()       { return _rawHumidity    * (100.0 / 65535); };
  float    getTemperature()    { return _rawTemperature * (175.0 / 65535) - 45; };
  float    getFahrenheit()     { return _rawTemperature * (63.0 /13107.0) - 49; };
  uint16_t getRawHumidity()    { return _rawHumidity; };
  uint16_t getRawTemperature() { return _rawTemperature; };


  // ASYNC INTERFACE
  bool requestData();
  bool dataReady();
  bool readData(bool fast = true);

  int  getError(); // clears error flag


protected:
  uint8_t  crc8(const uint8_t *data, uint8_t len);
  bool     writeCmd(uint16_t cmd);
  bool     readBytes(uint8_t n, uint8_t *val);
  TwoWire* _wire;

  uint8_t  _address;
  uint8_t  _heatTimeout;   // seconds
  uint32_t _lastRead;
  uint32_t _lastRequest;   // for async interface
  uint32_t _heaterStart;
  uint32_t _heaterStop;
  bool     _heaterOn;
  uint8_t  _type;

  uint16_t _rawHumidity;
  uint16_t _rawTemperature;

  uint8_t _error;
};



////////////////////////////////////////////////////////
//
// DERIVED
//
class SHT30 : public SHT
{
public:
  SHT30();
};


class SHT31 : public SHT
{
public:
  SHT31();
};


class SHT35 : public SHT
{
public:
  SHT35();
};


class SHT85 : public SHT
{
public:
  SHT85();
};


// -- END OF FILE --

