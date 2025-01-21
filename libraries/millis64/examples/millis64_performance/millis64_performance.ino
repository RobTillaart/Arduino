//
//    FILE: millis64_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test performance
//     URL: https://github.com/RobTillaart/millis64
//          https://github.com/RobTillaart/printHelpers


#include "millis64.h"
#include "printHelpers.h"

uint32_t start, stop;

volatile uint64_t t64;
volatile uint32_t t32;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MILLIS64_LIB_VERSION: ");
  Serial.println(MILLIS64_LIB_VERSION);
  Serial.println();
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) t32 = millis();
  stop = micros();
  Serial.print("MILLIS(): \t");
  Serial.println(stop - start);
  Serial.print(t32);
  Serial.println();
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) t32 = millis32();
  stop = micros();
  Serial.print("MILLIS32(): \t");
  Serial.println(stop - start);
  Serial.print(t32);
  Serial.println();
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) t32 = millis32(20);
  stop = micros();
  Serial.print("MILLIS32(20): \t");
  Serial.println(stop - start);
  Serial.print(t32);
  Serial.println();
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) t64 = millis64();
  stop = micros();
  Serial.print("MILLIS64(): \t");
  Serial.println(stop - start);
  Serial.print(print64(t64));
  Serial.println();
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) t64 = millis64(20);
  stop = micros();
  Serial.print("MILLIS64(20): \t");
  Serial.println(stop - start);
  Serial.print(print64(t64));
  Serial.println();
  delay(100);

  Serial.println("\n------------------------------\n");
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++) t32 = micros();
  stop = micros();
  Serial.print("MICROS(): \t");
  Serial.println(stop - start);
  Serial.print(t32);
  Serial.println();
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) t32 = micros32();
  stop = micros();
  Serial.print("MICROS32(): \t");
  Serial.println(stop - start);
  Serial.print(t32);
  Serial.println();
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) t32 = micros32(20);
  stop = micros();
  Serial.print("MICROS32(20): \t");
  Serial.println(stop - start);
  Serial.print(t32);
  Serial.println();
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) t64 = micros64();
  stop = micros();
  Serial.print("MICROS64(): \t");
  Serial.println(stop - start);
  Serial.print(print64(t64));
  Serial.println();
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) t64 = micros64(20);
  stop = micros();
  Serial.print("MICROS64(20): \t");
  Serial.println(stop - start);
  Serial.print(print64(t64));
  Serial.println();
  delay(100);


  Serial.print("\ndone...");
  Serial.println();
}


void loop()
{
}




//  -- END OF FILE --
