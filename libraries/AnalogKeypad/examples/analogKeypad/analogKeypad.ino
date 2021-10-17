//
//    FILE: analogKeypad.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo 4x4 analogue keypad
//
// https://www.tinytronics.nl/shop/nl/arduino/accessoires/robotdyn-keypad-4x4-matrix-analoog?search=matrix
//


#include "AnalogKeypad.h"

AnalogKeypad AKP(A0);
uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ANALOGKEYPAD_LIB_VERSION:\t");
  Serial.println(ANALOGKEYPAD_LIB_VERSION);

  Serial.println();
  test3();
  
  for (int i = 0; i < 100; i++) test1();
  for (int i = 0; i < 100; i++) test2();
}

void loop()
{
}


// 
void test1()
{
  int button = AKP.pressed();
  if (button != 0)
  {
    Serial.print("pressed:\t");
    Serial.println(button, HEX);
  }
  delay(100);
}


// use the "event" interface
void test2()
{
  uint8_t e = AKP.event();
  switch (e)
  {
    case 0x80:
      Serial.print("press\t");
      Serial.println(AKP.key());
      break;
    case 0x40:
      Serial.print("release\t");
      Serial.println(AKP.key());
      break;
    case 0x20:
      Serial.print("repeat\t");
      Serial.println(AKP.key());
      break;
    case 0x10:
      Serial.print("change\t");
      Serial.println(AKP.key());
      break;
    default:
      break;
  }
  delay(100);
}

// timing test
void test3()
{
  start = micros();
  int button = AKP.read();
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(button);
  delay(100);
}

// -- END OF FILE --
