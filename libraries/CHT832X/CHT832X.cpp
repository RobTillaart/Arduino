//
//    FILE: CHT832X.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.1
//    DATE: 2024-12-29
// PURPOSE: Arduino library for CHT832X temperature and humidity sensor
//     URL: https://github.com/RobTillaart/CHT832X


#include "CHT832X.h"


//  COMMANDS datasheet  Page 12/13
const uint16_t CHT832X_CMD_SINGLE_SHOT       = 0x2400;

const uint16_t CHT832X_CMD_ENABLE_HEATER     = 0x306D;
const uint16_t CHT832X_CMD_DISABLE_HEATER    = 0x3066;
const uint16_t CHT832X_CMD_CONFIG_HEATER     = 0x306E;

const uint16_t CHT832X_CMD_READ_STATUS       = 0xF32D;
const uint16_t CHT832X_CMD_CLEAR_STATUS      = 0x3041;

const uint16_t CHT832X_CMD_SOFTWARE_RESET    = 0x30A2;

const uint16_t CHT832X_CMD_READ_NIST_BASE    = 0x3683;
const uint16_t CHT832X_CMD_READ_MANUFACTURER = 0x3781;


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
    _error = CHT832X_ERROR_ADDR;
    return _error;
  }
  if (! isConnected())
  {
    _error = CHT832X_ERROR_CONNECT;
    return _error;
  }
  _error = CHT832X_OK;
  return _error;
}


bool CHT832X::isConnected()
{
  _wire->beginTransmission(_address);
  int rv = _wire->endTransmission();
  //  Serial.println(rv);
  return (rv == 0);
}


uint8_t CHT832X::getAddress()
{
  return _address;
}


////////////////////////////////////////////////
//
//  READ THE SENSOR - ASYNC INTERFACE
//
int CHT832X::requestData()
{
  _writeCommand(CHT832X_CMD_SINGLE_SHOT);
  _lastRequest = millis();
  return _error;
}


bool CHT832X::dataReady()
{
  return ((millis() - _lastRequest) > CHT832X_READ_DELAY);
}


int CHT832X::readData()
{
  uint8_t data[6] = { 0, 0, 0, 0, 0, 0 };
  _readBytes((uint8_t*) data, 6);
  if (_error != CHT832X_OK)
  {
    return _error;
  }

  _lastRead = millis();

  //  TEMPERATURE PART
  _error = CHT832X_OK;
  const float Tfactor = 175.0f / 65535.0f;
  uint16_t tmp = (data[0] << 8 | data[1]);
  _temperature = -45 + Tfactor * tmp;
  //  Handle temperature offset.
  if (_tempOffset != 0.0f)
  {
    _temperature += _tempOffset;
  }
  //  CHECK CRC TEMPERATURE
  if (_crc8(tmp) != data[2])
  {
    _error = CHT832X_ERROR_CRC;
    //  fall through as value might be correct.
  }

  //  HUMIDITY PART
  const float Hfactor = 100.0f / 65535.0f;
  uint16_t tmp2 = (data[3] << 8 | data[4]);
  _humidity = Hfactor * tmp2;
  if (_humOffset != 0.0f)
  {
    _humidity += _humOffset;
    //  handle out of range - clipping.
    if (_humidity < 0.0f)   _humidity = 0.0f;
    if (_humidity > 100.0f) _humidity = 100.0f;
  }
  //  CHECK CRC HUMIDITY
  if (_crc8(tmp) != data[5])
  {
    _error = CHT832X_ERROR_CRC;
    //  fall through as value might be correct.
  }
  return _error;
}


////////////////////////////////////////////////
//
//  READ THE SENSOR - SYNC INTERFACE
//
int CHT832X::read()
{
  //  do not read too fast
  if (millis() - _lastRead < 1000)
  {
    _error = CHT832X_ERROR_LASTREAD;
    return _error;
  }

  if (requestData() != CHT832X_OK)
  {
    return _error;
  }
  while (dataReady() == false)
  {
    yield();
    delay(1);
  }
  if (readData() != CHT832X_OK)
  {
    return _error;
  }
  _error = CHT832X_OK;
  return _error;
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
//  HEATER - datasheet Page 16/17
//
void CHT832X::enableHeater()
{
  _writeCommand(CHT832X_CMD_ENABLE_HEATER);
}


void CHT832X::enableHeaterFull()
{
  uint8_t buffer[3] = {0x3F, 0xFF, 0x06};
  _writeCommand(CHT832X_CMD_CONFIG_HEATER, buffer, 3);
}


void CHT832X::enableHeaterHalf()
{
  uint8_t buffer[3] = {0x03, 0xFF, 0x00};
  _writeCommand(CHT832X_CMD_CONFIG_HEATER, buffer, 3);
}


void CHT832X::enableHeaterQuarter()
{
  uint8_t buffer[3] = {0x00, 0x9F, 0x96};
  _writeCommand(CHT832X_CMD_CONFIG_HEATER, buffer, 3);
}


void CHT832X::disableHeater()
{
  _writeCommand(CHT832X_CMD_DISABLE_HEATER);
}


////////////////////////////////////////////////
//
//  STATUS - datasheet Page 17
//
uint16_t CHT832X::getStatusRegister()
{
  uint8_t buffer[3] = {0, 0, 0};
  _writeCommand(CHT832X_CMD_READ_STATUS);
  _readBytes(buffer, 3);
  uint16_t value = buffer[0] * 256 + buffer[1];
  //  check CRC.
  if (_crc8(value) != buffer[2])
  {
    _error = CHT832X_ERROR_CRC;
    //  Serial.println("debug: CRC-error");
  }
  //  mask reserved bits? (Page 17)
  //  value &= 0x2013
  return value;
}


void CHT832X::clearStatusRegister()
{
  _writeCommand(CHT832X_CMD_CLEAR_STATUS);
}


////////////////////////////////////////////////
//
//  SOFTWARE RESET
//
void CHT832X::softwareReset()
{
  _writeCommand(CHT832X_CMD_SOFTWARE_RESET);
}


////////////////////////////////////////////////
//
//  META DATA
//
uint16_t CHT832X::getNIST(uint8_t id)
{
  if (id > 2) return 0;
  uint8_t buffer[3] = {0, 0, 0};
  _writeCommand(CHT832X_CMD_READ_NIST_BASE + id);
  _readBytes(buffer, 3);
  uint16_t value = buffer[0] * 256 + buffer[1];
  //  check CRC.
  _error = CHT832X_OK;
  if (_crc8(value) != buffer[2])
  {
    _error = CHT832X_ERROR_CRC;
    //  Serial.println("debug: CRC-error");
  }
  return value;
}

uint16_t CHT832X::getManufacturer()
{
  uint8_t buffer[3] = {0, 0, 0};
  _writeCommand(CHT832X_CMD_READ_MANUFACTURER);
  _readBytes(buffer, 3);
  uint16_t value = buffer[0] * 256 + buffer[1];
  //  check CRC.
  _error = CHT832X_OK;
  if (_crc8(value) != buffer[2])
  {
    _error = CHT832X_ERROR_CRC;
    //  Serial.println("debug: CRC-error");
  }
  return value;
}


int CHT832X::getError()
{
  int e = _error;
  _error = CHT832X_OK;
  return e;
}


////////////////////////////////////////////////
//
//  PRIVATE
//
int CHT832X::_writeCommand(uint16_t command, uint8_t * buffer, uint8_t size)
{
  _wire->beginTransmission(_address);
  _wire->write(command >> 8);
  _wire->write(command & 0xFF);
  for (uint8_t i = 0; i < size; i++)
  {
    _wire->write(buffer[i]);
  }
  int n = _wire->endTransmission();
  if (n != 0)
  {
    //  Serial.println(n);
    _error = CHT832X_ERROR_I2C;
    return _error;
  }
  _error = CHT832X_OK;
  return _error;
}


int CHT832X::_readBytes(uint8_t * buffer, uint8_t size)
{
  int n = _wire->requestFrom(_address, size);
  if (n != size)
  {
    _error = CHT832X_ERROR_I2C;
    return _error;
  }

  for (uint8_t i = 0; i < size; i++)
  {
    buffer[i] = _wire->read();
  }
  _error = CHT832X_OK;
  return _error;
}


uint8_t CHT832X::_crc8(uint16_t data)
{
  uint8_t _crc = 0xFF;
  uint8_t value = (data >> 8);  //  MSB first
  uint8_t n = 2;
  while (n--)
  {
    _crc ^= value;
    for (uint8_t i = 8; i; i--)
    {
      if (_crc & (1 << 7))
      {
        _crc <<= 1;
        _crc ^= 0x31;
      }
      else
      {
        _crc <<= 1;
      }
    }
    value = (data & 0xFF);  //  LSB
  }
  return _crc;
}


//////////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
CHT8320::CHT8320(const uint8_t address, TwoWire *wire)
        :CHT832X(address, wire)
{
  //  type?
}

CHT8325::CHT8325(const uint8_t address, TwoWire *wire)
        :CHT832X(address, wire)
{
}



//  -- END OF FILE --

