//
//    FILE: FastShiftOut_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: test sketch
//     URL: https://github.com/RobTillaart/FastSHiftOut
//

#include "FastShiftOut.h"

FastShiftOut FSO(12, 13, LSBFIRST);

uint32_t start, duration1, duration2;

void setup()
{
  Serial.begin(115200);
  Serial.print("example fastShiftOut: ");
  Serial.println(FASTSHIFTOUT_LIB_VERSION);

  Serial.println("\nPerformance - time in us");
  test1();
  test2();
  test3();

  Serial.println("\ndone ...\n");
}

void test1()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.write(0x55);
  }
  duration1 = micros() - start;
  Serial.print("FastShiftOut1: ");
  Serial.println(duration1 * 0.001);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.write(0x55);
    FSO.write(0x55);
  }
  duration2 = micros() - start;
  Serial.print("FastShiftOut2: ");
  Serial.println(duration2 * 0.001);
  Serial.print("        Delta: ");
  Serial.println((duration2 - duration1) * 0.001);
  Serial.println();
  delay(100);
}


void test2()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    shiftOut(12, 13, LSBFIRST, 0x55);
  }
  duration1 = micros() - start;
  Serial.print("Standard shiftOut1: ");
  Serial.println(duration1 * 0.001);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    shiftOut(12, 13, LSBFIRST, 0x55);
    shiftOut(12, 13, LSBFIRST, 0x55);
  }
  duration2 = micros() - start;
  Serial.print("Standard shiftOut2: ");
  Serial.println(duration2 * 0.001);
  Serial.print("             Delta: ");
  Serial.println((duration2 - duration1) * 0.001);
  Serial.println();
  delay(100);
}

void test3()
{
  Serial.println("\nTest print interface");
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    FSO.println("Hello world");
  }
  duration1 = micros() - start;
  Serial.print("println(\"Hello world\"): \t");
  Serial.println(duration1 * 0.01);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    FSO.println(1357);
  }
  duration1 = micros() - start;
  Serial.print("println(1357): \t\t\t");
  Serial.println(duration1 * 0.01);


  start = micros();
  for (int i = 0; i < 100; i++)
  {
    FSO.println(3.14159265, 4);
  }
  duration1 = micros() - start;
  Serial.print("println(3.14159265, 4): \t");
  Serial.println(duration1 * 0.01);
  delay(100);
}

void loop()
{
}

// -- END OF FILE --
