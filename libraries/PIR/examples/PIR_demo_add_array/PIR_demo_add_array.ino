//
//    FILE: PIR_demo_add_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo pir sensor class
//     URL: https://github.com/RobTillaart/PIR


#include "PIR.h"


PIR  P;

uint8_t pins[4] = {3, 4, 5, 6};

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PIR_LIB_VERSION: ");
  Serial.println(PIR_LIB_VERSION);
  Serial.println();

  P.add(pins, 4);
}


void loop()
{
  uint8_t x = P.read();
  Serial.println(x, HEX);
  delay(1000);
}


//  -- END OF FILE --
