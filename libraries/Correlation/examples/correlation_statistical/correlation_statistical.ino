//
//    FILE: correlation_statistical.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-05-17
// VERSION: 0.1.0
// PUPROSE: demo of the Correlation Library
//


#include "Correlation.h"

Correlation C;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  C.clear();
  Serial.print("cnt\tminX\tmaxX\tminY\tmaxY\n");
  for (int i = 0; i < 20; i++)
  {
    C.add(i * 10, i * 40 + 0.1 * random(10));
    Serial.print(C.count());
    Serial.print("\t");
    Serial.print(C.getMinX(), 2);
    Serial.print("\t");
    Serial.print(C.getMaxX(), 2);
    Serial.print("\t");
    Serial.print(C.getMinY(), 2);
    Serial.print("\t");
    Serial.print(C.getMaxY(), 2);
    Serial.println();
  }
  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --

