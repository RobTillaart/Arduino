//
//    FILE: rain_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo read + percentage
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

  //  measured in an earlier run, adjust to your calibration.
  RS.setDryReference(3.5);
}


void loop()
{
  Serial.print(RS.read(), 3);
  Serial.print('\t');
  Serial.print(RS.percentage(), 1);
  Serial.print('\n');
  delay(1000);
}


//  -- END OF FILE --

