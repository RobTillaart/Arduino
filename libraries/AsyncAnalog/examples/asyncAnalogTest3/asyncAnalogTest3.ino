//
//    FILE: asyncAnalogTest3.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AsyncAnalog
//
//  measure micros() per 1000 calls
//


#include "AsyncAnalog.h"


AsyncAnalog AA(A0);

uint32_t start = 0;
uint32_t duration = 0;

volatile bool b;
volatile int x;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ASYNCANALOG_LIB_VERSION: ");
  Serial.println(ASYNCANALOG_LIB_VERSION);
  Serial.println();

  Serial.print("\nstart: ");
  Serial.println(analogRead(0));
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) AA.start();
  duration = micros() - start;
  Serial.print("START: \t");
  Serial.println(duration);
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) b = AA.ready();
  duration = micros() - start;
  Serial.print("READY: \t");
  Serial.println(duration);
  delay(100);


  start = micros();
  for (int i = 0; i < 1000; i++) x = AA.value();
  duration = micros() - start;
  Serial.print("VALUE: \t");
  Serial.println(duration);
  delay(100);

  Serial.println(b);
  Serial.println(x);
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
