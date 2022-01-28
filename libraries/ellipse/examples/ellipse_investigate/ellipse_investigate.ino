//
//    FILE: ellipse_investigate.ino
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

  for (uint32_t r = 10; r <= 1000000000; r *= 2)
  {
    float a = r * 0.1;
    el.setA(a);
    Serial.print(el.getB(), 2);
    Serial.print('\t');
    Serial.print(el.getA(), 2);
    Serial.print('\t');
    Serial.print(el.perimeter_ref(), 3);
    Serial.print("\t\t");

    // calculate PI back from circumference and Kepplers formula inverted.
    float C = el.perimeter_ref();
    float P = C / (a + 1);   // b == 1
    Serial.print(P, 8);
    Serial.print('\n');
  }

  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --
