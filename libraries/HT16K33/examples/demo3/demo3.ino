//
//    FILE: 4x7segmentI2C.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo 3
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33


#include "HT16K33.h"

HT16K33 seg(0x70);

uint32_t start;
uint32_t stop;

uint8_t ar[4];


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HT16K33_LIB_VERSION: ");
  Serial.println(HT16K33_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  seg.begin();

  seg.displayOn();
  seg.suppressLeadingZeroPlaces(0);

  Serial.println("displayTest()");
  seg.displayTest(10);
  seg.displayOff();
  delay(1000);
  seg.displayOn();
  seg.displayColon(false);
}

void loop()
{
  //  comment tests you do not want to see
  test_elsa();
  delay(100);
  test_random();
  delay(100);
  test_VULeft();
  delay(100);
  test_VURight();
  delay(100);
  test_VUStereo();
  delay(100);
}

void test_elsa()
{
  ar[0] = 0x79;
  ar[1] = 0x38;
  ar[2] = 0x6D;
  ar[3] = 0x77;
  seg.displayRaw(ar);
}

void test_random()
{
  for (uint8_t i = 0; i < 4; i++)
  {
    ar[i] = random(256);
  }
  seg.displayRaw(ar);
}

void test_VULeft()
{
  int val = analogRead(A0);
  val = val / 120;          //  0..8
  seg.displayVULeft(val);
}

void test_VURight()
{
  int val = analogRead(A0);
  val = val / 120;  // 0..8
  seg.displayVURight(val);
}

void test_VUStereo()
{
  uint8_t left = analogRead(A0) / 240;   //  0..4
  uint8_t right = analogRead(A1) / 240;  //  0..4
  displayVUStereo(left, right);
}

void displayVUStereo(uint8_t left, uint8_t right)
{
  switch (left)
  {
    case 0:
      ar[0] = 0x00;
      ar[1] = 0x00;
      break;
    case 1:
      ar[0] = 0x00;
      ar[1] = 0x06;
      break;
    case 2:
      ar[0] = 0x00;
      ar[1] = 0x36;
      break;
    case 3:
      ar[0] = 0x06;
      ar[1] = 0x36;
      break;
    case 4:
    default:
      ar[0] = 0x36;
      ar[1] = 0x36;
      break;
  }
  switch (right)
  {
    case 0:
      ar[2] = 0x00;
      ar[3] = 0x00;
      break;
    case 1:
      ar[2] = 0x30;
      ar[3] = 0x00;
      break;
    case 2:
      ar[2] = 0x36;
      ar[3] = 0x00;
      break;
    case 3:
      ar[2] = 0x36;
      ar[3] = 0x30;
      break;
    case 4:
    default:
      ar[2] = 0x36;
      ar[3] = 0x36;
      break;
  }
  seg.displayRaw(ar);

  //  sort of heartbeat
  static bool t = false;
  seg.displayColon(t);
  t = !t;
}

//  -- END OF FILE --
