//
//    FILE: AM2315.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: AM2315 Temperature and Humidity sensor library for Arduino
//     URL: https://github.com/RobTillaart/AM2315


#include "AM2315.h"


const uint8_t AM2315_ADDRESS = 0x5C;

//  READ_DELAY for blocking read
const uint16_t AM2315_READ_DELAY = 2000;


/////////////////////////////////////////////////////
//
//  PUBLIC
//
AM2315::AM2315(TwoWire *wire)
{
  _wire          = wire;
  //  reset() or begin() ?
  _humidity      = 0.0;
  _temperature   = 0.0;
  _humOffset     = 0.0;
  _tempOffset    = 0.0;
  _lastRead      = 0;
  _waitForRead   = false;
  _suppressError = false;
}


bool AM2315::begin()
{
  if (! isConnected()) return false;
  this->read();
  return true;
}


bool AM2315::isConnected(uint16_t timeout)
{
  uint32_t start = micros();
  while (micros() - start < timeout)
  {
    _wire->beginTransmission(AM2315_ADDRESS);
    if ( _wire->endTransmission() == 0) return true;
    yield();
    delayMicroseconds(100);
  }
  return false;
}


//  return values:
//    AM2315_OK
//    AM2315_ERROR_CONNECT
//    AM2315_MISSING_BYTES
//    AM2315_ERROR_CHECKSUM;
//    AM2315_HUMIDITY_OUT_OF_RANGE
//    AM2315_TEMPERATURE_OUT_OF_RANGE
int AM2315::read()
{
  while (millis() - _lastRead < AM2315_READ_DELAY)
  {
    if (!_waitForRead) return AM2315_WAITING_FOR_READ;
    yield();
  }
  int rv = _read();
  _lastRead = millis();
  return rv;
}


float AM2315::getHumidity()
{
  float _hum = _humidity;
  if (_humOffset != 0.0) _hum += _humOffset;
  return _hum;
}


float AM2315::getTemperature()
{
  float _tem = _temperature;
  if (_tempOffset != 0.0) _tem += _tempOffset;
  return _tem;
}


///////////////////////////////////////////////////////////
//
//  PRIVATE
//

//  return values:
//    AM2315_OK
//    AM2315_ERROR_CONNECT
//    AM2315_MISSING_BYTES
//    AM2315_ERROR_CHECKSUM;
//    AM2315_HUMIDITY_OUT_OF_RANGE
//    AM2315_TEMPERATURE_OUT_OF_RANGE
int AM2315::_read()
{
  // READ VALUES
  int rv = _readSensor();

  if (rv != AM2315_OK)
  {
    if (_suppressError == false)
    {
      _humidity    = AM2315_INVALID_VALUE;
      _temperature = AM2315_INVALID_VALUE;
    }
    return rv;  //  propagate error value
  }

  //  EXTRACT HUMIDITY AND TEMPERATURE
  _humidity = (_bits[2] * 256 + _bits[3]) * 0.1;
  int16_t t = ((_bits[4] & 0x7F) * 256 + _bits[5]);
  if (t == 0)
  {
    _temperature = 0.0;     // prevent -0.0;
  }
  else
  {
    _temperature = t * 0.1;
    if ((_bits[4] & 0x80) == 0x80 )
    {
      _temperature = -_temperature;
    }
  }

#ifdef AM2315_VALUE_OUT_OF_RANGE
  //  TEST OUT OF RANGE
  if (_humidity > 100)
  {
    return AM2315_HUMIDITY_OUT_OF_RANGE;
  }
  if ((_temperature < -40) || (_temperature > 125))
  {
    return AM2315_TEMPERATURE_OUT_OF_RANGE;
  }
#endif

  return AM2315_OK;
}


//  return values:
//    AM2315_OK
//    AM2315_ERROR_CONNECT
//    AM2315_MISSING_BYTES
//    AM2315_ERROR_CHECKSUM;
int AM2315::_readSensor()
{
  //  HANDLE PENDING IRQ etc.
  yield();

  // WAKE UP the sensor
  if (! isConnected() ) return AM2315_ERROR_CONNECT;

  //  SEND COMMAND
  _wire->beginTransmission(AM2315_ADDRESS);
  _wire->write(0X03);
  _wire->write(0);
  _wire->write(4);
  int rv = _wire->endTransmission();
  if (rv < 0) return rv;

  //  REQUEST DATA
  const int length = 8;
  int bytes = _wire->requestFrom((int)AM2315_ADDRESS, length);
  if (bytes == 0)     return AM2315_ERROR_CONNECT;
  if (bytes < length) return AM2315_MISSING_BYTES;

  //  READ DATA
  for (int i = 0; i < bytes; i++)
  {
    _bits[i] = _wire->read();
  }

  //  TEST CHECKSUM
  uint16_t crc = _bits[bytes - 1] * 256 + _bits[bytes - 2];
  if (_crc16(_bits, bytes - 2) != crc)
  {
    return AM2315_ERROR_CHECKSUM;
  }
  return AM2315_OK;
}


uint16_t AM2315::_crc16(uint8_t *ptr, uint8_t len)
{
  uint16_t crc = 0xFFFF;
  while(len--)
  {
    crc ^= *ptr++;
    for (uint8_t i = 0; i < 8; i++)
    {
      if (crc & 0x01)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }
  return crc;
}


//  -- END OF FILE --

