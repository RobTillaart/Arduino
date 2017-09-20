//
//    FILE: dht.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable
//
// HISTORY:
// see dht.cpp file
//

#ifndef dht_h
#define dht_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define DHT_LIB_VERSION "0.2.1 - dhtstable"

#define DHTLIB_OK                0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2
#define DHTLIB_INVALID_VALUE    -999

#define DHTLIB_DHT11_WAKEUP     18
#define DHTLIB_DHT_WAKEUP       1

// max timeout is 100usec.
// For a 16Mhz proc that is max 1600 clock cycles
// loops using TIMEOUT use at least 4 clock cycli
// so 100 us takes max 400 loops
// so by dividing F_CPU by 40000 we "fail" as fast as possible
#define DHTLIB_TIMEOUT (F_CPU/40000)

class dht
{
public:
    // return values:
    // DHTLIB_OK
    // DHTLIB_ERROR_CHECKSUM
    // DHTLIB_ERROR_TIMEOUT
    int read11(uint8_t pin);
    int read(uint8_t pin);

    inline int read21(uint8_t pin) { return read(pin); };
    inline int read22(uint8_t pin) { return read(pin); };
    inline int read33(uint8_t pin) { return read(pin); };
    inline int read44(uint8_t pin) { return read(pin); };

    float humidity;
    float temperature;

private:
    uint8_t bits[5];  // buffer to receive data
    int _readSensor(uint8_t pin, uint8_t wakeupDelay);
};
#endif
//
// END OF FILE
//