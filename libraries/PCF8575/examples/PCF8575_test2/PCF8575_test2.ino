//
//    FILE: pcf8575_test2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo rotateLeft, -Right and toggleMask
//     URL: https://github.com/RobTillaart/PCF8575


#include "PCF8575.h"

//  adjust addresses if needed
PCF8575 PCF(0x21);  //  add LEDs to lines      (used as output)


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

  Wire.begin();

  PCF.begin();

  PCF.write(0, 1);
  for (int i = 0; i < 15; i++)
  {
    PCF.rotateLeft();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    PCF.rotateRight();
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    PCF.rotateLeft(3);
    delay(100);
  }

  for (int i = 0; i < 15; i++)
  {
    PCF.rotateRight(2);
    delay(100);
  }

  for (uint16_t i = 0; i < 65535; i += 253)
  {
    PCF.toggleMask(i);
    delay(100);
  }

  //  0010 0111  -> 0x27
  //  1110 0100
  PCF.write16(0x2755);
  for (int i = 0; i < 255; i++)
  {
    PCF.reverse();
    delay(100);
  }
}


void loop()
{
}


//  -- END OF FILE --

