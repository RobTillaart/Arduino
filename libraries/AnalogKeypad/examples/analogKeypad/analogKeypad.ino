//
//    FILE: analogKeypad.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo 4x4 analogue keypad
//
// https://www.tinytronics.nl/shop/nl/arduino/accessoires/robotdyn-keypad-4x4-matrix-analoog?search=matrix


#include "AnalogKeypad.h"

AnalogKeypad AKP(A0);  //  adjust if needed


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ANALOGKEYPAD_LIB_VERSION:\t");
  Serial.println(ANALOGKEYPAD_LIB_VERSION);

  Serial.println();

  for (int i = 0; i < 100; i++) test1();
  for (int i = 0; i < 100; i++) test2();
}


void loop()
{
}


//  pressed interface
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


//  event interface
void test2()
{
  uint8_t e = AKP.event();
  switch (e)
  {
    case PRESSED:
      Serial.print("press\t");
      Serial.println(AKP.key());
      break;
    case RELEASED:
      Serial.print("release\t");
      Serial.println(AKP.key());
      break;
    case REPEATED:
      Serial.print("repeat\t");
      Serial.println(AKP.key());
      break;
    case CHANGED:
      Serial.print("change\t");
      Serial.println(AKP.key());
      break;
    default:  //  NOKEY
      break;
  }
  delay(100);
}


//  -- END OF FILE --

