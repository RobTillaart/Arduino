//
//    FILE: asyncAnalogTest.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2018-09-05

#include "AsyncAnalog.h"

AsyncAnalog AA(A0);

uint32_t start = 0;
uint32_t duration = 0;
uint16_t count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("start: ");
  Serial.println(analogRead(0));

  AA.start();
  start = micros();
}

void loop()
{

  // if sample ready 
  if (AA.ready())
  {
    // process sample
    duration = micros() - start;

    Serial.print(duration);
    Serial.print("\t");
    Serial.print(AA.value());
    Serial.print("\t");
    Serial.print(count);
    Serial.println();

    // request a new sample
    AA.start();
    start = micros();
    count = 0;
  }

  // do other stuff here
  count++;
}

// END OF FILE