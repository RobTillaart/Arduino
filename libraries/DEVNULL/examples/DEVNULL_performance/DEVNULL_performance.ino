//
//    FILE: DEVNULL_performance.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-11-24
//    (c) : MIT
//


#include "DEVNULL.h"

DEVNULL dn;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DEVNULL_LIB_VERSION: ");
  Serial.println(DEVNULL_LIB_VERSION);
  delay(100);


  start = micros();
  dn.println("it is dark in here...");
  stop = micros();
  Serial.print("text1: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  dn.write((const uint8_t *) "it is dark in here...", 22);
  stop = micros();
  Serial.print("text2: \t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  dn.print(123456789L);
  stop = micros();
  Serial.print("long: \t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  dn.print(PI, 5);
  stop = micros();
  Serial.print("float: \t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  dn.print(PI, 10);
  stop = micros();
  Serial.print("float: \t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  dn.print(PI, 15);
  stop = micros();
  Serial.print("float: \t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  dn.print(PI, 20);
  stop = micros();
  Serial.print("float: \t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  bool b = dn.find("hello");
  stop = micros();
  Serial.print("find: \t");
  Serial.println(stop - start);
  delay(10);


  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --

