//
//    FILE: APDS9900_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/APDS9900
//
//  This sketch is meant for debugging


#include "APDS9900.h"
#include "Wire.h"

APDS9900 apds;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("APDS9900_LIB_VERSION: ");
  Serial.println(APDS9900_LIB_VERSION);
  Serial.println();


  Wire.begin();
  apds.wakeUp();
  apds.begin();

  for (int r = 0; r < 26; r++)
  {
    Serial.print(r);
    Serial.print("\t");
    Serial.println(apds.readRegister(r));
    delay(20);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
