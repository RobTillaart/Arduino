//
//    FILE: HT16K33.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.2
//    DATE: 2019-02-07
// PURPOSE: Class for HT16K33 7segment I2C display
//          http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/Arduino.git
//
// Released to the public domain
//
//   TODO: negative values
//

#ifndef HT16K33_h
#define HT16K33_h

#include "Arduino.h"
#include "Wire.h"

#define HT16K33_LIB_VERSION "0.1.2"

class HT16K33
{
public:
  HT16K33();

  void begin(const uint8_t address);        // 0x70 .. 0x77
  void displayOn();
  void displayOff();
  void brightness(uint8_t val);             // 0 .. 15
  void blink(uint8_t val);                  // 0 .. 3     0 = off

  void displayClear();
  void displayInt(int n);                   // 0000 .. 9999
  void displayHex(uint16_t n);              // 0000 .. FFFF
  void displayTime(uint8_t left, uint8_t right);    // 00:00 .. 99:99
  void displayFloat(float f);               // 0.000 .. 9999.
  void display(uint8_t *arr);               // array with 4 elements
  void display(uint8_t *arr, uint8_t pt);   // pt = digit with . (0..3)
  void displayColon(uint8_t on);            // 0 = off

  void displayTest(uint8_t del);

private:

  void writeCmd(uint8_t cmd);
  void writePos(uint8_t pos, uint8_t mask);
  void writePos(uint8_t pos, uint8_t mask, bool pnt);

  uint8_t _addr;
  uint8_t _displayCache[5];                 // for performance
};

#endif
// -- END OF FILE --