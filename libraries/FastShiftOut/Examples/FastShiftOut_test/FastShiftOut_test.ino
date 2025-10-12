//
//    FILE: FastShiftOut_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance test sketch
//     URL: https://github.com/RobTillaart/FastShiftOut

#include "FastShiftOut.h"

FastShiftOut FSO(12, 13, LSBFIRST);

uint32_t start, duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTSHIFTOUT_LIB_VERSION: ");
  Serial.println(FASTSHIFTOUT_LIB_VERSION);
  Serial.println();

  Serial.println("\nPerformance - time in us");
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();

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
  Serial.print("        write: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.write(0x55);
    FSO.write(0x55);
  }
  duration2 = micros() - start;
  Serial.print("        write: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("        Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();
  delay(100);
}


void test2()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.writeLSBFIRST(0x55);
  }
  duration1 = micros() - start;
  Serial.print("writeLSBFIRST: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.writeLSBFIRST(0x55);
    FSO.writeLSBFIRST(0x55);
  }
  duration2 = micros() - start;
  Serial.print("writeLSBFIRST: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("        Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();
  delay(100);
}


void test3()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.writeMSBFIRST(0x55);
  }
  duration1 = micros() - start;
  Serial.print("writeMSBFIRST: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.writeMSBFIRST(0x55);
    FSO.writeMSBFIRST(0x55);
  }
  duration2 = micros() - start;
  Serial.print("writeMSBFIRST: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("        Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();
  delay(100);
}


void test4()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    shiftOut(12, 13, LSBFIRST, 0x55);
  }
  duration1 = micros() - start;
  Serial.print("Standard shiftOut1: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    shiftOut(12, 13, LSBFIRST, 0x55);
    shiftOut(12, 13, LSBFIRST, 0x55);
  }
  duration2 = micros() - start;
  Serial.print("Standard shiftOut2: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("             Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();
  delay(100);
}


void test5()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.write16(0x5555);
  }
  duration1 = micros() - start;
  Serial.print("      write16: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.write16(0x5555);
    FSO.write16(0x5555);
  }
  duration2 = micros() - start;
  Serial.print("      write16: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("        Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();
  delay(100);
}


void test6()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.write24(0x555555);
  }
  duration1 = micros() - start;
  Serial.print("      write24: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.write24(0x555555);
    FSO.write24(0x555555);
  }
  duration2 = micros() - start;
  Serial.print("      write24: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("        Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();
  delay(100);
}


void test7()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.write32(0x55555555);
  }
  duration1 = micros() - start;
  Serial.print("      write32: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSO.write32(0x55555555);
    FSO.write32(0x55555555);
  }
  duration2 = micros() - start;
  Serial.print("      write32: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("        Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();
  delay(100);
}


void test8()
{
  Serial.println("\nTest print interface");
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    FSO.println("Hello world");
  }
  duration1 = micros() - start;
  Serial.print("println(\"Hello world\"): \t");
  Serial.println(duration1 * 0.01f);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    FSO.println(1357);
  }
  duration1 = micros() - start;
  Serial.print("println(1357): \t\t\t");
  Serial.println(duration1 * 0.01f);
  delay(100);

  start = micros();
  for (int i = 0; i < 100; i++)
  {
    FSO.println(3.14159265f, 4);
  }
  duration1 = micros() - start;
  Serial.print("println(3.14159265, 4): \t");
  Serial.println(duration1 * 0.01f);
  Serial.println();
  delay(100);
}


void loop()
{
}


//  -- END OF FILE --
