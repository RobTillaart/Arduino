#pragma once
//
//    FILE: SHT85.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.6.0
//    DATE: 2021-02-10
// PURPOSE: Arduino library for the SHT85 temperature and humidity sensor
//          https://nl.rs-online.com/web/p/temperature-humidity-sensor-ics/1826530
//     URL: https://github.com/RobTillaart/SHT85
//
//  keep lib in sync with https://github.com/RobTillaart/SHT31
//
//  ALWAYS check datasheet for connections.
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


#define SHT_LIB_VERSION                 (F("0.6.0"))
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
#define SHT_ERR_SERIAL                  0x8A


class SHT
{
public:
  SHT(uint8_t address, TwoWire *wire = &Wire);

  bool     begin();
  uint8_t  getAddress();
  uint8_t  getType();


  //  SYNCHRONOUS INTERFACE
  //  read blocks 4 or 15 milliseconds + actual read + math
  bool     read(bool fast = true);


  //  ASYNCHRONOUS INTERFACE
  bool     requestData(bool fast = true);
  bool     dataReady(bool fast = true);
  bool     readData(bool fast = true);
  uint32_t lastRequest();


  //  STATUS
  //  check sensor is reachable over I2C
  bool     isConnected();

  //  details see datasheet; summary in SHT85.cpp file
  uint16_t readStatus();

  //  lastRead is in milliSeconds since start
  uint32_t lastRead();

  bool     reset(bool hard = false);

  //  returns last error and clears error flag
  int      getError();


  //  HEATER
  //  do not use heater for long periods,
  //  use it for max 3 minutes to heat up
  //  and let it cool down at least 3 minutes.
  void     setHeatTimeout(uint8_t seconds);
  uint8_t  getHeatTimeout();
  bool     heatOn();
  bool     heatOff();
  //  is the sensor still heating up?
  bool     isHeaterOn();


  //  TEMPERATURE & HUMIDITY
  float    getHumidity();
  float    getTemperature();
  float    getFahrenheit();
  uint16_t getRawHumidity();
  uint16_t getRawTemperature();

  //  TEMPERATURE & HUMIDITY OFFSET
  void     setTemperatureOffset(float offset = 0);
  float    getTemperatureOffset();
  void     setHumidityOffset(float offset = 0);
  float    getHumidityOffset();


protected:
  uint8_t  crc8(const uint8_t *data, uint8_t len);
  bool     writeCmd(uint16_t cmd);
  bool     readBytes(uint8_t n, uint8_t *val);
  TwoWire* _wire;

  uint8_t  _address;
  uint8_t  _heatTimeout;   //  seconds
  uint32_t _lastRead;
  uint32_t _lastRequest;   //  for async interface
  uint32_t _heaterStart;   //  timestamp
  uint32_t _heaterStop;    //  timestamp
  bool     _heaterOn;
  uint8_t  _type;          //  base class = 0

  uint16_t _rawHumidity;
  uint16_t _rawTemperature;

  //  offset in degrees Celsius
  float    _temperatureOffset = 0;
  float    _humidityOffset    = 0;


  uint8_t _error;
};



////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class SHT30 : public SHT
{
public:
  SHT30(uint8_t address, TwoWire *wire = &Wire);
};


class SHT31 : public SHT
{
public:
  SHT31(uint8_t address, TwoWire *wire = &Wire);
};


class SHT35 : public SHT
{
public:
  SHT35(uint8_t address, TwoWire *wire = &Wire);
};


class SHT85 : public SHT
{
public:
  SHT85(uint8_t address, TwoWire *wire = &Wire);

  //  catch incorrect calls with an address, only 0x44 allowed, see #19
  bool begin();

  //  EXPERIMENTAL for 0.4.1
  uint32_t GetSerialNumber();
};


//  -- END OF FILE --

