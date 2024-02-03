//
//    FILE: fastMap_performance_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of FastMap class ==> a faster map function
//     URL: https://github.com/RobTillaart/FastMap


#include "FastMap.h"

uint32_t start;
uint32_t stop;
uint32_t reference;

volatile long zz = 3000, yy = 20000;
volatile float x;
volatile int z;

FastMap mapper;
FastMapDouble mapperD;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTMAP_LIB_VERSION: ");
  Serial.println(FASTMAP_LIB_VERSION);
  Serial.println();
  delay(100);

  //  Get a non optimizable value;
  z = analogRead(A0);


  //  REFERENCE
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = map(z, 0, 1023, yy, zz);
  }
  stop = micros();
  reference = stop - start;
  Serial.print("MAP:\t");
  Serial.println(reference);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);
  Serial.println();
  delay(100);



  //  FASTMAP
  mapper.init(0, 1023, yy, zz);
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = mapper.map(z);
  }
  stop = micros();
  Serial.print("FASTMAP:\t");
  Serial.println(stop - start);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);
  Serial.print("Performance factor: ");
  Serial.println((float)reference / (stop - start));
  Serial.println();
  delay(100);



  //  FASTMAPDOUBLE
  mapperD.init(0, 1023, yy, zz);
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = mapperD.map(z);
  }
  stop = micros();
  Serial.print("FASTMAPD:\t");
  Serial.println(stop - start);
  Serial.print(z);
  Serial.print(" -> ");
  Serial.println(x);
  Serial.print("Performance factor: ");
  Serial.println((float)reference / (stop - start));
  Serial.println();

}


void loop()
{
}


//  -- END OF FILE --
