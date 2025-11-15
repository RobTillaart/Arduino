//
//    FILE: ellipse_table.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: generate table for spreadsheet analysis
//     URL: https://github.com/RobTillaart/ellipse
//
//  Q: what is the relation between ratio (B / A) and the perimeter factor
//  perimeter factor = (perimeter / A)

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

  for (float b = 1.0; b >= 0; b = b - 0.02)
  {
    el.setB(b);
    Serial.print(el.getA(), 2);
    Serial.print('\t');
    Serial.print(el.getB(), 2);
    Serial.print('\t');
    Serial.print(el.eccentricity(), 6);
    Serial.print('\t');
    Serial.print(el.perimeter_reference(), 6);
    Serial.print('\t');
    Serial.print(el.perimeter_polynome(), 6);
    Serial.print("\t");
    Serial.print('\n');
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
