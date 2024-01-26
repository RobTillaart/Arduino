#pragma once
//
//    FILE: AM2315.h
//  AUTHOR: Rob Tillaart
// PURPOSE: AM2315 Temperature and Humidity sensor library for Arduino
// VERSION: 0.2.1
//     URL: https://github.com/RobTillaart/AM2315
//
//  AM232X PIN layout             AM2315 COLOR
//  ============================================
//   bottom view  DESCRIPTION     COLOR
//       +---+
//       |o  |       VDD          RED
//       |o  |       SDA          YELLOW
//       |o  |       GND          BLACK
//       |o  |       SCL          GREY
//       +---+
//
//  do not forget pull up resistors between SDA, SCL and VDD.


#include "Arduino.h"
#include "Wire.h"


#define AM2315_LIB_VERSION                    (F("0.2.1"))


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

  bool     begin();
  //  datasheet- wake up is min 800 us max 3000 us
  bool     isConnected(uint16_t timeout = 3000);

  int      read();

  //  lastRead is in MilliSeconds since start sketch
  uint32_t lastRead()                 { return _lastRead; };

  //  preferred interface
  float    getHumidity();
  float    getTemperature();

  //  adding offsets works well in normal range
  //  might introduce under- or overflow at the ends of the sensor range
  void     setHumOffset(float offset = 0)  { _humOffset = offset; };
  void     setTempOffset(float offset = 0) { _tempOffset = offset; };
  float    getHumOffset()             { return _humOffset; };
  float    getTempOffset()            { return _tempOffset; };

  bool     getWaitForReading()        { return _waitForRead; };
  void     setWaitForReading(bool b ) { _waitForRead = b; };


  //  suppress error values of -999 => check return value of read() instead
  bool     getSuppressError()         { return _suppressError; };
  void     setSuppressError(bool b)   { _suppressError = b; };

  bool     wakeUp() { return isConnected(); };

private:
  uint8_t  _bits[8];    //  buffer to hold raw data
  float    _humidity      = 0.0;
  float    _temperature   = 0.0;
  float    _humOffset     = 0.0;
  float    _tempOffset    = 0.0;
  uint32_t _lastRead      = 0;

  bool     _waitForRead   = false;
  bool     _suppressError = false;

  int      _read();
  int      _readSensor();

  uint16_t _crc16(uint8_t *ptr, uint8_t len);

  TwoWire* _wire;
};


// -- END OF FILE --

