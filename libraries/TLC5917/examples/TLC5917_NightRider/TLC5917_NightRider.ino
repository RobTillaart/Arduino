//
//      FILE: TLC5917_NightRider.ino
//    AUTHOR: Rob Tillaart
//   PURPOSE: demo
//       URL: https://github.com/RobTillaart/TLC5917


#include "TLC5917.h"

int DEVICES = 1;
const int CLOCK = 13;
const int DATA  = 12;
const int LATCH = 11;
const int BLANK = 10;

TLC5917 tlc(DEVICES, CLOCK, DATA, LATCH, BLANK);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5917_LIB_VERSION: \t");
  Serial.println(TLC5917_LIB_VERSION);

  tlc.begin();
  tlc.enable();
}


void loop()
{
  static int pos = 0;
  static int delta = 1;

  //  clear;
  for (int i = 0; i < tlc.getChannels(); i++)
  {
    tlc.setChannel(i, false);
  }
  tlc.write();

  Serial.println(pos);
  tlc.setChannel(pos, true);
  tlc.write();
  delay(100);
  tlc.setChannel(pos, false);
  tlc.write();

  pos += delta;
  if ((pos == 0) || (pos == tlc.getChannels())) 
  {
    delta = -delta;
  }
}


//  -- END OF FILE --
