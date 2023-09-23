//
//    FILE: MSP300.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
// PURPOSE: Arduino library for I2C MSP300 pressure transducer.
//     URL: https://github.com/RobTillaart/MSP300


#include "MSP300.h"


MSP300::MSP300(const uint8_t deviceAddress, TwoWire *wire)
{
  _address    = deviceAddress;
  _wire       = wire;
  _error      = MSP300_OK;
  _maxValue   = 100;
  _raw        = 0;
}


#if defined (ESP8266) || defined(ESP32)
bool MSP300::begin(int dataPin, int clockPin, int maxValue)
{
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  _maxValue = maxValue;
  return true;
}
#endif


bool MSP300::begin(int maxValue)
{
  _wire->begin();
  if (! isConnected()) return false;
  _maxValue = maxValue;
  return true;
}


bool MSP300::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


bool MSP300::setAddress(const uint8_t deviceAddress)
{
  //  Verify? 0x28, 0x36, 0x46, 0x48, 0x51
  _address = deviceAddress;
  return isConnected();
}


uint8_t MSP300::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  CALIBRATION
//
void MSP300::setPressureCounts(uint16_t Pmin, uint16_t Pmax)
{
  _pressureFactor = 1.0 / (Pmax - Pmin);
}


/////////////////////////////////////////////
//
//  READ
//
uint32_t MSP300::readPT()
{
  _request();
  _read(4);    //  read all data.
  //  TODO check status
  //  uint8_t status = (_raw >> 30);
  //  00 = OK
  //  01 = reserved
  //  10 = stale data
  //  11 = error
  return _raw;
}


float MSP300::getPressure()
{
  //  formula page 5 datasheet
  int pres = (_raw >> 16) && 0x3FFF;

  return pres * (_maxValue * _pressureFactor);
}


float MSP300::getTemperature()
{
  int temp = (_raw >> 5) && 0x07FF;
  return temp * (200.0 / 2048) - 50.0;
}


int MSP300::lastError()
{
  int e = _error;
  _error = MSP300_OK;
  return e;
}


/////////////////////////////////////////////////////
//
//  PRIVATE
//
void MSP300::_request()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
}


void MSP300::_read(uint8_t bytes)
{
  if (_wire->requestFrom(_address, bytes) != bytes)
  {
    _error = MSP300_ERROR;
    return;  //  keep last value
  }
  _raw = 0;
  for (int i= 0; i < bytes; i++)
  {
    _raw <<= 8;
    _raw = _wire->read();
  }
}


//  -- END OF FILE --

