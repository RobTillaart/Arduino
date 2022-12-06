//
//    FILE: rain_demo_powerpin.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo read power pin
//     URL: https://github.com/RobTillaart/RAIN


#include "rain.h"

#define ANALOGPIN     A0
#define POWERPIN      7

RAIN  RS(ANALOGPIN, POWERPIN);

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("RAIN_LIB_VERSION: ");
  Serial.println(RAIN_LIB_VERSION);
  Serial.println("EXPERIMENTAL:");

  RS.begin(5.000, 1023);
}


void loop()
{
  Serial.print(RS.read(), 3);
  Serial.print('\t');
  Serial.print(RS.percentage(), 1);
  Serial.print('\n');
  delay(100);
}


// -- END OF FILE --
