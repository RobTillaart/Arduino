//
//    FILE: IA_test_mini_steps.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/infiniteAverage


#include "infiniteAverage.h"

IAVG IA;

uint32_t lastTime = 0;


void setup()
{
  //  while (!Serial);  // uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("IAVG_LIB_VERSION: ");
  Serial.println(IAVG_LIB_VERSION);
  Serial.println();

  IA.reset();
  IA.setDivideThreshold(1024);

  while (1)
  {
    IA.add(0.0001);
    lastTime = millis();
    Serial.print(IA.count());
    Serial.print("\t");
    Serial.print(IA.whole());
    Serial.print("\t");
    Serial.print(IA.decimals(), 6);
    Serial.print("\t\t");
    Serial.print(IA.average(), 7);
    Serial.print("\n");
  }
}


void loop()
{
}


//  -- END OF FILE --
