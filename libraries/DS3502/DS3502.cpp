//
//    FILE: DS3502.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-08-10
// VERSION: 0.1.0
// PURPOSE: Arduino library for the DS3502, I2C, 7-bit, non-volatile, digital potentiometer.
//     URL: https://github.com/RobTillaart/DS3502



#include "DS3502.h"


//  REGISTERS
const uint8_t DS3502_WIPER_REG = 0x00;
const uint8_t DS3502_CONTROL_REG = 0x02;


DS3502::DS3502(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _error = DS3502_OK;
}

bool DS3502::begin()
{
  //  reset variables
  _error = DS3502_OK;
  if (! isConnected())
  {
    _error = DS3502_CONNECT_ERROR;
    return false;
  }
  return true;
}

bool DS3502::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t DS3502::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  MODE
//
bool DS3502::enableNVRAM(bool nvram)
{
  _write(DS3502_CONTROL_REG, nvram ? 0x80 : 0x00);
  _useNVRAM = nvram;
  return _error == DS3502_OK;
}

bool DS3502::isEnabledNVRAM()
{
  return 0x80 == _read(DS3502_CONTROL_REG);
}


/////////////////////////////////////////////
//
//  SET VALUE
//
bool DS3502::setValue(uint8_t value)
{
  if (value > 127)
  {
    _error = DS3502_VALUE_ERROR;
    return false;
  }
  _error = DS3502_OK;
  //  force writes to NVRAM
  //  force write if no cache is used.
  //  force write if cached value is not new value
  if ((_useCache == false) || (value != _lastValue) || (_useNVRAM))
  {
    _write(DS3502_WIPER_REG, value);
    if (_error != DS3502_OK)
    {
      return false;
    }
    //  keep cache up to date
    _lastValue = value;
  }

  //  disable NVRAM after successful write to NVRAM.
  if (_useNVRAM)
  {
    enableNVRAM(false);
  }
  return _error == DS3502_OK;
}

uint8_t DS3502::getValue()
{
  //  test value is written
  if (_useCache) return _lastValue;
  return _read(DS3502_WIPER_REG);
}

bool DS3502::setOhm(uint16_t ohm)
{
  if (ohm > DS3502_MAX_OHM)
  {
    _error = DS3502_VALUE_ERROR;
    return false;
  }
  //  no rounding, truncating
  uint8_t value = (ohm * 127UL) / DS3502_MAX_OHM;
  return setValue(value);
}

uint16_t DS3502::getOhm()
{
  uint8_t value = getValue();
  if (_error != DS3502_OK)
  {
    return 0xFFFF;
  }
  return (value * DS3502_MAX_OHM) / 127;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int DS3502::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//

int DS3502::_write(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return _error;
}


uint8_t DS3502::_read(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = DS3502_READ_ERROR;
    return _error;
  }
  return _error;
  uint8_t bytes = _wire->requestFrom(_address, (uint8_t)1);
  if (bytes != 1)
  {
    _error = DS3502_REQUEST_ERROR;
    return _error;
  }
  uint8_t value = _wire->read();
  _error = DS3502_OK;
  return value;
}


//  -- END OF FILE --

