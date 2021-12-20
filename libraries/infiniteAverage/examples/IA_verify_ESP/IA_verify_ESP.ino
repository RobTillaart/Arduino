//
//    FILE: IA_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-01-21
//    (c) : MIT


#include "infiniteAverage.h"

IAVG IA;

uint32_t lastTime = 0;

double sum = 0;
uint64_t cnt = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  IA.reset();

  while (1)
  {
    float r = random(10000) * 0.0001;
    IA.add(r);
    sum += r;
    cnt++;

    if (millis() - lastTime >= 1000)
    {
      lastTime = millis();
      Serial.print(millis() / 1000);
      Serial.print("\t");
      Serial.print(IA.count());
      Serial.print("\t");
      Serial.print(IA.whole());
      Serial.print("\t");
      Serial.print(IA.decimals(), 10);
      Serial.print("\t\t");
      Serial.print(IA.average(), 10);
      Serial.print("\t");
      Serial.print(sum / cnt, 10);
      Serial.print("\t");
      Serial.print(abs(IA.average() - sum / cnt), 10);
      Serial.print("\n");
    }
  }
}


void loop()
{
}


// -- END OF FILE --

