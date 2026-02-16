//
//    FILE: ADS_meta_info.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog inputs - straightforward.
//     URL: https://github.com/RobTillaart/ADS1X15


#include "ADS1X15.h"

ADS1115 ADS(0x48);


void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);
  Serial.println();

  Serial.print(ADS.LibName());
  Serial.print(": ");
  Serial.println(ADS.LibVersion());
  Serial.println(ADS.LibURL());
  Serial.println(ADS.LibAuthor());
  Serial.println();

  Serial.print(ADS1115::LibName());
  Serial.print(": ");
  Serial.println(ADS1115::LibVersion());
  Serial.println(ADS1115::LibURL());
  Serial.println(ADS1115::LibAuthor());
}


void loop() 
{
}


//  -- END OF FILE --
