//
//    FILE: DHT20.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: Arduino library for DHT20 I2C temperature and humidity sensor.


#include "DHT20.h"


//  set DHT20_WIRE_TIME_OUT to 0 to disable.
//  note this timeout is commented in code below.
#define DHT20_WIRE_TIME_OUT         250000    //  microseconds

const uint8_t DHT20_ADDRESS = 0x38;


DHT20::DHT20(TwoWire *wire)
{
  _wire        = wire;
  //  reset() ?
  _temperature = 0;
  _humidity    = 0;
  _humOffset   = 0;
  _tempOffset  = 0;
  _status      = DHT20_OK;
  _lastRequest = 0;
  _lastRead    = 0;
}


bool DHT20::begin()
{
  _wire->begin();
  //  _wire->setWireTimeout(DHT20_WIRE_TIME_OUT, true);
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
  //  _wire->setWireTimeout(DHT20_WIRE_TIME_OUT, true);
  return isConnected();
}
#endif


bool DHT20::isConnected()
{
  _wire->beginTransmission(DHT20_ADDRESS);
  int rv = _wire->endTransmission();
  return rv == 0;
}


uint8_t DHT20::getAddress()
{
  return DHT20_ADDRESS;
}


//  See datasheet 7.4 Sensor Reading Process, point 1
//  use with care.
uint8_t DHT20::resetSensor()
{
  uint8_t count = 255;
  if ((readStatus() & 0x18) != 0x18)
  {
    count++;
    if (_resetRegister(0x1B)) count++;
    if (_resetRegister(0x1C)) count++;
    if (_resetRegister(0x1E)) count++;
    delay(10);
  }
  return count;
}


////////////////////////////////////////////////
//
//  READ THE SENSOR
//
int DHT20::read()
{
  //  do not read to fast == more than once per second.
  if (millis() - _lastRead < 1000)
  {
    return DHT20_ERROR_LASTREAD;
  }

  int status = requestData();
  if (status < 0) return status;
  //  wait for measurement ready
  while (isMeasuring())
  {
    yield();
  }
  //  read the measurement
  status = readData();
  if (status < 0) return status;

  //  convert it to meaningful data
  return convert();
}


int DHT20::requestData()
{
  //  reset sensor if needed.
  resetSensor();

  //  GET CONNECTION
  _wire->beginTransmission(DHT20_ADDRESS);
  _wire->write(0xAC);
  _wire->write(0x33);
  _wire->write(0x00);
  int rv = _wire->endTransmission();

  _lastRequest = millis();
  return rv;
}


int DHT20::readData()
{
  //  GET DATA
  const uint8_t length = 7;
  int bytes = _wire->requestFrom(DHT20_ADDRESS, length);

  if (bytes == 0)     return DHT20_ERROR_CONNECT;
  if (bytes < length) return DHT20_MISSING_BYTES;

  bool allZero = true;
  for (int i = 0; i < bytes; i++)
  {
    _bits[i] = _wire->read();
    //  if (_bits[i] < 0x10) Serial.print(0);
    //  Serial.print(_bits[i], HEX);
    //  Serial.print(" ");
    allZero = allZero && (_bits[i] == 0);
  }
  //  Serial.println();
  if (allZero) return DHT20_ERROR_BYTES_ALL_ZERO;

  _lastRead = millis();
  return bytes;
}


int DHT20::convert()
{
  //  CONVERT AND STORE
  _status      = _bits[0];
  uint32_t raw = _bits[1];
  raw <<= 8;
  raw += _bits[2];
  raw <<= 4;
  raw += (_bits[3] >> 4);
  _humidity = raw * 9.5367431640625e-5;   // ==> / 1048576.0 * 100%;

  raw = (_bits[3] & 0x0F);
  raw <<= 8;
  raw += _bits[4];
  raw <<= 8;
  raw += _bits[5];
  _temperature = raw * 1.9073486328125e-4 - 50;  //  ==> / 1048576.0 * 200 - 50;

  //  TEST CHECKSUM
  uint8_t _crc = _crc8(_bits, 6);
  //  Serial.print(_crc, HEX);
  //  Serial.print("\t");
  //  Serial.println(_bits[6], HEX);
  if (_crc != _bits[6]) return DHT20_ERROR_CHECKSUM;

  return DHT20_OK;
}


////////////////////////////////////////////////
//
//  TEMPERATURE & HUMIDITY & OFFSET
//
float DHT20::getHumidity()
{
  return _humidity + _humOffset;
};


float DHT20::getTemperature()
{
  return _temperature + _tempOffset;
};


void DHT20::setHumOffset(float offset)
{
  _humOffset = offset;
};


void DHT20::setTempOffset(float offset)
{
  _tempOffset = offset;
};


float DHT20::getHumOffset()
{
  return _humOffset;
};


float DHT20::getTempOffset()
{
  return _tempOffset;
};


////////////////////////////////////////////////
//
//  STATUS
//
uint8_t DHT20::readStatus()
{
  _wire->requestFrom(DHT20_ADDRESS, (uint8_t)1);
  delay(1);  //  needed to stabilize timing
  return (uint8_t) _wire->read();
}


bool DHT20::isCalibrated()
{
  return (readStatus() & 0x08) == 0x08;
}


bool DHT20::isMeasuring()
{
  return (readStatus() & 0x80) == 0x80;
}


bool DHT20::isIdle()
{
  return (readStatus() & 0x80) == 0x00;
}


int DHT20::internalStatus()
{
  return _status;
};


////////////////////////////////////////////////
//
//  TIMING
//
uint32_t DHT20::lastRead()
{
  return _lastRead;
};


uint32_t DHT20::lastRequest()
{
  return _lastRequest;
};


////////////////////////////////////////////////
//
//  PRIVATE
//
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


//  Code based on demo code sent by www.aosong.com
//  no further documentation.
//  0x1B returned 18, 0, 4
//  0x1C returned 18, 65, 0
//  0x1E returned 18, 8, 0
//    18 seems to be status register
//    other values unknown.
bool DHT20::_resetRegister(uint8_t reg)
{
  uint8_t value[3];
  _wire->beginTransmission(DHT20_ADDRESS);
  _wire->write(reg);
  _wire->write(0x00);
  _wire->write(0x00);
  if (_wire->endTransmission() != 0) return false;
  delay(5);

  int bytes = _wire->requestFrom(DHT20_ADDRESS, (uint8_t)3);
  for (int i = 0; i < bytes; i++)
  {
    value[i] = _wire->read();
    //  Serial.println(value[i], HEX);
  }
  delay(10);

  _wire->beginTransmission(DHT20_ADDRESS);
  _wire->write(0xB0 | reg);
  _wire->write(value[1]);
  _wire->write(value[2]);
  if (_wire->endTransmission() != 0) return false;
  delay(5);
  return true;
}


// -- END OF FILE --

