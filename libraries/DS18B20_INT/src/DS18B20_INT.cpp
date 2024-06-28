//
//    FILE: DS18B20_INT.cpp
//  AUTHOR: Rob.Tillaart
// VERSION: 0.3.3
//    DATE: 2017-07-25
// PURPOSE: library for DS18B20 temperature sensor - integer only.
//     URL: https://github.com/RobTillaart/DS18B20_INT
//          https://github.com/RobTillaart/DS18B20_RT


#include "DS18B20_INT.h"


//  OneWire commands
#define STARTCONVO              0x44
#define READSCRATCH             0xBE
#define WRITESCRATCH            0x4E


//  Device resolution
#define TEMP_9_BIT              0x1F    //   9 bit
#define TEMP_10_BIT             0x3F    //  10 bit
#define TEMP_11_BIT             0x5F    //  11 bit
#define TEMP_12_BIT             0x7F    //  12 bit


DS18B20_INT::DS18B20_INT(OneWire* ow)
{
  _oneWire      = ow;
  _addressFound = false;
  _resolution   = 9;
}


bool DS18B20_INT::begin(uint8_t retries)
{
  if (isConnected(retries))
  {
    _setResolution();
  }
  return _addressFound;
}


bool DS18B20_INT::isConnected(uint8_t retries)
{
  _addressFound = false;
  for (uint8_t rtr = retries; (rtr > 0) && (_addressFound == false); rtr--)
  {
    _oneWire->reset();
    _oneWire->reset_search();
    _deviceAddress[0] = 0x00;
    _oneWire->search(_deviceAddress);
    _addressFound = _deviceAddress[0] != 0x00 &&
                _oneWire->crc8(_deviceAddress, 7) == _deviceAddress[7];
  }
  return _addressFound;
}


void DS18B20_INT::requestTemperatures(void)
{
  _oneWire->reset();
  _oneWire->skip();
  _oneWire->write(STARTCONVO, 0);
}


bool DS18B20_INT::isConversionComplete(void)
{
  return (_oneWire->read_bit() == 1);
}


int16_t DS18B20_INT::getTempC(bool connectCheck)
{
  if (connectCheck)
  {
    if (isConnected(3) == false)
    {
      return DEVICE_DISCONNECTED;
    }
  }
  int16_t rawTemperature = _readRaw();
  rawTemperature >>= 4;
  if (rawTemperature < -55)
  {
    return DEVICE_DISCONNECTED;
  }
  return rawTemperature;
}


bool DS18B20_INT::getAddress(uint8_t * buf)
{
  if (_addressFound)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      buf[i] = _deviceAddress[i];
    }
  }
  return _addressFound;
}


bool DS18B20_INT::setResolution(uint8_t resolution)
{
  if (isConnected())
  {
    _resolution = resolution;
    _setResolution();
  }
  return _addressFound;
}


uint8_t DS18B20_INT::getResolution()
{
  return _resolution;
}


int16_t DS18B20_INT::getTempCentiC(void)
{
  if (isConnected(3) == false)
  {
    return DEVICE_DISCONNECTED;
  }
  int16_t rawTemperature = _readRaw();
  //  rawTemperature = rawTemperature * 100 / 16;
  rawTemperature *= 25;
  rawTemperature >>= 2;
  //  use at own risk. (not tested)
  if (rawTemperature < -5500)
  {
    return DEVICE_DISCONNECTED * 100;
  }
  return rawTemperature;
}


//////////////////////////////////////////////////
//
//  PRIVATE
//
int16_t DS18B20_INT::_readRaw(void)
{
  _oneWire->reset();
  _oneWire->select(_deviceAddress);
  _oneWire->write(READSCRATCH);

  int16_t rawTemperature = ((int16_t)_oneWire->read());
  rawTemperature |= _oneWire->read() << 8;
  _oneWire->reset();
  return rawTemperature;
}


void DS18B20_INT::_setResolution()
{
  uint8_t res;
  switch (_resolution)
  {
    case 12: res = TEMP_12_BIT;  break;
    case 11: res = TEMP_11_BIT;  break;
    case 10: res = TEMP_10_BIT;  break;
    //  lowest as default as we do only integer math.
    default: res = TEMP_9_BIT;   break;
  }

  _oneWire->reset();
  _oneWire->select(_deviceAddress);
  _oneWire->write(WRITESCRATCH);
  //  two dummy values for LOW & HIGH ALARM
  _oneWire->write(0);
  _oneWire->write(100);
  _oneWire->write(res);
  _oneWire->reset();
}


//  -- END OF FILE --

