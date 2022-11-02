//
//    FILE: DS18B20.cpp
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.13
//    DATE: 2017-07-25
// PUPROSE: library for DS18B20 temperature sensor with minimal footprint
//     URL: https://github.com/RobTillaart/DS18B20_RT
//
// HISTORY: see changelog.md


#include "DS18B20.h"


//  OneWire commands
#define STARTCONVO          0x44
#define READSCRATCH         0xBE
#define WRITESCRATCH        0x4E


//  Scratchpad locations
#define TEMP_LSB            0
#define TEMP_MSB            1
#define HIGH_ALARM_TEMP     2
#define LOW_ALARM_TEMP      3
#define CONFIGURATION       4
#define INTERNAL_BYTE       5
#define COUNT_REMAIN        6
#define COUNT_PER_C         7
#define SCRATCHPAD_CRC      8


//  Device resolution
#define TEMP_9_BIT          0x1F    //   9 bit
#define TEMP_10_BIT         0x3F    //  10 bit
#define TEMP_11_BIT         0x5F    //  11 bit
#define TEMP_12_BIT         0x7F    //  12 bit


DS18B20::DS18B20(OneWire* ow)
{
  _oneWire = ow;
  _addressFound = false;
  _config = DS18B20_CLEAR;
}


bool DS18B20::begin(uint8_t retries)
{
  _config = DS18B20_CLEAR;
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


bool DS18B20::isConversionComplete(void)
{
  return (_oneWire->read_bit() == 1);
}


void DS18B20::requestTemperatures(void)
{
  _oneWire->reset();
  _oneWire->skip();
  _oneWire->write(STARTCONVO, 0);
}


float DS18B20::getTempC(void)
{
  ScratchPad scratchPad;
  for (int i = 0; i < 9; i++) scratchPad[i] = 0;

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


void DS18B20::setResolution(uint8_t resolution)
{
  _oneWire->reset();
  _oneWire->select(_deviceAddress);
  _oneWire->write(WRITESCRATCH);
  //  two dummy values for LOW & HIGH ALARM
  _oneWire->write(0);
  _oneWire->write(100);
  switch (resolution)
  {
  case 12:
    _oneWire->write(TEMP_12_BIT);
    break;
  case 11:
    _oneWire->write(TEMP_11_BIT);
    break;
  case 10:
    _oneWire->write(TEMP_10_BIT);
    break;
  case 9:
  default:
    _oneWire->write(TEMP_9_BIT);
    break;
  }
  _oneWire->reset();
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


//  -- END OF FILE --

