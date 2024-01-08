//
//    FILE: PCF8574_test.ino
//  AUTHOR: Rob Tillaart
//    DATE: 27-08-2013
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PCF8574


#include "PCF8574.h"

//  adjust addresses if needed
PCF8574 PCF_38(0x38);  //  add switches to lines  (used as input)
PCF8574 PCF_39(0x39);  //  add LEDs to lines      (used as output)


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION:\t");
  Serial.println(PCF8574_LIB_VERSION);

  Wire.begin();

  PCF_38.begin();
  PCF_39.begin();

  uint8_t value = PCF_38.read8();
  Serial.print("#38:\t");
  Serial.println(value);

  for (int i = 0; i < 255; i++)
  {
    PCF_39.write8(i);
    delay(100);
  }

  PCF_39.write(0, 1);
  for (int i = 0; i < 7; i++)
  {
    PCF_39.shiftLeft();
    delay(100);
  }

  for (int i = 0; i < 7; i++)
  {
    PCF_39.shiftRight();
    delay(100);
  }

  for (int i = 0; i < 8; i++)
  {
    PCF_39.write(i, 1);
    delay(100);
    PCF_39.write(i, 0);
    delay(100);
  }

  for (int i = 0; i < 8; i++)
  {
    PCF_39.toggle(i);
    delay(100);
    PCF_39.toggle(i);
    delay(100);
  }
}


void loop()
{
  //  echo the state of the lines on the other PCF
  uint8_t value = PCF_38.read8();
  PCF_39.write8(value);
  delay(100);
}


//  -- END OF FILE --

