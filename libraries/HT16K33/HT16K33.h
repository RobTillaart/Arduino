#pragma once
//
//    FILE: HT16K33.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2019-02-07
// PURPOSE: Arduino Library for HT16K33 4x7segment display
//          http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33.git
//

#include "Arduino.h"
#include "Wire.h"

#define HT16K33_LIB_VERSION "0.3.0"

class HT16K33
{
public:
  HT16K33(const uint8_t address);           // 0x70 .. 0x77

#if defined (ESP8266) || defined(ESP32)
  void begin(uint8_t sda, uint8_t scl);
#endif
  void begin();
  void reset();

  // default _cache is true as it is ~3x faster but if one has noise
  // on the I2C and wants to force refresh one can disable caching
  // for one or more calls.
  void clearCache();
  void cacheOn()  { _cache = true; };
  void cacheOff() { _cache = false; };

  void displayOn();
  void displayOff();

  void brightness(uint8_t val);             // 0 .. 15
  void blink(uint8_t val);                  // 0 .. 3     0 = off

  // 0,1,2,3,4 digits - will replace suppressLeadingZeroPlaces
  void setDigits(uint8_t val);
  // 0 = off, 1,2,3,4 digits  space iso 0
  void suppressLeadingZeroPlaces(uint8_t val);    // will be obsolete

  void displayClear();
  void displayInt(int n);                   // -999 .. 9999
  void displayHex(uint16_t n);              // 0000 .. FFFF

  // Date could be {month.day} or {day.hour}           . as separator
  // Time could be hh:mm or mm:ss or ss:uu (hundreds   : as separator
  //
  void displayDate(uint8_t left, uint8_t right);    // 00.00 .. 99.99
  void displayTime(uint8_t left, uint8_t right);    // 00:00 .. 99:99
  
  void displayFloat(float f);               // -999 .. 0.000 .. 9999

  void display(uint8_t *arr);               // array with 4 elements
  void display(uint8_t *arr, uint8_t pt);   // pt = digit with . (0..3)
  void displayColon(uint8_t on);            // 0 = off
  void displayRaw(uint8_t *arr, bool colon = false);  // max control

  void displayVULeft(uint8_t val);          // 0..8
  void displayVURight(uint8_t val);         // 0..8

  // DEBUG
  void displayTest(uint8_t del);
  void dumpSerial(uint8_t *arr, uint8_t pnt);

private:

  void writeCmd(uint8_t cmd);
  void writePos(uint8_t pos, uint8_t mask);
  void writePos(uint8_t pos, uint8_t mask, bool pnt);

  uint8_t _addr;
  uint8_t _displayCache[5];                 // for performance
  bool    _cache = true;
  uint8_t _digits = 0;
  uint8_t _bright;
};

// -- END OF FILE --
