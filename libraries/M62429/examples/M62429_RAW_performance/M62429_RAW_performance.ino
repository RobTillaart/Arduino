//
//    FILE: M62429_RAW_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo M62429_RAW class for IC FM62429


#include "M62429.h"

uint32_t start, stop;

M62429_RAW  AMP;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("M62429_VERSION: ");
  Serial.println(M62429_VERSION);

  AMP.begin(4, 5);
  delay(100);

  start = micros();
  AMP.setAttn(0, 10);
  stop = micros();
  Serial.print("setAttn: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  AMP.setAttn(0, 10);
  stop = micros();
  Serial.print("setAttn: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  AMP.setAttn(0, 100);
  stop = micros();
  Serial.print("setAttn: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  AMP.setAttn(0, 100);
  stop = micros();
  Serial.print("setAttn: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  volatile uint8_t x = AMP.getAttn(0);
  stop = micros();
  Serial.print("getAttn: \t");
  Serial.println(stop - start);
  Serial.print("getAttn: \t");
  Serial.println(x);             //  keep build CI compiler happy

  delay(100);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
