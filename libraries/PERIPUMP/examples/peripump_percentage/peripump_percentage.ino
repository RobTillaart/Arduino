//
//    FILE: peripump_slow_start_stop.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PERIPUMP.git
//


#include "PERIPUMP.h"

PERIPUMP pump(5);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PERIPUMP_LIB_VERSION: ");
  Serial.println(PERIPUMP_LIB_VERSION);

  pump.begin();
  pump.stop();

  pump.setPercentage(100);
  delay(2000);
  pump.stop();
  delay(1000);
  pump.setPercentage(-100);
  delay(2000);
  pump.stop();
  delay(1000);

  for (int p = 0; p < 10; p++)
  {
    pump.setPercentage(p);
    Serial.println(pump.getPercentage());
    delay(2000);
  }

  for (int p = 10; p <= 100; p += 10)
  {
    pump.setPercentage(p);
    Serial.println(pump.getPercentage());
    delay(2000);
  }

  pump.stop();
  delay(1000);

  for (int p = 0; p < 10; p++)
  {
    pump.setPercentage(-p);  //  reverse!!
    Serial.println(pump.getPercentage());
    delay(2000);
  }

  for (int p = 10; p <= 100; p += 10)
  {
    pump.setPercentage(-p);
    Serial.println(pump.getPercentage());
    delay(2000);
  }

  pump.stop();
  delay(1000);

}

void loop()
{
}

//  -- END OF FILE --
