//
//    FILE: distanceTable_column_functions.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2015-06-18
//     URL: https://github.com/RobTillaart/DistanceTable
//


#include "DistanceTable.h"

DistanceTable dt(20);


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DISTANCETABLE_LIB_VERSION: ");
  Serial.println(DISTANCETABLE_LIB_VERSION);
  Serial.println();

  Serial.println("DistanceTable test 20x20: ");
  Serial.println("\n========================================\n");
  Serial.print("Size:\t\t");
  Serial.println(dt.dimension() * dt.dimension());
  Serial.print("elements:\t");
  Serial.println(dt.elements());
  Serial.print("memoryUsed:\t");
  Serial.println(dt.memoryUsed());
  Serial.println("\n========================================\n");

  dt.clear();
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      dt.set(i, j, random(1000) * 0.01);
    }
  }

  dt.dump();

  for (int i = 0; i < 20; i++)
  {
    Serial.print(dt.sumOfColumn(i));
    Serial.print("\t");
  }
  Serial.println();
  for (int i = 0; i < 20; i++)
  {
    Serial.print(dt.averageOfColumn(i));
    Serial.print("\t");
  }
  Serial.println();
  Serial.println();

  uint8_t a = 0;
  float v1 = dt.minColumn(a);
  Serial.print("minColumn:\t");
  Serial.print(a);
  Serial.print("\t");
  Serial.println(v1);
  delay(100);

  float v2 = dt.maxColumn(a);
  Serial.print("maxColumn:\t");
  Serial.print(a);
  Serial.print("\t");
  Serial.println(v2);
  delay(100);

  Serial.print("Ratio:\t\t\t");
  Serial.println(v1 / v2);
  Serial.println();
  delay(100);

  Serial.println();
  Serial.print("sumOfColumn(5):\t");
  Serial.println(dt.sumOfColumn(5));
  Serial.print("averageOfColumn(5):\t");
  Serial.println(dt.averageOfColumn(5));
  Serial.print("minimumOfColumn(5):\t");
  Serial.println(dt.minimumOfColumn(5));
  Serial.print("maximumOfColumn(5):\t");
  Serial.println(dt.maximumOfColumn(5));
  delay(100);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
