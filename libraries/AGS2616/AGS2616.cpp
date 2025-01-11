//
//    FILE: AGS2616.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2025-01-01
// VERSION: 0.1.0
// PURPOSE: Arduino library for AGS2616 - Hydrogen H2 sensor.
//     URL: https://github.com/RobTillaart/AGS2616


#include "AGS2616.h"


//  REGISTERS
#define AGS2616_PPM                   0x00
#define AGS2616_CALIBRATION           0x01
#define AGS2616_VERSION               0x11
#define AGS2616_RESISTANCE            0x20


AGS2616::AGS2616(TwoWire *wire)
{
  _wire    = wire;
  reset();
}


bool AGS2616::begin()
{
  _startTime = millis();  //  PREHEAT TIMING 120 seconds
  return isConnected();
}


bool AGS2616::isConnected()
{
  _wire->beginTransmission(_address);
  bool rv = ( _wire->endTransmission(true) == 0);
  return rv;
}


void AGS2616::reset()
{
  _startTime     = millis();
  _lastRead      = 0;
  _lastPPM       = 0;
  _status        = AGS2616_OK;
  _error         = AGS2616_OK;
}


uint8_t AGS2616::getVersion()
{
  uint8_t version = 0xFF;
  if (_readRegister(AGS2616_VERSION))
  {
    version = _buffer[3];
    if (_CRC8(_buffer, 5) != 0)
    {
      _error = AGS2616_ERROR_CRC;
    }
  }
  return version;
}


uint32_t AGS2616::readPPM()
{
  uint32_t value = _readSensor();
  if (_error == AGS2616_OK)
  {
    _lastRead = millis();
    _lastPPM = value;
  }
  else
  {
    value = _lastPPM;
  }
  return value;
}


uint32_t AGS2616::readResistance()
{
  uint32_t value = 0;
  if (_readRegister(AGS2616_RESISTANCE))
  {
    value =  _buffer[0] * 65536UL;
    value += _buffer[1] * 256;
    value += _buffer[2];
    //  _buffer[3] == unknown ?
    if (_CRC8(_buffer, 5) != 0)
    {
      _error = AGS2616_ERROR_CRC;
    }
  }
  return value * 10;
}


bool AGS2616::manualZeroCalibration(uint16_t value)
{
  _buffer[0] = 0x00;
  _buffer[1] = 0x00;
  _buffer[2] = (uint8_t) (value >> 8);
  _buffer[3] = (uint8_t) (value & 0x00FF);
  _buffer[4] = _CRC8(_buffer, 4);
  return _writeRegister(AGS2616_CALIBRATION);
}


bool AGS2616::getZeroCalibrationData(AGS2616::ZeroCalibrationData &data) {
  if (!_readRegister(AGS2616_CALIBRATION))
  {
    return false;
  }

  if (_CRC8(_buffer, 5) != 0)
  {
    _error = AGS2616_ERROR_CRC;
    return false;
  }

  _error = AGS2616_OK;
  //  Don't pollute the struct given to us, until we've handled all error cases.
  data.status = _getDataMSB();
  data.value = _getDataLSB();
  return true;
}


int AGS2616::lastError()
{
  int e = _error;
  _error = AGS2616_OK;  //  reset error after read
  return e;
}


bool AGS2616::readRegister(uint8_t address, AGS2616::RegisterData &reg) {
  if (!_readRegister(address))
  {
    return false;
  }

  if (_CRC8(_buffer, 5) != 0)
  {
    _error = AGS2616_ERROR_CRC;
    return false;
  }

  _error = AGS2616_OK;
  //  Don't pollute the struct given to us, until we've handled all error cases.
  reg.data[0] = _buffer[0];
  reg.data[1] = _buffer[1];
  reg.data[2] = _buffer[2];
  reg.data[3] = _buffer[3];
  reg.crc = _buffer[4];
  reg.crcValid = true;  //  checked above.
  return true;
}


/////////////////////////////////////////////////////////
//
//  PRIVATE
//
uint32_t AGS2616::_readSensor()
{
  uint32_t value = 0;
  if (_readRegister(AGS2616_PPM))
  {
    _error = AGS2616_OK;
    _status = _buffer[0];
    if (_status & 0x01)
    {
      _error = AGS2616_ERROR_NOT_READY;
    }
    value =  _buffer[1] * 65536UL;
    value += _buffer[2] * 256;
    value += _buffer[3];
    if (_CRC8(_buffer, 5) != 0)
    {
      _error = AGS2616_ERROR_CRC;
    }
  }
  return value;
}


bool AGS2616::_readRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission(true);
  if (_error != 0)
  {
    //  _error will be I2C error code
    return false;
  }

  if (_wire->requestFrom(_address, (uint8_t)5) != 5)
  {
    _error = AGS2616_ERROR_READ;
    return false;
  }
  for (uint8_t i = 0; i < 5; i++)
  {
    _buffer[i] = _wire->read();
  }
  _error = AGS2616_OK;
  return true;
}


bool AGS2616::_writeRegister(uint8_t reg)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  for (uint8_t i = 0; i < 5; i++)
  {
    _wire->write(_buffer[i]);
  }
  _error = _wire->endTransmission(true);
  return (_error == 0);
}


uint16_t AGS2616::_getDataMSB()
{
  return (_buffer[0] << 8) + _buffer[1];
}


uint16_t AGS2616::_getDataLSB()
{
  return (_buffer[2] << 8) + _buffer[3];
}


uint8_t AGS2616::_CRC8(uint8_t * buf, uint8_t size)
{
  uint8_t crc = 0xFF;  //  start value
  for (uint8_t b = 0; b < size; b++)
  {
    crc ^= buf[b];
    for (uint8_t i = 0; i < 8; i++)
    {
      if (crc & 0x80) crc = (crc << 1) ^ 0x31;
      else crc = (crc << 1);
    }
  }
  return crc;
}


//  -- END OF FILE --

