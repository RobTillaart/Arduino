//
//    FILE: log10_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: log performance test
//     URL: https://github.com/RobTillaart/fast_math


#include "Arduino.h"
#include "fast_math.h"


uint32_t start, stop;
float x, y;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTMATH_LIB_VERSION: ");
  Serial.println(FASTMATH_LIB_VERSION);
  Serial.println();
  delay(1000);

  Serial.println("Function\ttime\tX\tY\n");
  x = random(1000000) * 0.001;

  float inverseLog10_2 = 1.0 / log10(2);

  start = micros();
  y = log10(x) * inverseLog10_2;  //  mul is faster than div log10(2)
  stop = micros();
  Serial.print("log2: ");
  Serial.print("\t\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x, 3);
  Serial.print("\t");
  Serial.print(y, 6);
  Serial.print("\n");
  delay(100);

  start = micros();
  y = fastLog2(x);
  stop = micros();
  Serial.print("fast2: ");
  Serial.print("\t\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x, 3);
  Serial.print("\t");
  Serial.print(y, 6);
  Serial.print("\n");
  delay(100);

  start = micros();
  y = log10(x);
  stop = micros();
  Serial.print("log10: ");
  Serial.print("\t\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x, 3);
  Serial.print("\t");
  Serial.print(y, 6);
  Serial.print("\n");
  delay(100);

  start = micros();
  y = fastLog10(x);
  stop = micros();
  Serial.print("fast10: ");
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x, 3);
  Serial.print("\t");
  Serial.print(y, 6);
  Serial.print("\n");
  delay(100);

  start = micros();
  y = log(x);
  stop = micros();
  Serial.print("log: ");
  Serial.print("\t\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x, 3);
  Serial.print("\t");
  Serial.print(y, 6);
  Serial.print("\n");
  delay(100);

  start = micros();
  y = fastLog(x);
  stop = micros();
  Serial.print("fastLog: ");
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(x, 3);
  Serial.print("\t");
  Serial.print(y, 6);
  Serial.print("\n");
  delay(100);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
