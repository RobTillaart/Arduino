#pragma once
//
//    FILE: GY521.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.6.1
// PURPOSE: Arduino library for I2C GY521 accelerometer-gyroscope sensor
//     URL: https://github.com/RobTillaart/GY521


#include "Arduino.h"
#include "Wire.h"


#define GY521_LIB_VERSION           (F("0.6.1"))

const float GRAVITY = 9.80655;


//  THROTTLE TIMING
#ifndef GY521_THROTTLE_TIME
#define GY521_THROTTLE_TIME         10   //  milliseconds
#endif


//  ERROR CODES
#define GY521_OK                     0
#define GY521_THROTTLED              1
#define GY521_ERROR_READ            -1
#define GY521_ERROR_WRITE           -2
#define GY521_ERROR_NOT_CONNECTED   -3
#define GY521_ERROR_PARAMETER       -4


//  CONVERSION CONSTANTS
#define GY521_RAD2DEGREES          (180.0 / PI)
#define GY521_DEGREES2RAD          (PI / 180.0)
#define GY521_RAW2DPS              (1.0 / 131.0)
#define GY521_RAW2G                (1.0 / 16384.0)


class GY521
{
public:
  //  address == 0x68 or 0x69
  GY521(uint8_t address = 0x69, TwoWire *wire = &Wire);

  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();
  void     reset();

  //  EXPERIMENTAL
  //  calibrate needs to be called to compensate for errors.
  //  must be called after setAccelSensitivity(as); and setGyroSensitivity(gs);
  bool     calibrate(uint16_t times, float angleX = 0, float angleY = 0, bool inverted = false);

  bool     wakeup();
  //  throttle to force delay between reads.
  void     setThrottle(bool throttle = true) { _throttle = throttle; };
  bool     getThrottle()                     { return _throttle; };
  //  0..65535 max milliseconds == roughly 1 minute.
  void     setThrottleTime(uint16_t ti )     { _throttleTime = ti; };
  uint16_t getThrottleTime()                 { return _throttleTime; };


  //  SET BEFORE READ
  //  as = 0,1,2,3 ==> 2g 4g 8g 16g
  bool     setAccelSensitivity(uint8_t as);
  uint8_t  getAccelSensitivity();          //  returns 0,1,2,3
  //  gs = 0,1,2,3  ==>  250, 500, 1000, 2000 degrees/second
  bool     setGyroSensitivity(uint8_t gs);
  uint8_t  getGyroSensitivity();           //  returns 0,1,2,3
  //  normalizes Pitch Roll and Yaw.
  void     setNormalize(bool normalize = true) { _normalize = normalize; };
  bool     getNormalize() { return _normalize; };


  //  READ THE SENSOR
  //  returns GY521_OK or one of the error codes above.
  int16_t  read();
  //  optimized partial reading
  //  read accelerometer only
  int16_t  readAccel();
  //  read gyroscope only can be done too
  //  however for pitch roll yaw you need all.
  int16_t  readGyro();
  //  read temperature only, does not affect throttle.
  int16_t  readTemperature();


  //  CALL AFTER READ
  float    getAccelX()   { return _ax; };
  float    getAccelY()   { return _ay; };
  float    getAccelZ()   { return _az; };
  float    getAngleX()   { return _aax; };
  float    getAngleY()   { return _aay; };
  float    getAngleZ()   { return _aaz; };
  float    getTemperature() { return _temperature; };
  float    getGyroX()    { return _gx; };
  float    getGyroY()    { return _gy; };
  float    getGyroZ()    { return _gz; };

  //  EXPERIMENTAL
  //  pitch, roll and yaw is work in progress.
  float    getPitch()    { return _pitch; };
  float    getRoll()     { return _roll; };
  float    getYaw()      { return _yaw; };


  //  last time sensor is actually read.
  uint32_t lastTime()    { return _lastTime; };

  //  CONFIGURATION
  //  Digital Low Pass Filter - datasheet P13-reg26
  bool     setDLPFMode(uint8_t mode);  //  returns false if mode > 6
  uint8_t  getDLPFMode();

  //  generic worker to get access to all functionality
  uint8_t  setRegister(uint8_t reg, uint8_t value);
  uint8_t  getRegister(uint8_t reg);


  //  get last error and reset error to OK.
  int16_t  getError()    { return _error; _error = GY521_OK; };


  //  calibration errors
  float    axe = 0, aye = 0, aze = 0;  //  accelerometer errors
  float    gxe = 0, gye = 0, gze = 0;  //  gyro errors


private:
  uint8_t  _address;                //  I2C address
  bool     _throttle = true;        //  to prevent reading too fast
  uint16_t _throttleTime = GY521_THROTTLE_TIME;
  uint32_t _lastTime = 0;           //  to measure duration for math & throttle
  uint32_t _lastMicros = 0;         //  to measure duration for math & throttle
  int16_t  _error = GY521_OK;       //  initially everything is OK

  uint8_t  _afs = 0;                //  sensitivity factor
  float    _raw2g = GY521_RAW2G;    //  raw data to gravity g's
  float    _ax, _ay, _az;           //  accelerometer raw
  float    _aax, _aay, _aaz;        //  accelerometer processed

  uint8_t  _gfs = 0;
  float    _raw2dps = GY521_RAW2DPS;
  float    _gx, _gy, _gz;           //  gyro raw
  float    _gax, _gay, _gaz;        //  gyro processed
  float    _pitch, _roll, _yaw;     //  used by user

  float    _temperature = 0;

  bool     _normalize = true;       //  default true.

  int16_t  _readRaw();
  //  to read register of 2 bytes.
  int16_t  _WireRead2();

  TwoWire*  _wire;
};


//  -- END OF FILE --
