#pragma once
//
//    FILE: SHT2x.h
//  AUTHOR: Rob Tillaart, Viktor Balint
// VERSION: 0.1.0
//    DATE: 2021-09-25
// PURPOSE: Arduino library for the SHT2x temperature and humidity sensor
//     URL: https://github.com/RobTillaart/SHT2x
//


#include "Arduino.h"
#include "Wire.h"


#define SHT2x_LIB_VERSION             (F("0.1.0"))


// fields getStatus   TODO meaning?
#define SHT2x_STATUS_                 0x00


// error codes 
// kept in sync with SHT31 library
#define SHT2x_OK                      0x00
#define SHT2x_ERR_WRITECMD            0x81
#define SHT2x_ERR_READBYTES           0x82
#define SHT2x_ERR_HEATER_OFF          0x83
#define SHT2x_ERR_NOT_CONNECT         0x84
#define SHT2x_ERR_CRC_TEMP            0x85
#define SHT2x_ERR_CRC_HUM             0x86
#define SHT2x_ERR_CRC_STATUS          0x87     // not used
#define SHT2x_ERR_HEATER_COOLDOWN     0x88
#define SHT2x_ERR_HEATER_ON           0x89


class SHT2x
{
public:
  SHT2x();

#if defined(ESP8266) || defined(ESP32)
  bool begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  bool begin(TwoWire *wire = &Wire);

  // check sensor is reachable over I2C
  bool isConnected();

  // read must be called first...
  bool read();

  float    getTemperature();
  float    getHumidity();
  uint16_t getRawTemperature() { return _rawHumidity; };
  uint16_t getRawHumidity()    { return _rawTemperature; };

  // might take up to 15 milliseconds.
  bool reset();

  // details see datasheet; summary in SHT2x.cpp file
  uint8_t getStatus();

  // lastRead is in milliSeconds since start
  uint32_t lastRead() { return _lastRead; };


  // HEATER
  // do not use heater for long periods,
  // use it for max 3 minutes to heat up
  // and let it cool down at least 3 minutes.
  void    setHeatTimeout(uint8_t seconds);
  uint8_t getHeatTimeout() { return _heatTimeout; };

  bool heatOn();
  bool heatOff();
  bool isHeaterOn();  // is the sensor still heating up?

  int getError(); // clears error flag

private:
  uint8_t   crc8(const uint8_t *data, uint8_t len);

  bool      writeCmd(uint8_t cmd);
  bool      writeCmd(uint8_t cmd, uint8_t value);
  bool      readBytes(uint8_t n, uint8_t *val, uint8_t maxDuration);
  TwoWire* _wire;

  uint8_t   _heatTimeout;   // seconds
  uint32_t  _lastRead;
  uint32_t  _lastRequest;   // for async interface
  uint32_t  _heaterStart;
  uint32_t  _heaterStop;
  bool      _heaterOn;

  uint16_t  _rawHumidity;
  uint16_t  _rawTemperature;

  uint8_t   _status;

  uint8_t   _error;
};



////////////////////////////////////////////////////////
//
// DERIVED
//
class SHT20 : public SHT2x
{
public:
  SHT20();
};

class SHT21 : public SHT2x
{
public:
  SHT21();
};


class SHT25 : public SHT2x
{
public:
  SHT25();
};


// -- END OF FILE --
