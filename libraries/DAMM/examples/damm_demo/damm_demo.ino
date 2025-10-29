//
//    FILE: DAMM_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/DAMM


#include "DAMM.h"

DAMM damm;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DAMM_LIB_VERSION: ");
  Serial.println(DAMM_LIB_VERSION);
  Serial.println();

  damm.reset();
  Serial.print("test 1: \t");
  Serial.println(damm.isValid("5724"));

  Serial.print("test 2: \t");
  Serial.println(damm.generateChecksum("572"));  //  should be 4.

  //  STREAM MODE
  damm.reset();
  Serial.print("\ntest stream: \t");
  damm.add('5');
  damm.add('7');
  char z = damm.add('2');
  Serial.println(z);  //  should be 4.
}


void loop()
{
}


//  -- END OF FILE --
