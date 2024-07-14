//
//    FILE: TLC5917_demo_gain.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo writeConfiguration() to set gain.
//     URL: https://github.com/RobTillaart/TLC5917
//
//  needs investigation.

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

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while (1);
  }

  Serial.print("Channels: ");
  Serial.println(tlc.channelCount());

  //  set gain level
  tlc.setSpecialMode();
  tlc.writeConfiguration(255);
    
  //  set all leds ON
  tlc.setNormalMode();
  tlc.enable();

  for (int ch = 0; ch < tlc.channelCount(); ch++)
  {
    tlc.setChannel(ch, true);
  }
  tlc.write();
  delay(1000);

  Serial.print("MODE:\t");
  Serial.println(tlc.getMode());
  tlc.setSpecialMode();
  Serial.print("MODE:\t");
  Serial.println(tlc.getMode());

  uint32_t start = millis();
  for (int conf = 0; conf < 256; conf++)
  {
    tlc.writeConfiguration(conf);
  }
  uint32_t stop = millis();

  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("MODE:\t");
  Serial.println(tlc.getMode());

  Serial.println("25%");
  tlc.writeConfiguration(0);  //  very low.
  tlc.setNormalMode();
  tlc.enable();
  delay(3000);

  tlc.setSpecialMode();
  tlc.writeConfiguration(255);  //  MAX!
  tlc.setNormalMode();
  tlc.enable();
  delay(3000);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
