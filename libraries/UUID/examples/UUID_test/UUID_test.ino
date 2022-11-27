//
//    FILE: UUID_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "Arduino.h"
#include "UUID.h"


UUID uuid;

uint32_t start, stop, randomtime;


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("UUID_test.ino");
  Serial.print("UUID_LIB_VERSION: ");
  Serial.println(UUID_LIB_VERSION);
  delay(100);
  
  start = micros();
  uuid.seed(2);
  stop = micros();

  Serial.print("       seed: ");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uuid.generate();
  stop = micros();

  Serial.print("   generate: ");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uuid.toCharArray();
  stop = micros();

  Serial.print("toCharArray: ");
  Serial.println(stop - start);
  delay(100);

  Serial.print("UUID: ");
  Serial.println(uuid);
}


void loop()
{
  uuid.generate();
  Serial.print("UUID: ");
  Serial.println(uuid);
  delay(1000);
}


// -- END OF FILE --
