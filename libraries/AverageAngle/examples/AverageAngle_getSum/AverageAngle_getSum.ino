//
//    FILE: averageAngle_getSum.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demonstrates the usage of the AverageAngle Class
//     URL: https://github.com/RobTillaart/AverageAngle
//
//  View in serial plotter is nice.

#include "AverageAngle.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AVERAGE_ANGLE_LIB_VERSION: ");
  Serial.println(AVERAGE_ANGLE_LIB_VERSION);
  Serial.println();

  test0();
}

void loop()
{
}


void test0()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();

  Serial.println("Degrees\tSumX\tSumY\tLength");
  for (int d = 0; d <= 360; d++)
  {
    AA.add(d);
    Serial.print(d);
    Serial.print("\t");
    Serial.print(AA.getSumX(), 4);
    Serial.print("\t");
    Serial.print(AA.getSumY(), 4);
    Serial.print("\t");
    Serial.print(AA.getTotalLength(), 4);
    Serial.println();
  }
}



//  -- END OF FILE --
