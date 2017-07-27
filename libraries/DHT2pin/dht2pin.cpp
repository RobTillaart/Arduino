//
//    FILE: DHT2pin.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.3
// PURPOSE: Experimental DHT Temperature & Humidity Sensor library for Arduino
//     URL: 
//
// HISTORY:
// 0.0.3 Fix issue #33
// 0.0.2 support for non "F_CPU" boards especially Galileo
//       Tested and verified by Maria Emanuella Moura Silva (thanks)
//       changed name to DHT2pin
// 0.0.1 initial version - 2016 SEP 05 (based upon 0.1.13 DHT)
//
// Released to the public domain
//

#include "DHT2pin.h"

/////////////////////////////////////////////////////
//
// PUBLIC
//

// return values:
// DHTLIB_OK
// DHTLIB_ERROR_CHECKSUM
// DHTLIB_ERROR_TIMEOUT
int DHT2pin::read11()
{
    // READ VALUES
    int rv = _readSensor(DHTLIB_DHT11_WAKEUP);
    if (rv != DHTLIB_OK)
    {
        humidity    = DHTLIB_INVALID_VALUE; // invalid value, or is NaN prefered?
        temperature = DHTLIB_INVALID_VALUE; // invalid value
        return rv;
    }

    // CONVERT AND STORE
    humidity    = bits[0];  // bits[1] == 0;
    temperature = bits[2];  // bits[3] == 0;

    // TEST CHECKSUM
    // bits[1] && bits[3] both 0
    uint8_t sum = bits[0] + bits[2];
    if (bits[4] != sum) return DHTLIB_ERROR_CHECKSUM;

    return DHTLIB_OK;
}


// return values:
// DHTLIB_OK
// DHTLIB_ERROR_CHECKSUM
// DHTLIB_ERROR_TIMEOUT
int DHT2pin::read()
{
    // READ VALUES
    int rv = _readSensor(DHTLIB_DHT_WAKEUP);
    if (rv != DHTLIB_OK)
    {
        humidity    = DHTLIB_INVALID_VALUE;  // invalid value, or is NaN prefered?
        temperature = DHTLIB_INVALID_VALUE;  // invalid value
        return rv; // propagate error value
    }

    // CONVERT AND STORE
    humidity = word(bits[0], bits[1]) * 0.1;
    temperature = word(bits[2] & 0x7F, bits[3]) * 0.1;
    if (bits[2] & 0x80)  // negative temperature
    {
        temperature = -temperature;
    }

    // TEST CHECKSUM
    uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
    if (bits[4] != sum)
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
int DHT2pin::_readSensor(uint8_t wakeupDelay)
{
    // INIT BUFFERVAR TO RECEIVE DATA
    uint8_t mask = 128;
    uint8_t idx = 0;

    // EMPTY BUFFER
    for (uint8_t i = 0; i < 5; i++) bits[i] = 0;

    // REQUEST SAMPLE
    digitalWrite(_wpin, LOW);
    delay(wakeupDelay);
    digitalWrite(_wpin, HIGH);
    delayMicroseconds(40);
 
    // GET ACKNOWLEDGE or TIMEOUT
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

    // READ THE OUTPUT - 40 BITS => 5 BYTES
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
            bits[idx] |= mask;
        }
        mask >>= 1;
        if (mask == 0)   // next byte?
        {
            mask = 128;
            idx++;
        }
    }
    digitalWrite(_wpin, HIGH);

    return DHTLIB_OK;
}
//
// END OF FILE
//