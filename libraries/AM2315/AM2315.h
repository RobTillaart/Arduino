#pragma once
//
//    FILE: AM2315.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: AM2315 Temperature and Humidity sensor library for Arduino
//     URL: https://github.com/RobTillaart/AM2315


//  AM232X PIN layout             AM2315 COLOR
//  ============================================
//   bottom view  DESCRIPTION     COLOR
//       +---+
//       |o  |       VDD          RED
//       |o  |       SDA          YELLOW
//       |o  |       GND          BLACK
//       |o  |       SCL          GREY
//       +---+


#include "Arduino.h"
#include "Wire.h"


#define AM2315_LIB_VERSION                    (F("0.1.1"))


#define AM2315_OK                             0
#define AM2315_ERROR_CHECKSUM                 -10
#define AM2315_ERROR_CONNECT                  -11
#define AM2315_MISSING_BYTES                  -12
#define AM2315_WAITING_FOR_READ               -50


//  optionally detect out of range values.
//  occurs seldom so not enabled by default.
//  #define AM2315_VALUE_OUT_OF_RANGE
#define AM2315_HUMIDITY_OUT_OF_RANGE          -100
#define AM2315_TEMPERATURE_OUT_OF_RANGE       -101

//  allows to overrule AM2315_INVALID_VALUE e.g. to prevent spike in graphs.
#ifndef AM2315_INVALID_VALUE
#define AM2315_INVALID_VALUE                  -999
#endif


class AM2315
{
public:

  AM2315(TwoWire *wire = &Wire);

#if defined(ESP8266) || defined(ESP32)
  bool     begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  bool     begin();
  // datasheet- wake up is min 800 us max 3000 us
  bool     isConnected(uint16_t timeout = 3000);

  int      read();

  // lastRead is in MilliSeconds since start sketch
  uint32_t lastRead()                    { return _lastRead; };

  // preferred interface
  float    getHumidity();
  float    getTemperature();

  // adding offsets works well in normal range
  // might introduce under- or overflow at the ends of the sensor range
  void     setHumOffset(float offset)    { _humOffset = offset; };
  void     setTempOffset(float offset)   { _tempOffset = offset; };
  float    getHumOffset()                { return _humOffset; };
  float    getTempOffset()               { return _tempOffset; };

  bool     getWaitForReading()           { return _waitForRead; };
  void     setWaitForReading(bool b )    { _waitForRead = b; };

  // set readDelay to 0 will reset to datasheet values
  uint16_t getReadDelay()                { return _readDelay; };
  void     setReadDelay(uint16_t rd = 0) { _readDelay = rd; };


  // suppress error values of -999 => check return value of read() instead
  bool     getSuppressError()            { return _suppressError; };
  void     setSuppressError(bool b)      { _suppressError = b; };

  bool     wakeUp() { return isConnected(); };

private:
  float    _humOffset     = 0.0;
  float    _tempOffset    = 0.0;
  float    _humidity      = 0.0;
  float    _temperature   = 0.0;
  uint32_t _lastRead      = 0;
  bool     _waitForRead   = false;
  bool     _suppressError = false;
  uint16_t _readDelay     = 0;

  uint8_t  _bits[5];  // buffer to receive data
  int      _read();
  int      _readSensor();
  uint16_t _crc16(uint8_t *ptr, uint8_t len);

  TwoWire* _wire;
};


// -- END OF FILE --

