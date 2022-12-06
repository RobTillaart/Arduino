//
//    FILE: rain_delta.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo read + delta
//     URL: https://github.com/RobTillaart/RAIN
//
//  e.g. use with Arduino IDE plotter tool.


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
  Serial.println("READ\tDELTA");
}


void loop()
{
  Serial.print(RS.read(), 3);
  Serial.print('\t');
  Serial.print(RS.delta(), 1);
  Serial.print('\n');
  delay(100);
}


// -- END OF FILE --
