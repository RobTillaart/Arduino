//
//    FILE: UUID_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/UUID


#include "Arduino.h"
#include "UUID.h"

UUID uuid;


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println(__FILE__);
  Serial.print("UUID_LIB_VERSION: ");
  Serial.println(UUID_LIB_VERSION);
  Serial.println();
  delay(100);

  uint16_t count = 0;
  uuid.setVersion4Mode();

  uint32_t start = millis();
  while (millis() - start < 1000)
  {
    uuid.generate();
    count++;
  }
  Serial.print("Generate 4: ");
  Serial.print(count);
  Serial.println(" uuid's per second.");
  delay(100);

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


//  -- END OF FILE --
