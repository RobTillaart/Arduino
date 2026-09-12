//
//    FILE: DS1682.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-09-11
// VERSION: 0.1.0
// PURPOSE: Arduino library for the I2C DS1682 elapsed time monitor.
//     URL: https://github.com/RobTillaart/DS1682


#include "DS1682.h"


//            REGISTERS                  address     bytes
const uint8_t DS1682_REG_CONFIGURATION = 0x00;       //  1
const uint8_t DS1682_REG_ALARM         = 0x01;       //  4
const uint8_t DS1682_REG_ELAPSED_TIME  = 0x05;       //  4
const uint8_t DS1682_REG_EVENT_COUNT   = 0x09;       //  2
const uint8_t DS1682_REG_EEPROM_BASE   = 0x0B;       //  10
const uint8_t DS1682_REG_NOT_USED      = 0x15;       //  8
const uint8_t DS1682_REG_RESET         = 0x1D;       //  1
const uint8_t DS1682_REG_WRITE_DISABLE = 0x1E;       //  1
const uint8_t DS1682_REG_MEM_DISABLE   = 0x1F;       //  1


DS1682::DS1682(TwoWire *wire)
{
  _address = 0x6A;
  _wire = wire;
  _error = DS1682_OK;
}

bool DS1682::begin()
{
  //  reset variables
  _error = DS1682_OK;

  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool DS1682::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == DS1682_OK);
}

uint8_t DS1682::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  CONFIG
//
int DS1682::setConfiguration(uint8_t mask)
{
  _command(DS1682_REG_CONFIGURATION, &mask, 1);
  return _error;
}

uint8_t DS1682::getConfiguration()
{
  uint8_t mask;
  _request(DS1682_REG_CONFIGURATION, &mask, 1);
  return mask;
}


/////////////////////////////////////////////
//
//  ALARM
//
int DS1682::setAlarm(uint32_t alarm)
{
  alarm <<= 2;  //  adjust seconds to QSEC
  uint8_t arr[4];
  for (int i = 0; i < 4; i++)
  {
    arr[i] = alarm & 0xFF;
    alarm >>= 8;
  }
  _command(DS1682_REG_ALARM, arr, 4);
  return _error;
}

uint32_t DS1682::getAlarm()
{
  uint8_t arr[4];
  _request(DS1682_REG_ALARM, arr, 4);
  uint32_t value = arr[0];
  value += arr[1] * 256UL;
  value += arr[2] * (256UL * 256UL);
  value += arr[2] * (256UL * 256UL * 256UL);
  return value;
}


/////////////////////////////////////////////
//
//  READ COUNTERS
//
uint32_t DS1682::getElapsedSeconds()
{
  return getElapsedQSEC() / 4;
}

uint32_t DS1682::getElapsedQSEC()
{
  uint8_t arr[4];
  _request(DS1682_REG_ELAPSED_TIME, arr, 4);
  uint32_t value = arr[0];
  value += arr[1] * 256UL;
  value += arr[2] * (256UL * 256UL);
  value += arr[2] * (256UL * 256UL * 256UL);
  return value;  //  internal quarter of seconds.
}

uint32_t DS1682::getEventCounter()
{
  uint8_t arr[2];
  _request(DS1682_REG_EVENT_COUNT, arr, 2);
  uint32_t value = arr[0] + arr[1] * 256UL;
  uint8_t ECMSB = getConfiguration() & 0x01;
  if (ECMSB) value += 0x10000;
  return value;
}


/////////////////////////////////////////////
//
//  EEPROM
//
int DS1682::setEEPROM(uint8_t address, uint8_t value)
{
  if (address > 9)
  {
    _error = DS1682_EEPROM_ERROR;
    return _error;
  }
  _command(DS1682_REG_EEPROM_BASE + address, &value, 1);
  return _error;
}

uint8_t DS1682::getEEPROM(uint8_t address)
{
  if (address > 9)
  {
    _error = DS1682_EEPROM_ERROR;
    return 0;
  }
  uint8_t value;
  _request(DS1682_REG_EEPROM_BASE + address, &value, 1);
  return value;
}


/////////////////////////////////////////////
//
//  MISC
//
int DS1682::reset(bool flag)
{
  uint8_t value = flag ? 0x55 : 0x00;
  _command(DS1682_REG_RESET, &value, 1);
  return _error;
}

int DS1682::writeDisable(bool flag)
{
  uint8_t value = flag ? 0xAA : 0x00;
  _command(DS1682_REG_WRITE_DISABLE, &value, 1);
  return _error;
}

int DS1682::memoryDisable(bool flag)
{
  uint8_t value = flag ? 0xF0 : 0x00;
  _command(DS1682_REG_MEM_DISABLE, &value, 1);
  return _error;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int DS1682::getLastError()
{
  int e = _error;
  _error = DS1682_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//

int DS1682::_command(uint8_t reg, uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
  return _error;
}


int DS1682::_request(uint8_t reg, uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  _error = _wire->endTransmission();
  if (_error) return _error;
  uint8_t bytes = _wire->requestFrom(_address, size);
  if (bytes == 0)
  {
    _error = -1;
    return _error;
  }
  if (bytes < size)
  {
    _error = -2;
    return _error;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    arr[i] = _wire->read();
  }
  _error = DS1682_OK;
  return _error;
}



//  -- END OF FILE --

