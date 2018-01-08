//
//    FILE: dhtnew.cpp
//  AUTHOR: Rob.Tillaart@gmail.com
// VERSION: 0.1.3
// PURPOSE: New DHT Temperature & Humidity Sensor library for Arduino
//     URL:
//
// HISTORY:
// 0.1.0  2017-07-24 initial version based upon DHTStable
// 0.1.1  2017-07-29 add begin() to determine type once and for all instead of every call + refactor
// 0.1.2  2018-01-08 improved begin() + refactor()
// 0.1.3  2018-01-08 removed begin() + moved detection to read() function
//
// Released to the public domain
//

#include "dhtnew.h"

/////////////////////////////////////////////////////
//
// PUBLIC
//
DHTNEW::DHTNEW(uint8_t pin) { _pin = pin; };

// return values:
// DHTLIB_OK
// DHTLIB_ERROR_CHECKSUM
// DHTLIB_ERROR_TIMEOUT
int DHTNEW::read()
{
  if (_type != 0) return _read();

  _type = 22;
  _wakeupDelay = DHTLIB_DHT_WAKEUP;
  int rv = _read();
  if (rv == DHTLIB_OK) return rv;

  _type = 11;
  _wakeupDelay = DHTLIB_DHT11_WAKEUP;
  rv = _read();
  if (rv == DHTLIB_OK) return rv;

  _type = 0; // retry next time
  return rv;
}

// return values:
// DHTLIB_OK
// DHTLIB_ERROR_CHECKSUM
// DHTLIB_ERROR_TIMEOUT
int DHTNEW::_read()
{
  _lastRead = millis();

  // READ VALUES
  int rv = _readSensor();
  if (rv != DHTLIB_OK)
  {
    humidity    = DHTLIB_INVALID_VALUE;
    temperature = DHTLIB_INVALID_VALUE;
    return rv; // propagate error value
  }

  if (_type == 22) // DHT22, DHT33, DHT44, compatible
  {
    humidity =    (_bits[0] * 256 + _bits[1]) * 0.1;
    temperature = (_bits[2] * 256 + _bits[3]) * 0.1;
  }
  else // if (_type == 11)  // DHT11, DH12, compatible
  {
    humidity = _bits[0] + _bits[1] * 0.1;
    temperature = _bits[2] + _bits[3] * 0.1;
  }

  if (_bits[2] & 0x80)  // negative temperature
  {
    temperature = -temperature;
  }
  humidity += _humOffset;       // check overflow ???
  temperature += _tempOffset;

  // TEST CHECKSUM
  uint8_t sum = _bits[0] + _bits[1] + _bits[2] + _bits[3];
  if (_bits[4] != sum)
  {
    return DHTLIB_ERROR_CHECKSUM;
  }
  return DHTLIB_OK;
}

/////////////////////////////////////////////////////
//
// PRIVATE
//

// return values:
// DHTLIB_OK
// DHTLIB_ERROR_TIMEOUT
int DHTNEW::_readSensor()
{
  // INIT BUFFERVAR TO RECEIVE DATA
  uint8_t mask = 128;
  uint8_t idx = 0;

  // EMPTY BUFFER
  for (uint8_t i = 0; i < 5; i++) _bits[i] = 0;

  // REQUEST SAMPLE
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(_wakeupDelay);
  pinMode(_pin, INPUT);
  delayMicroseconds(40);

  // GET ACKNOWLEDGE or TIMEOUT
  uint16_t loopCnt = DHTLIB_TIMEOUT;
  while(digitalRead(_pin) == LOW)
  {
    if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
  }

  loopCnt = DHTLIB_TIMEOUT;
  while(digitalRead(_pin) == HIGH)
  {
    if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
  }

  // READ THE OUTPUT - 40 BITS => 5 BYTES
  for (uint8_t i = 40; i != 0; i--)
  {
    loopCnt = DHTLIB_TIMEOUT;
    while(digitalRead(_pin) == LOW)
    {
      if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    uint32_t t = micros();

    loopCnt = DHTLIB_TIMEOUT;
    while(digitalRead(_pin) == HIGH)
    {
      if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    if ((micros() - t) > 40)
    {
      _bits[idx] |= mask;
    }
    mask >>= 1;
    if (mask == 0)   // next byte?
    {
      mask = 128;
      idx++;
    }
  }

  return DHTLIB_OK;
}
//
// END OF FILE
//