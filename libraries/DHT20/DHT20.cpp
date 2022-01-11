//
//    FILE: DHT20.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for DHT20 I2C temperature and humidity sensor.
//
// HISTORY:
//  0.1.0   2022-01-11  initial version (based upon DHT20)



#include "DHT20.h"

const uint8_t DHT20_ADDRESS = 0x38;


DHT20::DHT20(TwoWire *wire)
{
  _wire        = wire;
  //  reset() ?
  _temperature = 0;
  _humidity    = 0;
  _humOffset   = 0;
  _tempOffset  = 0;
  _status      = 0;
  _lastRequest = 0;
  _lastRead    = 0;
}


bool DHT20::begin()
{
  _wire->begin();
  return isConnected();
}


#if defined(ESP8266) || defined(ESP32)
bool DHT20::begin(const uint8_t dataPin, const uint8_t clockPin)
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


bool DHT20::isConnected()
{
  _wire->beginTransmission(DHT20_ADDRESS);
  int rv = _wire->endTransmission();
  return rv == 0;
}


bool DHT20::readyData()
{
  return ((millis() - _lastRequest) > 85);
}


int DHT20::read()
{
  // READ SENSOR ==> uses the async interface!
  int status = _requestData();
  if (status < 0) return status;
  while (!readyData())
  {
    yield();
    delay(1);
  }
  _readData();

  // CONVERT AND STORE
  _status      = _bits[0];
  uint32_t tmp = _bits[1];
  tmp <<= 8;
  tmp += _bits[2];
  tmp <<= 4;
  tmp += (_bits[3] >> 4);
  _humidity = tmp * 9.5367431640625e-5;   // ==> / 1048576.0 * 100%;

  tmp = (_bits[3] & 0x0F);
  tmp <<= 8;
  tmp += _bits[4];
  tmp <<= 8;
  tmp += _bits[5];
  _temperature = tmp * 1.9073486328125e-4 - 50;  //  ==> / 1048576.0 * 200 - 50;

  // TEST CHECKSUM
  uint8_t _crc = _crc8(_bits, 6);
  // Serial.print(_crc, HEX);
  // Serial.print("\t");
  // Serial.println(_bits[6], HEX);
  if (_crc != _bits[6]) return DHT20_ERROR_CHECKSUM;

  return DHT20_OK;
}


int DHT20::_requestData()
{
  // GET CONNECTION
  _wire->beginTransmission(DHT20_ADDRESS);
  _wire->write(0xAC);
  _wire->write(0x33);
  _wire->write(0x00);
  int rv = _wire->endTransmission();

  _lastRequest = millis();
  return rv;
}


int DHT20::_readData()
{
  // GET DATA
  const uint8_t length = 7;
  int bytes = _wire->requestFrom(DHT20_ADDRESS, length);

  if (bytes == 0)     return DHT20_ERROR_CONNECT;
  if (bytes < length) return DHT20_MISSING_BYTES;

  for (int i = 0; i < bytes; i++)
  {
    _bits[i] = _wire->read();
    // if (_bits[i] < 0x10) Serial.print(0);
    // Serial.print(_bits[i], HEX);
    // Serial.print(" ");
  }
  // Serial.println();

  _lastRead = millis();
  return bytes;
}


int DHT20::_readStatus()
{
  // GET CONNECTION
  _wire->beginTransmission(DHT20_ADDRESS);
  _wire->write(0xAC);
  _wire->write(0x71);
  _wire->write(0x00);
  return _wire->endTransmission();

  _wire->requestFrom(DHT20_ADDRESS, (uint8_t)1);
}


uint8_t DHT20::_crc8(uint8_t *ptr, uint8_t len)
{
  uint8_t crc = 0xFF;
  while(len--)
  {
    crc ^= *ptr++;
    for (uint8_t i = 0; i < 8; i++)
    {
      if (crc & 0x80)
      {
        crc <<= 1;
        crc ^= 0x31;
      }
      else
      {
        crc <<= 1;
      }
    }
  }
  return crc;
}


// -- END OF FILE --

