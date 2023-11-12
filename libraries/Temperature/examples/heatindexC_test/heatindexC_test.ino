//
//    FILE: heatindexC_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo - test average performance per call in micros.
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

  Serial.println(heatIndexC(25, 50), 2);

  start = micros();
  int cnt = 0;
  for (int cel = 10; cel < 80; cel++)
  {
    for (int hum = 1; hum < 100; hum++)
    {
      hi = heatIndexC(cel, hum);
      cnt++;
    }
  }
  duration1 = micros() - start;
  Serial.println(duration1);
  Serial.println(1.0 * duration1 / cnt);

  Serial.print("Done...");
}


void loop()
{
}


//  -- END OF FILE --
