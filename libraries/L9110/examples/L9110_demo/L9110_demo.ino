//
//    FILE: L9110_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/H9110


#include "L9110.h"


L9110 driver(6, 7);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("L9110_LIB_VERSION: ");
  Serial.println(L9110_LIB_VERSION);
  Serial.println();

  driver.begin();
}


void loop()
{
  driver.forward();
  delay(1000);
  driver.stop();
  delay(1000);
  driver.reverse();
  delay(1000);
  driver.stop();
  delay(1000);
}


//  -- END OF FILE --
