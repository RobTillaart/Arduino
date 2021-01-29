//
//    FILE: I2C_ASDX.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: I2C_asdx library for Arduino.
//     URL: https://github.com/RobTillaart/I2C_ASDX
//
//  HISTORY:
//  0.1.0   2013-11-14  initial version
//  0.2.0   2020-03-18  refactor
//  0.2.1   2020-07-04  add getBar(), getMilliBar(), getPSI()
//  0.2.2   2020-12-29  add arduiino-ci + unit test (minimal), keywords update.

#include "I2C_ASDX.h"

I2C_ASDX::I2C_ASDX(uint8_t address, uint8_t psi)
{
  _address = address;
  _maxPressure = 0;
  if ((psi == 100) || (psi == 60) || (psi == 30) ||
      (psi ==  15) || (psi == 05) || (psi == 01))
  {
    _maxPressure = psi * PSI2MILLIBAR;
  }
  reset();
}

#if defined (ESP8266) || defined(ESP32)
void I2C_ASDX::begin(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);
  reset();
}
#endif

void I2C_ASDX::begin()
{
  Wire.begin();
  reset();
}

void I2C_ASDX::reset()
{
  _state = I2C_ASDX_INIT;
  _errorCount = 0;
  _lastRead = 0;
  _pressure = 0;
}

bool I2C_ASDX::available()
{
  Wire.beginTransmission(_address);
  return (Wire.endTransmission() == 0);
}

int I2C_ASDX::read()
{
  Wire.requestFrom(_address, (uint8_t)2);
  if (Wire.available() != 2)
  {
    _errorCount++;
    _state = I2C_ASDX_READ_ERROR;
    return _state;
  }
  int count = Wire.read() * 256;  // hi byte
  count    += Wire.read();        // lo byte
  if (count & 0xC000)
  {
    _errorCount++;
    _state = I2C_ASDX_C000_ERROR;  // no documentation, bits may not be set?
    return _state;
  }
  // _pressure = map(count, 1638, 14746, 0, _maxPressure);
  // _pressure = (count - 1638) * (_maxPressure - 0) / ( 14746 - 1638);
  _pressure = (count - 1638) * _maxPressure * 7.62892889838E-5;
  _state = I2C_ASDX_OK;
  _lastRead = millis();
  return _state;
}

// -- END OF FILE --
