//    FILE: fastShiftIn_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch
//     URL: https://github.com/RobTillaart/FastShiftIn


#include "FastShiftIn.h"

FastShiftIn FSI(12, 13);

volatile uint32_t x = 0;

uint32_t start, duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(FASTSHIFTIN_LIB_VERSION);

  FSI.setBitOrder(LSBFIRST);

  digitalWrite(12, HIGH);
  Serial.println("\n 8 bits HIGH\n");

  Serial.println("\nPerformance - time in us : read()");
  test_read();

  Serial.println("\nPerformance - time in us : read16()");
  test_read16();

  Serial.println("\nPerformance - time in us : read24()");
  test_read24();

  Serial.println("\nPerformance - time in us : read32()");
  test_read32();

  Serial.println("\nPerformance - time in us : readLSBFIRST()");
  test_readLSBFIRST();

  Serial.println("\nPerformance - time in us : readMSBFIRST()");
  test_readMSBFIRST();

  Serial.println("\nPerformance - time in us : reference shiftIn()");
  test_reference();

  Serial.println("done...");
}


void test_read()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.read();
  }
  duration1 = micros() - start;
  Serial.print("FastShiftIn1: ");
  Serial.println(duration1 * 0.001);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.read();
    x = FSI.read();
  }
  duration2 = micros() - start;
  Serial.print("FastShiftIn2: ");
  Serial.println(duration2 * 0.001);
  Serial.print("       Delta: ");
  Serial.println((duration2 - duration1) * 0.001);
  Serial.println();
  delay(100);
}


void test_read16()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.read16();
  }
  duration1 = micros() - start;
  Serial.print("FastShiftIn1: ");
  Serial.println(duration1 * 0.001);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.read16();
    x = FSI.read16();
  }
  duration2 = micros() - start;
  Serial.print("FastShiftIn2: ");
  Serial.println(duration2 * 0.001);
  Serial.print("       Delta: ");
  Serial.println((duration2 - duration1) * 0.001);
  Serial.println();
  delay(100);
}


void test_read24()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.read24();
  }
  duration1 = micros() - start;
  Serial.print("FastShiftIn1: ");
  Serial.println(duration1 * 0.001);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.read24();
    x = FSI.read24();
  }
  duration2 = micros() - start;
  Serial.print("FastShiftIn2: ");
  Serial.println(duration2 * 0.001);
  Serial.print("       Delta: ");
  Serial.println((duration2 - duration1) * 0.001);
  Serial.println();
  delay(100);
}


void test_read32()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.read32();
  }
  duration1 = micros() - start;
  Serial.print("FastShiftIn1: ");
  Serial.println(duration1 * 0.001);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.read32();
    x = FSI.read32();
  }
  duration2 = micros() - start;
  Serial.print("FastShiftIn2: ");
  Serial.println(duration2 * 0.001);
  Serial.print("       Delta: ");
  Serial.println((duration2 - duration1) * 0.001);
  Serial.println();
  delay(100);
}


void test_readLSBFIRST()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.readLSBFIRST();
  }
  duration1 = micros() - start;
  Serial.print("FastShiftIn1: ");
  Serial.println(duration1 * 0.001);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.readLSBFIRST();
    x = FSI.readLSBFIRST();
  }
  duration2 = micros() - start;
  Serial.print("FastShiftIn2: ");
  Serial.println(duration2 * 0.001);
  Serial.print("       Delta: ");
  Serial.println((duration2 - duration1) * 0.001);
  Serial.println();
  delay(100);
}


void test_readMSBFIRST()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.readMSBFIRST();
  }
  duration1 = micros() - start;
  Serial.print("FastShiftIn1: ");
  Serial.println(duration1 * 0.001);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.readMSBFIRST();
    x = FSI.readMSBFIRST();
  }
  duration2 = micros() - start;
  Serial.print("FastShiftIn2: ");
  Serial.println(duration2 * 0.001);
  Serial.print("       Delta: ");
  Serial.println((duration2 - duration1) * 0.001);
  Serial.println();
  delay(100);
}


void test_reference()
{
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = shiftIn(12, 13, LSBFIRST);
  }
  duration1 = micros() - start;
  Serial.print("Standard shiftIn1: ");
  Serial.println(duration1 * 0.001);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = shiftIn(12, 13, LSBFIRST);
    x = shiftIn(12, 13, LSBFIRST);
  }
  duration2 = micros() - start;
  Serial.print("Standard shiftIn2: ");
  Serial.println(duration2 * 0.001);
  Serial.print("            Delta: ");
  Serial.println((duration2 - duration1) * 0.001);
  Serial.println();
  delay(100);
}


void loop()
{
}


// -- END OF FILE --
