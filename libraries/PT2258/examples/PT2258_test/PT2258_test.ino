//
//    FILE: PT2258_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal demo
//     URL: https://github.com/RobTillaart/PT2258


#include "PT2258.h"

PT2258 pt(0x48);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PT2258_LIB_VERSION: ");
  Serial.println(PT2258_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();

  pt.begin();
  Serial.println(pt.getAddress());
  Serial.println(pt.isConnected());

  Serial.println("\nI\tVolume\tAttenuation");
  for (int i = 0; i < 6; i++)
  {
    pt.setVolume(i, random(79));
    Serial.print(i);
    Serial.print("\t");
    Serial.print(pt.getVolume(i));
    Serial.print("\t");
    Serial.println(pt.getAttenuation(i));
    delay(1000);
  }

  pt.mute(true);
  delay(1000);
  pt.mute(false);
  delay(1000);
  pt.mute(true);
  delay(1000);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
