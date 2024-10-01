//
//    FILE: Vibration_zeroCount.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Vibration


#include "Vibration.h"

VibrationSensor VBS(A0);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("VIBRATION_LIB_VERSION: ");
  Serial.println(VIBRATION_LIB_VERSION);

  Serial.println("done...\n");
}


void loop()
{
  //  measure for one second
  //  percentage with one decimal
  Serial.print("ZERO: \t");
  Serial.println(VBS.zeroCount(1000), 1);
}


//  -- END OF FILE --
