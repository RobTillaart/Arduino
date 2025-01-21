//
//    FILE: millis64_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/millis64
//          https://github.com/RobTillaart/printHelpers


#include "millis64.h"
#include "printHelpers.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MILLIS64_LIB_VERSION: ");
  Serial.println(MILLIS64_LIB_VERSION);
}


void loop()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.print(print64(millis64()));  //  no offset
  Serial.print("\t");
  Serial.print(millis32(0xFFFFF000));  //  big offset ~~ small negative offset
  Serial.print("\t");
  Serial.print(print64(millis64(0xFFFFF000)));  //  big offset
  Serial.println();

  delay(random(1000));
}


//  -- END OF FILE --
