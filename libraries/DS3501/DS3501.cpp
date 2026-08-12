//
//    FILE: DS3501.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-08-12
// VERSION: 0.1.0
// PURPOSE: Arduino library for the DS3501, I2C, 7-bit, non-volatile, digital potentiometer. Temperature control.
//     URL: https://github.com/RobTillaart/DS3501



#include "DS3501.h"


//  REGISTERS
//  datasheet page 8
//  default mode registers
const uint8_t DS3501_WIPER_REG       = 0x00;  //  NVRAM
const uint8_t DS3501_CONTROL0_REG    = 0x02;  //
const uint8_t DS3501_CONTROL1_REG    = 0x03;  //  NVRAM (LUT mode)
const uint8_t DS3501_CONTROL2_REG    = 0x0A;  //
//  LUT mode extra registers
const uint8_t DS3501_LUTAR_REG       = 0x08;  //
const uint8_t DS3501_WIPER2_REG      = 0x09;  //  read wiper in LUT mode.
const uint8_t DS3501_TEMPERATURE_REG = 0x0C;  //  Read Only
const uint8_t DS3501_VOLTAGE_REG     = 0x0E;  //  Read Only
const uint8_t DS3501_LUT_BASE_REG    = 0x80;  //  NVRAM


DS3501::DS3501(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  _error = DS3501_OK;
}

bool DS3501::begin()
{
  //  reset variables
  _error = DS3501_OK;
  if (! isConnected())
  {
    _error = DS3501_CONNECT_ERROR;
    return false;
  }
  return true;
}

bool DS3501::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t DS3501::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  NVRAM MODE
//
bool DS3501::enableNVRAM(bool nvram)
{
  _write(DS3501_CONTROL0_REG, nvram ? 0x80 : 0x00);
  _useNVRAM = nvram;
  return _error == DS3501_OK;
}

bool DS3501::isEnabledNVRAM()
{
  return 0x80 == _read(DS3501_CONTROL0_REG);
}


/////////////////////////////////////////////
//
//  SET VALUE
//
bool DS3501::setValue(uint8_t value)
{
  if (value > 127)
  {
    _error = DS3501_VALUE_ERROR;
    return false;
  }
  _error = DS3501_OK;
  //  force writes to NVRAM
  //  force write if no cache is used.
  //  force write if cached value is not new value
  if ((_useCache == false) || (value != _lastValue) || (_useNVRAM))
  {
    _write(DS3501_WIPER_REG, value);
    if (_error != DS3501_OK)
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
  return _error == DS3501_OK;
}

int DS3501::getValue()
{
  //  TODO depends on LUT mode?

  //  test value is written
  if (_useCache) return _lastValue;
  return _read(DS3501_WIPER_REG);
}

bool DS3501::setOhm(uint16_t ohm)
{
  if (ohm > DS3501_MAX_OHM)
  {
    _error = DS3501_VALUE_ERROR;
    return false;
  }
  //  no rounding, truncating
  uint8_t value = (ohm * 127UL) / DS3501_MAX_OHM;
  return setValue(value);
}

int16_t DS3501::getOhm()
{
  uint8_t value = getValue();
  if (_error != DS3501_OK)
  {
    return -1;
  }
  return (value * DS3501_MAX_OHM) / 127;
}


/////////////////////////////////////////////
//
//  STATUS
//
//  datasheet page 7
int16_t DS3501::getTemperature()
{
  int16_t temp = _read(DS3501_TEMPERATURE_REG);
  if (temp > 127) temp -= 256;
  return temp;
}

//  datasheet page 3, 7  LSB = 25.6 mV
int16_t DS3501::getMilliVolt()
{
  int16_t millivolt = _read(DS3501_VOLTAGE_REG);
  return (millivolt * 256 + 5) / 10;
}


/////////////////////////////////////////////
//
//  DEFAULT / LUT MODE
//
void DS3501::setDefaultMode()
{
  _write(DS3501_CONTROL1_REG, DS3501_DEFAULT_MODE);
}

void DS3501::setLUTMode()
{
  _write(DS3501_CONTROL1_REG, DS3501_LUT_MODE);
}

void DS3501::setLUTADDERMode()
{
  _write(DS3501_CONTROL1_REG, DS3501_LUT_ADDER_MODE);
}

int DS3501::getMode()
{
  uint8_t raw = _read(DS3501_CONTROL1_REG);
  if (_error != DS3501_OK) return -1;
  return raw & 0x03;
}


/////////////////////////////////////////////
//
//  LUT TABLE
//
bool DS3501::setLUTtable(uint8_t index, uint8_t value)
{
  if (index > 35)
  {
    _error = DS3501_LUTINDEX_ERROR;
    return false;
  }
  _write(DS3501_LUT_BASE_REG + index, value);
  return (_error == DS3501_OK);
}

int DS3501::getLUTtable(uint8_t index)
{
  if (index > 35)
  {
    _error = DS3501_LUTINDEX_ERROR;
    return 0;
  }
  uint8_t value = _read(DS3501_LUT_BASE_REG + index);
  if (_error != DS3501_OK)
  {
    return -1;
  }
  return value;
}

int DS3501::getLUTAR()
{
  uint8_t raw = _read(DS3501_LUTAR_REG);
  if (_error != DS3501_OK)
  {
    return -1;
  }
  return raw;
}

int DS3501::getWIPER()
{
  uint8_t raw = _read(DS3501_WIPER2_REG);
  if (_error != DS3501_OK)
  {
    return -1;
  }
  return raw;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int DS3501::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
int DS3501::_write(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _wire->write(value);
  _error = _wire->endTransmission();
  return _error;
}

uint8_t DS3501::_read(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error != 0)
  {
    _error = DS3501_READ_ERROR;
    return _error;
  }
  return _error;
  uint8_t bytes = _wire->requestFrom(_address, (uint8_t)1);
  if (bytes != 1)
  {
    _error = DS3501_REQUEST_ERROR;
    return _error;
  }
  uint8_t value = _wire->read();
  _error = DS3501_OK;
  return value;
}


//  -- END OF FILE --

