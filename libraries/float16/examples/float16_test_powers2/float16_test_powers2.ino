//
//    FILE: float16_test_powers2.ino
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

  for (uint32_t n = 1; n < 65536; n *= 2)
  {
    float16 f16(n);
    Serial.print(n);
    Serial.print('\t');
    Serial.print(f16.toString());
    Serial.print('\t');
    Serial.print(abs(f16.toDouble() / n), 8);
    Serial.println();
  }
  Serial.println();
  Serial.println();

  for (uint32_t n = 1; n < 32768; n *= 2)
  {
    float16 f16(1.0 / n);
    Serial.print(n);
    Serial.print('\t');
    Serial.print(1.0 / n, 8);
    Serial.print('\t');
    Serial.print(f16.toDouble(), 8);
    Serial.print('\t');
    Serial.print(abs(f16.toDouble() * n), 8);
    Serial.println();
  }

  Serial.println("\ndone");
}


void loop()
{
}


// -- END OF FILE --
