//
//    FILE: demo_count.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: search the longest palindrome
//    DATE: 2021-12-03
//     URL: https://github.com/RobTillaart/


#include "Arduino.h"
#include "palindrome.h"

palindrome pd;


uint32_t start, stop;

#define PLEN  1600
char str[PLEN];

int count;
float percentage;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  for (int i = 0; i < PLEN - 1; i++)
  {
    str[i] = 'a' + random(4);
  }
  str[PLEN - 1] = 0;

  // Serial.println(str);
  // delay(100);

  start = micros();
  count = pd.palindromeCount(str);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(count);
  Serial.println();
  delay(100);

  start = micros();
  percentage = pd.palindromePercentage(str);
  stop = micros();
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(percentage, 1);
  Serial.print("%");
  Serial.println();
  delay(100);

  Serial.println("done...");
}


void loop()
{
  /*
  for (int size = 100; size < 200; size++)
  {
    for (int i = 0; i < size; i++)
    {
      str[i] = 'a' + random(4);
    }
    str[size - 1] = 0;
    start = micros();
    percentage = pd.palindromePercentage(str);
    stop = micros();
    // Serial.print(stop - start);
    Serial.print("\t");
    Serial.print(percentage);
    Serial.println();
  }
  */
}



// -- END OF FILE --
