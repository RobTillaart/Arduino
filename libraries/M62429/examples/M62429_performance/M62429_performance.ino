//
//    FILE: M62429_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo volume IC FM62429
//    DATE: 2021-12-30


#include "M62429.h"

uint32_t start, stop;

M62429  AMP;


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
  AMP.setVolume(0, 10);
  stop = micros();
  Serial.print("setVolume: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  AMP.setVolume(0, 10);
  stop = micros();
  Serial.print("setVolume: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  AMP.setVolume(0, 100);
  stop = micros();
  Serial.print("setVolume: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  AMP.setVolume(0, 100);
  stop = micros();
  Serial.print("setVolume: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  volatile uint8_t x = AMP.getVolume(0);
  stop = micros();
  Serial.print("getVolume: \t");
  Serial.println(stop - start);
  Serial.print("getVolume: \t");
  Serial.println(x);               //  keep build-CI compiler happy
  delay(100);

  AMP.setVolume(2, 0);
  start = micros();
  AMP.incr();
  stop = micros();
  Serial.print("increment: \t");
  Serial.println(stop - start);
  delay(100);

  AMP.setVolume(2, 0);
  start = micros();
  AMP.decr();
  stop = micros();
  Serial.print("decrement: \t");
  Serial.println(stop - start);
  delay(100);

  AMP.setVolume(2, 10);
  start = micros();
  AMP.muteOn();
  stop = micros();
  Serial.print("muteOn: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  AMP.muteOff();
  stop = micros();
  Serial.print("muteOff: \t");
  Serial.println(stop - start);
  delay(100);

  AMP.setVolume(0, 10);
  AMP.setVolume(1, 20);
  start = micros();
  AMP.average();
  stop = micros();
  Serial.print("average: \t");
  Serial.println(stop - start);
  delay(100);

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
