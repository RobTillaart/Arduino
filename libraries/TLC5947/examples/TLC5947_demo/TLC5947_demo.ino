//
//    FILE: TLC5947_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"

const int CLOCK = 13;
const int DATA  = 12;
const int LATCH = 11;
const int BLANK = 10;

TLC5947 tlc(CLOCK, DATA, LATCH, BLANK);


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
}


void loop()
{
  for (int channel = 0; channel < 24; channel++)
  {
    tlc.setPWM(channel, random(4096));
  }
  tlc.write();

  delay(1000);
  tlc.disable();
  delay(1000);
  tlc.enable();
}


//  -- END OF FILE --

