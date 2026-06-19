//
//    FILE: M5BUTTON8_readButton.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/M5SWITCH8


#include "M5SWITCH8.h"

M5BUTTON8 myButton(71);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("M5SWITCH8_LIB_VERSION: ");
  Serial.println(M5SWITCH8_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (myButton.begin() == false)
  {
    Serial.println("Could not find device");
  }

  //  power LED
  myButton.setColorRGB(8, 0, 0, 255);
  //  233 interface
  for (int i = 0; i < 8; i++)
  {
    myButton.setColor233(i, i * 31);
  }
}


void loop()
{
  uint8_t x = 0;
  for (int i = 0; i < 8; i++)
  {
    x = myButton.readButton(i);
    Serial.print(x);
  }
  Serial.print("   ");
  Serial.print(myButton.readAll(), HEX);  //
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
