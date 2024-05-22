//
//    FILE: Max44007_two_sensors.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Max44007 library
//     URL: https://github.com/RobTillaart/MAX44007


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
  Serial.println();

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
    int error = LuxA.getError();
    if (error != 0) Serial.print(error);
    else            Serial.print(lux);
    Serial.print('\t');

    lux = LuxB.getLux();
    error = LuxB.getError();
    if (error != 0) Serial.print(error);
    else            Serial.print(lux);
    Serial.println();
  }
}


//  -- END OF FILE --

