//
//    FILE: pcf8575_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-03
// PUPROSE: demo


#include "PCF8575.h"

// adjust addresses if needed
PCF8575 PCF_38(0x38);  // add switches to lines  (used as input)
PCF8575 PCF_39(0x39);  // add leds to lines      (used as output)


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

  PCF_38.begin();
  PCF_39.begin();

  uint16_t value = PCF_38.read16();
  Serial.print("#38:\t");
  Serial.println(value);

  for (int i = 0; i < 255; i++)
  {
    PCF_39.write16(i);
    delay(100);
  }

  PCF_39.write(0, 1);
  for (int i = 0; i < 15; i++)
  {
    PCF_39.shiftLeft();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    PCF_39.shiftRight();
    delay(100);
  }

  for (int i = 0; i < 16; i++)
  {
    PCF_39.write(i, 1);
    delay(100);
    PCF_39.write(i, 0);
    delay(100);
  }

  for (int i = 0; i < 16; i++)
  {
    PCF_39.toggle(i);
    delay(100);
    PCF_39.toggle(i);
    delay(100);
  }
}


void loop()
{
  // echos the lines
  uint16_t value = PCF_38.read16();
  PCF_39.write16(value);
  delay(100);
}


// -- END OF FILE --

