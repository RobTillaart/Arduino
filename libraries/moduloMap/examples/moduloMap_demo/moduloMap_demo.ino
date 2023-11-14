//
//    FILE: moduloMap_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/moduloMap


#include "Arduino.h"
#include "moduloMap.h"

MODMAP  mm;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("MODMAP_LIB_VERSION: ");
  Serial.println(MODMAP_LIB_VERSION);

  mm.begin(PI, 2 * PI);

  for (int i = 0; i < 20; i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.print(mm.map(i), 5);
    Serial.println();
  }
  Serial.println();

  for (int i = 0; i < 20; i++)
  {
    uint32_t r = random(1000000);
    Serial.print(r);
    Serial.print('\t');
    Serial.print(mm.map(r), 5);
    Serial.println();
  }
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

