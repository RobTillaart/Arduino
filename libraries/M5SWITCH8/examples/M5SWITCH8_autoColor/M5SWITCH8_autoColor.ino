//
//    FILE: M5SWITCH8_autoColor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/M5SWITCH8


#include "M5SWITCH8.h"


M5SWITCH8 mySwitch(71);
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

  //  set the system define "auto" colors
  //  note one still need to read the buttons!
  for (int i = 0; i < 8; i++)
  {
    //  BGR
    mySwitch.setOnColor(i, 0x0000FF);
    mySwitch.setOffColor(i, 0x00FF00);
  }
  mySwitch.setMode(1);
}


void loop()
{
  Serial.println(millis());
  delay(1000);
}


//  -- END OF FILE --
