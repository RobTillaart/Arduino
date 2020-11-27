//
//    FILE: DS18B20.cpp
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.6
//    DATE: 2017-07-25
// PUPROSE: library for DS18B20 temperature sensor with minimal footprint
//
// HISTORY:
// 0.1.0	2017-07-25 initial version
// 0.1.1 	2020-02-18 added getAddress()
// 0.1.2    2020-04-11 #pragma once, refactor
// 0.1.3    2020-04-22 #1 fix library.json file
// 0.1.4    2020-04-23 #2 add retry in begin() to support Wemos
// 0.1.5    2020-04-29 #4 added set/getConfig + DEVICE_CRC_ERROR + example
// 0.1.6    2020-06-07 fix library.json

#include "DS18B20.h"

// OneWire commands
#define STARTCONVO      0x44
#define READSCRATCH     0xBE
#define WRITESCRATCH    0x4E

// Scratchpad locations
#define TEMP_LSB        0
#define TEMP_MSB        1
#define HIGH_ALARM_TEMP 2
#define LOW_ALARM_TEMP  3
#define CONFIGURATION   4
#define INTERNAL_BYTE   5
#define COUNT_REMAIN    6
#define COUNT_PER_C     7
#define SCRATCHPAD_CRC  8

// Device resolution
#define TEMP_9_BIT  0x1F //  9 bit
#define TEMP_10_BIT 0x3F // 10 bit
#define TEMP_11_BIT 0x5F // 11 bit
#define TEMP_12_BIT 0x7F // 12 bit


DS18B20::DS18B20(OneWire* _oneWire)
{
  _wire = _oneWire;
  _addresFound = false;
  _config = DS18B20_CLEAR;
}

bool DS18B20::begin(void)
{
  _config = DS18B20_CLEAR;
  _addresFound = false;
  for (uint8_t retries = 3; (retries > 0) && (_addresFound == false); retries--)
  {
    _wire->reset_search();
    _deviceAddress[0] = 0x00;
    _wire->search(_deviceAddress);
    _addresFound = _deviceAddress[0] != 0x00 &&
                _wire->crc8(_deviceAddress, 7) == _deviceAddress[7];
  }
  return _addresFound;
}

void DS18B20::readScratchPad(uint8_t *scratchPad, uint8_t fields)
{
  _wire->reset();
  _wire->select(_deviceAddress);
  _wire->write(READSCRATCH);

  for (uint8_t i = 0; i < fields; i++)
  {
    scratchPad[i] = _wire->read();
  }
  _wire->reset();
}

bool DS18B20::isConversionComplete(void)
{
  return (_wire->read_bit() == 1);
}	

void DS18B20::requestTemperatures(void)
{
  _wire->reset();
  _wire->skip();
  _wire->write(STARTCONVO, 0);
}

float DS18B20::getTempC(void)
{
  ScratchPad scratchPad;
  if (_config & DS18B20_CRC)
  {
    readScratchPad(scratchPad, 9);
    if (_wire->crc8(scratchPad, 8) != scratchPad[SCRATCHPAD_CRC])
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
  if (temp < -55) return DEVICE_DISCONNECTED;
  return temp;
}

void DS18B20::setResolution(uint8_t newResolution)
{
  _wire->reset();
  _wire->select(_deviceAddress);
  _wire->write(WRITESCRATCH);
  // two dummy values for LOW & HIGH ALARM
  _wire->write(0);
  _wire->write(100);
  switch (newResolution)
  {
  case 12:
    _wire->write(TEMP_12_BIT);
    break;
  case 11:
    _wire->write(TEMP_11_BIT);
    break;
  case 10:
    _wire->write(TEMP_10_BIT);
    break;
  case 9:
  default:
    _wire->write(TEMP_9_BIT);
    break;
  }
  _wire->reset();
}

bool DS18B20::getAddress(uint8_t* buf)
{
  if (_addresFound)
  {
	  for (uint8_t i = 0; i < 8; i++)
	  {
		 buf[i] = _deviceAddress[i];
	  }
  }
  return _addresFound;
}

//  -- END OF FILE --
