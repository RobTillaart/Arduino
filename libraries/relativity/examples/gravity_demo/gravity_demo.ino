//
//    FILE: gravity_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test formulas
//     URL: https://github.com/RobTillaart/relativity


#include "relativity.h"

relativity R;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RELATIVITY_LIB_VERSION: ");
  Serial.println(RELATIVITY_LIB_VERSION);
  Serial.println();

  Serial.print("\nSpeed of light (m/s):\t");
  Serial.println(R.getC());

  for (uint8_t p = 0; p < 10; p++)
  {
    Serial.print(p);
    Serial.print(":\t");
    Serial.println(1 - R.gravitationalTime(1, R.getPlanetMass(p), R.getPlanetRadius(p)), 6);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

