//
//    FILE: MS4525DO.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2025-12-06
// PURPOSE: Arduino library for the I2C MS4525DO pressure and temperature sensor.
//     URL: https://github.com/RobTillaart/MS4525DO_RT


#include "MS4525DO.h"


MS4525DO::MS4525DO(uint8_t address, TwoWire *wire)
{
  reset();
  _address     = address;
  _wire        = wire;
  _maxPressure = 0;
  _state       = MS4525DO_INIT;
  _type        = 'A';
}


bool MS4525DO::begin(uint8_t psi, char type)
{
  reset();
  if (! isConnected())
  {
    _state = MS4525DO_CONNECT_ERROR;
    return false;
  }

  if ((psi == 150) || (psi == 100) || (psi == 50) || (psi == 30) ||
      (psi ==  15) || (psi == 05)  || (psi == 02) || (psi == 01))
  {
    _maxPressure = psi * PSI2MILLIBAR;
  }
  else
  {
    _state = MS4525DO_CONFIG_ERROR;
    return false;
  }

  if ((type == 'A') || (type == 'B'))
  {
    _type = type;
  }
  else
  {
    _state = MS4525DO_CONFIG_ERROR;
    return false;
  }

  _state = MS4525DO_OK;
  return true;
}


void MS4525DO::reset()
{
  _errorCount  = 0;
  _lastRead    = 0;
  _pressure    = 0;
  _temperature = 0;
  _state       = MS4525DO_INIT;
}


uint8_t MS4525DO::getAddress()
{
  return _address;
}


bool MS4525DO::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


int MS4525DO::read()
{
  _wire->requestFrom(_address, (uint8_t)4);
  if (_wire->available() != 4)
  {
    _errorCount++;
    _state = MS4525DO_READ_ERROR;
    return _state;
  }
  //  PROCESS PRESSURE
  _rpc = _wire->read() * 256;  //  hi byte
  _rpc    += _wire->read();    //  lo byte
  if (_rpc & 0xC000)
  {
    _errorCount++;
    _state = MS4525DO_OVF_ERROR;  //  no documentation, bits may not be set
    return _state;
  }

  _lastRead = millis();
  //  raw = 0..16383
  //  A == 10 - 90
  //  B ==  5 - 95
  if (_type == 'A')
  {
    //  _pressure = map(_rpc, 1638, 14746, 0, _maxPressure);
    //  _pressure = (_rpc - 1638) * (_maxPressure - 0) / ( 14746 - 1638);
    _pressure = (_rpc - 1638) * _maxPressure * 7.6289289E-5;
  }
  else // type == 'B'
  {
    //  _pressure = map(_rpc, 819, 15563, 0, _maxPressure);
    //  _pressure = (_rpc - 819) * (_maxPressure - 0) / ( 15563 - 819);
    _pressure = (_rpc - 819) * _maxPressure * 6.7824200E-5;
  }


  //  PROCESS TEMPERATURE
  _rtc  = _wire->read() * 256;  //  hi byte
  _rtc += _wire->read();        //  lo byte
  if (_rtc & 0xF800)
  {
    _errorCount++;
    _state = MS4525DO_OVF_ERROR;  //  no documentation, bits may not be set
    return _state;
  }
  //  _temperature = -50.0 + _rtc * 200.0 / 2047;
  _temperature = -50.0 + _rtc * (200.0 * 4.8851979E-4);

  _state = MS4525DO_OK;
  return _state;
}


//  -- END OF FILE --

