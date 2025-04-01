//
//    FILE: GUID_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/UUID


#include "Arduino.h"
#include "UUID.h"


GUID guid;

uint32_t start, stop, randomtime;


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
  
  start = micros();
  guid.seed(2);
  stop = micros();

  Serial.print("       seed: ");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  guid.generate();
  stop = micros();

  Serial.print("   generate: ");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  guid.toCharArray();
  stop = micros();

  Serial.print("toCharArray: ");
  Serial.println(stop - start);
  delay(100);

  Serial.print("GUID: ");
  Serial.println(guid);
}


void loop()
{
  guid.generate();
  Serial.print("GUID: ");
  Serial.println(guid);
  delay(1000);
}


//  -- END OF FILE --
