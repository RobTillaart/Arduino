//
//    FILE: demo_VU.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: http://www.adafruit.com/products/1002
//     URL: https://github.com/RobTillaart/HT16K33

// connect potentiometer or so to A0 and A1 for the VU tests


#include "HT16K33.h"

HT16K33  seg(0x70);
uint32_t start, stop;
uint8_t  ar[4];


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
  seg.setDigits(4);

  Serial.println("displayTest()");
  seg.displayTest(10);
  seg.displayOff();
  delay(1000);
  seg.displayOn();
  seg.displayColon(false);
}


void loop()
{
  test_VULeft();
  delay(1000);
  test_VURight();
  delay(1000);
  test_VUStereo();
  delay(1000);
}


void test_VULeft()
{
  for (uint8_t run = 0; run < 50; run++)
  {
    int val = abs((sin(run * PI/ 50)) * 8);
    seg.displayVULeft(val);
    delay(100);
  }
}


void test_VURight()
{
  for (uint8_t run = 0; run < 50; run++)
  {
    int val = analogRead(A0);
    val = val / 120;  // 0..8
    seg.displayVURight(val);
    delay(100);
  }
}


void test_VUStereo()
{
  for (uint8_t run = 0; run < 50; run++)
  {
    // uint8_t left = analogRead(A0) / 240;   // 0..4
    // uint8_t right = analogRead(A1) / 240;  // 0..4
    uint8_t left = random(5);
    uint8_t right = random(5);
    displayVUStereo(left, right);
    delay(100);
  }
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

  // sort of heartbeat
  static bool hb = false;
  seg.displayColon(hb);
  hb = !hb;
}


// -- END OF FILE --

