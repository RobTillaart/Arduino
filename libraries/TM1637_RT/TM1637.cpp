//
//    FILE: TM1637.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2019-10-28
// VERSION: 0.1.2
// PURPOSE: TM1637 library for Arduino
//     URL: https://github.com/RobTillaart/TM1637_RT
//
//  HISTORY:
//  0.1.0   2019-10-28  initial version
//  0.1.1   2021-02-15  first release + examples. 
//  0.1.2   2021-04-16  update readme, fix default values.


//          tested on 6 digits display only for now.


#include "TM1637.h"


#define TM1637_ADDR_AUTO           0x40
#define TM1637_ADDR_FIXED          0x44

#define TM1637_CMD_SET_DATA        0x40
#define TM1637_CMD_SET_ADDR        0xC0
#define TM1637_CMD_DISPLAY         0x88


/***************
   ---
  |   |
   ---
  |   |
   ---  .


      -01-
  20 |    | 02
      -40-
  10 |    | 04
      -08-  .80

*/

// PROGMEM ?

static uint8_t seg[] =
{
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,   // 0 - 9
  0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00, 0x40                // A - F, ' ', '-'
};


TM1637::TM1637()
{
  _brightness = 0x03;
  _bitDelay   = 10;
}


void TM1637::init(uint8_t clockPin, uint8_t dataPin, uint8_t digits)
{
  _clock  = clockPin;
  _data   = dataPin;
  _digits = digits;

  pinMode(_clock, OUTPUT);
  digitalWrite(_clock, HIGH);
  pinMode(_data, OUTPUT);
  digitalWrite(_data, HIGH);
}


void TM1637::displayInt(long value)
{
  uint8_t data[8] = { 16, 16, 16, 16, 16, 16, 16, 16};

  long v = value;
  int last = _digits;
  bool neg = (v < 0);
  if (neg)
  {
    v = -v;
    last--;
    data[last] = 17;   // minus sign;
  }

  for (int i = 0; i < last; i++)
  {
    long t = v / 10;
    data[i] = v - 10 * t;  // faster than %
    v = t;
  }

  displayRaw(data, -1);
}


void TM1637::displayFloat(float value)
{
  uint8_t data[8] = { 16, 16, 16, 16, 16, 16, 16, 16};

  float v = value;
  int dpos = _digits-1;
  int last = _digits;
  bool neg = (v < 0);

  if (neg)
  {
    v = -v;
    dpos--;
    last--;
    data[last] = 17;   // minus sign;
  }

  while (v >= 10)
  {
    v /= 10;
    dpos--;
  }
  for (int i = last-1; i > -1; i--)
  {
    int d = v;
    data[i] = d;
    v -= d;
    v *= 10;
  }
  displayRaw(data, dpos);
}


void TM1637::displayHex(uint32_t value)
{
  uint8_t data[8] = { 16, 16, 16, 16, 16, 16, 16, 16};

  uint32_t v = value;
  for (int i = 0; i < _digits; i++)
  {
    uint32_t t = v / 16;
    data[i] = v & 0x0F;  // faster than %
    v = t;
  }
  displayRaw(data, -1);
}


void TM1637::displayClear()
{
  uint8_t data[8] = { 16, 16, 16, 16, 16, 16, 16, 16};
  displayRaw(data, -1);
}


void TM1637::setBrightness(uint8_t b)
{
  _brightness = b;
  if (_brightness > 0x07) _brightness = 0x07;
}


void TM1637::displayRaw(uint8_t * data, uint8_t pointPos)
{
  uint8_t b;
  start();
  writeByte(TM1637_ADDR_AUTO);
  stop();

  start();
  writeByte(TM1637_CMD_SET_ADDR);
  for (uint8_t i = 3; i < 6 ; i++)
  {
    b = seg[data[i]];
    if (i == pointPos) b |= 0x80;
    writeByte(b);
  }
  for (uint8_t i = 0; i < 3 ; i++)
  {
    b = seg[data[i]];
    if (i == pointPos) b |= 0x80;
    writeByte(b);
  }
  stop();

  start();
  writeByte(TM1637_CMD_DISPLAY | _brightness);
  stop();
}


uint8_t TM1637::writeByte(uint8_t data)
{
  // shift out data 8 bits LSB first
  for (uint8_t i = 8; i > 0; i--)
  {
    digitalWrite(_clock, LOW);
    digitalWrite(_data, data & 0x01);
    digitalWrite(_clock, HIGH);
    data >>= 1;
  }
  digitalWrite(_clock, LOW);
  digitalWrite(_data, HIGH);
  digitalWrite(_clock, HIGH);

  // get ACKNOWLEDGE
  pinMode(_data, INPUT);
  delayMicroseconds(_bitDelay);
  uint8_t rv = digitalRead(_data);

  // FORCE OUTPUT LOW
  pinMode(_data, OUTPUT);
  digitalWrite(_data, LOW);
  delayMicroseconds(_bitDelay);
  return rv;
}


void TM1637::start()
{
  digitalWrite(_clock, HIGH);
  digitalWrite(_data, HIGH);
  digitalWrite(_data, LOW);
  digitalWrite(_clock, LOW);
}


void TM1637::stop()
{
  digitalWrite(_clock, LOW);
  digitalWrite(_data, LOW);
  digitalWrite(_clock, HIGH);
  digitalWrite(_data, HIGH);
}


// -- END OF FILE --
