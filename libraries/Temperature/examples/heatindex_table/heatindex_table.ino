//
//    FILE: heatindex_table.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-04-04


#include "temperature.h"


volatile float hi;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.println();
  
  for (int t = 80; t <= 110; t += 2)
  {
    Serial.print("\t");
    Serial.print(t);
  }
  Serial.println();
  Serial.println();

  for (int hum = 40; hum <= 100; hum += 5)
  {
    Serial.print(hum);
    for (int t = 80; t <= 110; t += 2)
    {
      float hi = heatIndex(t, hum);
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

// -- END OF FILE --
