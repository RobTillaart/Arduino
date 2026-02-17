//
//    FILE: PIR_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PIR sensor class
//     URL: https://github.com/RobTillaart/PIR


#include "PIR.h"


PIR  P;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PIR_LIB_VERSION: ");
  Serial.println(PIR_LIB_VERSION);
  Serial.println();

  P.add(3);
  P.add(4);
  P.add(5);
}


void loop()
{
  uint8_t x = P.read();
  Serial.println(x, HEX);
  delay(1000);
}


//  -- END OF FILE --

