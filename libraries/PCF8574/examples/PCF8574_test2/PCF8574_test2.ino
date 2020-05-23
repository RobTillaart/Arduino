//
//    FILE: pcf8574_test2.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2016-04-30
//
// PUPROSE: demo rotateLeft, -Right and toggleMask
//

#include "PCF8574.h"
#include <Wire.h>

// adjust addresses if needed
PCF8574 PCF_39(0x39);  // add leds to lines      (used as output)

void setup()
{
  Serial.begin(115200);
  Serial.print("\npcf8574_test2.ino\nlib version: ");
  Serial.println(PCF8574_LIB_VERSION);

  PCF_39.begin();

  PCF_39.write(0, 1);
  for (int i = 0; i < 7; i++)
  {
    PCF_39.rotateLeft();
    delay(100);
  }

  for (int i = 0; i < 7; i++)
  {
    PCF_39.rotateRight();
    delay(100);
  }

  for (int i = 0; i < 7; i++)
  {
    PCF_39.rotateLeft(3);
    delay(100);
  }

  for (int i = 0; i < 7; i++)
  {
    PCF_39.rotateRight(2);
    delay(100);
  }

  for (int i = 0; i < 255; i++)
  {
    PCF_39.toggleMask(i);
    delay(100);
  }

  // 0010 0111  -> 0x27
  // 1110 0100
  PCF_39.write8(0x27);
  for (int i = 0; i < 255; i++)
  {
    PCF_39.reverse();
    delay(100);
  }
}

void loop()
{
}
//
// END OF FILE
//