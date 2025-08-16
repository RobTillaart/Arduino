//
//    FILE: AverageAngle_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance measurement
//     URL: https://github.com/RobTillaart/AverageAngle


#include "AverageAngle.h"

AverageAngle AA(AverageAngle::DEGREES);
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AVERAGE_ANGLE_LIB_VERSION: ");
  Serial.println(AVERAGE_ANGLE_LIB_VERSION);
  Serial.println();
  delay(100);

  AA.reset();
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    AA.add(i);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  float avg = AA.getAverage();
  float len = AA.getAverageLength();
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println();
  delay(100);

  AA.reset();
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    AA.add(i, i);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  avg = AA.getAverage();
  len = AA.getAverageLength();
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println();
  delay(100);

  AA.setType(AverageAngle::RADIANS);
  AA.reset();
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    AA.add(i);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  avg = AA.getAverage();
  len = AA.getAverageLength();
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println();
  delay(100);


  AA.setType(AverageAngle::GRADIANS);
  AA.reset();
  start = micros();
  for (int i = 0; i < 100; i++)
  {
    AA.add(i);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  avg = AA.getAverage();
  len = AA.getAverageLength();
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println();
  delay(100);

  Serial.println("\ndone...");
}

void loop()
{
}


// -- END OF FILE --
