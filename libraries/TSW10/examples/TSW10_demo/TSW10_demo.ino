//
//    FILE: TSW10_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TSW10


#include "TSW10.h"

TSW10 turbidity(A0);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TSW10_LIB_VERSION: ");
  Serial.println(TSW10_LIB_VERSION);
  Serial.println();

  turbidity.begin(5.0, 1023);
}


void loop()
{
  Serial.print(turbidity.getVoltage());
  Serial.print("\t");
  Serial.print(turbidity.getNTU());
  Serial.println();
  delay(2000);
}


//  -- END OF FILE --
