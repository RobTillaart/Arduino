//
//    FILE: dewpoint_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-04-04


#include "temperature.h"


uint32_t start;
uint32_t duration1;
uint32_t duration2;

float maxError;
volatile float dp;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TEMPERATURE_LIB_VERSION: ");
  Serial.println(TEMPERATURE_LIB_VERSION);
  Serial.println();
  Serial.println("takes ~40 seconds");

  Serial.println(dewPoint(25, 50), 2);
  Serial.println(dewPointFast(25, 50), 2);

  Serial.println("\ndewPoint()");
  start = millis();
  for (int cel = -40; cel < 80; cel++)
  {
    for (int hum = 1; hum < 100; hum++)
    {
      dp = dewPoint(cel, hum);
    }
  }
  duration1 = millis() - start;
  Serial.println(duration1);

  Serial.println("\ndewPointFast()");
  start = millis();
  for (int cel = -40; cel < 80; cel++)
  {
    for (int hum = 1; hum < 100; hum++)
    {
      dp = dewPointFast(cel, hum);
    }
  }
  duration2 = millis() - start;
  Serial.println(duration2);
  Serial.print("RATIO:\t");
  Serial.println((1.0 * duration1) / duration2, 3);


  Serial.println("\ndewPointFast() vs dewPoint()");
  for (int cel = -40; cel < 80; cel++)
  {
    for (int hum = 1; hum < 100; hum++)
    {
      float x = abs(dewPoint(cel, hum) - dewPointFast(cel, hum));
      if (x > maxError) maxError = x;
    }
  }
  Serial.print("ERROR:\t");
  Serial.println(maxError, 3);


  Serial.print("Done...");
}


void loop()
{
}


//  -- END OF FILE --

