//
//    FILE: seconds_toClock.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo simple clock
//     URL: https://github.com/RobTillaart/timing


#include "timing.h"

uint32_t last = 0;

seconds sec;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  sec.set(3545);
}


void loop()
{
  if (last != sec.now())
  {
    last = sec.now();
    Serial.println(sec.toClock());
  }
}


//  -- END OF FILE --
