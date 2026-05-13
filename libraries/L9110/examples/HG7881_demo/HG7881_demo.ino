//
//    FILE: HG7881_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/H9110


#include "L9110.h"


HG7881 driver(6, 7);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("L9110_LIB_VERSION: ");
  Serial.println(L9110_LIB_VERSION);
  Serial.println();

  driver.begin();
  //  improve reaction speed
  driver.setMicroDelay(10);
}


void loop()
{
  driver.forward();
  delay(500);
  driver.stop();
  delay(500);
  driver.reverse();
  delay(500);
  driver.stop();
  delay(500);
}


//  -- END OF FILE --
