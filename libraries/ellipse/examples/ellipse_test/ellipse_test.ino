//
//    FILE: ellipse_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-10-31
//     URL: https://github.com/RobTillaart/ellipse


#include "ellipse.h"


ellipse el(1, 1);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  for (int r = 10; r <= 100; r++)
  {
    float a = r * 0.1;
    el.setA(a);
    Serial.print(el.getB(), 2);
    Serial.print('\t');
    Serial.print(el.getA(), 2);
    Serial.print('\t');
    Serial.print(el.eccentricity(), 3);
    Serial.print('\t');
    Serial.print(el.area(), 3);
    Serial.print('\t');
    Serial.print(el.perimeter_ref(), 3);
    Serial.print("\t\t");
    Serial.print(el.circumference(), 3);
    Serial.print('\t');
    Serial.print(100 * abs(el.circumference() - el.perimeter_ref()) / el.perimeter_ref(), 2);
    Serial.print("%\t\t");
    Serial.print(el.perimeter_Keppler(), 3);
    Serial.print('\t');
    Serial.print(100 * abs(el.perimeter_Keppler() - el.perimeter_ref()) / el.perimeter_ref(), 2);
    Serial.print("%\t");
    Serial.print('\n');
  }

  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --
