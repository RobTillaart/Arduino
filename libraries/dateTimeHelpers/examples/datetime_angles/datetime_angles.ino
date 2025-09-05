//
//    FILE: datetime_angles.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/datetimeHelpers


#include "dateTimeHelpers.h"

uint32_t start, stop, duration1;

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
  uint32_t s = millis() / 1000;
  uint16_t days;
  uint8_t  hours;
  uint8_t  minutes;
  uint8_t  seconds;

  secondsSplit( s, &days, &hours, &minutes, &seconds);


  //  print only major functions.
  Serial.print(hourAngle(hours, minutes, seconds), 1);
  Serial.print("\t");
  Serial.print(minuteAngle(minutes, seconds), 1);
  Serial.print("\t");
  Serial.println(secondAngle(seconds), 1);
  delay(1234);
}


//  -- END OF FILE --
