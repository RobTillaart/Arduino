//
//    FILE: M5SWITCH8_demo.ino
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
  if (mySwitch.begin() == false)
  {
    Serial.println("Could not find device");
  }
}


void loop()
{
  uint8_t x = 0;
  for (int i = 0; i < 8; i++)
  {
    x = mySwitch.readSwitch(i);
    Serial.print(x);
  }
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
