//
//    FILE: INA228_meta_data.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: dump metadata
//     URL: https://github.com/RobTillaart/INA228


#include "INA228.h"


INA228 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("INA228_LIB_VERSION: ");
  Serial.println(INA228_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    while(1);
  }

  INA.setMaxCurrentShunt(10, 0.015);

  //  REGISTER 0
  Serial.print("Manufacturer: ");
  Serial.println(INA.getManufacturer(), HEX);
  Serial.print("DIE_ID: ");
  Serial.println(INA.getDieID(), HEX);
  Serial.print("Revision: ");
  Serial.println(INA.getRevision(), HEX);
  Serial.println();

  Serial.print("\nDone");
}


void loop()
{
}


//  -- END OF FILE --
