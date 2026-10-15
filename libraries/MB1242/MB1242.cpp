//
//    FILE: MB1242.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2026-10-13
// PURPOSE: Arduino library for the MaxBotix I2C MB1242 distance sensor.
//     URL: https://github.com/RobTillaart/MB1242



#include "MB1242.h"


MB1242::MB1242(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  //  reset variables
  _error = MB1242_OK;
  _lastRead = 0;
  _lastRequest = 0;
  _requestInProgress = false;
}

bool MB1242::begin()
{
  //  reset variables
  _error = 0;
  _lastRead = 0;
  _lastRequest = 0;
  _requestInProgress = false;
  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool MB1242::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}

uint8_t MB1242::getAddress()
{
  return _address;
}


///////////////////////////////////////
//
//  REQUEST
//
bool MB1242::requestDistance()
{
  //  what if already request in progress?
  uint8_t arr[1] = { 0x51 };
  _write(arr, 1);
  if (_error != MB1242_OK)
  {
    return false;
  }
  _lastRequest = millis();
  _requestInProgress = true;
  return true;
}

bool MB1242::requestInProgress()
{
  return _requestInProgress;
}

uint32_t MB1242::lastRequest()
{
  return _lastRequest;
}

void MB1242::setStatusPin(uint8_t statusPin)
{
  _statusPin = statusPin;
  pinMode(statusPin, INPUT);
}

bool MB1242::ready()
{
  if (_requestInProgress == false)
  {
    _error = MB1242_NO_REQUEST_PENDING;
    return false;
  }
  //  support status pin 2?
  if (_statusPin != 255)
  {
    if (digitalRead(_statusPin) == HIGH)
    {
      _error = MB1242_NOT_READY;
      return false;
    }
    _error = MB1242_OK;
    return true;
  }
  //  time based ready check...
  if ((millis() - _lastRequest) < 100)
  {
    _error = MB1242_NOT_READY;
    return false;
  }
  _error = MB1242_OK;
  return true;
}


///////////////////////////////////////
//
//  READ
//
int16_t MB1242::readCM()
{
  if (_requestInProgress == false)
  {
    _error = MB1242_NO_REQUEST_PENDING;
    return 0;  //  indicates error...
  }
  uint16_t raw;
  if (_read(raw) != MB1242_OK)
  {
    return 0;  //  indicates error...
  }
  _requestInProgress = false;
  _lastRead = millis();
  return raw;  //  20..750
}

float MB1242::readMeter()
{
  return readCM() * 0.01f;
}

float MB1242::readInch()
{
  return readCM() * (1.0f / 2.54f);
}

float MB1242::readFeet()
{
  return readCM() * (1.0f / 30.48f);
}

uint32_t MB1242::lastRead()
{
  return _lastRead;
}


///////////////////////////////////////
//
//  OTHER
//
bool MB1242::changeAddress(uint8_t address)
{
  //  if address is same, skip?
  if ((address == 0)   || (address == 80) ||
      (address == 164) || (address == 170))
  {
    _error = MB1242_INVALID_ADDRESS;
    return false;
  }
  uint8_t arr[4];
  arr[0] = _address << 1;
  arr[1] = 0xAA;  //  170
  arr[2] = 0xA5;  //  165
  arr[4] = address << 1;
  _write(arr, 4);
  if (_error != MB1242_OK)
  {
    return false;
  }
  _address = address;
  return true;
}

int MB1242::getLastError()
{
  int e = _error;
  _error = MB1242_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//
int MB1242::_write(uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
  return _error;
}


int MB1242::_read(uint16_t &raw)
{
  uint8_t bytes = _wire->requestFrom(_address, (uint8_t)2);
  if (bytes < 2)
  {
    _error = MB1242_REQUEST_ERROR;
    return _error;
  }
  raw =  _wire->read() << 8;
  raw |= _wire->read();
  _error = MB1242_OK;
  return _error;
}


//////////////////////////////////////
//
//  DERIVED (wrappers in .h for now)
//


//  -- END OF FILE --

