//
//    FILE: datetime_clockAMPM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo seconds2clockAMPM
//     URL: https://github.com/RobTillaart/dateTimeHelpers


#include "dateTimeHelpers.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  for (uint32_t s = 0; s <= 24 * 3600UL;  s += 1800)
  {
    Serial.println(seconds2clockAMPM(s, true));
  }

}


void loop()
{
}


// -- END OF FILE --
