//
//    FILE: MTP40F.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-07-25
// VERSION: 0.1.0
// PURPOSE: Arduino library for MTP40F CO2 sensor
//     URL: https://github.com/RobTillaart/MTP40F


#include "MTP40F.h"

//  debug flag, development.
//  #define MTP40F_DEBUG    1


MTP40F::MTP40F(Stream * str)
{
  _ser = str;
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

  //  max read freq 1x per 4 seconds  //  TODO CHECK.
  if (millis() - _lastRead < 4000) return _airPressureReference;  //  last value
  _lastRead = millis();

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
  if ((apr < 700) || (apr > 1100)) return false;  //  TODO CHECK

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

  //  max read freq 1x per 4 seconds
  if (millis() - _lastRead < 4000) return _gasLevel;  //  last value
  _lastRead = millis();

  uint8_t cmd[9] = { 0x42, 0x4D, 0xA0, 0x00, 0x03, 0x00, 0x00, 0x01, 0x32 };
  if (request(cmd, 9, 14) )
  {
    //  TODO  optimize shift.
    _gasLevel =  _buffer[7] * (256L * 256L * 256L);
    _gasLevel += _buffer[8] * (256L * 256L);
    _gasLevel += _buffer[9] * (256L);
    _gasLevel += _buffer[10];

    uint8_t status = _buffer[11];
    if (status == 0x00) return _gasLevel;
  }

  _lastError = MTP40F_INVALID_GAS_LEVEL;
  if (_suppressError) return _gasLevel;
  return _lastError;
}


bool MTP40F::setSinglePointCorrection(uint32_t spc)
{
  if ((spc < 400) || (spc > 2000)) return false;  //  TODO CHECK

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
  return 0x02;  //  TODO define error constant
}


uint16_t MTP40F::getSelfCalibrationHours()
{
  uint8_t cmd[9] = { 0x42, 0x4D, 0xA0, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 };
  if (request(cmd, 9, 11) )
  {
    uint16_t hrs = _buffer[7] * 256 + _buffer[8];
    return hrs;
  }
  return 0xFFFF;  //  TODO define error constant
}


bool MTP40F::setSelfCalibrationHours(uint16_t hrs)
{
  if ((hrs < 24) || (hrs > 720)) return false;
  uint8_t cmd[11] = { 0x42, 0x4D, 0xA0, 0x00, 0x09, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00 };
  cmd[7] = hrs / 256;
  cmd[8] = hrs & 0xFF;
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
//  PRIVATE
//
bool MTP40F::request(uint8_t *data, uint8_t commandLength, uint8_t answerLength)
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
  while (i < answerLength)
  {
    if (millis() - start > _timeout) return false;
    if (_ser->available())
    {
      _buffer[i++] = _ser->read();
    }
    yield();  //  because baud rate is low!
  }
  return true;
}


uint16_t MTP40F::CRC(uint8_t *data, uint16_t len)
{
  uint16_t sum = 0;
  for (uint16_t i= 0; i < len; i++)
  {
    sum += *data++;
  }
  return sum;
}


//  -- END OF FILE --

