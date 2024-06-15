//
//    FILE: TLC5917_demo_gain.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo writeConfiguration() to set gain.
//     URL: https://github.com/RobTillaart/TLC5917


#include "TLC5917.h"


const int DEVICES = 1;
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
  Serial.println();

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while (1);
  }

  Serial.print("Channels: ");
  Serial.println(tlc.channelCount());

  //  set all leds ON
  tlc.enable();
  for (int ch = 0; ch < tlc.channelCount(); ch++)
  {
    tlc.setChannel(ch, true);
  }
  tlc.write();

  Serial.print("MODE:\t");
  Serial.println(tlc.getMode());
  tlc.setSpecialMode();
  Serial.print("MODE:\t");
  Serial.println(tlc.getMode());
  uint32_t start = millis();
  for (int conf = 0; conf < 256; conf++)
  {
    tlc.writeConfiguration(conf);
    delay(100);
  }
  uint32_t stop = millis();
  tlc.setNormalMode();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("MODE:\t");
  Serial.println(tlc.getMode());

  Serial.println("\ndone...");

  tlc.setSpecialMode();
}


void loop()
{
  //  increase gain
  for (int conf = 0; conf < 256; conf++)
  {
    tlc.writeConfiguration(conf);
    delay(10);
  }
  // decrease gain
  for (int conf = 255; conf > 0; conf--)
  {
    tlc.writeConfiguration(conf);
    delay(10);
  }

}


//  -- END OF FILE --
