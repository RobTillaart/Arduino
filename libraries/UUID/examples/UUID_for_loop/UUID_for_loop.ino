//
//    FILE: UUID_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo different initialization in a loop
//     URL: https://github.com/RobTillaart/UUID


#include "Arduino.h"
#include "UUID.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println(__FILE__);
  Serial.print("UUID_LIB_VERSION: ");
  Serial.println(UUID_LIB_VERSION);
  Serial.println();
}


void loop()
{
  //  UUID initializes differently every loop.
  for (int i = 0; i < 5; i++)
  {
    UUID uuid;
    Serial.print("UUID: ");
    Serial.println(uuid);
    // delay(100);
  }
  Serial.println();
}


//  -- END OF FILE --
