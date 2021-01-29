//
//    FILE: IA_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-01-21
//    (c) : MIT
//


#include "infiniteAverage.h"

IAVG IA;

uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  IA.reset();

  while (1)
  {
    IA.add(random(10000) * 0.0001);

    if (millis() - lastTime >= 1000)
    {
      lastTime = millis();
      Serial.print(IA.count());
      Serial.print("\t");
      Serial.print(IA.whole());
      Serial.print("\t");
      Serial.print(IA.decimals(), 5);
      Serial.print("\t\t");
      Serial.print(IA.average(), 7);
      Serial.print("\n");
    }
  }
}

void loop()
{

}

// -- END OF FILE --
