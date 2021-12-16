#pragma once
//
//    FILE: DHTStable.h
//  AUTHOR: Rob Tillaart
// VERSION: 1.1.1
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: https://github.com/RobTillaart/DHTstable



#include "Arduino.h"

#define DHTSTABLE_LIB_VERSION           (F("1.1.1 - DHTStable"))


const int DHTLIB_OK              = 0;
const int DHTLIB_ERROR_CHECKSUM  = -1;
const int DHTLIB_ERROR_TIMEOUT   = -2;
const int DHTLIB_INVALID_VALUE   = -999;

const int DHTLIB_DHT11_WAKEUP    = 18;
const int DHTLIB_DHT_WAKEUP      = 1;


// max timeout is 100usec.
// For a 16Mhz processor that is max 1600 clock cycles
// loops using TIMEOUT use at least 4 clock cycles
// so 100 us takes max 400 loops
// so by dividing F_CPU by 40000 we "fail" as fast as possible
const int DHTLIB_TIMEOUT = (F_CPU/40000);


class DHTStable
{
public:
    DHTStable();

    void reset();

    // return values:
    // DHTLIB_OK
    // DHTLIB_ERROR_CHECKSUM
    // DHTLIB_ERROR_TIMEOUT
    int read11(uint8_t pin);      // DHT11 & DHT12
    int read(uint8_t pin);        // DHT22

    inline int read12(uint8_t pin)   { return read11(pin); }; // ok
    inline int read21(uint8_t pin)   { return read(pin); };   // ok
    inline int read22(uint8_t pin)   { return read(pin); };   // ok
    inline int read33(uint8_t pin)   { return read(pin); };   // ok
    inline int read44(uint8_t pin)   { return read(pin); };   // ok
    inline int read2301(uint8_t pin) { return read(pin); };   // ok
    inline int read2302(uint8_t pin) { return read(pin); };   // ok
    inline int read2320(uint8_t pin) { return read(pin); };   // ok
    inline int read2322(uint8_t pin) { return read(pin); };   // ok

    // read values from cache, call read() to refresh!
    float getHumidity()    { return _humidity; };
    float getTemperature() { return _temperature; };

    bool  getDisableIRQ()            { return _disableIRQ; };
    void  setDisableIRQ(bool b )     { _disableIRQ = b; };

private:
    uint8_t _bits[5];  // buffer to receive data
    int     _readSensor(uint8_t pin, uint8_t wakeupDelay);
    bool    _disableIRQ = false;
    float   _humidity;
    float   _temperature;
};


// -- END OF FILE --
