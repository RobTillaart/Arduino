//
//    FILE: AGS02MA_setAddress.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: test application
//    DATE: 2021-08-13
//     URL: https://github.com/RobTillaart/AGS02MA
//

#include "AGS02MA.h"


AGS02MA AGS(26);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();

  Serial.print("AGS02MA_LIB_VERSION: ");
  Serial.println(AGS02MA_LIB_VERSION);
  Serial.println();


  bool b = AGS.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);

  b = AGS.setAddress(42);
  Serial.print("SET_ADDR:\t");
  Serial.print(b, HEX);
  Serial.print("\t");
  Serial.print(AGS.lastStatus(), HEX);
  Serial.print("\t");
  Serial.print(AGS.lastError(), HEX);
  Serial.println();

  uint8_t addr = AGS.getAddress();
  Serial.print("GET_ADDR:\t");
  Serial.print(addr, HEX);
  Serial.print("\t");
  Serial.print(AGS.lastStatus(), HEX);
  Serial.print("\t");
  Serial.print(AGS.lastError(), HEX);
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


// -- END OF FILE --
