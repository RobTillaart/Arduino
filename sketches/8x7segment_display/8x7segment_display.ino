//
//    FILE: 8x7segment_display.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.2
// PURPOSE: demo 8x7segment display with 74HC595 controllers
// LICENSE: MIT
// HISTORY: based upon demo code @ Tinytronics
// 0.5.1    added PROGMEM
// 0.5.2    added showRaw(uint8_t ar[8]) showVUvertical() howEqualizer()
//
//     TODO: put all in a class?


const int datapin = 5;  //DIO
const int clockpin = 6; //SCK
const int latchpin = 7; //RCK

/* Segment bit location(7=MSB, 0=LSB):

      |--0--|
     5|     |1
      |--6--|
     4|     |2
      |--3--| **7
*/

// Array with possible values(0 = segment ON, 1 = segment off)
const byte value[] PROGMEM = {
  B11000000, // 0
  B11111001, // 1
  B10100100, // 2
  B10110000, // 3
  B10011001, // 4
  B10010010, // 5
  B10000010, // 6
  B11111000, // 7
  B10000000, // 8
  B10010000, // 9
  B10001000, // A    TODO A..F
  B10000011, // b
  B11000110, // C
  B10100001, // d
  B10000110, // E
  B10001110, // F
  B11111111, // 16  space = display nothing
  B10111111, // 17  -    sign
  B11001001, // 18  ||   sign  - VU(2) vertical (value 1 is |)
  B11111101, // 19  |    sign  - VU(1) vertical stereo left
  B11011101, // 20  ||   sign  - VU(2) vertical stereo left
  B11111011, // 21  |    sign  - VU(1) vertical stereo right
  B11101011, // 22  ||   sign  - VU(2) vertical stereo right
  B11110111, // 23  |    sign  - equalizer(1) horizontal   equalizer(0) == space   idx=17;
  B10110111, // 24  ||   sign  - equalizer(2) horizontal
  B10110110, // 25  |||  sign  - equalizer(3) horizontal
};

const byte digit[] PROGMEM = {
  B00010000, // left segment
  B00100000,
  B01000000,
  B10000000,
  B00000001,
  B00000010,
  B00000100,
  B00001000
}; // right segment

////////////////////////////////////////////////////////////////////////

void showVUvertical(uint8_t val)
{
  for (int i = 7; i > -1; i--)
  {
    if (val == 0) return;
    if (val >= 2)
    {
      showDigit(i, 18, false);  // digit 8 also works very well...
      val -= 2;
      continue;
    }
    if (val == 1)
    {
      showDigit(i, 1, false);
      return;
    }
  }
}

// TODO same values at once would be faster
void showEqualizer(uint8_t ar[8])  // values 0..3
{
  for (int i = 0; i < 8; i++)
  {
    switch (ar[i])
    {
      case 3: showDigit(i, 25, false); break;
      case 2: showDigit(i, 24, false); break;
      case 1: showDigit(i, 23, false); break;
      case 0: showDigit(i, 16, false); break;
      default: break;
    }
  }
}



void showRaw(uint8_t ar[8])
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(latchpin, LOW);
    shiftOut(datapin, clockpin, MSBFIRST, ar[i]);
    shiftOut(datapin, clockpin, MSBFIRST, pgm_read_byte_near(digit + i));
    digitalWrite(latchpin, HIGH);
  }
}


void showHex(uint32_t value)
{
  uint32_t v = value;
  for (int i = 7; i > -1; i--)
  {
    uint32_t t = v / 16;
    int d = v - 16 * t;  // faster than %
    v = t;
    showDigit(i, d, false);
  }
}


// implementation of showing a float number in one go.
// range positive from 0.0000001 - 99999999 + 0  (8 digits)
// range negative from -0.000001 - -9999999      (7 digits + sign)
// needs to be called also as much as possible, once every millisecond.
void showFloat(float value)
{
  float v = value;
  int dpos = 0;
  int start = 0;
  bool neg = (v < 0);

  if (neg)
  {
    v = -v;
    dpos++;
    start = 1;
    showDigit(0, 17, false);
  }

  while (v >= 10)
  {
    v /= 10;
    dpos++;
  }
  for (int i = start; i < 8; i++)
  {
    int d = v;
    showDigit(i, d, i == dpos);
    v -= d;
    v *= 10;
  }
}


// implementation of showing a long number in one go.
// range from -9999999 (7 digits + sign)   -   99999999  (8 digits)
// needs to be called also as much as possible, once every millisecond.
void showLong(long value)
{
  long v = value;
  int last = -1;
  bool neg = (v < 0);
  if (neg)
  {
    v = -v;
    last = 0;
    showDigit(0, 17, false);
  }

  for (int i = 7; i > last; i--)
  {
    long t = v / 10;
    int d = v - 10 * t;  // faster than %
    v = t;
    showDigit(i, d, false);
  }
}

// clear does write a space to all segments in one step
//
void clear()
{
  showDigit(0xFF, 16, false);
}


// displaying single digit
// shiftOut could be replaced by faster implementation
// as the datapin and clockpin are always same and
// the order is always MSBFIRST
// see also my FastShiftOut library
void showDigit(int segmentnum, int number, bool showdecimalpoint)
{
  byte value_temp = pgm_read_byte_near(value + number);
  if (showdecimalpoint) value_temp &= B01111111;

  digitalWrite(latchpin, LOW);
  shiftOut(datapin, clockpin, MSBFIRST, value_temp);
  shiftOut(datapin, clockpin, MSBFIRST, pgm_read_byte_near(digit + segmentnum));
  digitalWrite(latchpin, HIGH);
}

///////////////////////////////////////////////////////////////////////////////////
//
// demo sketch
//
uint32_t counter = 0;
uint32_t start = 0;
uint32_t stop = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  pinMode(clockpin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(datapin, OUTPUT);
}


void loop()
{
  //  for (float p = PI / 100000000; p < 100000000; p *= 10)
  //  {
  //    for (int j = 0; j < 200; j++)  // keep updating
  //    {
  //      showFloat(p);
  //    }
  //  }
  //
  //  clear();
  //  delay(1000);
  //
  //  for (float p = PI / 100000000; p < 100000000; p *= 10)
  //  {
  //    for (int j = 0; j < 200; j++)
  //    {
  //      showFloat(-p);
  //    }
  //  }
  //
  //  clear();
  //  delay(1000);
  //
  //  for (int i = 0; i < 10; i++)
  //  {
  //    long r = random(10000000);
  //    for (int j = 0; j < 200; j++)
  //    {
  //      showLong(r);
  //    }
  //  }
  //
  //  clear();
  //  delay(1000);

  //  for (int i = 0; i < 10; i++)
  //  {
  //    long r = -random(10000000);
  //    for (int j = 0; j < 200; j++)
  //    {
  //      showLong(r);
  //    }
  //  }
  //
  //  clear();
  //  delay(1000);

  //  for (int i = 0; i < 10; i++)
  //  {
  //    uint32_t r = random(0x7FFFFFFF);
  //    Serial.println(r);
  //    for (int j = 0; j < 200; j++)
  //    {
  //      showHex(r);
  //    }
  //  }
  //  clear();
  //  delay(1000);

  // "Alien display"
  //  for (int i = 0; i < 10; i++)
  //  {
  //    uint8_t ar[8];
  //    for (int j = 0; j < 8; j++) ar[j] = random(255);
  //    for (int j = 0; j < 200; j++)
  //    {
  //      showRaw(ar);
  //    }
  //  }
  //  clear();
  //  delay(1000);

  //  for (int i = 0; i < 255; i++)
  //  {
  //    uint8_t ar[8];
  //    for (int j = 0; j < 8; j++) ar[j] = i;
  //    for (int j = 0; j < 200; j++)
  //    {
  //      showRaw(ar);
  //    }
  //  }
  //  clear();
  //  delay(1000);

  //  for (int i = 0; i < 1000; i++)
  //  {
  //    uint8_t value = 8 + 8 * sin(i / 100.0);
  //    for (int j = 0; j < 20; j++)
  //    {
  //      showVUvertical(value);
  //    }
  //  }
  //  clear();
  //  delay(1000);

  for (int i = 0; i < 1000; i++)
  {
    uint8_t ar[8];
    for (int j = 0; j < 8; j++) ar[j] = (i + j) % 4;
    for (int j = 0; j < 80; j++)
    {
      showEqualizer(ar);
    }
  }
  clear();
  delay(1000);
}

// -- END OF FILE --
