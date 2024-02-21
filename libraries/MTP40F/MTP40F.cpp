//
//    FILE: MTP40F.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-25
// VERSION: 0.2.0
// PURPOSE: Arduino library for MTP40F CO2 sensor
//     URL: https://github.com/RobTillaart/MTP40F


#include "MTP40F.h"

//  debug flag, development.
//  #define MTP40F_DEBUG    1


MTP40F::MTP40F(Stream * stream)
{
  _ser = stream;
  _buffer[0] = '\0';
  _type = 5;
}


bool MTP40F::begin()
{
  _timeout       = 100;
  _lastRead      = 0;
  _airPressureReference = 0;
  _gasLevel      = 0;
  _suppressError = false;
  _lastError     = MTP40F_OK;
  return true;
}


int MTP40F::getAirPressureReference()
{
  _lastError = MTP40F_OK;

  uint8_t cmd[9] = { 0x42, 0x4D, 0xA0, 0x00, 0x02, 0x00, 0x00, 0x01, 0x31 };
  if (request(cmd, 9, 11))
  {
    _airPressureReference = _buffer[7] * 256 + _buffer[8];
    return _airPressureReference;
  }

  _lastError = MTP40F_INVALID_AIR_PRESSURE;
  if (_suppressError) return _airPressureReference;
  return _lastError;
}


bool MTP40F::setAirPressureReference(int apr)
{
  if ((apr < 700) || (apr > 1100))  //  page 5 datasheet
  {
    return false;
  }

  uint8_t cmd[11] = { 0x42, 0x4D, 0xA0, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00 };
  cmd[7] = apr / 256;
  cmd[8] = apr % 256;
  if (request(cmd, 11, 11) )
  {
    return true;
  }
  return false;
}


uint32_t MTP40F::getGasConcentration()
{
  _lastError = MTP40F_OK;

  //  max read freq 1x per 2 seconds
  //  datasheet measurement interval = 2s
  if (millis() - _lastRead < 2000)
  {
    return _gasLevel;  //  last value
  }
  _lastRead = millis();

  uint8_t cmd[9] = { 0x42, 0x4D, 0xA0, 0x00, 0x03, 0x00, 0x00, 0x01, 0x32 };
  if (request(cmd, 9, 14) )
  {
    uint8_t status = _buffer[11];
    if (status == 0x00) 
    {
      _gasLevel =  _buffer[7];
      _gasLevel <<= 8;
      _gasLevel |= _buffer[8];
      _gasLevel <<= 8;
      _gasLevel |= _buffer[9];
      _gasLevel <<= 8;
      _gasLevel += _buffer[10];
      return _gasLevel;
    }
    _lastError = MTP40F_INVALID_GAS_LEVEL;
    if (_suppressError) return _gasLevel;  //  last level
    return _lastError;
  }

  _lastError = MTP40F_REQUEST_FAILED;
  if (_suppressError) return _gasLevel;  //  last level
  return _lastError;
}


bool MTP40F::setSinglePointCorrection(uint32_t spc)
{
  if ((spc < 400) || (spc > 2000))  //  datasheet unclear 0x2000???
  {
    return false;
  }

  uint8_t cmd[13] = { 0x42, 0x4D, 0xA0, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  cmd[7]  = 0;
  cmd[8]  = 0;
  cmd[9]  = spc / 256;
  cmd[10] = spc % 256;
  if (request(cmd, 13, 10) )
  {
    if (_buffer[7] ) return true;
  }
  return false;
}


bool MTP40F::getSinglePointCorrectionReady()
{
  uint8_t cmd[9] = { 0x42, 0x4D, 0xA0, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00 };
  if (request(cmd, 9, 10) )
  {
    if (_buffer[8] == 0) return true;
  }
  return false;
}


bool MTP40F::openSelfCalibration()
{
  uint8_t cmd[10] = { 0x42, 0x4D, 0xA0, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00 };
  if (request(cmd, 10, 9) )
  {
    return true;
  }
  return false;
}


bool MTP40F::closeSelfCalibration()
{
  uint8_t cmd[10] = { 0x42, 0x4D, 0xA0, 0x00, 0x06, 0x00, 0x01, 0xFF, 0x00, 0x00 };
  if (request(cmd, 10, 9) )
  {
    return true;
  }
  return false;
}


uint8_t MTP40F::getSelfCalibrationStatus()
{
  uint8_t cmd[9] = { 0x42, 0x4D, 0xA0, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00 };
  if (request(cmd, 9, 10) )
  {
    return _buffer[7];   //  0x00 or 0xFF
  }
  _lastError = MTP40F_REQUEST_FAILED;
  return _lastError;
}


uint16_t MTP40F::getSelfCalibrationHours()
{
  uint8_t cmd[9] = { 0x42, 0x4D, 0xA0, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 };
  if (request(cmd, 9, 11) )
  {
    uint16_t hours = _buffer[7] * 256 + _buffer[8];
    return hours;
  }
  _lastError = MTP40F_REQUEST_FAILED;
  return _lastError;
}


bool MTP40F::setSelfCalibrationHours(uint16_t hours)
{
  if ((hours < 24) || (hours > 720))
  {
    return false;
  }
  uint8_t cmd[11] = { 0x42, 0x4D, 0xA0, 0x00, 0x09, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00 };
  cmd[7] = hours / 256;
  cmd[8] = hours & 0xFF;
  if (request(cmd, 11, 10) )
  {
    return (_buffer[7] == 0x00);
  }
  return false;
}


int MTP40F::lastError()
{
  int e = _lastError;
  _lastError = MTP40F_OK;
  return e;
}


//////////////////////////////////////////////////////////////////////
//
//  PROTECTED
//
bool MTP40F::request(uint8_t *data, uint8_t commandLength, uint8_t responseLength)
{
  //  calculate CRC of command
  uint16_t crc = CRC(data, commandLength - 2);
  data[commandLength - 2] = crc / 256;
  data[commandLength - 1] = crc & 0xFF;
  while (commandLength--)
  {
#ifdef MTP40F_DEBUG
    if (*data < 0x10) Serial.print(0);
    Serial.print(*data++, HEX);
    Serial.print(" ");
#else
    _ser->write(*data++);
#endif
     yield();   //  because baud rate is low!
  }

  uint32_t start = millis();
  uint8_t i = 0;
  while (i < responseLength)
  {
    if (millis() - start > _timeout) return false;
    if (_ser->available())
    {
      _buffer[i++] = _ser->read();
    }
    yield();  //  because baud rate is low!
  }
  if (responseLength > 2)
  {
    uint16_t expected_crc = (_buffer[responseLength - 2] << 8) | _buffer[responseLength - 1];
    uint16_t calc_crc = CRC(_buffer, responseLength - 2);
    if (calc_crc != expected_crc)
    {
      _lastError = MTP40F_INVALID_CRC;
      return false;
    }
    return calc_crc == expected_crc;
  }

  return true;
}


uint16_t MTP40F::CRC(uint8_t *data, uint16_t length)
{
  uint16_t sum = 0;
  for (uint16_t i= 0; i < length; i++)
  {
    sum += *data++;
  }
  return sum;
}


//  -- END OF FILE --

