//
//    FILE: statistic_add_overflow.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: this sketch shows a known (rounding) problem when the
//          internal sum is orders of magnitude larger than the added value.


#include "Statistic.h"

Statistic myStats;


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("STATISTIC_LIB_VERSION: ");
  Serial.println(STATISTIC_LIB_VERSION);
  
  myStats.clear();

  Serial.println("\nCOUNT\tVALUE\tACTUAL\tRATIO");
  for (float value = 1e8; value > 1; value *= 0.1)
  {
    float actual = myStats.add(value);
    float ratio = actual / value;

    Serial.print(myStats.count());
    Serial.print('\t');
    Serial.print(value);
    Serial.print('\t');
    Serial.print(actual);
    Serial.print('\t');
    Serial.print(ratio);
    Serial.print('\n');
  }

  for (float value = 10; value > 0.1; value -= 1)
  {
    float actual = myStats.add(value);
    float ratio = actual / value;

    Serial.print(myStats.count());
    Serial.print('\t');
    Serial.print(value);
    Serial.print('\t');
    Serial.print(actual);
    Serial.print('\t');
    Serial.print(ratio);
    Serial.print('\n');
  }

   Serial.print("\nQED...");
}


void loop(void)
{
}


// -- END OF FILE --

