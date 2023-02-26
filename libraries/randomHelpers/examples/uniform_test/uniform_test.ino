//
//    FILE: uniform_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2021-11-15
//     URL: https://github.com/RobTillaart/randomHelpers


#include "randomHelpers.h"

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("RANDOM_HELPERS_VERSION: ");
  Serial.println(RANDOM_HELPERS_VERSION);
  Serial.println();

  test_throwDice();

  Serial.println("\ndone...");
}


void loop()
{
}


void test_throwDice()
{
  Serial.println(__FUNCTION__);
  Serial.println("takes ~20 seconds...\n");

  delay(10);
  uint32_t ar[10];
  for (int i = 0; i < 10; i++) ar[i] = 0;

  start = micros();
  for (uint32_t i = 0; i < 1000000; i++)
  {
    uint8_t x = throwDice();
    ar[x - 1]++;
  }
  stop = micros();
  for (int i = 0; i < 10; i++)
  {
    Serial.print("\t");
    Serial.print(ar[i]);
  }
  Serial.println();
  for (int i = 0; i < 6; i++)
  {
    Serial.print("\t");
    Serial.print(ar[i] / 1666.6666 - 100, 2);
    Serial.print("%");
  }
  Serial.println();
  Serial.println();
  Serial.println((stop - start) * 1e-6, 2);
  Serial.println();
  delay(10);
}


//  -- END OF FILE --
