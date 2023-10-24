//
//    FILE: DHT2pin.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Experimental DHT _temperature & _humidiy Sensor library for Arduino
//     URL: https://github.com/RobTillaart/DHT2pin
//          http://arduino.cc/playground/Main/DHTLib


#include "DHT2pin.h"


/////////////////////////////////////////////////////
//
//  PUBLIC
//
DHT2pin::DHT2pin(uint8_t rpin, uint8_t wpin)
{
  _rpin        = rpin;
  _wpin        = wpin;
  _temperature = 0;
  _humidity    = 0;
};


void DHT2pin::begin()
{
  pinMode(_rpin, INPUT);
  pinMode(_wpin, OUTPUT);
}


//  return values:
//  DHTLIB_OK
//  DHTLIB_ERROR_CHECKSUM
//  DHTLIB_ERROR_TIMEOUT
int DHT2pin::read11()
{
  //  READ VALUES
  int rv = _readSensor(DHTLIB_DHT11_WAKEUP);
  if (rv != DHTLIB_OK)
  {
    _humidity    = DHTLIB_INVALID_VALUE;
    _temperature = DHTLIB_INVALID_VALUE;
    return rv;
  }

  //  CONVERT AND STORE
  _humidity    = _bits[0];  //  _bits[1] == 0;
  _temperature = _bits[2];  //  _bits[3] == 0;

  //  TEST CHECKSUM
  //  _bits[1] && _bits[3] both 0
  uint8_t sum = _bits[0] + _bits[2];
  if (_bits[4] != sum) return DHTLIB_ERROR_CHECKSUM;

  return DHTLIB_OK;
}


//  return values:
//  DHTLIB_OK
//  DHTLIB_ERROR_CHECKSUM
//  DHTLIB_ERROR_TIMEOUT
int DHT2pin::read()
{
  //  READ VALUES
  int rv = _readSensor(DHTLIB_DHT_WAKEUP);
  if (rv != DHTLIB_OK)
  {
    _humidity    = DHTLIB_INVALID_VALUE;
    _temperature = DHTLIB_INVALID_VALUE;
    return rv;      //  propagate error value
  }

  //  CONVERT AND STORE
  _humidity = word(_bits[0], _bits[1]) * 0.1;
  _temperature = word(_bits[2] & 0x7F, _bits[3]) * 0.1;
  if (_bits[2] & 0x80)     //  negative _temperature
  {
    _temperature = -_temperature;
  }

  //  TEST CHECKSUM
  uint8_t sum = _bits[0] + _bits[1] + _bits[2] + _bits[3];
  if (_bits[4] != sum)
  {
    return DHTLIB_ERROR_CHECKSUM;
  }
  return DHTLIB_OK;
}


float DHT2pin::temperature()
{
  return _temperature;
}


float DHT2pin::humidity()
{
  return _humidity;
}


/////////////////////////////////////////////////////
//
//  PRIVATE
//

//  return values:
//  DHTLIB_OK
//  DHTLIB_ERROR_TIMEOUT
int DHT2pin::_readSensor(uint8_t wakeupDelay)
{
  //  INIT BUFFERVAR TO RECEIVE DATA
  uint8_t mask = 128;
  uint8_t idx = 0;

  //  EMPTY BUFFER
  for (uint8_t i = 0; i < 5; i++) _bits[i] = 0;

  //  REQUEST SAMPLE
  digitalWrite(_wpin, LOW);
  delay(wakeupDelay);
  digitalWrite(_wpin, HIGH);
  delayMicroseconds(40);

  //  GET ACKNOWLEDGE or TIMEOUT
  uint16_t loopCnt = DHTLIB_TIMEOUT;
  while(digitalRead(_rpin) == LOW)
  {
      if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
  }

  loopCnt = DHTLIB_TIMEOUT;
  while(digitalRead(_rpin) == HIGH)
  {
      if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
  }

  // READ THE OUTPUT - 40 _bits => 5 BYTES
  for (uint8_t i = 40; i != 0; i--)
  {
    loopCnt = DHTLIB_TIMEOUT;
    while(digitalRead(_rpin) == LOW)
    {
      if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    uint32_t t = micros();

    loopCnt = DHTLIB_TIMEOUT;
    while(digitalRead(_rpin) == HIGH)
    {
      if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    if ((micros() - t) > 40)
    {
      _bits[idx] |= mask;
    }
    mask >>= 1;
    if (mask == 0)   //  next byte?
    {
      mask = 128;
      idx++;
    }
  }
  digitalWrite(_wpin, HIGH);

  return DHTLIB_OK;
}


//  -- END OF FILE --

