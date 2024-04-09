//
//    FILE: AverageAngle_setType.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AverageAngle


#include "AverageAngle.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  test_setType();
}


void loop()
{
}


void test_setType()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  AA.add(45);
  AA.setType(AverageAngle::RADIANS);
  AA.add(PI/4);
  AA.setType(AverageAngle::GRADIANS);
  AA.add(50);

  //  expected output
  //  45.00000
  //   0.78540
  //  50.00000
  
  AA.setType(AverageAngle::DEGREES);
  Serial.println(AA.getAverage(), 5);
  AA.setType(AverageAngle::RADIANS);
  Serial.println(AA.getAverage(), 5);
  AA.setType(AverageAngle::GRADIANS);
  Serial.println(AA.getAverage(), 5);

  Serial.println();
}


//  -- END OF FILE --
