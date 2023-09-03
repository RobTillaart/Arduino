//
//    FILE: SWSO_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/SWSerialOut


#include "SWSerialOut.h"

SWSerialOut SWSO(7);

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SWSERIALOUT_LIB_VERSION: ");
  Serial.println(SWSERIALOUT_LIB_VERSION);
  Serial.println();

  SWSO.begin(9600);
  SWSO.println("Hello world");

  Serial.println("\nDone...");
}

void loop()
{

}


//  -- END OF FILE --
