//
//    FILE: TLC5947_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"


TLC5947 tlc(13, 12, 11, 10);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5947_LIB_VERSION: \t");
  Serial.println(TLC5947_LIB_VERSION);

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while(1);
  }

  for (int ch = 0; ch < 24; ch++)
  {
    tlc.setPWM(ch, random(4096));
  }
  tlc.write();

  delay(1000);
  tlc.disable();
  delay(1000);
  tlc.enable();

}


void loop()
{

}


//  -- END OF FILE --

