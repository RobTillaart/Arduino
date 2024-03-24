//
//    FILE: dhtnew.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.20
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: https://github.com/RobTillaart/DHTNEW
//
//  HISTORY: see changelog.md


#include "dhtnew.h"
#include <stdint.h>


//  these defines are not for user to adjust (microseconds)
#define DHTLIB_DHT11_WAKEUP           (18 * 1100UL)
#define DHTLIB_DHT_WAKEUP             (1 * 1100UL)
//  experimental 0.4.14
#define DHTLIB_SI7021_WAKEUP          (500)


//  READ_DELAY for blocking read
//  datasheet: DHT11 = 1000 and DHT22 = 2000
//  use setReadDelay() to overrule (at own risk)
//  as individual sensors can be read faster.
//  see example DHTnew_setReadDelay.ino
#define DHTLIB_DHT11_READ_DELAY    1000
#define DHTLIB_DHT22_READ_DELAY    2000


/////////////////////////////////////////////////////
//
//  PUBLIC
//
DHTNEW::DHTNEW(uint8_t pin)
{
  _dataPin = pin;
  reset();
};


void DHTNEW::reset()
{
  //  Data-bus's free status is high voltage level.
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, HIGH);

  _wakeupDelay   = 0;
  _type          = 0;
  _humOffset     = 0.0;
  _tempOffset    = 0.0;
  _humidity      = 0.0;
  _temperature   = 0.0;
  _lastRead      = 0;
  _disableIRQ    = true;
  _waitForRead   = false;
  _suppressError = false;
  _readDelay     = 0;
#if defined(__AVR__)
  _disableIRQ    = false;
#endif
// #if defined(ARDUINO_SAMD_MKRWIFI1010)  //  fix for issue #67
  // _disableIRQ    = false;
// #endif
}


uint8_t DHTNEW::getType()
{
  if (_type == 0) read();
  return _type;
}


void DHTNEW::setType(uint8_t type)
{
  //  default type == 0  or  unsupported
  _type = 0;
  _wakeupDelay = DHTLIB_DHT11_WAKEUP;

  if ((type == 22) || (type == 23))
  {
    _type = type;
    _wakeupDelay = DHTLIB_DHT_WAKEUP;
  }
  else if (type == 11)
  {
    _type = type;
    _wakeupDelay = DHTLIB_DHT11_WAKEUP;
  }
  //  experimental 0.4.14
  else if (type == 70)
  {
    _type = type;
    _wakeupDelay = DHTLIB_SI7021_WAKEUP;
  }
}


//  return values:
//  DHTLIB_OK
//  DHTLIB_WAITING_FOR_READ
//  DHTLIB_ERROR_CHECKSUM
//  DHTLIB_ERROR_BIT_SHIFT
//  DHTLIB_ERROR_SENSOR_NOT_READY
//  DHTLIB_ERROR_TIMEOUT_A
//  DHTLIB_ERROR_TIMEOUT_B
//  DHTLIB_ERROR_TIMEOUT_C
//  DHTLIB_ERROR_TIMEOUT_D
int DHTNEW::read()
{
  if (_readDelay == 0)
  {
    _readDelay = DHTLIB_DHT22_READ_DELAY;
    if (_type == 11) _readDelay = DHTLIB_DHT11_READ_DELAY;
  }
  if (_type != 0)
  {
    while (millis() - _lastRead < _readDelay)
    {
      if (!_waitForRead) return DHTLIB_WAITING_FOR_READ;
      yield();
    }
    return _read();
  }

  //  AUTODETECT
  //  make sure sensor had time to wake up.
  while (millis() < 1000);

  //  NOTE: cannot differentiate between type 23 and 22
  _type = 22;
  _wakeupDelay = DHTLIB_DHT_WAKEUP;
  int rv = _read();
  if (rv == DHTLIB_OK) return rv;

  _type = 11;
  _wakeupDelay = DHTLIB_DHT11_WAKEUP;
  rv = _read();
  if (rv == DHTLIB_OK) return rv;

  //  experimental 0.4.14
  _type = 70;
  _wakeupDelay = DHTLIB_SI7021_WAKEUP;
  rv = _read();
  if (rv == DHTLIB_OK) return rv;

  _type = 0; // retry next time
  return rv;
}


//  return values:
//  DHTLIB_OK
//  DHTLIB_ERROR_CHECKSUM
//  DHTLIB_ERROR_BIT_SHIFT
//  DHTLIB_ERROR_SENSOR_NOT_READY
//  DHTLIB_ERROR_TIMEOUT_A
//  DHTLIB_ERROR_TIMEOUT_B
//  DHTLIB_ERROR_TIMEOUT_C
//  DHTLIB_ERROR_TIMEOUT_D
int DHTNEW::_read()
{
  //  READ VALUES
  int rv = _readSensor();

  //  enable interrupts again
#if defined(ESP32)
  portENABLE_INTERRUPTS();
#else
  interrupts();
#endif
  //  Data-bus's free status is high voltage level.
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, HIGH);
  _lastRead = millis();

  if (rv != DHTLIB_OK)
  {
    if (_suppressError == false)
    {
      _humidity    = DHTLIB_INVALID_VALUE;
      _temperature = DHTLIB_INVALID_VALUE;
    }
    return rv;        //  propagate error value
  }

  if (_type == 11)    //  DHT11, DH12, compatible
  {
    _humidity    = _bits[0] + _bits[1] * 0.1;
    _temperature = _bits[2] + _bits[3] * 0.1;
  }
  else               //  DHT22, DHT33, DHT44, compatible + Si7021
  {
    _humidity = (_bits[0] * 256 + _bits[1]) * 0.1;
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
  }


  //  HEXDUMP DEBUG
  /*
  Serial.println();
  //  CHECKSUM
  if (_bits[4] < 0x10) Serial.print(0);
  Serial.print(_bits[4], HEX);
  Serial.print("    ");
  //  TEMPERATURE
  if (_bits[2] < 0x10) Serial.print(0);
  Serial.print(_bits[2], HEX);
  if (_bits[3] < 0x10) Serial.print(0);
  Serial.print(_bits[3], HEX);
  Serial.print("    ");
  Serial.print(_temperature, 1);
  Serial.print("    ");
  //  HUMIDITY
  if (_bits[0] < 0x10) Serial.print(0);
  Serial.print(_bits[0], HEX);
  if (_bits[1] < 0x10) Serial.print(0);
  Serial.print(_bits[1], HEX);
  Serial.print("    ");
  Serial.print(_humidity, 1);
  */

  //  TEST OUT OF RANGE
#ifdef DHTLIB_VALUE_OUT_OF_RANGE
  if (_humidity > 100)
  {
    return DHTLIB_HUMIDITY_OUT_OF_RANGE;
  }
  if ((_temperature < -40) || (_temperature > 80))
  {
    return DHTLIB_TEMPERATURE_OUT_OF_RANGE;
  }
#endif

  if (_humOffset != 0.0)
  {
    _humidity += _humOffset;
    if (_humidity > 100)    _humidity = 100;
    else if (_humidity < 0) _humidity = 0;
  }
  if (_tempOffset != 0.0)
  {
    _temperature += _tempOffset;
  }

  //  TEST CHECKSUM
  uint8_t sum = _bits[0] + _bits[1] + _bits[2] + _bits[3];
  if (_bits[4] != sum)
  {
    return DHTLIB_ERROR_CHECKSUM;
  }

  return DHTLIB_OK;
}


void DHTNEW::powerUp()
{
  digitalWrite(_dataPin, HIGH);
  //  do a dummy read to synchronise the sensor
  read();
};


void DHTNEW::powerDown()
{
  digitalWrite(_dataPin, LOW);
}


/////////////////////////////////////////////////////
//
//  PRIVATE
//

//  return values:
//  DHTLIB_OK
//  DHTLIB_ERROR_CHECKSUM
//  DHTLIB_ERROR_BIT_SHIFT
//  DHTLIB_ERROR_SENSOR_NOT_READY
//  DHTLIB_ERROR_TIMEOUT_A
//  DHTLIB_ERROR_TIMEOUT_B
//  DHTLIB_ERROR_TIMEOUT_C
//  DHTLIB_ERROR_TIMEOUT_D
int DHTNEW::_readSensor()
{
  //  INIT BUFFERVAR TO RECEIVE DATA
  uint8_t mask = 0x80;
  uint8_t idx = 0;

  //  EMPTY BUFFER
  for (uint8_t i = 0; i < 5; i++)
  {
    _bits[i] = 0;
  }

  //  REQUEST SAMPLE - SEND WAKEUP TO SENSOR
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);

  //  HANDLE SI7021 separately (see #79)
  if (_type == 70)
  {
    delayMicroseconds(DHTLIB_SI7021_WAKEUP);  //  hardcoded for now
  }
  else
  {
    //  WAKE UP - add 10% extra for timing inaccuracies in sensor.
    uint32_t startWakeup = micros();
    do
    {
      //  HANDLE PENDING IRQ
      yield();
      //  180 gives good wakeup delay on UNO for DHT22 / DHT11 (issue #72)
      delayMicroseconds(180UL);
    }
    while((micros() - startWakeup) < _wakeupDelay);
  }

  //  HOST GIVES CONTROL TO SENSOR
  digitalWrite(_dataPin, HIGH);
  delayMicroseconds(2);
  pinMode(_dataPin, INPUT_PULLUP);

  //  DISABLE INTERRUPTS when clock in the bits
  if (_disableIRQ)
  {
#if defined(ESP32)
    portDISABLE_INTERRUPTS();
#else
    noInterrupts();
#endif
  }

  //  DHT22  (and others including Si7021)
  //  SENSOR PULLS LOW after 20-40 us  => if stays HIGH ==> device not ready
  //  timeout is 20 us less due to delay() above
  //  DHT11
  //  SENSOR PULLS LOW after 6000-10000 us
  uint32_t WAITFORSENSOR = 50;
  if (_type == 11)  WAITFORSENSOR = 15000UL;
  if (_waitFor(LOW, WAITFORSENSOR)) return DHTLIB_ERROR_SENSOR_NOT_READY;

  //  SENSOR STAYS LOW for ~80 us => or TIMEOUT
  if (_waitFor(HIGH, 90)) return DHTLIB_ERROR_TIMEOUT_A;

  //  SENSOR STAYS HIGH for ~80 us => or TIMEOUT
  if (_waitFor(LOW, 90)) return DHTLIB_ERROR_TIMEOUT_B;

  //  SENSOR HAS NOW SEND ACKNOWLEDGE ON WAKEUP
  //  NOW IT SENDS THE BITS

  //  READ THE OUTPUT - 40 BITS => 5 BYTES
  for (uint8_t i = 40; i != 0; i--)
  {
    //  EACH BIT START WITH ~50 us LOW
    if (_waitFor(HIGH, 90))
    {
      //  Most critical timeout
      //  Serial.print("IC: ");
      //  Serial.println(i);
      return DHTLIB_ERROR_TIMEOUT_C;
    }

    //  DURATION OF HIGH DETERMINES 0 or 1
    //  26-28 us  ==>  0
    //     70 us  ==>  1
    uint32_t t = micros();
    if (_waitFor(LOW, 90))
    {
      //  Serial.print("ID: ");
      //  Serial.println(i);
      return DHTLIB_ERROR_TIMEOUT_D;
    }
    if ((micros() - t) > DHTLIB_BIT_THRESHOLD)
    {
      _bits[idx] |= mask;
    }

    //  PREPARE FOR NEXT BIT
    mask >>= 1;
    if (mask == 0)   //  next byte?
    {
      mask = 0x80;
      idx++;
    }
  }
  //  After 40 bits the sensor pulls the line LOW for 50 us
  //  No functional need to wait for this one
  //  if (_waitFor(HIGH, 60)) return DHTLIB_ERROR_TIMEOUT_E;

  //  CATCH RIGHTSHIFT BUG ESP (only 1 single bit shift)
  //  humidity is maximum 1000 = 0x03E8 for DHT22 and 0x6400 for DHT11
  //  so most significant bit may never be set.
  if (_bits[0] & 0x80) return DHTLIB_ERROR_BIT_SHIFT;

  return DHTLIB_OK;
}


//  returns true  if timeout has passed.
//  returns false if timeout is not reached and state is seen.
bool DHTNEW::_waitFor(uint8_t state, uint32_t timeout)
{
  uint32_t start = micros();
  uint8_t  count = 2;
  while ((micros() - start) < timeout)
  {
    //  delayMicroseconds(1);         //  less # reads ==> minimizes # glitch reads
    if (digitalRead(_dataPin) == state)
    {
      count--;
      if (count == 0) return false;   //  requested state seen count times
    }
  }
  return true;
}


//  -- END OF FILE --

