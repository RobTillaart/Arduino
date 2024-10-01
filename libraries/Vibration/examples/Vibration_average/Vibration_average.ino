//
//    FILE: Vibration_average.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Vibration


#include "Vibration.h"

VibrationSensor VBS(A0);

void setup()
{
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("VIBRATION_LIB_VERSION: ");
  Serial.println(VIBRATION_LIB_VERSION);

  Serial.println("done...\n");
}


void loop()
{
  Serial.println(VBS.average(1000));
}


//  -- END OF FILE --
