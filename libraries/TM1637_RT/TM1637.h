#pragma once
//
//    FILE: TM1637.h
//  AUTHOR: Rob Tillaart
//    DATE: 2019-10-28
// VERSION: 0.3.1
// PUPROSE: TM1637 library for Arduino
//     URL: https://github.com/RobTillaart/TM1637_RT


// only tested on 6 digit display yet


#include "Arduino.h"

#define TM1637_LIB_VERSION      (F("0.3.1"))


class TM1637
{
  public:
    TM1637();

    void init(uint8_t clockPin, uint8_t dataPin, uint8_t digits = 6);

    void displayRaw(uint8_t * data, uint8_t pointPos);
    void displayInt(long value);
    void displayFloat(float value);
    void displayHex(uint32_t value);
    void displayClear();

    void    setBrightness(uint8_t b);
    uint8_t getBrightness() { return _brightness; };

    // tune the timing of writing bytes.
    void    setBitDelay(uint8_t bitDelay = 10) { _bitDelay = bitDelay; };
    uint8_t getBitDelay() { return _bitDelay; };
    uint8_t keyscan(void);


  private:
    uint8_t _clock      = -1;
    uint8_t _data       = -1;
    uint8_t _digits     = 4;
    uint8_t _brightness = 3;
    uint8_t _bitDelay   = 10;

    uint8_t writeByte(uint8_t data);
    void    start();
    void    stop();

    void writeSync(uint8_t pin, uint8_t val);
    void nanoDelay(uint16_t n);
};


// -- END OF FILE --

