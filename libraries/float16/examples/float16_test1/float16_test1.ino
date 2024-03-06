//
//    FILE: float16_test1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16
//     URL: https://github.com/RobTillaart/float16


#include "float16.h"

float16 X;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FLOAT16_LIB_VERSION: ");
  Serial.println(FLOAT16_LIB_VERSION);

  float f;

  // dump all possible values
  for (uint16_t n = 0; n < 65535; n++)  
  {
    f = X.f16tof32(n);
    Serial.print(n);
    Serial.print('\t');
    Serial.println(f, 6);
  }

  Serial.println("\ndone");
}


void loop()
{
}


//  -- END OF FILE --


