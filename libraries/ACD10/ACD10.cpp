//
//    FILE: ACD10.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-25
// VERSION: 0.2.0
// PURPOSE: Arduino library for for I2C ACD10 CO2 sensor
//     URL: https://github.com/RobTillaart/ACD10
//          http://www.aosong.com/en/products-77.html


#include "ACD10.h"


ACD10::ACD10(TwoWire *wire)
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


bool ACD10::begin()
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


bool ACD10::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t ACD10::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  READ CO2
//
bool ACD10::preHeatDone()
{
  return preHeatMillisLeft() == 0;
}


uint32_t ACD10::preHeatMillisLeft()
{
  uint32_t delta = millis() - _preHeatStart;
  if (delta >= 120000UL) return 0;
  return 120000UL - delta;
}


int ACD10::requestSensor()
{
  uint8_t buf[2] = { 0x03, 0x00 };
  _requestStart = millis();
  return _command(buf, 2);
}


bool ACD10::requestReady()
{
  if (_requestStart == 0)  //  no request pending.
  {
    return false;
  }
  return ((millis() - _requestStart) > _requestTime);
}


int ACD10::readSensor()
{
  if (requestReady() == false)
  {
    return ACD10_NOT_READY;
  }

  uint8_t buf[10];
  if (_request(buf, 9) != 0)
  {
    return ACD10_REQUEST_ERROR;
  }
  _requestStart = 0;  //  set no request pending.

  //  CRC CHECK
  if (buf[2] != _crc8(&buf[0], 2))
  {
    //  Serial.println("CRC error 1");
    return ACD10_CRC_ERROR;
  }
  if (buf[5] != _crc8(&buf[3], 2))
  {
    //  Serial.println("CRC error 2");
    return ACD10_CRC_ERROR;

  }
  if (buf[8] != _crc8(&buf[6], 2))
  {
    //  Serial.println("CRC error 3");
    return ACD10_CRC_ERROR;
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

  return ACD10_OK;
}


uint32_t ACD10::getCO2Concentration()
{
  return _concentration;
}


uint16_t ACD10::getTemperature()
{
  return _temperature;
}


uint32_t ACD10::lastRead()
{
  return _lastRead;
}


void ACD10::setRequestTime(uint8_t milliseconds)
{
  _requestTime = milliseconds;
}


uint8_t ACD10::getRequestTime()
{
  return _requestTime;
}


/////////////////////////////////////////////
//
//  CALIBRATION
//
bool ACD10::setCalibrationMode(uint8_t mode)
{
  if (mode > 1) return false;
  uint8_t buf[5] = { 0x53, 0x06, 0x00, 0x00, 0x00 };
  buf[3] = mode;
  buf[4] = _crc8(&buf[2], 2);
  //  Serial.println(buf[4], HEX);
  _command(buf, 5);
  return true;
}


uint8_t ACD10::readCallibrationMode()
{
  uint8_t buf[3] = { 0x53, 0x06, 0x00 };
  _command(buf, 2);
  _request(buf, 3);
  // if (buf[2] != _crc8(&buf[0], 2))
  // {
    // Serial.print(__FUNCTION__);
    // Serial.println(": CRC error");
  // }
  return buf[1];
}


bool ACD10::setManualCalibration(uint16_t value)
{
  if ((value < 400) || (value > 5000)) return false;
  uint8_t buf[5] = { 0x52, 0x04, 0x00, 0x00, 0x00 };
  buf[3] = value & 0xFF;
  buf[2] = value >> 8;
  buf[4] = _crc8(&buf[2], 2);
  _command(buf, 5);
  return true;
}


uint16_t ACD10::readManualCalibration()
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
void ACD10::factoryReset()
{
  uint8_t buf[3] = { 0x52, 0x02, 0x00};
  _command(buf, 3);
}


bool ACD10::readFactorySet()
{
  uint8_t buf[3] = { 0x52, 0x02, 0x00 };
  _command(buf, 2);
  _request(buf, 3);
  // if (buf[2] != _crc8(&buf[0], 2))
  // {
    // Serial.print(__FUNCTION__);
    // Serial.println(": CRC error");
  // }
  return (buf[1] == 0x01);
}


void ACD10::readFirmwareVersion(char * arr)
{
  uint8_t buf[2] = { 0xD1, 0x00 };
  _command(buf, 2);
  _request((uint8_t *) arr, 10);
  arr[10] = '\0';
}


void ACD10::readSensorCode(char * arr)
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
int ACD10::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//

int ACD10::_command(uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
  return _error;
}


int ACD10::_request(uint8_t * arr, uint8_t size)
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


uint8_t ACD10::_crc8(uint8_t * arr, uint8_t size)
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

