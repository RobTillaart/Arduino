//
//    FILE: datetime_millis2duration.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo millis2duration
//     URL: https://github.com/RobTillaart/dateTimeHelpers


#include "dateTimeHelpers.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DATETIMEHELPER_LIB_VERSION: ");
  Serial.println(DATETIMEHELPER_LIB_VERSION);
  Serial.println();
}


void loop()
{
  uint32_t mil = micros();  //  simulation fast clock

  Serial.println(millis2duration(mil));
  delay(1234);
}


//  -- END OF FILE --
