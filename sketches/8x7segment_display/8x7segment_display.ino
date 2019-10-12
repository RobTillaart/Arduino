//
//    FILE: 8x7segment_display.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.5.0
// PURPOSE: demo 8x7segment display with 74HC595 controllers
// LICENSE: MIT
// HISTORY: based upon demo code @ Tinytronics
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
byte value[] = { B11000000, // 0
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
                 B11111111, // space = display nothing
                 B10111111, // - sign
               };

byte digit[] = { B00010000, // left segment
                 B00100000,
                 B01000000,
                 B10000000,
                 B00000001,
                 B00000010,
                 B00000100,
                 B00001000
               }; // right segment


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
  uint32_t val = 1;
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
// as the datapin and clockpin are allways same and
// the order is always MSBFIRST
// see also my FastShiftOut library
void showDigit(int segmentnum, int number, bool showdecimalpoint)
{
  byte value_temp = value[number];
  if (showdecimalpoint) value_temp &= B01111111;

  digitalWrite(latchpin, LOW);
  shiftOut(datapin, clockpin, MSBFIRST, value_temp);
  shiftOut(datapin, clockpin, MSBFIRST, digit[segmentnum]);
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

  for (float p = PI / 100000000; p < 100000000; p *= 10)
  {
    for (int i = 0; i < 200; i++)  // keep updating 
    {
      showFloat(p);
    }
  }

  clear();
  delay(1000);

  for (float p = PI / 100000000; p < 100000000; p *= 10)
  {
    for (int i = 0; i < 200; i++)
    {
      showFloat(-p);
    }
  }

  clear();
  delay(1000);

  for (int i = 0; i < 10; i++)
  {
    long r = random(10000000);
    for (int i = 0; i < 400; i++)
    {
      showLong(r);
    }
  }

  clear();
  delay(1000);
  for (int i = 0; i < 10; i++)
  {
    long r = -random(10000000);
    for (int i = 0; i < 400; i++)
    {
      showLong(r);
    }
  }

  clear();
  delay(1000);

  for (int i = 0; i < 10; i++)
  {
    uint32_t r = random(0xFFFFFFFF);
    for (int i = 0; i < 400; i++)
    {
      showHex(r);
    }
  }
  clear();
  delay(1000);
}

// -- END OF FILE --