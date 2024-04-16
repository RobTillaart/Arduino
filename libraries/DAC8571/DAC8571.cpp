//
//    FILE: DAC8571.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-04-16
// VERSION: 0.1.0
// PURPOSE: Arduino library for DAC8571 I2C.
//     URL: https://github.com/RobTillaart/DAC8571


#include "DAC8571.h"


//  INTERNAL USE ONLY
#define DAC8571_DAC_FLAG                0x40
#define DAC8571_INCR_FLAG               0x04


DAC8571::DAC8571(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
  _dac     = 0;
  _error = DAC8571_OK;
  setWriteMode(DAC8571_MODE_NORMAL);
}


bool DAC8571::begin(uint16_t val)
{
  if ((_address != 0x4C) && (_address != 0x4E))
  {
    _error = DAC8571_ADDRESS_ERROR;
    return false;
  }
  if (!isConnected()) return false;

  return write(val);
}


bool DAC8571::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();  //  default == 0 == DAC8571_OK
  return (_error == DAC8571_OK);
}


uint8_t DAC8571::getAddress()
{
  return _address;
}


//////////////////////////////////////////////////////////
//
//  DAC PART
//
bool DAC8571::write(uint16_t value)
{
  uint8_t lowByte = value & 0xFF;
  uint8_t highByte = value >> 8;

  _wire->beginTransmission(_address);
  _wire->write(_control);
  _wire->write(highByte);
  _wire->write(lowByte);
  _error = _wire->endTransmission();

  if (_error != 0)
  {
    _error = DAC8571_I2C_ERROR;
    return false;
  }
  _error = DAC8571_OK;
  _dac = value;
  return true;
}


uint16_t DAC8571::lastWrite()
{
  return _dac;
}


uint16_t DAC8571::read()
{
  uint8_t highByte = 0;
  uint8_t lowByte  = 0;
  uint8_t control  = 0;

  uint8_t n = _wire->requestFrom(_address, uint8_t(3));
  if (n == 3)
  {
    highByte = _wire->read();
    lowByte  = _wire->read();
    control  = _wire->read();  //  not used.
    _error = DAC8571_OK;
  }
  else
  {
    _error = DAC8571_I2C_ERROR;
    return 0;
  }
  //  keep compiler happy.
  if (control == 0) _error = DAC8571_OK;
  _error = DAC8571_OK;
  uint16_t value = highByte * 256 + lowByte;
  return value;
}


bool DAC8571::write(uint16_t * arr, uint8_t length)
{
  if (length > 14)
  {
    _error = DAC8571_BUFFER_ERROR;
    return false;
  }
  _wire->beginTransmission(_address);
  _wire->write(_control);
  for (int i = 0; i < length; i++)
  {
    uint8_t lowByte = arr[i] & 0xFF;
    uint8_t highByte = arr[i] >> 8;
    _wire->write(highByte);
    _wire->write(lowByte);
  }
  _error = _wire->endTransmission();

  if (_error != 0)
  {
    _error = DAC8571_I2C_ERROR;
    return false;
  }
  _error = DAC8571_OK;
  _dac = arr[length - 1];
  return true;
}


//////////////////////////////////////////////////////////
//
//  MODE PART
//
void DAC8571::setWriteMode(uint8_t mode)
{
  //  3 and 4 not supported.
  if (mode > DAC8571_MODE_WRITE_CACHE)
  {
    mode = DAC8571_MODE_NORMAL;
  }
  _control = (mode << 4);
}


uint8_t DAC8571::getWriteMode()
{
  uint8_t mode = (_control >> 4) & 0x03;
  return mode;
}


//////////////////////////////////////////////////////////
//
//  POWER DOWN PART
//
void DAC8571::powerDown(uint8_t pMode)
{
  //  overwrite parameter for now.
  //  table 6, page 22.
  pMode = 0;
  _control = 0x11;
  write(0);
}


void DAC8571::wakeUp(uint16_t value)
{
  _control = 0x10;
  write(value);
}


//////////////////////////////////////////////////////////
//
//  ERROR HANDLING
//
int DAC8571::lastError()
{
  int e = _error;
  _error = DAC8571_OK;
  return e;
}


//  -- END OF FILE --

