//
//    FILE: getRandomBits_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/randomHelpers


#include "randomHelpers.h"

uint32_t start, duration1, duration2;

volatile uint32_t x;

float sum = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RANDOM_HELPERS_VERSION: ");
  Serial.println(RANDOM_HELPERS_VERSION);
  Serial.println();
  delay(100);

 Serial.println("n\t rnd\t opt\t ratio\n");
  for (uint8_t i = 1; i <= 32; i++)
  {
    test_getRandomBits(i);
  }
  Serial.println();
  Serial.print("AVG ratio: ");
  Serial.println(sum / 32);
  Serial.println("\ndone...");
}


void loop()
{
}


void test_getRandomBits(uint8_t n)
{
  start = micros();
  uint32_t mask = ((1UL << n) - 1);
  for (int i = 0; i < 1000; i++)
  {
    x = random(0xFFFFFFFF) & mask;
  }
  duration1 = micros() - start;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = getRandomBits(n);
  }
  duration2 = micros() - start;

  float ratio = (1.0 * duration1) / duration2;
  sum += ratio;

  Serial.print(n);
  Serial.print("\t");
  Serial.print(duration1);
  Serial.print("\t");
  Serial.print(duration2);
  Serial.print("\t");
  Serial.print(ratio, 2);
  Serial.println();
  delay(10);
}


//  -- END OF FILE --
