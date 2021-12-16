//
//    FILE: DHTStable.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 1.1.1
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: https://github.com/RobTillaart/DHTstable
//
//  HISTORY:

//  1.1.1   2021-12-16  update library.json, license, minor edits
//  1.1.0   2021-11-06  fix DHTNew-#67 negative temperature
//  1.0.1   2021-06-01  change architecture to fix incompatible flag.
//  1.0.0   2021-05-26  rename files and class to DHTStable to fix incompatible flag.
//                      changed temperature and humidity to private
//                      breaking change!

//  0.2.9   2021-02-27  fix URL in library.json
//  0.2.8   2021-02-01  fix negative temperature (from DHTStablenew)
//  0.2.7   2020-12-20  add Arduino-CI, unit test,
//                      reset(), getTemperature(), getHumidity()
//  0.2.6   2020-07-20  update URL in .cpp
//  0.2.5   2020-06-30  move to own repository; update headers mainly.
//  0.2.4   2018-04-03  add get-/setDisableIRQ(bool b)
//  0.2.3   2018-02-21  change #defines in const int to enforce return types.
//                      https://github.com/RobTillaart/Arduino/issues/94
//  0.2.2   2017-12-12  add support for AM23XX types more explicitly
//  0.2.1   2017-09-20  fix https://github.com/RobTillaart/Arduino/issues/80
//  0.2.0   2017-07-24  fix https://github.com/RobTillaart/Arduino/issues/31 + 33
//  0.1.13  fix negative temperature
//  0.1.12  support DHT33 and DHT44 initial version
//  0.1.11  renamed DHTLIB_TIMEOUT
//  0.1.10  optimized faster WAKEUP + TIMEOUT
//  0.1.09  optimize size: timeout check + use of mask
//  0.1.08  added formula for timeout based upon clock speed
//  0.1.07  added support for DHT21
//  0.1.06  minimize footprint (2012-12-27)
//  0.1.05  fixed negative temperature bug (thanks to Roseman)
//  0.1.04  improved readability of code using DHTLIB_OK in code
//  0.1.03  added error values for temp and humidity when read failed
//  0.1.02  added error codes
//  0.1.01  added support for Arduino 1.0, fixed typos (31/12/2011)
//  0.1.0   by Rob Tillaart (01/04/2011)
//
// inspired by DHT11 library
//


#include "DHTStable.h"


/////////////////////////////////////////////////////
//
// PUBLIC
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


// return values:
// DHTLIB_OK
// DHTLIB_ERROR_CHECKSUM
// DHTLIB_ERROR_TIMEOUT
int DHTStable::read11(uint8_t pin)
{
    // READ VALUES
    if (_disableIRQ) noInterrupts();
    int rv = _readSensor(pin, DHTLIB_DHT11_WAKEUP);
    if (_disableIRQ) interrupts();
    if (rv != DHTLIB_OK)
    {
        _humidity    = DHTLIB_INVALID_VALUE; // invalid value, or is NaN prefered?
        _temperature = DHTLIB_INVALID_VALUE; // invalid value
        return rv;
    }

    // CONVERT AND STORE
    _humidity = _bits[0] + _bits[1] * 0.1;
    _temperature = (_bits[2] & 0x7F) + _bits[3] * 0.1;
    if (_bits[2] & 0x80)  // negative temperature
    {
        _temperature = -_temperature;
    }

    // TEST CHECKSUM
    uint8_t sum = _bits[0] + _bits[1] + _bits[2] + _bits[3];
    if (_bits[4] != sum)
    {
      return DHTLIB_ERROR_CHECKSUM;
    }
    return DHTLIB_OK;
}


// return values:
// DHTLIB_OK
// DHTLIB_ERROR_CHECKSUM
// DHTLIB_ERROR_TIMEOUT
int DHTStable::read(uint8_t pin)
{
    // READ VALUES
    if (_disableIRQ) noInterrupts();
    int rv = _readSensor(pin, DHTLIB_DHT_WAKEUP);
    if (_disableIRQ) interrupts();
    if (rv != DHTLIB_OK)
    {
        _humidity    = DHTLIB_INVALID_VALUE;  // NaN preferred?
        _temperature = DHTLIB_INVALID_VALUE;  // NaN preferred?
        return rv; // propagate error value
    }
    // CONVERT AND STORE
    _humidity  = word(_bits[0], _bits[1]) * 0.1;
    int16_t t = ((_bits[2] & 0x7F) * 256 + _bits[3]);
    if (t == 0)
    {
      _temperature = 0.0;     // prevent -0.0;
    }
    else
    {
      _temperature = t * 0.1;
      if((_bits[2] & 0x80) == 0x80 )
      {
        _temperature = -_temperature;
      }
    }
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
int DHTStable::_readSensor(uint8_t pin, uint8_t wakeupDelay)
{
    // INIT BUFFERVAR TO RECEIVE DATA
    uint8_t mask = 128;
    uint8_t idx = 0;

    // EMPTY BUFFER
    for (uint8_t i = 0; i < 5; i++) _bits[i] = 0;

    // REQUEST SAMPLE
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(wakeupDelay);
    pinMode(pin, INPUT);
    delayMicroseconds(40);

    // GET ACKNOWLEDGE or TIMEOUT
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

    // READ THE OUTPUT - 40 _bits => 5 BYTES
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


// -- END OF FILE --
