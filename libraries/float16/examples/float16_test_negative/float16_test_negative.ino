//
//    FILE: float16_test_negative.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16
//     URL: https://github.com/RobTillaart/float16


#include "float16.h"


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FLOAT16_LIB_VERSION: ");
  Serial.println(FLOAT16_LIB_VERSION);
  Serial.println();


  for( int i = -10; i < 2; i++)
  {
    float16 f16(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.println(f16.toDouble(), 4);
  }

  Serial.println("\ndone");
}


void loop()
{
}


//  -- END OF FILE --
