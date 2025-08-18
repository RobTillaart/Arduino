//
//    FILE: DRV8825_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DRV8825


#include "DRV8825.h"

DRV8825 stepper;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DRV8825_LIB_VERSION: ");
  Serial.println(DRV8825_LIB_VERSION);
  Serial.println();

  stepper.begin(4, 5);  //  set direction pin + step pin.
}


void loop()
{
  //  slow in one direction
  stepper.setDirection(DRV8825_CLOCK_WISE);
  for (int i = 0; i < 100; i++)
  {
    stepper.step();
    delay(100);
  }
  //  fast go back to start position.
  stepper.setDirection(DRV8825_COUNTERCLOCK_WISE);
  for (int i = 0; i < 100; i++)
  {
    stepper.step();
    delay(10);
  }
}


// -- END OF FILE --
