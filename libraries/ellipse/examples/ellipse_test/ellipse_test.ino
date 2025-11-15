//
//    FILE: ellipse_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ellipse


#include "ellipse.h"


ellipse el(1, 1);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ELLIPSE_LIB_VERSION: ");
  Serial.println(ELLIPSE_LIB_VERSION);
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
    Serial.print(el.perimeter_reference(), 3);
    Serial.print("\t\t");
    Serial.print(el.circumference(), 3);
    Serial.print('\t');
    Serial.print(100 * abs(el.circumference() - el.perimeter_reference()) / el.perimeter_reference(), 2);
    Serial.print("%\t\t");
    Serial.print(el.perimeter_Kepler(), 3);
    Serial.print('\t');
    Serial.print(100 * abs(el.perimeter_Kepler() - el.perimeter_reference()) / el.perimeter_reference(), 2);
    Serial.print("%\t");
    Serial.print('\n');
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
