//
//    FILE: I2C_ASDX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
// PURPOSE: I2C_asdx library for Arduino.
//     URL: https://github.com/RobTillaart/I2C_ASDX
//
// HISTORY: see changelog.md


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

