//
//    FILE: I2C_ASDX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
// PURPOSE: I2C_asdx library for Arduino.
//     URL: https://github.com/RobTillaart/I2C_ASDX
//
//  HISTORY:
//  0.1.0   2013-11-14  initial version
//  0.2.0   2020-03-18  refactor
//  0.2.1   2020-07-04  add getBar(), getMilliBar(), getPSI()
//  0.2.2   2020-12-29  add Arduino-CI + unit test (minimal), keywords update.
//  0.2.3   2021-06-06  add different units to read pressure
//  0.3.0   2021-06-07  add multiWire interface
//  0.3.1   2021-12-19  update library.json, license, minor edits


#include "I2C_ASDX.h"


I2C_ASDX::I2C_ASDX(uint8_t address, uint8_t psi, TwoWire *wire)
{
  reset();
  _address     = address;
  _wire        = wire;
  _maxPressure = 0;

  if ((psi == 100) || (psi == 60) || (psi == 30) ||
      (psi ==  15) || (psi == 05) || (psi == 01))
  {
    _maxPressure = psi * PSI2MILLIBAR;
  }
  _state = I2C_ASDX_INIT;
}


#if defined (ESP8266) || defined(ESP32)
bool I2C_ASDX::begin(uint8_t sda, uint8_t scl)
{
  reset();
  _wire = &Wire;
  _wire->begin(sda, scl);
  if (! isConnected())
  {
    _state = I2C_ASDX_CONNECT_ERROR;
    return false;
  }
  _state = I2C_ASDX_OK;
  return true;
}
#endif


bool I2C_ASDX::begin()
{
  reset();
  _wire->begin();
  if (! isConnected())
  {
    _state = I2C_ASDX_CONNECT_ERROR;
    return false;
  }
  _state = I2C_ASDX_OK;
  return true;
}


void I2C_ASDX::reset()
{
  _errorCount = 0;
  _lastRead = 0;
  _pressure = 0;
}


bool I2C_ASDX::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


int I2C_ASDX::read()
{
  _wire->requestFrom(_address, (uint8_t)2);
  if (_wire->available() != 2)
  {
    _errorCount++;
    _state = I2C_ASDX_READ_ERROR;
    return _state;
  }
  int count = _wire->read() * 256;  // hi byte
  count    += _wire->read();        // lo byte
  if (count & 0xC000)
  {
    _errorCount++;
    _state = I2C_ASDX_C000_ERROR;  // no documentation, bits may not be set?
    return _state;
  }

  //  _pressure = map(count, 1638, 14746, 0, _maxPressure);
  //  _pressure = (count - 1638) * (_maxPressure - 0) / ( 14746 - 1638);
  _pressure = (count - 1638) * _maxPressure * 7.62892889838E-5;
  _lastRead = millis();

  _state = I2C_ASDX_OK;
  return _state;
}


// -- END OF FILE --

