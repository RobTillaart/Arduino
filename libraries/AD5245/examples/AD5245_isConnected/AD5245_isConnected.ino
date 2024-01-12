//
//    FILE: AD5245_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD5245 demo program
//     URL: https://github.com/RobTillaart/AD5245


#include "AD5245.h"


AD5245 AD(0x2C);     //  AD0 == GND


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5245_LIB_VERSION: ");
  Serial.println(AD5245_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  bool b = AD.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD.isConnected());

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
