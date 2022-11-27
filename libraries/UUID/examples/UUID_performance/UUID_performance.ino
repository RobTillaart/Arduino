//
//    FILE: UUID_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "Arduino.h"
#include "UUID.h"


UUID uuid;


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("UUID_performance.ino");
  Serial.print("UUID_LIB_VERSION: ");
  Serial.println(UUID_LIB_VERSION);

  uint16_t count = 0;
  uuid.setVariant4Mode();
  uint32_t start = millis();
  while (millis() - start < 1000)
  {
    uuid.generate();
    count++;
  }
  Serial.print("Generate 4: ");
  Serial.print(count);
  Serial.println(" uuid's per second.");

  count = 0;
  uuid.setRandomMode();
  start = millis();
  while (millis() - start < 1000)
  {
    uuid.generate();
    count++;
  }
  Serial.print("Generate R: ");
  Serial.print(count);
  Serial.println(" uuid's per second.");
}


void loop()
{
}


// -- END OF FILE --
