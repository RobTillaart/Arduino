//
//    FILE: runTime_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/runTime


#include "runTime.h"


runTime rt;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RUNTIME_LIB_VERSION: ");
  Serial.println(RUNTIME_LIB_VERSION);
  Serial.println();

  for (uint32_t i = 0; i < 10000; i++)
  {
    rt.start();
    delay(1);
    rt.stop();
  }

  Serial.print(rt.runCount());
  Serial.print("\t");
  Serial.print(rt.seconds());
  Serial.print("\t");
  Serial.print(rt.averageSeconds(), 4);
  Serial.print("\t");
  Serial.println();
}


void loop()
{

}


//  -- END OF FILE --
