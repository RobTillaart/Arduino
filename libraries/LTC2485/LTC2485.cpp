//
//    FILE: LTC2485.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-02-21
// PURPOSE: Arduino library for LTC2485 I2C 24 bit ADC.
//     URL: https://github.com/RobTillaart/LTC2485


#include "LTC2485.h"



/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
//
LTC2485::LTC2485(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


bool LTC2485::begin(float VREF)
{
  _vref = VREF;
  //  optional address check
  if (! isConnected()) return false;
  configure(0x00);
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

uint8_t LTC2485::configure(uint8_t config)
{
  //  skip invalid configuration, see table 1.
  if ((config & 0x06) || (config == 0x09)) return 255;
  if (config & 0xF0) return 255;
  _config = config;
  return _write(_config);
}


int32_t LTC2485::getADC()
{
  if ((_config & LTC2485_INTERNAL_TEMP) > 0)
  {
    configure(_config & 0x07);
  }
  int32_t value = _read();
  //  TODO check read error
  value ^= 0x80000000;
  return int32_t(value);
}


float LTC2485::getVolts()
{
  //  return (getADC() * _vref) / 16777215L;
  return getADC() * _vref * 6.1643863061e-8;
}


float LTC2485::getTemperature()
{
  if ((_config & LTC2485_INTERNAL_TEMP) == 0)
  {
    configure(_config | LTC2485_INTERNAL_TEMP);
  }
  //  datasheet page 20
  //  27 C  == 420 mV
  //  SLOPE == 1.40 mV
  float TC = 27.0 + (getVolts() - 0.420);
  return TC;
}


uint32_t LTC2485::lastRead()
{
  return _lastRead;
}


//////////////////////////////////////////////////////////////////
//
//  PRIVATE functions
//
uint8_t LTC2485::_write(uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(value);
  return _wire->endTransmission();
}


uint32_t LTC2485::_read()
{
  uint32_t rv = 0;
  if ( 4 == _wire->requestFrom(_address, (uint8_t)4))
  {
    _lastRead = millis();
    rv |= _wire->read();
    rv <<= 8;
    rv |= _wire->read();
    rv <<= 8;
    rv |= _wire->read();
    rv <<= 8;
    rv |= _wire->read();
    return rv;
  }
  return 0xFFFFFFFF;
}



//  -- END OF FILE --

