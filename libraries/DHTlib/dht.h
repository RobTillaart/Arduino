    //
//    FILE: dht.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.26
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: http://arduino.cc/playground/Main/DHTLib
//
// HISTORY:
// see dht.cpp file
//

#ifndef dht_h
#define dht_h

#if ARDUINO < 100
#include <WProgram.h>
#include <pins_arduino.h>  // fix for broken pre 1.0 version - TODO TEST
#else
#include <Arduino.h>
#endif

#define DHT_LIB_VERSION "0.1.26"

#define DHTLIB_OK                   0
#define DHTLIB_ERROR_CHECKSUM       -1
#define DHTLIB_ERROR_TIMEOUT        -2
#define DHTLIB_ERROR_CONNECT        -3
#define DHTLIB_ERROR_ACK_L          -4
#define DHTLIB_ERROR_ACK_H          -5

#define DHTLIB_DHT11_WAKEUP         18
#define DHTLIB_DHT_WAKEUP           1

#define DHTLIB_DHT11_LEADING_ZEROS  1
#define DHTLIB_DHT_LEADING_ZEROS    6

// max timeout is 100 usec.
// For a 16 Mhz proc 100 usec is 1600 clock cycles
// loops using DHTLIB_TIMEOUT use at least 4 clock cycli
// so 100 us takes max 400 loops
// so by dividing F_CPU by 40000 we "fail" as fast as possible
#ifndef F_CPU
#define DHTLIB_TIMEOUT 1000  // ahould be approx. clock/40000
#else
#define DHTLIB_TIMEOUT (F_CPU/40000)
#endif

class dht
{
public:
    dht() {};
    // return values:
    // DHTLIB_OK
    // DHTLIB_ERROR_CHECKSUM
    // DHTLIB_ERROR_TIMEOUT
    // DHTLIB_ERROR_CONNECT
    // DHTLIB_ERROR_ACK_L
    // DHTLIB_ERROR_ACK_H
    int8_t read11(uint8_t pin);
    int8_t read(uint8_t pin);
    int8_t read12(uint8_t pin);

    inline int8_t read21(uint8_t pin) { return read(pin); };
    inline int8_t read22(uint8_t pin) { return read(pin); };
    inline int8_t read33(uint8_t pin) { return read(pin); };
    inline int8_t read44(uint8_t pin) { return read(pin); };
    inline int8_t read2301(uint8_t pin) { return read(pin); };
    inline int8_t read2302(uint8_t pin) { return read(pin); };
    inline int8_t read2303(uint8_t pin) { return read(pin); };
    inline int8_t read2320(uint8_t pin) { return read(pin); };
    inline int8_t read2322(uint8_t pin) { return read(pin); };

    float humidity;
    float temperature;

private:
    uint8_t bits[5];  // buffer to receive data
    int8_t _readSensor(uint8_t pin, uint8_t wakeupDelay, uint8_t leadingZeroBits);
};
#endif
//
// END OF FILE
//