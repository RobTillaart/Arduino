//
//    FILE: tinySHT2x.cpp
//  AUTHOR: Rob Tillaart, Viktor Balint
// VERSION: 0.2.0
//    DATE: 2021-09-27
// PURPOSE: Arduino library for the SHT2x temperature and humidity sensor optimized for AVR tiny
//     URL: https://github.com/RobTillaart/tinySHT2x



#include "tinySHT2x.h"

#define SHT2x_GET_TEMPERATURE_NO_HOLD       0xF3
#define SHT2x_GET_HUMIDITY_NO_HOLD          0xF5
#define SHT2x_SOFT_RESET                    0xFE
#define SHT2x_ADDRESS                       0x40


tinySHT2x::tinySHT2x(TwoWire *wire)
{
  _wire = wire;
}


bool tinySHT2x::begin()
{
  return isConnected();
}


bool tinySHT2x::isConnected()
{
  _wire->beginTransmission(SHT2x_ADDRESS);
  return (_wire->endTransmission() == 0);
}


bool tinySHT2x::reset()
{
  return writeCmd(SHT2x_SOFT_RESET);
}


///////////////////////////////////
//
//  ASYNC INTERFACE
//
void tinySHT2x::requestTemperature()
{
  writeCmd(SHT2x_GET_TEMPERATURE_NO_HOLD);
}


float tinySHT2x::readTemperature()
{
  uint8_t buffer[3];
  uint16_t raw;

  if (readBytes(3, (uint8_t*) &buffer[0], 90) == false)
  {
    return TINY_SHT2x_NO_VALUE;
  }
  raw = buffer[0] << 8;
  raw += buffer[1];
  raw &= 0xFFFC;

  return -46.85 + (175.72 / 65536.0) * raw;
}


void tinySHT2x::requestHumidity()
{
  writeCmd(SHT2x_GET_HUMIDITY_NO_HOLD);
}


float tinySHT2x::readHumidity()
{
  uint8_t buffer[3];
  uint16_t raw;

  if (readBytes(3, (uint8_t*) &buffer[0], 30) == false)
  {
    return TINY_SHT2x_NO_VALUE;
  }
  raw = buffer[0] << 8;
  raw += buffer[1];
  raw &= 0xFFFC;

  return -6.0 + (125.0 / 65536.0) * raw;
}


///////////////////////////////////
//
//  SYNC INTERFACE
//
float tinySHT2x::getTemperature(uint8_t del)
{
  requestTemperature();
  delay(del);
  return readTemperature();
}


float tinySHT2x::getHumidity(uint8_t del)
{
  requestHumidity();
  delay(del);
  return readHumidity();
}


//////////////////////////////////////////////////////////
//
//  PRIVATE
//
bool tinySHT2x::writeCmd(uint8_t cmd)
{
  _wire->beginTransmission(SHT2x_ADDRESS);
  _wire->write(cmd);
  return (_wire->endTransmission() == 0);
}


bool tinySHT2x::readBytes(uint8_t n, uint8_t * val, uint8_t maxDuration)
{
  _wire->requestFrom((uint8_t)SHT2x_ADDRESS, (uint8_t) n);
  uint32_t start = millis();
  while (_wire->available() < n)
  {
    if (millis() - start > maxDuration)
    {
      return false;
    }
    yield();
  }

  for (uint8_t i = 0; i < n; i++)
  {
    val[i] = _wire->read();
  }
  return true;
}


//  -- END OF FILE --

