//
//    FILE: DS18B20.cpp
//  AUTHOR: Rob.Tillaart
// VERSION: 0.2.2
//    DATE: 2017-07-25
// PURPOSE: library for DS18B20 temperature sensor with minimal footprint
//     URL: https://github.com/RobTillaart/DS18B20_RT
//          https://github.com/RobTillaart/DS18B20_INT


#include "DS18B20.h"


//  OneWire commands
#define STARTCONVO              0x44
#define READSCRATCH             0xBE
#define WRITESCRATCH            0x4E


//  Scratchpad locations
#define TEMP_LSB                 0
#define TEMP_MSB                 1
#define HIGH_ALARM_TEMP          2
#define LOW_ALARM_TEMP           3
#define CONFIGURATION            4
#define INTERNAL_BYTE            5
#define COUNT_REMAIN             6
#define COUNT_PER_C              7
#define SCRATCHPAD_CRC           8


//  Device resolution
#define TEMP_9_BIT              0x1F    //   9 bit
#define TEMP_10_BIT             0x3F    //  10 bit
#define TEMP_11_BIT             0x5F    //  11 bit
#define TEMP_12_BIT             0x7F    //  12 bit


DS18B20::DS18B20(OneWire* ow, uint8_t resolution)
{
  _oneWire      = ow;
  _addressFound = false;
  _resolution   = resolution;
  _config       = DS18B20_CLEAR;
}


bool DS18B20::begin(uint8_t retries)
{
  _config = DS18B20_CLEAR;
  if (isConnected(retries))
  {
    _setResolution();
  }
  return _addressFound;
}


bool DS18B20::isConnected(uint8_t retries)
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


void DS18B20::requestTemperatures(void)
{
  _oneWire->reset();
  _oneWire->skip();
  _oneWire->write(STARTCONVO, 0);
}


bool DS18B20::isConversionComplete(void)
{
  return (_oneWire->read_bit() == 1);
}


float DS18B20::getTempC(bool checkConnect)
{
  ScratchPad scratchPad;
  if (checkConnect)
  {
    if (isConnected(3) == false)
    {
      return DEVICE_DISCONNECTED;
    }
  }

  if (_config & DS18B20_CRC)
  {
    readScratchPad(scratchPad, 9);
    if (_oneWire->crc8(scratchPad, 8) != scratchPad[SCRATCHPAD_CRC])
    {
      return DEVICE_CRC_ERROR;
    }
  }
  else
  {
    readScratchPad(scratchPad, 2);
  }
  int16_t rawTemperature = (((int16_t)scratchPad[TEMP_MSB]) << 8) | scratchPad[TEMP_LSB];
  float temp = 0.0625 * rawTemperature;
  if (temp < -55)
  {
    return DEVICE_DISCONNECTED;
  }
  return temp;
}


bool DS18B20::getAddress(uint8_t* buf)
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


bool DS18B20::setResolution(uint8_t resolution)
{
  if (isConnected())
  {
    _resolution = resolution;
    _setResolution();
  }
  return _addressFound;
}


uint8_t DS18B20::getResolution()
{
  return _resolution;
}


void DS18B20::setConfig(uint8_t config)
{
  _config = config;
}


uint8_t DS18B20::getConfig()
{
  return _config;
}


//////////////////////////////////////////////////
//
//  PRIVATE
//
void DS18B20::readScratchPad(uint8_t *scratchPad, uint8_t fields)
{
  _oneWire->reset();
  _oneWire->select(_deviceAddress);
  _oneWire->write(READSCRATCH);

  for (uint8_t i = 0; i < fields; i++)
  {
    scratchPad[i] = _oneWire->read();
  }
  _oneWire->reset();
}


void DS18B20::_setResolution()
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

