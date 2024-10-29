//
//    FILE: ACD3100_preheat_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD3100


#include "ACD3100.h"


ACD3100 mySensor;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD3100_LIB_VERSION: ");
  Serial.println(ACD3100_LIB_VERSION);

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
