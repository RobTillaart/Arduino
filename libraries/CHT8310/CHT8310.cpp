//
//    FILE: CHT8310.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for CHT8310 temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CHT8310


#include "CHT8310.h"


/////////////////////////////////////////////////////
//
// PUBLIC
//
CHT8310::CHT8310(const uint8_t address, TwoWire *wire)
{
  _wire    = wire;
  _address = address;
}


int CHT8310::begin()
{
  //  address = 0x40, 0x44, 0x48, 0x4C
  if ((_address != 0x40) && (_address != 0x44) && (_address != 0x48) && (_address != 0x4C)) 
  {
    return CHT8310_ERROR_ADDR;
  }
  if (! isConnected()) return CHT8310_ERROR_CONNECT;
  return CHT8310_OK;
}


bool CHT8310::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t CHT8310::getAddress()
{
  return _address;
}


////////////////////////////////////////////////
//
//  READ THE SENSOR
//
int CHT8310::read()
{
  //  do not read too fast
  if (millis() - _lastRead < 1000)
  {
    return CHT8310_ERROR_LASTREAD;
  }
  _lastRead = millis();

  uint8_t data[4] = { 0, 0, 0, 0 };
  _readRegister(CHT8310_REG_TEMPERATURE, &data[0], 4);

  //  DATASHEET P13
  int16_t tmp = (data[0] << 8 | data[1]);
  if (_resolution == 13)
  {
    _temperature = (tmp >> 3) * 0.03125;
  }
  else  //  _resolution == 14
  {
    _temperature = (tmp >> 2) * 0.03125;
  }
  //  DATASHEET P14
  tmp = data[2] << 8 | data[3];
  _humidity = tmp * (1.0 / 327.67);  //  == / 32767 * 100%

  if (_tempOffset != 0.0) _temperature += _tempOffset;
  if (_humOffset  != 0.0)
  {
    _humidity += _humOffset;
    if (_humidity < 0.0)   _humidity = 0.0;
    if (_humidity > 100.0) _humidity = 100.0;
  }

  return CHT8310_OK;
}


int CHT8310::readTemperature()
{
  //  do not read too fast
  if (millis() - _lastRead < 1000)
  {
    return CHT8310_ERROR_LASTREAD;
  }
  _lastRead = millis();

  uint8_t data[2] = { 0, 0 };
  _readRegister(CHT8310_REG_TEMPERATURE, &data[0], 2);

  //  DATASHEET P13
  int16_t tmp = (data[0] << 8 | data[1]);
  if (_resolution == 13)
  {
    _temperature = (tmp >> 3) * 0.03125;
  }
  else  //  _resolution == 14
  {
    _temperature = (tmp >> 2) * 0.03125;
  }

  if (_tempOffset != 0.0)
  {
    _temperature += _tempOffset;
  }

  return CHT8310_OK;
}


int CHT8310::readHumidity()
{
  //  do not read too fast
  if (millis() - _lastRead < 1000)
  {
    return CHT8310_ERROR_LASTREAD;
  }
  _lastRead = millis();

  uint8_t data[2] = { 0, 0 };
  _readRegister(CHT8310_REG_HUMIDITY, &data[0], 2);

  //  DATASHEET P14
  int16_t tmp = data[0] << 8 | data[1];
  _humidity = tmp * (1.0 / 327.67);  //  == / 32767 * 100%

  if (_humOffset != 0.0)
  {
    _humidity += _humOffset;
    if (_humidity < 0.0)   _humidity = 0.0;
    if (_humidity > 100.0) _humidity = 100.0;
  }

  return CHT8310_OK;
}


//  MilliSeconds since start sketch
uint32_t CHT8310::lastRead()
{
  return _lastRead;
}


float CHT8310::getHumidity()
{
  return _humidity;
}


float CHT8310::getTemperature()
{
  return _temperature;
}


void CHT8310::setConversionDelay(uint8_t cd)
{
  if (cd < 8) cd = 8;
  _conversionDelay = cd;
}


uint8_t CHT8310::getConversionDelay()
{
  return _conversionDelay;
}


void CHT8310::setHumidityOffset(float offset)
{
  _humOffset = offset;
}


void CHT8310::setTemperatureOffset(float offset)
{
  _tempOffset = offset;
}


float CHT8310::getHumidityOffset()
{
  return _humOffset;
}


float CHT8310::getTemperatureOffset()
{
  return _tempOffset;
}


////////////////////////////////////////////////
//
//  META DATA
//
uint16_t CHT8310::getManufacturer()
{
  uint8_t data[2] = { 0, 0 };
  _readRegister(CHT8310_REG_MANUFACTURER, &data[0], 2);
  uint16_t tmp = data[0] << 8 | data[1];
  return tmp;
}


////////////////////////////////////////////////
//
//  ACCESS REGISTERS
//
uint16_t CHT8310::readRegister(uint8_t reg)
{
  uint8_t data[2] = { 0, 0 };
  _readRegister(reg, &data[0], 2);
  uint16_t tmp = data[0] << 8 | data[1];
  return tmp;
}


int CHT8310::writeRegister(uint8_t reg, uint16_t value)
{
  uint8_t data[2];
  data[0] = value & 0xFF;
  data[1] = value >> 8;
  return _writeRegister(reg, data, 2);
}


////////////////////////////////////////////////
//
//  PRIVATE
//
int CHT8310::_readRegister(uint8_t reg, uint8_t * buf, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  int n = _wire->endTransmission();
  if (n != 0) return CHT8310_ERROR_I2C;

  if (reg == CHT8310_REG_TEMPERATURE)  //  wait for conversion...
  {
    delay(_conversionDelay);  //  2x 6.5 ms @ 14 bit = 14  (10 works).
  }

  n = _wire->requestFrom(_address, size);
  if (n == size)
  {
    for (uint8_t i = 0; i < size; i++)
    {
      buf[i] = _wire->read();
    }
  }
  return CHT8310_OK;
}


int CHT8310::_writeRegister(uint8_t reg, uint8_t * buf, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(reg);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(buf[i]);
  }
  int n = _wire->endTransmission();
  if (n != 0) return CHT8310_ERROR_I2C;
  return CHT8310_OK;
}


//  -- END OF FILE --

