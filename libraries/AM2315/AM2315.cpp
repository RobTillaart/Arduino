//
//    FILE: AM2315.cpp
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.1
// PURPOSE: AM2315 Temperature and Humidity sensor library for Arduino
//     URL: https://github.com/RobTillaart/AM2315
//
//  HISTORY:
//  0.1.0  2022-01-05  initial version
//  0.1.1  2022-01-11  fix handshake.


#include "AM2315.h"


// these defines are not for user to adjust
// READ_DELAY for blocking read
#define AM2315_READ_DELAY                     2000

#define AM2315_ADDRESS                        0x5C



/////////////////////////////////////////////////////
//
// PUBLIC
//
AM2315::AM2315(TwoWire *wire)
{
  _wire        = wire;
  _temperature = 0;
  _humidity    = 0;
  _humOffset   = 0;
  _tempOffset  = 0;
};


#if defined(ESP8266) || defined(ESP32)
bool AM2315::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  return isConnected();
}
#endif


bool AM2315::begin()
{
  _wire->begin();
  return isConnected();
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


int AM2315::read()
{
  // reset readDelay
  if (_readDelay == 0) _readDelay = AM2315_READ_DELAY;
  while (millis() - _lastRead < _readDelay)
  {
    if (!_waitForRead) return AM2315_WAITING_FOR_READ;
    yield();
  }
  int rv = _read();
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
int AM2315::_read()
{
  // READ VALUES
  int rv = _readSensor();

  _lastRead = millis();

  if (rv != AM2315_OK)
  {
    if (_suppressError == false)
    {
      _humidity    = AM2315_INVALID_VALUE;
      _temperature = AM2315_INVALID_VALUE;
    }
    return rv;  // propagate error value
  }

  _humidity = (_bits[0] * 256 + _bits[1]) * 0.1;
  int16_t t = ((_bits[2] & 0x7F) * 256 + _bits[3]);
  if (t == 0)
  {
    _temperature = 0.0;     // prevent -0.0;
  }
  else
  {
    _temperature = t * 0.1;
    if ((_bits[2] & 0x80) == 0x80 )
    {
      _temperature = -_temperature;
    }
  }

  // TEST OUT OF RANGE
#ifdef AM2315_VALUE_OUT_OF_RANGE
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


/////////////////////////////////////////////////////
//
// PRIVATE
//

// return values:
//    AM2315_OK
//    AM2315_ERROR_CONNECT
//    AM2315_MISSING_BYTES
//    AM2315_ERROR_CHECKSUM;
int AM2315::_readSensor()
{
  // EMPTY BUFFER
  for (uint8_t i = 0; i < 5; i++) _bits[i] = 0;

  // HANDLE PENDING IRQ
  yield();

  // WAKE UP the sensor
  _wire->beginTransmission(AM2315_ADDRESS);
  for (int i = 0; i < 10; i++) _wire->write(0);
  int rv = _wire->endTransmission();
  if (rv < 0) return rv;

  // REQUEST DATA
  _wire->beginTransmission(AM2315_ADDRESS);
  _wire->write(0X03);
  _wire->write(0);
  _wire->write(4);
  rv = _wire->endTransmission();
  if (rv < 0) return rv;

  delayMicroseconds(1500);
  // GET DATA
  const int length = 8;
  int bytes = _wire->requestFrom(AM2315_ADDRESS, length);
  if (bytes == 0)     return AM2315_ERROR_CONNECT;
  if (bytes < length) return AM2315_MISSING_BYTES;

  uint8_t buffer[12];
  for (int i = 0; i < bytes; i++)
  {
    buffer[i] = _wire->read();
  }
  _bits[0] = buffer[2];
  _bits[1] = buffer[3];
  _bits[2] = buffer[4];
  _bits[3] = buffer[5];

  // TEST CHECKSUM
  uint16_t crc0 = buffer[7] * 256 + buffer[6];
  uint16_t crc1 = _crc16(buffer, bytes - 2);
  // Serial.print("CRC: ");
  // Serial.print(crc0 - crc1);
  // Serial.print("\t");
  // Serial.print(crc1);
  // Serial.println();
  if (crc0 != crc1) return AM2315_ERROR_CHECKSUM;

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
      if(crc & 0x01)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
      {
        crc>>=1;
      }
    }
  }
  return crc;
}


// -- END OF FILE --

