#pragma once
//
//    FILE: AM232X.h
//  AUTHOR: Rob Tillaart
// PURPOSE: AM232X Temperature and Humidity sensor library for Arduino
// VERSION: 0.5.1
//     URL: https://github.com/RobTillaart/AM232X
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


#define AM232X_LIB_VERSION              (F("0.5.1"))


#define AM232X_OK                        0
#define AM232X_ERROR_UNKNOWN            -10
#define AM232X_ERROR_CONNECT            -11
#define AM232X_ERROR_FUNCTION           -12
#define AM232X_ERROR_ADDRESS            -13
#define AM232X_ERROR_REGISTER           -14
#define AM232X_ERROR_CRC_1              -15
#define AM232X_ERROR_CRC_2              -16
#define AM232X_ERROR_WRITE_DISABLED     -17
#define AM232X_ERROR_WRITE_COUNT        -18
#define AM232X_MISSING_BYTES            -19
#define AM232X_READ_TOO_FAST            -20


/*
   from datasheet
   0x80: not support function code
   0x81: Read an illegal address
   0x82: write data beyond the scope
   0x83: CRC checksum error
   0x84: Write disabled
*/


//  optionally detect out of range values.
//  occurs seldom so not enabled by default.
//  #define AM232X_VALUE_OUT_OF_RANGE
#define AM232X_HUMIDITY_OUT_OF_RANGE          -100
#define AM232X_TEMPERATURE_OUT_OF_RANGE       -101


//  allows to overrule AM232X_INVALID_VALUE e.g. to prevent spike in graphs.
#ifndef AM232X_INVALID_VALUE
#define AM232X_INVALID_VALUE                  -999
#endif


class AM232X
{
public:
  explicit AM232X(TwoWire *wire = &Wire);

  bool     begin();
  //  datasheet 8.2 - wake up is min 800 us max 3000 us
  bool     isConnected(uint16_t timeout = 3000);

  int      read();
  //  lastRead is in MilliSeconds since start sketch
  uint32_t lastRead()     { return _lastRead; };

  //  set readDelay to 0 will reset to datasheet values
  uint16_t getReadDelay() { return _readDelay; };
  void     setReadDelay(uint16_t readDelay = 0);

  //  negative return values are errors
  int      getModel();
  int      getVersion();
  uint32_t getDeviceID();

  int      getStatus();
  int      getUserRegisterA();
  int      getUserRegisterB();

  int      setStatus(uint8_t value);
  int      setUserRegisterA(int value);
  int      setUserRegisterB(int value);

  float    getHumidity();
  float    getTemperature();

  // adding offsets works well in normal range
  // might introduce under- or overflow at the ends of the sensor range
  void     setHumOffset(float offset = 0)  { _humOffset = offset; };
  void     setTempOffset(float offset = 0) { _tempOffset = offset; };
  float    getHumOffset()           { return _humOffset; };
  float    getTempOffset()          { return _tempOffset; };

  // suppress error values of -999 => check return value of read() instead
  bool     getSuppressError()         { return _suppressError; };
  void     setSuppressError(bool b)   { _suppressError = b; };

  bool     wakeUp() { return isConnected(); };


protected:
  uint8_t  _bits[8];    //  buffer to hold raw data
  float    _humidity      = 0.0;
  float    _temperature   = 0.0;
  float    _humOffset     = 0.0;
  float    _tempOffset    = 0.0;
  uint32_t _lastRead      = 0;
  uint16_t _readDelay     = 2000;

  bool     _suppressError = false;

  int      _readRegister(uint8_t reg, uint8_t count);
  int      _writeRegister(uint8_t reg, uint8_t count, int16_t value);
  int      _getData(uint8_t length);

  uint16_t _crc16(uint8_t *ptr, uint8_t length);

  TwoWire* _wire;
};


/////////////////////////////////////////////////////////////////////////////
//
//  AM232X derived classes
//
class AM2320 : public AM232X
{
public:
  AM2320(TwoWire *wire = &Wire);
};


class AM2321 : public AM232X
{
public:
  AM2321(TwoWire *wire = &Wire);
};


class AM2322 : public AM232X
{
public:
  AM2322(TwoWire *wire = &Wire);
};


// -- END OF FILE --

