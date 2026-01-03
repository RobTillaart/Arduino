//
//    FILE: SHT31_SW.cpp
//  AUTHOR: Rob Tillaart, Gunter Haug
// VERSION: 0.3.2
//    DATE: 2019-02-08 (base SHT31 lib)
// PURPOSE: Arduino library for the SHT31 temperature and humidity sensor
//          to be used with the SoftWire library instead of (hardware) Wire.
//          derives from SHT31 0.3.8
//     URL: https://www.adafruit.com/product/2857
//          https://github.com/RobTillaart/SHT31_SW
//          https://github.com/RobTillaart/SHT31


#include "SHT31_SW.h"


SHT31_SW::SHT31_SW(const uint8_t address,  SoftWire *softWire)
{
  _address        = address;
  _softWire       = softWire;
  _lastRead       = 0;
  _rawTemperature = 0;
  _rawHumidity    = 0;
  _heatTimeout    = 0;
  _heaterStart    = 0;
  _heaterStop     = 0;
  _heaterOn       = false;
  _error          = SHT31_OK;
}


bool SHT31_SW::begin()
{
  if ((_address != 0x44) && (_address != 0x45))
  {
    return false;
  }
  _softWire->begin();
  //  See #12
  _softWire->setTxBuffer(swTxBuffer, sizeof(swTxBuffer));
  _softWire->setRxBuffer(swRxBuffer, sizeof(swRxBuffer));
  return reset();
}


bool SHT31_SW::isConnected()
{
  _softWire->beginTransmission(_address);
  int rv = _softWire->endTransmission();
  if (rv != 0) _error = SHT31_ERR_NOT_CONNECT;
  return (rv == 0);
}


////////////////////////////////////////////////////
//
//  PRIVATE
//
bool SHT31_SW::writeCmd(uint16_t cmd)
{
  _softWire->beginTransmission(_address);
  _softWire->write(cmd >> 8);
  _softWire->write(cmd & 0xFF);
  if (_softWire->endTransmission() != 0)
  {
    _error = SHT31_ERR_WRITECMD;
    return false;
  }
  //  delay(1);
  return true;
}


bool SHT31_SW::readBytes(uint8_t n, uint8_t *val)
{
  int rv = _softWire->requestFrom(_address, (uint8_t) n);
  if (rv == n)
  {
    for (uint8_t i = 0; i < n; i++)
    {
      val[i] = _softWire->read();
    }
    return true;
  }
  _error = SHT31_ERR_READBYTES;
  return false;
}


//  -- END OF FILE --

