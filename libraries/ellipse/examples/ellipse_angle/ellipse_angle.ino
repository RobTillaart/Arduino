//
//    FILE: ellipse_angle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ellipse
//
//  use the plotter tool to see the angle() curve.
//

#include "ellipse.h"


ellipse el(1, 1);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  for (int  a = 1; a <= 500; a++)
  {
    el.setA(1 + a * 0.002);
    Serial.print(el.getB(), 2);
    Serial.print('\t');
    Serial.print(el.getA(), 4);
    Serial.print('\t');
    Serial.print(el.angle(), 4);
    Serial.print('\n');
  }

  Serial.println("\nDone...");
}


void loop()
{
}


// -- END OF FILE --
