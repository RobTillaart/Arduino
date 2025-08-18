//
//    FILE: DRV8825_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: minimal performance measurement
//     URL: https://github.com/RobTillaart/DRV8825


#include "DRV8825.h"

DRV8825 stepper;
const int DIRECTION_PIN = 4;
const int STEP_PIN = 5;

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DRV8825_LIB_VERSION: ");
  Serial.println(DRV8825_LIB_VERSION);
  Serial.println();
  delay(100);

  stepper.begin(DIRECTION_PIN, STEP_PIN);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    stepper.step();
  }
  stop = micros();
  Serial.print("TIME 1\t");
  Serial.println(stop - start);
  delay(100);
}


void loop()
{
}


//  -- END OF FILE --
