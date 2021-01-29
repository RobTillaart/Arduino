#pragma once
//
//    FILE: HT16K33.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
//    DATE: 2019-02-07
// PURPOSE: Arduino Library for HT16K33 4x7segment display
//          http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33.git
//


#include "Arduino.h"
#include "Wire.h"


#define HT16K33_LIB_VERSION         (F("0.3.2"))


// Characters
#define HT16K33_0                0
#define HT16K33_1                1
#define HT16K33_2                2
#define HT16K33_3                3
#define HT16K33_4                4
#define HT16K33_5                5
#define HT16K33_6                6
#define HT16K33_7                7
#define HT16K33_8                8
#define HT16K33_9                9
#define HT16K33_A                10
#define HT16K33_B                11
#define HT16K33_C                12
#define HT16K33_D                13
#define HT16K33_E                14
#define HT16K33_F                15
#define HT16K33_SPACE            16
#define HT16K33_MINUS            17
#define HT16K33_NONE             99


class HT16K33
{
public:
  HT16K33(const uint8_t address, TwoWire *wire = &Wire);   // 0x70 .. 0x77

#if defined (ESP8266) || defined(ESP32)
  bool begin(uint8_t sda, uint8_t scl);
#endif
  bool begin();
  void reset();

  bool isConnected();

  // default _cache is true as it is ~3x faster but if one has noise
  // on the I2C and wants to force refresh one can disable caching
  // for one or more calls.
  void clearCache();
  void cacheOn()  { _cache = true; };
  void cacheOff() { _cache = false; };
  void refresh(); // force writing of cache to display
  
  void displayOn();
  void displayOff();

  void brightness(uint8_t val);             // 0 .. 15
  void blink(uint8_t val);                  // 0 .. 3     0 = off


  // 0,1,2,3,4 digits - will replace suppressLeadingZeroPlaces
  void setDigits(uint8_t val);
  // 0 = off, 1,2,3,4 digits  space iso 0
  void suppressLeadingZeroPlaces(uint8_t val);    // will be obsolete

  void displayClear();
  bool displayInt(int n);                   // -999 .. 9999
  bool displayHex(uint16_t n);              // 0000 .. FFFF

  // Date could be {month.day} or {day.hour}           . as separator
  // Time could be hh:mm or mm:ss or ss:uu (hundreds   : as separator
  bool displayDate(uint8_t left, uint8_t right);    // 00.00 .. 99.99
  bool displayTime(uint8_t left, uint8_t right, bool colon = true);    // 00:00 .. 99:99
  bool displaySeconds(uint16_t seconds, bool colon = true);    // 00:00 .. 99:99

  bool displayFloat(float f, uint8_t decimals = 3); // -999 .. 0.000 .. 9999

  void display(uint8_t *arr);               // array with 4 elements
  void display(uint8_t *arr, uint8_t pt);   // pt = digit with . (0..3)
  void displayColon(uint8_t on);            // 0 = off
  void displayRaw(uint8_t *arr, bool colon = false);  // max control

  bool displayVULeft(uint8_t val);          // 0..8
  bool displayVURight(uint8_t val);         // 0..8


  // DEBUG
  void    displayTest(uint8_t del);
  void    dumpSerial(uint8_t *arr, uint8_t pnt);  // array as numbers
  void    dumpSerial();                           // display cache in HEX format
  uint8_t getAddr() { return _addr; };


  // EXPERIMENTAL
  bool    getOverflow() { return _overflow; };
  void    clrOverflow() { _overflow = false; };

  bool    displayFixedPoint0(float f);
  bool    displayFixedPoint1(float f);
  bool    displayFixedPoint2(float f);
  bool    displayFixedPoint3(float f);


private:
  void    _refresh();
  void    writeCmd(uint8_t cmd);
  void    writePos(uint8_t pos, uint8_t mask);
  void    writePos(uint8_t pos, uint8_t mask, bool pnt);

  uint8_t _addr;
  uint8_t _displayCache[5];                 // for performance
  bool    _cache = true;
  uint8_t _digits = 0;
  uint8_t _bright;

  TwoWire*  _wire;
  
  // EXPERIMENTAL
  bool    _overflow = false;
};

// -- END OF FILE --
