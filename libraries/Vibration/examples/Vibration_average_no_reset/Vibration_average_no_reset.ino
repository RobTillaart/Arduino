//
//    FILE: Vibration_average_no_reset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Vibration
//
//  value of sampleCount will grow till 2^32
//  before it wraps to zero.

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
  //  measure
  VBS.measure(100000, false);
  //  average with one decimal
  Serial.print("Samples: \t");
  Serial.print(VBS.sampleCount());  //   will grow up to 2^32
  Serial.print("\t avg: \t");
  Serial.print(VBS.average());
  Serial.println();
}


//  -- END OF FILE --
