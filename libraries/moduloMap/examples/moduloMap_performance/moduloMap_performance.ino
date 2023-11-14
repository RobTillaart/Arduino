//
//    FILE: moduloMap_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/moduloMap


#include "Arduino.h"
#include "moduloMap.h"

MODMAP  mm;

uint32_t start, stop;
volatile float f;
volatile float t = 5;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("MODMAP_LIB_VERSION: ");
  Serial.println(MODMAP_LIB_VERSION);
  delay(1000);

  start = micros();
  mm.begin(PI, 2 * PI);
  stop = micros();

  Serial.print("begin() call:\t");
  Serial.println(stop - start);
  delay(1000);


  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    f = mm.map(i);
  }
  stop = micros();

  Serial.print("1000 map() calls:\t");
  Serial.println(stop - start);
  delay(1000);


  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    f = mm.map(t);
  }
  stop = micros();

  Serial.print("1000 map() calls:\t");
  Serial.println(stop - start);
  delay(1000);

/*
  t = 500;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    f = mm.map(t);
  }
  stop = micros();

  Serial.print("1000 map() calls:\t");
  Serial.println(stop - start);
  delay(1000);
*/

  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
