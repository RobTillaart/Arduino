//
//    FILE: HT16K33.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.2
//    DATE: 2019-02-07
// PURPOSE: Arduino Library for HT16K33 4x7segment display
//     URL: https://github.com/RobTillaart/HT16K33
//
//  HISTORY:
//  0.1.0   2019-02-07  initial version
//  0.1.1   2019-02-07  first stable version
//  0.1.2   2019-02-11  optimized performance
//  0.1.3   2019-10-07  fixed clear, added suppressLeadingZeroPlaces();
//  0.1.4   2019-11-28  added displayRaw(), displayVULeft(), displayVURight()
//  0.1.5   2019-11-30  refactor,
//  0.2.0   2020-06-13  ESP32 support; fix brightness bug;
//  0.2.1   2020-07-15  fix #160 - decimal point
//  0.2.2   2020-10-04  added displayDate() thanks to bepitama
//  0.2.3   2020-10-09  issue #4 add negative values for displayInt()
//  0.2.4   2020-10-10  refactor #5 setDigits() iso suppressLeadingZeroPlaces()
//  0.3.0   2020-10-12  negative float, cache control, extend displayRaw()
//  0.3.1   2020-12-28  arduino-CI, unit test (framework only), 
//  0.3.2   2021-01-14  add WireN suppoprt, 
//                      add refresh(),                  // experimental
//                      add getOverflow();              // experimental
//                      add displayFloat(f, decimals);  // experimental

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
//
// CONSTRUCTOR
//
HT16K33::HT16K33(const uint8_t address, TwoWire *wire)
{
  _addr = address;
  _wire = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool HT16K33::begin(uint8_t sda, uint8_t scl)
{
  _wire = &Wire;
  if ((sda < 255) && (scl < 255))
  {
    _wire->begin(sda, scl);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  reset();
  return true;
}
#endif


bool HT16K33::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  reset();
  return true;
}

bool HT16K33::isConnected()
{
  _wire->beginTransmission(_addr);
  return (0 == _wire->endTransmission());
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


void HT16K33::refresh()
{
  _refresh();
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


// DIV10 & DIV100 optimize?
bool HT16K33::displayInt(int n)
{
  bool inRange = ((-1000 < n) && (n < 10000));
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
  return inRange;
}


// 0000..FFFF
bool HT16K33::displayHex(uint16_t n)
{
  uint8_t x[4], h, l;
  h = n >> 8;
  l = n & 0xFF;
  x[3] = l & 0x0F;
  x[2] = l >> 4;
  x[1] = h & 0x0F;;
  x[0] = h >> 4;
  display(x);
  return true;
}


// 00.00 .. 99.99
bool HT16K33::displayDate(uint8_t left, uint8_t right)
{
  bool inRange = ((left < 100) && (right < 100));
  uint8_t x[4];
  x[0] = left / 10;
  x[1] = left - x[0] * 10;
  x[2] = right / 10;
  x[3] = right - x[2] * 10;
  display(x, 1);
  displayColon(false);
  return inRange;
}


// 00:00 .. 99:99
bool HT16K33::displayTime(uint8_t left, uint8_t right, bool colon)
{
  bool inRange = ((left < 100) && (right < 100));
  uint8_t x[4];
  x[0] = left / 10;
  x[1] = left - x[0] * 10;
  x[2] = right / 10;
  x[3] = right - x[2] * 10;
  display(x);
  displayColon(colon);
  return inRange;
}


// seconds / minutes max 6039 == 99:99
bool HT16K33::displaySeconds(uint16_t seconds, bool colon)
{
  uint8_t left = seconds / 60;
  uint8_t right = seconds - left * 60;
  return displayTime(left, right, colon);
}


bool HT16K33::displayFloat(float f, uint8_t decimals)
{
  bool inRange = ((-999.5 < f) && (f < 9999.5));

  bool neg = (f < 0);
  if (neg) f = -f;

  if (decimals == 2) f = round(f * 100) * 0.01;
  if (decimals == 1) f = round(f * 10) * 0.1;
  if (decimals == 0) f = round(f);

  int whole = f;
  int point = 3;
  if (whole < 1000) point = 2; 
  if (whole < 100) point = 1; 
  if (whole < 10) point = 0;

  if (f >= 1)
  {
    while (f < 1000) f *= 10;
    whole = round(f);
  }
  else
  {
    whole = round(f * 1000);
  }

  uint8_t x[4], h, l;
  h = whole / 100;
  l = whole - h * 100;
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
    point++;
  }
  // add leading spaces
  while (point + decimals < 3)
  {
    x[3] = x[2];
    x[2] = x[1];
    x[1] = x[0];
    x[0] = HT16K33_SPACE;
    point++;
  }

  display(x, point);

  return inRange;
}


/////////////////////////////////////////////////////////////////////
//
// EXPERIMENTAL
//
bool HT16K33::displayFixedPoint0(float f)
{
  bool inRange = ((-999.5 < f) && (f < 9999.5));
  displayFloat(f, 0);
  return inRange;
}

bool HT16K33::displayFixedPoint1(float f)
{
  bool inRange = ((-99.5 < f) && (f < 999.95));
  displayFloat(f, 1);
  return inRange;
}

bool HT16K33::displayFixedPoint2(float f)
{
  bool inRange = ((-9.95 < f) && (f < 99.995));
  displayFloat(f, 2);
  return inRange;
}

bool HT16K33::displayFixedPoint3(float f)
{
  bool inRange = ((0 < f) && (f < 9.9995));
  displayFloat(f, 3);
  return inRange;
}

/////////////////////////////////////////////////////////////////////

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


bool HT16K33::displayVULeft(uint8_t val)
{
  bool inRange = (val < 9); // can display 0..8  bars
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
  return inRange;
}


bool HT16K33::displayVURight(uint8_t val)
{
  bool inRange = (val < 9);
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
  return inRange;
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
    if (i == pnt) Serial.print(".");
  }
  Serial.print(" ");
  Serial.println(pnt);
}


void HT16K33::dumpSerial()
{
  // to debug without display
  for (int i = 0; i < 4; i++)
  {
    if (_displayCache[i] < 0x10) Serial.print("0");
    Serial.print(_displayCache[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}


//////////////////////////////////////////////////////////
//
// PRIVATE
//
void HT16K33::_refresh()
{
  for (uint8_t pos = 0; pos < 4; pos++)
  {
    _wire->beginTransmission(_addr);
    _wire->write(pos * 2);
    _wire->write(_displayCache[pos]);
    _wire->endTransmission();
  }
}

void HT16K33::writeCmd(uint8_t cmd)
{
  _wire->beginTransmission(_addr);
  _wire->write(cmd);
  _wire->endTransmission();
}


void HT16K33::writePos(uint8_t pos, uint8_t mask)
{
  if (_cache && (_displayCache[pos] == mask)) return;
  _wire->beginTransmission(_addr);
  _wire->write(pos * 2);
  _wire->write(mask);
  _wire->endTransmission();
  _displayCache[pos] = _cache ? mask : HT16K33_NONE;
}


void HT16K33::writePos(uint8_t pos, uint8_t mask, bool pnt)
{
  if (pnt) mask |= 0x80;
  // if (_overflow) mask |= 0x80;
  else mask &= 0x7F;
  writePos(pos, mask);
}


// -- END OF FILE --
