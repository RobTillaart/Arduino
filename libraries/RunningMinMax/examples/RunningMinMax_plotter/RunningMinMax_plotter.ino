//
//    FILE: RunningMinMax_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: array of runningWinMax objects
//     URL: https://github.com/RobTillaart/RunningMinMax


#include "RunningMinMax.h"

RunningMinMax RMM(20);


void setup()
{
  while (!Serial);  //  Wait for serial port to connect. Needed for Leonardo + MKR1010.
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("RUNNING_MINMAX_LIB_VERSION: "));
  Serial.println(RUNNING_MINMAX_LIB_VERSION);
  Serial.println();

  Serial.println("MIN\tAVG\tMAX");
}


void loop()
{
  RMM.add(random(100));

  Serial.print(RMM.getMinimum());
  Serial.print("\t");
  Serial.print(RMM.getAverage());
  Serial.print("\t");
  Serial.print(RMM.getMaximum());
  Serial.println();
  delay(10);
}


//  -- END OF FILE --
