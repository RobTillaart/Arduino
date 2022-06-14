//
//    FILE: UUID_minimum.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo - will generate same UUID's  (no external entropy)

#include "Arduino.h"
#include "UUID.h"

UUID uuid;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("UUID_minimum.ino");
  Serial.print("UUID_LIB_VERSION: ");
  Serial.println(UUID_LIB_VERSION);
}


void loop()
{
  uuid.generate();
  Serial.print("UUID: ");
  Serial.println(uuid);
  delay(100);
}


// -- END OF FILE --
