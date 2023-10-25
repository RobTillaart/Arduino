//
//    FILE: dht.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.36
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino, AVR optimized
//     URL: https://github.com/RobTillaart/DHTlib
//          http://arduino.cc/playground/Main/DHTLib
//
//  inspired by DHT11 library


#include "dht.h"


#define DHTLIB_DHT11_WAKEUP             18
#define DHTLIB_DHT_WAKEUP               1

#define DHTLIB_DHT11_LEADING_ZEROS      1
#define DHTLIB_DHT_LEADING_ZEROS        6


//  max timeout is 100 microseconds.
//  For a 16 MHz processor 100 microseconds is 1600 clock cycles
//  loops using DHTLIB_TIMEOUT use at least 4 clock cycles
//  so 100 us takes max 400 loops
//  so by dividing F_CPU by 40000 we "fail" as fast as possible
#ifndef F_CPU
#define DHTLIB_TIMEOUT 1000  //  should be approx. clock/40000
#else
#define DHTLIB_TIMEOUT (F_CPU/40000)
#endif


/////////////////////////////////////////////////////
//
//  PUBLIC
//

int8_t dht::read11(uint8_t pin)
{
    //  READ VALUES
    if (_disableIRQ) noInterrupts();
    int8_t result = _readSensor(pin, DHTLIB_DHT11_WAKEUP, DHTLIB_DHT11_LEADING_ZEROS);
    if (_disableIRQ) interrupts();

    //  these bits are always zero, masking them reduces errors.
    bits[0] &= 0x7F;
    bits[2] &= 0x7F;

    //  CONVERT AND STORE
    humidity    = bits[0];  //  bits[1] == 0;
    temperature = bits[2];  //  bits[3] == 0;

    //  TEST CHECKSUM
    uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
    if (bits[4] != sum)
    {
        return DHTLIB_ERROR_CHECKSUM;
    }
    return result;
}


int8_t dht::read12(uint8_t pin)
{
    //  READ VALUES
    if (_disableIRQ) noInterrupts();
    int8_t result = _readSensor(pin, DHTLIB_DHT11_WAKEUP, DHTLIB_DHT11_LEADING_ZEROS);
    if (_disableIRQ) interrupts();

    //  CONVERT AND STORE
    humidity = bits[0] + bits[1] * 0.1;
    temperature = bits[2] + (bits[3] & 0x7F) * 0.1;
    if (bits[3] & 0x80)  //  negative temperature
    {
        temperature = -temperature;
    }

    //  TEST CHECKSUM
    uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
    if (bits[4] != sum)
    {
        return DHTLIB_ERROR_CHECKSUM;
    }
    return result;
}


int8_t dht::read(uint8_t pin)
{
    //  READ VALUES
    if (_disableIRQ) noInterrupts();
    int8_t result = _readSensor(pin, DHTLIB_DHT_WAKEUP, DHTLIB_DHT_LEADING_ZEROS);
    if (_disableIRQ) interrupts();

    //  these bits are always zero, masking them reduces errors.
    bits[0] &= 0x03;
    bits[2] &= 0x83;

    //  CONVERT AND STORE
    humidity  = (bits[0] * 256 + bits[1]) * 0.1;
    int16_t t = ((bits[2] & 0x7F) * 256 + bits[3]);
    if (t == 0)
    {
      temperature = 0.0;     //  prevent -0.0;
    }
    else
    {
      temperature = t * 0.1;
      if((bits[2] & 0x80) == 0x80 )
      {
        temperature = -temperature;
      }
    }

    //  HEXDUMP DEBUG
    /*
    Serial.println();
    // CHECKSUM
    if (_bits[4] < 0x10) Serial.print(0);
    Serial.print(_bits[4], HEX);
    Serial.print("    ");
    // TEMPERATURE
    if (_bits[2] < 0x10) Serial.print(0);
    Serial.print(_bits[2], HEX);
    if (_bits[3] < 0x10) Serial.print(0);
    Serial.print(_bits[3], HEX);
    Serial.print("    ");
    Serial.print(temperature, 1);
    Serial.print("    ");
    // HUMIDITY
    if (_bits[0] < 0x10) Serial.print(0);
    Serial.print(_bits[0], HEX);
    if (_bits[1] < 0x10) Serial.print(0);
    Serial.print(_bits[1], HEX);
    Serial.print("    ");
    Serial.print(humidity, 1);
    */

    //  TEST CHECKSUM
    uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
    if (bits[4] != sum)
    {
        return DHTLIB_ERROR_CHECKSUM;
    }
    return result;
}


/////////////////////////////////////////////////////
//
//  PRIVATE
//
int8_t dht::_readSensor(uint8_t pin, uint8_t wakeupDelay, uint8_t leadingZeroBits)
{
    //  INIT BUFFERVAR TO RECEIVE DATA
    uint8_t mask = 128;
    uint8_t idx = 0;

    uint8_t data = 0;
    uint8_t state = LOW;
    uint8_t pstate = LOW;
    uint16_t zeroLoop = DHTLIB_TIMEOUT;
    uint16_t delta = 0;

    leadingZeroBits = 40 - leadingZeroBits;  //  reverse counting...

    //  replace digitalRead() with Direct Port Reads.
    //  reduces footprint ~100 bytes => portability issue?
    //  direct port read is about 3x faster
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *PIR = portInputRegister(port);

    //  REQUEST SAMPLE
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);  //  T-be
    if (wakeupDelay > 8) delay(wakeupDelay);
    else delayMicroseconds(wakeupDelay * 1000UL);
    digitalWrite(pin, HIGH);  //  T-go
    pinMode(pin, INPUT);

    uint16_t loopCount = DHTLIB_TIMEOUT * 2;  //  200 uSec max
    //  while(digitalRead(pin) == HIGH)
    while ((*PIR & bit) != LOW )
    {
        if (--loopCount == 0)
        {
          return DHTLIB_ERROR_CONNECT;
        }
    }

    //  GET ACKNOWLEDGE or TIMEOUT
    loopCount = DHTLIB_TIMEOUT;
    //  while(digitalRead(pin) == LOW)
    while ((*PIR & bit) == LOW )  //  T-rel
    {
        if (--loopCount == 0)
        {
          return DHTLIB_ERROR_ACK_L;
        }
    }

    loopCount = DHTLIB_TIMEOUT;
    //  while(digitalRead(pin) == HIGH)
    while ((*PIR & bit) != LOW )  //  T-reh
    {
        if (--loopCount == 0)
        {
          return DHTLIB_ERROR_ACK_H;
        }
    }

    loopCount = DHTLIB_TIMEOUT;

    //  READ THE OUTPUT - 40 BITS => 5 BYTES
    for (uint8_t i = 40; i != 0; )
    {
        //  WAIT FOR FALLING EDGE
        state = (*PIR & bit);
        if (state == LOW && pstate != LOW)
        {
            if (i > leadingZeroBits)  //  DHT22 first 6 bits are all zero !!   DHT11 only 1
            {
                zeroLoop = min(zeroLoop, loopCount);
                delta = (DHTLIB_TIMEOUT - zeroLoop)/4;
            }
            else if ( loopCount <= (zeroLoop - delta) )  //  long -> one
            {
                data |= mask;
            }
            mask >>= 1;
            if (mask == 0)   //  next byte
            {
                mask = 128;
                bits[idx] = data;
                idx++;
                data = 0;
            }
            //  next bit
            --i;

            //  reset timeout flag
            loopCount = DHTLIB_TIMEOUT;
        }
        pstate = state;
        //  Check timeout
        if (--loopCount == 0)
        {
          return DHTLIB_ERROR_TIMEOUT;
        }

    }
    //  pinMode(pin, OUTPUT);
    //  digitalWrite(pin, HIGH);
    return DHTLIB_OK;
}


//  -- END OF FILE --

