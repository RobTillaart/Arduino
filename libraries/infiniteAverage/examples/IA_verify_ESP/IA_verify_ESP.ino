//
//    FILE: IA_verify_ESP.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/infiniteAverage


#include "infiniteAverage.h"

IAVG IA;

uint32_t lastTime = 0;

double sum = 0;
uint64_t cnt = 0;


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


//  -- END OF FILE --

