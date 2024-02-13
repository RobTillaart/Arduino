//
//      FILE: TLC5947_NightRider.ino
//    AUTHOR: Rob Tillaart
//   PURPOSE: demo
//       URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"

int DEVICES = 1;
const int CLOCK = 13;
const int DATA  = 12;
const int LATCH = 11;
const int BLANK = 10;

TLC5947 tlc(DEVICES, CLOCK, DATA, LATCH, BLANK);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5947_LIB_VERSION: \t");
  Serial.println(TLC5947_LIB_VERSION);

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
    tlc.setPWM(i, 0);
  }
  tlc.write();

  //  5 pixel wave
  if (pos > 1) tlc.setPWM(pos - 2, 400);
  if (pos > 0) tlc.setPWM(pos - 1, 1200);
  tlc.setPWM(pos, 4095);
  Serial.println(pos);  
  if (pos < 22) tlc.setPWM(pos + 1, 1200);
  if (pos < 23) tlc.setPWM(pos + 2, 400);
  tlc.write();

  pos += delta;
  if ((pos == 0) || (pos == 23)) delta = -delta;

  delay(100);
}


//  -- END OF FILE --
