//
//    FILE: AD524X_midScaleReset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD524X demo program
//     URL: https://github.com/RobTillaart/AD524X


#include "AD524X.h"

AD524X AD01(0x2C);  //  AD0 & AD1 == GND


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD524X_LIB_VERSION: ");
  Serial.println(AD524X_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  bool b = AD01.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD01.isConnected());
}


void loop()
{
  Serial.println(255);
  AD01.write(1, 255);
  delay(1000);

  Serial.println("midScaleReset(1)");
  AD01.midScaleReset(1);
  delay(1000);

  Serial.println(0);
  AD01.write(1, 0);
  delay(1000);

  Serial.println("midScaleReset(1)");
  AD01.midScaleReset(1);
  delay(1000);
}


//  -- END OF FILE --

