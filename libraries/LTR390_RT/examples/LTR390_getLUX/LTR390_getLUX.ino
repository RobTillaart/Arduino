//
//    FILE: LTR390_getLUX.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/LTR390


#include "LTR390.h"

LTR390 ltr;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LTR390_LIB_VERSION: ");
  Serial.println(LTR390_LIB_VERSION);
  Serial.println();

  Wire.begin();

  delay(1000);

  if (ltr.begin() == false)
  {
    Serial.println("Could not connect, fix and reboot");
  }
  else
  {
    Serial.println("Device found.");
  }

  ltr.setALSMode();
  ltr.enable();
}


void loop()
{
  delay(1000);
  Serial.print(ltr.getALSData());
  Serial.print("\t");
  Serial.println(ltr.getLUX());
}


//  -- END OF FILE --
