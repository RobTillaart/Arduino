//
//    FILE: LTC2485.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.4
//    DATE: 2025-02-21
// PURPOSE: Arduino library for LTC2485 I2C 24 bit ADC.
//     URL: https://github.com/RobTillaart/LTC2485


#include "LTC2485.h"


//  CONVERSION
//  needed as I2C is blocked during conversion.
#define LTC2485_DELAY_1X                        200
#define LTC2485_DELAY_2X                        100  //  not used yet


//  CALIBRATION
//  adjust these numbers to your need
//  determine them by averaging multiple TC measurements.
//
//  Datasheet page 20: 27 C; 420 mV; 1.40 mV/°C
//
const float LTC2485_TAVERAGE       = 27.0;    //  °C
const float LTC2485_MVOLT_TAVERAGE = 420.0;   //  mV
const float LTC2485_SLOPE          = 1.40;    //  mV/°C


/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
//
LTC2485::LTC2485(uint8_t address, TwoWire *wire)
{
  _address    = address;
  _wire       = wire;
  //  defaults
  _lastAccess = 0;
  _timeout    = LTC2485_DELAY_1X;
  _error      = LTC2485_OK;
  _vref       = 2.5;
  _config     = LTC2485_SPEED_1X | LTC2485_REJECT_50_60_HZ;
}


bool LTC2485::begin(float VREF)
{
  _vref = VREF;
  //  optional address check
  if (! isConnected()) return false;
  configure(_config);
  return true;
}


bool LTC2485::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t LTC2485::getAddress()
{
  return _address;
}


int LTC2485::configure(uint8_t config)
{
  //  skip invalid configurations, see table 1.
  //  TODO specific error codes.
  if (config & 0x06) return 255;
  if (config == 0x09) return 255;
  if (config & 0xF0) return 255;
  _config = config;

  //  hard wait until conversion is done...
  delay(_timeout);
  int rv = _write(_config);

  //  update lastAccess on successful write
  if (rv == 0)
  {
    _lastAccess = millis();
  }
  return rv;
}


int32_t LTC2485::getADC()
{
  //  only reconfigure if TEMPERATURE flag is set.
  if ((_config & LTC2485_INTERNAL_TEMP) > 0)
  {
    if (configure(_config & 0x07) != 0)
    {
      _error = LTC2485_ERR_CONFIG_ADC;
      return 0;
    }
  }

  //  hard wait until conversion is done...
  delay(_timeout);
  //  read the ADC
  int32_t value = _read();
  //  update lastAccess
  _lastAccess = millis();
  //  make two complements.
  value ^= 0x80000000;
  return value / 128;  //  31 bits => 24 bits.
}


float LTC2485::getVolts()
{
  //  return getADC() * _vref / 16777215L;
  return getADC() * _vref * 5.960464832810e-8;
}


float LTC2485::getTemperature()
{
  //  only reconfigure if TEMPERATURE flag is NOT set.
  if ((_config & LTC2485_INTERNAL_TEMP) == 0)
  {
    if (configure(_config | LTC2485_INTERNAL_TEMP) != 0)
    {
      _error = LTC2485_ERR_CONFIG_TEMP;
      return 0;
    }
  }

  //  hard wait until conversion is done...
  delay(_timeout);
  //  read the ADC
  int32_t value = _read();
  //  DEBUG
  //  Serial.print(F("TRAW: \t"));
  //  Serial.print(value, HEX);
  //  Serial.print(F("\t"));
  //  Serial.println(value, DEC);

  //  update lastAccess
  _lastAccess = millis();
  //  make two complements.
  value ^= 0x80000000;
  value /= 128;

  //  16777215 == 2^24 - 1
  //  div 16777215 == mul 5.960464832810e-8
  //  float milliVolts = value * _vref * 5.960464832810e-8 * 1000;
  float milliVolts = value * _vref * 5.960464832810e-5;
  _lastAccess = millis();
  //  datasheet page 20
  //  adjust constants at top of file.
  //  27 C  == 420 mV
  //  SLOPE == 1.40 mV / °C
  float TC = LTC2485_TAVERAGE + (milliVolts - LTC2485_MVOLT_TAVERAGE) / LTC2485_SLOPE;
  return TC;
}


uint32_t LTC2485::lastAccessed()
{
  return _lastAccess;
}


/////////////////////////////////////////////////////
//
//  ERROR HANDLING
//
int LTC2485::getLastError()
{
  int e = _error;
  _error = LTC2485_OK;
  return e;
}


//////////////////////////////////////////////////////////////////
//
//  PRIVATE functions
//
int LTC2485::_write(uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(value);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    _error = LTC2485_ERR_I2C_W;
  }
  return n;
}


uint32_t LTC2485::_read()
{
  int n = _wire->requestFrom(_address, (uint8_t)4);
  if (n != 4)
  {
    _error = LTC2485_ERR_I2C_R;
    return n;
  }
  uint32_t rv = 0;
  rv |= _wire->read();
  rv <<= 8;
  rv |= _wire->read();
  rv <<= 8;
  rv |= _wire->read();
  rv <<= 8;
  rv |= _wire->read();
  return rv;

  //  DEBUG
  //  uint32_t A = _wire->read();
  //  uint32_t B = _wire->read();
  //  uint32_t C = _wire->read();
  //  uint32_t D = _wire->read();
  //  if (A < 0x10) Serial.print(0);
  //  Serial.print(A, HEX);
  //  Serial.print("\t");
  //  if (B < 0x10) Serial.print(0);
  //  Serial.print(B, HEX);
  //  Serial.print("\t");
  //  if (C < 0x10) Serial.print(0);
  //  Serial.print(C, HEX);
  //  Serial.print("\t");
  //  if (D < 0x10) Serial.print(0);
  //  Serial.print(D, HEX);
  //  Serial.print("\t");

  //  rv = (A << 24) + (B << 16) + (C << 8) + D;
  //  return rv;
}


//  -- END OF FILE --

