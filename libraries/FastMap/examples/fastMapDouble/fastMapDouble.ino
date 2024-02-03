//
//    FILE: fastMapDouble.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of FastMapDouble class
//     URL: https://github.com/RobTillaart/FastMap
//
//    Note: the mapping used in the example cannot be done
//          with the normal map function.


#include "FastMap.h"

#include "printHelpers.h"    //  https://github.com/RobTillaart/printHelpers

uint32_t start, stop;
volatile double x;

FastMapDouble mapper;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FASTMAP_LIB_VERSION: ");
  Serial.println(FASTMAP_LIB_VERSION);
  Serial.println();

  //  Get a non optimizable value;
  volatile double pie = PI;

  //  FASTMAP
  //  map 0 .. 100% to lightspeed in km/hr
  mapper.init(0, 100, 0, 1.0792528488E+12);
  start = micros();
  for (int i = 0; i < 10000; i++)
  {
    x = mapper.map(pie);
  }
  stop = micros();
  Serial.print("10000 calls map:\t");
  Serial.print(pie, 5);
  Serial.print(" -> ");
  Serial.println(sci(x, 5));
  Serial.print("           time:\t");
  Serial.println(stop - start);
  Serial.println();

  Serial.println("PERC\tSpeed in Km/h");
  for (float p = 80; p <= 100; p += 0.25)
  {
    x = mapper.map(p);
    Serial.print(p, 2);
    Serial.print('\t');
    Serial.print(sci(x, 4));
    Serial.println();
  }
  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
