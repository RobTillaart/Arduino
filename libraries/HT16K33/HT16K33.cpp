//
//    FILE: HT16K33.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2019-02-07
// PURPOSE: Arduino Library for HT16K33 4x7segment display
//     URL: https://github.com/RobTillaart/HT16K33
//
// HISTORY:
// 0.1.0   2019-02-07 initial version
// 0.1.1   2019-02-07 first stable version
// 0.1.2   2019-02-11 optimized performance
// 0.1.3   2019-10-07 fixed clear, added suppressLeadingZeroPlaces();
// 0.1.4   2019-11-28 added displayRaw(), displayVULeft(), displayVURight()
// 0.1.5   2019-11-30 refactor,
// 0.2.0   2020-06-13 ESP32 support; fix brightness bug;
// 0.2.1   2020-07-15 fix #160 - decimal point
// 0.2.2   2020-10-04 added displayDate() thanks to bepitama
// 0.2.3   2020-10-09 issue #4 add negative values for displayInt()
// 0.2.4   2020-10-10 refactor #5 setDigits() iso suppressLeadingZeroPlaces()
// 0.3.0   2020-10-12 negative float, cache control, extend displayRaw()

#include "HT16K33.h"

// Commands
#define HT16K33_ON              0x21  // 0=off 1=on
#define HT16K33_STANDBY         0x20  // bit xxxxxxx0

// bit pattern 1000 0xxy
// y    =  display on / off
// xx   =  00=off     01=2Hz     10=1Hz     11=0.5Hz
#define HT16K33_DISPLAYON       0x81
#define HT16K33_DISPLAYOFF      0x80
#define HT16K33_BLINKON0_5HZ    0x87
#define HT16K33_BLINKON1HZ      0x85
#define HT16K33_BLINKON2HZ      0x83
#define HT16K33_BLINKOFF        0x81

// bit pattern 1110 xxxx
// xxxx    =  0000 .. 1111 (0 - F)
#define HT16K33_BRIGHTNESS      0xE0

// Special characters
#define HT16K33_SPACE            16
#define HT16K33_MINUS            17
#define HT16K33_NONE             99

//
//  HEX codes 7 segment
//
//      01
//  20      02
//      40
//  10      04
//      08
//
static const uint8_t charmap[] = {  // TODO PROGMEM ?

  0x3F,   // 0
  0x06,   // 1
  0x5B,   // 2
  0x4F,   // 3
  0x66,   // 4
  0x6D,   // 5
  0x7D,   // 6
  0x07,   // 7
  0x7F,   // 8
  0x6F,   // 9
  0x77,   // A
  0x7C,   // B
  0x39,   // C
  0x5E,   // D
  0x79,   // E
  0x71,   // F
  0x00,   // space
  0x40,   // minus
};

////////////////////////////////////////////////////

HT16K33::HT16K33(const uint8_t address)
{
  _addr = address;
}

#if defined (ESP8266) || defined(ESP32)
void HT16K33::begin(uint8_t sda, uint8_t scl)
{
  Wire.begin(sda, scl);
  reset();
}
#endif

void HT16K33::begin()
{
  Wire.begin();
  reset();
}

void HT16K33::reset()
{
  displayOn();
  displayClear();
  setDigits(1);    
  clearCache();
  brightness(8);
}

void HT16K33::clearCache()
{
  for (uint8_t i = 0; i < 5; i++)
  {
    _displayCache[i] = HT16K33_NONE;
  }
}

void HT16K33::displayOn()
{
  writeCmd(HT16K33_ON);
  writeCmd(HT16K33_DISPLAYON);
  brightness(_bright);
}

void HT16K33::displayOff()
{
  writeCmd(HT16K33_DISPLAYOFF);
  writeCmd(HT16K33_STANDBY);
}

void HT16K33::blink(uint8_t val)
{
  if (val > 0x03) val = 0x00;
  writeCmd(HT16K33_BLINKOFF | (val << 1) );
}

void HT16K33::brightness(uint8_t val)
{
  if (val == _bright) return;
  _bright = val;
  if (_bright > 0x0F) _bright = 0x0F;
  writeCmd(HT16K33_BRIGHTNESS | _bright);
}

void HT16K33::setDigits(uint8_t val)
{
  _digits = val > 4 ? 4 : val;
}

void HT16K33::suppressLeadingZeroPlaces(uint8_t val)
{
  _digits = val > 4 ? 0 : 4 - val;
}

//////////////////////////////////////////
//
// display functions
//
void HT16K33::displayClear()
{
  uint8_t x[4] = {HT16K33_SPACE, HT16K33_SPACE, HT16K33_SPACE, HT16K33_SPACE};
  display(x);
  displayColon(false);
}

// -999..9999
// DIV10 & DIV100 optimize?
void HT16K33::displayInt(int n)
{
  uint8_t x[4], h, l;
  bool neg = (n < 0);
  if (neg) n = -n;
  h = n / 100;
  l = n - h * 100;
  x[0] = h / 10;
  x[1] = h - x[0] * 10;
  x[2] = l / 10;
  x[3] = l - x[2] * 10;

  if (neg)
  {
    if (_digits >= 3)
    {
      x[0] = HT16K33_MINUS;
    }
    else
    {
      int i = 0;
      for (i = 0; i < (4 - _digits); i++)
      {
        if (x[i] != 0) break;
        x[i] = HT16K33_SPACE;
      }
      x[i-1] = HT16K33_MINUS;
    }
  }
  display(x);
}

// 0000..FFFF
void HT16K33::displayHex(uint16_t n)
{
  uint8_t x[4], h, l;
  h = n >> 8;
  l = n & 0xFF;
  x[3] = l & 0x0F;
  x[2] = l >> 4;
  x[1] = h & 0x0F;;
  x[0] = h >> 4;
  display(x);
}

// 00.00 .. 99.99
void HT16K33::displayDate(uint8_t left, uint8_t right)
{
  uint8_t x[4];
  x[0] = left / 10;
  x[1] = left - x[0] * 10;
  x[2] = right / 10;
  x[3] = right - x[2] * 10;
  display(x, 1);
  displayColon(false);
}

// 00:00 .. 99:99
void HT16K33::displayTime(uint8_t left, uint8_t right)
{
  uint8_t x[4];
  x[0] = left / 10;
  x[1] = left - x[0] * 10;
  x[2] = right / 10;
  x[3] = right - x[2] * 10;
  display(x);
  displayColon(false);
}

// only 0.000 .. 9999.
// TODO x.yEz
void HT16K33::displayFloat(float f)
{
  if (f > 9999 || f < -999 ) 
  {
    // display overflow ?
    return;
  }
  bool neg = (f < 0);
  if (neg) f = -f;
  int w = f;

  int pt = 3;
  if (w < 1000) pt = 2; 
  if (w < 100) pt = 1; 
  if (w < 10) pt = 0;

  if (f >= 1)
  {
    while (f < 1000) f *= 10;
    w = round(f);
  }
  else
  {
    w = round(f * 1000);
  }

  uint8_t x[4], h, l;
  h = w / 100;
  l = w - h * 100;
  x[0] = h / 10;
  x[1] = h - x[0] * 10;
  x[2] = l / 10;
  x[3] = l - x[2] * 10;
  if (neg) // corrections for neg => all shift one position
  {
    x[3] = x[2];
    x[2] = x[1];
    x[1] = x[0];
    x[0] = HT16K33_MINUS;
    pt++;
  }
  display(x, pt);
}

void HT16K33::displayTest(uint8_t del)
{
  for (int i = 0; i < 256; i++)
  {
    writePos(0, i);
    writePos(1, i);
    writePos(2, i);
    writePos(3, i);
    writePos(4, i);
    delay(del);
  }
}

void HT16K33::displayRaw(uint8_t *arr, bool colon)
{
  writePos(0, arr[0]);
  writePos(1, arr[1]);
  writePos(3, arr[2]);
  writePos(4, arr[3]);
  writePos(2, colon ? 255 : 0);
}

void HT16K33::displayVULeft(uint8_t val)
{
  uint8_t ar[4];
  for (int idx = 3; idx >=0; idx--)
  {
    if (val >= 2)
    {
      ar[idx] = 0x36;       //   ||
      val -= 2;
    }
    else if (val == 1)
    {
      ar[idx] = 0x06;        //   _|
      val = 0;
    }
    else ar[idx] = 0x00;     //   __
  }
  displayRaw(ar);
}

void HT16K33::displayVURight(uint8_t val)
{
  uint8_t ar[4];
  for (uint8_t idx = 0; idx < 4; idx++)
  {
    if (val >= 2)
    {
      ar[idx] = 0x36;       //   ||
      val -= 2;
    }
    else if (val == 1)
    {
      ar[idx] = 0x30;        //   |_
      val = 0;
    }
    else ar[idx] = 0x00;     //   __
  }
  displayRaw(ar);
}

void HT16K33::display(uint8_t *arr)
{
  for (uint8_t i = 0; i < (4 - _digits); i++)
  {
    if (arr[i] != 0) break;
    arr[i] = HT16K33_SPACE;
  }
  writePos(0, charmap[arr[0]]);
  writePos(1, charmap[arr[1]]);
  writePos(3, charmap[arr[2]]);
  writePos(4, charmap[arr[3]]);

  // debug to Serial
  // dumpSerial(arr, 0);
}

void HT16K33::display(uint8_t *arr, uint8_t pnt)
{
  // debug to Serial
  // dumpSerial(arr, pnt);

  writePos(0, charmap[arr[0]], pnt == 0);
  writePos(1, charmap[arr[1]], pnt == 1);
  writePos(3, charmap[arr[2]], pnt == 2);
  writePos(4, charmap[arr[3]], pnt == 3);
}

void HT16K33::displayColon(uint8_t on)
{
  writePos(2, on ? 2 : 0);
}

void HT16K33::dumpSerial(uint8_t *arr, uint8_t pnt)
{
  // to debug without display
  for (int i = 0; i < 4; i++)
  {
    if (arr[i] == HT16K33_SPACE) Serial.print(" ");
    else if (arr[i] == HT16K33_MINUS) Serial.print("-");
    else Serial.print(arr[i]);
  }
  Serial.print(" ");
  Serial.println(pnt);
}

//////////////////////////////////////////////////////////
//
// PRIVATE
//
void HT16K33::writeCmd(uint8_t cmd)
{
  Wire.beginTransmission(_addr);
  Wire.write(cmd);
  Wire.endTransmission();
}

void HT16K33::writePos(uint8_t pos, uint8_t mask)
{
  if (_cache && (_displayCache[pos] == mask)) return;
  Wire.beginTransmission(_addr);
  Wire.write(pos * 2);
  Wire.write(mask);
  Wire.endTransmission();
  _displayCache[pos] = _cache ? mask : HT16K33_NONE;
}

void HT16K33::writePos(uint8_t pos, uint8_t mask, bool pnt)
{
  if (pnt) mask |= 0x80;
  else mask &= 0x7F;
  writePos(pos, mask);
}

// -- END OF FILE --
