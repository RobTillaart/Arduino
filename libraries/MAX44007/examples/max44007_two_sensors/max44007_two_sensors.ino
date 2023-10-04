//
//    FILE: Max44007_two_sensors.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Max44007 library
//    DATE: 2022-01-04


#include "Wire.h"
#include "Max44007.h"

Max44007 LuxA(0x5A);
Max44007 LuxB(0x5B);

uint32_t lastDisplay = 0;
uint32_t count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX44007_LIB_VERSION: ");
  Serial.println(MAX44007_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);

  Serial.print("\n\tCOUNT\tLUXA\tLUXB\n");
}


void loop()
{
  const uint32_t interval = 500;

  if (millis() - lastDisplay >= interval)
  {
    lastDisplay += interval;
    count++;
    if (count % 10 == 0)
    {
      Serial.print("\n\tCOUNT\tLUXA\tLUXB\n");
    }
    Serial.print('\t');
    Serial.print(count);
    Serial.print('\t');

    float lux = LuxA.getLux();
    int err = LuxA.getError();
    if (err != 0) Serial.print(err);
    else          Serial.print(lux);
    Serial.print('\t');

    lux = LuxB.getLux();
    err = LuxB.getError();
    if (err != 0) Serial.print(err);
    else          Serial.print(lux);
    Serial.println();
  }
}


// -- END OF FILE --
