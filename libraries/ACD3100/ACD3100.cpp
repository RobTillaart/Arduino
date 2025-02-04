//
//    FILE: ACD3100.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2024-10-29
// VERSION: 0.1.2
// PURPOSE: Arduino library for I2C ACD3100 CO2 sensor
//     URL: https://github.com/RobTillaart/ACD3100
//          http://www.aosong.com/products-220.html


#include "ACD3100.h"


ACD3100::ACD3100(TwoWire *wire)
{
  _wire = wire;
  _error = 0;
  _lastRead = 0;
  _concentration = 0;
  _temperature = 0;
  _preHeatStart = millis();
  _requestTime = 80;
  _requestStart = 0;
}


bool ACD3100::begin()
{
  //  reset variables
  _error = 0;
  _lastRead = 0;
  _concentration = 0;
  _temperature = 0;
  _requestTime = 80;
  _requestStart = 0;

  if (! isConnected())
  {
    return false;
  }
  return true;
}


bool ACD3100::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t ACD3100::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  READ CO2
//
bool ACD3100::preHeatDone()
{
  return preHeatMillisLeft() == 0;
}


uint32_t ACD3100::preHeatMillisLeft()
{
  uint32_t delta = millis() - _preHeatStart;
  if (delta >= 120000UL) return 0;
  return 120000UL - delta;
}


int ACD3100::requestSensor()
{
  uint8_t buf[2] = { 0x03, 0x00 };
  _requestStart = millis();
  return _command(buf, 2);
}


bool ACD3100::requestReady()
{
  if (_requestStart == 0)  //  no request pending.
  {
    return false;
  }
  return ((millis() - _requestStart) > _requestTime);
}


int ACD3100::readSensor()
{
  if (requestReady() == false)
  {
    return ACD3100_NOT_READY;
  }

  uint8_t buf[10];
  if (_request(buf, 9) != 0)
  {
    return ACD3100_REQUEST_ERROR;
  }
  _requestStart = 0;  //  set no request pending.

  //  CRC CHECK
  if (buf[2] != _crc8(&buf[0], 2))
  {
    //  Serial.println("CRC error 1");
    return ACD3100_CRC_ERROR;
  }
  if (buf[5] != _crc8(&buf[3], 2))
  {
    //  Serial.println("CRC error 2");
    return ACD3100_CRC_ERROR;

  }
  if (buf[8] != _crc8(&buf[6], 2))
  {
    //  Serial.println("CRC error 3");
    return ACD3100_CRC_ERROR;
  }

  //  DUMP
  // for (int i = 0; i < 9; i++)
  // {
    // if (buf[i] < 16) Serial.print("0");
    // Serial.print(buf[i], HEX);
    // Serial.print(" ");
  // }
  // Serial.println();

  _concentration   = buf[0];
  _concentration <<= 8;
  _concentration  += buf[1];
  _concentration <<= 8;
  _concentration  += buf[3];
  _concentration <<= 8;
  _concentration  += buf[4];

  _temperature = buf[6] * 256 + buf[7];
  _lastRead = millis();

  return ACD3100_OK;
}


uint32_t ACD3100::getCO2Concentration()
{
  return _concentration;
}


uint16_t ACD3100::getTemperature()
{
  return _temperature;
}


uint32_t ACD3100::lastRead()
{
  return _lastRead;
}


void ACD3100::setRequestTime(uint8_t milliseconds)
{
  _requestTime = milliseconds;
}


uint8_t ACD3100::getRequestTime()
{
  return _requestTime;
}


/////////////////////////////////////////////
//
//  CALIBRATION
//
bool ACD3100::setManualCalibration(uint16_t value)
{
  if ((value < 400) || (value > 5000)) return false;
  uint8_t buf[5] = { 0x52, 0x04, 0x00, 0x00, 0x00 };
  buf[3] = value & 0xFF;
  buf[2] = value >> 8;
  buf[4] = _crc8(&buf[2], 2);
  _command(buf, 5);
  return true;
}


uint16_t ACD3100::readManualCalibration()
{
  uint8_t buf[3] = { 0x52, 0x04, 0x00 };
  _command(buf, 2);
  _request(buf, 3);
  // if (buf[2] != _crc8(&buf[0], 2))
  // {
    // Serial.print(__FUNCTION__);
    // Serial.println(": CRC error");
  // }
  uint16_t value = buf[0] * 256 + buf[1];
  return value;
}


/////////////////////////////////////////////
//
//  MISC
//
void ACD3100::factoryReset()
{
  uint8_t buf[3] = { 0x52, 0x02, 0x00};
  _command(buf, 3);
}


bool ACD3100::readFactorySet()
{
  uint8_t buf[3] = { 0x52, 0x02, 0x00 };
  _command(buf, 2);
  _request(buf, 3);
  // if (buf[2] != _crc8(&buf[0], 2))
  // {
    // Serial.print(__FUNCTION__);
    // Serial.println(": CRC error");
  // }
  return ((buf[0] == 0) && (buf[1] == 0x01));
}


void ACD3100::readFirmwareVersion(char * arr)
{
  uint8_t buf[2] = { 0xD1, 0x00 };
  _command(buf, 2);
  _request((uint8_t *) arr, 10);
  arr[10] = '\0';
}


void ACD3100::readSensorCode(char * arr)
{
  uint8_t buf[2] = { 0xD2, 0x01 };
  _command(buf, 2);
  _request((uint8_t *) arr, 10);
  arr[10] = '\0';
}


/////////////////////////////////////////////
//
//  DEBUG
//
int ACD3100::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
int ACD3100::_command(uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
  return _error;
}


int ACD3100::_request(uint8_t * arr, uint8_t size)
{
  uint8_t bytes = _wire->requestFrom(_address, size);
  if (bytes == 0)
  {
    _error = -1;
    return _error;
  }
  if (bytes < size)
  {
    _error = -2;
    return _error;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    arr[i] = _wire->read();
  }
  _error = 0;
  return _error;
}


uint8_t ACD3100::_crc8(uint8_t * arr, uint8_t size)
{
  uint8_t crc = 0xFF;
  for (uint8_t b = 0; b < size; b++)
  {
    crc ^= arr[b];
    for (uint8_t bit = 0x80; bit; bit >>= 1)
    {
      if (crc & 0x80)
      {
        crc <<= 1;
        crc ^= 0x31;
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  return crc;
}


//  -- END OF FILE --

