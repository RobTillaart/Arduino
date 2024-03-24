//
//    FILE: TLC5917_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/TLC5917


#include "TLC5917.h"

const int DEVICES = 2;
const int CLOCK = 13;
const int DATA  = 12;
const int LE    = 11;
const int OE    = 10;

TLC5917 tlc(DEVICES, CLOCK, DATA, LE, OE);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5917_LIB_VERSION: \t");
  Serial.println(TLC5917_LIB_VERSION);

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while(1);
  }

  Serial.print("Channels: ");
  Serial.println(tlc.getChannels());

  tlc.enable();

  for (int ch = 0; ch < tlc.getChannels(); ch++)
  {
    tlc.setChannel(ch, true);
    tlc.write();
    delay(100);
    tlc.setChannel(ch, false);
  }
  tlc.write();
}


void loop()
{
}


//  -- END OF FILE --
