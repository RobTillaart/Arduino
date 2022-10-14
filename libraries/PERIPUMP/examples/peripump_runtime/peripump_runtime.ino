//
//    FILE: peripump_runtime.ino
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

  Serial.println(pump.getRunTime());
  delay(5000);

  Serial.println(pump.getRunTime());
  delay(1000);

  pump.setPercentage(50);
  delay(2000);
  Serial.println(pump.getRunTime());

  pump.setPercentage(75);
  delay(2000);
  Serial.println(pump.getRunTime());

  pump.stop();
  delay(2000);
  Serial.println(pump.getRunTime());

  pump.resetRunTime();
  pump.setPercentage(50);
  delay(2000);
  Serial.println(pump.getRunTime());

  pump.stop();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
