#pragma once
//
//    FILE: dhtint.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
// PURPOSE: Arduino library for DHT sensors - integer only
//     URL: https://github.com/RobTillaart/DHTINT
//
//  DHT PIN layout from left to right
//  =================================
//  FRONT   :   DESCRIPTION
//  pin 1   :   VCC
//  pin 2   :   DATA
//  pin 3   :   Not Connected
//  pin 4   :   GND


#include "Arduino.h"


#define DHTINT_LIB_VERSION                (F("0.1.4 experimental"))


#define DHTLIB_OK                         0
#define DHTLIB_ERROR_CHECKSUM            -1
#define DHTLIB_ERROR_TIMEOUT_A           -2
#define DHTLIB_ERROR_BIT_SHIFT           -3
#define DHTLIB_ERROR_SENSOR_NOT_READY    -4
#define DHTLIB_ERROR_TIMEOUT_C           -5
#define DHTLIB_ERROR_TIMEOUT_D           -6
#define DHTLIB_ERROR_TIMEOUT_B           -7
#define DHTLIB_WAITING_FOR_READ          -8

//  optionally detect out of range values.
//  occurs seldom so not enabled by default.
//  #define DHTLIB_VALUE_OUT_OF_RANGE
#define DHTLIB_HUMIDITY_OUT_OF_RANGE     -100
#define DHTLIB_TEMPERATURE_OUT_OF_RANGE  -101

//  allows to overrule DHTLIB_INVALID_VALUE e.g. to prevent spike in graphs.
#ifndef DHTLIB_INVALID_VALUE
#define DHTLIB_INVALID_VALUE           -999
#endif


//  bits are timing based (datasheet)
//    26-28us ==> 0
//    70 us   ==> 1
//  See https://github.com/RobTillaart/DHTNew/issues/11
#ifndef DHTLIB_BIT_THRESHOLD
#define DHTLIB_BIT_THRESHOLD             50
#endif


class DHTINT
{
public:

  DHTINT(uint8_t pin);

  //  resets all internals to construction time
  //  might help to reset a sensor behaving badly..
  void     reset();

  //  0 = unknown, 11 or 22
  uint8_t  getType();
  void     setType(uint8_t type = 0);
  int      read();

  //  lastRead is in MilliSeconds since start sketch
  uint32_t lastRead()                    { return _lastRead; };

  //  preferred interface
  int      getHumidity();
  int      getTemperature();

  //  adding offsets works well in normal range
  //  might introduce under- or overflow at the ends of the sensor range
  void     setHumOffset(int offset)      { _humOffset = offset * 10; };
  void     setTempOffset(int offset)     { _tempOffset = offset * 10; };
  int      getHumOffset()                { return _humOffset / 10; };
  int      getTempOffset()               { return _tempOffset / 10; };

  //  set offset in 1/10th
  void     setHumOffsetDecimal(int offset)  { _humOffset = offset; };
  void     setTempOffsetDecimal(int offset) { _tempOffset = offset; };
  int      getHumOffsetDecimal()            { return _humOffset; };
  int      getTempOffsetDecimal()           { return _tempOffset; };


  bool     getDisableIRQ()               { return _disableIRQ; };
  void     setDisableIRQ(bool b )        { _disableIRQ = b; };

  bool     getWaitForReading()           { return _waitForRead; };
  void     setWaitForReading(bool b )    { _waitForRead = b; };

  //  set readDelay to 0 will reset to datasheet values
  uint16_t getReadDelay()                { return _readDelay; };
  void     setReadDelay(uint16_t rd = 0) { _readDelay = rd; };

  //  minimal support for low power applications.
  //  after powerUp one must wait up to two seconds.
  void     powerUp();
  void     powerDown();

  //  suppress error values of -999 => check return value of read() instead
  bool     getSuppressError()            { return _suppressError; };
  void     setSuppressError(bool b)      { _suppressError = b; };

  //  raw data for efficient storage / transport and
  //  to access the decimal part if needed.
  //  decoding depends on type sensor.
  uint16_t getRawTemperature();
  uint16_t getRawHumidity();


private:
  uint8_t  _dataPin       = 0;
  uint8_t  _wakeupDelay   = 0;
  uint8_t  _type          = 0;
  int      _humOffset     = 0;
  int      _tempOffset    = 0;
  int      _humidity      = 0;
  int      _temperature   = 0;
  uint32_t _lastRead      = 0;
  bool     _disableIRQ    = true;
  bool     _waitForRead   = false;
  bool     _suppressError = false;
  uint16_t _readDelay     = 0;

  uint8_t  _bits[5];  //  buffer to receive data
  int      _read();
  int      _readSensor();
  bool     _waitFor(uint8_t state, uint32_t timeout);
};


//  -- END OF FILE --

