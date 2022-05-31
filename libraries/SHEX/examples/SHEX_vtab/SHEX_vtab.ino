//
//    FILE: SHEX_vtab.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SHEX hex dump class
//    DATE: 2022-05-28


#include "SHEX.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHEX_LIB_VERSION: ");
  Serial.println(SHEX_LIB_VERSION);

  Serial.println("\nSHEX DEFAULT");
  SHEX shex(&Serial, 16);
  shex.setHEX();
  for (int i = 0; i < 300; i++)
  {
    char c = random(150);
    shex.print(c);
  }

  for (uint8_t vtab = 0; vtab < 6; vtab++)
  {
    //  shex.flushASCII();   when using SHEXA
    shex.setVTAB(vtab);
    Serial.print("\n\nSHEX VTAB ");
    Serial.println(shex.getVTAB());
    for (int i = 0; i < 300; i++)
    {
      char c = random(150);
      shex.print(c);
    }
  }

  Serial.println("\n Done...\n");
}


void loop()
{
}


// -- END OF FILE --
