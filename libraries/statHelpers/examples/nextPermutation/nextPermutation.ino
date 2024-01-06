//
//    FILE: nextPermutation.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/statHelpers


#include "statHelpers.h"


char hello[] = "abcde";
uint32_t count = 0;

uint8_t score[] = { 1, 2, 3, 4, 5, 6 };
uint8_t score2[] = { 1, 2, 3, 4, 5, 6 };
uint32_t start, duration1;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("STATHELPERS_LIB_VERSION: ");
  Serial.println(STATHELPERS_LIB_VERSION);
  Serial.println();

  Serial.println("120 permutations + print");
  do
  {
    Serial.print(count++);
    Serial.print('\t');
    Serial.println(hello);
  }
  while (nextPermutation<char>(hello, 5));


  ////////////////////////////////////////////////////////////////

  Serial.println("timing 720 permutations + print");
  start = micros();
  count = 0;
  do
  {
    Serial.print(count++);
    Serial.print('\t');
    for (uint8_t i = 0; i < 6; i++) Serial.print(score[i]);
    Serial.println();
  }
  while (nextPermutation<uint8_t>(score, 6));
  duration1 = micros() - start;
  
  Serial.println("\ntiming 720 permutations + print");
  Serial.print("time:\t");
  Serial.println(duration1);
  delay(10);


  ////////////////////////////////////////////////////////////////

  start = micros();
  while (nextPermutation<uint8_t>(score2, 6));
  duration1 = micros() - start;
  Serial.println("\ntiming 120 permutations only");
  Serial.print("time:\t");
  Serial.println(duration1);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

