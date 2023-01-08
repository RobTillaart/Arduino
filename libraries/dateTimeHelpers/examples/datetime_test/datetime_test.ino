//
//    FILE: datetime_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo seconds2clock
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/datetimeHelpers


#include "dateTimeHelpers.h"

uint32_t start, stop, duration1;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  uint32_t seconds = 12345678;

  //  print all "clocks"
  Serial.println(seconds2clock24(seconds, false));
  Serial.println(seconds2clock24(seconds, true));
  Serial.println(seconds2clock12(seconds, false));
  Serial.println(seconds2clock12(seconds, true));
  Serial.println(seconds2clockAMPM(seconds, false));
  Serial.println(seconds2clockAMPM(seconds, true));
  Serial.println();

  delay(3000);
}


void loop()
{
  uint32_t seconds = micros();
  //  print only major functions.
  Serial.println(seconds2clock24(seconds, false));
  Serial.println(seconds2clock24(seconds, true));
  Serial.println(seconds2clockAMPM(seconds, false));
  Serial.println(seconds2clockAMPM(seconds, true));
  Serial.println();
  delay(1234);
}


// -- END OF FILE --
