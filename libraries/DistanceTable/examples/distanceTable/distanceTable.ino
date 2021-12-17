//
//    FILE: distanceTable.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of memory efficient distance table class
//    DATE: 2015-06-18
//     URL: https://github.com/RobTillaart/DistanceTable
//


#include "DistanceTable.h"


#if defined (ARDUINO_ARCH_AVR)
uint32_t freeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (uint32_t) &v - (__brkval == 0 ? (uint32_t) &__heap_start : (uint32_t) __brkval);
};
#else
uint32_t freeRam()
{
  return -1;
};
#endif


DistanceTable dt(20);

uint32_t start;
uint32_t stop;


void setup()
{
  Serial.begin(115200);
  Serial.print("DistanceTable: ");
  Serial.println(DISTANCETABLE_LIB_VERSION);
  Serial.println("DistanceTable test 20x20: ");

  Serial.print("clear:\t");
  start = micros();
  dt.clear();
  stop = micros();
  Serial.println(stop - start);


  Serial.print("set:\t");
  start = micros();
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      dt.set(i, j, i * j + PI);
    }
  }
  stop = micros();
  Serial.println(stop - start);


  Serial.print("get:\t");
  int count = 0;
  start = micros();
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      if ( dt.get(i, j) < 0.5 ) count++;
    }
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.print("count:\t");
  Serial.println(count);

  Serial.print("ram:\t");
  Serial.println(freeRam());

  Serial.println();
  Serial.println("dump:\t");
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      Serial.print( dt.get(i, j), 1);
      Serial.print("\t");
    }
    Serial.println();
  }

  Serial.println();
  Serial.println("dump:\t");
  dt.dump();

  Serial.println();
  Serial.println("done...");

  Serial.println("\n========================================\n");
  delay(10);

  dt.set (5, 6, 1);

  uint8_t a = 0, b = 0;
  start = micros();
  float v1 = dt.minimum(a, b);
  stop = micros();
  Serial.print("minimum:\t");
  Serial.println(stop - start);
  Serial.println(v1);
  Serial.println(a);
  Serial.println(b);
  delay(10);

  start = micros();
  float v2 = dt.maximum(a, b);
  stop = micros();
  Serial.print("maximum:\t");
  Serial.println(stop - start);
  Serial.println(v2);
  Serial.println(a);
  Serial.println(b);
  delay(10);

  Serial.println("\n========================================\n");
  delay(10);
  Serial.println(dt.count(21.14, 0.005));
  delay(10);


}


void loop()
{
}


// -- END OF FILE --
