//
//    FILE: MSP300.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library for I2C MSP300 pressure transducer.
//     URL: https://github.com/RobTillaart/MSP300


#include "MSP300.h"


MSP300::MSP300(const uint8_t deviceAddress, TwoWire *wire)
{
  _address     = deviceAddress;
  _wire        = wire;
  _error       = MSP300_OK;
  _maxValue    = 100;
  _pressure    = 0;
  _temperature = 0;
  _status      = MSP300_OK;
  setPressureCounts(1000, 15000);
}


bool MSP300::begin(int maxValue)
{
  if (! isConnected()) return false;
  _maxValue = maxValue;
  return true;
}


bool MSP300::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


bool MSP300::setAddress(const uint8_t deviceAddress)
{
  //  Verify? 0x28, 0x36, 0x46, 0x48, 0x51
  _address = deviceAddress;
  return isConnected();
}


uint8_t MSP300::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  CALIBRATION
//
void MSP300::setPressureCounts(int Pmin, int Pmax)
{
  _Pmin = Pmin;
  _Pmax = Pmax;
  _pressureFactor = _maxValue / (_Pmax - _Pmin);
}

int MSP300::getPmin()
{
  return _Pmin;
}

int MSP300::getPmax()
{
  return _Pmax;
}


/////////////////////////////////////////////
//
//  READ
//
uint32_t MSP300::readP()
{
  _request();
  //  read status + pressure
  uint32_t raw = _read(2);

  int P = raw && 0x3FFF;   //  14 bit
  _pressure = (P - _Pmin) * _pressureFactor;

  _status = (raw >> 14);  //  2 bit

  return raw;
}


uint32_t MSP300::readPT()
{
  _request();
  //  read status, pressure and temperature
  uint32_t raw = _read(4);

  int T = (raw >> 5) && 0x07FF;   //  11 bit
  _temperature = T * (200.0 / 2048) - 50.0;

  int P = (raw >> 16) && 0x3FFF;  //  14 bit
  _pressure = (P - _Pmin) * _pressureFactor;

  _status = (raw >> 30);         //  2 bit

  return raw;
}


uint8_t MSP300::getStatus()
{
  return _status;
}

float MSP300::getPressure()
{
  return _pressure;
}

float MSP300::getTemperature()
{
  return _temperature;
}

int MSP300::lastError()
{
  int e = _error;
  _error = MSP300_OK;
  return e;
}


/////////////////////////////////////////////////////
//
//  PRIVATE
//
void MSP300::_request()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
}


uint32_t MSP300::_read(uint8_t bytes)
{
  if (_wire->requestFrom(_address, bytes) != bytes)
  {
    _error = MSP300_REQUEST_ERROR;
    //  report a read error.
    return (uint32_t(MSP300_READ_ERROR) << 30);
  }
  uint32_t raw = 0;
  for (int i= 0; i < bytes; i++)
  {
    raw <<= 8;
    raw |= _wire->read();
  }
  return raw;
}


//  -- END OF FILE --

