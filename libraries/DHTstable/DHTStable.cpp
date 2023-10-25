//
//    FILE: DHTStable.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 1.1.2
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: https://github.com/RobTillaart/DHTstable
//
// HISTORY: see CHANGELOG.md


#include "DHTStable.h"


/////////////////////////////////////////////////////
//
//  PUBLIC
//
DHTStable::DHTStable()
{
  reset();
}


void DHTStable::reset()
{
  _temperature = 0.0;
  _humidity = 0.0;
  _disableIRQ = false;
}


//  return values:
//  DHTLIB_OK
//  DHTLIB_ERROR_CHECKSUM
//  DHTLIB_ERROR_TIMEOUT
int DHTStable::read11(uint8_t pin)
{
  //  READ VALUES
  if (_disableIRQ) noInterrupts();
  int rv = _readSensor(pin, DHTLIB_DHT11_WAKEUP);
  if (_disableIRQ) interrupts();
  if (rv != DHTLIB_OK)
  {
    _humidity    = DHTLIB_INVALID_VALUE;  //  invalid value, or is NaN prefered?
    _temperature = DHTLIB_INVALID_VALUE;  //  invalid value
    return rv;
  }

  //  CONVERT AND STORE
  _humidity = _bits[0] + _bits[1] * 0.1;
  _temperature = (_bits[2] & 0x7F) + _bits[3] * 0.1;
  if (_bits[2] & 0x80)  //  negative temperature
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


//  return values:
//  DHTLIB_OK
//  DHTLIB_ERROR_CHECKSUM
//  DHTLIB_ERROR_TIMEOUT
int DHTStable::read(uint8_t pin)
{
  //  READ VALUES
  if (_disableIRQ) noInterrupts();
  int rv = _readSensor(pin, DHTLIB_DHT_WAKEUP);
  if (_disableIRQ) interrupts();
  if (rv != DHTLIB_OK)
  {
    _humidity    = DHTLIB_INVALID_VALUE;  //  NaN preferred?
    _temperature = DHTLIB_INVALID_VALUE;  //  NaN preferred?
    return rv;  //  propagate error value
  }
  //  CONVERT AND STORE
  _humidity  = word(_bits[0], _bits[1]) * 0.1;
  int16_t t = ((_bits[2] & 0x7F) * 256 + _bits[3]);
  if (t == 0)
  {
    _temperature = 0.0;     //  prevent -0.0;
  }
  else
  {
    _temperature = t * 0.1;
    if((_bits[2] & 0x80) == 0x80 )
    {
      _temperature = -_temperature;
    }
  }
  //  TEST CHECKSUM
  uint8_t sum = _bits[0] + _bits[1] + _bits[2] + _bits[3];
  if (_bits[4] != sum)
  {
    return DHTLIB_ERROR_CHECKSUM;
  }
  return DHTLIB_OK;
}


/////////////////////////////////////////////////////
//
//  PRIVATE
//

//  return values:
//  DHTLIB_OK
//  DHTLIB_ERROR_TIMEOUT
int DHTStable::_readSensor(uint8_t pin, uint8_t wakeupDelay)
{
  //  INIT BUFFERVAR TO RECEIVE DATA
  uint8_t mask = 128;
  uint8_t idx = 0;

  //  EMPTY BUFFER
  for (uint8_t i = 0; i < 5; i++) _bits[i] = 0;

  //  REQUEST SAMPLE
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(wakeupDelay);
  pinMode(pin, INPUT);
  delayMicroseconds(40);

  //  GET ACKNOWLEDGE or TIMEOUT
  uint16_t loopCnt = DHTLIB_TIMEOUT;
  while(digitalRead(pin) == LOW)
  {
    if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
  }

  loopCnt = DHTLIB_TIMEOUT;
  while(digitalRead(pin) == HIGH)
  {
    if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
  }

  //  READ THE OUTPUT - 40 _bits => 5 BYTES
  for (uint8_t i = 40; i != 0; i--)
  {
    loopCnt = DHTLIB_TIMEOUT;
    while(digitalRead(pin) == LOW)
    {
      if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    uint32_t t = micros();

    loopCnt = DHTLIB_TIMEOUT;
    while(digitalRead(pin) == HIGH)
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


//  -- END OF FILE --
