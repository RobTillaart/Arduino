//
//    FILE: TM1637.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2019-10-28
// VERSION: 0.3.0
// PURPOSE: TM1637 library for Arduino
//     URL: https://github.com/RobTillaart/TM1637_RT
//
//  HISTORY:
//  0.1.0   2019-10-28  initial version
//  0.1.1   2021-02-15  first release + examples. 
//  0.1.2   2021-04-16  update readme, fix default values.
//  0.2.0   2021-09-26  add ESP32 support - kudos to alexthomazo
//          2021-10-07  add support for letters g-z; added keyscan()
//                      tested on ESP8266
//  0.3.0   2021-10-27  improved keyscan + documentation - kudos to wfdudley


//          tested on 6 digits display only for now.


// NOTE: on the inexpensive TM1637 boards @wfdudley has used, keyscan
// works if you add a 1000 ohm pullup resistor from DIO to 3.3v
// This reduces the rise time of the DIO signal when reading the key info.
// If one only uses the pull-up inside the microcontroller, 
// the rise time is too long for the data to be read reliably.


#include "TM1637.h"


#define TM1637_ADDR_AUTO           0x40
#define TM1637_READ_KEYSCAN        0x42
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

static uint8_t alpha_seg[] =
{
    0x00, 0x74, 0x10, 0x00,      // g, h, i, j,
    0x00, 0x38, 0x00, 0x54,      // k, l, m, n,
    0x5c, 0x00, 0x00, 0x50,      // o, p, q, r,
    0x00, 0x31, 0x1c, 0x1c,      // s, t, u, v,
    0x00, 0x00, 0x00, 0x00       // w, x, y, z
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
  uint8_t b, dp;
  start();
  writeByte(TM1637_ADDR_AUTO);
  stop();

  start();
  writeByte(TM1637_CMD_SET_ADDR);
  for (uint8_t i = 3; i < 6 ; i++)
  {
    dp = data[i] & 0x80;
    data[i] &= 0x7f;
    if(data[i] <= 17) {
      b = seg[data[i]];
    }
    else if(data[i] <= 37) {
      b = alpha_seg[data[i]-18];
    }
    if (i == pointPos || dp) b |= 0x80;
    writeByte(b);
  }
  for (uint8_t i = 0; i < 3 ; i++)
  {
    dp = data[i] & 0x80;
    data[i] &= 0x7f;
    if(data[i] <= 17) {
      b = seg[data[i]];
    }
    else if(data[i] <= 37) {
      b = alpha_seg[data[i]-18];
    }
    if (i == pointPos || dp) b |= 0x80;
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
    writeSync(_clock, LOW);
    writeSync(_data, data & 0x01);
    writeSync(_clock, HIGH);
    data >>= 1;
  }

  writeSync(_clock, LOW);
  writeSync(_data, HIGH);
  writeSync(_clock, HIGH);

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
  writeSync(_clock, HIGH);
  writeSync(_data, HIGH);
  writeSync(_data, LOW);
  writeSync(_clock, LOW);
}


void TM1637::stop()
{
  writeSync(_clock, LOW);
  writeSync(_data, LOW);
  writeSync(_clock, HIGH);
  writeSync(_data, HIGH);
}


void TM1637::writeSync(uint8_t pin, uint8_t val) 
{
  digitalWrite(pin, val);

  #if defined(ESP32)
    nanoDelay(2);
  #endif
  // other processors may need other "nanoDelay(n)"
}


// keyscan results are reversed left for right from the data sheet.
// here are the values returned by keyscan():
// pin       2    3    4    5    6    7    8    9
//         sg1  sg2  sg3  sg4  sg5  sg6  sg7  sg8
// 19  k1 0xf7 0xf6 0xf5 0xf4 0xf3 0xf2 0xf1 0xf0
// 20  k2 0xef 0xee 0xed 0xec 0xeb 0xea 0xe9 0xe8

uint8_t TM1637::keyscan(void)
{
  uint8_t halfDelay = _bitDelay >> 1;
  uint8_t key;
  start();
  key = 0;
  writeByte(TM1637_READ_KEYSCAN);	// includes the ACK, leaves DATA low
  pinMode(_data, INPUT_PULLUP);

  for (uint8_t i = 0; i <= 7; i++) {
    writeSync(_clock, LOW);
    delayMicroseconds(halfDelay);
    writeSync(_clock, HIGH);
    delayMicroseconds(halfDelay);
    key >>= 1;
    key |= (digitalRead(_data)) ? 0x80 : 0x00 ;
  }

  writeSync(_clock, LOW);
  delayMicroseconds(halfDelay);
  writeSync(_clock, HIGH);

  // wait for ACK
  delayMicroseconds(halfDelay);

  // FORCE OUTPUT LOW
  pinMode(_data, OUTPUT);
  digitalWrite(_data, LOW);
  delayMicroseconds(halfDelay);
  stop();
  return key;
}


// nanoDelay() makes it possible to go into the sub micron delays. 
// It is used to lengthen pulses to be minimal 400 ns but not much longer. See datasheet.
void TM1637::nanoDelay(uint16_t n)
{
  volatile uint16_t i = n;
  while (i--);
}

// -- END OF FILE --
