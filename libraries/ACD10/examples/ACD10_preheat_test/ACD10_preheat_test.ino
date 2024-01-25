//
//    FILE: ACD10_preheat_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD10


#include "ACD10.h"


ACD10 mySensor;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD10_LIB_VERSION: ");
  Serial.println(ACD10_LIB_VERSION);

  Wire.begin();
  mySensor.begin();
}


void loop()
{
  Serial.print(millis() / 1000);
  if (mySensor.preHeatDone())
  {
    Serial.println("\tOK");
  }
  else
  {
    Serial.print("\tWarming up\t");
    Serial.println(mySensor.preHeatMillisLeft());
  }
  delay(5000);
}


//  -- END OF FILE --
