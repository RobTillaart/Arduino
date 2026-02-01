//
//    FILE: RunningMinMax_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: array of runningWinMax objects
//     URL: https://github.com/RobTillaart/RunningMinMax


#include "RunningMinMax.h"


//  create an different lengths
RunningMinMax a(5);
RunningMinMax b(10);
RunningMinMax c(15);
RunningMinMax d(20);

RunningMinMax RMM[4] = { a, b, c, d };


void setup()
{
  while (!Serial);  //  Wait for serial port to connect. Needed for Leonardo + MKR1010.
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("RUNNING_MINMAX_LIB_VERSION: "));
  Serial.println(RUNNING_MINMAX_LIB_VERSION);
  Serial.println();
}


void loop()
{
  for (int i = 0; i < 4; i++)
  {
    RMM[i].add(random(100));
  }
  for (int i = 0; i < 4; i++)
  {
//    Serial.print(RMM[i].getCount());
//    Serial.print("\t");
    Serial.print(RMM[i].getMinimum());
    Serial.print("\t");
    Serial.print(RMM[i].getAverage());
    Serial.print("\t");
    Serial.print(RMM[i].getMaximum());
    Serial.print("\t");
  }
  Serial.println();
  delay(10);
}


//  -- END OF FILE --
