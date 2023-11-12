//
//    FILE: heatIndex_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-04-04


#include "temperature.h"

uint32_t start;
uint32_t duration1;

volatile float hi;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TEMPERATURE_LIB_VERSION: ");
  Serial.println(TEMPERATURE_LIB_VERSION);
  Serial.println();

  Serial.println(heatIndex(100, 50), 2);

  start = millis();
  for (int t = 40; t < 110; t++)
  {
    for (int hum = 1; hum < 100; hum++)
    {
      hi = heatIndex(t, hum);
    }
  }
  duration1 = millis() - start;
  Serial.println(duration1);

  Serial.print("Done...");
}


void loop()
{
}


//  -- END OF FILE --

