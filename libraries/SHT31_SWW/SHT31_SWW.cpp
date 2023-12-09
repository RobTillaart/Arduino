//
//    FILE: SHT31_SWW.cpp
//  AUTHOR: Rob Tillaart, Gunter Haug
// VERSION: 0.2.0
//    DATE: 2019-02-08 (base SHT31 lib)
// PURPOSE: Arduino library for the SHT31 temperature and humidity sensor
//          to be used with the SoftwareWire library instead of (hardware) Wire.
//          derives from SHT31 0.3.8
//     URL: https://www.adafruit.com/product/2857
//          https://github.com/RobTillaart/SHT31_SWW
//          https://github.com/RobTillaart/SHT31


#include "SHT31_SWW.h"


//  SUPPORTED COMMANDS - single shot mode only
#define SHT31_READ_STATUS       0xF32D
#define SHT31_CLEAR_STATUS      0x3041

#define SHT31_SOFT_RESET        0x30A2
#define SHT31_HARD_RESET        0x0006

#define SHT31_MEASUREMENT_FAST  0x2416     //  page 10 datasheet
#define SHT31_MEASUREMENT_SLOW  0x2400     //  no clock stretching

#define SHT31_HEAT_ON           0x306D
#define SHT31_HEAT_OFF          0x3066
#define SHT31_HEATER_TIMEOUT    180000UL   //  milliseconds


SHT31_SWW::SHT31_SWW(uint8_t address,  SoftwareWire * wire)
{
  _address        = address;
  _softwareWire   = wire;
  _lastRead       = 0;
  _rawTemperature = 0;
  _rawHumidity    = 0;
  _heatTimeout    = 0;
  _heaterStart    = 0;
  _heaterStop     = 0;
  _heaterOn       = false;
  _error          = SHT31_OK;
}


bool SHT31_SWW::begin()
{
  if ((_address != 0x44) && (_address != 0x45))
  {
    return false;
  }
  _softwareWire->begin();
  return reset();
}


bool SHT31_SWW::isConnected()
{
  _softwareWire->beginTransmission(_address);
  int rv = _softwareWire->endTransmission();
  if (rv != 0) _error = SHT31_ERR_NOT_CONNECT;
  return (rv == 0);
}


////////////////////////////////////////////////////
//
//  PRIVATE
//
bool SHT31_SWW::writeCmd(uint16_t cmd)
{
  _softwareWire->beginTransmission(_address);
  _softwareWire->write(cmd >> 8 );
  _softwareWire->write(cmd & 0xFF);
  if (_softwareWire->endTransmission() != 0)
  {
    _error = SHT31_ERR_WRITECMD;
    return false;
  }
  return true;
}


bool SHT31_SWW::readBytes(uint8_t n, uint8_t *val)
{
  int rv = _softwareWire->requestFrom(_address, (uint8_t) n);
  if (rv == n)
  {
    for (uint8_t i = 0; i < n; i++)
    {
      val[i] = _softwareWire->read();
    }
    return true;
  }
  _error = SHT31_ERR_READBYTES;
  return false;
}


//  -- END OF FILE --

