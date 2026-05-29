//
//    FILE: I2C_ABP2.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2026-05-27
// PURPOSE: Arduino library for the Honeywell I2C ABP2 pressure sensors.
//     URL: https://github.com/RobTillaart/I2C_ABP2
//          https://github.com/RobTillaart/pressure   (conversions)



#include "I2C_ABP2.h"


I2C_ABP2::I2C_ABP2(uint8_t address, TwoWire *wire)
{
  _address  = address;
  _wire     = wire;
  _error    = 0;
  _lastRead = 0;
  _Bar      = 0;
  _celsius  = 0;
}


bool I2C_ABP2::begin(float minBar, float maxBar)
{
  _minBar = minBar;
  _maxBar = maxBar;
  //  reset variables
  _error    = 0;
  _lastRead = 0;
  _Bar      = 0;
  _celsius  = 0;

  if (! isConnected())
  {
    return false;
  }
  return true;
}


bool I2C_ABP2::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t I2C_ABP2::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  ASYNC INTERFACE
//
//  par 6.8 datasheet
//  split into an ASYNC interface
//
int I2C_ABP2::request()
{
  uint8_t readCommand[3] = { 0xAA, 0x00, 0x00 };
  _wire->beginTransmission(_address);
  _wire->write(readCommand, 3);
  _error = _wire->endTransmission();
  if (_error != 0) return _error;

  _error = I2C_ABP2_OK;
  return _error;
}

int I2C_ABP2::read()
{
  //  read data
  if (7 != _wire->requestFrom((uint8_t)_address, (uint8_t)7))
  {
    return I2C_ABP2_REQUEST_ERROR;
  }
  //  get state
  _state = _wire->read();
  //  get pressure
  uint32_t rawP = 0;
  for (int i = 0; i < 3; i++)
  {
    rawP <<= 8;
    rawP += _wire->read();
  }
  const float maxCnt = 15099494.0;
  const float minCnt = 1677722.0;
  _Bar = ((rawP - minCnt) * (_maxBar - _minBar)) / (maxCnt - minCnt) + _minBar; 
  //  get temperature
  uint32_t rawT = 0;
  for (int i = 0; i < 3; i++)
  {
    rawT <<= 8;
    rawT += _wire->read();
  }
  _celsius = rawT * (200.0 / 16777215.0) - 50;
  _lastRead = millis();
  _error = I2C_ABP2_OK;
  return _error;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int I2C_ABP2::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//


//  -- END OF FILE --

