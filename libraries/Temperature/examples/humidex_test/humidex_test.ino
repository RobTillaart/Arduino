//
//    FILE: humidex_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-04-05


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

  Serial.println(humidex(25, 50), 2);

  start = millis();
  for (int t = 25; t <= 45; t++)
  {
    for (int hum = 1; hum <= 100; hum++)
    {
      float dp = dewPoint(t, hum);
      hi = humidex(t, dp);
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

