//
//    FILE: distanceTable_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of memory efficient distance table class
//    DATE: 2015-06-18
//     URL: https://github.com/RobTillaart/DistanceTable
//


#include "DistanceTable.h"


DistanceTable dt(20);

uint32_t start;
uint32_t stop;


void setup()
{
  Serial.begin(115200);
  Serial.print("DistanceTable: ");
  Serial.println(DISTANCETABLE_LIB_VERSION);
  Serial.println("DistanceTable test 20x20: ");

  Serial.println("\n========================================\n");
  Serial.println(dt.elements());
  Serial.println(dt.memoryUsed());
  Serial.println("\n========================================\n");

  dt.clear();
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      dt.set(i, j, i * j + PI);
    }
  }

  dt.dump();
  dt.setInvert(true);
  dt.dump();
  dt.setInvert(false);
  delay(100);

  dt.set(5, 6, 1);

  uint8_t a = 0, b = 0;
  start = micros();
  float v1 = dt.minimum(a, b);
  stop = micros();
  Serial.print("minimum:\t");
  Serial.println(stop - start);
  Serial.println(v1);
  Serial.println(a);
  Serial.println(b);
  Serial.println();
  delay(100);

  start = micros();
  float v2 = dt.maximum(a, b);
  stop = micros();
  Serial.print("maximum:\t");
  Serial.println(stop - start);
  Serial.println(v2);
  Serial.println(a);
  Serial.println(b);
  Serial.println();
  delay(100);


  start = micros();
  float v3 = dt.sum();
  stop = micros();
  Serial.print("sum:\t");
  Serial.println(stop - start);
  Serial.println(v3);
  Serial.println();
  delay(100);


  start = micros();
  float v4 = dt.average();
  stop = micros();
  Serial.print("average:\t");
  Serial.println(stop - start);
  Serial.println(v4);
  Serial.println();
  delay(100);

  Serial.println("\n========================================\n");
  delay(100);
  dt.setInvert(true);

  start = micros();
  v1 = dt.minimum(a, b);
  stop = micros();
  Serial.print("minimum:\t");
  Serial.println(stop - start);
  Serial.println(v1);
  Serial.println(a);
  Serial.println(b);
  Serial.println();
  delay(100);

  start = micros();
  v2 = dt.maximum(a, b);
  stop = micros();
  Serial.print("maximum:\t");
  Serial.println(stop - start);
  Serial.println(v2);
  Serial.println(a);
  Serial.println(b);
  Serial.println();
  delay(100);

  Serial.println("\n========================================\n");
  delay(10);
  Serial.println("21.14");
  Serial.print("COUNT: ");
  Serial.println(dt.count(21.14, 0.005));
  delay(10);

  dt.set(1, 3, -21.14);
  Serial.print("COUNT: ");
  Serial.println(dt.count(21.14, 0.005));
  delay(10);

  dt.setInvert(false);

  Serial.print("COUNT: ");
  Serial.println(dt.count(21.15, 0.005));
  delay(10);
  Serial.print("ABOVE: ");
  Serial.println(dt.countAbove(21.15));
  delay(10);
  Serial.print("BELOW: ");
  Serial.println(dt.countBelow(21.15));
  delay(10);
}


void loop()
{
}


// -- END OF FILE --
