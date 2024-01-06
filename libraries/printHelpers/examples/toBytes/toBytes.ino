//
//    FILE: toBytes.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo toBytes(double val);
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"

volatile uint32_t n = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_VERSION: ");
  Serial.println(PRINTHELPERS_VERSION);
  Serial.println();

  delay(100);

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


//  -- END OF FILE --
