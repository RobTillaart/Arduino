//
//    FILE: randomHelpers_shuffle_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance test
//     URL: https://github.com/RobTillaart/randomHelpers


#include "randomHelpers.h"

uint32_t start, stop, duration1, duration2;

volatile uint32_t x;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RANDOM_HELPERS_VERSION: ");
  Serial.println(RANDOM_HELPERS_VERSION);
  Serial.println();
  delay(100);

  test_shuffleArrayFY();

  Serial.println("\ndone...");
}


void loop()
{
}


void test_shuffleArrayFY()
{
  float ar[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = shuffleArrayFY<float>(ar, 10);
  }
  duration1 = micros() - start;

  Serial.println(__FUNCTION__);
  Serial.print("TIME:\t");
  Serial.print(duration1);
  Serial.println();
  Serial.print("ar\t");
  for (int i = 0; i < 10; i++)
  {
    Serial.print(ar[i], 1);
    Serial.print("\t");
  }
  Serial.println();
  delay(100);


  int ar2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = shuffleArrayFY<int>(ar2, 10);
  }
  duration1 = micros() - start;

  Serial.println(__FUNCTION__);
  Serial.print("TIME:\t");
  Serial.print(duration1);
  Serial.println();
  Serial.print("ar2\t");
  for (int i = 0; i < 10; i++)
  {
    Serial.print(ar2[i]);
    Serial.print("\t");
  }
  Serial.println();
  delay(100);
}


//  -- END OF FILE --
