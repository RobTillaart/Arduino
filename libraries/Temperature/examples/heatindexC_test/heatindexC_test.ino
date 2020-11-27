//
//    FILE: heatindexC_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-04-04
//

#include "temperature.h"

uint32_t start;
uint32_t duration1;

volatile float hi;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println(heatIndexC(25, 50), 2);

  start = millis();
  for (int cel = 10; cel < 80; cel++)
  {
    for (int hum = 1; hum < 100; hum++)
    {
      hi = heatIndexC(cel, hum);
    }
  }
  duration1 = millis() - start;
  Serial.println(duration1);


  Serial.print("Done...");
}

void loop()
{

}

// -- END OF FILE --
