//
//    FILE: humidex_table.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-04-05


#include "temperature.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TEMPERATURE_LIB_VERSION: ");
  Serial.println(TEMPERATURE_LIB_VERSION);
  Serial.println();

  for (int cel = 20; cel < 45; cel++)
  {
    Serial.print("\t");
    Serial.print(cel);
  }
  Serial.println();
  Serial.println();

  for (int hum = 100; hum > 15; hum -= 2)
  {
    Serial.print(hum);
    for (int cel = 20; cel < 45; cel++)
    {
      float dp = dewPoint(cel, hum);
      float hi = humidex(cel, dp);
      Serial.print("\t");
      Serial.print(round(hi));
    }
    Serial.println();
  }
  Serial.println();
  Serial.println();

  Serial.print("Done...");
}


void loop()
{
}


//  -- END OF FILE --

