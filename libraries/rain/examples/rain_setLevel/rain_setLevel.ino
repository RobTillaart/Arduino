//
//    FILE: rain_setLevel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo setLevel + getLevel
//     URL: https://github.com/RobTillaart/RAIN


#include "rain.h"

RAIN  RS(A0);

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RAIN_LIB_VERSION: ");
  Serial.println(RAIN_LIB_VERSION);
  Serial.println();

  RS.begin(5.000, 1023);

  //  set the 4 levels in milliVolts
  //  they do not need to be equidistant
  //  level 0 == 0 volts.
  RS.setLevel(1, 0250);
  RS.setLevel(2, 2750);
  RS.setLevel(3, 3250);
  RS.setLevel(4, 3500);
}


void loop()
{
  Serial.print(RS.read(), 3);
  Serial.print('\t');
  Serial.print(RS.getLevel());
  Serial.print('\n');
  delay(100);
}


//  -- END OF FILE --
