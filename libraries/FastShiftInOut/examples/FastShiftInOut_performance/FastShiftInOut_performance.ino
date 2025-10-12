//
//    FILE: FastShiftInOut_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance test sketch
//     URL: https://github.com/RobTillaart/FastShiftInOut


#include "FastShiftInOut.h"

FastShiftInOut FSIO(8, 9, 0, LSBFIRST);   //  ESP32 needs other pins

uint32_t start, duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTSHIFTINOUT_LIB_VERSION: ");
  Serial.println(FASTSHIFTINOUT_LIB_VERSION);
  Serial.println();

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
    FSIO.write(0x55);
  }
  duration1 = micros() - start;
  Serial.print("        write: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSIO.write(0x55);
    FSIO.write(0x55);
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
    FSIO.writeLSBFIRST(0x55);
  }
  duration1 = micros() - start;
  Serial.print("writeLSBFIRST: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSIO.writeLSBFIRST(0x55);
    FSIO.writeLSBFIRST(0x55);
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
    FSIO.writeMSBFIRST(0x55);
  }
  duration1 = micros() - start;
  Serial.print("writeMSBFIRST: ");
  Serial.println(duration1 * 0.001f);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    FSIO.writeMSBFIRST(0x55);
    FSIO.writeMSBFIRST(0x55);
  }
  duration2 = micros() - start;
  Serial.print("writeMSBFIRST: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("        Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();
  delay(100);
}


void loop()
{
}


//  -- END OF FILE --
