//
//    FILE: fastShiftIn.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: test sketch
//     URL:
//
// Released to the public domain
//

#include "FastShiftIn.h"

FastShiftIn FSI(12, 13, LSBFIRST);

volatile int x = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("example fastShiftIn: "); 
  Serial.println(FASTSHIFTIN_LIB_VERSION);

  digitalWrite(12, HIGH);
  Serial.println("\n 8 bits HIGH\n"); 

  Serial.println("\nPerformance - time in us"); 
  uint32_t start = micros();
  for (int i=0; i<100; i++)
  {
    x = FSI.read();
  }
  uint32_t duration = micros() - start;
  Serial.print("FastShiftIn1: ");
  Serial.println(duration/100.0, 1);

  start = micros();
  for (int i=0; i<100; i++)
  {
    x = FSI.read();
    x = FSI.read();
  }
  duration = micros() - start;
  Serial.print("FastShiftIn2: ");
  Serial.println(duration/100.0, 1);


  start = micros();
  for (int i=0; i<10000; i++)
  {
    x = shiftIn(12, 13, LSBFIRST);
  }
  duration = micros() - start;
  Serial.print("Standard shiftIn1: ");
  Serial.println(duration/10.0, 1);

  start = micros();
  for (int i=0; i<10000; i++)
  {
    x = shiftIn(12, 13, LSBFIRST);
    x = shiftIn(12, 13, LSBFIRST);
  }
  duration = micros() - start;
  Serial.print("Standard shiftIn2: ");
  Serial.println(duration/10.0, 1);
}

void loop()
{
}
