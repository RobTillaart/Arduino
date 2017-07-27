//
//    FILE: dht2pin.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.3
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: http://arduino.cc/playground/Main/DHTLib
//
// HISTORY:
// see dht.cpp file
//

#ifndef dht_h
#define dht_h

#include <Arduino.h>

#define DHT2PIN_LIB_VERSION "0.0.3"

#define DHTLIB_OK                   0
#define DHTLIB_ERROR_CHECKSUM       -1
#define DHTLIB_ERROR_TIMEOUT        -2
#define DHTLIB_ERROR_CONNECT        -3
#define DHTLIB_ERROR_ACK_L          -4
#define DHTLIB_ERROR_ACK_H          -5
#define DHTLIB_INVALID_VALUE        -999

#define DHTLIB_DHT11_WAKEUP     18
#define DHTLIB_DHT_WAKEUP       1

// max timeout is 100usec.
// For a 16Mhz proc that is max 1600 clock cycles
// loops using TIMEOUT use at least 4 clock cycli
// so 100 us takes max 400 loops
// so by dividing F_CPU by 40000 we "fail" as fast as possible
#ifdef F_CPU
#define DHTLIB_TIMEOUT (F_CPU/40000)
#else
#define DHTLIB_TIMEOUT (75000000/40000)
#endif
    
class DHT2pin
{
public:
    // return values:
    // DHTLIB_OK
    // DHTLIB_ERROR_CHECKSUM
    // DHTLIB_ERROR_TIMEOUT
    DHT2pin(uint8_t rpin, uint8_t wpin) 
    { 
        _rpin = rpin; 
        _wpin = wpin; 
    };

    void begin()
    {
        pinMode(_rpin, INPUT);
        pinMode(_wpin, OUTPUT);
    }
    
    int read11();
    int read();

    inline int read21() { return read(); };
    inline int read22() { return read(); };
    inline int read33() { return read(); };
    inline int read44() { return read(); };

    float humidity;
    float temperature;

private:
    uint8_t _rpin;
    uint8_t _wpin;
    uint8_t bits[5];  // buffer to receive data
    int _readSensor(uint8_t wakeupDelay);
};
#endif
//
// END OF FILE
//