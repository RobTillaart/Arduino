//
//    FILE: CHT832X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for CHT832X temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CHT832X


#include "CHT832X.h"


//  COMMANDS
//  TODO magic numbers to descriptive const uint16_t variables.


/////////////////////////////////////////////////////
//
// PUBLIC
//
CHT832X::CHT832X(const uint8_t address, TwoWire *wire)
{
  _wire    = wire;
  _address = address;
}


int CHT832X::begin()
{
  //  check address range
  if ((_address < 0x44) || (_address > 0x47))
  {
    return CHT832X_ERROR_ADDR;
  }
  if (! isConnected()) return CHT832X_ERROR_CONNECT;
  return CHT832X_OK;
}


bool CHT832X::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t CHT832X::getAddress()
{
  return _address;
}


////////////////////////////////////////////////
//
//  READ THE SENSOR
//
int CHT832X::read()
{
  //  do not read too fast
  if (millis() - _lastRead < 1000)
  {
    return CHT832X_ERROR_LASTREAD;
  }
  _lastRead = millis();

  //  TEMPERATURE PART
  uint8_t data[6] = { 0, 0, 0, 0, 0, 0 };
  int status = _readRegister(0xE000, data, 6);
  if (status != CHT832X_OK)
  {
    return status;
  }

  //  DATASHEET P16
  //  TODO check CRC 0,1,2
  int16_t tmp = (data[0] << 8 | data[1]);
  _temperature = -45 + (175.0 / 65535) * tmp;
  //  Handle temperature offset.
  if (_tempOffset != 0.0)
  {
    _temperature += _tempOffset;
  }

  //  TODO check CRC 3,4,5
  tmp = (data[3] << 8 | data[4]);
  _humidity = (100.0 / 65535) * tmp;
  if (_humOffset  != 0.0)
  {
    _humidity += _humOffset;
    //  handle out of range.
    if (_humidity < 0.0)   _humidity = 0.0;
    if (_humidity > 100.0) _humidity = 100.0;
  }

  return CHT832X_OK;
}


uint32_t CHT832X::lastRead()
{
  return _lastRead;
}


float CHT832X::getHumidity()
{
  return _humidity;
}


float CHT832X::getTemperature()
{
  return _temperature;
}


////////////////////////////////////////////////
//
//  OFFSET
//
void CHT832X::setHumidityOffset(float offset)
{
  _humOffset = offset;
}


void CHT832X::setTemperatureOffset(float offset)
{
  _tempOffset = offset;
}


float CHT832X::getHumidityOffset()
{
  return _humOffset;
}


float CHT832X::getTemperatureOffset()
{
  return _tempOffset;
}


////////////////////////////////////////////////
//
//  HEATER - datasheet P17
//
void CHT832X::enableHeater()
{
  _writeRegister(0x306D, NULL, 0);
}


void CHT832X::enableHeaterFull()
{
  uint8_t buffer[3] = {0x3F, 0xFF, 0x06};
  _writeRegister(0x306E, buffer, 3);
}


void CHT832X::enableHeaterHalf()
{
  uint8_t buffer[3] = {0x03, 0xFF, 0x00};
  _writeRegister(0x306E, buffer, 3);
}


void CHT832X::enableHeaterQuarter()
{
  uint8_t buffer[3] = {0x00, 0x9F, 0x96};
  _writeRegister(0x306E, buffer, 3);
}


void CHT832X::disableHeater()
{
 _writeRegister(0x3066, NULL, 0);
}



////////////////////////////////////////////////
//
//  STATUS - datasheet P17
//
uint16_t CHT832X::getStatusRegister()
{
  uint8_t buffer[3] = {0, 0, 0};
  _readRegister(0xF32D, buffer, 3);
  //  TODO check CRC.
  uint16_t value = buffer[0] * 256 + buffer[1];
  //  mask all reserved bits?
  return value;
}


void CHT832X::clearStatusRegister()
{
  _writeRegister(0x3041, NULL, 0);
}


////////////////////////////////////////////////
//
//  SOFTWARE RESET
//
void CHT832X::softwareReset()
{
  _writeRegister(0x30A2, NULL, 0);
}


////////////////////////////////////////////////
//
//  META DATA
//
uint16_t CHT832X::getNIST(uint8_t id)
{
  if (id > 2) return 0;
  uint8_t buffer[3] = {0, 0, 0};
  _readRegister(0x3683 + id, buffer, 3);
  //  TODO check CRC.
  uint16_t value = buffer[0] * 256 + buffer[1];
  return value;
}

uint16_t CHT832X::getManufacturer()
{
  uint8_t buffer[3] = {0, 0};
  _readRegister(0x3781, buffer, 3);
  //  TODO check CRC.
  uint16_t value = buffer[0] * 256 + buffer[1];
  return value;
}


////////////////////////////////////////////////
//
//  PRIVATE
//
int CHT832X::_readRegister(uint16_t command, uint8_t * buf, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(command >> 8);
  _wire->write(command & 0xFF);
  int n = _wire->endTransmission();
  if (n != 0)
  {
    return CHT832X_ERROR_I2C;
  }

  n = _wire->requestFrom(_address, size);
  if (n != size)
  {
    return CHT832X_ERROR_I2C;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    buf[i] = _wire->read();
  }
  return CHT832X_OK;
}


int CHT832X::_writeRegister(uint16_t command, uint8_t * buf, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(command >> 8);
  _wire->write(command & 0xFF);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(buf[i]);
  }
  int n = _wire->endTransmission();
  if (n != 0)
  {
    return CHT832X_ERROR_I2C;
  }
  return CHT832X_OK;
}


//  -- END OF FILE --

