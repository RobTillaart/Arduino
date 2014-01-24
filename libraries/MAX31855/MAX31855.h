#ifndef MAX31855_H
#define MAX31855_H
//
//    FILE: MAX31855.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: MAX31855 - Thermocouple
//    DATE: 2014-01-01
//     URL:
//
// Released to the public domain
//

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include "Arduino.h"
#endif

#define MAX31855_VERSION "0.1.03"

#define STATUS_OK               0x00
#define STATUS_OPEN_CIRCUIT     0x01
#define STATUS_SHORT_TO_GND     0x02
#define STATUS_SHORT_TO_VCC     0x04

class MAX31855
{
public:
    MAX31855(uint8_t SCLK, uint8_t CS, uint8_t MISO);
    void begin();
    uint8_t read();
    float getInternal(void) { return _internal; };
    // Celsius
    float getTemperature(void) { return _temperature; };
    uint8_t getStatus(void) {return _status; };

    void setOffset(float t) { _offset = t; };
    float getOffset(float t) { return _offset; };


private:
    uint32_t _read();
    float _internal;
    float _temperature;
    uint8_t _status;
    float _offset;

    uint8_t _sclk;
    uint8_t _miso;
    uint8_t _cs;
};

#endif

// END OF FILE