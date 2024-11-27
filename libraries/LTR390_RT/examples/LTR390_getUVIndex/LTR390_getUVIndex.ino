//
//    FILE: LTR390_getUVIndex.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/LTR390


#include "LTR390.h"


LTR390 uv;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LTR390_LIB_VERSION: ");
  Serial.println(LTR390_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (uv.begin() == false)
  {
    Serial.println("Could not connect, fix and reboot");
  }
  else
  {
    Serial.println("Device found.");
  }

  uv.setUVSMode();
  uv.enable();
}


void loop()
{
  delay(1000);
  Serial.print(uv.getUVSData());
  Serial.print("\t");
  Serial.println(uv.getUVIndex());
}


//  -- END OF FILE --
