//
//    FILE: TLC5917_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo basic usage
//     URL: https://github.com/RobTillaart/TLC5917


#include "TLC5917.h"


const int DEVICES = 1;
const int CLOCK   = 13;
const int DATA    = 12;
const int LATCH   = 11;
const int ENABLE  = 10;

TLC5917 tlc(DEVICES, CLOCK, DATA, LATCH, ENABLE);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5917_LIB_VERSION: \t");
  Serial.println(TLC5917_LIB_VERSION);
  Serial.println();

  Serial.println(sizeof(tlc));

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while (1);
  }

  Serial.print("Channels: ");
  Serial.println(tlc.channelCount());

  tlc.enable();
}


void loop()
{
  Serial.println("ON");
  for (int ch = 0; ch < tlc.channelCount(); ch++)
  {
    Serial.println(ch);
    tlc.setChannel(ch, true);
    tlc.write();
    delay(100);
  }

  Serial.println("OFF");

  for (int ch = 0; ch < tlc.channelCount(); ch++)
  {
    Serial.println(ch);
    tlc.setChannel(ch, false);
    tlc.write();
    delay(100);
  }
}


//  -- END OF FILE --
