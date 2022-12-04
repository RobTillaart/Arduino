//
//    FILE: rain_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/RAIN


#include "rain.h"

RAIN  RS(A0);

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("RAIN_LIB_VERSION: ");
  Serial.println(RAIN_LIB_VERSION);
  Serial.println("EXPERIMENTAL:");

  RS.begin(5.000, 1023);

  //  set the levels
  //  no need to be equi-distant
  RS.setLevel(1, 0.25);
  RS.setLevel(2, 2.75);
  RS.setLevel(3, 3.25);
  RS.setLevel(4, 3.50);
}


void loop()
{
  Serial.print(RS.read(), 3);
  Serial.print('\t');
  Serial.print(RS.getLevel());
  Serial.print('\n');
  delay(10);
}


// -- END OF FILE --
