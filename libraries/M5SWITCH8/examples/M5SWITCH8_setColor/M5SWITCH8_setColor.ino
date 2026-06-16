//
//    FILE: M5SWITCH8_setColor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/M5SWITCH8


#include "M5SWITCH8.h"


M5SWITCH8 mySwitch(70);
//  M5SWITCH8 myButton(71);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("M5SWITCH8_LIB_VERSION: ");
  Serial.println(M5SWITCH8_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setTimeout(3000);

  if (mySwitch.begin() == false)
  {
    Serial.println("Could not find device");
  }

  for (int i = 0; i < 9; i++)
  {
    mySwitch.setBrightness(i, 127);
  }
  mySwitch.setBrightness(8, 50);
  //  BGR
  mySwitch.setColor(8, 0xFF0000);
}


void loop()
{
  uint8_t x = 0;
  for (int i = 0; i < 8; i++)
  {
    x = mySwitch.readSwitch(i);
    //  BGR
    mySwitch.setColor(i, x * 0x0000FF);
  }
  delay(100);
}


//  -- END OF FILE --
