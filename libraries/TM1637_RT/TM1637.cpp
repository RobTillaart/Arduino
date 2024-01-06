//
//    FILE: TM1637.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2019-10-28
// VERSION: 0.4.0
// PURPOSE: TM1637 library for Arduino
//     URL: https://github.com/RobTillaart/TM1637_RT

//  NOTE:
//  on the inexpensive TM1637 boards @wfdudley has used, keyScan
//  works if you add a 1000 ohm pull-up resistor from DIO to 3.3v
//  This reduces the rise time of the DIO signal when reading the key info.
//  If one only uses the pull-up inside the microcontroller,
//  the rise time is too long for the data to be read reliably.


#include "TM1637.h"


#define TM1637_ADDR_AUTO           0x40
#define TM1637_READ_KEYSCAN        0x42
#define TM1637_ADDR_FIXED          0x44

#define TM1637_CMD_SET_DATA        0x40
#define TM1637_CMD_SET_ADDR        0xC0
#define TM1637_CMD_DISPLAY         0x88

//  Special chars
#define TM1637_SPACE      16
#define TM1637_MINUS      17
#define TM1637_DEGREE     18


/***************
   ---
  |   |
   ---
  |   |
   ---    .


      -01-
  20 |    | 02
      -40-
  10 |    | 04
      -08-    .80

*/


// PROGMEM ?


static uint8_t seg[] =
{
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,   // 0 - 9
  0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00, 0x40, 0x63          // A - F, ' ', '-', '°'
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
  _digits     = 6;
  _brightness = 3;
  _bitDelay   = 10;
}


void TM1637::begin(uint8_t clockPin, uint8_t dataPin, uint8_t digits)
{
  _clockPin = clockPin;
  _dataPin  = dataPin;
  _digits   = digits;

  pinMode(_clockPin, OUTPUT);
  digitalWrite(_clockPin, HIGH);
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, HIGH);

  //  TODO: replace _digits by a display enumeration?
  if (_digits == 4)
  {
    setDigitOrder(3, 2, 1, 0);
  }
  else  //  (_digits == 6 )    //  default
  {
    setDigitOrder(3, 4, 5, 0, 1, 2);
  }
}


void TM1637::displayInt(long value)
{
  for (int i = 0; i < 8; i++) _data[i] = TM1637_SPACE;  //  16

  long v = value;
  int last = _digits;
  bool neg = (v < 0);
  if (neg)
  {
    v = -v;
    last--;
    _data[last] = TM1637_MINUS;
  }

  for (int i = 0; i < last; i++)
  {
    long t = v / 10;
    _data[i] = v - 10 * t;   //  faster than %
    v = t;
  }

  displayRaw(_data, -1);
}


void TM1637::displayFloat(float value)
{
  for (int i = 0; i < 8; i++) _data[i] = TM1637_SPACE;  //  16

  float v  = value;
  int dpos = _digits - 1;
  int last = _digits;
  bool neg = (v < 0);

  if (neg)
  {
    v = -v;
    dpos--;
    last--;
    _data[last] = TM1637_MINUS;
  }

  while (v >= 10)
  {
    v /= 10;
    dpos--;
  }
  for (int i = last-1; i > -1; i--)
  {
    int d = v;
    _data[i] = d;
    v -= d;
    v *= 10;
  }
  displayRaw(_data, dpos);
}


void TM1637::displayFloat(float value, uint8_t fixedPoint)
{
  for (int i = 0; i < 8; i++) _data[i] = TM1637_SPACE;  //  16

  float v   = value;
  int dpos  = _digits - 1;
  int last  = _digits;
  bool neg  = (v < 0);
  int point = fixedPoint + 1;

  if (neg)
  {
    v = -v;
    dpos--;
    last--;
  }
  //  v += 0.0001; //  Bug fix for 12.999 <> 13.000
  v += 0.001;      //  Bug fix for 12.99 <> 13.00

  while (v >= 10)
  {
    v /= 10;
    dpos--;
    point++;
  }

  if (neg)
  {
    _data[point] = TM1637_MINUS;
  }

  for (int i = point - 1; i > -1; i--)
  {
    int d = v;
    _data[i] = d;
    v -= d;
    v *= 10;
  }
  displayRaw(_data, fixedPoint);
}


void TM1637::displayHex(uint32_t value)
{
  for (int i = 0; i < 8; i++) _data[i] = TM1637_SPACE;  //  16

  uint32_t v = value;
  for (int i = 0; i < _digits; i++)
  {
    uint32_t t = v / 16;
    _data[i] = v & 0x0F;     //  faster than %
    v = t;
  }
  displayRaw(_data, -1);
}


void TM1637::displayTime(uint8_t hour, uint8_t minute, bool colon)
{
  if (_digits != 4) return;
  for (int i = 0; i < 8; i++) _data[i] = TM1637_SPACE;  //  16

  //  optional
  //  if (hour > 99) hour = 99;
  //  if (minute > 99) minute = 99;
  _data[3] = hour / 10;
  _data[2] = hour % 10;
  _data[1] = minute / 10;
  _data[0] = minute % 10;
  displayRaw(_data, colon ? 2 : -1);
}


void TM1637::displayTwoInt(int left, int right, bool colon)
{
  if (_digits != 4) return;
  for (int i = 0; i < 8; i++) _data[i] = TM1637_SPACE;  //  16

  //  optional
  //  if (left < -9)  left = -9;
  //  if (left > 99)  left = 99;
  //  if (right < -9) right = -9;
  //  if (right > 99) right = 99;
  if (left < 0)
  {
    _data[3] = TM1637_MINUS;
    _data[2] = -left;
  }
  else
  {
    _data[3] = left / 10;
    _data[2] = left % 10;
  }
  if (right < 0)
  {
    _data[1] = TM1637_MINUS;
    _data[0] = -right;
  }
  else
  {
    _data[1] = right / 10;
    _data[0] = right % 10;
  }
  displayRaw(_data, colon ? 2 : -1);
}


void TM1637::displayCelsius(int temp, bool colon)
{
  if (_digits != 4) return;
  for (int i = 0; i < 8; i++) _data[i] = TM1637_SPACE;  //  16
  _data[0] = 12;             //  C
  _data[1] = TM1637_DEGREE;  //  ° degree sign

  if (temp < -9) temp = -9;
  if (temp > 99) temp = 99;
  if (temp < 0)
  {
    _data[3] = TM1637_MINUS;
    _data[2] = -temp;
  }
  else
  {
    _data[3] = temp / 10;
    _data[2] = temp % 10;
  }
  displayRaw(_data, colon ? 2 : -1);
}


void TM1637::displayFahrenheit(int temp, bool colon)
{
  if (_digits != 4) return;
  for (int i = 0; i < 8; i++) _data[i] = TM1637_SPACE;  //  16
  _data[0] = 15;             //  F
  _data[1] = TM1637_DEGREE;  //  ° degree sign

  if (temp < -9) temp = -9;
  if (temp > 99) temp = 99;
  if (temp < 0)
  {
    _data[3] = TM1637_MINUS;
    _data[2] = -temp;
  }
  else
  {
    _data[3] = temp / 10;
    _data[2] = temp % 10;
  }
  displayRaw(_data, colon ? 2 : -1);
}


void TM1637::displayClear()
{
  for (int i = 0; i < 8; i++) _data[i] = TM1637_SPACE;  //  16
  displayRaw(_data, -1);
}


void TM1637::displayRefresh()
{
  //  display internal buffer again.
  displayRaw(_data, _lastPointPos);
}


void TM1637::hideSegment(uint8_t idx)
{
  if (idx > 7) return;
  uint8_t tmp[8];
  for (int i = 0; i < 8; i++) tmp[i] = _data[i];
  tmp[idx] = TM1637_SPACE;
  displayRaw(tmp, _lastPointPos);
}


void TM1637::hideMultiSegment(uint8_t mask)
{
  uint8_t tmp[8];
  for (int i = 0; i < 8; i++)
  {
    if ((mask & 0x01) == 0x01) tmp[i] = TM1637_SPACE;
    else tmp[i] = _data[i];
    mask >>= 1;
  }
  displayRaw(tmp, _lastPointPos);
}


void TM1637::setBrightness(uint8_t brightness)
{
  _brightness = brightness;
  if (_brightness > 0x07) _brightness = 0x07;
}


uint8_t TM1637::getBrightness()
{
  return _brightness;
}


void TM1637::setBitDelay(uint8_t bitDelay)
{
  _bitDelay = bitDelay;
}


uint8_t TM1637::getBitDelay()
{
  return _bitDelay;
}


void TM1637::setDigitOrder(uint8_t a, uint8_t b,
                uint8_t c, uint8_t d, uint8_t e,
                uint8_t f, uint8_t g, uint8_t h)
{
  _digitOrder[0] = a;
  _digitOrder[1] = b;
  _digitOrder[2] = c;
  _digitOrder[3] = d;
  _digitOrder[4] = e;
  _digitOrder[5] = f;
  _digitOrder[6] = g;
  _digitOrder[7] = h;
}


//  Set sign bit on any char to display decimal point
void TM1637::displayPChar( char * data )
{
  start();
  writeByte(TM1637_ADDR_AUTO);
  stop();

  start();
  writeByte(TM1637_CMD_SET_ADDR);

  for (int d = _digits-1; d >= 0 ; d--)
  {
    uint8_t i = _digitOrder[d];
    writeByte( asciiTo7Segment(data[i]) );
  }
  stop();

  start();
  writeByte(TM1637_CMD_DISPLAY | _brightness);
  stop();
}


void TM1637::displayRaw(uint8_t * raw, uint8_t pointPos)
{
  //  DEBUG
  // for (uint8_t d = 0; d < _digits; d++)
  // {
    // uint8_t x = raw[_digits - d - 1];
    // if (x < 0x10) Serial.print('0');
    // Serial.print(x, HEX);
    // Serial.print('-');
  // }
  // Serial.println();

  uint8_t b = 0;
  _lastPointPos = pointPos;

  start();
  writeByte(TM1637_ADDR_AUTO);
  stop();

  start();
  writeByte(TM1637_CMD_SET_ADDR);

  for (uint8_t d = 0; d < _digits; d++)
  {
    uint8_t i = _digitOrder[d];
    bool hasPoint = raw[i] & 0x80;
    raw[i] &= 0x7f;
    if (raw[i] <= 18)        //  HEX DIGIT
    {
      b = seg[raw[i]];
    }
    else if (raw[i] <= 37)   //  ASCII
    {
      b = alpha_seg[raw[i] - 18];
    }
    //  do we need a decimal point
    if ((i == pointPos) || hasPoint)
    {
      b |= 0x80;
    }
    writeByte(b);
  }
  stop();

  start();
  writeByte(TM1637_CMD_DISPLAY | _brightness);
  stop();
}


void TM1637::dumpCache()
{
  for (int i = 0; i < 8; i++)
  {
    Serial.print(_data[i]);
    Serial.print(" ");
  }
  Serial.println();
}


//////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t TM1637::writeByte(uint8_t data)
{
  //  shift out data 8 bits LSB first
  for (uint8_t i = 8; i > 0; i--)
  {
    writeSync(_clockPin, LOW);
    writeSync(_dataPin, data & 0x01);
    writeSync(_clockPin, HIGH);
    data >>= 1;
  }

  writeSync(_clockPin, LOW);
  writeSync(_dataPin, HIGH);
  writeSync(_clockPin, HIGH);

  //  get ACKNOWLEDGE
  pinMode(_dataPin, INPUT);
  delayMicroseconds(_bitDelay);
  uint8_t rv = digitalRead(_dataPin);

  //  FORCE OUTPUT LOW
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
  delayMicroseconds(_bitDelay);
  return rv;
}


void TM1637::start()
{
  writeSync(_clockPin, HIGH);
  writeSync(_dataPin, HIGH);
  writeSync(_dataPin, LOW);
  writeSync(_clockPin, LOW);
}


void TM1637::stop()
{
  writeSync(_clockPin, LOW);
  writeSync(_dataPin, LOW);
  writeSync(_clockPin, HIGH);
  writeSync(_dataPin, HIGH);
}


void TM1637::writeSync(uint8_t pin, uint8_t val)
{
  digitalWrite(pin, val);

  #if defined(ESP32)
    nanoDelay(21);  //  delay(2) is not enough in practice.
  #endif
  //  other processors may need other "nanoDelay(n)"
}


//  keyScan results are reversed left for right from the data sheet.
//  here are the values returned by keyScan():
//
//  pin         2     3     4     5     6     7     8     9
//            sg1   sg2   sg3   sg4   sg5   sg6   sg7   sg8
//  19   k1  0xf7  0xf6  0xf5  0xf4  0xf3  0xf2  0xf1  0xf0
//  20   k2  0xef  0xee  0xed  0xec  0xeb  0xea  0xe9  0xe8

uint8_t TM1637::keyScan(void)
{
  uint8_t halfDelay = _bitDelay >> 1;
  uint8_t key;
  start();
  key = 0;
  writeByte(TM1637_READ_KEYSCAN);  //  includes the ACK, leaves DATA low
  pinMode(_dataPin, INPUT_PULLUP);

  for (uint8_t i = 0; i <= 7; i++) {
    writeSync(_clockPin, LOW);
    delayMicroseconds(halfDelay);
    writeSync(_clockPin, HIGH);
    delayMicroseconds(halfDelay);
    key >>= 1;
    key |= (digitalRead(_dataPin)) ? 0x80 : 0x00 ;
  }

  writeSync(_clockPin, LOW);
  delayMicroseconds(halfDelay);
  writeSync(_clockPin, HIGH);

  //  wait for ACK
  delayMicroseconds(halfDelay);

  //  FORCE OUTPUT LOW
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
  delayMicroseconds(halfDelay);
  stop();
  return key;
}


//  nanoDelay() makes it possible to go into the sub micron delays.
//  It is used to lengthen pulses to be minimal 400 ns but not much longer.
//  See datasheet.
void TM1637::nanoDelay(uint16_t n)
{
  volatile uint16_t i = n;
  while (i--);
}


uint8_t TM1637::asciiTo7Segment ( char c )
{
  /*
      -01-
  20 |    | 02
      -40-
  10 |    | 04
      -08-     .80
  */
  //  7+1  Segment patterns for ASCII 0x30-0x5F
  const uint8_t asciiToSegments[] = {
    0x3f,0x06,0x5b,0x4f, 0x66,0x6d,0x7d,0x07,  //  0123 4567
    0x7f,0x6f,0x09,0x89, 0x58,0x48,0x4c,0xD3,  //  89:; <=>?
    0x5f,0x77,0x7c,0x39, 0x5E,0x79,0x71,0x3d,  //  @ABC DEFG
    0x76,0x06,0x0E,0x75, 0x38,0x37,0x54,0x5c,  //  HIJK LMNO
    0x73,0x67,0x50,0x6D, 0x78,0x3E,0x1C,0x9c,  //  PQRS TUVW
    0x76,0x6E,0x5B,0x39, 0x52,0x0F,0x23,0x08   //  XYZ[ /]^_
  };

  uint8_t segments = c & 0x80;
  c &= 0x7f;
  if ( c >= 0x60 ) c -= 0x20 ;                 //  a-z -> A-Z
  if ( c == '.' ) segments = 0x80;             //  decimal point only
  if ( c == '-' ) segments |= 0x40;            //  minus sign
  if ( ( c >= 0x30 ) && ( c <= 0x5F ) ) {
    segments |= asciiToSegments[ c - 0x30 ];
  }
  return segments;
}


//  -- END OF FILE --

