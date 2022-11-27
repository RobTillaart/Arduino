//
//    FILE: UUID_random_seed.ino
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

  uint32_t seedling = extractEntropy();
  Serial.println(seedling, HEX);

  start = micros();
  uuid.seed(seedling);
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


uint32_t extractEntropy()
{
  // GET COMPILE TIME ENTROPY
  uint32_t r = 0;
  uint16_t len = strlen(__FILE__);
  for (uint16_t i = 0; i < len; i++)
  {
    r ^= __FILE__[i];
    r = r * (r << 3);
  }
  len = strlen(__DATE__);
  for (uint16_t i = 0; i < len; i++)
  {
    r ^= __DATE__[i];
    r = r * (r << 17);
  }
  len = strlen(__TIME__);
  for (uint16_t i = 0; i < len; i++)
  {
    r ^= __TIME__[i];
    r = r * (r << 7);
  }

  // GET RUNTIME ENTROPY
  Serial.println("send 8 chars");
  uint32_t mask = 0;
  for (int i = 0; i < 8; i++)
  {
    while (Serial.available() == 0);
    if (Serial.available())
    {
      mask <<= 7;
      mask ^= micros();
      Serial.read();
    }
  }
  return r ^ mask;
}


//  -- END OF FILE --

