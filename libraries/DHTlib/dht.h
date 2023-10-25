#pragma once
//
//    FILE: dht.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.36
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino. AVR optimized
//     URL: https://github.com/RobTillaart/DHTlib
//          http://arduino.cc/playground/Main/DHTLib


#if ARDUINO < 100
#include <WProgram.h>
#include <pins_arduino.h>  //  fix for broken pre 1.0 version - TODO TEST
#else
#include <Arduino.h>
#endif


#define DHT_LIB_VERSION                 (F("0.1.36"))

#define DHTLIB_OK                       0
#define DHTLIB_ERROR_CHECKSUM           -1
#define DHTLIB_ERROR_TIMEOUT            -2
#define DHTLIB_ERROR_CONNECT            -3
#define DHTLIB_ERROR_ACK_L              -4
#define DHTLIB_ERROR_ACK_H              -5


class dht
{
public:
    dht() { _disableIRQ = false; };
    //  return values:
    //  DHTLIB_OK
    //  DHTLIB_ERROR_CHECKSUM
    //  DHTLIB_ERROR_TIMEOUT
    //  DHTLIB_ERROR_CONNECT
    //  DHTLIB_ERROR_ACK_L
    //  DHTLIB_ERROR_ACK_H
    int8_t read11(uint8_t pin);
    int8_t read(uint8_t pin);
    int8_t read12(uint8_t pin);

    inline int8_t read21(uint8_t pin)   { return read(pin); };
    inline int8_t read22(uint8_t pin)   { return read(pin); };
    inline int8_t read33(uint8_t pin)   { return read(pin); };
    inline int8_t read44(uint8_t pin)   { return read(pin); };
    inline int8_t read2301(uint8_t pin) { return read(pin); };
    inline int8_t read2302(uint8_t pin) { return read(pin); };
    inline int8_t read2303(uint8_t pin) { return read(pin); };
    inline int8_t read2320(uint8_t pin) { return read(pin); };
    inline int8_t read2322(uint8_t pin) { return read(pin); };

    bool getDisableIRQ()                { return _disableIRQ; };
    void setDisableIRQ(bool b )         { _disableIRQ = b; };

    float humidity;
    float temperature;

private:
    uint8_t bits[5];  //  buffer to receive data
    int8_t _readSensor(uint8_t pin, uint8_t wakeupDelay, uint8_t leadingZeroBits);
    bool   _disableIRQ;
};


//  -- END OF FILE --

