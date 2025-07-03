//
//    FILE: print_inch_feet.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo program distance functions
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpersMT.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_LIB_VERSION: ");
  Serial.println(PRINTHELPERS_LIB_VERSION);
  Serial.println();

  //  test some random values
  for (float inch = 0; inch < 100; inch += 5.43)
  {
    Serial.print(inch, 2);
    Serial.print('\t');
    Serial.println(printInch(inch, 32));
  }
  Serial.println();


  for (float feet = 0; feet < 100; feet += 5.43)
  {
    Serial.print(feet, 2);
    Serial.print('\t');
    Serial.println(printFeet(feet));
  }

  //  test small steps
  for (float inch = 0; inch <= 0.5; inch += 0.01)
  {
    Serial.print(inch, 2);
    Serial.print('\t');
    Serial.println(printInch(inch, 32));
  }
  Serial.println();

}


void loop()
{
}


//  -- END OF FILE --
