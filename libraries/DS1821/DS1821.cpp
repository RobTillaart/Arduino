//
//    FILE: DS1821.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.6
//    DATE: 2014-10-05
// PURPOSE: Arduino library for DS1821 temperature sensor
//     URL: https://github.com/RobTillaart/DS1821


#include "DS1821.h"


//  CONFIG REGISTER MASKS.   P7-8 datasheet
#define DS1821_CONF_1SHOT    0x01
#define DS1821_CONF_POL      0x02
#define DS1821_CONF_TR       0x04
#define DS1821_CONF_TLF      0x08
#define DS1821_CONF_THF      0x10
#define DS1821_CONF_NVB      0x20
// skip always one           0x40
#define DS1821_CONF_DONE     0x80


//  COMMANDS                 P10-11 datasheet
#define START_CONVERT        0xEE
#define STOP_CONVERT         0x22
#define READ_CONFIG_REG      0xAC
#define WRITE_CONFIG_REG     0x0C
#define READ_TEMPERATURE     0xAA
#define READ_COUNTER         0xA0
#define LOAD_COUNTER         0x41
#define WRITE_TH             0x01
#define WRITE_TL             0x02
#define READ_TH              0xA1
#define READ_TL              0xA2


////////////////////////////////////////////////////////////////
//
//  PUBLIC
//
DS1821::DS1821(OneWire *ow)
{
  _oneWire = ow;
  _error = DS1821_RESET_OK;
}


//  P5 - Operation measuring temperature
int DS1821::requestTemperature()
{
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(START_CONVERT);
  return DS1821_RESET_OK;
}


int DS1821::requestContinuous()
{
  _clrConfigFlag(DS1821_CONF_1SHOT);
  return requestTemperature();
}


int DS1821::stopContinuous()
{
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(STOP_CONVERT);
  return DS1821_RESET_OK;
}


int DS1821::conversionReady()
{
  return _getConfigFlag(DS1821_CONF_DONE);
}


//  P5 - Operation measuring temperature
float DS1821::readTemperature()
{
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(READ_TEMPERATURE);
  int temperature = _readByte();

  //  Handle negative values: >= 200 ==> subtract 256;
  if (temperature >= 200) temperature -= 256;

  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(READ_COUNTER);
  int countRemain = _readByte() * 256;
  countRemain += _readByte();

  //  Load counter to populate the slope accumulator into counter register
  //  Q: is this a fixed number? if so it could be hard coded...
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(LOAD_COUNTER);

  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(READ_COUNTER);

  int countPerC = _readByte() * 256;
  countPerC += _readByte();

  return temperature + 0.5 - (1.0 * countRemain) / countPerC;
}


int DS1821::setLow(int8_t lo)
{
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(WRITE_TL);
  _command(lo);
  return DS1821_RESET_OK;
}


int DS1821::getLow()
{
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(READ_TL);
  return _readByte();
}


int DS1821::setHigh(int8_t hi)
{
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(WRITE_TH);
  _command(hi);
  return DS1821_RESET_OK;
}


int DS1821::getHigh()
{
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(READ_TL);
  return _readByte();
}


int DS1821::getHighFlag()
{
  return _getConfigFlag(DS1821_CONF_THF);
}


int DS1821::clrHighFlag()
{
  return _clrConfigFlag(DS1821_CONF_THF);
}


int DS1821::getLowFlag()
{
  return _getConfigFlag(DS1821_CONF_TLF);
}


int DS1821::clrLowFlag()
{
  return _clrConfigFlag(DS1821_CONF_TLF);
}


//////////////////////////////////////////////////////////
//
//  THERMOSTAT CONFIG
//
int DS1821::setOneWireMode(uint8_t VDD, uint8_t DQ)
{
  _VDD = VDD;
  _DQ = DQ;
  //  switch off power
  pinMode(_VDD, OUTPUT);
  digitalWrite(_VDD, LOW);
  pinMode(_DQ, OUTPUT);
  digitalWrite(_DQ, HIGH);
  delay(1);
  //  toggle 16 times.
  for(uint8_t i = 0; i < 16; i++)
  {
    digitalWrite(_DQ, LOW);
    digitalWrite(_DQ, HIGH);
  }
  pinMode(_DQ, INPUT);
  //  switch power on again.
  digitalWrite(_VDD, HIGH);
  delay(1);
  return _clrConfigFlag(DS1821_CONF_TR);
}


int DS1821::setPolarity(int activeState)
{
  if (activeState == HIGH) return _setConfigFlag(DS1821_CONF_POL);
  return _clrConfigFlag(DS1821_CONF_POL);
}


int DS1821::getPolarity()
{
  return _getConfigFlag(DS1821_CONF_POL);
}


int DS1821::setThermostatMode()
{
  int rv = _setConfigFlag(DS1821_CONF_TR);
  delay(10);    // wait for copy to NVRAM
  digitalWrite(_VDD, LOW);
  delay(1000);
  digitalWrite(_VDD, HIGH);
  return rv;
}


////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
int DS1821::_getConfigFlag(uint8_t flag)
{
  return ((_readConfig() & flag) > 0);  // true = 1 / false = 0
}


//  See page 4 datasheet
uint8_t DS1821::_waitForNVB()
{
  uint8_t config = 0;
  for (uint8_t i = 0; i < 10; i++)
  {
    config = _readConfig();
    if (!(config & DS1821_CONF_NVB)) break;
    delay(1);
  }
  return config;
}


int DS1821::_setConfigFlag(uint8_t flag)
{
  uint8_t config = _waitForNVB();
  config |= flag;
  return _writeConfig(config);
}


int DS1821::_clrConfigFlag(uint8_t flag)
{
  uint8_t config = _waitForNVB();
  config &= ~flag;
  return _writeConfig(config);
}


int DS1821::_readConfig()
{
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(READ_CONFIG_REG);
  return _readByte();
}


int DS1821::_writeConfig(uint8_t val)
{
  while (_getConfigFlag(DS1821_CONF_NVB)) delay(1);
  if (_reset() != DS1821_RESET_OK) return DS1821_RESET_ERROR;
  _command(WRITE_CONFIG_REG);
  _command(val);
  return DS1821_RESET_OK;
}


//  -- END OF FILE --

