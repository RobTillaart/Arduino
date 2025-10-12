//
//    FILE: fastShiftIn_readMSBFIRST.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch
//     URL: https://github.com/RobTillaart/FastShiftIn


#include "FastShiftIn.h"

FastShiftIn FSI(12, 13);

volatile int x = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println("FASTSHIFTIN_LIB_VERSION: ");
  Serial.println(FASTSHIFTIN_LIB_VERSION);
  Serial.println();

  digitalWrite(12, HIGH);
  Serial.println("\n 8 bits HIGH\n");

  Serial.println("\nPerformance - time in us");
  uint32_t start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.readMSBFIRST();
  }
  uint32_t duration1 = micros() - start;
  Serial.print("FastShiftIn1: ");
  Serial.println(duration1 * 0.001f);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = FSI.readMSBFIRST();
    x = FSI.readMSBFIRST();
  }
  uint32_t duration2 = micros() - start;
  Serial.print("FastShiftIn2: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("       Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();


  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = shiftIn(12, 13, MSBFIRST);
  }
  duration1 = micros() - start;
  Serial.print("Standard shiftIn1: ");
  Serial.println(duration1 * 0.001f);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = shiftIn(12, 13, MSBFIRST);
    x = shiftIn(12, 13, MSBFIRST);
  }
  duration2 = micros() - start;
  Serial.print("Standard shiftIn2: ");
  Serial.println(duration2 * 0.001f);
  Serial.print("            Delta: ");
  Serial.println((duration2 - duration1) * 0.001f);
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

