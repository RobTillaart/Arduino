//
//    FILE: LC7822_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour

//     URL: https://github.com/RobTillaart/LC7822


#include "LC7822.h"

//  LC7822(dataPin, clockPin, cePin, sPin, resetPin);
LC7822 LC(4,5,6,7);  //  no reset Pin.


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LC7822_LIB_VERSION: ");
  Serial.println(LC7822_LIB_VERSION);
  Serial.println();

  if (LC.begin() == false)
  {
    Serial.println("error begin()");
  }
  //  tune timing.
  LC.setMicroDelay(10);
}


void loop()
{
  //  set on, one by one
  for (int sw = 0; sw < 8; sw ++)
  {
    LC.setSwitch(sw, 1);
    delay(500);
  }

  // set off, one by one
  for (int sw = 0; sw < 8; sw ++)
  {
    LC.setSwitch(sw, 0);
    delay(500);
  }
  delay(2000);
}


//  -- END OF FILE --
