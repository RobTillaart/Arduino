//
//    FILE: max44009_two_sensors.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo of max44009 library
//    DATE: 2020-02-16
//
// Released to the public domain
//

#include "Wire.h"
#include "Max44009.h"

Max44009 LuxA(0x4A);
Max44009 LuxB(0x4B);

uint32_t lastDisplay = 0;
uint32_t count = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("Start max44009_two_sensors : ");
  Serial.println(MAX44009_LIB_VERSION);

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

// END OF FILE