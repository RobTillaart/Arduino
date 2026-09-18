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

  rt.start();
}


void loop()
{
  delay(2333);
  Serial.print(rt.hours(), 4);
  Serial.print("\t");
  Serial.println(rt);  //  seconds.
}


//  -- END OF FILE --
