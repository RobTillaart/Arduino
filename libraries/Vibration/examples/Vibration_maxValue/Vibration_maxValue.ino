//
//    FILE: Vibration_maxValue.ino
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
  Serial.println();
}


void loop()
{
  //  measure for one second
  VBS.measure(1000000);
  //  max value
  Serial.print("Samples: \t");
  Serial.print(VBS.sampleCount());
  Serial.print("\t max: \t");
  Serial.print(VBS.maxValue());
  Serial.println();
}


//  -- END OF FILE --
