//
//    FILE: GY521.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library for I2C GY521 accelerometer-gyroscope sensor
//     URL: https://github.com/RobTillaart/GY521
//
//  HISTORY:
//  0.1.0   2017-11-20  initial version
//  0.1.1   2020-07-09  refactor + initial release
//  0.1.2   2020-08-06  fix setAccelSensitivity + add getters
//  0.1.3   2020-08-07  fix ESP support + pitch roll yaw demo
//  0.1.4   2020-09-29  fix #5 missing ;
//  0.1.5   2020-09-29  fix #6 fix math for Teensy
//  0.2.0   2020-11-03  improve error handling
//  0.2.1   2020-12-24  arduino-ci + unit tests
//  0.2.2   2021-01-24  add interface part to readme.md 
//                      add GY521_registers.h
//  0.2.3   2021-01-26  align version numbers (oops)
//  0.3.0   2021-04-07  fix #18 acceleration error correction (kudo's to Merkxic)


#include "GY521.h"

// keep register names in sync with BIG MPU6050 lib
#include "GY521_registers.h"

#define GY521_WAKEUP                 0x00

#define RAD2DEGREES                 (180.0 / PI)


/////////////////////////////////////////////////////
//
// PUBLIC
//
GY521::GY521(uint8_t address)
{
  _address = address;
  setThrottleTime(GY521_THROTTLE_TIME);
}

#if defined (ESP8266) || defined(ESP32)
bool GY521::begin(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);
  return isConnected();
}
#endif

bool GY521::begin()
{
  Wire.begin();
  return isConnected();
}

bool GY521::isConnected()
{
  Wire.beginTransmission(_address);
  return (Wire.endTransmission() == 0);
}

bool GY521::wakeup()
{
  Wire.beginTransmission(_address);
  Wire.write(GY521_PWR_MGMT_1);
  Wire.write(GY521_WAKEUP);
  return (Wire.endTransmission() == 0);
}

int16_t GY521::read()
{
  if (_throttle)
  {
    if ((millis() - _lastTime) < _throttleTime)
    {
      return GY521_THROTTLED;
    }
  }

  // Connected ?
  Wire.beginTransmission(_address);
  Wire.write(GY521_ACCEL_XOUT_H);
  if (Wire.endTransmission() != 0) return GY521_ERROR_WRITE;

  // Get the data
  int8_t n = Wire.requestFrom(_address, (uint8_t)14);
  if (n != 14) return GY521_ERROR_READ;
  // ACCELEROMETER
  _ax = _WireRead2();  // ACCEL_XOUT_H  ACCEL_XOUT_L
  _ay = _WireRead2();  // ACCEL_YOUT_H  ACCEL_YOUT_L
  _az = _WireRead2();  // ACCEL_ZOUT_H  ACCEL_ZOUT_L
  // TEMPERATURE
  _temperature = _WireRead2(); // TEMP_OUT_H    TEMP_OUT_L
  // GYROSCOPE
  _gx = _WireRead2();  // GYRO_XOUT_H   GYRO_XOUT_L
  _gy = _WireRead2();  // GYRO_YOUT_H   GYRO_YOUT_L
  _gz = _WireRead2();  // GYRO_ZOUT_H   GYRO_ZOUT_L

  // time interval
  uint32_t now = millis();
  float duration = (now - _lastTime) * 0.001;   // time in seconds.
  _lastTime = now;

  // Convert raw acceleration to g's
  _ax *= _raw2g;
  _ay *= _raw2g;
  _az *= _raw2g;

  // Error correct raw acceleration (in g) measurements  // #18 kudos to Merkxic
  _ax += axe;
  _ay += aye;
  _az += aze;

  // prepare for Pitch Roll Yaw
  _aax = atan(_ay / hypot(_ax, _az)) * RAD2DEGREES;
  _aay = atan(-1.0 * _ax / hypot(_ay, _az)) * RAD2DEGREES;
  _aaz = atan(_az / hypot(_ax, _ay)) * RAD2DEGREES;

  // Convert to Celsius
  _temperature = _temperature * 0.00294117647 + 36.53;  //  == /340.0  + 36.53;

  // Convert raw Gyro to degrees/seconds
  _gx *= _raw2dps;
  _gy *= _raw2dps;
  _gz *= _raw2dps;
  
  // Error correct raw gyro measurements.
  _gx += gxe;
  _gy += gye;
  _gz += gze;
  
  _gax += _gx * duration;
  _gay += _gy * duration;
  _gaz += _gz * duration;

  _yaw = _gaz;
  _pitch = 0.96 * _gay + 0.04 * _aay;
  _roll = 0.96 * _gax + 0.04 * _aax;

  return GY521_OK;
}

bool GY521::setAccelSensitivity(uint8_t as)
{
  _afs = as;
  if (_afs > 3) _afs = 3;
  uint8_t val = getRegister(GY521_ACCEL_CONFIG);
  if (_error != 0)
  {
    return false;
  }
  // no need to write same value
  if (((val >> 3) & 3) != _afs)
  {
    val &= 0xE7;
    val |= (_afs << 3);
    if (setRegister(GY521_ACCEL_CONFIG, val) != GY521_OK)
    {
      return false;
    }
  }
  // calculate conversion factor.
  _raw2g = (1 << _afs) / 16384.0;
  return true;
}

uint8_t GY521::getAccelSensitivity()
{
  uint8_t val = getRegister(GY521_ACCEL_CONFIG);
  if (_error != GY521_OK)
  {
    return _error; // return and propagate error (best thing to do)
  }
  _afs = (val >> 3) & 3;
  return _afs;
}

bool GY521::setGyroSensitivity(uint8_t gs)
{
  _gfs = gs;
  if (_gfs > 3) _gfs = 3;
  uint8_t val = getRegister(GY521_GYRO_CONFIG);
  if (_error != 0)
  {
    return false;
  }
  // no need to write same value
  if (((val >> 3) & 3) != _gfs)
  {
    val &= 0xE7;
    val |= (_gfs << 3);
    if (setRegister(GY521_GYRO_CONFIG, val) != GY521_OK)
    {
      return false;
    }
  }
  // calculate conversion factor.
  _raw2dps = (1 << _gfs) / 131.0;
  return true;
}

uint8_t GY521::getGyroSensitivity()
{
  uint8_t val = getRegister(GY521_GYRO_CONFIG);
  if (_error != GY521_OK)
  {
    return _error; // return and propagate error (best thing to do)
  }
  _gfs = (val >> 3) & 3;
  return _gfs;
}

uint8_t GY521::setRegister(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write(value);
  // no need to do anything if not connected.
  if (Wire.endTransmission() != 0) 
  {
    _error = GY521_ERROR_WRITE;
    return _error;
  }
  return GY521_OK;
}

uint8_t GY521::getRegister(uint8_t reg)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  if (Wire.endTransmission() != 0)
  {
    _error = GY521_ERROR_WRITE;
    return _error;
  }
  uint8_t n = Wire.requestFrom(_address, (uint8_t) 1);
  if (n != 1) 
  {
    _error = GY521_ERROR_READ;
    return _error;
  }
  uint8_t val = Wire.read();
  return val;
}

// to read register of 2 bytes.
int16_t GY521::_WireRead2()
{
  int16_t tmp = Wire.read();
  tmp <<= 8;
  tmp |= Wire.read();
  return tmp;
}

// -- END OF FILE --
