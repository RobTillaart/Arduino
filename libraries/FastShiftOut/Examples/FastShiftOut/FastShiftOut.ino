//
//    FILE: fastShiftOut.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: test sketch
//     URL:
//
// Released to the public domain
//

#include "FastShiftOut.h"

FastShiftOut FSO(12, 13, LSBFIRST);

void setup()
{
  Serial.begin(115200);
  Serial.print("example fastShiftOut: "); 
  Serial.println(FASTSHIFTOUT_LIB_VERSION);

  Serial.println("\nPerformance - time in us"); 
  uint32_t start = micros();
  for (int i=0; i<100; i++)
  {
    FSO.write(0x55);
  }
  uint32_t duration = micros() - start;
  Serial.print("FastShiftOut1: ");
  Serial.println(duration/100.0, 1);

  start = micros();
  for (int i=0; i<100; i++)
  {
    FSO.write(0x55);
    FSO.write(0x55);
  }
  duration = micros() - start;
  Serial.print("FastShiftOut2: ");
  Serial.println(duration/100.0, 1);


  start = micros();
  for (int i=0; i<100; i++)
  {
    shiftOut(12, 13, 0x55, LSBFIRST);
  }
  duration = micros() - start;
  Serial.print("Standard shiftOut1: ");
  Serial.println(duration/100.0, 1);

  start = micros();
  for (int i=0; i<100; i++)
  {
    shiftOut(12, 13, 0x55, LSBFIRST);
    shiftOut(12, 13, 0x55, LSBFIRST);
  }
  duration = micros() - start;
  Serial.print("Standard shiftOut2: ");
  Serial.println(duration/100.0, 1);


  Serial.println("\nTest print interface");
  start = micros();
  for (int i=0; i<100; i++)
  {
    FSO.println("Hello world");
  }
  duration = micros() - start;
  Serial.print("println(\"Hello world\"): ");
  Serial.println(duration/100.0, 1);


  start = micros();
  for (int i=0; i<100; i++)
  {
    FSO.println(1357);
  }
  duration = micros() - start;
  Serial.print("println(1357): ");
  Serial.println(duration/100.0, 1);


  start = micros();
  for (int i=0; i<100; i++)
  {
    FSO.println(3.14159265, 4);
  }
  duration = micros() - start;
  Serial.print("println(3.14159265, 4): ");
  Serial.println(duration/100.0, 1);

  Serial.println("\ndone");
}

void loop()
{
}


