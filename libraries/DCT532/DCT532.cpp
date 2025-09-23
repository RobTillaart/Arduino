//
//    FILE: DCT532.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-06-03
// VERSION: 0.1.0
// PURPOSE: Arduino library for DCT532
//     URL: https://github.com/RobTillaart/DCT532



#include "DCT532.h"


DCT532::DCT532(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _error = DCT532_OK;
  _lastRead = 0;
  _pressure = 0;
  _temperature = 0;
  P = 0;
  T = 0;
}


bool DCT532::begin(float maxPressure, float minPressure)
{
  //  reset variables
  _error = DCT532_OK;
  _lastRead = 0;
  _pressure = 0;
  _temperature = 0;
  P = 0;
  T = 0;
  _minPressure = minPressure;
  _maxPressure = maxPressure;

  if (! isConnected())
  {
    return false;
  }
  return true;
}


bool DCT532::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t DCT532::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  READ SENSOR
//
int DCT532::readSensor()
{
  if (_wire->requestFrom(_address, (uint8_t)4) != 4)
  {
    _error = DCT532_REQUEST_ERROR;
    return _error;
  }
  _lastRead = millis();

  //  read the raw pressure
  P = _wire->read() << 8;
  P |= _wire->read();
  P &= 0x3FFF;  //  mask unused bits.
  //  read the raw temperature.
  T = _wire->read() << 8;
  T |= _wire->read();

  //  raw convert to float pressure
  //  (P - 1638)/13106 * (Pmax - Pmin) - Pmin
  _pressure = ((P - 1638) * (_maxPressure - _minPressure));
  _pressure *= 7.630093e-5;  //  MUL faster than DIV
  _pressure -= _minPressure;

  //  raw convert to float temperature
  //  ((T >> 5)/2048) * 165 - 40
  //  >> 5 = 1/32 = 0.03125
  //  1 / 2048 = 4.8828125e-4
  _temperature = T * (0.03125 * 4.8828125e-4 * 165.0) - 40.0;
  _error = DCT532_OK;
  return _error;
}


float DCT532::getPressure()
{
  return _pressure;
}


float DCT532::getTemperature()
{
  return _temperature;
}


uint32_t DCT532::lastRead()
{
  return _lastRead;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int DCT532::getLastError()
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

