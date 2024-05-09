//
//    FILE: LTR390_UV_demo.ino
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

  Serial.print("PARTID:\t");
  Serial.println(uv.getPartID());
  Serial.print("REVID:\t");
  Serial.println(uv.getRevisionID());

  uv.setUVSMode();
  uv.enable();

  Serial.println("\ndone...");
}


void loop()
{
  delay(1000);
  Serial.println(uv.getUVSData());
}


//  -- END OF FILE --
