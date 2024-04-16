//
//    FILE: pcf8575_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PCF8575


#include "PCF8575.h"

//  adjust addresses if needed
PCF8575 PCF_20(0x20);  //  add switches to lines  (used as input)
PCF8575 PCF_21(0x21);  //  add LEDs to lines      (used as output)


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

  Wire.begin();

  PCF_20.begin();
  PCF_21.begin();

  uint16_t value = PCF_20.read16();
  Serial.print("#38:\t");
  Serial.println(value);

  for (int i = 0; i < 255; i++)
  {
    PCF_21.write16(i);
    delay(100);
  }

  PCF_21.write(0, 1);
  for (int i = 0; i < 15; i++)
  {
    PCF_21.shiftLeft();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    PCF_21.shiftRight();
    delay(100);
  }

  for (int i = 0; i < 16; i++)
  {
    PCF_21.write(i, 1);
    delay(100);
    PCF_21.write(i, 0);
    delay(100);
  }

  for (int i = 0; i < 16; i++)
  {
    PCF_21.toggle(i);
    delay(100);
    PCF_21.toggle(i);
    delay(100);
  }
}


void loop()
{
  //  echoes the lines
  uint16_t value = PCF_20.read16();
  PCF_21.write16(value);
  delay(100);
}


//  -- END OF FILE --

