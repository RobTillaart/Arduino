//
//    FILE: DS1683.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2026-09-13
// VERSION: 0.1.0
// PURPOSE: Arduino library for the I2C DS1683 elapsed time monitor
//     URL: https://github.com/RobTillaart/DS1683


#include "DS1683.h"


//  datasheet page 5
//            REGISTERS                   address     bytes
const uint8_t DS1683_REG_ELAPSED_TIME   = 0x0A;       //  4
const uint8_t DS1683_REG_ETC_ALARM      = 0x12;       //  4
const uint8_t DS1683_REG_EVENT_COUNT    = 0x08;       //  2
const uint8_t DS1683_REG_EC_ALARM       = 0x10;       //  2

const uint8_t DS1683_REG_STATUS         = 0x01;       //  1
const uint8_t DS1683_REG_CONFIGURATION  = 0x16;       //  1
const uint8_t DS1683_REG_COMMAND        = 0x00;       //  1

const uint8_t DS1683_REG_EEPROM_BASE    = 0x20;       //  16
const uint8_t DS1683_REG_PASSWORD_ENTRY = 0x02;       //  4
const uint8_t DS1683_REG_PASSWORD_VALUE = 0x1A;       //  4


DS1683::DS1683(TwoWire *wire)
{
  _address = 0x6B;
  _wire = wire;
  _error = DS1683_OK;
}

bool DS1683::begin()
{
  //  reset variables
  _error = DS1683_OK;

  if (! isConnected())
  {
    return false;
  }
  return true;
}

bool DS1683::isConnected()
{
  _wire->beginTransmission(_address);
  _error = _wire->endTransmission();
  return (_error == DS1683_OK);
}

uint8_t DS1683::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  CONFIGURATION
//
int DS1683::setConfiguration(uint8_t mask)
{
  _command(DS1683_REG_CONFIGURATION, &mask, 1);
  return _error;
}

uint8_t DS1683::getConfiguration()
{
  uint8_t mask;
  _request(DS1683_REG_CONFIGURATION, &mask, 1);
  return mask;
}


/////////////////////////////////////////////
//
//  COMMAND
//
int DS1683::setCommand(uint8_t command)
{
  _command(DS1683_REG_COMMAND, &command, 1);
  return _error;
}

uint8_t DS1683::getCommand()
{
  uint8_t mask;
  _request(DS1683_REG_COMMAND, &mask, 1);
  return mask;
}


/////////////////////////////////////////////
//
//  STATUS
//
uint8_t DS1683::getStatus()
{
  uint8_t mask;
  _request(DS1683_REG_STATUS, &mask, 1);
  return mask;
}


/////////////////////////////////////////////
//
//  ALARM
//
int DS1683::setEventTimeAlarm(uint32_t alarm)
{
  alarm <<= 2;  //  adjust seconds to QSEC
  uint8_t arr[4];
  for (int i = 0; i < 4; i++)
  {
    arr[i] = alarm & 0xFF;
    alarm >>= 8;
  }
  _command(DS1683_REG_ETC_ALARM, arr, 4);
  return _error;
}

uint32_t DS1683::getEventTimeAlarm()
{
  uint8_t arr[4];
  _request(DS1683_REG_ETC_ALARM, arr, 4);
  uint32_t value = arr[0];
  value += arr[1] * 256UL;
  value += arr[2] * (256UL * 256UL);
  value += arr[2] * (256UL * 256UL * 256UL);
  return value;
}

int DS1683::setEventCountAlarm(uint16_t alarm)
{
  alarm <<= 2;  //  adjust seconds to QSEC
  uint8_t arr[2];
  for (int i = 0; i < 2; i++)
  {
    arr[i] = alarm & 0xFF;
    alarm >>= 8;
  }
  _command(DS1683_REG_EC_ALARM, arr, 2);
  return _error;
}

uint16_t DS1683::getEventCountAlarm()
{
  uint8_t arr[2];
  _request(DS1683_REG_EC_ALARM, arr, 2);
  uint32_t value = arr[0];
  value += arr[1] * 256UL;
  return value;
}


/////////////////////////////////////////////
//
//  READ COUNTERS
//
uint32_t DS1683::getElapsedSeconds()
{
  return getElapsedQSEC() / 4;
}

uint32_t DS1683::getElapsedQSEC()
{
  uint8_t arr[4];
  _request(DS1683_REG_ELAPSED_TIME, arr, 4);
  uint32_t value = arr[0];
  value += arr[1] * 256UL;
  value += arr[2] * (256UL * 256UL);
  value += arr[2] * (256UL * 256UL * 256UL);
  return value;  //  internal quarter of seconds.
}

uint32_t DS1683::getEventCounter()
{
  uint8_t arr[2];
  _request(DS1683_REG_EVENT_COUNT, arr, 2);
  uint32_t value = arr[0] + arr[1] * 256UL;
  uint8_t ECMSB = getConfiguration() & 0x01;
  if (ECMSB) value += 0x10000;
  return value;
}


/////////////////////////////////////////////
//
//  RESET COUNTERS
//
int DS1683::resetEventTime()
{
  uint8_t arr[4] = {0,0,0,0};
  _command(DS1683_REG_ELAPSED_TIME, arr, 4);
  return _error;
}

int DS1683::resetEventCounter()
{
  uint8_t arr[4] = {0,0,0,0};
  _command(DS1683_REG_EVENT_COUNT, arr, 4);
  return _error;
}


/////////////////////////////////////////////
//
//  EEPROM
//
int DS1683::setEEPROM(uint8_t address, uint8_t value)
{
  if (address > 15)
  {
    _error = DS1683_EEPROM_ERROR;
    return _error;
  }
  _command(DS1683_REG_EEPROM_BASE + address, &value, 1);
  return _error;
}

uint8_t DS1683::getEEPROM(uint8_t address)
{
  if (address > 15)
  {
    _error = DS1683_EEPROM_ERROR;
    return 0;
  }
  uint8_t value;
  _request(DS1683_REG_EEPROM_BASE + address, &value, 1);
  return value;
}


/////////////////////////////////////////////
//
//  PASSWORD
//
int DS1683::setPasswordEntry(uint32_t entry)
{
  uint8_t arr[4];
  for (int i = 0; i < 4; i++)
  {
    arr[i] = entry & 0xFF;
    entry >>= 8;
  }
  _command(DS1683_REG_PASSWORD_ENTRY, arr, 4);
  return _error;
}

int DS1683::setPasswordValue(uint32_t value)
{
  uint8_t arr[4];
  for (int i = 0; i < 4; i++)
  {
    arr[i] = value & 0xFF;
    value >>= 8;
  }
  _command(DS1683_REG_PASSWORD_VALUE, arr, 4);
  return _error;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int DS1683::getLastError()
{
  int e = _error;
  _error = DS1683_OK;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//

int DS1683::_command(uint8_t reg, uint8_t * arr, uint8_t size)
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


int DS1683::_request(uint8_t reg, uint8_t * arr, uint8_t size)
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
  _error = DS1683_OK;
  return _error;
}



//  -- END OF FILE --

