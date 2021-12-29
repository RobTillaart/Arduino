//
//    FILE: tinytinySHT2x.cpp
//  AUTHOR: Rob Tillaart, Viktor Balint
// VERSION: 0.1.1
//    DATE: 2021-09-27
// PURPOSE: Arduino library for the SHT2x temperature and humidity sensor optimized for AVR tiny
//     URL: https://github.com/RobTillaart/tinytinySHT2x
//

//  HISTORY:
//  0.1.0   2021-09-27  initial version
//  0.1.1   2021-12-29  update library.json, readme, license, minor edits


#include "tinySHT2x.h"

#define SHT2x_GET_TEMPERATURE_NO_HOLD       0xF3
#define SHT2x_GET_HUMIDITY_NO_HOLD          0xF5
#define SHT2x_SOFT_RESET                    0xFE
#define SHT2x_ADDRESS                       0x40


tinySHT2x::tinySHT2x()
{
}


void tinySHT2x::begin(TwoWire *wire)
{
  _wire = wire;
  _wire->begin();
}


float tinySHT2x::getTemperature()
{
  uint8_t buffer[3];
  uint16_t raw;

  writeCmd(SHT2x_GET_TEMPERATURE_NO_HOLD);
  delay(70);
  if (readBytes(3, (uint8_t*) &buffer[0], 90) == false)
  {
    return TINY_SHT2x_NO_VALUE;
  }
  raw = buffer[0] << 8;
  raw += buffer[1];
  raw &= 0xFFFC;

  return -46.85 + (175.72 / 65536.0) * raw;
}


float tinySHT2x::getHumidity()
{
  uint8_t buffer[3];
  uint16_t raw;

  //  HUMIDITY
  writeCmd(SHT2x_GET_HUMIDITY_NO_HOLD);
  delay(30);
  if (readBytes(3, (uint8_t*) &buffer[0], 30) == false)
  {
    return -999;
  }
  raw = buffer[0] << 8;
  raw += buffer[1];
  raw &= 0xFFFC;

  return -6.0 + (125.0 / 65536.0) * raw;
}


bool tinySHT2x::reset()
{
  return writeCmd(SHT2x_SOFT_RESET);
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


bool tinySHT2x::readBytes(uint8_t n, uint8_t *val, uint8_t maxDuration)
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


// -- END OF FILE --

