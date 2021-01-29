//
//    FILE: toBytes.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo toBytes(double val);
//    DATE: 2020-07-03

#include "printHelpers.h"

volatile uint32_t n = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  delay(10);

  Serial.println("20 random() values");
  for (uint8_t i = 0; i < 20; i++)
  {
    n = random(PI * pow(10, i));
    Serial.print(i);
    Serial.print('\t');
    Serial.print(sci(n, 3));
    Serial.print('\t');
    Serial.print(toBytes(n));
    Serial.print('\t');
    Serial.println();
  }
  Serial.println();

  Serial.println("20 BIG values");
  double n = PI * 12345;
  for (uint8_t i = 0; i < 20; i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.print(sci(n, 3));
    Serial.print('\t');
    Serial.print(toBytes(n));
    Serial.print('\t');
    Serial.println();
    n = n * (PI * PI * PI * PI);
  }

  Serial.println("\ndone...");
}

void loop()
{
}

// -- END OF FILE --
