//
//    FILE: PT2323_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/PT2323


#include "PT2323.h"

PT2323 pt;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PT2323_LIB_VERSION: ");
  Serial.println(PT2323_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();

  pt.begin();
  Serial.println(pt.getAddress());
  Serial.println(pt.getChannel());
  Serial.println(pt.getSurround());
  Serial.println(pt.getMixedChannel());

  Serial.println("\ntest all channels + some not allowed");
  for (int i = 0; i < 7; i++)
  {
    Serial.print("Chan: ");
    Serial.print(i);
    Serial.print("\t");
    Serial.println(pt.setChannel(i));
  }

  Serial.println("\ntest surround");
  pt.setSurround(true);
  Serial.println(pt.getSurround());
  pt.setSurround(false);
  Serial.println(pt.getSurround());

  Serial.println("\ntest mixedChannel");
  pt.setMixedChannel(true);
  Serial.println(pt.getMixedChannel());
  pt.setMixedChannel(false);
  Serial.println(pt.getMixedChannel());

  Serial.println("\ntest MUTE (takes several seconds)");
  Serial.println(pt.muteFrontLeft(false));
  delay(1000);
  Serial.println(pt.muteFrontRight(false));
  delay(1000);
  Serial.println(pt.muteCenter(false));
  delay(1000);
  Serial.println(pt.muteSubWoofer(false));
  delay(1000);
  Serial.println(pt.muteRearLeft(false));
  delay(1000);
  Serial.println(pt.muteRearRight(false));
  delay(1000);
  Serial.println(pt.muteAll(true));
  delay(1000);

  Serial.println(pt.muteAll(false));
  delay(1000);
  Serial.println(pt.muteFrontLeft(true));
  delay(1000);
  Serial.println(pt.muteFrontRight(true));
  delay(1000);
  Serial.println(pt.muteCenter(true));
  delay(1000);
  Serial.println(pt.muteSubWoofer(true));
  delay(1000);
  Serial.println(pt.muteRearLeft(true));
  delay(1000);
  Serial.println(pt.muteRearRight(true));
  delay(1000);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
