#pragma once
//
//    FILE: HT16K33.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.1
//    DATE: 2019-02-07
// PURPOSE: Arduino Library for HT16K33 4x7segment display
//          http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33.git


#include "Arduino.h"
#include "Wire.h"


#define HT16K33_LIB_VERSION         (F("0.4.1"))


//  Supported characters
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
#define HT16K33_TOP_C            18     //  c
#define HT16K33_DEGREE           19     //  °
#define HT16K33_NONE             99


//  Raw segments, See #28
//
//  HEX codes 7 segment
//
//     A               0x01
//  F     B        0x20    0x02
//     G               0x40
//  E     C        0x10    0x04
//     D    dp         0x08      0x80
//
const uint8_t SEG_NONE = 0x00;
const uint8_t SEG_A    = 0x01;
const uint8_t SEG_B    = 0x02;
const uint8_t SEG_C    = 0x04;
const uint8_t SEG_D    = 0x08;
const uint8_t SEG_E    = 0x10;
const uint8_t SEG_F    = 0x20;
const uint8_t SEG_G    = 0x40;
const uint8_t SEG_DP   = 0x80;


class HT16K33
{
public:
  HT16K33(const uint8_t address, TwoWire *wire = &Wire);   //  0x70 .. 0x77

  bool    begin();
  void    reset();
  bool    isConnected();

  //  default _cache is true as it is ~3x faster but if one has noise
  //  on the I2C and wants to force refresh one can disable caching
  //  for one or more calls.
  void    clearCache();
  void    cacheOn();
  void    cacheOff();
  void    refresh();     //  force writing of cache to display

  void    displayOn();
  void    displayOff();

  void    setBrightness(uint8_t value);          //  0 .. 15
  uint8_t getBrightness();
  void    setBlink(uint8_t value);               //  0 .. 3     0 = off
  uint8_t getBlink();


  //  0,1,2,3,4 digits - will replace suppressLeadingZeroPlaces
  void    setDigits(uint8_t value);
  uint8_t getDigits();


  void    displayClear();
  bool    displayInt(int n);                   //  -999 .. 9999
  bool    displayHex(uint16_t n);              //  0000 .. FFFF

  //  Date could be {month.day} or {day.hour}           . as separator
  //  Time could be hh:mm or mm:ss or ss:uu (hundreds   : as separator
  //     colon displays :   lz = Leading Zero or space
  bool    displayDate(uint8_t left, uint8_t right, bool lz = true);                     //  00.00 .. 99.99
  bool    displayTime(uint8_t left, uint8_t right, bool colon = true, bool lz = true);  //  00:00 .. 99:99
  bool    displaySeconds(uint16_t seconds, bool colon = true, bool lz = true);          //  00:00 .. 99:99

  // -999 .. 0.000 .. 9999
  bool    displayFloat(float f, uint8_t decimals = 3);

  // -99 .. 0.00 .. 999
  bool    displayUnit(float f, uint8_t decimals = 2, uint8_t unitChar = HT16K33_SPACE);


  void    display(uint8_t *array);                  //  array with 4 elements
  void    display(uint8_t *array, uint8_t point);   //  point = digit with . (0..3)
  void    displayColon(uint8_t on);                 //  0 = off
  void    displayRaw(uint8_t *array, bool colon = false);  //  max control

  //  from issue #21 - used in special layout   :88:8'8   normal = 88:88 or 8.8.8.8
  //  value = 0 ==> all off.
  //   2 = colon
  //   4 = upper left point, left of the 1st digit
  //   8 = lower left point, left of the 1st digit
  //  16 = upper point between 3rd and 4th digit
  void    displayExtraLeds(uint8_t value);

  bool    displayVULeft(uint8_t value);        //  0..8
  bool    displayVURight(uint8_t value);       //  0..8


  //  DEBUG
  void    displayTest(uint8_t del);
  //  array as numbers
  void    dumpSerial(uint8_t *array, uint8_t point);
  //  display cache in HEX format
  void    dumpSerial();
  uint8_t getAddress();


  //  EXPERIMENTAL
  bool    displayFixedPoint0(float f);
  bool    displayFixedPoint1(float f);
  bool    displayFixedPoint2(float f);
  bool    displayFixedPoint3(float f);

  //  use setDigits(); instead.
  //  0 = off, 1,2,3,4 digits  space instead of 0
  void    suppressLeadingZeroPlaces(uint8_t value);


  //  OBSOLETE 0.4.x
  void    brightness(uint8_t value) { setBrightness(value); };
  void    blink(uint8_t value)      { setBlink(value); };


private:
  void    _refresh();
  void    writeCmd(uint8_t cmd);
  void    writePos(uint8_t pos, uint8_t mask);
  void    writePos(uint8_t pos, uint8_t mask, bool point);

  uint8_t _address;
  uint8_t _displayCache[5];                 //  for performance
  bool    _cache = true;
  uint8_t _digits = 0;
  uint8_t _bright;
  uint8_t _blink;

  TwoWire*  _wire;
};


//  -- END OF FILE --

